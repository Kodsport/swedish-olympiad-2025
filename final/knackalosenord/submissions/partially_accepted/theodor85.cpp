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
    vector<pair<ll,ll>> v(k);
    ll last = n;
    fo(i, k-1){
        cout << "? " << string(n, 'a'+i) << endl;
        cin >> v[i].first;
        v[i].second = i;
        last-=v[i].first;
    }
    v[k-1] = {last, k-1};
    sort(all(v));
    string current = string(v[0].first, 'a'+v[0].second);
    v[0].first = 0; 
    
    fo(c, k){
        char ch = 'a'+v[c].second;
        ll am = v[c].first;
        fo(i, current.size()+1){
            if(current.size() == n || !am) break;
            if(ch == current[i]) continue;
            ll res;
            if(i<current.size() && current.size()+1<n){
                string temp = current.substr(0, i)+ch+current[i]+ch+current.substr(i+1, ((ll)current.size())-i-1);
                cout << "? " << temp << endl;
                cin >> res;
                if(res == current.size()){
                    i++;
                    continue;
                }
                if(res == temp.size()){
                    am-=2;
                    current = temp;
                    continue;
                }
                temp = current.substr(0, i)+ch+current.substr(i, ((ll)current.size())-i);
                cout << "? " << temp << endl;
                cin >> res;
                if(res == temp.size()){
                    am--;
                    current = temp;
                    continue;
                }
                temp = current.substr(0, i+1)+ch+current.substr(i+1, ((ll)current.size())-i-1);
                cout << "? " << temp << endl;
                cin >> res;
                if(res == temp.size()){
                    am--;
                    current = temp;
                }
                
            }else if(i==current.size()){
                current = current.substr(0, i)+string(am, ch);
                am = 0;
            }else{
                string temp = current.substr(0, i)+ch+current.substr(i, ((ll)current.size())-i);
                cout << "? " << temp << endl;
                cin >> res;
                if(res == temp.size()){
                    am--;
                    current = temp;
                }
            }
        }
    }
    cout << "! " << current << endl;

    return 0;
}