#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int* data;
    int size;
    int capacity;
} ResultArray;

static void pushBack(ResultArray* arr, int val){
    if(arr->size >= arr->capacity){
        arr->capacity = arr->capacity == 0 ? 4 : arr->capacity * 2;
        arr->data = (int*)realloc(arr->data, arr->capacity * sizeof(int));
    }
    arr->data[arr->size++] = val;
}

static int compare(const void* a, const void* b){
    return (*(int*)a - *(int*)b);
}

static ResultArray solve(char* expr, int start, int end){
    ResultArray res = {NULL, 0, 0};
    int hasOperator = 0;

    for(int i = start; i <= end; i++){
        if(expr[i] == '+' || expr[i] == '-' || expr[i] == '*'){
            hasOperator = 1;
            
            ResultArray leftRes = solve(expr, start, i - 1);
            ResultArray rightRes = solve(expr, i + 1, end);

            for(int l = 0; l < leftRes.size; l++){
                for(int r = 0; r < rightRes.size; r++){
                    int val = 0;
                    if(expr[i] == '+') val = leftRes.data[l] + rightRes.data[r];
                    else if(expr[i] == '-') val = leftRes.data[l] - rightRes.data[r];
                    else if(expr[i] == '*') val = leftRes.data[l] * rightRes.data[r];
                    
                    pushBack(&res, val);
                }
            }
            free(leftRes.data);
            free(rightRes.data);
        }
    }

    if(!hasOperator){
        int val = 0;
        for(int i = start; i <= end; i++){
            val = val * 10 + (expr[i] - '0');
        }
        pushBack(&res, val);
    }

    return res;
}

int main(){
    char expr[25];
    if(scanf("%s", expr) == 1){
        int len = strlen(expr);
        ResultArray ans = solve(expr, 0, len - 1);
        
        qsort(ans.data, ans.size, sizeof(int), compare);
        
        for(int i = 0; i < ans.size; i++){
            printf("%d%s", ans.data[i], (i == ans.size - 1) ? "" : " ");
        }
        printf("\n");
        
        free(ans.data);
    }
    return 0;
}
