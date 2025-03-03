## Collection of data structures
Just a bunch of data structures that I've coded myself/find interesting

### Segment/Range Tree
Most range trees I was found are inclusive-exclusive range tree (which I hated). Later on, I was shown a 1D inclusive-inclusive range tree a while back, and really liked it.

When I recently found out of the existance of a 2D range tree - where you can query any sub-square in a 2D array - I wanted to code an inclusive-inclusive version of it because I can't find any online. Queries I supported were sum, min, and max.

It works basically by having a range tree inside of every single node of the range tree.

I have tested it and everything, so I'm mostly confident that it works.


### Dijkstra's
The implementation is very similar copied from the one that is found in COMP4128, but I added a bunch of comments to understand what is happening

I didn't test it, so please don't use it for your own uses.