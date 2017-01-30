#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mpi.h"
#include <string.h>
int W,H;
double P;
void PrintPlot(char* Plot[][W]){
	for(int x = 0;x<H;x++){
		for(int i =0;i<W;i++){
			printf("%s",Plot[x][i]);
		}
		printf("\n");
	}
	printf("\n\n\n\n");
}
int RandomizePlot(char* Plot[][W],int Fire[]){
	int par;
	int count1 = 0;
	int count =0;
	int numtrees= 0;
	//printf("\n%d,%d\n",H,W);
	for(int x = 0;x<H;x++){
		for(int i =0;i<W;i++){
			par = ((double)rand() / (double)RAND_MAX)<P;
			Plot[x][i] = "_";
			if(par==1){
				if(i ==0){
					Plot[x][i] ="*";
					Fire[count1] = (x*W)+i;

					//printf("%d\t%d\t%d\n",count1, (x*W)+i, Fire[count1]);
					count1++;
				}
				else{
					Plot[x][i]="T";
					count++;
					numtrees++;
				}
			}
		}
	}
	return numtrees;
}
int Lightup(char* Plot[][W], int Fire[], int numtrees){
	int iterations = 0;
	int count = 0;
	int TFire[H*W];
	int height;
	int width;
	int fcount=0;
	int i;
	//PrintPlot(Plot);
	while(numtrees>0&&Fire[0]>-1){
		iterations++;
		count = 0;
		for(i = 0;i<H*W;i++){
			TFire[i] = -1;
		}
		fcount =0;
		while(Fire[count]>-1){
			//printf("Bumppp\n");
			height = Fire[count]/W;
			width = Fire[count]%W;
			Plot[height][width] = "_";
			if(height>0 && *Plot[height-1][width]=='T'){
				Plot[height-1][width] = "*";
				TFire[fcount] = Fire[count]-W;
				fcount++;
				numtrees--;
			}
			if(height<H-1 && *Plot[height+1][width]=='T'){
				TFire[fcount]=Fire[count]+W;
				fcount++;
				Plot[height+1][width] = "*";
				numtrees--;
			}
			if(width<W-1 &&*Plot[height][width+1]=='T'){
				TFire[fcount]=Fire[count]+1;
				fcount++;
				Plot[height][width+1] = "*";
				numtrees--;
			}
			if(width>0&& *Plot[height][width-1]=='T'){
				TFire[fcount]=Fire[count]-1;
				fcount++;
				Plot[height][width-1] = "*";
				numtrees--;
			}
			count++;


		}
		//PrintPlot(Plot);
		for(i = 0;i<H*W;i++)
			Fire[i] = TFire[i];
		//printf("%d\n",Fire[0]);
	}
	//printf("%d\n",iterations);
	return iterations;
}
int main(int argc , char* argv[]){
	//MPI variables
	int        rank    ;
  int        size    ;
  MPI_Status status  ;
  int        tag = 0 ;
	//Other variables
	int iter, x, i, j, k;
	double nbt, data;

	//MPI Initialization
		MPI_Init(      &argc          , &argv ) ;
   MPI_Comm_size( MPI_COMM_WORLD , &size ) ; // same
   MPI_Comm_rank( MPI_COMM_WORLD , &rank ) ; // different
	//The Other Stuff

	if(rank ==0){
		srand(time(NULL));
		//double PS[] = {0,.1,.2,.8,.9,1};
		double PS[] = {0,.1,.2,.3,.4,.45,.5,.54,.56,.565,.57,.575,.58,.585,.59,.595,.6,.61,.62,.63,.64,.65,.66,.67,.68,.705,.73,.78,.8,.9,1};
		double Workers[size];
		int count = -1;;
		P=0;
		//printf("%w",sizeof(PS));
		for( j = 1 ; j < size ; j++ )
      {
        count+=1;
        	P=PS[count];
         if(count>sizeof(PS))
            break;
         MPI_Send( &P , 1 , MPI_DOUBLE , j , tag , MPI_COMM_WORLD ) ;
		 Workers[j] = P;
		 //printf("\n%d,%f\n",j,P);
	     

      }
			while(PS[count]<1){
				MPI_Recv( &nbt , 1 , MPI_DOUBLE , MPI_ANY_SOURCE , tag , MPI_COMM_WORLD , &status ) ;
				j = status.MPI_SOURCE ;
				printf( "%f\t%20.16f\n" , Workers[j],nbt);
				count+=1;
				P = PS[count];
				Workers[j] = P;
				//printf("\n%d,%f\n",j,P);
                MPI_Send( &P , 1 , MPI_DOUBLE , j , tag , MPI_COMM_WORLD ) ;
                

			}
		for( k = 1 ; k < size ; k++ )
      {
        printf("Made it");
         MPI_Recv( &nbt , 1 , MPI_DOUBLE , MPI_ANY_SOURCE , tag , MPI_COMM_WORLD , &status ) ;
         //
         j = status.MPI_SOURCE ;
         P = -1.0;
         //
         printf( "%f\t%20.16f\n" , Workers[j],nbt);
        MPI_Send( &P , 1 , MPI_DOUBLE , j , tag , MPI_COMM_WORLD ) ;
        //printf("%d %d",numtrees, burntime);
	    //nbt=burntime;
	    
      }
      exit(0);  
      MPI_Finalize();
    
	}
    else{
        while(P>=0){
        MPI_Recv( &P , 1 , MPI_DOUBLE , 0 , tag , MPI_COMM_WORLD , &status );
        if(P<0)
            break;
        W = 300;
        H = 300;
        //printf("\n%d,%d,%f\n",W,H,P);
	    char* Plot[H][W];
	    int Fire[H*W];
	    int numtrees =0;
	    int burntime = 0;
	    int Trials = 100;
	    for(x=0;x<Trials;x++){
	        for(int i =0;i<H*W;i++){
            Fire[i] = -1;
            }

        numtrees = RandomizePlot(Plot, Fire);
	    burntime+=Lightup(Plot,Fire,numtrees);
        }
        nbt = (double)((((double)burntime/(double)Trials))/(double)W);
        MPI_Send( &nbt , 1 , MPI_DOUBLE , 0 , tag , MPI_COMM_WORLD ) ;
    }
    }




	// while(P<1.0){
	// 	burntime = 0;
	// 		//printf("%d\n",burntime);
	// 	}
	// 	printf("%f\t%f\n",P,(double)(((double)burntime/(double)100.0))/(double)W);
	// 	P+=.05;

}
