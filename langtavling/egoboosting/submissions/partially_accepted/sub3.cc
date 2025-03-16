#include <iostream> // score: 42
#include <vector>

using namespace std;

int INFINITE = 2E9;

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
    int ans = INFINITE;
    for (int i = 0; i < n; i++) {
        int left = i - 1;
        int right = i + 1;
        int purchased = arr[i];
        int energy = arr[i] + 1;
        while ((left >= 0) || (right <= n - 1)) {
            int next;
            if (left == -1) {
                next = right;
                right++;
            } else if (right == n) {
                next = left;
                left--;
            } else if (arr[left] < arr[right]) {
                next = left;
                left--;
            } else {
                next = right;
                right++;
            }
            if (energy < arr[next]) {
                purchased += arr[next] - energy;
                energy = arr[next];
            }
            energy++;
        }
        if (ans > purchased) {
            ans = purchased;
        }
    }
    cout << ans << endl;
    return 0;
}
