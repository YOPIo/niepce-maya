#include "arena_allocator.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
auto AllocateAligned (size_t bytes) -> void*
{
  return memalign (kMemoryAlignment, bytes);

  /*
  void* ptr = nullptr;
  if (posix_memalign (&ptr, kMemoryAlignment, bytes) != 0)
  {
    ptr = nullptr;
  }
  return ptr;
  */
}
/*
// ---------------------------------------------------------------------------
*/
auto FreeAligned (void* ptr) -> void
{
  if (ptr != nullptr)
  {
    free (ptr);
  }
}
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
