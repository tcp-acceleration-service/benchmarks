#ifndef RNG_H_
#define RNG_H_

#include <stddef.h>
#include <stdint.h>

struct rng {
    uint64_t seed;
};

void rng_init(struct rng *rng, uint64_t seed);
uint32_t rng_gen32(struct rng *rng);
/** Double uniform between 0 and 1 */
double rng_gend(struct rng *rng);
void rng_gen(struct rng *rng, void *buf, size_t size);

#endif // ndef RNG_H_
