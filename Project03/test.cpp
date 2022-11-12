#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

string intToBinary(int x, int length);

int main(){
     int x;
     int length;
     cin >> x >> length;
     cout << intToBinary(x,length) << endl;
}

string intToBinary(int x, int length){
    string ret = "";
    for (int i=0;i<length;i++){
        ret += to_string(x%2);
        x/=2;
    }
    reverse(ret.begin(), ret.end());
    return ret;
}