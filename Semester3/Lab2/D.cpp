#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <fstream>

#include <set>
#include <map>
//#include "../../../Helper/show_collections.hpp"
using namespace std;

int n, m;


unordered_set<uint16_t> input;
unordered_map<uint16_t,int> input_num;
unordered_set<uint16_t> checked_2;
unordered_map<uint16_t ,unordered_set<uint16_t >> checked3;

bool checked_3(uint16_t a, uint16_t b){
    if (checked3.find(a)!=checked3.end()){
        if (checked3[a].find(b)!=checked3[a].end()) return true;
    }
    return false;
}

uint16_t insert_into_hashset(vector<int> &vec) {

//    unordered_set<uint16_t> &input1 =input ;
//    unordered_set<uint16_t> & checked1 = checked_2;
    uint16_t num = 0;
    for (int i = 0; i < vec.size(); i++) {
        num |= (1 << vec[i]);
    }
    input.insert(num);
    return num;
}

bool check_2(uint16_t t) {

//    unordered_set<uint16_t> &input1 =input ;
//    unordered_set<uint16_t> & checked1 = checked_2;
    if (checked_2.find(t) != checked_2.end()) return true;
    if (input.find(t) == input.end()) return false;
    for (int i = 1; i <= n; i++) {
        uint16_t mask = (1 << i);
        if ((t & mask) != 0){
           if (!check_2(t ^ mask)) return false;
        }
    }
    checked_2.insert(t);
    return true;
}

bool check_3(uint16_t a, uint16_t b){
    if (checked_3(a,b)) return true;
    //a<b
    if (input_num[a] > input_num[b]) swap(a,b);
    for (int i = 1; i <=n; i++){
        uint16_t  mask = (1 << i);
        if ((b & mask)!=0) {
            if ((a & mask ) == 0){
                if (input.find(a | mask)!= input.end()) {
                    checked3[a].insert(b);
                    checked3[b].insert(a);
                    return true;
                }
            }
        }
    }
    return false;
}

int main() {

#ifdef MY_DEBUG
    std::ifstream cin("a.in");
    std::ofstream cout("a.out");
#else
    std::ifstream cin("check.in");
    std::ofstream cout("check.out");
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> m;
    if (m==0) {
        cout << "NO";
        return 0;
    }

//    unordered_set<uint16_t> &input1 =input ;
//    unordered_set<uint16_t> & checked1 = checked_2;
    for (int i = 0; i < m; i++) {
        int k;
        cin >> k;
        vector<int> vec(k);
        for (int j = 0; j < k; j++) {
            cin >> vec[j];
        }
        input_num[insert_into_hashset(vec)] = k;
    }

    for (auto t : input) {
        if (!check_2(t)) {
            cout << "NO";
            return 0;
        }
    }

    for (auto b : input){
        for (auto a : input){
            if (input_num[a]!=input_num[b])  {
                if (!check_3(a,b)) {
                    cout << "NO";
                    return 0;
                }
            }
        }
    }


    cout << "YES";
    return 0;
}