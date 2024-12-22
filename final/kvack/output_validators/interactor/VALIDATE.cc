#include "validate.h"

#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(i, a) for(auto& i : a)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define pb push_back
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

auto Start = chrono::high_resolution_clock::now();
void resettimer() { Start = chrono::high_resolution_clock::now(); }
int elapsedmillis() { return chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - Start).count(); }

/*
Input contains the information of how the judge should behave.
Inputformat:
N Q T
x1 x2 x3 ... xN
*/


// ./a.out ../../data/secret/group1/001-random-01.in  ../../data/secret/group1/001-random-01.ans . < ../../submissions/accepted/harry.py 

const int MAX_ROUNDS = 100;
int query_c = 0;

vector<vector<int>> g;

int main(int argc, char **argv) {
    init_io(argc, argv);
    

    int n,q,t;
    judge_in >> n >> q >> t;

    vi pos(n);
    rep(i,0,n) cin >> pos[i];



    //std::seed_seq seed(all(words[0])); 
    //std::mt19937 generator(seed);   // mt19937 is a standard mersenne_twister_engine


    // "game loop"
    while (query_c < MAX_ROUNDS) {
        // Judge writes an output
        /*
        if (query_c < n){
            prev = words[query_c];
            cout << prev << endl;
        }
        else {
            
            if (k == 1) {
                int length = generator() % 100 + 1; // randomize length of the string
                prev = "";
                rep(i,0,length) {
                    prev = prev + (char)(generator() % 26 + 97);
                    //cout <<  // randomize the chars of the string
                }
                cout << prev << endl;
            }
            else if (k == 2) {
                prev = user_words[sz(user_words) - 1];
                cout << prev << endl;
            }
            else if (k == 3) {
                prev = user_words[(generator() % sz(user_words))];
                cout << prev << endl;
            }
        }
        */


        // Read in user query
        string query;
        if (!getline(cin, query)) {
            judge_message("Expected more queries\n");
            break;
        };

        if (sz(query) == 0) {
            judge_message("Query is empty\n");
            cout << "!" << endl;
            break;
        }


        bool valid = true;
        for (char &c : query) {
            if (!('a' <= c && c <= 'z')) {
                valid = false;
                judge_message("Query contains invalid character\n");
                cout << "!" << endl;
                break;
            }
        }

        if (!valid) break;

        if (sz(query) > 100) {
            judge_message("Query is too long\n");
            cout << "!" << endl;
            break;
        }

        if (query == prev) {
            judge_message("Query is the same as the judge's answer\n");
            cout << "!" << endl;
            break;
        }

        query_c++;
    }

    if (query_c == 0) wrong_answer("Did not successfully answer any queries.\n");
    else if (query_c == MAX_ROUNDS) accept_with_score(100);
    else accept_with_score(query_c); 

}
