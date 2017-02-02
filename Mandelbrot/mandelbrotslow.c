//Vishal Tandale Period 5
#ifdef __APPLE__
#include<GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define Width   500//480
#define Height  500//620
int r, g, b;
int pic[Width][Height];
int step, maxstep, threshhold;
double boundxmin,boundxmax, boundymin,boundymax;
double realx, realy;
double dx, dy;
double zx, zy;
double xsize, ysize;
void create(); // prototype
double getPix(int x, int y){
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

void displayfunc()
{
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
        pixel = pic[x][y]*1.0/maxstep;

        glColor3f( r*pixel , g*pixel , b*pixel ) ;
         glBegin(GL_POINTS);
         glVertex2f(x,y);
         glEnd();
      }
   }
   glutSwapBuffers(); // single buffering... call glFlush();
}
void reshapefunc(int wscr,int hscr)
{
   glViewport(0,0,(GLsizei)Width,(GLsizei)Height);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluOrtho2D(0.0,1.0*Width,0.0,1.0*Height); // always a square
   glMatrixMode(GL_MODELVIEW);
}
void zoom(int x, int y){
  realx = boundxmin + 2*xsize*((double) x)/(1.0*Height);
  realy = boundymin + 2*ysize*((double) y)/(1.0*Width);
  printf("%f,%f\n",realx,realy);
  xsize = .5*xsize;
  ysize = .5*ysize;
  boundxmin = realx - xsize;
  boundxmax = realx + xsize;
  boundymin = realy - ysize;
  boundymax = realy + ysize;
  printf("%f-%f\t%f-%f\n",boundxmin,boundxmax,boundymin,boundymax);
  create();
}
void mousefunc(int button,int state,int xscr,int yscr)
{
      if(button == GLUT_LEFT_BUTTON){
        if(state==GLUT_DOWN){
      printf("%d\t%d\n",xscr,yscr);
      zoom(xscr,Height-yscr);
    }
    }
}
void keyfunc(unsigned char key,int xscr,int yscr)
{
  //printf("*** %c\n",key);
   if( key == 'w' )
  {
      maxstep = 2*maxstep;
      create();
   }
   else if( key == 'r'){
     r = 1;
     g = 0;
     b = 0;
     create();
   }
   else if (key == 'b'){
     r=0;
     g=0;
     b=1;
     create();
   }
   else if(key == 'g'){
     r=0;
     g=1;
     b=0;
     create();
   }
  else
     if( key == 'q' )
   {
      exit( 0 ) ;
   }
}

void create(){
  int i, e, d;

  dx = 2*xsize/(double)Height;
  dy = 2*ysize/(double)Width;
  int temp[Height];
  for(i =0;i<Width;i++){
    getRow(i, temp);
    for(d = 0;d<Height;d++){
      pic[i][d]=temp[d];
      //glutPostRedisplay();
      //printf("%d\t",pic[i][d]);

    }
    glutPostRedisplay();
    //printf("\n");
  }
}
int main(int argc, char* argv[])
{

  //printf("I'm IN the main");
  glutInit(&argc,argv);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize(Width,Height);
   glutInitWindowPosition(100,50);
   glutCreateWindow("");
   glClearColor(0,1.0,1.0,0.0);
   glShadeModel(GL_SMOOTH);
   r=1;
   g=1;
   b=1;
   xsize =2.0;
   ysize = 1.5;
   boundxmin = 0-xsize;
   boundxmax = xsize;
   boundymin = 0-ysize;
   boundymax = ysize;
   threshhold = 4;
   maxstep = 100;

   create();

   glutDisplayFunc(displayfunc);
   glutReshapeFunc(reshapefunc);
   glutMouseFunc(mousefunc);
   glutKeyboardFunc(keyfunc);
   //
   glutMainLoop();




  return 0;
}
