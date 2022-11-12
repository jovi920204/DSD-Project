#include <iostream>
#include <string>
using namespace std;

int main(){
    string numStr = "01111";
    cout << stoi(numStr,0,2) << endl;
}