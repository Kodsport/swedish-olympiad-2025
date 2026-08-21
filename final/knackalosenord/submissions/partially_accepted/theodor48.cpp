#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define fo(i, n) for(ll i=0;i<((ll)n);i++)
#define all(x) begin(x),end(x)
typedef vector<ll> vl;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    ll n, k;
    cin >> n >> k;
    string current = "";
    fo(c, k){
        char ch = 'a'+c;
        fo(i, current.size()+1){
            if(current.size() == n) break;
            string temp = current.substr(0, i)+ch+current.substr(i, ((ll)current.size())-i);
            cout << "? " << temp << endl;
            ll res;
            cin >> res;
            if(res == temp.size()){
                current = temp;
            }
        }
    }
    cout << "! " << current << endl;

    return 0;
}