#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <vector>
using namespace std;

string intToBinary(int x, int length);

vector<int>  v;

int main(){

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