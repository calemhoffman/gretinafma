#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/mtio.h>
#include <math.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

float PKX(int k, float x){
  float value;
  switch(k){
    case 0:
      value = 1.0;
      break;
    case 2:
      value = 0.5*(3.0*powf(x,2.)-1.);
      break;
    case 4:
      value = (35.0*powf(x,4.)-30.*powf(x,2.)+3)/8.0;
      break;
  }
  return value;
}

int main(int argc, char **argv)
{
  float a0, a2, a4;
  float x,j;
  float angle,Radian;
  float value;

  Radian=atan(1.0)/45.0;

  if (argc==4){
    a0 = (float)strtod(argv[1], NULL);
    a2 = (float)strtod(argv[2], NULL);
    a4 = (float)strtod(argv[3], NULL);
    //printf("a0=%10.6f; a2=%10.6f; a4=%10.6f\n",a0,a2,a4);

    for(j=0.0;j<90.0;j++){
      x=cosf(j*Radian);
      value=PKX(0,x)*a0;
      value+=PKX(2,x)*a2;
      value+=PKX(4,x)*a4;
      printf("%10.6f\t%10.6f\n",x,value);
    }
  }
  else if(argc==5){
    a0 = (float)strtod(argv[1], NULL);
    a2 = (float)strtod(argv[2], NULL);
    a4 = (float)strtod(argv[3], NULL);
    //printf("a0=%10.6f; a2=%10.6f; a4=%10.6f\n",a0,a2,a4);
    angle = (float)strtod(argv[4], NULL);
    x=cosf(angle*Radian);
    value=PKX(0,x)*a0;
    value+=PKX(2,x)*a2;
    value+=PKX(4,x)*a4;
    //printf("%10.6f\t%10.6f\t%10.6f\n",angle,x,value);
    printf("%10.6f\t%10.6f\n",x,value);
  }
  else{
    printf("USAGE1: a0 a2 a4\n");
    printf("USAGE2: a0 a2 a4 angle(in degree)\n");
    exit(-1);
  }
}

