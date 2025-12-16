#include <stdio.h>
#include <string.h>

int main()
{
    int N, L, C;
    char story[100002];
    int len, chars, lines, pages, checkpoint;
    int i, j;

    while (scanf("%d%d%d",&N,&L,&C) != EOF) {
        getchar();

        fgets(story, 100002, stdin);
        len = strlen(story) - 1;

        chars = checkpoint = 0;
        lines = pages = 1;

        for (i = 0; i < len; ++i) {
            if (i && story[i-1] == ' ')
                checkpoint = i;

            if (chars == C) {
                lines++;
                if (story[i] == ' ')
                    chars = 0;
                else
                    chars = i - checkpoint + 1;
            } else
                chars++;
        }

        pages = lines / L + (lines % L > 0);

        printf("%d\n", pages);
    }

    return 0;
}
