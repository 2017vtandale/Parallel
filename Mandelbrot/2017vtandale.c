//Vishal Tandale Period 5
#ifdef __APPLE__
#include<GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <time.h>
#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define Width   480//480
#define Height  620//620
MPI_Status status  ;
int pic[Width][Height];
int step, maxstep, threshhold;
double boundxmin,boundxmax, boundymin,boundymax;
double realx, realy;
double dx, dy;
double zx, zy;
double xsize, ysize;
int r, g, b;
int  rank, size, tag;
int main(int argc, char* argv[]);
void create(); // prototype

double getPix(int x, int y){
  //printf("%d,%d\n",x,y);
  step = 0;
  realx = boundxmin + ((double) x) *dx;
  realy = boundymin + ((double) y) *dy;
  zx = 0;
  zy = 0;
  double tzx = 0;
  int i;
  for(i =0; i<maxstep;i++){
    if(zx*zx + zy*zy >threshhold){
      return i; }
    tzx = zx;
    zx = zx*zx - zy*zy + realx;
    zy = 2*tzx*zy + realy;
  }
  return 0;//(zx*zx + zy*zy)*255/threshhold;
}

void  getRow(int x, int col[]){
  int i =0;
  for(i =0;i<Height;i++){
    col[i] = (int)getPix(x,i);
    //printf("%d\t",col[i]);
  }
  //printf("\n");
  //printf("I made it to rows");
}

void displayfunc(){
   int    x  , y  ;
   //
  //  double x1 , y1 ;
  //  double x2 , y2 ;
  //  double x3 , y3 ;
   double  pixel;
   char stepstr[20]; // overkill... 20 digits
   //
   glClear(GL_COLOR_BUFFER_BIT); // white
   //
   for( x = 0 ; x < Width; x++ )
   {
      for( y = 0 ; y <Height; y++ )
      {
        pixel =1 -  pic[x][y]*1.0/maxstep;

        glColor3f( r*pixel ,(g)*pixel ,(b)*pixel ) ;
         glBegin(GL_POINTS);
         glVertex2f(x,y);
         glEnd();
      }
   }
   glutSwapBuffers(); // single buffering... call glFlush();
}
void reshapefunc(int wscr,int hscr){
   glViewport(0,0,(GLsizei)Width,(GLsizei)Height);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluOrtho2D(0.0,1.0*Width,0.0,1.0*Height); // always a square
   glMatrixMode(GL_MODELVIEW);
}
void zoom(int x, int y){
  time_t seconds;
  seconds = time(NULL);
  realx = boundxmin + 2*xsize*((double) x)/(1.0*Height);
  realy = boundymin + 2*ysize*((double) y)/(1.0*Width);
  //printf("%f,%f\n",realx,realy);
  xsize = .5*xsize;
  ysize = .5*ysize;
  boundxmin = realx - xsize;
  boundxmax = realx + xsize;
  boundymin = realy - ysize;
  boundymax = realy + ysize;
  printf("%f-%f\t%f-%f\n",boundxmin,boundxmax,boundymin,boundymax);
  seconds = time(NULL)- seconds;
  printf("Time Taken: %ld\n", seconds);
  create();
}
void mousefunc(int button,int state,int xscr,int yscr){
      if(button == GLUT_LEFT_BUTTON){
        if(state==GLUT_DOWN){
      printf("%d\t%d\n",xscr,yscr);
      zoom(xscr,Height-yscr);
    }
    }
}
void keyfunc(unsigned char key,int xscr,int yscr){
  //printf("*** %c\n",key);
   if( key == 'w' )
  {
      maxstep = 2*maxstep;
      printf("%d\n",maxstep);
      create();
   }
   else if( key == 'r'){
     r = 0;
     g = 1;
     b = 1;
     create();
   }
   else if (key == 'b'){
     r=1;
     g=1;
     b=0;
     create();
   }
   else if(key == 'g'){
     r=1;
     g=0;
     b=1;
     create();
   }
  else
     if( key == 'q' )
   {
      exit( 0 ) ;
   }
}



