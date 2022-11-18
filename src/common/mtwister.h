#ifndef MTWISTER_H
#define MTWISTER_H
#ifndef __MTWISTER_H
#define __MTWISTER_H

#define STATE_VECTOR_LENGTH 624
#define STATE_VECTOR_M 397
/* changes to STATE_VECTOR_LENGTH also require changes to this */

typedef struct tagMTRand
{
    unsigned long mt[STATE_VECTOR_LENGTH];
    int index;
} MTRand;

MTRand seed_rand(unsigned long seed);
unsigned long gen_rand_long(MTRand *rand);
double gen_rand(MTRand *rand);

#endif /* #ifndef __MTWISTER_H */

#endif /* MTWISTER_H */
