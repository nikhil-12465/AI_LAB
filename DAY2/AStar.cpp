#include <iostream>
#include <climits>
#include <cmath>
using namespace std;

inline int H(int i, int j, int k, int l) {
    return abs(k - i) + abs(l - j);
}

pair<int, int> calculatecost(int arr[5][5], int i, int j, int k, int l) {
    auto try_relax = [&](int ni, int nj){
        if (ni < 0 || ni >= 5 || nj < 0 || nj >= 5) return;
        if (arr[ni][nj] == INT_MAX) return;         // obstacle
        int cand = (arr[i][j] - H(i,j,k,l)) + 1 + H(ni,nj,k,l); // g+1 + h = new f
        if (arr[ni][nj] == -1 || cand < arr[ni][nj]) arr[ni][nj] = cand;
    };


    try_relax(i+1, j);
    try_relax(i-1, j);
    try_relax(i, j+1);
    try_relax(i, j-1);

    
    int best = INT_MAX;  // Pick best neighbor
    pair<int,int> next = { -1, -1 };
    auto consider = [&](int ni, int nj){
        if (ni < 0 || ni >= 5 || nj < 0 || nj >= 5) return;
        if (arr[ni][nj] == INT_MAX || arr[ni][nj] == -1) return;
        if (arr[ni][nj] < best) { best = arr[ni][nj]; next = {ni, nj}; }
    };
    consider(i+1, j);
    consider(i-1, j);
    consider(i, j+1);
    consider(i, j-1);

    return next; 
}

int main() {
    int arr[5][5];

  
    for (int r=0; r<5; ++r) for (int c=0; c<5; ++c) arr[r][c] = -1;
    arr[2][0] = INT_MAX;
    arr[3][1] = INT_MAX;
    arr[2][2] = INT_MAX;
    arr[0][3] = INT_MAX;
    arr[1][4] = INT_MAX;

    int i, j, k, l;
    cout << "The coordinates of the source: ";
    cin >> i >> j;
    cout << "The coordinates of destination: ";
    cin >> k >> l;

    if (arr[i][j] == INT_MAX || arr[k][l] == INT_MAX) {
        cout << "Source or destination is blocked.\n";
        return 0;
    }

    
    arr[i][j] = H(i, j, k, l);

    cout << "Path: (" << i << "," << j << ") ";
    while (i != k || j != l) {
        pair<int, int> next = calculatecost(arr, i, j, k, l);
        if (next.first == -1) {
            cout << "\nNo path.\n";
            return 0;
        }
        i = next.first;
        j = next.second;
        cout << "-> (" << i << "," << j << ") ";
    }

    cout << "\nDestination reached!\n";
    return 0;
}
