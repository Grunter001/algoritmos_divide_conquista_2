#include <stdio.h>
#include <stdlib.h>

long long mergeAndCount(int* arr, int* temp, int left, int mid, int right){
    int i = left;
    int j = mid;
    int k = left;
    long long invCount = 0;

    while((i <= mid - 1) && (j <= right)){
        if(arr[i] <= arr[j]){
            temp[k++] = arr[i++];
        }else{
            temp[k++] = arr[j++];
            invCount += (mid - i);
        }
    }

    while(i <= mid - 1){
        temp[k++] = arr[i++];
    }

    while(j <= right){
        temp[k++] = arr[j++];
    }

    for(i = left; i <= right; i++){
        arr[i] = temp[i];
    }

    return invCount;
}

long long mergeSortAndCount(int* arr, int* temp, int left, int right){
    long long invCount = 0;
    if(right > left){
        int mid = (right + left) / 2;
        invCount += mergeSortAndCount(arr, temp, left, mid);
        invCount += mergeSortAndCount(arr, temp, mid + 1, right);
        invCount += mergeAndCount(arr, temp, left, mid + 1, right);
    }
    return invCount;
}

int main(){
    int n;
    while(scanf("%d", &n) == 1 && n != 0){
        int* arr = (int*)malloc(n * sizeof(int));
        int* temp = (int*)malloc(n * sizeof(int));
        for(int i = 0; i < n; i++){
            scanf("%d", &arr[i]);
        }
        long long result = mergeSortAndCount(arr, temp, 0, n - 1);
        printf("%lld\n", result);
        free(arr);
        free(temp);
    }
    return 0;
}
