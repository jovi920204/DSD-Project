#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

string intToBinary(int x, int length);

vector<int>  v;

int main(){
    int x;
    int length;
    // cin >> x >> length;
    // cout << intToBinary(x,length) << endl;
    for (int i=0;i<5;i++){
        v.push_back(i);
    }
    for (auto& val : v){
        if (val == 3) val = 10;
    }
    for (int i=0;i<v.size();i++){
        cout << v[i] << " ";
    }
    cout << endl;
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