// Aluno: Hugo Folloni Guarilha
// DRE: 121085854

#include <iostream>
#include <algorithm>

using namespace std;

class Aresta {
    public: 
        int origem;
        int destino;
        int peso;
        Aresta();
        Aresta(int origem, int destino, int peso);
};

class ListaArestas {
    public:
        Aresta arestas[100];
        int tamanho;
        ListaArestas();
        void inserir(Aresta aresta);
        void printLista();
        void ordenar();
};

class Arvore {
    public:
        Aresta arestas[100];
        int tamanho;
        Arvore();
        void inserir(Aresta aresta);
        void printArvore();
        bool existeNaArvore(int valor);
        void inserirCondicionado(Aresta aresta);
};

Arvore::Arvore(){
    this->tamanho = 0;
};

void Arvore::inserir(Aresta aresta){
    this->arestas[this->tamanho] = aresta;
    this->tamanho++;
};

bool Arvore::existeNaArvore(int valor){
    for(int i = 0; i < this->tamanho; i++){
        if(this->arestas[i].origem == valor || this->arestas[i].destino == valor){
            return true;
        }
    }
    return false;
};

class Grafo {
    public:
        Arvore subarvores[100];
        int quantidadeArvores;
        Grafo();
        void inserirArvore(Arvore arvore);
        void getSubarvores(Aresta aresta);
        void printSubarvores();
        bool existeSubarvore(Arvore arvore);
        void unirSubarvores(ListaArestas lista);
        void removerArvore(int index);
};

Grafo:: Grafo(){
    this->quantidadeArvores = 0;
};

void Arvore:: printArvore(){
    for(int i = 0; i < this->tamanho; i++){
        cout<<this->arestas[i].origem<<"-"<<this->arestas[i].destino<<" ";
    }
    cout<<endl;
};

// AVISO: POR ALGUM MOTIVO ELE TA PRINTANDO O 0-2 NAS ARVORES SUBSEQUENTES, E A SEGUNDA ARVORE TA 0-0, SENDO A PRIMEIRA E A TERCEIRA AS CERTAS (SALVO A FALTA DO 0-2)
void Grafo:: printSubarvores(){
    for(int i = 0; i < this->quantidadeArvores; i++){
        cout<<"\n Subarvore "<<i + 1<<endl;
        this->subarvores[i].printArvore();
    }
    cout<<endl;
};

void Arvore:: inserirCondicionado(Aresta aresta){
    if(!this->existeNaArvore(aresta.destino) || !this->existeNaArvore(aresta.origem)){
        this->inserir(aresta);
    }
};

bool Grafo:: existeSubarvore(Arvore arvore){
    for(int i = 0; i < this->quantidadeArvores; i++){
        bool igual = true;
        int maxSize = max(arvore.tamanho, this->subarvores[i].tamanho);
        for(int j = 0; j < maxSize; j++){
            if(arvore.arestas[j].origem != this->subarvores[i].arestas[j].origem || arvore.arestas[j].destino != this->subarvores[i].arestas[j].destino){
                igual = false;
            }
        }
        if(igual){
            return true;
        }
    }
    return false;
};

void Grafo:: getSubarvores(Aresta aresta){
    bool algumVerticeExiste = false;
    bool existeV1 = false;
    bool existeV2 = false;
    int arvoreV1 = -1;
    int arvoreV2 = -1;
    for(int i = 0; i < this->quantidadeArvores; i++){
        for(int j = 0; j < this->subarvores[i].tamanho; j++){
                if(this->subarvores[i].arestas[j].origem == aresta.origem || this->subarvores[i].arestas[j].destino == aresta.origem){
                    algumVerticeExiste = true;
                    existeV1 = true;
                    arvoreV1 = i;
                }
                if(this->subarvores[i].arestas[j].origem == aresta.destino || this->subarvores[i].arestas[j].destino == aresta.destino){
                    algumVerticeExiste = true;
                    existeV2 = true;
                    arvoreV2 = i;

                            
            }
        }
    }
    if(existeV1 && !existeV2){
        this->subarvores[arvoreV1].inserirCondicionado(aresta);
    }
    if(!existeV1 && existeV2){
        this->subarvores[arvoreV2].inserirCondicionado(aresta);
    }
    if(!existeV1 && !existeV2){
        Arvore arvore;
        arvore.inserir(aresta);
        this->inserirArvore(arvore);
    }
};

void Grafo::inserirArvore(Arvore arvore){
    this->subarvores[this->quantidadeArvores] = arvore;
    this->quantidadeArvores++;
};

void Grafo:: removerArvore(int index){
    for(int i = index; i < this->quantidadeArvores - 1; i++){
        this->subarvores[i] = this->subarvores[i + 1];
    }
    this->quantidadeArvores--;
};

Aresta:: Aresta(){
    this->origem = 0;
    this->destino = 0;
    this->peso = 0;
};

Aresta:: Aresta(int origem, int destino, int peso){
    this->origem = origem;
    this->destino = destino;
    this->peso = peso;
};

ListaArestas:: ListaArestas(){
    this->tamanho = 0;
};

void ListaArestas:: inserir(Aresta aresta){
    this->arestas[this->tamanho] = aresta;
    this->tamanho++;
};

void ListaArestas:: printLista(){
    for(int i = 0; i < this->tamanho; i++){
        cout << "Aresta: " << this->arestas[i].origem << " " << this->arestas[i].destino << " " << this->arestas[i].peso << endl;
    }
};

