


#include <vector>
#include <iostream>
#include <algorithm>
#include <set>
#include <list>
#include <fstream>
#include <string>
#include <climits>
#include <queue>
#include <numeric>


using namespace std;
static string yes = "YES";

//#include "../../../Helper/show_collections.hpp"
bool compare(int i , int j)
{
    cout << 1 << " "<< i << " " << j << "\n";
    cout.flush();
    string ans;
    cin >> ans;
    return (ans == yes);//YES
}


int main() {
#ifdef MY_DEBUG
//    std::ifstream cin("chvatal.in");
//    std::ofstream cout("chvatal.out");
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n;//n<=100
    cin >> n;

    vector<int> vec(n);
    iota(vec.begin(), vec.end(), 1);
//    for (auto i : vec){
//        cout << i << " ";
//    }
    stable_sort(vec.begin(), vec.end(),compare);
//    cout <<  0 << " ";
   /* for (int i = 0; i < vec.size()-1; i++){
        cout << 1 << " "<< vec[i] << " " << vec[i+1] << "\n";
        cout.flush();
        string ans;
        cin >> ans;
        if (ans != yes) {
            for (int k = 0; k <= n; k++){
                cout << 0 << " ";
            }
            return 0;
        }
//        return (ans == "1");//YES
    }*/
    cout << 0 << " ";
    for (auto i : vec){
        cout << i << " ";
    }

}