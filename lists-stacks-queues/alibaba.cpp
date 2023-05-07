#include <fstream>
using namespace std;

ifstream f("alibaba.in");
ofstream g("alibaba.out");

int n, k, i, t, v[10005];
int main() {
    f >> n >> k;
    while (n--) {
        char digit;
        f >> digit;
        while (k > 0 && t && digit - '0' > v[t]) {
            k--;
            t--;
        }
        v[++t] = digit - '0';
    }

    for (i = 1; i <= t - k; i++)
        g << v[i];
}