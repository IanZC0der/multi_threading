# multi_threading

## Topics
- Multithreading in C
- Sieve of Eratosthenes algorithm
- Using bits to represent numbers

## Introduction
This is originally a project for the operating systems class at PSU. This multi-threaded program implements the [Sieve of Eratosthenes](https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes) 
algorithm to find the prime number between 2 and 10240. Instead of using a large interger array to represent the numbers between 2 and 10240, a "bit-array" is used to keep track of the numbers, 
in which each bit represents an actual number. Each thread enters the bit array to mask the "composite" bit, which involves the mutual exclusion.


## Algorithms
**How to use bits to represent the numbers**

As mentioned, an array of numbers is inappropriate in this project as it's not memory-wise. Instead, we use an array of bits to represent all the numbers. For example, we have 16 bits as follows in little endian fashion:


![Bits](https://user-images.githubusercontent.com/116975970/227818374-3601e05a-6e11-43a0-9e3d-e878903d7cbc.png)


In this case, the first bit 0 represents number 0 and the 16th bit 15 represents number 15. Each number needs only one bit. However, some math needs to performed in order to figure out where the bit representing the number we are looking for is residing in the bit array. For instance, we have an `array` containg three data members of type `uint16_t` and we aree looking for the numbeer 21. First we figure out which one, of the three data members, we should refer to by the divide operation `21/16`, which turns out to be 1. Then the numbeer 21 should be in `array[1]`. To figure out which bit it is, we use the modulo operation `21%16`, which is 5. This positon corresponding to the bit marked "5" in the previous image. 


Thus, we can just loop through all the numbers, find out where the bit is and seive out the multiples. This operatiopn is equivalent to marking the multiples in the [Sieve of Eratosthenes algorithm](https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes).


**How to flip the bits**

