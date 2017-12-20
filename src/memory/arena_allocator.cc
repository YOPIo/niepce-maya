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
#ifdef _WIN64
    return _aligned_malloc (bytes, kMemoryAlignment);
#else
    return memalign (kMemoryAlignment, bytes);
#endif // _WIN64



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
