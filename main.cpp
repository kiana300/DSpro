#include "hash.cpp"
#include <iostream>
#include <cmath>
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
    void deleteRecursive(TreeNode* node) {
        if (node->leftChild != nullptr) {
            deleteRecursive(node->leftChild);
        }
        if (node->rightChild != nullptr) {
            deleteRecursive(node->rightChild);
        }
        auto it = find(nodes.begin(), nodes.end(),node);
        if (it != nodes.end()) {
            nodes.erase(it);
        }
    }
    int maxDepth(TreeNode* root) {
        if (root == nullptr) {
            return 0;
        }
        int leftDepth = maxDepth(root->leftChild);
        int rightDepth = maxDepth(root->rightChild);
        return max(leftDepth, rightDepth) + 1;
    }
    int findDistance(TreeNode* Node1, TreeNode* Node2) {
        if (Node1 == NULL || Node1 == NULL) {
            return -1; 
        }
        TreeNode* commonAncestor = findCommonAncestor(Node1, Node2);
        int distance1 = calculateDistance(commonAncestor, Node1);
        int distance2 = calculateDistance(commonAncestor, Node2);
        return distance1 + distance2;
    }
    TreeNode* findCommonAncestor(TreeNode* Node1, TreeNode* Node2){
        while (Node1 != NULL) {
            TreeNode* temp = Node2;
            while (temp != NULL) {
                if (Node1 == temp) {
                    return Node1;
                }
                temp = temp->parent;
            }
            Node1 = Node1->parent;
        }
        return NULL; 
    }
    int calculateDistance(TreeNode* parent, TreeNode* child) {
        int distance = 0;
        while (child != parent) {
            child = child->parent;
            distance ++;
        }
        return distance;
    } 
    TreeNode* findNode(string Value) {
        for (int i = 0; i < nodes.size(); i++) {
            if (nodes[i]->hValue == Value) {
                return nodes[i];
            }
        }
        return NULL; 
    }
public:
    Genealogy(){}
    // add a root
    void add(string name) {
        string hValue = sha256(name);
        TreeNode* newNode = new TreeNode(hValue);
        nodes.push_back(newNode);
    }
    // add a child 
    void addChild(string parent, string child) {
        TreeNode* parentNode = findNode(sha256(parent));
        if (parentNode != NULL) {
            TreeNode* childNode = new TreeNode(sha256(child));
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
        cout << nodes.size() << endl;
    }
    // find Node
    void Find(string name){
        bool found = false;
        string Value = sha256(name);
        for (int i = 0; i < nodes.size(); i++) {
            if (nodes[i] -> hValue == Value) {
                cout << "yes" << endl;
                found = true;
                break;
            }
        }
        if(!found){
            cout << "not found" << endl;
        }
    }
    //Delete Node
    void Delete(string name){
        TreeNode* p = findNode(sha256(name));
        if (p != NULL) {
            deleteRecursive(p);
        }
    }
    //B
    bool sibling(string person1,string person2){
        TreeNode* Node1 = findNode(sha256(person1));
        TreeNode* Node2 = findNode(sha256(person2));
        if (Node1 == NULL || Node2 == NULL) {
            return false;  
        }
        if(Node1->parent == Node2->parent){
            return true;
        }
        return false;
    }
    //A
    bool Ancestor(string ancestor,string child) {
        TreeNode* ancestorNode = findNode(sha256(ancestor));
        TreeNode* childNode = findNode(sha256(child));
        if (ancestorNode == NULL || childNode == NULL) {
            return false;
        }
        while (childNode != NULL) {
            if (childNode == ancestorNode) {
                return true;
            }
            childNode = childNode -> parent; 
        }
        return false;
    }
    //C
    bool distantfamily(string person1,string person2){
        TreeNode* Node1 = findNode(sha256(person1));
        TreeNode* Node2 = findNode(sha256(person2));
        if (Node1 == NULL || Node2 == NULL) {
            return false;  
        }
        if (Ancestor(person1, person2) || Ancestor(person2, person1) || sibling(person1,person2)) {
            return false; 
        }
        vector<string> a, b;
        while (Node1 != NULL) {
            a.push_back(Node1->hValue);
            Node1 = Node1->parent;
        }
        while (Node2 != NULL) {
            b.push_back(Node2->hValue);
            Node2 = Node2->parent;
        }
        for (int i = 0;i < a.size();i++) {
            for (int j = 0;j < b.size();j++) {
                if (a[i] == b[j]) {
                    return true; 
                }
            }
        }
        return false; 
    }
    //D
    void commonAncestor(string person1,string person2){
        bool check = false;
        TreeNode* Node1 = findNode(sha256(person1));
        TreeNode* Node2 = findNode(sha256(person2));
        if (Node1 == NULL || Node2 == NULL) {
            cout << "not found"<< endl;  
        }
        while (Node1 != nullptr) {
            TreeNode* temp = Node2;
            while (temp != NULL) {
                if (Node1 == temp) {
                    cout <<  Node1 -> hValue << endl;
                    check = true;
                }
                temp = temp->parent;
            }
            Node1 = Node1->parent;
        }
        if(!check){
            cout << "no common ancestor" << endl;
        }
    }
    //F
    int findFarthestChild(string name) {
        TreeNode* node = findNode(sha256(name));
        if (node == NULL) {
            return -1; 
        }
        return maxDepth(node) - 1;
    }
    //E
    pair<string,string> findMostDistantRelatives() {
        pair<string,string> result;
        int maxDistance = 0;
        for (int i = 0; i < nodes.size(); i++){
            for (int j = i + 1; j < nodes.size(); j++) {
                int distance = findDistance(nodes[i], nodes[j]);
                if (distance > maxDistance) {
                    maxDistance = distance;
                    result = make_pair(nodes[i]->hValue, nodes[j]->hValue);
                }
            }
        }
        return result;
    }
};

