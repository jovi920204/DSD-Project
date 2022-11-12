#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

int main(int argc, char *argv[]){
    // ifstream inputFile;
    // ofstream outputFile;
    // inputFile.open(argv[1]);
    // outputFile.open(argv[2]);
    ifstream inputFile("input.kiss");
    ofstream outputFile("output.kiss");

    while(inputFile.good()){
        string type = "";
        string name = "";
        string temp = "";
        string resetState = "";
        int inputNum;
        int outputNum;
        int termNum;
        int stateNum;
        inputFile >> type;
        if (type == ".start_kiss"){
            continue;
        }
        else if (type == "i"){
            inputFile >> temp;
            inputNum = stoi(temp);
        }
        else if (type == "o"){
            inputFile >> temp;
            outputNum = stoi(temp);
        }
        else if (type == "p"){
            inputFile >> temp;
            termNum = stoi(temp);
        }
        else if (type == "s"){
            inputFile >> temp;
            stateNum = stoi(temp);
        }
        else if (type == "r"){
            inputFile >> resetState;
            for(int i = 0; i < termNum ; i++){

            }
        }
        else if (type == ".end_kiss"){
            continue;
        }
    }
    return 0;
}
