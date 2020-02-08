

//
// Created by lnv20 on 09.05.2019.
//




#include <fstream>
//#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#include <cmath>
#include <iomanip>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <set>
#include <algorithm>


using namespace std;
std::ifstream cin("nfc.in");
std::ofstream cout("nfc.out");
//std::ifstream cin("a.in");
//std::ofstream cout("a.out");

static void show_vector(vector<long long int> &vec) {
    for (long long int i = 0; i < vec.size(); i++) {
        cout << vec[i] << " ";
    }
    cout << endl;
}

static void show_matrix(vector<vector<long long int>> &m) {
    for ( long long int i = 0; i < m.size(); i++) {
        show_vector(m[i]);
    }
    cout << endl;
}
void show_matrix_3( vector<vector<vector<long long int>>> & dp){
    for (long long int i = 0; i < 26; i++){
        cout << (char) ('A' + i)<< endl;
        show_matrix(dp[i]);
    }
}

 int main() {
    long long int mod = 1000000007;
  //  unordered_map<char, unordered_map<char, unordered_set<char>>> rules;
    unordered_map<char, unordered_set<char>> t_rules;
    unordered_map<char, unordered_set<string>> rules;

    long long int n;
    char start;
    cin >> n >> start;
    char in;
    string word;
    for (long long int i = 0; i < n; i++){
        cin >> in >> word >> word;
        if (word.length() > 1) {
            rules[in].insert(word);
        } else {
            t_rules[in].insert(word[0]);
        }

    }
    cin >> word;
   // cout << mod * mod;
    vector<vector<vector<long long int>>> dp(26, vector<vector<long long int>>(word.size(), vector<long long int>(word.size(),0)));
    for (long long int i = 0; i < word.length(); i++){
        char cur_char = word[i];
        for (char j = 'A'; j <= 'Z'; j++){
            if (t_rules[j].find(cur_char) != t_rules[j].end()){
                dp[j-'A'][i][i] = 1;
            }
        }
    }
    for (long long int i = 1; i < word.length(); i++){//длина подстроки
        for (long long int j = 0; j+i < word.length(); j++){//передвигаемся по строки со сдвигом
            for (char k= 'A'; k <='Z'; k++){//перебираем первые буквы правила
                long long int sum = 0;
               // prlong long intf("find  dp[%c][%d][%d]\n", k,j,j+i);
                for (string rule : rules[k]){//перебираем все правила
                    for (long long int s = j; s < j+i; s++ ){
                        /*long long int a = rule[0]-'A';
                        long long int b = dp[rule[0]-'A'][j][s];
                        long long int c = rule[1]-'A';
                        long long int d = dp[rule[1]-'A'][s+1][j+i];*/
                        sum += (dp[rule[0]-'A'][j][s]*dp[rule[1]-'A'][s+1][j+i]) % mod;
                      //  cout << rule;
                       // prlong long intf(" dp[%c][%d][%d]*dp[%c][%d][%d] = %d\n",rule[0],j,s,rule[1],s+1,j+i,dp[rule[0]-'A'][j][s]*dp[rule[1]-'A'][s+1][j+i]);
                    }
                }

                dp[k-'A'][j][j+i] += sum;
                dp[k-'A'][j][j+i] %= mod;

               // prlong long intf("res=%d\n",dp[k-'A'][j][j+i]);
            }
        }
    }

 //   show_matrix_3( dp);
    cout << dp[start-'A'][0][word.length()-1];

    return 0;
}
