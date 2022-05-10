#include <iostream>
#include <string.h>
using namespace std;

float operacao(float a, float b, char operador){
    switch(operador){
        case 43: 
            return a + b;
        case 45:
            return a - b;
        case 42:
            return a * b;
        case 47:
            return a / b;
    }
};

class Pilha{
    private:
        int topo;
        int capacidade;
        float pilha[80];
    public:
        Pilha();
        int isFull();
        int isEmpty();
        void adicionar(string item);
        void adicionar(char item);
        float retirar();
        float itemTopo();
        void runOperators(string expressao);
        void runNumbers(string expressao);
        void showPilha();
};

Pilha:: Pilha(){
    topo = -1;
    capacidade = 80;
};

int Pilha:: isFull(){
    if(topo == capacidade - 1){
        return 1;
    }
    return 0;

};

int Pilha:: isEmpty(){
    if(topo == -1){
        return 1;
    }
    return 0;
};

void Pilha:: adicionar(string item){
    if(isFull()){
        cout<<"Stack Overflow";
        return;
    }
    float itemToAdd = stof(item);
    topo++;
    pilha[topo] = itemToAdd;
};

void Pilha:: adicionar(char item){
    if(isFull()){
        cout<<"Stack Overflow";
        return;
    }
    topo++;
    pilha[topo] = item;
};

float Pilha:: retirar(){
    if(isEmpty() == 0){
        float item = pilha[topo];
        topo--;
        return item;
    }
    else{
        cout<<"Stack Underflow!";
    }
};

float Pilha:: itemTopo(){
    cout<<"\nO item no topo é: "<<pilha[topo];
    
};

void Pilha:: runNumbers(string expressao){

    int posicaoOperadores[60];

    int pos = 0;

    for(int i = 0; i < expressao.length() + 1; i++){
        if(expressao[i] == '*' || expressao[i] == '/' || expressao[i] == '+' || expressao[i] == '-' || expressao[i] == '(' || expressao[i] == ')'){
            posicaoOperadores[pos] = i;
            pos++;
        }
    }


    for(int i = 0; i < pos; i++){
        int posicao = posicaoOperadores[i];
    }

    int inicioNumero = 0;


    for(int i = 0; i <= pos; i++){
        int posicao = posicaoOperadores[i];
        string miniStr = " ";
        int tamanho = posicao - inicioNumero;
        if(tamanho > 0){
            miniStr = expressao.substr(inicioNumero, tamanho);
            adicionar(miniStr);

            inicioNumero = posicao + 1;
        }
    }

};

void Pilha:: runOperators(string expressao){
    for(int i = 0; i < expressao.length(); i++){
        if(expressao[i] == '*' || expressao[i] == '/' || expressao[i] == '+' || expressao[i] == '-' || expressao[i] == '(' || expressao[i] == ')'){
            adicionar(expressao[i]);
        }
    }
};

float calcular(Pilha numeros, Pilha operadores){
    float resultado = 0;
    float a = 0;
    float b = 0;
    int operador = 0;
    while(operadores.isEmpty() == 0){
        a = numeros.retirar();
        b = numeros.retirar();
        operador = operadores.retirar();
        resultado = operacao(a, b, operador);
        numeros.adicionar(resultado);
    }
    return resultado;
};
    

void Pilha:: showPilha(){
    cout<<"\nPilha: ";
    for(int i = 0; i <= topo; i++){
        cout<<pilha[i]<<" ";
    }
};

int main(){
    Pilha numeros;
    Pilha operadores;

    // string expressao;
    // cout<<"\nMe diga sua expressão:";
    // cin>>expressao;

    string expressao = "4 + 5 + 9 + 4 + 2 + 1 + 2";

    numeros.runNumbers(expressao);
    operadores.runOperators(expressao);

    cout<<"Resultado = "<<calcular(numeros, operadores);
};

// O algoritmo consegue calcular expressoes lineares de soma, somente. Falta colocar prioridades e '(', ')'.
