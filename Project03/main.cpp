#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
using namespace std;

struct Next {
    string next = "";
    string output = "";
};
struct Pair {
    string first;
    string second;
};
// currentState, binaryInput
map<string, vector<Next> > stateTable;
vector<vector<vector<Pair> > > implicationTable;
vector<vector<bool> > incompatible; // 1 means incompatible.
map<string, int> stateIndex;
vector<string> stateName;
vector<string> deletedStates;

void sieveIncompatible(int inputNum, int stateNum);
void listTransitionPair(int stateNum);
void checkTransitionPair(int stateNum, int inputNum);
void mergeCompatibleState(int stateNum, int inputNum);
string intToBinary(int x, int length);
void writeKiss(ofstream& kissOutputFile, int inputNum, int outputNum, int termNum, int stateNum, string resetState);


int main(int argc, char *argv[]){
    ifstream inputFile;
    ofstream kissOutputFile;
    inputFile.open(argv[1]);
    kissOutputFile.open(argv[2]);
    // ifstream inputFile("input.kiss");
    // ofstream kissOutputFile("output.kiss");
    // ofstream dotOutputFile("output.dot");
    
    string resetState = "";
    int inputNum;
    int outputNum;
    int termNum;
    int stateNum;

    while(inputFile.good()){
        string type = ""; 
        string temp = "";
        inputFile >> type;
        if (type == ".start_kiss"){
            continue;
        }
        else if (type == ".i"){
            inputFile >> temp;
            inputNum = stoi(temp);
        }
        else if (type == ".o"){
            inputFile >> temp;
            outputNum = stoi(temp);
        }
        else if (type == ".p"){
            inputFile >> temp;
            termNum = stoi(temp);
        }
        else if (type == ".s"){
            inputFile >> temp;
            stateNum = stoi(temp);
        }
        else if (type == ".r"){
            inputFile >> resetState;
            string input;
            string currentState;
            string nextState;
            string output;
            for(int i = 0; i < termNum ; i++){
                inputFile >> input >> currentState >> nextState >> output;
                Next nextTemp;
                nextTemp.next = nextState;
                nextTemp.output = output;
                stateTable[currentState].push_back(nextTemp);
            }
            int index = 0;
            for (auto val : stateTable){
                stateIndex[val.first] = index;
                stateName.push_back(val.first);
                index++;
            }
        }
        else if (type == ".end_kiss"){
            continue;
        }
    }

    implicationTable = vector<vector<vector<Pair> > >(stateNum, vector<vector<Pair> >(stateNum));
    incompatible = vector<vector<bool> >(stateNum, vector<bool>(stateNum,0));
    sieveIncompatible(inputNum, stateNum);
    
    
    listTransitionPair(stateNum);
    checkTransitionPair(stateNum, inputNum);
    mergeCompatibleState(stateNum, inputNum);
    // for (auto val : stateTable){
    //     cout << val.first << endl;
    //     for (auto n : val.second){
    //         cout << n.next << " " << n.output << endl;
    //     }
    // }
    // for (auto val : stateIndex){
    //     cout << val.first << " " << stateIndex[val.first] << endl;
    // }
    // for (auto val : incompatible){
    //     for (auto val2 : val){
    //         cout << val2 << " ";
    //     }
    //     cout << endl;
    // }

    // for (auto val : deletedStates){
    //     cout << val << " ";
    // }
    // cout << endl;

    // for (int i=0;i<pow(2,inputNum);i++){
    //     cout << implicationTable[1][0][i].first << " " << implicationTable[1][0][i].second << endl;
    // }
    for (auto val : incompatible){
        for (auto val2 : val){
            cout << val2 << " ";
        }
        cout << endl;
    }
    // for (auto val : stateTable){
    //     cout << val.first << endl;
    //     for (auto n : val.second){
    //         cout << n.next << " " << n.output << endl;
    //     }
    // }

    writeKiss(kissOutputFile, inputNum, outputNum, pow(2,inputNum)*(stateNum-deletedStates.size()), stateNum-deletedStates.size(), resetState);

    return 0;
}

