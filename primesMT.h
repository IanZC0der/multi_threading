#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <unistd.h>
#include <stdint.h>
#include <pthread.h>
#include <math.h>

#ifndef UPPER_LIMIT
# define UPPER_LIMIT 10240
#endif // UPPER_LIMIT

#ifndef DEF_LIMIT
# define DEF_LIMIT 10240
#endif // DEF_LIMIT

#ifndef BITS_SIZE
# define BITS_SIZE 32
#endif // BITS_SIZE
typedef struct BitBlock_s {
	uint32_t bits;
	pthread_mutex_t mutex;
} BitBlock_t;

BitBlock_t *allocBitsList(void);
void init(BitBlock_t *);
void freeList(BitBlock_t *);
void printToFileOrScreen(BitBlock_t *);
void *setBit(void *);
int nextCandidate(void);
//int createMask(void);
