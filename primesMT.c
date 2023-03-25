#include "primesMT.h"

static int numThreads = 1;
static int upperLimit = DEF_LIMIT;
static BitBlock_t *bitsList = NULL;
static int size = 0;
static int isVerbose = 0;


/*
int createMask(void) {	
	int mask = 0;
	for(int i = 0; i <= BITS_SIZE - 1; i += 2)
		mask |= (1 << i);
	return ~mask;
}
*/

BitBlock_t *allocBitsList(void) {
	BitBlock_t *aList;
	size = upperLimit/BITS_SIZE + 1;
	aList = malloc(size * sizeof(BitBlock_t));
	/*
	for(int i = 0; i < size; ++i) {
		aList[i] = malloc(sizeof(BitBlock_t));
	}
	*/

	return aList;
}

void init(BitBlock_t *list) {
	for(int i = 0; i < size; ++i) {
		list[i].bits = ~0;
		pthread_mutex_init(&list[i].mutex, NULL);
	}
	/*
	list[0]->bits &= ~2;
	list[0]->bits |= (1 << 2);
	*/
}

void freeList(BitBlock_t *list) {
	for(int i = 0; i < size; i++) {
		pthread_mutex_destroy(&list[i].mutex);
	}// free the mutex lock
	free(list);
}


void printToFileOrScreen(BitBlock_t *list) {
	/*
	FILE *op = NULL;
#define FILE_NAME "primes.txt"
	op = fopen(FILE_NAME, "w");
	if(!op) {
		perror("could not open file : " FILE_NAME);
		exit(17);
	}
	

	fprintf(op, "%d\n", 2);
	for(int i = 3; i < upperLimit; i += 2) {
		if((list[i/BITS_SIZE].bits >> (i % BITS_SIZE)) & 1)
				fprintf(op, "%d\n", i);
	}
	fclose(op);//print to a txt file
	*/
	printf("%d\n", 2);
	for(int i = 3; i < upperLimit; i += 2) {
		if((list[i/BITS_SIZE].bits >> (i % BITS_SIZE)) & 1)
				printf("%d\n", i);
	} //loop through all the odd numbers. Even numbers are excluded as by no means they can be prime numbers except 2
}

void *setBit(void *) {
	for(int i = nextCandidate(); i <= sqrt(upperLimit); i = nextCandidate()) {
		for(int j = i * i; j < upperLimit; j += i){
			if(j % 2 == 0)
				continue; // ignore the even numbers
			pthread_mutex_lock(&bitsList[j/BITS_SIZE].mutex);
			bitsList[j/BITS_SIZE].bits &= ~(1 << (j % BITS_SIZE)); // set composite bits to 0
			pthread_mutex_unlock(&bitsList[j/BITS_SIZE].mutex);
		}
	}
	pthread_exit(EXIT_SUCCESS);
}

int nextCandidate(void) {
	static int nextBit = 3;
	static pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
	int currBit = 0;
	pthread_mutex_lock(&lock);
	currBit = nextBit;
	nextBit += 2;
	pthread_mutex_unlock(&lock);
	return currBit;
}

int main(int argc, char *argv[]) {
	pthread_t *threads = NULL;
	long tid = 0;
	{
		int opt = 0;
		while((opt = getopt(argc, argv, "t:u:hv")) != -1) {
			switch(opt) {
				case 't':
					numThreads = atoi(optarg);
					break;
				case 'u':
					upperLimit = atoi(optarg);
					/*
					if(upperLimit < DEF_LIMIT)
						upperLimit = DEF_LIMIT;
					else if(upperLimit > UPPER_LIMIT)
						upperLimit = UPPER_LIMIT;
						*/
					break;
				case 'h':
					printf("%s: -t # -u # -h -v\n", argv[0]);
                                        printf("\t-t #: number of threads\n");
 					printf("\t-u #: size of matrix\n");
 					printf("\t-h: help\n");
 					printf("\t-v: verbose mode\n");
					exit(0);
       					break;

				case 'v':
					isVerbose = 1;
					fprintf(stderr, "verbose processing\n");
					break;
				default:
					exit(EXIT_FAILURE);
					break;
			}
		}
	}
	bitsList = allocBitsList();
	init(bitsList);
	threads = malloc(numThreads * sizeof(pthread_t));
	for(tid = 0; tid < numThreads; tid++){
		pthread_create(&threads[tid], NULL, setBit, (void *) tid);
	}
	for(tid = 0; tid < numThreads; tid++){
		pthread_join(threads[tid], NULL);
	}
	printToFileOrScreen(bitsList);
	freeList(bitsList);
	free(threads);
	bitsList = NULL;
	pthread_exit(EXIT_SUCCESS);
	return EXIT_SUCCESS;
}
