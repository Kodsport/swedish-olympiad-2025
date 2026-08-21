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
    vl v(k);
    ll last = n;
    fo(i, k-1){
        cout << "? " << string(n, 'a'+i) << endl;
        cin >> v[i];
        last-=v[i];
    }
    v[k-1] = last;
    pair<ll,ll> biggest = {-1, -1};
    fo(i, k){
        biggest=max(biggest, {v[i], i});
    }
    string current = string(biggest.first, 'a'+biggest.second);
    v[biggest.second] = 0;
    fo(c, k){
        char ch = 'a'+c;
        ll am = v[c];
        fo(i, current.size()+1){
            if(current.size() == n || !am) break;
            string temp = current.substr(0, i)+ch+current.substr(i, ((ll)current.size())-i);
            cout << "? " << temp << endl;
            ll res;
            cin >> res;
            if(res == temp.size()){
                am--;
                current = temp;
            }
        }
    }
    cout << "! " << current << endl;

    return 0;
}