#include <iostream>
#include <algorithm>

using namespace std;


class Node {
    public:
        int data;
        Node *left;
        Node *rigth;
        Node();
        Node(int data);
};


Node:: Node(){
    data = -1;
    left = NULL;
    rigth = NULL;
}

Node:: Node(int data){
    this->data = data;
    left = NULL;
    rigth = NULL;
}

class Tree {
    public:
        Node root;
        Node nodes[100];
        int size;
        Tree();
        Tree(int root);
        void add(int data);
        void print();
        void findPlace(int data);
        Node findNode(int data);
};

Tree:: Tree(){
    root.data = -1;
    root.left = NULL;
    root.rigth = NULL;
    size = 0;
}

Tree:: Tree(int root){
    this->root.data = root;
    this->root.left = NULL;
    this->root.rigth = NULL;
    size = 0;
}

Node Tree:: findNode(int data){
    Node current = root;
    while(current.data != data){
        if(data < current.data){
            if(current.left == NULL){
                return current;
            }
            current = *current.left;
        }
        else{
            if(current.rigth == NULL){
                return current;
            }
            current = *current.rigth;
        }
    }
    cout<<"current.data: "<<current.data<<endl;
    return current;
}


void Tree:: add(int data){
    Node spot = findNode(data);
    if(spot.data == data){
        cout << "Node already exists" << endl;
        return;
    }
    if(data < spot.data){
        Node newNode(data);
        spot.left = &newNode;
        this->nodes[size] = newNode;
        size++;
        cout<<spot.left->data << " foi adicionado a esquerda de "<<spot.data<<endl;
    }
    else{
        Node newNode(data);
        spot.rigth = &newNode;
        this->nodes[size] = newNode;
        size++;
        cout<<spot.rigth->data << " foi adicionado a direita de "<<spot.data<<endl;
    }
}

void Tree:: print(){
    for(int i = 0; i < size; i++){
        cout << nodes[i].left << " <"  << nodes[i].data << " > " << nodes[i].rigth << endl;
    }
}

int main(){
    Tree tree(7);
    
    tree.add(4);
    tree.add(13);
    tree.add(1);
    tree.add(5);
    tree.add(9);
    tree.add(16);

    tree.print();

    return 0;
}