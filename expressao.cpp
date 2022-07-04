// Aluno: Hugo Folloni Guarilha
// DRE: 121085854

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
            return (float) a / b;
    }
    return 0;
};


bool existeNoVetor(char item, string vetor){
    for(int i = 0; i < vetor.length(); i++){
        if(vetor[i] == item){
            return true;
        }
    }
    return false;
}

class Pilha{
    private:
        int capacidade;
        float pilha[80];
    public:
        int topo;
        Pilha();
        int isFull();
        int isEmpty();
        void adicionar(float item);
        void adicionar(char item);
        float retirar();
        float itemTopo();
        void runOperators(string expressao);
        void runNumbers(string expressao);
        void showPilha();
        void showPilha(char modificador);
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

void Pilha:: adicionar(float item){
    if(isFull()){
        return;
    }
    topo++;
    pilha[topo] = item;
};

void Pilha:: adicionar(char item){
    if(isFull()){
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
        return 0;
    }
};

float Pilha:: itemTopo(){
    return pilha[topo];
};

void Pilha:: runNumbers(string expressao){

    int posicaoOperadores[60];

    int pos = 0;


    for(int i = 0; i < expressao.length() + 1; i++){
        if(expressao[i] == ')'){
            int fim = i, comeco = 0;
            while(expressao[fim] != '('){
                fim--;
            }
            comeco = fim;

            string miniExp = expressao.substr(comeco + 1, i - comeco - 1);      

            Pilha miniExpNumero;
            Pilha miniExpOperador;
            miniExpNumero.runNumbers(miniExp);
            miniExpOperador.runOperators(miniExp);

            float resultadoMiniPilha = miniExpNumero.resolverPilha(miniExpNumero, miniExpOperador);

            string resultadoMiniPilhaString = to_string(resultadoMiniPilha);

            expressao.replace(comeco, i - comeco + 1, resultadoMiniPilhaString);
  
            i += resultadoMiniPilhaString.length();

        }
    }

    for(int i = 0; i < expressao.length(); i++){
        if(expressao[i] == '*' || expressao[i] == '/' || expressao[i] == '+' || expressao[i] == '-'){
            posicaoOperadores[pos] = i;
            pos++;
        }
    }

    int inicioNumero = 0;

    if(existeNoVetor('(', expressao) == 1){
        return runNumbers(expressao);
    }

    for(int i = 0; i <= pos; i++){
        int posicao = posicaoOperadores[i];
        string miniStr = " ";
        int tamanho = posicao - inicioNumero;
        if(tamanho > 1){
            miniStr = expressao.substr(inicioNumero, tamanho);
            adicionar(stof(miniStr));

            inicioNumero = posicao + 1;
        }
    }

};

void Pilha:: runOperators(string expressao){
    for(int i = 0; i < expressao.length(); i++){
        if(expressao[i] == '('){
            int comeco = i, fim = i;
            while(expressao[fim] != ')'){
                fim++;
            }
            i = fim;
        }
        if(expressao[i] == '*' || expressao[i] == '/' || expressao[i] == '+' || expressao[i] == '-'){
            adicionar(expressao[i]);
        }
    }
};

void Pilha:: showPilha(){
    for(int i = 0; i <= topo; i++){
        cout<<pilha[i]<<" ";
    }
};

void Pilha:: showPilha(char modificador){
    for(int i = 0; i <= topo; i++){
        if(modificador == 'o'){
            cout<<(char) pilha[i]<<" ";
        }
    }
};

float Pilha:: resolverPilha(Pilha numeros, Pilha operadores){

    numeros = numeros.inverterPilha();
    operadores = operadores.inverterPilha();

    Pilha pilhaAuxiliar;
    Pilha operatorAuxiliar;

    float resultado = 0;
    float a = 0;
    float b = 0;
    int operador = 0;
    while(numeros.isEmpty() == 0){ 
        if(numeros.topo == 0){
            pilhaAuxiliar.adicionar(numeros.retirar());
            operatorAuxiliar.adicionar(operadores.retirar());
        }
        else{
            a = numeros.retirar();
            b = numeros.retirar();
            operador = operadores.retirar();
            if(operador == 0){
                operador = operadores.retirar();
            }
            if(operador == 42 || operador == 47){
                resultado = operacao(a, b, operador);
                pilhaAuxiliar.adicionar(resultado);
                operatorAuxiliar.adicionar(operadores.retirar());
            }
            else{
                pilhaAuxiliar.adicionar(a);
                if(numeros.topo == -1){
                    pilhaAuxiliar.adicionar(b);
                }
                else{
                    numeros.adicionar(b);
                }
                operatorAuxiliar.adicionar((char) operador);
            }
        }
    }

    pilhaAuxiliar = pilhaAuxiliar.inverterPilha();
    operatorAuxiliar = operatorAuxiliar.inverterPilha();

    if(operatorAuxiliar.existeNaPilha('*') == 1 || operatorAuxiliar.existeNaPilha('/') == 1){
        pilhaAuxiliar = pilhaAuxiliar.inverterPilha();
        operatorAuxiliar = operatorAuxiliar.inverterPilha();
        return numeros.resolverPilha(pilhaAuxiliar, operatorAuxiliar);
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
    while(numeros.topo > 0){
        float a = numeros.retirar();
        float b = numeros.retirar();
        int operador = operadores.retirar();
        float resultado = operacao(a, b, operador);
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

    char expressao[80];
    cout<<"\nMe diga sua expressão:\n  ";
    cin.getline(expressao, sizeof(expressao));

    numeros.runNumbers(expressao);
    operadores.runOperators(expressao);

    cout<<"Resultado = "<<numeros.resolverPilha(numeros, operadores);
};