int main(int argc, char* argv[]){
  tag = 0 ;
  r = 1;
  g = 1;
  b = 1;
  MPI_Init(      &argc          , &argv ) ;
  MPI_Comm_size( MPI_COMM_WORLD , &size ) ; // same
  MPI_Comm_rank( MPI_COMM_WORLD , &rank ) ; // different


  if(rank ==0){
    glutInit(&argc,argv);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize(Width,Height);
   glutInitWindowPosition(100,50);
   glutCreateWindow("");
   glClearColor(0,1.0,1.0,0.0);
   glShadeModel(GL_SMOOTH);

   xsize =2.0;
   ysize = 1.5;
   boundxmin = 0-xsize;
   boundxmax = xsize;
   boundymin = 0-ysize;
   boundymax = ysize;
   threshhold = 4;
   maxstep = 100;
   dx = 2*xsize/(double)Height;
   dy = 2*ysize/(double)Width;
   create();


   glutDisplayFunc(displayfunc);
   glutReshapeFunc(reshapefunc);
   glutMouseFunc(mousefunc);
   glutKeyboardFunc(keyfunc);

   //
   glutMainLoop();
   exit(0);
   MPI_Finalize();

 }
 else{
  double P[7] = {1,1,1,1,1,1,1};
  while(P[6]>-1){

    MPI_Recv( &P , 7 , MPI_DOUBLE , 0 , tag , MPI_COMM_WORLD , &status );
    boundxmin = P[0];
    boundxmax = P[1];
    boundymin = P[2];
    boundymax = P[3];
    xsize = (boundxmax-boundxmin)/(double)2;
    ysize = (boundymax-boundymin)/(double)2;
    threshhold = (int)P[4];
    maxstep = (int)P[5];
    dx = 2*xsize/(double)Height;
    dy = 2*ysize/(double)Width;
    //printf("%f,%f,%f,%f,%f,%f,%f\n",P[0],P[1],P[2],P[3],P[4],P[5],P[6]);
    int temp[Height];
    getRow((int)P[6],temp);
    MPI_Send( &temp , Height , MPI_INT , 0 , tag , MPI_COMM_WORLD ) ;
  }
}


    return 0;
  }
void create(){
  int Workers[size];
  int k, count, d, j,i;
  int row[Height];
  double keyvalues[7] = {boundxmin,boundxmax,boundymin,boundymax,threshhold,maxstep, (double)0};

  for(j=0; j<Width;j++){
    for(k=0;k<Height;k++){ pic[j][k]=0;
    }}
  count = 0;
  for( j = 1 ; j < size ; j++ )
    {
        keyvalues[6]=1.0*count;
        Workers[j] = count;

       MPI_Send( &keyvalues , 7 , MPI_DOUBLE , j , tag , MPI_COMM_WORLD );
       count++;
    }

    while(count<Width){
      //printf("imadeit\n");
      MPI_Recv( &row ,Height , MPI_INT , MPI_ANY_SOURCE , tag , MPI_COMM_WORLD , &status ) ;
      j = status.MPI_SOURCE ;
      //printf( "%d\t%20.16f\n" , Workers[j],nbt);
      i=Workers[j];
      for(d = 0;d<Height;d++){
        pic[i][d]=row[d];
        //printf("%d\t",pic[i][d]);
      }
      //printf("\n");
      //glutPostRedisplay();

      Workers[j] = count;

      //printf("\n%d,%f\n",j,P);
      keyvalues[6]=  1.0*count;
      MPI_Send( &keyvalues , 7 , MPI_DOUBLE , j , tag , MPI_COMM_WORLD ) ;
      //printf("%d\n",count);
      count++;

    }
    //printf("Made it\n");
  for( k = 1 ; k < size ; k++ )
    {

      MPI_Recv( &row ,Height , MPI_INT , MPI_ANY_SOURCE , tag , MPI_COMM_WORLD , &status ) ;
      j = status.MPI_SOURCE ;
      //printf( "%f\t%20.16f\n" , Workers[j],nbt);
      i = Workers[j];
      for(d = 0;d<Height;d++){
        pic[i][d]=row[d];
        //printf("%d\t",pic[i][d]);
      }
      //printf("\n");
      //glutPostRedisplay();
       //
       //printf( "%f\t%20.16f\n" , Workers[j],nbt);
       keyvalues[6]= -1;
       MPI_Send( &keyvalues , 5 , MPI_DOUBLE , j , tag , MPI_COMM_WORLD ) ;
      //printf("%d %d",numtrees, burntime);
    //nbt=burntime;

    }
    //printf("Imadeit\n");
    glutPostRedisplay();


}
