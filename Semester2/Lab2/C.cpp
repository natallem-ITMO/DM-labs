#include <fstream>
#include <vector>
#include <string>
#include <stdio.h>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <algorithm>

using namespace std;
//std::ifstream cin("a.in");
std::ifstream cin("problem3.in");
std::ofstream cout("problem3.out");
//std::ofstream cout("a.out");

int mod = 1000000000 + 7;

struct Node {
    int num;
    unordered_map<int, int> out;//pair<node_num, amount_edges>
    unordered_map<int, int> in;
    bool terminal;
    int color;
    long long int sum;

    Node(int num, bool terminal = false) : num(num), terminal(terminal), color(0), sum(0) {
    };
};

bool dfs(int vertex, vector<Node *> &nodes, unordered_map<int, bool> &connect_terminal_start) {
    Node *cur_node = nodes[vertex - 1];
    cur_node->color = 1;
    for (pair<int, int> out_node_pair : cur_node->out) {
        int out_node = out_node_pair.first;
        if (connect_terminal_start.find(out_node) != connect_terminal_start.end() &&
            connect_terminal_start[out_node]) {
            if (nodes[out_node - 1]->color == 1) return true;
            if (nodes[out_node - 1]->color == 0)
                if (dfs(out_node, nodes, connect_terminal_start)) return true;
        }
    }
    cur_node->color = 2;
    return false;
}

void getSum(Node *node, vector<Node *> &nodes, unordered_map<int, bool> &connect_terminal_start) {
    unordered_map<int, int> &out_node = node->in;
    long long int sum = 0;
    for (pair<int, int> pair : node->in) {
        int son = pair.first;
        int amount = pair.second;
        if (connect_terminal_start.find(son) != connect_terminal_start.end() && connect_terminal_start[son]) {
            if (nodes[son - 1]->sum == 0) getSum(nodes[son - 1], nodes, connect_terminal_start);
            for (int i = 0 ; i< amount; i++){
                sum += nodes[son - 1]->sum;
                sum %= mod;
            }
        }
    }
    node->sum = sum;
}

int main() {
    unordered_set<int> terminal_states;

    int n, m, k;

    cin >> n >> m >> k;
    vector<Node *> nodes(n);
    for (int i = 1; i <= n; i++) {
        nodes[i - 1] = new Node(i);
    }
    for (int i = 0; i < k; i++) {
        int fd;
        cin >> fd;
        nodes[fd - 1]->terminal = true;
        terminal_states.insert(fd);
    }
    for (int i = 0; i < m; i++) {
        int start, end;
        char ch;
        cin >> start >> end >> ch;
        Node *stNode = nodes[start - 1];
        Node *endNode = nodes[end - 1];
        if (endNode->in.find(start) != endNode->in.end()) endNode->in[start]++;
        else endNode->in[start] = 1;
        if (stNode->out.find(end) != stNode->out.end()) stNode->out[end]++;
        else stNode->out[end] = 1;
        ch = 'a';
    }
    //обходом в глубину ищем все вершины, которые имеют связь с допускающими состояниями
    unordered_map<int, bool> connect_terminal_start;
    unordered_set<int>::iterator itr_terminal_states = terminal_states.begin();
    queue<int> queue;
    queue.push(*itr_terminal_states);
    itr_terminal_states++;
    while (!queue.empty()) {
        int cur_node = queue.front();
        queue.pop();
        if (connect_terminal_start.find(cur_node) == connect_terminal_start.end()) {
            connect_terminal_start[cur_node] = false;
            unordered_map<int, int> &cur_in = nodes[cur_node - 1]->in;
            for (pair<int, int> x : cur_in) {
                int cur_son = x.first;
                if (connect_terminal_start.find(cur_son) == connect_terminal_start.end()) {
                    queue.push(cur_son);
                }
            }
        }
        while (queue.empty() && itr_terminal_states != terminal_states.end()) {
            if (connect_terminal_start.find(*itr_terminal_states) == connect_terminal_start.end()) {
                queue.push(*itr_terminal_states);
            }
            ++itr_terminal_states;
        }
    }
    queue.push(1);
    vector<bool> visited_start(n + 1, false);
    //обходим все вершины в глубину, ищем те, которые имеют связь с началом
    while (!queue.empty()) {//ЕСЛИ ТЛ ТО МОЖНО НЕ ЗАХОДИТЬ В РЕБРА КОТОРЫЕ НЕДОСТУПНЫ ИЗ ТЕРМИНАЛЬНЫХ
        int cur_node = queue.front();
        queue.pop();
        visited_start[cur_node] = true;
        if (connect_terminal_start.find(cur_node) != connect_terminal_start.end()) {
            connect_terminal_start[cur_node] = true;
        }
        unordered_map<int, int> &cur_out = nodes[cur_node - 1]->out;
        for (pair<int, int> x : cur_out) {
            int cur_son = x.first;
            if (!visited_start[cur_son]) {
                queue.push(cur_son);
            }
        }
    }
    bool cycle = 0;


    int x = 10;
    //vector<int> vec;
    for (pair<int, bool> pair : connect_terminal_start) {
        int cur_node = pair.first;
        // vec.push_back(cur_node);
        if (nodes[cur_node - 1]->color == 0)
            if (dfs(cur_node, nodes, connect_terminal_start)) {
                cycle = 1;
                break;
            }
    }
    if (cycle) {
        cout << -1;
    } else {
        nodes[0]->sum = 1;
        long long int sum = 0;
        for (int x: terminal_states) {
            Node * cur_node = nodes[x-1];
            if (cur_node->sum == 0) getSum(cur_node, nodes, connect_terminal_start);
            sum += cur_node->sum;
            sum %= mod;
        }
        cout << sum;
    }

    return 0;
}


