#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <limits>
using namespace std;

#define N 3

struct state {
    vector<vector<int>> mat;
    int row, col;
    int state_num;
    state* parent;
    state(vector<vector<int>> m, int r, int c, int st, state* p=nullptr)
        : mat(m), row(r), col(c), state_num(st), parent(p) {}
};

int row_list[] = {-1, 1, 0, 0};
int col_list[] = { 0, 0,-1, 1};

bool isValid(int x, int y){ return (x>=0 && x<N && y>=0 && y<N); }

bool isGoalMatrix(vector<vector<int>>& mat){
    static vector<vector<int>> goal = {{1,2,3},{4,5,6},{7,8,0}};
    return mat == goal;
}

void printBoard(const vector<vector<int>>& mat){
    for (auto& r : mat){ for (auto v : r) cout << v << " "; cout << "\n"; }
    cout << "------\n";
}

/* ---------- Solvability (inversions) ---------- */
int inversions(const vector<vector<int>>& a){
    vector<int> v; v.reserve(N*N);
    for(int i=0;i<N;i++) for(int j=0;j<N;j++) if(a[i][j]!=0) v.push_back(a[i][j]);
    int inv=0;
    for(size_t i=0;i<v.size();++i) for(size_t j=i+1;j<v.size();++j) if(v[i]>v[j]) ++inv;
    return inv;
}
int isSolvable(const vector<vector<int>>& a){ return (inversions(a)%2==0) ? 1 : 0; }

/* ---------- Heuristic: Manhattan distance ---------- */
int h_manhattan(const vector<vector<int>>& mat){
    int h=0;
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            int val = mat[i][j];
            if(val==0) continue;
            int gr = (val-1)/N, gc = (val-1)%N;
            h += abs(i-gr) + abs(j-gc);
        }
    }
    return h;
}

/* ---------- Neighbor generation ---------- */
void gen_neighbors(const state* s, vector<state*>& out){
    out.clear();
    for(int k=0;k<4;k++){
        int nr = s->row + row_list[k];
        int nc = s->col + col_list[k];
        if(!isValid(nr,nc)) continue;
        vector<vector<int>> t = s->mat;
        swap(t[s->row][s->col], t[nr][nc]);
        out.push_back(new state(t, nr, nc, s->state_num+1, (state*)s));
    }
}

/* ---------- Steepest-ascent Hill Climbing ---------- */
void Hill_Climbing(vector<vector<int>>& start, int row, int col){
    state* cur = new state(start, row, col, 0, nullptr);
    int cur_h = h_manhattan(cur->mat);

    cout << "Start (h=" << cur_h << ")\n";
    printBoard(cur->mat);

    if(isGoalMatrix(cur->mat)){
        cout << "Goal reached at step 0\n";
        return;
    }

    const int MAX_STEPS = 20000; 
    for(int step=0; step<MAX_STEPS; ++step){
        vector<state*> nbrs;
        gen_neighbors(cur, nbrs);

        int best_h = numeric_limits<int>::max();
        state* best = nullptr;

        for(auto s : nbrs){
            int h = h_manhattan(s->mat);
            if(h < best_h){ best_h = h; best = s; }
        }

        if(best == nullptr){
            cout << "No neighbors generated. Stopping.\n";
            return;
        }

        if(best_h < cur_h){
            cur = best;
            cur_h = best_h;
            cout << "Step " << cur->state_num << " (h=" << cur_h << ")\n";
            printBoard(cur->mat);
            if(isGoalMatrix(cur->mat)){
                cout << "Goal reached at step " << cur->state_num << "\n";
                return;
            }
        } else {
            cout << "Stuck at local minimum/plateau (h=" << cur_h << "). No better neighbor.\n";
            cout << "Final state after " << cur->state_num << " steps:\n";
            printBoard(cur->mat);
            return;
        }
    }
    cout << "Step cap reached. Stopping.\n";
}

int main(){
  
    // vector<vector<int>> puzzle = {{1,2,3},{4,5,6},{7,0,8}}; // solvable, very easy
    // vector<vector<int>> puzzle = {{2,8,3},{1,6,4},{7,0,5}}; // solvable, harder (may plateau)
    vector<vector<int>> puzzle = {{1,2,3},{0,4,5},{6,7,8}}; // solvable but hill-climbing may plateau

    cout << "Starting Puzzle:\n";
    printBoard(puzzle);

    if(!isSolvable(puzzle)){
        cout << "Unsolvable start (inversions = " << inversions(puzzle) << ").\n";
        return 0;
    }

    int r=-1,c=-1;
    for(int i=0;i<N;i++) for(int j=0;j<N;j++) if(puzzle[i][j]==0){ r=i; c=j; }
    Hill_Climbing(puzzle, r, c);
    return 0;
}
