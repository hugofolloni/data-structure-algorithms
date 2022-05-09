#include <stdio.h>
#include <stdlib.h>

float operacao(float a, float b, char operador){
    switch(operador){
        case '+': 
            return a + b;
        case '-':
            return a - b;
        case '*':
            return a * b;
        case '/':
            return a / b;
    }
}

struct Pilha {
	int topo;
	int fim;
	float *pElem;
};

void criar( struct Pilha *p, int c ){

    p->pElem = (float*) malloc (c * sizeof(float));
    p->topo = -1;
    p->fim = c;
    
    printf("Consegue criar a pilha!");

}

int isFull(struct Pilha *p){
    if(p->topo == p->fim - 1){
        return 1;
    }
    else{
        return 0;
    }
}

int isEmpty(struct Pilha *p){
    if(p->topo == -1){
        return 1;
    }
    else{
        return 0;
    }
}

int adicionar(struct Pilha *p, float item){
    if(isFull(p) == 0){
        p->topo++;
        p->pElem[p->topo] = item;
        return 1;
        printf("Adicionei item %f\n", item);
    }
    else{
        return 0;
        printf("Não pude adicionar pois estava cheio!");
    }
}

int retirar(struct Pilha *p){
    if(isEmpty(p) == 0){
        float item = p->topo;
        p->topo--;
        return item;
    }
    else{
        return 0;
    }
}

float itemTopo(struct Pilha *p){
    return  p->topo;
}

int operar(){
    float a = 20.0, b = 15.0;

    printf("%f\n", operacao(a, b, '+'));
    printf("%f\n", operacao(a, b, '-'));
    printf("%f\n", operacao(a, b, '*'));
    printf("%f\n", operacao(a, b, '/'));
}

int runExpression(char* expressao, struct Pilha *pilhaNumeros, struct Pilha *pilhaOperadores){

    char *miniStr = "";
    
    printf("Cheguei!");

    for(int i = 0; i < 80; i++){
        printf("To aqui");
        char c = expressao[i];
        if((c != '*') && (c != '+') && (c != '-') && (c != '/') && (c != ' ')){
            adicionar(pilhaNumeros, c);
        }
        else if(c != '\n'){
            adicionar(pilhaOperadores, c);
        }
    }
    
        printf("Sai!");


    printf("%s", pilhaOperadores);
    printf("%s", pilhaNumeros);

}

int main(){
    
    struct Pilha *numeros, *operadores;

    criar(&numeros, 5);
    criar(&operadores, 5);

    char expressao[80]= " ";

    printf("Me diga sua expressão:\n ");
    // sscanf(str, "%s", &expressao, 80); // Saber como usar!!!
    // scanf("%s", &expressao);


    gets(expressao);

    runExpression(expressao, numeros, operadores);
}




// O algoritmo não consegue chegar na função runExoression -> nunca é printado o chegeuei!
