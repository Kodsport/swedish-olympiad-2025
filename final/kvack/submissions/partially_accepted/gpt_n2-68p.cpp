#include <iostream>
#include <vector>
#include <set>
using namespace std;

int main() {
    int T;
    cin >> T;

    vector<int> out;

    cout << "? 0" << endl;
    int l;
    cin >> l;
    out.push_back(l);

    cout << "? " << 1000000000 << endl;
    cin >> l;
    out.push_back(l);

    set<pair<int, int>> asked;

    bool found = true;
    while (found) {
        found = false;
        for (size_t i = 0; i < out.size() - 1; ++i) {
            if (asked.count({out[i], out[i + 1]})) {
                continue;
            }
            asked.insert({out[i], out[i + 1]});
            cout << "? " << (out[i] + out[i + 1] + 1) / 2 << endl;
            int ans;
            cin >> ans;
            if (ans == out[i] || ans == out[i + 1]) {
                continue;
            }
            out.insert(out.begin() + i + 1, ans);
            found = true;
            break;
        }
    }

    cout << "! " << out.size() << endl;
    for (size_t i = 0; i < out.size(); ++i) {
        cout << out[i] << " ";
    }
    cout << endl;

    return 0;
}
