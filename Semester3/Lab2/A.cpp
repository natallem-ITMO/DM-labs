


#include <vector>
#include <iostream>
#include <algorithm>
#include <set>
#include <list>
#include <unordered_map>
#include <map>
#include <fstream>
#include <string>
#include <climits>
#include <queue>
#include <numeric>


//#include "../../../Helper/show_collections.hpp"

using namespace std;

struct compare {
    bool operator()(long a, long b) const {
        return a > b;
    }
};


int main() {
//#ifdef MY_DEBUG
    std::ifstream cin("schedule.in");
    std::ofstream cout("schedule.out");
//#endif
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n;
    cin >> n;
    map<long, vector<long>> tasks;
    for (int i = 0; i < n; i++){
        long a, b;
        cin >> a >> b;
        tasks[a].push_back(b);
    }

    long long sum = 0;
    multiset<long> cur_tasks;

    for (auto pair : tasks){
        long time=pair.first;
        for (auto t : pair.second){
            cur_tasks.insert(t);
        }
        for (int i = cur_tasks.size(); i > time; i--){
            sum+=*cur_tasks.begin();
            cur_tasks.erase(cur_tasks.begin());
        }
    }
    cout << sum;
}