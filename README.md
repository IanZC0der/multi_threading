# Multithreaded Sieve of Eratosthenes

## Topics
- Multithreading in C
- Sieve of Eratosthenes algorithm
- Using bits to represent numbers

## Introduction
This is originally a project for the operating systems class at PSU. This multi-threaded program implements the [Sieve of Eratosthenes](https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes) 
algorithm to find the prime number between 2 and 10240. Instead of using a large integer array to represent the numbers between 2 and 10240, a "bit-array" is used to keep track of the numbers, 
in which each bit represents an actual number. Each thread enters the bit array to mask the "composite" bit, which involves the mutual exclusion.


## Algorithms
**How to use bits to represent the numbers**

As mentioned, an array of numbers is inappropriate in this project as it's not memory-wise. Instead, we use an array of bits to represent all the numbers. For example, we have 16 bits as follows in little endian fashion:


![Bits](https://user-images.githubusercontent.com/116975970/227818374-3601e05a-6e11-43a0-9e3d-e878903d7cbc.png)


In this case, the first bit 0 represents number 0 and the 16th bit 15 represents number 15. Each number needs only one bit. However, some math needs to performed in order to figure out where the bit representing the number we are looking for is residing in the bit array. For instance, we have an `array` containg three data members of type `uint16_t` and we aree looking for the numbeer 21. First we figure out which one, of the three data members, we should refer to by the divide operation `21/16`, which turns out to be 1. Then the numbeer 21 should be in `array[1]`. To figure out which bit it is, we use the modulo operation `21%16`, which is 5. This positon corresponding to the bit marked "5" in the previous image. 


Thus, we can just loop through all the numbers, find out where the bit is and seive out the multiples. This operatiopn is equivalent to marking the multiples in the [Sieve of Eratosthenes algorithm](https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes).


**How to flip the bits**

All the bits can be initialized to 1 and we need to flip the composite bits to 0 to seive out the composites. In the Sieve of Eratosthenes algorithm, the composites are marked by finding out the multiples of the primes from 2 through `sqrt(N)`. In our algorithm, we don't care about even numbers as they are, for sure, composites. In the implementation, we can set up a mask to flip the even bits to 0 (except 2) in the initialization step.

Thus, we can just use a counter that traverses thourgh all the odd numbers between 2 and the 10240. Each time when a prime number is found, we can just go ahead and flip the bits that represent its multiples. For example, we know 3 is a prime number. Then we flip the bit for 9 (not 6 because 6 is an even number and therefore has been excluded).


**Multithreading**


This is a very good example where multlethreading can be applied. We can use many threads and have each thread flip the bits for the multiples of different prime numbers. For example, if we have two threads, we can use one thread to flip the bits for the multiples of 3 and the other to flip the bits for the multiples of 5. 


Following the logic stated above, we can have a counter, say, a global variable, starts counting from 3 and increments by 2 to traverse all the odd numbers between 2 and 10240 (as discussed, we skip all the even numbers). Each thread that increments the counter will get odd number and then flip the bits for its multiples. However, we cannot have multiple threads entering the counter all together. Therefore, we need to set up a critical region. The pseudo code is as follows.


```
global counter = 1
...
def nextOddNumber():
  mutex lock
  thread_lock(&lock)
  counter += 2
  thread_unlock(&lock)
  return counter
```

In this way, each thread gets a unique odd number and it's guarantteed that no odd numbers can be missed.


The next question is, how to guaranttee that multiples threads cannot flip the same bit at the same time. An intuition is that a mutex lock need to set. But how? To figure out this question, we need to refer to the pesudo code below.


```
1 def seive():
2   for(i = nextOddNumber(); i <= sqrt(MAX); i = nextOddNumber())
3    for(j = i*i; j < MAX; j += i) // find all the multiples of the odd bit
4      if(j is even number)
5        continue
6      flipBit(j)
```

The answer should be obvious now. We just need to set `line 6` to critical region. 


**Review**
To be updated.
