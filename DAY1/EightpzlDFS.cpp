#include<iostream>
#include<vector>
#include<set>
#include<stack>
#include<algorithm>
using namespace std;
#define N 3

struct State {
    vector<vector<int>> mat;
    int row, col;
    int state_num;
    State* parent;

    State(vector<vector<int>> b, int i, int j, int d, State* p = nullptr) {
        mat = b;
        row = i;
        col = j;
        state_num = d;
        parent = p;
    }
};

bool isGoalState(vector<vector<int>>& mat) {
    vector<vector<int>> goal = {{1,2,3},{4,5,6},{7,8,0}};
    return mat == goal;
}

bool isValid(int x, int y) {
    return (x >= 0 && x < N && y >= 0 && y < N);
}

int row_list[] = {0, 0, -1, 1};
int col_list[] = {-1, 1, 0, 0};

void printMat(vector<vector<int>>& mat) {
    for(int i=0; i<N; i++) {
        for(int j=0; j<N; j++) {
            cout << mat[i][j] << " ";
        }
        cout << endl;
    }
    cout << "------" << endl;
}

// ---- Added: inversion + solvability check ----
int inversions(const vector<vector<int>>& a){
    vector<int> v;
    v.reserve(N*N);
    for(int i=0;i<N;i++)
        for(int j=0;j<N;j++)
            if(a[i][j]!=0) v.push_back(a[i][j]);
    int inv=0;
    for(size_t i=0;i<v.size();++i)
        for(size_t j=i+1;j<v.size();++j)
            if(v[i]>v[j]) ++inv;
    return inv;
}
bool isSolvable(const vector<vector<int>>& a){
    // For 3x3, solvable iff inversion count is even
    return inversions(a)%2==0;
}
// ----------------------------------------------

void DFS(vector<vector<int>>& mat, int row, int col) {
    stack<State*> st;
    set<vector<vector<int>>> visited;

    State* start = new State(mat, row, col, 0, nullptr);
    st.push(start);
    visited.insert(mat);

    while(!st.empty()) {
        State* current = st.top();
        st.pop();

        if(isGoalState(current->mat)) {
            cout << "Goal state_num reached at: " << current->state_num << endl;
            printMat(current->mat);
            return;
        }

        for(int i=0; i<4; i++) {
            int new_row = current->row + row_list[i];
            int new_col = current->col + col_list[i];

            if(isValid(new_row, new_col)) {
                vector<vector<int>> temp = current->mat;
                swap(temp[current->row][current->col], temp[new_row][new_col]);

                if(visited.find(temp) == visited.end()) {
                    visited.insert(temp);
                    State* child = new State(temp, new_row, new_col, current->state_num + 1, current);
                    st.push(child);
                }
            }
        }
    }

    cout << "No solution found !!" << endl;
}

int main() {
    // vector<vector<int>> starting_puzzle = {{1,3,2},{0,4,6},{7,5,8}}; // this one is UNSOLVABLE because only the even number of inversion are solvable 
    vector<vector<int>> starting_puzzle = {{1,2,3},{4,5,6},{7,0,8}}; // try this solvable one

    cout << "Starting state_num:" << endl;
    printMat(starting_puzzle);

    if(!isSolvable(starting_puzzle)){
        cout << "Unsolvable start (inversions = " << inversions(starting_puzzle) << ")." << endl;
        return 0;
    }

    int row=-1, col=-1;
    for(int i=0;i<N;i++)
        for(int j=0;j<N;j++)
            if(starting_puzzle[i][j]==0){ row=i; col=j; }

    DFS(starting_puzzle, row, col);
    return 0;
}
