// score: 7
// This greedy solution always starts at the EP with minimum difficulty.
// Although it's a wrong algorithm, it is correct for N <= 3.
#include <iostream> 
#include <vector>
#include <algorithm>

using namespace std;

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
    auto min_it = min_element(arr.begin(), arr.end());
    int min_value = *min_it;
    int min_index = distance(arr.begin(), min_it);
    int left = min_index - 1;
    int right = min_index + 1;
    int purchased = arr[min_index];
    int energy = arr[min_index] + 1;
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
    cout << purchased << endl;
    return 0;
}