int main(){
    Genealogy familyTree;
    int input;

    cout << "enter 1 for add a root" << endl;
    cout << "enter 2 for add a child" << endl;
    cout << "enter 3 for find a node" << endl;
    cout << "enter 4 for check size of family tree" << endl;
    cout << "enter 5 for delete a node" << endl;
    cout << "enter 6 for check two nodes are ancestors or not" << endl;
    cout << "enter 7 for check two nodes are siblings or not" << endl;
    cout << "enter 8 for check two nodes are distant family or not" << endl;
    cout << "enter 9 for find a common ancestor" << endl;
    cout << "enter 10 for find a farthest child" << endl;
    cout << "enter 11 for find most distant relatives" << endl;
    cout << "enter -1 for exit" << endl;

   cin >> input; 
    while(input != -1){
        if(input == 1){
            cout <<"name of root" << endl;
            string name;
            cin >> name;
            familyTree.add(name);
        }
        else if(input == 2){
            cout << "name of parent " << endl;
            string name , name1;
            cin >> name ;
            cout << "name of child" << endl;
            cin >> name1;
            familyTree.addChild(name , name1);
        }
        else if(input == 3){
            cout << "name " << endl;
            string name;
            cin >> name;
            familyTree.Find(name);
        }
        else if(input == 4){
            familyTree.Size();
        }
        else if(input == 5){
            cout << "name " << endl;
            string name;
            cin >> name;
            familyTree.Delete(name);
        }
        else if(input == 6){
            cout << "name1 and name2 with space" << endl;
            string name , name1;
            cin >> name >> name1;
            if(familyTree.Ancestor(name,name1)){
                cout << "they are ancestors" << endl;
            }
            else{
                cout << "they aren't ancestors" << endl;
            }
        }
        else if(input == 7){
            cout << "name1 and name2 with space" << endl;
            string name , name1;
            cin >> name >> name1;
            if(familyTree.sibling(name,name1)){
                cout << "they are siblings" << endl;
            }
            else{
                cout << "they aren't siblings" << endl;
            }
        }
        else if(input == 8){
            cout << "name1 and name2 with space" << endl;
            string name , name1;
            cin >> name >> name1;
            if(familyTree.distantfamily(name,name1)){
                cout << "they are distant family" << endl;
            }
            else{
                cout << "they aren't distant family" << endl;
            }
        }
        else if(input == 9){
            cout << "name1 and name2 with space" << endl;
            string name , name1;
            cin >> name >> name1;
            familyTree.commonAncestor(name,name1);
        }
        else if(input == 10){
            cout << "name" << endl;
            string name ;
            cin >> name ;
            cout << familyTree.findFarthestChild(name);
            cout << endl;
        }
        else if(input == 11){
            pair<string, string> distantRelatives = familyTree.findMostDistantRelatives();
            cout << "Most Distant Relatives: " << distantRelatives.first << " and " << distantRelatives.second << endl;
        }
        cin >> input;
    }
}
    

    
  
/*

         Grandparent
    Ava          Danial
 Arta  Sara   Olya


*/