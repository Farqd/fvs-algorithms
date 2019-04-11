# Bipartite-Permutation Graph

Implementation based on: https://www.researchgate.net/publication/261490799_On_Minimum_Feedback_Vertex_Sets_in_Graphs

* Some bugs in pseudocode from paper :(
  * `i1 = i1` in line 6, same for `j1`, should be `i1 = i - 1`
  * `l(j1) = i2` in line 11, should be `l(i1) = j2` instead 
* I implemented it in a form of `permutation` -> `graph` -> `FVS`, thus my time complexity is `O(N*log(N) + M)`, in the algorithm we need to list all edges and I don't think there is any way to calculate them faster (I use MergeSort)
* I could implement `graph -> permutation` step as well (algorithm requires both list of edges and starting permutation), but it is not trivial
* I don't know how to generate non-trivial biparite-permutation, right now I tested on all graphs with `size <= 10` for correctness and some trivial big ones for performance (seems to be in line with `O(N*log(N) + M)`)