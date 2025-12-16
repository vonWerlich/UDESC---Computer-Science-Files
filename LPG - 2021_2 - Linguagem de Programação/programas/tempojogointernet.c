#include <stdio.h>
int main()
{
int h1,h2,m1,m2,htotal,mtotal;
    scanf("%d %d %d %d", &h1, &m1, &h2, &m2);

htotal = h2 - h1;

if (htotal < 0)
    {
        htotal = 24 + (h2 - h1);
    }

mtotal = m2 - m1;
if (mtotal < 0)

  {
   mtotal = 60 + (m2 - m1);
   if (htotal==0)
   {htotal=23;}
   else
   {htotal--;
   }
  }

    if (h1 == h2 && m1 == m2)

    {
    printf("O JOGO DUROU 24 HORA(S) E 0 MINUTO(S)\n");
    }
    else printf("O JOGO DUROU %d HORA(S) E %d MINUTO(S)\n",htotal,mtotal);
    return 0;
}
