#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MOD = 1000000007;

struct Node {
    int next[26];
    int fail;
    bool output;
    Node() : fail(0), output(false) {
        for(int i=0;i<26;i++) next[i] = -1;
    }
};

int main(){
    int N, M;
    cin >> N >> M;
    vector<string> forbidden(M);
    for(auto &s : forbidden) cin >> s;

    // Build Aho-Corasick automaton
    vector<Node> trie;
    trie.emplace_back(); // root node

    // Insert forbidden words
    for(auto &word : forbidden){
        int current = 0;
        for(char c : word){
            int ci = c - 'a';
            if(trie[current].next[ci] == -1){
                trie[current].next[ci] = trie.size();
                trie.emplace_back();
            }
            current = trie[current].next[ci];
        }
        trie[current].output = true;
    }

    // Build failure links
    queue<int> q;
    // Initialize fail links for depth 1 nodes
    for(int ci=0; ci<26; ci++){
        if(trie[0].next[ci] != -1){
            trie[trie[0].next[ci]].fail = 0;
            q.push(trie[0].next[ci]);
        }
        else{
            trie[0].next[ci] = 0;
        }
    }

    while(!q.empty()){
        int current = q.front(); q.pop();
        for(int ci=0; ci<26; ci++){
            if(trie[current].next[ci] != -1){
                int child = trie[current].next[ci];
                int fail = trie[current].fail;
                while(trie[fail].next[ci] == -1 && fail != 0){
                    fail = trie[fail].fail;
                }
                if(trie[fail].next[ci] != -1){
                    trie[child].fail = trie[fail].next[ci];
                }
                else{
                    trie[child].fail = 0;
                }
                trie[child].output = trie[child].output || trie[trie[child].fail].output;
                q.push(child);
            }
            else{
                trie[current].next[ci] = trie[trie[current].fail].next[ci];
            }
        }
    }

    int num_states = trie.size();

    // Precompute transitions and output flags
    vector<vector<int>> trans(num_states, vector<int>(26, 0));
    vector<bool> isForbidden(num_states, false);
    for(int i=0;i<num_states;i++){
        for(int ci=0; ci<26; ci++){
            trans[i][ci] = trie[i].next[ci];
        }
        isForbidden[i] = trie[i].output;
    }

    // Initialize DP
    // Use two vectors for previous and current
    vector<long long> dp_prev(num_states, 0);
    vector<long long> dp_current(num_states, 0);
    dp_prev[0] = 1;

    for(int pos=0; pos<N; pos++){
        fill(dp_current.begin(), dp_current.end(), 0LL);
        for(int state=0; state<num_states; state++){
            if(dp_prev[state] == 0) continue;
            if(isForbidden[state]) continue;
            for(int ci=0; ci<26; ci++){
                int next_state = trans[state][ci];
                if(!isForbidden[next_state]){
                    dp_current[next_state] = (dp_current[next_state] + dp_prev[state]) % MOD;
                }
            }
        }
        swap(dp_prev, dp_current);
    }

    // Sum all dp_prev[state] where state is not forbidden
    long long result = 0;
    for(int state=0; state<num_states; state++) {
        if(!isForbidden[state]){
            result = (result + dp_prev[state]) % MOD;
        }
    }
    cout << result;
}
