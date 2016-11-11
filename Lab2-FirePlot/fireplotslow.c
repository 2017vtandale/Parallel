#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
int W;
int H;
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
int RandomizePlot(char* Plot[][W],int Fire[],int numtrees){
	int par;
	int count1 = 0;
	int count =0;
	numtrees= 0;
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
		//rintPlot(Plot);
		for(i = 0;i<H*W;i++)
			Fire[i] = TFire[i];
		//printf("%d\n",Fire[0]);
	}
	//printf("%d\n",iterations);
	return iterations;
}
int main(){
	srand(time(NULL));
	W=(int)(((double)rand() / (double)RAND_MAX)*70)+300;
	H = (int)(((double)rand() / (double)RAND_MAX)*70)+400;
	printf("%d\n",rand());
	printf("%d\t%d\n",W,H);
	int size = W*H;
	P = .05;
	int x;
	int i;
	char* Plot[H][W];
	int Fire[size];
	int numtrees =0;
	int burntime = 0;

	while(P<1.0){
		burntime = 0;
		for(x=0;x<100;x++){
			numtrees = 0;
			for(i = 0;i<size;i++){
				Fire[i] = -1;
			}
			numtrees = RandomizePlot(Plot, Fire,numtrees );
			burntime+=Lightup(Plot,Fire,numtrees);
			//printf("%d\n",burntime);
		}
		printf("%f\t%f\n",P,(double)(((double)burntime/(double)100.0))/(double)W);
		P+=.05;

	}
}
