
### requirements
- Array of indexes
- Memory Pool
- Next, Last ptr to other arrays

### functions
- create - creates a singular empty pool
- add - adds new variable of size x
- clear - clears variable from pool
- destroy - destroys all the pools that are interconnected
- defragment - copies contents of current pool into new pool while removing fragmentation
- set, copy, get - normal memory operations with access checks
- get pointer - returns pointer and let's just hope it works
- check ptr access - check if ptr access is within memory pool or within variable
- register memMove callback - will call function if pointer is altered
- register memDelete callback

### internal behaviors
- check if new variable fits in memory
	- allocate new pool if no
	- if variable bigger than default pool size allocate separate pool for variable
- thread locks (binary operations) - in case multiple threads access same data
- 