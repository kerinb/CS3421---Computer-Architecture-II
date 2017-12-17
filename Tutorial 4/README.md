# Computer Architecture CS3421 - Tutorial 4#
## LKN Cache Simulation ##

### Description of Tutorial###

The purpose of this assignment is to model the operation of an LKN cache. For this model, we are to assume; and use, a
**L**east **R**ecently **U**sed;_LRU_, eviction policy. This program will be used to simulate a 16KB direct mapped
_instruction_; _L = 16, K = 1, N = 1024, cache and an 8-way 32KB data cache; _L = 16, K = 8, N = 256_.

In this program the data is read in from the **gcc1.trace** file; This file is a 16MB address trace file supplied by the
lecturer; Jeremy Jones. This address file contains all of the physical addresses accessed by an I486 microprocessor while
gcc was compiling a program.

### Description of Code ###

This program was written in the programming language **python 3.5.2**, the program was written and tested on my laptop.
#### Laptop specs ####
1.   Intel Core i7-6500
2.   8 GB RAM
3.   1 TB HDD
4.   OS - Linux Mint

This program has 3 files:
1.   main.py
2.   Cache.py
3.   CacheFunctions.py

1.   *main*.py
The *main.py* instantiates two versions of the cache object; these modelling *data* and *instruction* caches. This file
also measures the time taken to determine the number of hits and misses using the instruction and data caches. The results
obtained are also printed to terminal using this file.

2.   *Cache*.py
The cache file models a cache as an object. The cache object has the following attributes:
*   L, K, N, lru_queue, cache_sets, directories, tag_mask, set_mask, offset_mask, set_shift, tag_shift, hits, misses
*   TODO - Talk more about the implementation here

3.   *CacheFunctions*.py
*    TODO - Talk about the implementationhere

## Results ##
Using the machine with the specs I have highlighted above in *Laptop specs*, the results I achieved are highlighted in the
image below.

![Alt text](compArchRes.png "Results Obtained for Cache Simulation.")

The number of hits and misses obtained for the instruction cache are: *328780* and *27695* respectively
The number of hits and misses obtained for the data cache are: *511464* and *7909* respectively
The time taken to compute the above metrics was 1503.2337 ms. This time was significantly larger than the time expected
for this program. The expected time taken for this program was 100ms. Hence, my solution, on my machine is 15X the expected
time.
 TODO - dicuss the results a bit more. possible issues with time; machine, implemenation,

