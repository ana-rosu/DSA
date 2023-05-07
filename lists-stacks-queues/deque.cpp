#include <deque>
#include <fstream>
using namespace std;

ifstream f("deque.in");
ofstream g("deque.out");

int n, k;
long long ans, x;
deque<pair<long long, long long>> dq;

int main() {
    f >> n >> k;

    for (int i = 1; i <= n; i++) {
        f >> x;
        if (!dq.empty())
            while (x <= dq.back().first) {
                dq.pop_back();
                if (dq.empty())
                    break;
            }
        dq.push_back({x, i});

        if (k <= i)
            ans += dq.front().first;

        if (dq.front().second + k - 1 == i)
            dq.pop_front();
    }
    g << ans;

    return 0;
}