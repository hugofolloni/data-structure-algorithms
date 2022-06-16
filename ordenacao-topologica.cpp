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

class grausDeEntrada {
    public: 
        int tamanho;
        grausDeEntrada();
        int graus[100];
        void printGraus();
};

grausDeEntrada:: grausDeEntrada(){
    this->tamanho = 0;
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
        void findGraus(grausDeEntrada& g);
        void reduzirGrau(grausDeEntrada& g);
        bool isAllZero(grausDeEntrada g);
        int listaOrdenada[100];
        void adicionarNaListaOrdenada(int valor);
        int tamanhoListaOrdenada;
        void printListaOrdenada();
};

void Grafo:: printListaOrdenada(){
    cout<<"O grafo ordenado ficou: ";
    for(int i = 0; i < this->tamanhoListaOrdenada; i++){
        cout << this->listaOrdenada[i] << " ";
    }
    cout << endl;
}

void Grafo:: adicionarNaListaOrdenada(int valor){
    listaOrdenada[tamanhoListaOrdenada] = valor;
    tamanhoListaOrdenada++;
};


void Grafo:: findGraus(grausDeEntrada& g){
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
        g.graus[i] = grau;
        g.tamanho++;
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
    this->tamanhoListaOrdenada = 0;
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

bool Grafo:: isAllZero(grausDeEntrada g){
    bool notZero = true;
    for(int i = 0; i < tamanhoListaRelacoes; i++){
        if(g.graus[i] > 0){
            notZero = false;
        }
    }
    return notZero;
};

void grausDeEntrada:: printGraus(){
    for(int i = 0; i < tamanho; i++){
        cout<<"Grau de entrada do vertice "<<i + 1<<": "<<graus[i]<<endl;
    }
    cout<<endl;
};

void Grafo:: reduzirGrau(grausDeEntrada& g){
    for(int i = 0; i < tamanhoListaRelacoes; i++){
        int grauVerticeAnalisado = g.graus[i];
        if(grauVerticeAnalisado == 0){
            g.graus[i] = -1;
            adicionarNaListaOrdenada(i + 1);
            for(int j = 0; j < listaRelacoes[i].tamanho; j++){
                int vertice = listaRelacoes[i].lista[j];
                g.graus[vertice - 1]--;
            }
        }
    }
};


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

    grausDeEntrada graus;
    
    
    grafo.parse(lines);
    grafo.findGraus(graus);;
    
    while(!grafo.isAllZero(graus)){
        grafo.reduzirGrau(graus);
    }

    grafo.printListaOrdenada();
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
