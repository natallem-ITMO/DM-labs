#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <fstream>
#include <queue>

#include <set>
#include <map>
//#include "../../../Helper/show_collections.hpp"


using namespace std;


int m, n;

bool containCycle(vector<unordered_multiset<int>> &edges, int i, std::vector<bool> &visited, int i1 = -1) {
    visited[i] = true;
    for (auto next : edges[i]) {
        if (next == i1) continue;
        if (visited[next]) return true;
        if (containCycle(edges, next, visited, i)) return true;
    }
    return false;
}

bool isTree(vector<unordered_multiset<int>> &edges_in_J) {
    vector<bool> visited(edges_in_J.size() + 1, false);
    for (int i = 1; i < edges_in_J.size(); i++) {
        if (!visited[i] && containCycle(edges_in_J, i, visited)) {
            return false;
        }
    }
    return true;
}

bool isColorful(vector<int> &colors, int colorToAdd, int colorToErase) {
    if (colorToAdd == colorToErase) return true;
    return colors[colorToAdd] == 0;
}

void create_X1_X2(unordered_set<int> &X1, unordered_set<int> &X2, vector<int> &a, vector<int> &b, vector<int> &c, vector
        <unordered_multiset<int>> &edges_in_J, vector<int> colors, unordered_set<int> &X_without_J) {
    for (auto edge_in_X_J: X_without_J) {
        int start = a[edge_in_X_J];
        int end = b[edge_in_X_J];
        int color = c[edge_in_X_J];
        edges_in_J[start].insert(end);
        edges_in_J[end].insert(start);
        if (isTree(edges_in_J)) {
            X1.insert(edge_in_X_J);
        }
        if (colors[color] == 0) {
            X2.insert(edge_in_X_J);
        }
        edges_in_J[start].erase(edges_in_J[start].find(end));
        edges_in_J[end].erase(edges_in_J[end].find(start));
    }
}

/*

unordered_map<int, unordered_set<int>>
create_D(vector<int> &a, vector<int> &b, vector<int> &c, vector<unordered_multiset<int>> &edges_in_J,
         vector<int> &colors,
         unordered_set<int> &J, unordered_set<int> &X_without_J) {
    unordered_map<int, unordered_set<int>> result;
    for (auto edge_in_X_J: X_without_J) {
        int start_erase = a[edge_in_X_J];
        int end_erase = b[edge_in_X_J];
        int colorToErase = c[edge_in_X_J];
        edges_in_J[start_erase].insert(end_erase);
        edges_in_J[end_erase].insert(start_erase);
        for (auto edge_in_J: J) {
            int start, end, colorToAdd;
            start = a[edge_in_J];
            end = b[edge_in_J];
            colorToAdd = c[edge_in_J];
            edges_in_J[start].erase(edges_in_J[start].find(end));
            edges_in_J[end].erase(edges_in_J[end].find(start));
            if (isTree(edges_in_J)) {
                result[edge_in_J].insert(edge_in_X_J);
            }
            if (isColorful(colors, colorToAdd, colorToErase)) {
                result[edge_in_X_J].insert(edge_in_J);
            }
            edges_in_J[start].insert(end);
            edges_in_J[end].insert(start);
        }
        edges_in_J[start_erase].erase(edges_in_J[start_erase].find(end_erase));
        edges_in_J[end_erase].erase(edges_in_J[end_erase].find(start_erase));
    }
    return result;
}

*/
vector<int>
find_min_path(unordered_set<int> &X1, unordered_set<int> &X2, vector<bool> &isInJ, vector<int> &a, vector<int> &b,
              vector<int> &c, vector<unordered_multiset<int>> &edges_in_J, vector<int> &colors) {
    vector<bool> inBFS(m + 1, false);
    vector<int> parent(m + 1, -1);
    queue<int> Q;
    for (auto t : X1) {
        Q.push(t);
        parent[t] = -1;
        inBFS[t] = true;
        parent[t] = -1;
        if (X2.count(t)) {
            return {t};
        }
    }

    while (!Q.empty()) {
        int cur = Q.front();
        Q.pop();
        for (int i = 1; i <= m; i++) {
            if (!inBFS[i]) {
                bool goahead = false;
                //cur in J, i in X\J
                //need to connect by I1 => tree then replace
                if (isInJ[cur] && !isInJ[i]) {
                    int start_erase = a[i];
                    int end_erase = b[i];
                    edges_in_J[start_erase].insert(end_erase);
                    edges_in_J[end_erase].insert(start_erase);
                    int edge_in_J = cur;
                    int start, end;
                    start = a[edge_in_J];
                    end = b[edge_in_J];
                    edges_in_J[start].erase(edges_in_J[start].find(end));
                    edges_in_J[end].erase(edges_in_J[end].find(start));
                    if (isTree(edges_in_J)) {
                        goahead = true;
                    }
                    edges_in_J[start].insert(end);
                    edges_in_J[end].insert(start);
                    edges_in_J[start_erase].erase(edges_in_J[start_erase].find(end_erase));
                    edges_in_J[end_erase].erase(edges_in_J[end_erase].find(start_erase));

                } else
                    //i in J, cur in X\J
                    //need to connect by I2 => colorful then add color X\J end erase color J
                if (!isInJ[cur] && isInJ[i]) {
                    int colorToAdd = c[cur];
                    int colorToErase = c[i];
                    if (isColorful(colors, colorToAdd, colorToErase)) {
                        goahead = true;
                    }
                }
                if (goahead) {
                    parent[i] = cur;
                    if (X2.count(i)) {
                        cur = i;
                        vector<int> result;
                        while (cur != -1) {
                            result.push_back(cur);
                            cur = parent[cur];
                        }
                        return result;
                    } else {
                        Q.push(i);
                        inBFS[i] = true;//todo
                    }

                }

            }
        }

    }
    return {};
}

