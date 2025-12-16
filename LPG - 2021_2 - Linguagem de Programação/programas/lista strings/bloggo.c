#include <stdio.h>
#include <string.h>
int main() {
    char letra, texto[60];
    int tam, italic = 0, bold = 0, i;
    while (fgets(texto, 50, stdin)) {
        tam = strlen(texto);
        for (i = 0; i < tam; i++) {
            letra = texto[i];
            if (letra == '_') {
                italic++;
                if (italic % 2)
                    printf("<i>");
                else
                    printf("</i>");
            }
            else if (letra == '*') {
                bold++;
                if (bold % 2)
                    printf("<b>");
                else
                    printf("</b>");
            }
            else
                printf("%c", letra);
        }
    }
    return 0;
}
