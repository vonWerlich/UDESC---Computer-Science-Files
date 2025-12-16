#include <stdio.h>

int main ()
{
int h1,m1,h2,m2;
int totalhoras,totalminutos;

scanf("%d", &h1);
scanf("%d", &m1);
scanf("%d", &h2);
scanf("%d", &m2);

totalhoras = h2 - h1;

totalminutos = m2 - m1;
 
 if (totalminutos < 0)

   {totalminutos = 60 + (m2 - m1);
    totalhoras--;}
    
 if (totalhoras < 0)

   {
    totalhoras = 24 + (h2 - h1);
   }

 if (h1 == h2 && m1 == m2)

   {printf("O JOGO DUROU 24 HORA(S) E 0 MINUTO(S)\n");}
    
 else
 	{
 	printf("O JOGO DUROU %d HORA(S) E %d MINUTO(S)\n", totalhoras, totalminutos);
	}	
		
	return 0;
}
