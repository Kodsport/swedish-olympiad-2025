#include <iostream> // score: 17
#include <vector>

using namespace std;

int INFINITE = 2E9;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, e;
    cin >> n >> e;
    vector<int> arr(n);
    int small = INFINITE;
    int big = -INFINITE;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        arr[i] = max(0, arr[i] - e);
        if (small > arr[i]) {
            small = arr[i];
        }
        if (big < arr[i]) {
            big = arr[i];
        }
    }
    if (small == big) {
        cout << small << endl;
        return 0;
    }

    int max_small_length = 0;
    int cur_small_length = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] == small) {
            cur_small_length++;
        } else {
            cur_small_length = 0;
        }
        if (max_small_length < cur_small_length) {
            max_small_length = cur_small_length;
        }
    }
    cout << small + max(0, big - small - max_small_length);
    
    return 0;
}
