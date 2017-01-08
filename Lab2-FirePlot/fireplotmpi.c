#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mpi.h"
#include <string.h>

// void PrintPlot(char* Plot[][W]){
// 	for(int x = 0;x<H;x++){
// 		for(int i =0;i<W;i++){
// 			printf("%s",Plot[x][i]);
// 		}
// 		printf("\n");
// 	}
// 	printf("\n\n\n\n");
// }
// int RandomizePlot(char* Plot[][W],int Fire[],int numtrees){
// 	int par;
// 	int count1 = 0;
// 	int count =0;
// 	numtrees= 0;
// 	for(int x = 0;x<H;x++){
// 		for(int i =0;i<W;i++){
// 			par = ((double)rand() / (double)RAND_MAX)<P;
// 			Plot[x][i] = "_";
// 			if(par==1){
// 				if(i ==0){
// 					Plot[x][i] ="*";
// 					Fire[count1] = (x*W)+i;
//
// 					//printf("%d\t%d\t%d\n",count1, (x*W)+i, Fire[count1]);
// 					count1++;
// 				}
// 				else{
// 					Plot[x][i]="T";
// 					count++;
// 					numtrees++;
// 				}
// 			}
// 		}
// 	}
// 	return numtrees;
// }
// int Lightup(char* Plot[][W], int Fire[], int numtrees){
// 	int iterations = 0;
// 	int count = 0;
// 	int TFire[H*W];
// 	int height;
// 	int width;
// 	int fcount=0;
// 	int i;
// 	//PrintPlot(Plot);
// 	while(numtrees>0&&Fire[0]>-1){
// 		iterations++;
// 		count = 0;
// 		for(i = 0;i<H*W;i++){
// 			TFire[i] = -1;
// 		}
// 		fcount =0;
// 		while(Fire[count]>-1){
// 			//printf("Bumppp\n");
// 			height = Fire[count]/W;
// 			width = Fire[count]%W;
// 			Plot[height][width] = "_";
// 			if(height>0 && *Plot[height-1][width]=='T'){
// 				Plot[height-1][width] = "*";
// 				TFire[fcount] = Fire[count]-W;
// 				fcount++;
// 				numtrees--;
// 			}
// 			if(height<H-1 && *Plot[height+1][width]=='T'){
// 				TFire[fcount]=Fire[count]+W;
// 				fcount++;
// 				Plot[height+1][width] = "*";
// 				numtrees--;
// 			}
// 			if(width<W-1 &&*Plot[height][width+1]=='T'){
// 				TFire[fcount]=Fire[count]+1;
// 				fcount++;
// 				Plot[height][width+1] = "*";
// 				numtrees--;
// 			}
// 			if(width>0&& *Plot[height][width-1]=='T'){
// 				TFire[fcount]=Fire[count]-1;
// 				fcount++;
// 				Plot[height][width-1] = "*";
// 				numtrees--;
// 			}
// 			count++;
//
//
// 		}
// 		//rintPlot(Plot);
// 		for(i = 0;i<H*W;i++)
// 			Fire[i] = TFire[i];
// 		//printf("%d\n",Fire[0]);
// 	}
// 	//printf("%d\n",iterations);
// 	return iterations;
// }
int main(){
	//MPI variables
	int        rank    ;
  int        size    ;
  MPI_Status status  ;
  int        tag = 0 ;
	//Other variables
	int iter = 0;
	double P = 0.0;
	int W = 0;
	int H = 0;
	int x;
	int i;
	//MPI Initialization
		MPI_Init(      &argc          , &argv ) ;
   MPI_Comm_size( MPI_COMM_WORLD , &size ) ; // same
   MPI_Comm_rank( MPI_COMM_WORLD , &rank ) ; // different
	//The Other Stuff

	if(rank ==0){
		srand(time(NULL));
		W=300;
		H =300;
		P = .05;
		double data[] = {W,H,P};
		for( j = 1 ; j < size ; j++ )
      {
         MPI_Send( &data , 1 , MPI_DOUBLE , j , tag , MPI_COMM_WORLD ) ;
      }
		for( k = 1 ; k < size ; k++ )
      {
         MPI_Recv( &nbt , 1 , MPI_DOUBLE , MPI_ANY_SOURCE , tag , MPI_COMM_WORLD , &status ) ;
         //
         j = status.MPI_SOURCE ;
         //
         printf( "%d %d %20.16f\n" , j , size , nbt ) ;
      }
	}




	// char* Plot[H][W];
	// int Fire[size];
	// int numtrees =0;
	// int burntime = 0;

	// while(P<1.0){
	// 	burntime = 0;
	// 	for(x=0;x<100;x++){
	// 		numtrees = 0;
	// 		for(i = 0;i<size;i++){
	// 			Fire[i] = -1;
	// 		}
	// 		numtrees = RandomizePlot(Plot, Fire,numtrees );
	// 		burntime+=Lightup(Plot,Fire,numtrees);
	// 		//printf("%d\n",burntime);
	// 	}
	// 	printf("%f\t%f\n",P,(double)(((double)burntime/(double)100.0))/(double)W);
	// 	P+=.05;

	}
}
