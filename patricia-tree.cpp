#include <iostream>
#include <algorithm>

using namespace std;

class Node {
    public: 
        int data;
        Node *left;
        Node *right;
        Node();
};

Node:: Node(){
    data = -1;
    left = NULL;
    right = NULL;
}

class Tree {
    public: 
        Node root;
        Node nodes[100];
        int size;
        Tree();
        void add(string data);
        void print();
};

Tree:: Tree(){
    root.data = -1;
    size = 0;
}

void Tree:: add(string data){
    Node *current = &root;
    for(int i = 0; i < data.size(); i++){
        if(data[i] == '0'){
            current = current->left;
            if(current == NULL){
                current = new Node();
                current->data = 0;
                current->left = NULL;
                current->right = NULL;
                this->nodes[size] = *current;
                size++;
                break;
            }
        }
        else if(data[i] == '1'){
            current = current->right;
            if(current == NULL){
                current = new Node();
                current->data = 1;
                current->left = NULL;
                current->right = NULL;
                this->nodes[size] = *current;
                size++;
                break;
            }
        }
    }           
}

void Tree:: print(){
    cout<< this->root.data <<endl;
    cout<< this->root.left->data <<endl;
    cout<< this->root.right->data <<endl;
    cout << endl;
}

int main(){
    Tree tree;
    tree.add("0101");
    tree.add("0110");
    tree.add("0111");
    tree.add("1000");

    tree.print();
}