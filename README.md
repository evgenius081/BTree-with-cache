<h2>BTreee with cache</h2>

The goal of this project is to implement a B-tree and to measure an enhanced structure where an amount of cache can be used.  
The tree is as described during the lecture. I.e. a tree of order t, has to store at least t-1 elements in each node (except the root) and at most 2t-1.  

First, to implement B-tree - the basic operations are:  
I x - Construct a tree of order x.  
A x - Add the value x to the tree, x is a signed integer. The values added are unique, i.e. there will be no two insertions of the same value (except the case when it was deleted in between).  
? x - Check if the value x is in the tree. If it is present print "x +", otherwise print "x -".  
P   - Print all values that are in the tree in increasing order.  
L t - Load a tree of order t. In the next line there is a tree in a format given as follows. A pair of brackets ( ) signify a node. A value signify a record (key in the tree).  
( )   Hence ( ( ( 1 2 ) 3 ( 4 ) 5 ( 6 7 ) ) 8 ( ( 9 ) 10 ( 11 ) ) ) can be interpreted as the following tree:  
<pre>                                        (         .           8       .    )
                                        (  . 3    .  5   .  )   ( . 10  .  )  
                                        ( 1 2 ) ( 4 ) ( 6 7 )   ( 9 ) ( 11 ) </pre>
S   - Save the tree in the format described above.  
R x - Remove the element x from the tree. The element may be present or not. Hence the operation might not change the elements in the tree, but may force reorganization.  
X   - End the program.  
C x q1, q2, ... - Calculate an impact of a hypothetical cache.   

Assume that you are given a set of quarries q1, ..., qn (the list of quarries ends by a new line character).  
The program can store the result of the quarry in a cache of size x - measured in the number of entries (keys) that can be stored.  
Hence, if the next quarried entry was already visited, the program does not have to visit B-tree, but may simply read the data from cache.  
Due to the fact that the size of the cache is much smaller than the size of B-tree, only chosen entries can be stored.   
The policy that has to be implemented is First-In-First-Out.   
I.e. the first entry that was read to the cache is removed from it when some other entry is read from B-tree and the result has to be added to the cache.   
Keep in mind, that a result "Not found" is a proper result to store in the cache.  
The measure of the impact of the cache is given by the number of accesses to the disk (measured as depth in the B-tree).  
   As an example consider the tree from point L and series of quarries given by C 2  1 2 1 1 3 1.  
The measure without cache is 17.  
The measure with cache is 3 + 3 ( to fill the cache ) + 0 + 0 ( free loads due to the cache) + 2 + 3 (sadly, the entry 1 was removed from the cache, hence it has to be re-loaded) = 11.  
