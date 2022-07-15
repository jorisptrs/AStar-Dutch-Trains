# AStar and Dijstra's Search Algorithms for Dutch Train Routing

## Problem description

This finds the shortest path between two of eleven Dutch cities accounting for routes under construction.

## Input-output behavior

The input consists of a positive integer n that denotes the number of connections that should be removed. The number n is followed by a set of n pairs of strings, containing city names, which denote which direct connections between cities should be discontinued. These pairs of strings are then followed by another set of any number of string pairs that denote the start and end of each journey. The program is terminated by the character "!". The output consists of the city names denoting the shortest path from the starting location to the goal location followed by the time in minutes, or the string "UNREACHABLE" if no path exists. This is repeated for every pair of strings in the second set of the input.

## Example
**Input**
```3
Leeuwarden
Groningen
Utrecht
Zwolle
Enschede
Zwolle
Leeuwarden
Groningen
Amsterdam
Groningen
Enschede
Eindhoven
!
```
**Output**
```
Leeuwarden
Meppel
Groningen
90
Amsterdam
Utrecht
Eindhoven
Nijmegen
Zwolle
Meppel
Groningen
270
UNREACHABLE
```

## Solution
A weighted graph was used to represent the problem (dutch train system). As the search tree resulting from this problem has infinite depth, A*, a variation of Dijkstra's shortest path algorithm was used to intruduce a geographic heuristic to the search; A* prioritizes the city where the sum of the pseudo-distance and the straight line distance between the goal and the given city (heuristic) is minimal. A priority queue was used for this purpose. This is the main algorithm:

```
algorithm aStar()
    input: a weighted graph G, the nodes start and end
    output: the shortest distance from start to end
    result: the path is marked in the graph
    create empty minimum priority queue S
    forall city c in G do
        add c to S
        if c = start then /* initialize pseudo distances*/
            d[c] <- 0
        else
            d[c] <- 1
        while S not empty do
            u <- city in S with smallest d[u] + h[u] /* distance plus heuristic */
            remove u from S
            if u = end or d[u] = 1 then
                return distance to u /* if the distance to the dequeued item is still 1, the goal is unreachable*/
            forall e incident with u do
                z <- the city lead to by e from u
                relaxation(u,z,S,G)
```

## Run

From the Astar or Dijkstra directory:
```
gcc * -lm
./a.out
```