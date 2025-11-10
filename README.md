# AI Lab Work 

Here are some codes which i had done in my AI Practical lab

## DAY 1 : Solving Eight Puzzel Problem with diffrent methods

### 1. Eight Puzzel Problem Using Breath First Search Technique

BFS is used to find the shortest path or minimum number of moves required to reach the goal state from a given start state in an unweighted problem like the 8-puzzle.It explores all possible moves level by level.

**How it works :-**

   1.It starts with the initial puzzle configuration.

   2.It uses a queue (FIFO) to explore all possible next moves (left, right, up, down) of the blank tile.

   3.Each new configuration is stored in a visited (closed) set to avoid repetition.

   4.The algorithm continues expanding states level by level until the goal configuration is found.

   5.Once the goal is found, the search stops — this ensures minimum steps are used.

**Time Complexity :-**

   O(b^d)

   b = branching factor (average 2–3 moves possible)

   d = depth of the solution

   → Exponential growth as depth increases.

**Space Complexity:**

   O(b^d) — Because BFS stores all generated states (open and closed lists) in memory.

**Output:**

<img width="416" height="224" alt="image" src="https://github.com/user-attachments/assets/c841dea9-2836-4cb9-866e-2e53e3ef25e3" />


### 2. Eight Puzzel Problem Using Depth First Search Technique

DFS is used to search or traverse all possible puzzle states in a deep manner — it explores one path fully before backtracking.
In this 8-puzzle program, DFS is used to reach the goal configuration (1 2 3 4 5 6 7 8 0) from a given start state.

**How It Works :-**

   1.The algorithm starts from the initial state and uses a stack (LIFO) to explore moves.

   2.It moves the blank tile (0) in all possible directions (left, right, up, down).

   3.Each new configuration is pushed onto the stack if it hasn’t been visited before.

   4.DFS goes deep along one path, and when it cannot move further, it backtracks to explore another path.

   5.It continues until the goal state is reached or no more new states are left.

**Inversion Concept (Solvability Check)  :- **

   Before DFS starts, the code checks whether the puzzle is solvable.

   Inversion = when a higher-numbered tile precedes a lower-numbered tile (ignoring 0).

   For a 3×3 puzzle →

   Even inversions ⇒ Solvable 

   Odd inversions ⇒ Unsolvable 

**Time Complexity:**

   O(b^d), where

   b = branching factor (average number of possible moves ≈ 2–3)

   d = maximum depth of search

   DFS can explore many states; hence complexity grows exponentially in the worst case.

**Space Complexity:**

   O(b·d) → because it stores only the current path in the stack (less memory than BFS).


**Output:**

<img width="659" height="334" alt="image" src="https://github.com/user-attachments/assets/2c8fd960-e912-4338-83ea-dca2c86c90e1" />

### Eight puzzel Problem Uisng Hill climbing :

A greedy local search to quickly move toward the goal by always choosing the neighbor with the lowest heuristic (h). It’s fast and memory-light, but not guaranteed to find the optimal path—or any solution—because it can get stuck.

**How it works :**

   1.Start at the initial board; compute h = Manhattan distance.

   2.Generate all valid neighbors (move blank U/D/L/R).

   3.Pick the neighbor with strictly smaller h (best improvement).

   4.Move there and repeat.

   5.If no neighbor improves h, stop ⇒ you’re on a local minimum / plateau (or shoulder).

**Complexity**

   **Per step:** generate ≤4 neighbors and compute h → O(1) neighbors × O(N²) to compute h ⇒ ~O(N²) per move (here, N=3).

   **Total:** depends on steps taken until stuck/goal; no global bound—often much less than exhaustive search, but not complete.

   **Space:** stores only current state + neighbors ⇒ O(1) (very small).

**Output :**


<img width="549" height="772" alt="image" src="https://github.com/user-attachments/assets/d7d8a5af-31d5-499b-b13e-bec48578ac4e" />


## DAY 2 : Path finding using diffrent algorithm :

### 1. A* algorithm :

A* algorithm is used to find the shortest and most efficient path from a given start node to a goal node, using both the actual cost and an estimated cost (heuristic).
It is widely used in pathfinding, AI navigation, and puzzle-solving.

**How It Works :**

   f(n) = g(n) + h(n)
   g(n) → cost from the start node to the current node
   h(n) → estimated cost from the current node to the goal (heuristic)

   1. The algorithm always selects the node with the lowest f(n).

   2.It expands that node and updates the cost of its neighbors.

   3. This continues until the goal node is reached or all paths are exhausted.

   4. The Manhattan distance is used as the heuristic function in this code.

**Time Complexity:**

   O(E log V) — because it uses a priority queue (min-heap) for node selection.
   (E = number of edges, V = number of vertices)


**Space Complexity:**
 O(V) — for storing open and closed lists (visited nodes and costs).

**Output :**

<img width="564" height="131" alt="Screenshot 2025-11-10 213327" src="https://github.com/user-attachments/assets/7dbfba74-f456-49bc-8f50-d79af9708eab" />


### 2. Water Jug Problem 

Finds the minimum number of steps to measure exactly target liters using two jugs of capacities jug1 and jug2, by exploring all valid states level by level.

**How It Works :- **

1.   State = (x, y) where x = water in jug1, y = water in jug2.

2.   Start from (0, 0); push to a queue; mark visited.

3.   From each state, generate all legal next states:

 ->  Fill jug1: (jug1, y)

 ->  Fill jug2: (x, jug2)

 ->  Empty jug1: (0, y)

 ->  Empty jug2: (x, 0)

 ->  Pour jug1 → jug2

 ->  Pour jug2 → jug1

4.   Stop when x == target or y == target.

5.   Use a parent map to reconstruct and print the path (sequence of states).

**Time Complexity**

O(jug1 × jug2) states at most; each processed once → O(C1·C2).

Each expansion generates a constant number of moves.

**Space Complexity**

O(C1·C2) for the visited set and parent map.

**Solvability Condition (important for viva) :**

A solution exists iff target ≤ max(jug1, jug2) and target % gcd(jug1, jug2) == 0.

**Output :**

<img width="404" height="143" alt="Screenshot 2025-11-11 013208" src="https://github.com/user-attachments/assets/ed25185b-1bc7-4a20-82fa-23cb26cc1285" />



















   





