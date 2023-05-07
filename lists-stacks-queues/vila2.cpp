#include <fstream>
#include <queue>

using namespace std;

ifstream f("vila2.in");
ofstream g("vila2.out");

int n, k, i, ans, v[100005];
deque<int> dq_min, dq_max;

int main() {
    f >> n >> k;

    for (i = 0; i < n; i++)
        f >> v[i];

    for (i = 0; i < n; i++) {
        while (!dq_max.empty() && dq_max.front() < i - k)
            dq_max.pop_front();
        while (!dq_min.empty() && dq_min.front() < i - k)
            dq_min.pop_front();

        while (!dq_max.empty() && v[dq_max.back()] <= v[i])
            dq_max.pop_back();
        while (!dq_min.empty() && v[dq_min.back()] >= v[i])
            dq_min.pop_back();

        dq_max.push_back(i);
        dq_min.push_back(i);

        if (v[dq_max.front()] - v[dq_min.front()] > ans)
            ans = v[dq_max.front()] - v[dq_min.front()];
    }

    g << ans;
}