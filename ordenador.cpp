// Aluno: Hugo Folloni Guarilha
// DRE: 121085854

#include <iostream>
#include <string.h>
#include <chrono>
using namespace std;
using namespace std::chrono;

class Vetor {
    private:
        int inicio;
        int fim;
        int vetor[10000];
    public:
        Vetor();
        int adicionar(int item);
        int mergeSort(int inicio, int fim);
        int merge(int inicio, int meio, int fim);
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
    for(int i = 0; i < 10000; i++){
        vetor[i] = 0;
    }
};

int Vetor:: adicionar(int item){
    vetor[fim] = item;
    fim++;

    return item;
};

int Vetor:: mergeSort(int inicio, int fim){
    int meio = 0;
    if(inicio < fim){
        int meio = (inicio + fim) / 2;
        mergeSort(inicio, meio);
        mergeSort(meio + 1, fim);
        merge(inicio, meio, fim);
    }
    return 0;
};

int Vetor:: merge(int inicio, int meio, int fim){
    int vetorTempSize = fim - inicio + 5;
    int vetorTemp[vetorTempSize];	
    int i = inicio;
    int j = meio + 1;
    int pos = 0;

    while(i <= meio && j <= fim){
        if(vetor[i] < vetor[j]){
            vetorTemp[pos] = vetor[i];
            i++;
        }else{
            vetorTemp[pos] = vetor[j];
            j++;
        }
        pos++;
    }
    while (i <= meio){
        vetorTemp[pos] = vetor[i];
        i++;
        pos++;
    }
    while (j <= fim){
        vetorTemp[pos] = vetor[j];
        j++;
        pos++;
    }
    for(int k = 0; k < pos; k++){
        vetor[inicio + k] = vetorTemp[k];
    }
    return 0;
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

int findChar (int argc, char *argv[], string c_){
    int i = 0;
    while(i < argc){
        if(string(argv[i]) == c_){
            return i;
        }
        i++;
    }
    return NULL;
}

int main ( int argc, char *argv[] ){
    Vetor vetor;
    string ordenador = "";
    

    int vetorSize = atoi(argv[findChar(argc, argv, "-n") + 1]);
    

    string choose = "-b";
    if(findChar(argc, argv, "-m") != NULL){
        choose = "-m";
    }
    else if(findChar(argc, argv, "-q") != NULL){
        choose = "-q";
    }


    cout<<"A quantidade de numeros para serem gerados no vetor: "<<vetorSize<<endl;
    cout<<"O vetor gerado foi: [ ";
    int i = 0;
    for(i; i < vetorSize; i++){
        cout<<vetor.adicionar(rand() % 10000)<<" ";
    }
    cout << "]" << endl;

    // Aplicando Bubble Sort, ou seja, algoritmo de O(n²).
    if(choose == "-b"){
        auto start = high_resolution_clock::now();
       
        vetor.bubbleSort(vetorSize);
        
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);

        vetor.printVetor("bubble-sort");
        cout << "O tempo de execucao foi: " << duration.count() << " microsegundos." << endl;
    }
    // Caso seja escolhido -m, o algoritmo é o Merge Sort.
    else if(choose == "-m"){
        auto start = high_resolution_clock::now();

        vetor.mergeSort(0, vetorSize -1);
        
        
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);

        vetor.printVetor("merge-sort");
        cout << "O tempo de execucao foi: " << duration.count() << " microsegundos." << endl;
    }
    // Caso seja escolhido, o algoritmo é o Quick Sort.
    else if( choose == "-q"){
        auto start = high_resolution_clock::now();

        vetor.quickSort(0, vetorSize);

        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);

        vetor.printVetor("quick-sort");
        cout << "O tempo de execucao foi: " << duration.count() << " microsegundos." << endl;
    }
    else{
        printf("\n Argumento invalido");
    }

};