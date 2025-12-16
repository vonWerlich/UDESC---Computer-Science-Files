#include <stdio.h>
#include <unistd.h>

int getTamanho(char *palavra);

int main() {
    
    int n, i, j, k, digito;
    char str[101], resposta[101];
    
    while (scanf("%i %s", &n, str) != EOF) {
        
        if (n == 0 && !strcmp(str, "0"))
            exit(0);
        
        for (i = 0, j = 0; i < getTamanho(str); i++) {
            
            digito = str[i] - '0';
            
            if (n != digito)
                resposta[j++] = str[i];
                
        }
        
        for (i = 0; i < j; i++)
            if (resposta[i] != '0')
                break;
        
        if (j == i)
            printf("0\n");
        else {
            for (k = i; k < j; k++)
                printf("%c", resposta[k]);
            
            printf("\n");
        }
    }

    return 0;
}

int getTamanho(char *palavra) {
    int i = 0;
    
    while (palavra[i] != '\0')
        i++;
    
    return i;
}
