#include "rng.h"

static const uint64_t a = 0x5deece66dULL;
static const uint64_t c = 0xb;
static const uint64_t m = 1ULL << 48;

void rng_init(struct rng *rng, uint64_t seed)
{
    rng->seed = (seed ^ a) % m;
}

uint32_t rng_gen32(struct rng *rng)
{
    uint64_t next;
    next = (a * rng->seed + c) % m;
    rng->seed = next;
    return next >> 16;
}

double rng_gend(struct rng *rng)
{
    // This is what Java seems to do
    uint64_t x =
            (((uint64_t) rng_gen32(rng) >> 6) << 27) + (rng_gen32(rng) >> 5);
    return x / ((double) (1ULL << 53));
}

void rng_gen(struct rng *rng, void *buf, size_t size)
{
    uint32_t x;
    while (size >= 4) {
        * ((uint32_t *) buf) = rng_gen32(rng);
        buf = (void*) ((uintptr_t) buf + 4);
        size -= 4;
    }

    x = rng_gen32(rng);
    while (size > 0) {
        * ((uint8_t *) buf) = x >> 24;
        x <<= 8;
        buf = (void*) ((uintptr_t) buf + 1);
        size--;
    }

}

