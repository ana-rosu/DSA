#include <iostream>
#include <fstream>
#include <stack>
using namespace std;

ifstream f("queue.in");
ofstream g("queue.out");

int main(){
  stack<int> s1,s2;
  int n, WR;
  string command;

  f>>n;
  for(int i = 0; i < n; ++i){
    f>>command;
    if(command == "pop_front()"){
      g<< i+1<<": ";
      if(!s2.empty()){
        //if s2 is not empty => pop_front from s2
        //  while(s2.size() > 1){
        //     WR = s2.top();
        //     s1.push(WR);
        //     s2.pop();
        //     g<<"pop(2) push(1,"<<WR<<") "; 
        // }
        WR = s2.top();
        g<<"pop(2) write("<<WR<<") \n";
        s2.pop();
      }
      else{
        //if s2 is empty => pop_front from s1
        while(s1.size() > 1){
            WR = s1.top();
            s2.push(WR);
            s1.pop();
            g<<"pop(1) push(2,"<<WR<<") "; 
        }
        WR = s1.top();
        g<<"pop(1) write("<<WR<<") \n";
        s1.pop();
      }
    }
    else{
    // command is push_back(number)
      WR = stoi(command.substr(10,command.size()-11));
      s1.push(WR);
      g << i+1 << ": read(" << WR << ") push(1," << WR <<")\n";
    }
  }
  f.close();
  g.close();      
 return 0;
}
