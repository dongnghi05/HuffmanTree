/*
 Filename: huffmantree.cpp
 Description: Implementation of the class HuffmanTree to represent the binary Huffman Tree
 Author: Nghi Vo
 Date: 06/01/2019
 Course: Data Structures II
*/
#include "huffmantree.h"
#include <memory>
#include "sstream"

/**
 * Create node for huffman tree
 * @param e
 * @param left
 * @param right
 * @return node for huffman tree
 */
Node* huffmantree::getNode(pair<string,int> e, Node* left, Node*right){
    Node* newNode = new Node();
    newNode->element = e;
    newNode->left = left;
    newNode->right = right;
    return newNode;
}
/**
 * Build huffman tree based on the frequency table
 * @param array
 */
void huffmantree::buildHuffmanTree(vector<int> array) {
    for(int i = 0; i < 256; i++){
        if(array[i] != 0) {
            // Character \r
            if(i == 10){
                FrequencyTable.insert(pair<string, int>("LF", array[i]));
            }
            // Character \n
            else if(i == 13){
                FrequencyTable.insert(pair<string, int>("CR", array[i] - 1));
            }
            // Character digit or char
            else {
                string s(1,i);
                FrequencyTable.insert(pair<string, int>(s, array[i]));
            }
        }
    }

    // add character to priority queque
    for (auto it :FrequencyTable){
        Node * neo = getNode(pair<string, int>(it.first, it.second), nullptr, nullptr);
        FrequencyTableAsc.push(neo);
    }

    // add to the stack to create asscending order of frequency table
    priority_queue<Node*, vector<Node*>, comparation> check = FrequencyTableAsc;
    while(!check.empty()){
        reversal.push(check.top()->element.first);
        check.pop();
    }

    // create huffman tree
    while(FrequencyTableAsc.size() != 1){
        Node* left = FrequencyTableAsc.top();
        FrequencyTableAsc.pop();
        Node* right = FrequencyTableAsc.top();
        FrequencyTableAsc.pop();
        Node*top = getNode(pair<string, int>(left->element.first + right->element.first, left->element.second + right->element.second), left, right);
        FrequencyTableAsc.push(top);
    }
    root = FrequencyTableAsc.top();
    string encodeString;
    encode(root, encodeString);
}

/**
 * encode function using huffman tree
 * @param root
 * @param encodeString
 */
void huffmantree::encode(Node *root, string encodeString) {
    if(root == nullptr){
        return;
    }
    if(root->left == nullptr && root->right == nullptr){
        HuffmanTable[root->element.first] = encodeString;
    }
    encode(root->left, encodeString + "1");
    encode(root->right, encodeString + "0");
}
/**
 *
 * @return string of the encode
 */
string huffmantree::printEncoding() {
    stringstream retVal;
    while(!reversal.empty()){
        retVal <<"{key: " << reversal.top() << ", code " << HuffmanTable[reversal.top()] << "}" << endl;
        reversal.pop();
    }
    return retVal.str();
}

/**
 * delete the tree
 */
huffmantree::~huffmantree() {
    delete root;
}

/**
 * write to the file with the encode string
 * @param output
 * @param fileName
 */
void huffmantree::WriteFile(string output, string fileName) {
    ofstream outstream;
    string encodedFile;
    outstream.open(output);
    if(!outstream){
        cerr << "Error: file could not be opened" << endl;
        exit(1);
    }
    for(auto i: fileName){
        string s(1,i);
        encodedFile += HuffmanTable[s];
    }
    outstream << encodedFile;
    outstream.close();
}
/**
 * make the priority queque desendent
 * @param left
 * @param right
 * @return true if left > right and false if left < right
 */
bool comparation::operator()(Node *left, Node *right) {
    if(left->element.second == right->element.second){
        return left->element.first[0] > right->element.first[0];
    }
    else {
        return left->element.second > right->element.second;
    }
}
/**
 * delete node
 */
Node::~Node() {
    if(left != nullptr){
        delete left;
    }
    if(right != nullptr){
        delete right;
    }
}
