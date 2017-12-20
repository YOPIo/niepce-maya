#ifndef _ARENA_H_
#define _ARENA_H_
/*
// ---------------------------------------------------------------------------
*/
#include <cstddef>
#include <cstdlib>
#include <memory>
#include <malloc.h>
#include <list>
#include <utility>
#include <algorithm> // for windows to use std::max () and std::min ()
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
// Memory constant value
// ---------------------------------------------------------------------------
*/
constexpr size_t kMemoryAlignment = 64;
/*
// ---------------------------------------------------------------------------
// Memory allocator utility functions
// ---------------------------------------------------------------------------
*/
auto AllocateAligned (size_t bytes) -> void*;
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto AllocateAligned (size_t bytes) -> T*
{
  return reinterpret_cast<T*> (AllocateAligned (bytes * sizeof (T)));
}
/*
// ---------------------------------------------------------------------------
*/
auto FreeAligned (void* ptr) -> void;
/*
// ---------------------------------------------------------------------------
// Fixed arena memory allocator
// ---------------------------------------------------------------------------
*/
class ArenaAllocator
{
  /* ArenaAllocator constructors */
 public:
  ArenaAllocator (size_t block_size = 262144) :
      block_size_         (block_size),
      current_block_pos_  (0),
      current_alloc_size_ (0),
      current_block_      (nullptr),
      used_blocks_        (),
      available_blocks_   ()
  {}


  /* ArenaAllocator destructor */
 public:
  ~ArenaAllocator ()
  {
    FreeAligned (current_block_);
    for (auto& block : used_blocks_)
    {
      FreeAligned (block.second);
    }
    for (auto& block : available_blocks_)
    {
      FreeAligned (block.second);
    }
  }


  /* ArenaAllocator public operators*/
 public:
  ArenaAllocator (ArenaAllocator&& arena) = default;
  auto operator =     (ArenaAllocator&& arena)
      -> ArenaAllocator& = default;

  /* ArenaAllocator private operators */
 private:
  ArenaAllocator (const ArenaAllocator& arena) = default;
  auto operator =     (const ArenaAllocator& arena)
      -> ArenaAllocator& = default;


  /* ArenaAllocator public methods */
 public:
  template <typename T, typename ...ArgTypes>
  auto Allocate (ArgTypes&& ... args) -> T*
  {
    // T* ret = (T*) Allocate (sizeof (T));
    T* ret = reinterpret_cast <T*> (Allocate (sizeof (T)));
    new (ret) T (std::forward<ArgTypes> (args) ...);
    return ret;
  }

 private:
  auto Allocate (size_t num_bytes) -> void*
  {
    // Round up to power of two
    num_bytes = RoundUp (num_bytes);

    if (current_block_pos_ + num_bytes > current_alloc_size_)
    {
      if (current_block_)
      {
        used_blocks_.push_back
            (std::make_pair (current_alloc_size_, current_block_));
        current_block_      = nullptr;
        current_alloc_size_ = 0;
      }

      for (auto iter = available_blocks_.begin ();
           iter != available_blocks_.end (); ++iter)
      {
        if (iter->first >= num_bytes)
        {
          current_alloc_size_ = iter->first;
          current_block_      = iter->second;
          available_blocks_.erase (iter);
          break;
        }
      }

      if (!current_block_)
      {
        current_alloc_size_ = std::max (num_bytes, block_size_);
        current_block_      = AllocateAligned <uint8_t> (current_alloc_size_);
      }
      current_block_pos_ = 0;
    }

    void* ret = current_block_ + current_block_pos_;
    current_block_pos_ += num_bytes;

    return ret;
  }

  auto Clear () -> void
  {
    current_block_pos_ = 0;
    available_blocks_.splice (available_blocks_.begin (), used_blocks_);
  }

  auto CurrentBlockSize () const -> size_t
  {
    // TODO: 
  }

  auto TotalAllocated () const -> size_t
  {
    // TODO: 
  }


  /* ArenaAllocator private methods */
 private:
  // Round up to power of two
  auto RoundUp (size_t num_bytes) -> size_t
  {
    // Get maximum alignment
#if __GNUC__ == 4 && __GNUC_MINOR__ < 9
    // gcc bug: max_align_t wasn't in std:: until 4.9.0
    const int align = alignof(::max_align_t);
#else
    const size_t align = alignof (std::max_align_t);
#endif
    return (num_bytes + align - 1) & ~(align - 1);
  }


  /* ArenaAllocator private data */
 private:
  const size_t block_size_;
  size_t       current_block_pos_;
  size_t       current_alloc_size_;
  uint8_t*     current_block_;
  std::list<std::pair<size_t, uint8_t*>> used_blocks_, available_blocks_;

}; // class ArenaAllocator
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _ARENA_H_
