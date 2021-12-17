#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>

// A Tree node
struct Node
{
  char ch;
  int freq;
  Node *left, *right;
};

struct comp
{
  bool operator()(Node* l, Node* r)
  {
    // highest priority item has lowest frequency
    return l->freq > r->freq;
  }
};
Node* createNode(char ch, int freq, Node* left, Node* right);
void encode(Node* root, std::string str, std::unordered_map<char, std::string> &huffmanCode);
void decode(Node* root, int &index, std::string str);
std::string buildHuffmanTree(std::string text);

#endif // HUFFMAN_H
