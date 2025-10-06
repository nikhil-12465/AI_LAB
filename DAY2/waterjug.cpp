#include <bits/stdc++.h>
using namespace std;

struct State {
    int x, y;
};

bool cmp(const State &a, const State &b) {
    if (a.x == b.x) return a.y < b.y;
    return a.x < b.x;
}

void printPath(map<State, State, bool(*)(const State&, const State&)> &parent, State goal) {
    if (parent.find(goal) == parent.end()) {
        cout << "(" << goal.x << ", " << goal.y << ")" << endl;
        return;
    }
    printPath(parent, parent[goal]);
    cout << "(" << goal.x << ", " << goal.y << ")" << endl;
}

State makeState(int x, int y) {
    State s;
    s.x = x;
    s.y = y;
    return s;
}

void waterJugBFS(int jug1, int jug2, int target) {
    queue<State> q;
    set<pair<int, int>> visited;
    map<State, State, bool(*)(const State&, const State&)> parent(cmp);

    q.push(makeState(0, 0));
    visited.insert({0, 0});

    while (!q.empty()) {
        State curr = q.front(); q.pop();
        int x = curr.x, y = curr.y;

        if (x == target || y == target) {
            printPath(parent, curr);
            return;
        }

        vector<State> nextStates;
        nextStates.push_back(makeState(jug1, y));
        nextStates.push_back(makeState(x, jug2));
        nextStates.push_back(makeState(0, y));
        nextStates.push_back(makeState(x, 0));
        int pour = min(x, jug2 - y);
        nextStates.push_back(makeState(x - pour, y + pour));
        pour = min(y, jug1 - x);
        nextStates.push_back(makeState(x + pour, y - pour));

        for (auto ns : nextStates) {
            if (visited.find({ns.x, ns.y}) == visited.end()) {
                visited.insert({ns.x, ns.y});
                parent[ns] = curr;
                q.push(ns);
            }
        }
    }
    cout << "No solution possible." << endl;
}

int main() {
    int jug1 = 4, jug2 = 3, target = 2;
    waterJugBFS(jug1, jug2, target);
    return 0;
}
