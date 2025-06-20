## Collection of data structures
Just a bunch of data structures that I've coded myself/find interesting

### 1D Segment/Rage Tree
Most range trees I was found are inclusive-exclusive range tree (which I hated). Later on, I was was informed of the existence of a 1D inclusive-inclusive range tree, which made a lot more sense.

This is my implementation of it. Queries support is sum, but it can be easily expanded to include min and max.

It is tested, so feel free to use it.

### 2D Segment/Range Tree
When I out that 2D range trees existed - ie. where you can query any sub-square in a 2D array in log^2(n) time - I wanted to code an inclusive-inclusive version of it because I can't find any online. Queries supported are sum, min, and max.

Basic idea is that you have a segment tree for every row, and then another segment tree for every node of the outer segment tree. A full explanation can be found [here](https://cp-algorithms.com/data_structures/segment_tree.html#generalization-to-higher-dimensions).

It is tested, so feel free to use it.

### Dijkstra's
There are multiple possible implementations of Dijkstra's. I just used one which was easy to code, and added a bunch of comments to explain what is happening.

I didn't test it, so use it at your discretion.

### Bellman Ford
Coded from scratch. Documentation can use a bit more work. Might update in the future.
