# AI Lab Work 

Here are some codes which i had done in my AI Practical lab

## DAY 1 : Solving Eight Puzzel Problem with diffrent methods

#### 1. Eight Puzzel Problem Using Breath First Search Technique

BFS is used to find the shortest path or minimum number of moves required to reach the goal state from a given start state in an unweighted problem like the 8-puzzle.It explores all possible moves level by level.

How it works :-
It starts with the initial puzzle configuration.

It uses a queue (FIFO) to explore all possible next moves (left, right, up, down) of the blank tile.

Each new configuration is stored in a visited (closed) set to avoid repetition.

The algorithm continues expanding states level by level until the goal configuration is found.

Once the goal is found, the search stops — this ensures minimum steps are used.

Time Complexity :-

O(b^d)

b = branching factor (average 2–3 moves possible)

d = depth of the solution

→ Exponential growth as depth increases.

Space Complexity:

O(b^d) — Because BFS stores all generated states (open and closed lists) in memory.

**Output:**

<img width="416" height="224" alt="image" src="https://github.com/user-attachments/assets/c841dea9-2836-4cb9-866e-2e53e3ef25e3" />


#### 2. Eight Puzzel Problem Using Depth First Search Technique

DFS is used to search or traverse all possible puzzle states in a deep manner — it explores one path fully before backtracking.
In this 8-puzzle program, DFS is used to reach the goal configuration (1 2 3 4 5 6 7 8 0) from a given start state.

**How It Works :-**

The algorithm starts from the initial state and uses a stack (LIFO) to explore moves.

It moves the blank tile (0) in all possible directions (left, right, up, down).

Each new configuration is pushed onto the stack if it hasn’t been visited before.

DFS goes deep along one path, and when it cannot move further, it backtracks to explore another path.

It continues until the goal state is reached or no more new states are left.

** Inversion Concept (Solvability Check)  :- **

Before DFS starts, the code checks whether the puzzle is solvable.

Inversion = when a higher-numbered tile precedes a lower-numbered tile (ignoring 0).

For a 3×3 puzzle →

Even inversions ⇒ Solvable ✅

Odd inversions ⇒ Unsolvable ❌

**Time Complexity:**

O(b^d), where

b = branching factor (average number of possible moves ≈ 2–3)

d = maximum depth of search

DFS can explore many states; hence complexity grows exponentially in the worst case.

**Space Complexity:**

O(b·d) → because it stores only the current path in the stack (less memory than BFS).


**Output:**
<img width="659" height="334" alt="image" src="https://github.com/user-attachments/assets/2c8fd960-e912-4338-83ea-dca2c86c90e1" />



















   





