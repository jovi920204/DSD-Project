#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
using namespace std;

struct Next {
    string next = "";
    string output = "";
};
// currentState, binaryInput
map<string, vector<Next>> stateTable;

int main(int argc, char *argv[]){
    // ifstream inputFile;
    // ofstream outputFile;
    // inputFile.open(argv[1]);
    // outputFile.open(argv[2]);
    ifstream inputFile("input.kiss");
    ofstream outputFile("output.kiss");
    
    string resetState = "";
    int inputNum;
    int outputNum;
    int termNum;
    int stateNum;

    while(inputFile.good()){
        string type = ""; 
        string temp = "";
        inputFile >> type;
        cout << type << endl;
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
        }
        else if (type == ".end_kiss"){
            continue;
        }
    }

    for (auto val : stateTable){
        cout << val.first << endl;
        for (auto n : val.second){
            cout << n.next << " " << n.output << endl;
        }
    }

    return 0;
}
