
//#include <bits/stdc++.h>
#include <fstream>
#include <vector>
#include <set>
#include <queue>
#include <map>
#include <unordered_set>
#include <unordered_map>
#define ll long long
#define f first
#define s second
#define all(x) (x).begin(), (x).end()
#define make_unique(x) sort(all((x))); (x).resize(unique(all((x))) - (x).begin())
using namespace std;

vector <vector <int> > rev;
vector <int> used;
vector <vector <pair <int, int> > > vv;

void dfs(int v) {
    used[v] = 1;
    for (int i = 0; i < rev[v].size(); i++) {
        int to = rev[v][i];
        if (used[to])
            continue;
        dfs(to);
    }
}

void dfs_forward(int v) {
    used[v] = 1;
    for (int i = 0; i < vv[v].size(); i++) {
        int to = vv[v][i].f;
        if (used[to])
            continue;
        dfs_forward(to);
    }
}

int main()
{
    ifstream cin("fastminimization.in");
    ofstream cout("fastminimization.out");
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, m, k, x, f, t;
    char c;
    cin >> n >> m >> k;

    vector <int> classes(n + 1);
    queue <pair <unordered_set<int>, int> > q;
    vector <vector <vector <int> > > inv(n + 1, vector <vector <int> > (26));
    vector <unordered_set<int> > P(2);
    map <int, vector <int> > involved;

    vector <int> term(n + 1);
    vector <vector <int> > just_to_check(n + 1, vector <int> (26));
    rev.resize(n + 1);
    used.resize(n + 1);
    vv.resize(n + 1);
    for (int i = 0; i < k; i++)
        cin >> x,
                term[x] = 1;
    for (int i = 0; i < m; i++) {
        cin >> f >> t >> c;
        vv[f].push_back({t, c});
        rev[t].push_back(f);
        just_to_check[f][c - 'a'] = t;
        inv[t][c - 'a'].push_back(f);
    }
    for (int i = 1; i <= n; i++)
        if (term[i] && !used[i])
            dfs(i);
    if (!used[1]) {
        return cout << 0 << " " << 0 << " " << 0 << '\n' << '\n', 0;
    }
    for (int i = 0; i <= n; i++)
        for (int j = 0; j < 26; j++)
            if (!just_to_check[i][j])
                inv[0][j].push_back(i);
    for (int i = 0; i <= n; i++) {
        if (term[i])
            P[1].insert(i),
                    classes[i] = 1;
        else
            P[0].insert(i),
                    classes[i] = 0;
    }
    for (int i = 0; i < 26; i++) {
        q.push({P[1], i});
        q.push({P[0], i});
    }
    int id = 2;
    while (q.size() > 0) {
        auto p = q.front();
        q.pop();
        auto C = p.f;
        auto a = p.s;
        involved.clear();
        for (int q : C)
            for (int r : inv[q][a]) {
                //cout << r << " " << classes.size() << endl;
                int i = classes[r];
                involved[i].push_back(r);
            }
        // cout << "!" << endl;
        for (auto it = involved.begin(); it != involved.end(); it++) {
            int i = it->f;
            if (involved[i].size() < P[i].size()) {
                unordered_set<int> kek;
                P.push_back(kek);
                int j = P.size() - 1;
                for (int r : involved[i]) {
                    P[i].erase(r);
                    P[j].insert(r);
                }
                if (P[j].size() > P[i].size())
                    swap(P[i], P[j]);
                for (int r : P[j])
                    //cout << r << " " << classes.size() << endl,
                    classes[r] = j;
                //cout << P[j].size() << endl;
                for (int i = 0; i < 26; i++)
                    q.push({P[j], i});
            }
        }
        //cout << endl;
    }
    int pomoika = classes[0];
    vector <int> term_min(P.size() + 2);
    int cnt_term = 0, cnt_edges = 0, cnt_vertex = P.size();
    vector <int> mapa, rev_mapa;
    int start, mn = 0;
    used.assign(n + 1, 0);
    dfs_forward(1);
    for (int i = 1; i <= n; i++)
        if (!used[i]) {
            P[classes[0]].insert(i);
            P[classes[i]].erase(i);
            classes[i] = classes[0];
        }
    for (int i = 0; i < P.size(); i++) {
        if (P[i].size() == 0 || classes[*P[i].begin()] == pomoika)


        cnt_vertex--;
        else
        mapa.push_back(i);
        if (i == classes[1])
            start = i;
    }

    rev_mapa.resize(P.size() + 10);
    rev_mapa[start] = 1;
    for (int i = 0; i < mapa.size(); i++) {
        if (mapa[i] == start) {
            mn = -1;
            continue;
        }
        rev_mapa[mapa[i]] = i + 2 + mn;
    }
    for (int i = 0; i < P.size(); i++) {
        for (int j : P[i])
            if (term[j] && used[j]) {
                term_min[rev_mapa[i]] = 1,
                        cnt_term++;
                break;
            }
    }
    /*for (int i = 0; i < P.size(); i++) {
        cout << i << " " << P[i].size() << '\n';
        for (int j : P[i])
            cout << j << " ";
        cout << endl;
    }*/
    unordered_map<int, bool> ump[n + 2][26];
    vector <vector <pair <int, char> > > tree(P.size() + 2);
    for (int i = 1; i <= n; i++) {
        if (classes[i] == pomoika)
            continue;
        for (int j = 0; j < vv[i].size(); j++) {
            int real_i = rev_mapa[classes[i]], real_j = rev_mapa[classes[vv[i][j].f]];
            //cout << i << " " << classes[i] << " " << real_i << " " << vv[i][j].f << " " << classes[vv[i][j].f] << " " << real_j << '\n';
            if (classes[vv[i][j].f] == pomoika)
                continue;
            if (ump[real_i][vv[i][j].s - 'a'][real_j])
                continue;
            //cout << "!" << real_i << " " << real_j << endl;
            tree[real_i].push_back({real_j, vv[i][j].s});
            cnt_edges++;
            ump[real_i][vv[i][j].s - 'a'][real_j] = 1;
        }
    }
    cout << cnt_vertex << " " << cnt_edges << " " << cnt_term << '\n';
    for (int i = 1; i < P.size() + 1; i++)
        if (term_min[i])
            cout << i << " ";
    cout << '\n';
    for (int i = 1; i <= P.size(); i++)
        for (int j = 0; j < tree[i].size(); j++)
            cout << i << " " << tree[i][j].f << " " << tree[i][j].s << '\n';
}
