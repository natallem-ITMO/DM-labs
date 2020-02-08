/*
#include <fstream>
#include <vector>
#include <string>
#include <stdio.h>
#include <cmath>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <algorithm>

using namespace std;
//std::ifstream cin("a.in");
std::ifstream cin("minimization.in");
std::ofstream cout("minimization.out");
//std::ofstream cout("a.out");
int n, m, k;
unordered_set<int> terminal_states;
unordered_set<int> Q;
unordered_set<int> Q_T;
vector<int> class_by_vertex;
vector<unordered_set<int>> equivalence_classes;
queue<pair<int, unordered_set<int>>> que;
vector<bool> connect_terminal;
vector<bool> connect_start;
vector<bool> normal_vertex;

bool is_terminal(int v) {
    return (terminal_states.find(v) != terminal_states.end());
}

void reverse_edges(int vertex, vector<unordered_map<int, vector<int>>> &edges_in_vertex_by_symbol) {
    unordered_map<int, vector<int>>::iterator itr;
    for (itr = edges_in_vertex_by_symbol[vertex].begin(); itr != edges_in_vertex_by_symbol[vertex].end(); itr++) {
        for (int i = 0; i < itr->second.size(); i++) {
            itr->second[i] = 0;
        }
    }
}

void find_vertexes_connected_with_start(int vertex, vector<unordered_set<int>> &straight_edges_in_vertex) {
    // connect_start_used[vertex] = true;
    connect_start[vertex] = true;
    for (int son : straight_edges_in_vertex[vertex]) {
        if (!connect_start[son]) find_vertexes_connected_with_start(son, straight_edges_in_vertex);
    }
}

void find_vertexes_connected_with_terminal(int vertex, vector<unordered_set<int>> &reverse_edges_in_vertex) {
    // connect_terminal_used[vertex] = true;
    connect_terminal[vertex] = true;
    for (int son : reverse_edges_in_vertex[vertex]) {
        if (!connect_terminal[son]) find_vertexes_connected_with_terminal(son, reverse_edges_in_vertex);
    }
}

int main() {
    cin >> n >> m >> k;
    vector<int> input_start(m);
    vector<int> input_end(m);
    vector<char> input_char(m);
    class_by_vertex.push_back(-1);
    for (int i = 0; i < k; i++) {
        int fd;
        cin >> fd;
        terminal_states.insert(fd);
    }
    vector<unordered_map<int, vector<int>>> reverse_edges_in_vertex_by_symbol(n + 1);
    vector<unordered_set<int>> straight_edges_in_vertex(n + 1);
    vector<unordered_set<int>> reverse_edges_in_vertex(n + 1);
    for (int i = 0; i < m; i++) {
        cin >> input_start[i] >> input_end[i] >> input_char[i];
        reverse_edges_in_vertex_by_symbol[input_end[i]][input_char[i] - 'a'].push_back(input_start[i]);
        straight_edges_in_vertex[input_start[i]].insert(input_end[i]);
        reverse_edges_in_vertex[input_end[i]].insert(input_start[i]);
    }
    unordered_set<int>::iterator itr_set_int;
    for (int i = 0; i <= n; i++) {
        connect_terminal.push_back(false);
        connect_start.push_back(false);
        normal_vertex.push_back(false);
    }
    for (itr_set_int = terminal_states.begin(); itr_set_int != terminal_states.end(); itr_set_int++) {
        if (!connect_terminal[*itr_set_int]) {
            find_vertexes_connected_with_terminal(*itr_set_int, reverse_edges_in_vertex);
        }
    }
    find_vertexes_connected_with_start(1, straight_edges_in_vertex);

    for (int i = 1; i <= n; i++) {
        if (connect_start[i] && connect_terminal[i]) normal_vertex[i] = true;
        else {
            reverse_edges(i, reverse_edges_in_vertex_by_symbol);
            if (is_terminal(i)) terminal_states.erase(i);
        }
    }

    if (terminal_states.empty() || !normal_vertex[1]) {
        cout << "0 0 0\n";
    } else {
        for (int i = 1; i <= n; i++) {
            class_by_vertex.push_back(-1);
            if (is_terminal(i)) {
                Q_T.insert(i);
                class_by_vertex[i] = 0;
            } else if (normal_vertex[i]) {
                Q.insert(i);
                class_by_vertex[i] = 1;
            }
        }
        equivalence_classes.push_back(Q_T);
        for (int i = 0; i < 26; i++) {
            que.push({i, Q_T});
        }
        if (!Q.empty()) {
            equivalence_classes.push_back(Q);
            for (int i = 0; i < 26; i++) {
                que.push({i, Q});
            }
        }

        while (!que.empty()) {
            pair<int, unordered_set<int>> &current_pair = que.front();
            unordered_map<int, unordered_set<int>> involved;
            int cur_char = current_pair.first;
            for (int vertex : current_pair.second) {
                if (reverse_edges_in_vertex_by_symbol[vertex].find(cur_char) !=
                    reverse_edges_in_vertex_by_symbol[vertex].end())
                    for (int edge : reverse_edges_in_vertex_by_symbol[vertex][cur_char]) {
                        if (normal_vertex[edge]) {
                            int i = class_by_vertex[edge];
                            if (involved.find(i) == involved.end()) involved[i] = {edge};
                            else involved[i].insert(edge);
                        }
                    }
            }
            for (pair<int, unordered_set<int>> involved_pair : involved) {
                int cur_index_involved = involved_pair.first;
                if (involved_pair.second.size() < equivalence_classes[cur_index_involved].size()) {
                    unordered_set<int> new_class;
                    for (int x : involved_pair.second) {
                        new_class.insert(x);
                        equivalence_classes[cur_index_involved].erase(x);
                    }
                    equivalence_classes.push_back(new_class);
                    int j = equivalence_classes.size() - 1;
                    if (equivalence_classes[j].size() > equivalence_classes[cur_index_involved].size())
                        swap(equivalence_classes[j], equivalence_classes[cur_index_involved]);
                    for (int r : equivalence_classes[j]) {
                        class_by_vertex[r] = j;
                    }
                    for (int i = 0; i < 26; i++) {
                        que.push({i, equivalence_classes[j]});
                    }
                }
            }
            que.pop();
        }
        int start_num_min_aut = class_by_vertex[1];
        // int start_num_min_aut_change = equivalence_classes.size()-1;
        for (int i = 0; i < class_by_vertex.size(); i++) {
            int x = class_by_vertex[i];
            if (x == 0) class_by_vertex[i] = start_num_min_aut;
            else if (x == start_num_min_aut) class_by_vertex[i] = 0;
        }
        unordered_set<string> edges_output;
        unordered_set<int> terminal_output;
        for (int i = 0; i < m; i++) {
            char cur_ch = input_char[i];
            int cur_st_min = class_by_vertex[input_start[i]];
            int cur_end_min = class_by_vertex[input_end[i]];
            if (!(cur_st_min == -1 || cur_end_min == -1)) {
                edges_output.insert(to_string(cur_st_min + 1) + " " + to_string(cur_end_min + 1) + " " + cur_ch);
            }
        }
        cout << equivalence_classes.size() << " " << edges_output.size() << " " << terminal_states.size() << "\n";
        for (itr_set_int = terminal_states.begin(); itr_set_int != terminal_states.end(); itr_set_int++)
            cout << (class_by_vertex[*itr_set_int] + 1) << " ";
        cout << "\n";
        unordered_set<string>::iterator itr_str;
        for (itr_str = edges_output.begin(); itr_str != edges_output.end(); itr_str++) {
            cout << *itr_str << "\n";
        }
    }
    return 0;
}
*/
