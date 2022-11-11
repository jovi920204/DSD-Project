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
        int inputNum;
        int outputNum;
        int patermNum;
        int variableNum;
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
            patermNum = stoi(temp);
        }
        else if (type == "s"){
            inputFile >> temp;
            variableNum = stoi(temp);
        }
        else if (type == "r"){
            inputFile >> name;
            for(int i = 0; i < patermNum ; i++){
                
            }
        }
        else if (type == ".end_kiss"){
            continue;
        }
    }
    return 0;
}