#include <iostream>
#include <string.h>
using namespace std;

float operacao(float a, float b, char operador){
    switch(operador){
        case 43: 
            return a + b;
        case 45:
            return b - a;
        case 42:
            return a * b;
        case 47:
            return b / a;
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
        float resolverPilha(Pilha numeros, Pilha operadores);
        float resolverPilhaLinear(Pilha numeros, Pilha operadores);
        Pilha inverterPilha();
        bool existeNaPilha(char item);
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

// float calcular(Pilha numeros, Pilha operadores){
//     float resultado = 0;
//     float a = 0;
//     float b = 0;
//     int operador = 0;
//     while(operadores.isEmpty() == 0){
//         a = numeros.retirar();
//         b = numeros.retirar();
//         operador = operadores.retirar();
//         resultado = operacao(a, b, operador);
//         numeros.adicionar(resultado);
//     }
//     return resultado;
// };
    

void Pilha:: showPilha(){
    for(int i = 0; i <= topo; i++){
        cout<<pilha[i]<<" ";
    }
};

float Pilha:: resolverPilha(Pilha numeros, Pilha operadores){

    Pilha pilhaAuxiliar;
    Pilha operatorAuxiliar;

    float resultado = 0;
    float a = 0;
    float b = 0;
    int operador = 0;
    while(operadores.isEmpty() == 0){ 
        cout<<"\n\nMinha pilha numeros esta"<<endl;
        numeros.showPilha();
        cout<<"\n\nMinha pilha operadores esta"<<endl;
        operadores.showPilha();
        cout<<"\n\nMinha pilha auxiliar esta"<<endl;
        pilhaAuxiliar.showPilha();
        cout<<"\n\nMinha pilha operator auxiliar esta"<<endl;
        operatorAuxiliar.showPilha();

        a = numeros.retirar();
        b = numeros.retirar();
        operador = operadores.retirar();
        if(operador == 42 || operador == 47){
            resultado = operacao(a, b, operador);
            pilhaAuxiliar.adicionar(resultado);
            operatorAuxiliar.adicionar(operadores.retirar());
        }
        else{
            pilhaAuxiliar.adicionar(a);
            pilhaAuxiliar.adicionar(b);
            operatorAuxiliar.adicionar(operador);
        }
    }

    bool existeMultiplicacao = operatorAuxiliar.existeNaPilha('*');
    bool existeDivisao = operatorAuxiliar.existeNaPilha('/');

    cout<<existeMultiplicacao<< " "<<existeDivisao<<endl;

    pilhaAuxiliar = pilhaAuxiliar.inverterPilha();
    operatorAuxiliar = operatorAuxiliar.inverterPilha();

    if(existeMultiplicacao || existeDivisao){
        resolverPilha(pilhaAuxiliar, operatorAuxiliar);
    }


    return numeros.resolverPilhaLinear(pilhaAuxiliar, operatorAuxiliar);
};

bool Pilha:: existeNaPilha(char item){
    for(int i = 0; i <= topo; i++){
        if(pilha[i] == item){
            return true;
        }
    }
    return false;
}

float Pilha:: resolverPilhaLinear(Pilha numeros, Pilha operadores){
    cout<<"Cheguei na pilha linear"<<endl;


    cout<<"\n\n\nAo final no loop temos na pilha de numeros: "<<endl;
    numeros.showPilha();
    cout<<"\nAo final no loop temos na pilha de operadores: "<<endl;
    operadores.showPilha();
  
    while(numeros.topo > 0){
        float a = numeros.retirar();
        float b = numeros.retirar();
        int operador = operadores.retirar();
        float resultado = operacao(a, b, operador);
        cout<<"\n\nResultado da operacao:"<<a<<" "<<b<<" "<<operador<<" e: "<<resultado<<endl;
        numeros.adicionar(resultado);
    }
    return numeros.retirar();
};

Pilha Pilha:: inverterPilha(){
    Pilha pilhaAuxiliar;
    while(isEmpty() == 0){
        pilhaAuxiliar.adicionar(retirar());
    }
    return pilhaAuxiliar;
}

// 42 = *
// 47 = /
// 43 = +
// 45 = -
// 40 = (
// 41 = )

int main(){
    Pilha numeros;
    Pilha operadores;

    // string expressao;
    // cout<<"\nMe diga sua expressão:";
    // cin>>expressao;

    string expressao = "4 * 2 + 3 * 2 - 4 / 2";

    numeros.runNumbers(expressao);
    operadores.runOperators(expressao);

    cout<<"Resultado = "<<numeros.resolverPilha(numeros, operadores);
};

// O algoritmo consegue calcular expressoes lineares de soma, somente. Falta colocar prioridades e '(', ')'.
