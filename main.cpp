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
        auto removeCondition = [node](TreeNode* otherNode) {
        return node == otherNode;
    };
    nodes.erase(std::remove_if(nodes.begin(), nodes.end(), removeCondition), nodes.end());
    delete node;
    // Reduce memory usage
    nodes.shrink_to_fit();
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
            cout <<"they are siblings" << endl;
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
    bool cousin(string person1,string person2){
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
                    cout <<  Node1 -> hValue;
                }
                temp = temp->parent;
            }
            Node1 = Node1->parent;
        }
        if(!check){
            cout << "no common ancestor" << endl;
        }
    }
    //E
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

    familyTree.add("Grandparent");

    familyTree.addChild("Grandparent", "zahra");
    familyTree.addChild("Grandparent", "milad");
    familyTree.addChild("zahra", "Child1");
    familyTree.addChild("zahra", "yasy");
    familyTree.addChild("milad", "mina");
    familyTree.addChild("milad", "mina");
  // pair<string, string> distantRelatives = familyTree.findMostDistantRelatives();
    familyTree.Delete("yasy");
    familyTree.Size();
    //cout << "Most Distant Relatives: " << distantRelatives.first << " and " << distantRelatives.second << endl;
}
/*

        grand
    zahra    milad
Child  yasy    mina


*/