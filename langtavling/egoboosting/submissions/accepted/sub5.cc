#include <iostream> // score: 100
#include <vector>
#include <cmath>

using namespace std;

class SparseTable {
private:
    vector<vector<pair<int, int>>> st;
    vector<int> log;

public:
    SparseTable(const vector<int>& arr) {
        int n = arr.size();
        log.resize(n + 1);
        log[1] = 0;
        for (int i = 2; i <= n; ++i) log[i] = log[i / 2] + 1;

        st.resize(n, vector<pair<int, int>>(log[n] + 1));
        for (int i = 0; i < n; ++i)
            st[i][0] = {arr[i], i};

        for (int j = 1; j <= log[n]; ++j) {
            for (int i = 0; i + (1 << j) <= n; ++i) {
                auto left = st[i][j - 1];
                auto right = st[i + (1 << (j - 1))][j - 1];
                st[i][j] = (left.first > right.first) ? left : right;
            }
        }
    }

    pair<int, int> query(int l, int r) {
        int j = log[r - l + 1];
        auto left = st[l][j];
        auto right = st[r - (1 << j) + 1][j];
        return (left.first > right.first) ? left : right;
    }
};

int f(const vector<int>& arr, SparseTable& st, int l, int r) {
    if (l >= r) return 0;
    auto [maxVal, maxIdx] = st.query(l, r - 1);
    int leftResult = f(arr, st, l, maxIdx);
    int rightResult = f(arr, st, maxIdx + 1, r);
    int fromLeft = max(maxVal - (maxIdx - l), leftResult);
    int fromRight = max(maxVal - (r - maxIdx - 1), rightResult);
    return min(fromLeft , fromRight);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, e;
    cin >> n >> e;
    vector<int> arr(n);    
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
        arr[i] = max(0, arr[i] - e);
    }
    SparseTable st(arr);
    cout << f(arr, st, 0, n) << endl;
    return 0;
}
