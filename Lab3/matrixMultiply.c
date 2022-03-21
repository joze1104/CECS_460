#include "matrixMultiply.h"
void matrixMultiply(int a[2][2], int b[2][2], int c[2][2])
{
   int i, j, k;


   // Loop through a matrix rows
   Row_Loop:for(i=0; i<2; i++)
   {
	   // Loop through b matrix columns
       Col_Loop:for(j=0; j<2; j++)
       {
           Product_Loop:for(k=0; k<2; k++)
           {
               c[i][j] += a[i][k]*b[k][j];
           }
       }
   }

}
