#include <stdio.h>

int regressiva(int k){
    if (k < 0){
        return k;
    }
    printf("%d ", k);
    k--;
    return regressiva(k);
}

int main(){
    int k;

    scanf("%d", &k);

    return regressiva(k);
}