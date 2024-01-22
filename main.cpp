#include "hash.cpp"
#include <iostream>
#include <vector>
#include <algorithm>
class TreeNode{
public:
    string hValue;
    TreeNode* leftChild;
    TreeNode* rightChild;
    TreeNode* parent;
    TreeNode(string Value , TreeNode* parentNode = NULL){
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
    TreeNode* findNode(string Value) {
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
        TreeNode* newNode = new TreeNode(hValue);
        nodes.push_back(newNode);
    }
    // add a child 
    void addChild(string parent, string child) {
        string pHash = sha256(parent);
        string cHash = sha256(child);
        TreeNode* parentNode = findNode(pHash);
        if (parentNode != NULL) {
            TreeNode* childNode = new TreeNode(cHash);
            childNode->parent = parentNode;
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
        string Value = sha256(name);
        for (int i = 0; i < nodes.size(); i++) {
            if (nodes[i] -> hValue == Value) {
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
        TreeNode* p = findNode(hValue);
        if (p != NULL) {
            deleteRecursive(p);
        }

        cout << nodes.size();
    }
    void sibling(string person1,string person2){
        string hperson1 = sha256(person1);
        string hperson2 = sha256(person2);
        TreeNode* Node1 = findNode(hperson1);
        TreeNode* Node2 = findNode(hperson2);
        if (Node1 == NULL || Node2 == NULL) {
            cout << "not found"<< endl;  
        }
        if(Node1->parent == Node2->parent){
            cout <<"they are siblings" << endl;
        }
        else{
            cout << "they aren't siblings" <<endl;
        }
    }
    void Ancestor(string ancestor,string child) {
        bool check = false;
        string hancestor = sha256(ancestor);
        string hchild = sha256(child);
        TreeNode* ancestorNode = findNode(hancestor);
        TreeNode* childNode = findNode(hchild);
        if (ancestorNode == NULL || childNode == NULL) {
            cout << "not found" << endl; 
        }
        while (childNode != NULL) {
            if (childNode == ancestorNode) {
                check = true;
                cout << ancestor << " is the ancestor of " << "child"<< endl;
            }
            childNode = childNode -> parent; 
        }
        if(!check){
            cout << ancestor << " isn't the ancestor of " << child << endl;
        }
    }
};

int main(){
   Genealogy familyTree;

    familyTree.add("Grandparent");

    familyTree.addChild("Grandparent", "zahra");
    familyTree.addChild("Grandparent", "milad");
    familyTree.addChild("zahra", "Child1");
    familyTree.addChild("zahra", "yasy");
    familyTree.addChild("milad", "mina");
    familyTree.sibling("Child1","yasy");
    familyTree.Ancestor("Grandparent","yasy");
}