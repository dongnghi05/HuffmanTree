/*
 Filename: main.cpp
 Description: Run the project
 Author: Nghi Vo
 Date: 06/01/2019
 Course: Data Structures II
*/
#include <iostream>
#include "huffmantree.h"
#include <vector>

int main(int argc, char* argv[]){
    for(int i = 0; i < argc;++i){
        cout << "Parameter " << i << " :" << argv[i] << endl;
    }
    if(argc != 4){
        cerr << "Not enough or too many arguments" << endl;
        return 1;
    }
    string action = argv[1];
    string filename = argv[2];
    string output = argv[3];
    if(action != "-encode"){
        cerr << "Wrong operation, use -encode" << endl;
    }
    else {
        vector<int> freqencyTable;
        huffmantree huffmanTree;
        string testFile;
        ifstream input;
        char getChar;
        for (int i = 0; i < 256; i++) {
            freqencyTable.push_back(0);
        }
        cout << "File to encoding: " << endl;
        input.open(filename);
        if (!input.is_open()) {
            cout << "File does not exist" << endl;
            exit(0);
        }
        while (!input.eof()) {
            input.get(getChar);
            if (getChar == '\n') {
                freqencyTable[13]++;
                testFile += getChar;
            } else if (getChar == '\r') {
                freqencyTable[10]++;
                testFile += getChar;
            } else {
                freqencyTable[getChar]++;
                testFile += getChar;
            }
        }
        input.close();
        huffmanTree.buildHuffmanTree(freqencyTable);
        cout << huffmanTree.printEncoding();
        huffmanTree.WriteFile(output, testFile);
    }
};