// #pragma GCC target ("avx,avx2,fma")
// #pragma GCC optimize ("Ofast,inline") // O1 - O2 - O3 - Os - Ofast
// #pragma GCC optimize ("unroll-loops")
#include <bits/stdc++.h>

using namespace std;

#define rep(i, a, b) for (ll i = (a); i < (b); ++i)
#define per(i, a, b) for (ll i = (b) - 1; i >= (a); --i)
#define trav(a, x) for (auto &a : x)

#define all(x) x.begin(), x.end()
#define sz(x) (ll)x.size()
#define pb push_back
#define debug(x) cout<<#x<<" = "<<x<<endl

#define umap unordered_map
#define uset unordered_set

typedef pair<int, int> ii;
typedef pair<int, ii> iii;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<vi> vvi;

typedef long long ll;
typedef pair<ll,ll> pll;
typedef pair<ll,pll> ppll;
typedef vector<ll> vll;
typedef vector<pll> vpll;
typedef vector<vll> vvll;

const ll INF = 1'000'000'007;

struct Node {
    ll val=0,lo,hi;
    Node *l,*r;
    Node(ll L, ll R) : lo(L),hi(R) {
        if(hi-lo!=1) {
            ll mid=(lo+hi)/2;
            l=new Node(lo,mid);
            r=new Node(mid,hi);
        }
    }

    ll query(ll L,ll R) {
        if(hi<=L||R<=lo) return 0;
        if(L<=lo&&hi<=R) return val;

        return l->query(L,R)+r->query(L,R);
    }

    void update(ll pos,ll x) {
        if(pos<lo||hi<=pos) return;
        val+=x;
        if(hi-lo==1) return;
        l->update(pos,x);
        r->update(pos,x);
    }
};

ll n;
ll rows,cols;
vvll grid;
vll degrees;
vector<vpll> teddies;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    cin>>n>>rows>>cols;
    grid.assign(rows,vll(cols));
    degrees.assign(n,0);
    teddies.resize(n);
    rep(i,0,rows) rep(j,0,cols) {
        cin>>grid[i][j];
        --grid[i][j];
        teddies[grid[i][j]].emplace_back(i,j);
        if(i&&grid[i-1][j]!=grid[i][j]) ++degrees[grid[i][j]];
    }

    vll answers(n,-1);
    queue<ll> q;
    Node segtree(0,cols);
    vll lpoints,rpoints;
    lpoints.assign(cols,0);
    rpoints.assign(cols,0);
    rep(i,0,n) if(!degrees[i]) q.push(i);
    while(sz(q)) {
        ll teddy=q.front(); q.pop();
        ll lo=cols,hi=0;
        trav(cell,teddies[teddy]) {
            ll row=cell.first,col=cell.second;
            lo=min(lo,col);
            hi=max(hi,col);
            if(row+1!=rows) {
                if(--degrees[grid[row+1][col]]==0) q.push(grid[row+1][col]);
            }
        }

        ll ans=segtree.query(0,lo);
        rep(i,lo,hi+1) ans+=lpoints[i];
        rep(i,lo,hi+1) {
            ll cnt=lpoints[i];
            lpoints[i]=0;
            lpoints[lo]+=cnt;
            segtree.update(lo,cnt);
            segtree.update(i,-cnt);
        }
        rep(i,lo,hi+1) {
            ll cnt=rpoints[i];
            rpoints[i]=0;
            rpoints[hi]+=cnt;
            segtree.update(hi,-cnt);
            segtree.update(i,cnt);
        }
        ++lpoints[lo];
        ++rpoints[hi];
        segtree.update(lo,1);
        segtree.update(hi,-1);
        answers[teddy]=ans;
    }

    rep(i,0,n) cout<<answers[i]<<' ';
    cout<<endl;
    _Exit(0);
    return 0;
}