#ifndef MICROBENCH_H_
#define MICROBENCH_H_

#include <stdint.h>
#include <utils.h>

static inline uint64_t rdtsc(void)
{
    uint32_t eax, edx;
    asm volatile ("rdtsc" : "=a" (eax), "=d" (edx));
    return ((uint64_t) edx << 32) | eax;
}

static inline uint32_t kill_cycles(uint32_t cyc, uint32_t opaque)
{
  uint64_t start = rdtsc();
  uint64_t end = start + cyc;

  if (end >= start) {
    while (rdtsc() < end) {
      opaque = opaque * 42 + 37;
      opaque ^= 0x12345678;
      opaque = opaque * 42 + 37;
      opaque ^= 0x87654321;
    }
  } else {
    while (rdtsc() >= start || rdtsc() < end) {
      opaque = opaque * 42 + 37;
      opaque ^= 0x12345678;
      opaque = opaque * 42 + 37;
      opaque ^= 0x87654321;
    }
  }
  return opaque;
}

#endif /* ndef MICROBENCH_H_ */
