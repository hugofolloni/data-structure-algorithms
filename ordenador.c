// Aluno: Hugo Folloni Guarilha
// DRE: 121085854

// Merge Sort não está funcionando direito, enquanto os outros estão!

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int main ( int argc, char *argv[] ){
    // Criando o vetor a ser usado, pegando como parâmetro a terceira posição do argv
    int vetorSize = atoi(argv[2]);
    int *vetor = (int*) malloc(vetorSize * sizeof(int));
    printf("A quantidade de numeros para serem gerados no vetor: %d\n", vetorSize);
    printf("O vetor gerado foi: [ ");
    for(int i = 0; i < vetorSize; i++){
        vetor[i] = (rand() % 1000);
        printf("%d  ", vetor[i]);
    }
    printf("]\n");

    // Aplicando Bubble Sort, ou seja, algoritmo de O(n²).
    if(argc == 3){
        bubbleSort(vetor, vetorSize);
        printVetor(vetor, vetorSize, "bubble-sort");

    }

    else if( argc  == 4 ){
        // Caso seja escolhido -m, o algoritmo é o Merge Sort.
        if( strcmp(argv[3], "-m") == 0){
            mergeSort(vetor, 0, vetorSize - 1);
            printVetor(vetor, vetorSize, "merge-sort");
        }
        // Caso seja escolhido, o algoritmo é o Quick Sort.
        else if( strcmp(argv[3], "-q") == 0){
            quickSort(vetor, 0, vetorSize);
            printVetor(vetor, vetorSize, "quick-sort");
        }
        else{
            printf("\n Argumento invalido");
        }
    }
    else {
        printf("O numero de argumentos nao e valido");
    }
}

int mergeSort(int *vetor, int inicio, int fim){
    if(inicio > fim){
        return;
    }
    int meio = (inicio + fim) / 2;
    mergeSort(vetor, inicio, meio);
    mergeSort(vetor, meio + 1, fim);
    merge(vetor, inicio, meio, fim);
    
}

int merge(int *vetor, int inicio, int meio, int fim){
    int vetorTempSize = fim - inicio;
    int *vetorTemp = (int*) malloc(vetorTempSize * sizeof(int));
    int i = inicio;
    int j = meio;
    int pos = inicio;
    
    while(i <= meio && j <= fim){
        if(vetor[i] <= vetor[j]){
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
    while(j < fim){
        vetorTemp[pos] = vetor[j];
        j++;
        pos++;
    }
    for(int i = inicio; i < fim; i++){
        vetor[i] = vetorTemp[i];
    }   

    free(vetorTemp);
} 

int bubbleSort(int *vetor, int tamanho){
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
}

int quickSort(int *vetor, int inicio, int fim){
    if(fim - inicio > 1){
        int posPivot = particiona(vetor, inicio, fim);
        quickSort(vetor, inicio, posPivot);
        quickSort(vetor, posPivot + 1, fim);
    }
}

int particiona(int *vetor, int inicio, int fim){
    int p = randomNumber(inicio, fim - 1);
    troca(vetor, inicio, p);

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
            troca(vetor, i, j);
        }
    }
    vetor[inicio] = vetor[j];
    vetor[j] = pivot;
    return j;
}

int troca(int *vetor, int i, int j){
    int temp = vetor[i];
    vetor[i] = vetor[j];
    vetor[j] = temp;
}

int printVetor(int *vetor, int tamanho, char *ordenador){
    printf("\nO vetor ordenado por %s ficou assim:\n [ ",  ordenador);
    for(int i = 0; i < tamanho; i++){
        printf("%d  ", vetor[i]);
    }
    printf("]\n");
}

int randomNumber(int min, int max){
    return rand() % (max - min + 1) + min;
}