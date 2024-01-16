#include "hash.cpp"
#include <iostream>
#include <vector>

class TreeNode{
public:
    int hValue;
    string name;
    TreeNode* leftChild;
    TreeNode* rightChild;
    TreeNode(int Value,string n){
        hValue = Value;
        name = n;
        leftChild = NULL;
        rightChild = NULL;
    }
};

int main(){
    
}