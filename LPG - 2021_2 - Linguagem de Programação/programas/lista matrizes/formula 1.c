#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

#define TRUE 1
#define FALSE 0


int corrida[101][101], sistema[101], ponto[101];

int main(){
 int m,g,p,s,k,i,j;
 while(scanf("%i %i", &g, &p) && (g || p)){
  for (i = 0; i < g; ++i){
   for (j = 0; j < p; ++j){
    scanf("%d", &corrida[i][j]);
   }
  }
  scanf("%d", &s);
  while(s--){
   memset(ponto, 0, sizeof(ponto)); 
   memset(sistema, 0, sizeof(sistema));
   scanf("%d", &k);
   for (i = 0; i < k; ++i)
    scanf("%d", &sistema[i]);
   for (i = 0; i < g; ++i){
    for (j = 0; j < p; ++j){
     ponto[j] += sistema[corrida[i][j]-1];
    }
   }
   m = 0;
   for (i = 0; i < p; ++i)
   if( ponto[i] > m) 
   m = ponto[i];
   int f = TRUE;
   for (i = 0; i < p; ++i){
    if(ponto[i] == m){
     if(f==TRUE){
      printf("%d", i + 1);
      f = FALSE;
     }else{
      printf(" %d", i + 1);
     }
    }
   }
   printf("\n");
  }
 }
 return 0;
}
