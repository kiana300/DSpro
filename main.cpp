#include "hash.cpp"
#include <iostream>
#include <vector>
#include <algorithm>
class TreeNode{
public:
    int hValue;
    TreeNode* leftChild;
    TreeNode* rightChild;
    TreeNode(int Value){
        hValue = Value;
        leftChild = NULL;
        rightChild = NULL;
    }
};

class Genealogy{
private:
    vector<TreeNode*> nodes;
public:
    Genealogy(){}
    //find Node
    TreeNode* findNode(int Value) {
        for (int i = 0; i < nodes.size(); i++) {
            if (nodes[i]->hValue == Value) {
                return nodes[i];
            }
        }
        return NULL; 
    }
    // add a root
    void add(string name) {
        string hValue = sha256(name);
        TreeNode* newNode = new TreeNode(stoi(hValue));
        nodes.push_back(newNode);
    }
    // add a child 
    void addChild(string parent,string child) {
        string pHash = sha256(parent);
        string cHash = sha256(child);
        TreeNode* parentNode = findNode(stoi(pHash));
        if (parentNode != NULL) {
            TreeNode* childNode = new TreeNode(stoi(cHash));
            if (parentNode->leftChild == NULL) {
                parentNode->leftChild = childNode;
            } 
            else {
                parentNode->rightChild = childNode;
            }
            nodes.push_back(childNode);
        }
    }
    // size
    void Size(){
        cout << nodes.size() ;
    }
    void Find(string name){
        bool found = false;
        string hValue = sha256(name);
        for (int i = 0; i < nodes.size(); i++) {
            if (nodes[i] -> hValue == stoi(hValue)) {
                cout << "yes";
                found = true;
                break;
            }
        }
        if(!found){
            cout << "no";
        }
    }
    void deleteRecursive(TreeNode* node) {
            if(node -> leftChild != NULL){
                deleteRecursive(node->leftChild);
            }
            if(node -> rightChild != NULL){
                deleteRecursive(node->rightChild);
            }
            auto it = remove(nodes.begin(), nodes.end(), node);
            nodes.erase(it, nodes.end());
            delete node;
    }
    void Delete(string name){
        string hValue = sha256(name);
        TreeNode* p = findNode(stoi(hValue));
        if (p != NULL) {
            deleteRecursive(p);
        }

        cout << nodes.size();
    }
    void sibling(string n1,string n2){
        string hn1 = sha256(n1);
        string hn2 = sha256(n2);
        
    }
};

int main(){
   Genealogy familyTree;

    familyTree.add("Grandparent");

    familyTree.addChild("Grandparent", "Parent1");
    familyTree.addChild("Grandparent", "Parent2");
    familyTree.addChild("Parent1", "Child1");
    familyTree.addChild("Parent1", "Child2");
    familyTree.Size();
    familyTree.Delete("Parent2");
}