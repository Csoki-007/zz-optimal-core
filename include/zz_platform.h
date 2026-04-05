#ifndef ZZ_PLATFORM_H
#define ZZ_PLATFORM_H

#include <cstddef>
#include <cstdint>

uint64_t zz_platform_now_us();
size_t zz_platform_free_heap_bytes();
size_t zz_platform_min_free_heap_bytes();
uint32_t zz_platform_cpu_freq_mhz();
void zz_platform_checkpoint();

#endif
