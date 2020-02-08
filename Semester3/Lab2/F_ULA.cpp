#include <stdio.h>
#include <vector>
#include <unordered_set>
#include <queue>
#include <algorithm>
#include <list>

using namespace std;

bool dfs(int j, vector<bool> &used, int n, int parent, vector<vector<int>> &graphInJ) {
    if (used[j]) return false;
    used[j] = true;
    bool first = true;
    bool acyclic = true;
    for (int i : graphInJ[j]) {
        if (i != parent) {
            acyclic &= dfs(i, used, n, j, graphInJ);
        } else if (i == parent && first) {
            first = false;
        } else {
            acyclic &= dfs(i, used, n, j, graphInJ);
        }
    }
    return acyclic;
}

void bfs(vector<vector<int>> &d, list<int> &x1, unordered_set<int> &x2, vector<int> &path,
         vector<vector<int>> &back_d) {
    int minPathSize = 2000000;
    queue<int> arrayDeque;
    for (int start : x1) {
        vector<int> length(d.size(), 2000000);
        vector<bool> used(d.size());
        arrayDeque.push(start);
        length[start] = 0;
        used[start] = true;
        while (!arrayDeque.empty()) {
            int v = arrayDeque.front();
            arrayDeque.pop();
            for (int to : d[v]) {
                if (used[to])continue;
                used[to] = true;
                if (length[v] + 1 < length[to]) {
                    arrayDeque.push(to);
                    length[to] = length[v] + 1;
                }
            }
        }
        int newMinPathSize = 2000000;
        for (int i = 0; i < length.size(); i++) {
            if (x2.find(i) != x2.end()) {
                newMinPathSize = min(newMinPathSize, length[i]);
            }
        }
        if (minPathSize > newMinPathSize) {
            minPathSize = newMinPathSize;
            path.clear();
            int end = -1;
            for (int i = 0; i < length.size(); i++) {
                if (x2.find(i) != x2.end() && length[i] == minPathSize) {
                    end = i;
                    break;
                }
            }
            path.push_back(end);
            while (newMinPathSize > 0) {
                for (int from :                         back_d[end]) {
                    if (length[from] == newMinPathSize - 1) {
                        path.push_back(from);
                        end = from;
                        newMinPathSize--;
                        break;
                    }
                }
            }
        }
    }
}

