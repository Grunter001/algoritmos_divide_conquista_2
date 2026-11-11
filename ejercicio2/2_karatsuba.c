#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void strReverse(char* str, int len){
    int i = 0, j = len - 1;
    while(i < j){
        char temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++;
        j--;
    }
}

void addStrings(char* num1, char* num2, char* result){
    int len1 = strlen(num1);
    int len2 = strlen(num2);
    int carry = 0, i = 0, j = 0, k = 0;
    
    while(i < len1 || j < len2 || carry){
        int sum = carry;
        if(i < len1) sum += num1[i++] - '0';
        if(j < len2) sum += num2[j++] - '0';
        result[k++] = (sum % 10) + '0';
        carry = sum / 10;
    }
    result[k] = '\0';
}

void subStrings(char* num1, char* num2, char* result){
    int len1 = strlen(num1);
    int len2 = strlen(num2);
    int borrow = 0, i = 0, j = 0, k = 0;
    
    while(i < len1){
        int diff = (num1[i++] - '0') - borrow;
        if(j < len2) diff -= (num2[j++] - '0');
        if(diff < 0){
            diff += 10;
            borrow = 1;
        }else{
            borrow = 0;
        }
        result[k++] = diff + '0';
    }
    while(k > 1 && result[k-1] == '0'){
        k--;
    }
    result[k] = '\0';
}

void multiplySchool(char* num1, char* num2, char* result){
    int len1 = strlen(num1);
    int len2 = strlen(num2);
    int* temp = (int*)calloc(len1 + len2, sizeof(int));
    
    for(int i = 0; i < len1; i++){
        for(int j = 0; j < len2; j++){
            temp[i + j] += (num1[i] - '0') * (num2[j] - '0');
        }
    }
    
    int carry = 0, k = 0;
    for(int i = 0; i < len1 + len2; i++){
        int sum = temp[i] + carry;
        result[k++] = (sum % 10) + '0';
        carry = sum / 10;
    }
    while(k > 1 && result[k-1] == '0'){
        k--;
    }
    result[k] = '\0';
    free(temp);
}

void karatsuba(char* num1, char* num2, char* result){
    int len1 = strlen(num1);
    int len2 = strlen(num2);
    int n = len1 > len2 ? len1 : len2;
    
    if(n <= 32){
        multiplySchool(num1, num2, result);
        return;
    }
    
    int m = (n / 2) + (n % 2);
    
    char* low1 = (char*)malloc(m + 1);
    char* high1 = (char*)malloc(n + 1);
    char* low2 = (char*)malloc(m + 1);
    char* high2 = (char*)malloc(n + 1);
    
    memset(low1, 0, m + 1);
    memset(high1, 0, n + 1);
    memset(low2, 0, m + 1);
    memset(high2, 0, n + 1);
    
    for(int i = 0; i < len1; i++){
        if(i < m) low1[i] = num1[i];
        else high1[i - m] = num1[i];
    }
    if(strlen(low1) == 0) strcpy(low1, "0");
    if(strlen(high1) == 0) strcpy(high1, "0");
    
    for(int i = 0; i < len2; i++){
        if(i < m) low2[i] = num2[i];
        else high2[i - m] = num2[i];
    }
    if(strlen(low2) == 0) strcpy(low2, "0");
    if(strlen(high2) == 0) strcpy(high2, "0");
    
    char* z0 = (char*)malloc(2 * n + 2);
    char* z1 = (char*)malloc(2 * n + 2);
    char* z2 = (char*)malloc(2 * n + 2);
    
    karatsuba(low1, low2, z0);
    karatsuba(high1, high2, z2);
    
    char* sum1 = (char*)malloc(n + 2);
    char* sum2 = (char*)malloc(n + 2);
    addStrings(low1, high1, sum1);
    addStrings(low2, high2, sum2);
    
    karatsuba(sum1, sum2, z1);
    
    char* tempSub1 = (char*)malloc(2 * n + 2);
    char* tempSub2 = (char*)malloc(2 * n + 2);
    subStrings(z1, z0, tempSub1);
    subStrings(tempSub1, z2, tempSub2);
    strcpy(z1, tempSub2);
    
    char* resTemp = (char*)malloc(4 * n + 2);
    memset(resTemp, '0', 4 * n + 2);
    int k = 0;
    
    int lenZ0 = strlen(z0);
    for(int i = 0; i < lenZ0; i++){
        resTemp[i] = z0[i];
        k++;
    }
    
    int lenZ1 = strlen(z1);
    int carry = 0;
    for(int i = 0; i < lenZ1 || carry; i++){
        int val1 = (i + m < k) ? resTemp[i + m] - '0' : 0;
        int val2 = (i < lenZ1) ? z1[i] - '0' : 0;
        int sum = val1 + val2 + carry;
        resTemp[i + m] = (sum % 10) + '0';
        carry = sum / 10;
        if(i + m >= k) k = i + m + 1;
    }
    
    int lenZ2 = strlen(z2);
    carry = 0;
    for(int i = 0; i < lenZ2 || carry; i++){
        int val1 = (i + 2 * m < k) ? resTemp[i + 2 * m] - '0' : 0;
        int val2 = (i < lenZ2) ? z2[i] - '0' : 0;
        int sum = val1 + val2 + carry;
        resTemp[i + 2 * m] = (sum % 10) + '0';
        carry = sum / 10;
        if(i + 2 * m >= k) k = i + 2 * m + 1;
    }
    
    while(k > 1 && resTemp[k-1] == '0'){
        k--;
    }
    resTemp[k] = '\0';
    strcpy(result, resTemp);
    
    free(low1); free(high1); free(low2); free(high2);
    free(z0); free(z1); free(z2);
    free(sum1); free(sum2);
    free(tempSub1); free(tempSub2); free(resTemp);
}

int main(){
    char str1[10005];
    char str2[10005];
    
    if(scanf("%s", str1) == 1 && scanf("%s", str2) == 1){
        int len1 = strlen(str1);
        int len2 = strlen(str2);
        
        if((len1 == 1 && str1[0] == '0') || (len2 == 1 && str2[0] == '0')){
            printf("0\n");
            return 0;
        }
        
        strReverse(str1, len1);
        strReverse(str2, len2);
        
        char* result = (char*)malloc(20010);
        
        karatsuba(str1, str2, result);
        
        int resLen = strlen(result);
        strReverse(result, resLen);
        
        printf("%s\n", result);
        free(result);
    }
    return 0;
}
