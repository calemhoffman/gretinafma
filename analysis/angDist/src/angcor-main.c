#include "shell.h"
int
main (int argc, char **argv){
  int option;
  int i1,i2,i3,i4,i5,i6;
  double fji,fjf,faci,facf;
  double fj,fac;
  int l11, l21, ji, jf, j;
  int l12, l22;
  double value,delta1,delta2,sigma;
  double a0,a2,a4,a6;

  if (argc==1) {
    printf("USAGE: For Clebsch_Gordan:       1 j1 j2 j3 m1 m2 m3\n");
    printf("USAGE: For Wigner 6j-symbol:     2 j1 j2 j3 l1 l2 l3\n");
    printf("USAGE: For angular distribution: 3 ji l1 l2 jf delta sigma\n");
    printf("USAGE: For angular correlations: 4 ji l11 l21 j l12 l22 jf delta1 delta2\n");
    exit(-1);
  }

  option = strtol(argv[1], NULL, 0);
  if(option == 1){
    if(argc!=8){
      printf("1 j1 j2 j3 m1 m2 m3\n");
      exit(-1);
    }
    i1 = strtol(argv[2], NULL, 0);
    i2 = strtol(argv[3], NULL, 0);
    i3 = strtol(argv[4], NULL, 0);
    i4 = strtol(argv[5], NULL, 0);
    i5 = strtol(argv[6], NULL, 0);
    i6 = strtol(argv[7], NULL, 0);

    value = clebsch_gordan(i1,i2,i3,i4,i5,i6);
    printf("CG: <%i %i %i %i | %i %i> = %g\n",
                 i1/2,i4/2,i2/2,i5/2,i3/2,i6/2,value);
  }
  else if(option == 2){
    if(argc!=8){
      printf("2 j1 j2 j3 l1 l2 l3\n");
      exit(-1);
    }
    i1 = strtol(argv[2], NULL, 0);
    i2 = strtol(argv[3], NULL, 0);
    i3 = strtol(argv[4], NULL, 0);
    i4 = strtol(argv[5], NULL, 0);
    i5 = strtol(argv[6], NULL, 0);
    i6 = strtol(argv[7], NULL, 0);

    value = wigner_6j(i1,i2,i3,i4,i5,i6);
    printf("Wigner 6j: {%i %i %i; %i %i %i} = %g\n",
                       i1/2,i2/2,i3/2,i4/2,i5/2,i6/2,value);
  }
  else if(option == 3){
    if(argc!=8){
      printf("3 ji l1 l2 jf delta sigma\n");
      exit(-1);
    }
    fji = strtod(argv[2], NULL);
    l11 = strtol(argv[3], NULL, 0);
    l21 = strtol(argv[4], NULL, 0);
    fjf = strtod(argv[5], NULL);
    delta1 = strtod(argv[6], NULL);
    sigma = strtod(argv[7], NULL);
    //sigma*=fji;
    ji=(int)(fji*2);
    faci=((float)ji-fji*2.0);
    jf=(int)(fjf*2);
    facf=((float)jf-fjf*2.0);
    if(faci==0.0 && facf==0.0){
      l11*=2;l21*=2;

      //printf("a0=%f; a2=%f; a4=%f; a6=%f\n",a0,a2,a4,a6);
      for (int incr=0;incr<3600;incr++){
        delta1 = (float)incr*0.1-180.0;
        a0=aK(ji, l11, l21, jf, 0, delta1, sigma);
        a2=aK(ji, l11, l21, jf, 2, delta1, sigma);
        a4=aK(ji, l11, l21, jf, 4, delta1, sigma);
        a6=aK(ji, l11, l21, jf, 6, delta1, sigma);
        printf("%f %f %f %f %f %f %d %d %d %d\n",
        delta1,a0,a2,a4,a6,sigma,ji/2, l11/2, l21/2, jf/2);
      }
    }
    else{
      printf("%f or %f are not integer or half integer\n",fji,fjf);
      exit(0);
    }
  }
  else if(option == 4){
    if(argc!=11){
      printf("4 ji l11 l21 j l12 l22 jf delta1 delta2\n");
      exit(-1);
    }
    fji = strtod(argv[2], NULL);
    l11 = strtol(argv[3], NULL, 0);
    l21 = strtol(argv[4], NULL, 0);
    fj = strtod(argv[5], NULL);
    l12 = strtol(argv[6], NULL, 0);
    l22 = strtol(argv[7], NULL, 0);
    fjf = strtod(argv[8], NULL);
    delta1 = strtod(argv[9], NULL);
    delta2 = strtod(argv[10], NULL);

    ji=(int)(fji*2);
    faci=((float)ji-fji*2.0);
    jf=(int)(fjf*2);
    facf=((float)jf-fjf*2.0);
    j=(int)(fj*2);
    fac=((float)j-fj*2.0);

    if(faci==0.0 && facf==0.0 && fac==0.0){
      l11*=2;l21*=2;
      l12*=2;l22*=2;
      a0=caK(ji, l11, l21, j, l12, l22, jf, delta1, delta2, 0);
      a2=caK(ji, l11, l21, j, l12, l22, jf, delta1, delta2, 2);
      a4=caK(ji, l11, l21, j, l12, l22, jf, delta1, delta2, 4);
      a6=caK(ji, l11, l21, j, l12, l22, jf, delta1, delta2, 6);
      printf("a0=%f; a2=%f; a4=%f; a6=%f\n",a0,a2,a4,a6);
    }
    else{
      printf("%f, %f or %f are not integer or half integer\n",fji,fj,fjf);
      exit(0);
    }

  }
  else{
    printf("\007  ERROR -- choose 1, 2, 3 or 4!\n");
    printf("USAGE: Clebsch_Gordan:\n");
    printf("       1 j1 j2 j3 m1 m2 m3\n");
    printf("USAGE: Wigner 6j-symbol:\n");
    printf("       2 j1 j2 j3 l1 l2 l3\n");
    printf("USAGE: angular distributions (a0, a2, a4, a6):\n");
    printf("       3 ji l1 l2 jf delta sigma/ji\n");
    printf("USAGE: angular correlations (a0, a2, a4, a6):\n");
    printf("       4 ji l11 l21 j l12 l22 jf delta1 delta2\n");
    exit(0);
  }
  exit(1);
}
