#include<iostream>
#include<vector>
#include<queue>
#include<set>
#include<algorithm>
using namespace std;
#define N 3

struct state {
    vector<vector<int>> mat;
    int row;
    int col;
    int state_no;
    state* parent;
    state(vector<vector<int>> p, int x, int y, int num, state* par = nullptr)
        : mat(p), row(x), col(y), state_no(num), parent(par) {}
};

int isValid(int x, int y) { return (x >= 0 && x < N && y >= 0 && y < N); }

int inversions(const vector<vector<int>>& a){
    vector<int> v; v.reserve(N*N);
    for(int i=0;i<N;i++) for(int j=0;j<N;j++) if(a[i][j]!=0) v.push_back(a[i][j]);
    int inv=0;
    for(size_t i=0;i<v.size();++i) for(size_t j=i+1;j<v.size();++j) if(v[i]>v[j]) ++inv;
    return inv;
}
int isSolvable(const vector<vector<int>>& a){ return (inversions(a)%2==0) ? 1 : 0; }

int isGoalMatrix(vector<vector<int>>& mat) {
    static vector<vector<int>> goal = {{1,2,3},{4,5,6},{7,8,0}};
    return mat == goal;
}

void printpuzzle(vector<vector<int>>& matrix) {
    for (auto& r : matrix) { for (auto& i : r) cout << i << " "; cout << "\n"; }
    cout << "------\n";
}

int row_list[] = {0, 0, -1, 1};
int col_list[] = {-1, 1, 0, 0};

void BFS_puzzle(vector<vector<int>>& mat, int row, int col) {
    queue<state*> q;
    set<vector<vector<int>>> closed;
    state* first = new state(mat, row, col, 0, nullptr);
    q.push(first);
    closed.insert(mat);
    while (!q.empty()) {
        state* present = q.front(); q.pop();
        if (isGoalMatrix(present->mat)) {
            cout << "Goal matrix achieved at step " << present->state_no << "\n";
            printpuzzle(present->mat);
            return;
        }
        for (int i = 0; i < 4; i++) {
            int new_row = present->row + row_list[i];
            int new_col = present->col + col_list[i];
            if (isValid(new_row, new_col)) {
                vector<vector<int>> temp = present->mat;
                swap(temp[present->row][present->col], temp[new_row][new_col]);
                if (closed.find(temp) == closed.end()) {
                    closed.insert(temp);
                    state* child = new state(temp, new_row, new_col, present->state_no + 1, present);
                    q.push(child);
                }
            }
        }
    }
    cout << "No such goal found !!\n";
}

int main() {
    vector<vector<int>> puzzle = {{1,2,3},{4,5,6},{8,7,0}};
    cout << "Starting Puzzle:\n";
    printpuzzle(puzzle);

    if (!isSolvable(puzzle)) {
        cout << "Unsolvable start (inversions = " << inversions(puzzle) << ").\n";
        return 0;
    }

    int row=-1, col=-1;
    for(int i=0;i<N;i++) for(int j=0;j<N;j++) if(puzzle[i][j]==0){ row=i; col=j; }
    BFS_puzzle(puzzle, row, col);
    return 0;
}
