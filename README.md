# fvs-algorithms


# Currently implemented algorithms

## Interval Graphs

Implementation inspired by https://www.researchgate.net/publication/228903606_An_algorithm_to_find_a_minimum_feedback_vertex_set_of_an_interval_graph

* `O((N+M)*log(M))` - `log` comes from sorting input
* We don't need to explicitly create all cliques, simpler greedy algorithms is enough 

## Chordal Graphs

Based on https://www.sciencedirect.com/science/article/pii/0166218X88900868

* Article presents solution to more general problem, for it FVS gives `O(N^5)` time complexity, I haven't found any faster algorithm
* I take list of edges as input, test if graph is Chordal, then run dynamic programming solution based on perfect elimination order

## Permutation Graphs

Implementation based on https://www.sciencedirect.com/science/article/pii/0020019094001332
* Works in `(N*M)`
* I take `permutation` as input
* Pseudocode in the article had lot's of bugs/typos :(

## Bipartite-Permutation Graphs

Implementation based on https://www.researchgate.net/publication/261490799_On_Minimum_Feedback_Vertex_Sets_in_Graphs

* Code takes permutaiton as an input, thus my time complexity is `O(N*log(N) + M)`, in the algorithm we need to list all edges and I don't think there is any way to calculate them faster (I use MergeSort)
* Taking list of edges as an input would require implementing recognition of permutation graph class
* I don't know how to generate non-trivial biparite-permutation, right now I tested on all graphs with `size <= 10` for correctness and some trivial big ones for performance (seems to be in line with `O(N*log(N) + M)`)
* Some bugs in pseudocode from paper :(
  * `i1 = i1` in line 6, same for `j1`, should be `i1 = i - 1`
  * `l(j1) = i2` in line 11, should be `l(i1) = j2` instead 



# Building & running library

## Google Test
I use gtest as git submodule `third_party/googletest`, you can pull it when cloning  
```bash
git clone --recursive URL
```  
or after cloning by executing 
```bash
git submodule init
git submodule update
```

## Buck

Before building you need to install buck  
https://buckbuild.com/  

You can do it by building from sources or as follows:

```bash
wget https://github.com/facebook/buck/releases/download/v2019.01.10.01/buck.2019.01.10.01_all.deb
sudo dpkg -i buck.2019.01.10.01_all.deb
```

## build & run tests

in main folder:

```bash
buck build test:test
buck test --all
```

## build library

```bash

buck build //:fvs-algorithms

```

## build graph_class/main.cpp file

to build chordal/main.cpp use:

```bash

buck build //:chordal_main --out executable_name

```

similar for `chordal_main`, `permutation_main`, `bipartite_permutation_main`




