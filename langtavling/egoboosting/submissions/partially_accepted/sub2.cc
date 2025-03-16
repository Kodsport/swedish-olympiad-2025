#include <iostream> // score: 19
#include <vector>

using namespace std;

int INFINITE = 2E9;

int n, e;

int calculate_purchase(const vector<int>& arr, int index, int left, int right, int energy) {
    int purchased = 0;
    if (energy < arr[index]) {
        purchased = arr[index] - energy;
        energy = arr[index];
    }
    energy++;
    if (left == -1 && right == n) {
        return purchased;
    }
    int left_ans = INFINITE;
    int right_ans = INFINITE;
    if (right != n) {
        right_ans = calculate_purchase(arr, right, left, right + 1, energy);
    }
    if (left != -1) {
        left_ans = calculate_purchase(arr, left, left - 1, right, energy);
    }
    return purchased + min(left_ans, right_ans);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> e;
    vector<int> arr(n);    
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
        arr[i] = max(0, arr[i] - e);
    }
    int ans = INFINITE;
    for (int i = 0; i < n; i++) {
        int purchased = calculate_purchase(arr, i, i - 1, i + 1, 0);
        if (ans > purchased) {
            ans = purchased;
        }
    }
    cout << ans << endl;
    return 0;
}