int main() {
    freopen("rainbow.in", "r", stdin);
    int n, m;
    scanf("%d", &n);
    scanf("%d", &m);
    vector<int> a(m);
    vector<int> b(m);
    vector<int> c(m);
    vector<vector<int>> verticesByColor;
    for (int i = 0; i <= 100; ++i) {
        verticesByColor.emplace_back(vector<int>());
    }
    for (int i = 0; i < m; i++) {
        int ai, bi, ci;
        scanf("%d", &ai);
        scanf("%d", &bi);
        scanf("%d", &ci);

        verticesByColor[ci].push_back(i);
        a[i] = ai - 1;
        b[i] = bi - 1;
        c[i] = ci;
    }
    fclose(stdin);
    vector<bool> inJ(m, false);
    unordered_set<int> J;
    unordered_set<int> S_without_J;
    for (int l = 0; l < m; ++l) {
        S_without_J.insert(l);
    }
    bool flag = true;
    while (flag) {
        vector<bool> colorInJ(101,
                              false);
        vector<vector<int>> d;
        vector<vector<int>> back_d;
        list<int> x1;
        unordered_set<int> x2;
        vector<vector<int>> graphInJ;
        graphInJ.reserve(n);
        for (int i = 0; i < n; i++) {
            graphInJ.emplace_back(vector<int>());
        }
        for (int i = 0; i < m; i++) {
            d.emplace_back(vector<int>());
            back_d.emplace_back(vector<int>());
        }
        for (int i:J) {
            colorInJ[c[i]] = true;
            graphInJ[a[i]].push_back(b[i]);
            graphInJ[b[i]].push_back(a[i]);
        }
        vector<int> del;
        for (int i:S_without_J) {
            if (!colorInJ[c[i]]) {
                graphInJ[a[i]].push_back(b[i]);
                graphInJ[b[i]].push_back(a[i]);
                vector<bool> used(n, false);
                bool acyclic = true;
                for (int j = 0; j < n; j++) {
                    if (!used[j]) {
                        acyclic &= dfs(j, used, n, -1, graphInJ);
                        if (!acyclic)                            break;
                    }
                }
                if (acyclic) {
                    inJ[i] = true;
                    J.insert(i);
                    S_without_J.erase(i);
                    del.push_back(i);
                    colorInJ[c[i]] = true;
                } else {
                    graphInJ[a[i]].erase(--graphInJ[a[i]].end());
                    graphInJ[b[i]].erase(--graphInJ[b[i]].end());
                }
            }
        }
        for (int dell:del) {
            S_without_J.erase(dell);
        }
        for (int i:S_without_J) {
            if (!colorInJ[c[i]]) {
                x1.push_back(i);
            } else {
                graphInJ[a[i]].push_back(b[i]);
                graphInJ[b[i]].push_back(a[i]);
                vector<bool> used(n, false);
                bool acyclic = true;
                for (int j = 0; j < n; j++) {
                    if (!used[j]) {
                        acyclic &= dfs(j, used, n, -1, graphInJ);
                    }
                    if (!acyclic) break;
                }
                if (acyclic) x2.insert(i);
                graphInJ[a[i]].erase(--graphInJ[a[i]].end());
                graphInJ[b[i]].erase(--graphInJ[b[i]].end());
            }
        }
        if (x1.empty() || x2.empty()) {
            flag = false;
        } else {
            for (int i:J) {
                for (int to : verticesByColor[c[i]]) {
                    if (!inJ[to]) {
                        d[i].push_back(to);
                        back_d[to].push_back(i);
                    }
                }
                for (int x : x1) {
                    d[i].push_back(x);
                    back_d[x].push_back(i);
                }
            }
            for (int x : x2) {
                for (int i = 0; i < m; i++) {
                    if (inJ[i]) {
                        d[x].push_back(i);
                        back_d[i].push_back(x);
                    }
                }
            }

            for (int i :J) {
                inJ[i] = false;
                for (auto j =
                        graphInJ[a[i]].begin(); j != graphInJ[a[i]].end(); j++) {
                    if (*j == b[i]) {
                        graphInJ[a[i]].erase(j);
                        break;
                    }
                }
                for (auto j = graphInJ[b[i]].begin(); j != graphInJ[b[i]].end(); j++) {
                    if (*j == a[i]) {
                        graphInJ[b[i]].erase(j);
                        break;
                    }
                }
                del.clear();
                for (int s:S_without_J) {
                    if (x2.find(s) == x2.end()) {
                        inJ[s] = true;
                        del.push_back(s);
                        graphInJ[a[s]].push_back(b[s]);
                        graphInJ[b[s]].push_back(a[s]);
                        vector<bool> used(n, false);
                        bool acyclic = true;
                        for (int j = 0; j < n; j++) {
                            if (!used[j]) {
                                acyclic &= dfs(j, used, n, -1, graphInJ);
                            }
                            if (!acyclic) break;
                        }
                        if (acyclic) {
                            d[s].push_back(i);
                            back_d[i].push_back(s);
                        }
                        inJ[s] = false;
                        graphInJ[a[s]].erase(--graphInJ[a[s]].end());
                        graphInJ[b[s]].erase(--graphInJ[b[s]].end());
                    }
                }
                inJ[i] = true;
                graphInJ[a[i]].push_back(b[i]);
                graphInJ[b[i]].push_back(a[i]);
            }
            vector<int> path;
            bfs(d, x1, x2, path,
                back_d);
            if (path.empty()) {
                flag = false;
            } else {
                for (int i : path) {
                    inJ[i] = !inJ[i];
                    if (inJ[i]) {
                        J.insert(i);
                        S_without_J.erase(i);
                    } else {
                        S_without_J.insert(i);
                        J.erase(i);
                    }
                }
            }
        }
    }
    freopen("rainbow.out", "w", stdout);
    int k = J.size();
    printf("%d\n", k);
    for (int i :J) {
        printf("%d ", (i + 1));
    }
    fclose(stdout);
    return 0;
}
