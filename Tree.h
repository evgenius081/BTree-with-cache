#pragma once
#include <string>
#include <iostream>
using namespace std;

struct Node {
    int* keys;
    Node** children;
    Node* parent;
    int count;
    int countSons;
    bool isLeaf;
};

class Tree {
private:
    Node* root;
    int t = 0;
    int* cacheArray;
    int noCache = 0;
    int cache = 0;
    void insert_to_node(int key, Node* node);
    int findPlaceToInsert(Node* node, int key);
    void updateNode(Node** node, int* temp);
    int getChildPosition(Node* parent, Node* child);
    int getKeyPosition(Node* node, int key);
    void copyArray(int** arr1, int* arr2, int count);
    void copyArray(int** arr1, int* arr2, int start, int end);
    void copyArray(int** arr1, int* arr2, int start, int end, int difference);
    void copyArray(Node*** arr1, Node** arr2, int count);
    void copyArray(Node*** arr1, Node** arr2, int start, int end);
    void copyArray(Node*** arr1, Node** arr2, int start, int end, int difference);
    Node* restruct(Node* node);
    void deletenode(Node* node);
    bool searchKey(int key, Node* node);
    int searchKeyLevel(int key, Node* node, int level);
    void remove(int key, Node* node);
    void turnRight(Node* left, Node* parent, Node* right);
    void turnLeft(Node* left, Node* parent, Node* right);
    Node* mergeNodes(Node* node1, Node* node2, Node* parent);
    int takeKey(Node* node, int pos);
    Node* takeChild(Node* node, int pos);
    void removeKeyFromNode(int key, Node* node);
    void removeChildFromNode(Node* child, Node* node);
    void printNode(Node* node);
    void printNodeS(Node* node);
    void addKeyToNode(Node* node, int  key);
    void addChildToNode(Node* node, Node* child, int pos);
    Node* strToNode(string line, Node* parent);
    bool isInArray(int* arr, int key, int size);
    void addKeyToArray(int** array, int key, int* arraySize);
    void updateArray(int** array, int key, int size);
    int getBottomRightNodeLevel();
    void calculateCache(int size, string str);

public:
    Tree();
    ~Tree();
    void setT(int t);
    void insert(int key);
    bool search(int key);
    void remove(int key);
    void load(string line);
    void print();
    void printS();
    void getCache(string str);
};

