#include <iostream>
#include <fstream>
#include <stack>
using namespace std;

ifstream f("paranteze.in");
ofstream g("paranteze.out");

stack <pair <int, char>> s;
char p; 
int n, maxi;

int main(){
    f >> n; // number of parantheses
    for (int i = 0; i < n; ++i){
        f>>p; // paranthesis
        if (p == '(' || p == '[' || p == '{')
            s.push({i, p});
        else 
            if (!s.empty())
            if ((p == ')' && s.top().second == '(') || ( p == ']' && s.top().second == '[') || (p == '}' && s.top().second == '{')){
                s.pop();
                if (s.empty())                          
                    maxi = max(maxi, i + 1);        
                else
                    maxi = max(maxi, i - s.top().first);  
            }
            else
                s.push({i, p});            
    }
    g << maxi;

    return 0;
}