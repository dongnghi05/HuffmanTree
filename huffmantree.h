/*
 Filename: huffmantree.h
 Description: Declaration of the class HuffmanTree to represent the binary Huffman Tree
 Author: Nghi Vo
 Date: 06/01/2019
 Course: Data Structures II
*/

#ifndef HUFFMAN_DONGNGHI05_HUFFMANTREE_H
#define HUFFMAN_DONGNGHI05_HUFFMANTREE_H


#include <utility>
#include <queue>
#include <map>
#include <fstream>
#include <iostream>
#include "unordered_map"
#include <stack>
using namespace std;
struct Node
{
    pair<string, int> element;
    Node *left, *right;
    ~Node();
};

struct comparation
{
    bool operator()(Node* left,Node* right);
};
class huffmantree {
    Node *root;
    map<string, string> HuffmanTable;
    map<string, int> FrequencyTable;
    priority_queue<Node*, vector<Node*>, comparation> FrequencyTableAsc;
    Node* getNode(pair<string,int> e, Node* left, Node*right);
    stack<string> reversal;
public:
    void buildHuffmanTree(vector<int> freq);
    void encode(Node* root, string encoded);
    string printEncoding();
    ~huffmantree();

    void WriteFile(string output, string fileName);
};

#endif //HUFFMAN_DONGNGHI05_HUFFMANTREE_H