void handleLine(string line, ListaArestas& listaArestas){
    string entrada = "";
    string saida = "";
    string peso = "";
    int i = 0;
    while(line[i] != '-'){
        entrada += line[i];
        i++;
    }
    i++;
    while(line[i] != ' '){
        saida += line[i];
        i++;
    }
    i++;
    while(i < line.size()){
        peso += line[i];
        i++;
    }
    int origem = stoi(entrada);
    int destino = stoi(saida);
    int pesoAresta = stoi(peso);
    Aresta aresta(origem, destino, pesoAresta);
    listaArestas.inserir(aresta);
};

void ListaArestas:: ordenar(){
    for(int i = 0; i < this->tamanho; i++){
        for(int j = 0; j < this->tamanho; j++){
            if(this->arestas[i].peso < this->arestas[j].peso){
                Aresta aux = this->arestas[i];
                this->arestas[i] = this->arestas[j];
                this->arestas[j] = aux;
            }
        }
    }
};

class ListaAuxiliar {
    public:
        int lista[100];
        int tamanho;
        ListaAuxiliar();
        void inserir(int valor);
        bool existe(int valor);
        void printListaAuxiliar();
};

ListaAuxiliar:: ListaAuxiliar(){
    this->tamanho = 0;
}

void ListaAuxiliar:: inserir(int valor){
    this->lista[this->tamanho] = valor;
    this->tamanho++;
}

bool ListaAuxiliar:: existe(int valor){
    for(int i = 0; i < this->tamanho; i++){
        if(this->lista[i] == valor){
            return true;
        }
    }
    return false;
}

void ListaAuxiliar:: printListaAuxiliar(){
    for(int i = 0; i < this->tamanho; i++){
        cout << this->lista[i] << " ";
    }
    cout << endl;
}


void Grafo:: unirSubarvores(ListaArestas lista){
    ListaAuxiliar listaAuxiliarVerticeUm;
    ListaAuxiliar listaAuxiliarVerticesResto;
    int pesoLigacao = 1000;
    int origem = 0;
    int destino = 0;
    int subarvore = 0;
    for(int i = 0; i < this->subarvores[0].tamanho; i++){
        if(!listaAuxiliarVerticeUm.existe(this->subarvores[0].arestas[i].origem)){
            listaAuxiliarVerticeUm.inserir(this->subarvores[0].arestas[i].origem);
        }
        if(!listaAuxiliarVerticeUm.existe(this->subarvores[0].arestas[i].destino)){
            listaAuxiliarVerticeUm.inserir(this->subarvores[0].arestas[i].destino);
        }
    }
    for(int i = 1; i < this->quantidadeArvores; i++){
        for(int j = 0; j < this->subarvores[i].tamanho; j++){
            if(listaAuxiliarVerticesResto.existe(this->subarvores[i].arestas[j].origem)){
                continue;
            }
            else{
                listaAuxiliarVerticesResto.inserir(this->subarvores[i].arestas[j].origem);
            }
            if(listaAuxiliarVerticesResto.existe(this->subarvores[i].arestas[j].destino)){
                continue;
            }
            else{
                listaAuxiliarVerticesResto.inserir(this->subarvores[i].arestas[j].destino);
            }
        }
    }


    for(int i = 0; i < listaAuxiliarVerticeUm.tamanho; i++){
        for(int j = 0; j < listaAuxiliarVerticesResto.tamanho; j++){
            for(int k = 0; k < lista.tamanho; k++){
                if(lista.arestas[k].origem == listaAuxiliarVerticeUm.lista[i] && lista.arestas[k].destino == listaAuxiliarVerticesResto.lista[j] || lista.arestas[k].origem == listaAuxiliarVerticesResto.lista[j] && lista.arestas[k].destino == listaAuxiliarVerticeUm.lista[i]){
                    if(lista.arestas[k].peso < pesoLigacao){
                        pesoLigacao = lista.arestas[k].peso;
                        origem = listaAuxiliarVerticeUm.lista[i];
                        destino = listaAuxiliarVerticesResto.lista[j];
                    }
                }
            }
        }
    }

    for(int i = 1; i < this->quantidadeArvores; i++){
        for(int j = 0; j < this->subarvores[i].tamanho; j++){
            if(this->subarvores[i].arestas[j].origem == destino || this->subarvores[i].arestas[j].destino == destino){
                subarvore = i;
            }
        }
    }

    Aresta aresta(origem, destino, pesoLigacao);
    this->subarvores[0].inserir(aresta);
    for(int i = 0; i < this->subarvores[subarvore].tamanho; i++){
        this->subarvores[0].inserir(this->subarvores[subarvore].arestas[i]);
    }
    this->removerArvore(subarvore);
};

int main() {
    ListaArestas listaArestas;
    Grafo grafo;

    bool existsLine = true;
    while(existsLine){
        string line = "";
        getline(cin, line);
        if(line == ""){
            existsLine = false;
        }
        else{
            handleLine(line, listaArestas);
        }
    }

    listaArestas.ordenar();

    listaArestas.printLista();

    Arvore miniarvore;
    miniarvore.inserir(listaArestas.arestas[0]);

    grafo.inserirArvore(miniarvore);

    for(int i = 0; i < listaArestas.tamanho; i++){
        grafo.getSubarvores(listaArestas.arestas[i]);
    }

    while(grafo.quantidadeArvores > 1){
        grafo.unirSubarvores(listaArestas);
    }

    grafo.subarvores[0].printArvore();

}

/* 
FUNCIONAMENTO: 
    - Recebe um grafo com as arestas e pesos, e a árvore mínima (usando union-find):

        3-5 0
        6-7 2 
        4-5 7 
        0-2 3 
        0-1 5 
        3-4 6 
        1-7 1
        0-7 4
        0-6 9 
        0-5 11
        4-7 8 
        4-6 9 

    Gabarito: 5 - 3 - 4 - 7 - (1, 6) 0 - 2 ou inverso

    - Ele ta pegando e achando as arestas mínimas e verificando se ela já tá na lista de arestas
*/