void sieveIncompatible(int inputNum, int stateNum){
    for (int i=0;i<stateTable.size();i++){
        incompatible[i][i] = 1;
    }
    for (int i=0;i<stateNum;i++){
        for (int j=0;j<stateNum;j++){
            int count = 0;
            for (int k=0;k<inputNum+1;k++){
                if (stateTable[stateName[i]][k].output != stateTable[stateName[j]][k].output){
                    incompatible[i][j] = 1;
                    break;
                }
            }
        }
    }
}

void listTransitionPair(int stateNum){
    for (int i = 0; i < stateNum; i++){
        for (int j = 0; j < stateNum; j++){
            if (i == j || incompatible[i][j] == 1) continue;
            else{
                int inputNum = stateTable[stateName[i]].size();
                Pair pairTemp;
                vector<Pair> list;
                for (int k = 0; k < inputNum; k++){
                    pairTemp.first = stateTable[stateName[i]][k].next;
                    pairTemp.second = stateTable[stateName[j]][k].next;
                    list.push_back(pairTemp);
                }
                implicationTable[i][j] = list;
            }
        }
    }
}

void checkTransitionPair(int stateNum, int inputNum){
    for (int i = 0; i < stateNum; i++){
        for (int j = 0; j < stateNum; j++){
            if (incompatible[i][j] == 1) continue;
            string first, second;
            for (int k = 0; k < pow(2,inputNum); k++){
                first = implicationTable[i][j][k].first;
                second = implicationTable[i][j][k].second;
                // cout << implicationTable[i][j][k].first << " " << implicationTable[i][j][k].second << endl;
                if (first != second && incompatible[stateIndex[first]][stateIndex[second]] == 1){
                    incompatible[i][j] = 1;
                    checkTransitionPair(stateNum, inputNum);
                }
            }
        }
    }
}

void mergeCompatibleState(int stateNum, int inputNum){
    for (int i = 0; i < stateNum; i++){
        for (int j = 0; j < stateNum; j++){
            if (incompatible[i][j] == 0){
                string keepState = stateName[i];
                string deleteState = stateName[j];
                cout << keepState << " " << deleteState << " " << j << endl;
                for (int k = 0; k < stateNum; k++){
                    incompatible[j][k] = 1;
                    incompatible[k][j] = 1;
                }
                for (auto& val : stateTable){
                    for (auto& n : val.second){
                        if (n.next == deleteState){
                            n.next = keepState;
                        }
                    }
                }
                listTransitionPair(stateNum);
                auto it = find(deletedStates.begin(), deletedStates.end(), deleteState);
                if (it == deletedStates.end()) deletedStates.push_back(deleteState);
            }
        }
    }
}

void writeKiss(ofstream& kissOutputFile, int inputNum, int outputNum, int termNum, int stateNum, string resetState){
    kissOutputFile << ".start_kiss\n";
    kissOutputFile << ".i " << inputNum << "\n";
    kissOutputFile << ".o " << outputNum << "\n";
    kissOutputFile << ".p " << termNum << "\n";
    kissOutputFile << ".s " << stateNum << "\n";
    kissOutputFile << ".r " << resetState << "\n";
    for (auto val : stateTable){
        string curr = val.first;
        auto it = find(deletedStates.begin(), deletedStates.end(), curr);
        if (it != deletedStates.end()) continue;
        for (int i = 0; i < val.second.size(); i++){
            kissOutputFile << intToBinary(i, inputNum) << " " << curr << " " << val.second[i].next << " " << val.second[i].output << "\n";
        }
    }
    kissOutputFile << ".end_kiss";
}
// map<string, vector<Next>> stateTable;
// vector<vector<vector<Pair>>> implicationTable;
// vector<vector<bool>> incompatible; // 1 means incompatible.
// map<string, int> stateIndex;
// vector<string> stateName;
// struct Pair {
//     string first;
//     string second;
// };

// string resetState = "";
// int inputNum;
// int outputNum;
// int termNum;
// int stateNum;
string intToBinary(int x, int length){
    string ret = "";
    for (int i=0;i<length;i++){
        ret += to_string(x%2);
        x/=2;
    }
    reverse(ret.begin(), ret.end());
    return ret;
}