#include <iostream>
#include <algorithm>

using namespace std;

bool isNumber(string s){
    return std::any_of(s.begin(), s.end(), ::isdigit);
}

class Lista {
    public:
        int lista[100];
        int tamanho;
        Lista();
        void inserir(int valor);
};

class StringArray {
    public:
        string strings[100];
        int tamanho;
        StringArray();
        void add(string c);
        void printArray();
        Lista parse(int i);
        Lista handleNumber(string line, int i);
};
class Grafo {
    public:
        int nVertices;
        int nArestas;
        Lista listaRelacoes[100];
        int tamanhoListaRelacoes;
        void inserirNaLista(Lista lista);
        Grafo();
        void parse(StringArray SA);
        void printRelacoes();
        void findGraus();
        int grausEntrada[];
        void reduzirGrau();
        bool isAllZero();
};

void Grafo:: findGraus(){
    for(int i = 0; i < tamanhoListaRelacoes; i++){
        int vertice = i + 1;
        int grau = 0;
        for(int k = 0; k < tamanhoListaRelacoes; k++){
            for(int j = 0; j < listaRelacoes[k].tamanho; j++){
                if(listaRelacoes[k].lista[j] == vertice){
                    grau++;
                }
            }
        }
        cout<<"Vertice "<<i + 1<<" tem grau "<<grau<<endl;
    }
};

Lista:: Lista(){
    tamanho = 0;
};

void Lista::inserir(int valor){
    lista[tamanho] = valor;
    tamanho++;
};

Grafo:: Grafo(){
    this->nArestas = 0;
    this->nVertices = 0;
    this->tamanhoListaRelacoes = 0;
};

StringArray:: StringArray(){
    this->tamanho = 0;
};

void StringArray:: add(string c){
    strings[tamanho] = c;
    tamanho++;
};

void Grafo:: inserirNaLista(Lista lista){
    this->listaRelacoes[tamanhoListaRelacoes] = lista;
    tamanhoListaRelacoes++;
};

void StringArray:: printArray(){
    for(int i = 0; i < tamanho; i++){
        cout<< i + 1<<": "<<strings[i]<<endl;
    }
    cout<<endl;
};

Lista StringArray:: handleNumber(string line, int i){
    Lista lista;
    int n = line.length();
    int j = 0;
    string substring = "";
    while(j < n){
        if(line[j] != ' '){
            substring += line[j];
        }
        else{
            int valor = stoi(substring);
            lista.inserir(valor);
            substring = "";
        }
        j++;
    }
    if(substring != "" && substring != " "){
        int valor = stoi(substring);
        lista.inserir(valor);
    } 
    return lista;
};

Lista StringArray:: parse(int i){
    Lista lista;
    string line = strings[i];
    if(isNumber(line)){
        lista = handleNumber(line, i);
    }
    return lista;
};

void Grafo:: parse(StringArray SA){
    for(int i = 0; i < SA.tamanho; i++){
        Lista lista = SA.parse(i);
        this->inserirNaLista(lista);
    }
};

void Grafo:: printRelacoes(){
    for(int i = 0; i < this->tamanhoListaRelacoes; i++){
        cout<<"\n Aresta "<<i + 1<<endl;
        for(int j = 0; j < this->listaRelacoes[i].tamanho; j++){
            cout<<this->listaRelacoes[i].lista[j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
};

bool Grafo:: isAllZero(){
    for(int i = 0; i < nVertices; i++){
        if(grausEntrada[i] != 0){
            return false;
        }
    }
    return true;
}

void Grafo:: reduzirGrau(){
    for(int i = 0; i < nVertices; i++){
        int grauVerticeAnalisado = grausEntrada[i];
        if(grauVerticeAnalisado == 0){
            grausEntrada[i] == -1;
            for(int j = 0; j < listaRelacoes[i].tamanho; j++){
                int verticeAMudar = listaRelacoes[i].lista[j];
                grausEntrada[verticeAMudar] -= 1;
                cout<<"Reduzi o grau de entrada de "<<verticeAMudar<<endl;
            }
        }
    }
}


int main() {
    Grafo grafo;

    string firstLine = "";
    getline(cin, firstLine);
    
    StringArray lines;

    char nVerticesS = firstLine[0];
    int nVertices = nVerticesS - '0';

    for(int i = 0; i < nVertices; i++){
        string line = "";
        getline(cin, line);
        lines.add(line);
    }

    
    cout<<"\n Número de Vértices e Número de Arestas\n"<<firstLine<<endl;
    
    grafo.parse(lines);

    cout<<"\n\n Para quem cada aresta aponta: \n";
    grafo.printRelacoes();
    
    grafo.findGraus();
    
    while(!grafo.isAllZero()){
        grafo.reduzirGrau();
    }
    
    grafo.findGraus();
}

// O aplicativo já lê as entradas e organiza uma tabela com cada entrada por aresta.
// Preciso organizar o código separando classes de métodos de construtores.

// Não está reduzindo grau...

/* 
Estou lendo as entradas com 3 grafos, em arquivos grafo1.txt, grafo2.txt e grafo3.txt, usando .\ordtop < grafo...txt
 - grafo3.txt: 
        "6 10
        2 3 4
        3
        \n
        2 3
        1 4
        3 4"
*/
