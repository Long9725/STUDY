#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 50

int max(int a, int b);
void LCS(char* X, char* Y, int m, int n);
void printLCS(int b[][MAX], char* X, int i, int j, char* output);

int main() {
    char X[] = "ABCDEFDEF";
    char Y[] = "GBCDFEDEF";

    LCS(X, Y, strlen(X), strlen(Y));

    return 0;
}

/*
X, Y는 문자열, m은 col, n은 row
*/
void LCS(char* X, char* Y, int m, int n) {
    // print table
    int b[MAX][MAX] = { 0 };
    // cost table
    int c[MAX][MAX] = { 0 };
    char output[MAX] = { 0 };      
    
    for (int i = 0; i < m+1; i++) c[i][0] = 0;
    for (int i = 0; i < n+1; i++) c[0][i] = 0;

    for (int i = 1; i < m+1; i++) {
        for (int j = 1; j < n+1; j++) {
            if (X[i-1] == Y[j-1]) {
                c[i][j] = c[i-1][j-1] + 1;
                b[i-1][j-1] = 2; // 대각선 = 2
            } else {
                c[i][j] = max(c[i-1][j], c[i][j-1]);
                if (c[i][j] == c[i-1][j] && c[i][j] == c[i][j-1]) b[i-1][j-1] = 4; // 왼쪽, 위 둘 다 = 4
                else if (c[i][j] == c[i-1][j]) b[i-1][j-1] = 3; // 위 = 3
                else b[i-1][j-1] = 1; // 왼쪽 = 1
            }
        }
    }

    for (int i = 0; i < m; i++) printf("%c  ", *(X+i));
    printf("\n");
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) printf("%d  ", b[i][j]);
        printf("\n");
    }

    printLCS(b, X, m-1, n-1, output);
}


void printLCS(int b[][MAX], char* X, int i, int j, char* output) {
    if (i == 0 || j == 0) {
        for (int k = 0; k < strlen(X); k++) printf("%c", output[k]);
        printf("\n");
        return;
    }
    // 대각선
    if (b[i][j] == 2) { 
        output[i-1] = X[i];
        printLCS(b, X, i-1, j-1, output);
    } else if (b[i][j] == 4) {
        char* temp = (char*)malloc(sizeof(char)*strlen(output)+1);
        for (int k = 0; k < strlen(X)+1; k++) temp[k] = output[k];
        printLCS(b, X, i-1, j, temp);
        printLCS(b, X, i, j-1, output);
        free(temp);
    } else if (b[i][j] == 3) printLCS(b, X, i-1, j, output); // 위
    else printLCS(b, X, i, j-1, output); // 왼쪽
}

int max(int a, int b) {
    if(a < b) return b;
    else return a;
}