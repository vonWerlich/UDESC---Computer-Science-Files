#include <stdio.h>
#include <string.h>
int main() {
    int n, d;
    while (scanf("%d %d", &n, &d) != EOF) {
        if (!n)
            break;
        int alunos[n], r = 0, v, i;
        memset(alunos, 0, sizeof(alunos));
        while (d--) {
            for (i = 0; i < n; i++) {
                scanf("%d", &v);
                if (!v)
                    alunos[i] = 1;
            }
        }
        while (n)
            if (!alunos[--n]) {
                r = 1;
                break;
            }
        printf("%s\n", r? "yes" : "no");
    }
    return 0;
}
