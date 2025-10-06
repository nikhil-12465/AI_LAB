#include <iostream>
#include <vector>
using namespace std;

#define N 3

struct tic_tac {
    vector<vector<char>> board;
    int score;
    int level;
    vector<tic_tac*> children;

    tic_tac(vector<vector<char>> b, int s=0, int l=0) {
        board = b;
        score = s;
        level = l;
    }
};

bool isWin(const vector<vector<char>>& board, char player) {
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player) return true;
    }
    for (int j = 0; j < 3; j++) {
        if (board[0][j] == player && board[1][j] == player && board[2][j] == player) return true;
    }
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player) return true;
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player) return true;
    return false;
}

bool isDraw(const vector<vector<char>>& board, int level) {
    return (!isWin(board, 'X') && !isWin(board, 'O') && level == 9);
}

void display(const vector<vector<char>>& grid) {
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size(); j++) {
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
}

void TreeCreation(tic_tac* node, char player) {
    if (isWin(node->board, 'X')) { node->score = 1; return; }
    if (isWin(node->board, 'O')) { node->score = -1; return; }
    if (isDraw(node->board, node->level)) { node->score = 0; return; }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (node->board[i][j] == ' ') {
                vector<vector<char>> newBoard = node->board;
                newBoard[i][j] = player;

                tic_tac* child = new tic_tac(newBoard, 0, node->level + 1);
                node->children.push_back(child);

                TreeCreation(child, (player == 'X' ? 'O' : 'X'));
            }
        }
    }
}

int main() {
    vector<vector<char>> start(3, vector<char>(3, ' '));
    tic_tac* root = new tic_tac(start, 0, 0);

    TreeCreation(root, 'X');

    cout << "Game tree built successfully!" << endl;
    return 0;
}