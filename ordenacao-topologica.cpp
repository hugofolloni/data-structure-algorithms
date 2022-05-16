#include <iostream>

using namespace std;

class Grafo {
    private:
        int tamanho;    
        int vertices[10];
        int vizinhos[100];
    public:
        Grafo();
        int adicionarVertice(int item);
        void printGrafo();
};

Grafo:: Grafo(){
    tamanho = 10;
    for(int i = 0; i < tamanho; i++){
        vertices[i] = 0;
    }
    printGrafo();
};

void Grafo:: printGrafo() {
    int tamanhoGrafo = tamanho;
    for(int i = 0; i < tamanhoGrafo; i++){
        cout<<" vértice: "<<vertices[i];
    }
};


int main()
{
    cout<<"Hello World";

    Grafo grafo;
    
    grafo.printGrafo();
    return 0;
}
