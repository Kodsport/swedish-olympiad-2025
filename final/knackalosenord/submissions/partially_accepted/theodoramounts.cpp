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
    vl v(k);
    ll last = n;
    fo(i, k-1){
        cout << "? " << string(n, 'a'+i) << endl;
        cin >> v[i];
        last-=v[i];
    }
    v[k-1] = last;
    pl biggest = {-1, -1};
    fo(i, k){
        biggest=max(biggest, {v[i], i});
    }
    string current = string(biggest.F, 'a'+biggest.S);
    v[biggest.S] = 0;
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