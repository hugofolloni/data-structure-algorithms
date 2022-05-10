// Aluno: Hugo Folloni Guarilha
// DRE: 121085854

#include <iostream>
#include <string.h>
using namespace std;

class Vetor {
    private:
        int inicio;
        int fim;
        float vetor[80];
    public:
        Vetor();
        int adicionar(int item);
        void mergeSort(int iniio, int fim);
        void merge(int inicio, int meio, int fim);
        void bubbleSort(int tamanho);
        void quickSort(int inicio, int fim);
        int particiona(int inicio, int fim);
        void troca(int i, int j);
        void printVetor(string ordenador);
};

int randomNumber(int min, int max){
    return rand() % (max - min + 1) + min;
};

Vetor:: Vetor(){
    inicio = 0;
    fim = 0;
};

int Vetor:: adicionar(int item){
    vetor[fim] = item;
    fim++;

    return item;
};

void Vetor:: mergeSort(int inicio, int fim){
    if(inicio < fim){
        int meio = (inicio + fim) / 2;
        mergeSort(inicio, meio);
        mergeSort(meio + 1, fim);
        merge(inicio, meio, fim);
    }
};

void Vetor:: merge(int inicio, int meio, int fim){
    int vetorTempSize = fim - inicio;
    int vetorTemp[vetorTempSize];	
    int i = inicio;
    int j = meio + 1;
    int pos = inicio;

    while(i <= meio && j <= fim){
        if(vetor[i] < vetor[j]){
            vetorTemp[pos] = vetor[i];
            i++;
        }
        else{
            vetorTemp[pos] = vetor[j];
            j++;
        }
        pos++;
    }
    while(i <= meio){
        vetorTemp[pos] = vetor[i];
        i++;
        pos++;
    }
    while(j <= fim){
        vetorTemp[pos] = vetor[j];
        j++;
        pos++;
    }
    for(int i = inicio; i <= fim; i++){
        vetor[i] = vetorTemp[i];
    };
};

void Vetor:: bubbleSort(int tamanho){
    int i = 0;
    bool trocou = true;
    while((i < tamanho) && trocou){
        trocou = false;
        for(int j = 0; j < tamanho - i - 1; j++){
            if(vetor[j] > vetor[j + 1]){
                int temp = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = temp;
                trocou = true;
            }
        }
        i++;
    }
};

void Vetor:: quickSort(int inicio, int fim){
    if(fim - inicio > 1){
        int posPivot = particiona(inicio, fim);
        quickSort(inicio, posPivot);
        quickSort(posPivot + 1, fim);
    }
};

int Vetor:: particiona(int inicio, int fim){
    int p = randomNumber(inicio, fim - 1);
    troca(inicio, p);

    int pivot = vetor[inicio];
    int i = inicio;
    int j = fim - 1;
    while(i < j){
        while(i < fim && vetor[i] <= pivot){
            i++;
        }
        while(j > inicio && vetor[j] >= pivot){
            j--;
        }
        if(i < j){
            troca(i, j);
        }
    }
    vetor[inicio] = vetor[j];
    vetor[j] = pivot;
    return j;
};

void Vetor:: troca(int i, int j){
    int temp = vetor[i];
    vetor[i] = vetor[j];
    vetor[j] = temp;
};

void Vetor:: printVetor(string ordenador){
    cout<<"\nO vetor ordenado por "<<ordenador<<" ficou assim:\n [ ";
     for(int i = 0; i < fim; i++){
        cout<<vetor[i]<<" ";
    }
    printf("]\n");
};

int main ( int argc, char *argv[] ){
    Vetor vetor;
    string ordenador = "";

    int vetorSize = atoi(argv[2]);

    cout<<"A quantidade de numeros para serem gerados no vetor: "<<vetorSize<<endl;
    cout<<"O vetor gerado foi: [ ";
    for(int i = 0; i < vetorSize; i++){
        cout<<vetor.adicionar(rand() % 1000)<<" ";
    }
    cout << "]" << endl;

    // Aplicando Bubble Sort, ou seja, algoritmo de O(n²).
    if(argc == 3){
        vetor.bubbleSort(vetorSize);
        vetor.printVetor("bubble-sort");
    }
    else if( argc  == 4 ){
        // Caso seja escolhido -m, o algoritmo é o Merge Sort.
        if( strcmp(argv[3], "-m") == 0){
            vetor.mergeSort(0, vetorSize);
            vetor.printVetor("merge-sort");
        }
        // Caso seja escolhido, o algoritmo é o Quick Sort.
        else if( strcmp(argv[3], "-q") == 0){
            vetor.quickSort(0, vetorSize);
            vetor.printVetor("quick-sort");
        }
        else{
            printf("\n Argumento invalido");
        }
    }
    else {
        printf("O numero de argumentos nao e valido");
    }
};