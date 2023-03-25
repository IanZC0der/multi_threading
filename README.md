# multi_threading
## Introduction
This is originally a project for the operating systems class at PSU. This multi-threaded program implements the [Sieve of Eratosthenes](https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes) 
algorithm to find the prime number between 2 and 10240. Instead of using a large interger array to repreesent the numbers between 2 and 10240, a "bit-array" is used to keep track of the numbers, 
in which each bit represents an actual number. Each thread enters the bit array to mask the "composite" bit, which involves the mutual exclusion.




