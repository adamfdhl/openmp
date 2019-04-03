#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void printArr(int* data,int n){
    for (int i=0;i<n;i++){
        printf("%d ",data[i]);
    }
    printf("\n");
}

void countSort(int* data,int start,int n,int exp){
    int count[10] = {0};
    int tempCount[10] = {0};
    int i; 
    int *temp = malloc((n)*sizeof(int));
    
    for (i=0; i < n; i++){
        count[(data[start+i]/exp)%10] += 1;
        tempCount[(data[start+i]/exp)%10] +=1;
    }

    for (i=1; i<10; i++){
        count[i] += count[i-1];
        tempCount[i] += tempCount[i-1];
    }
    for (i=n-1;i>=0;i--){
        temp[count[(data[start+i]/exp)%10] - 1] = data[start+i]; 
        count[(data[start+i]/exp)%10] -=1;
    }
    for (i=0;i<n;i++){
        data[start+i] = temp[i];
    }
        if (tempCount[0]>1 && exp/10>=1){
                #pragma omp task
                countSort(data,start,tempCount[0],exp/10);
        }
        for (i=1;i<10;i++){
            if (tempCount[i]-tempCount[i-1]>1 && exp/10>=1){
                    #pragma omp task
                    countSort(data,start + tempCount[i-1],tempCount[i]-tempCount[i-1],exp/10);     
            }
        }
}

int getMax(int* data,int n){
    int max = data[0];
    for (int i=1;i<n;i++){
        if (data[i]>max){
            max = data[i];
        }
    }
    return max;
}

int getExpMax(int *data, int n) {
    int max = getMax(data,n);
    int expMax = 1;
    while(max/expMax>=10){
        expMax *= 10; 
    }
    return expMax;
}

void radixSort(int* data,int n){
    // int max = getMax(data, n);
    int expMax = getExpMax(data, n);
    // printf("%d\n",max);
    // printf("expMax = %d\n",expMax);
    #pragma omp parallel
    #pragma omp single
    countSort(data,0,n,expMax);
}


void rng(int* arr, int n) {
    int seed = 13516054; // Ganti dengan NIM anda sebagai seed.
    srand(seed);
    for(long i = 0; i < n; i++) {
        arr[i] = (int)rand();
    }
}

int main(int argc, char *argv[]){
    int n = strtol(argv[1], NULL, 10);
    int* data;
    data = malloc(n *sizeof(int));
    // for (int i=0;i<n;i++){
    //     data[i] = 100-i;
    // }
    rng(data,n);
    printf("ARRAY BEFORE SORT\n");
    printArr(data,n);
    double start_time = omp_get_wtime();
    radixSort(data,n);
    double time_exec = omp_get_wtime() - start_time;
    printf("ARRAY AFTER SORT\n");
    printArr(data,n);
    printf("Time execution: %f\n", time_exec);
    return 0;
}