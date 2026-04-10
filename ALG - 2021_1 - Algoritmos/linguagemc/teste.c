#include <stdio.h>
#define L 3
#define C 4

int main()
{
    int M[L][L]={1,2,3, 
                 4,5,6, 
                 7,8,9};
    int lin, col;
    
    for(lin=0; lin < L ; lin++){
        printf("\n");
        for(col=0; col<L; col++){
            //scanf("%i", &M[lin][col]);
            printf("%i\t", M[lin][col]);
        }
    }
    //Diagonal Principal
    for(lin=0; lin < L ; lin++){
        printf("\n");
        for(col=0; col<L; col++){
            if (lin==col )
               printf("%i\t", M[lin][col]);
        }
    }
    
    
    
    return 0;
}
