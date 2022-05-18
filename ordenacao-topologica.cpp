#include <iostream>

using namespace std;

class Grafo {
    private:
        int tamanho;    
        int populado;
        int vertices[100];
        int vizinhos[100];
    public:
        Grafo(int size);
        int adicionarVertice(int indice, string item);
        void printGrafo();
};

Grafo:: Grafo(int size){
    tamanho = size;
    for(int i = 0; i < tamanho; i++){
        vizinhos[i] = 0;
    }
    populado = 0;
};

void Grafo:: printGrafo() {
    int tamanhoGrafo = tamanho;
    for(int i = 0; i < tamanhoGrafo; i++){
        cout<<" \nvértice "<<i<<+ " aponta: "<<vizinhos[i];
    }
};

class Vetor {
    public:
        int array[100];
        int topo;
};

Vetor findChar(char c, string itens){
    Vetor vetor;
    for(int i = 0; i < 100; i++){
        vetor.array[i] = -1;
    }
    int arrayPos = 0;
    for(int i = 0; i < itens.length(); i++){
        if(itens[i] == ' '){
            vetor.array[arrayPos++] = i;
        }
    }
    vetor.topo = arrayPos;
    return vetor;
};

int Grafo:: adicionarVertice(int indice, string itens){
    Vetor vetor = findChar(' ', itens);
    for(int i = 0; i < vetor.topo; i++){
        cout<<" "<<vetor.array[i];
    }
    int inicioNumero = 0;
    int verticeAdicionado = 0;
    for(int i = 0; i < vetor.topo; i++){
        int posicao = vetor.array[i];
        string miniStr = " ";
        int tamanho = posicao - inicioNumero;
        if(tamanho > 1){
            miniStr = itens.substr(inicioNumero, tamanho);
            vizinhos[verticeAdicionado++] = stoi(miniStr);

            inicioNumero = posicao + 1;
        }
    }
    
}

int main()
{
    cout<<"Hello World";

    int size = 0;
    cout<<"Qual será o tamanho do grafo? ";
    cin>>size;
    
    Grafo grafo(size);
    
    for(int i = 0; i < size; i++){
        cout<<"\nMe fala os vizinhos do vértice "<<i<<": ";
        string meusVizinhos = " ";
        cin>>meusVizinhos;
        grafo.adicionarVertice(i, meusVizinhos);
    }
    
    grafo.printGrafo();
    return 0;
}

// Não funciona mas é um processo!!
