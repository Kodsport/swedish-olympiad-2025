#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define INF ((ll)(1e9+7))
#define fo(i, n) for(ll i=0;i<((ll)n);i++)
#define deb(x) cout << #x << " = " << (x) << endl;
#define deb2(x, y) cout << #x << " = " << (x) << ", " << #y << " = " << (y) << endl
#define pb push_back
#define mp make_pair
#define F first
#define S second
#define LSOne(S) ((S) & (-S))
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
typedef pair<int, int> pii;
typedef pair<ll, ll> pl;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<pii> vpii;
typedef vector<pl> vpl;
typedef vector<vi> vvi;
typedef vector<vl> vvl;
typedef vector<vpii> vvpii;
typedef vector<vpl> vvpl;



int main() {
    cin.tie(0)->sync_with_stdio(0);

    ll n, k;
    cin >> n >> k;
    vpl v(k);
    ll last = n;
    fo(i, k-1){
        cout << "? " << string(n, 'a'+i) << endl;
        cin >> v[i].F;
        v[i].S = i;
        last-=v[i].F;
    }
    v[k-1] = {last, k-1};
    sort(all(v));
    string current = string(v[0].F, 'a'+v[0].S);
    v[0].F = 0; 
    
    fo(c, k){
        char ch = 'a'+v[c].S;
        ll am = v[c].F;
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