void fall() {
    vector<int> a;
    cout << a[10];
}

int main() {

//#ifdef MY_DEBUG
//    std::ifstream cin("a.in");
//    std::ofstream cout("a.out");
//#else
//    std::ifstream cin("rainbow.in");
//    std::ofstream cout("rainbow.out");
//#endif
//    ios_base::sync_with_stdio(false);
//    cin.tie(nullptr);
//    cout.tie(nullptr);
//    vector<int> vv;
//    cout << vv[45];
//    int n, m;
    freopen("rainbow.in", "r", stdin);

    scanf("%d", &n);
    scanf("%d", &m);
//    cin >> n >> m;
    vector<int> a(m + 1), b(m + 1), c(m + 1);

    unordered_set<int> J;
    unordered_set<int> X_without_J;
    for (int i = 0; i < m; i++) {
//        int a, b, c;
        scanf("%d", &a[i + 1]);
        scanf("%d", &b[i + 1]);
        scanf("%d", &c[i + 1]);
//        cin >> a >> b >> c;

//        edges[i + 1] = {a, b, c};
        X_without_J.insert(i + 1);
    }

    bool isMaximal = false;
    vector<unordered_multiset<int>> edges_in_J(n + 1);
    vector<int> colors(101, 0);
    vector<bool> inJ(m + 1, false);
    while (!isMaximal) {
        unordered_set<int> X1, X2;
        create_X1_X2(X1, X2, a, b, c, edges_in_J, colors, X_without_J);
        auto path = find_min_path(X1, X2, inJ, a, b, c, edges_in_J, colors);
        if (!path.empty()) {
            for (int i = 0; i < path.size(); i++) {
                int start = a[path[i]];
                int end = b[path[i]];
                int color = c[path[i]];
                if (i % 2 == 0) {
                    J.insert(path[i]);
                    inJ[path[i]] = true;
                    X_without_J.erase(path[i]);
                    edges_in_J[start].insert(end);
                    edges_in_J[end].insert(start);
                    colors[color] = true;
                } else {
                    inJ[path[i]] = false;
                    J.erase(path[i]);
                    X_without_J.insert(path[i]);
                    edges_in_J[start].erase(edges_in_J[start].find(end));
                    edges_in_J[end].erase(edges_in_J[end].find(start));
                    colors[color] = false;
                }
            }
        } else {
            isMaximal = true;
        }
    }
    freopen("rainbow.out", "w", stdout);

//    cout << J.size() << "\n";
//    for (auto t : J) {
//        cout << t << " ";
//    }

    int k = J.size();
    printf("%d\n", k);
    for (int i :J) {
        printf("%d ", (i));
    }
    fclose(stdout);
    return 0;
}
//todo getRidOf J X_J map set...