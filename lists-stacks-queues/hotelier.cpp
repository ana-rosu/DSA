#include <iostream>
using namespace std;

int main(){
    int n, v[10];
    cin >> n;

    for(int cnt = 0; cnt < n; ++cnt){
        char customer;
        cin >> customer;
        //left entrance
        if(customer == 'L'){
            for(int i = 0; i < 10; i++)
                if(v[i] == 0){
                    v[i] = 1;
                     break;
                }

        //right entrance
        }else if(customer == 'R'){
            for(int i = 9; i >= 0; i--)
                if(v[i] == 0){
                    v[i] = 1;
                    break;
                }
        }else
            v[customer - '0'] = 0;
    }

    for(int i = 0; i < 10; i++)
      cout << v[i];

    return 0;
}
// #include <iostream>
// using namespace std;

// char dir;
// int n, v[10];

// int main() {
//     cin >> n;

//     while (n--) {
//         cin >> dir;
//         if (dir == 'L') {
//             for (int i = 0; i <= 9; i++)
//                 if (v[i] == 0) {
//                     v[i] = 1;
//                     break;
//                 }
//         } else if (dir == 'R') {
//             for (int i = 9; i >= 0; i--)
//                 if (v[i] == 0) {
//                     v[i] = 1;
//                     break;
//                 }
//         } else
//             v[dir - '0'] = 0;
//     }

//     for (int i = 0; i <= 9; i++)
//         cout << v[i];
// }