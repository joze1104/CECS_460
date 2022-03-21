#include "matrixMultiply.h"

int main(void)
{
	// Stimulus
    int a[2][2] = {{69, 42}, {99, 21}};
	int b[2][2] = {{74, 69}, {30, 42}};

	// Reference Model
	int Refc[2][2] = {{6366, 6525}, {7956, 7713}};


	int c[2][2] = {{0,0}, {0,0}};
    int i, j;
    int errCnt = 0;


    // DUT
    matrixMultiply(a, b, c);

    // Printing matrix a
	printf("The first matrix: \n");
	for(i = 0; i < 2; i++){
	  for(j = 0; j < 2; j++){
		  printf("%d",a[i][j]);
		  printf("\t");
	  }
	  printf("\n");
	}

	// Printing matrix b
	printf("The second matrix: \n");
	for(i = 0; i < 2; i++){
	  for(j = 0; j < 2; j++){
		  printf("%d",b[i][j]);
		  printf("\t");
	  }
	  printf("\n");
	}

	// Printing resulting matrix
	printf("The result of matrix multiplication is: \n");
	for(i = 0; i < 2; i++){
	  for(j = 0; j < 2; j++){
		  printf("%d",c[i][j]);
		  printf("\t");
	  }
	  printf("\n");
	}

	// Scoreboard
	for(i = 0; i < 2; i++)
	{
		  for(j = 0; j < 2; j++)
		  {
			  if (c[i][j] == Refc[i][j])
			  {
				  printf("\n");
			  }
			  else
			  {
				  printf("%d\n",Refc[i][j]);
				  errCnt++;
			  }
		  }
		  printf("\n");
	}

    return 0;
}
