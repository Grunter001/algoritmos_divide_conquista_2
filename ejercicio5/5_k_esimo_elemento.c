#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int* a, int* b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int* arr, int low, int high){
    int pivotIndex = low + rand() % (high - low + 1);
    swap(&arr[pivotIndex], &arr[high]);
    int pivot = arr[high];
    int i = low - 1;
    
    for(int j = low; j < high; j++){
        if(arr[j] <= pivot){
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

int quickSelect(int* arr, int low, int high, int kIndex){
    if(low == high){
        return arr[low];
    }
    
    int pi = partition(arr, low, high);
    
    if(kIndex == pi){
        return arr[pi];
    }else if(kIndex < pi){
        return quickSelect(arr, low, pi - 1, kIndex);
    }else{
        return quickSelect(arr, pi + 1, high, kIndex);
    }
}

int main(){
    int n, k;
    srand(time(NULL));
    
    if(scanf("%d %d", &n, &k) == 2){
        int* arr = (int*)malloc(n * sizeof(int));
        for(int i = 0; i < n; i++){
            scanf("%d", &arr[i]);
        }
        
        int kIndex = n - k;
        int result = quickSelect(arr, 0, n - 1, kIndex);
        
        printf("%d\n", result);
        free(arr);
    }
    return 0;
}
