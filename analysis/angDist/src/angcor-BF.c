#include "shell.h"

       /*
       ** returns the value of the B_(k/2)(j/2) coefficient                                  
       */

double BK(int j, int k){
  double value=0.0;
  
  if((j % 2)==0){
    value = PHASE(j/2)*sqrt(j+1)*clebsch_gordan(j, j, k, 0, 0, 0);
  }
  else if((j % 2)==1){
    value = PHASE((j-1)/2)*sqrt(j+1)*clebsch_gordan(j, j, k, 1, -1, 0);
  }
  printf("BK(%i,%i)=%g\n",j/2,k/2,value);
  return value;
}

       /*
       ** returns the value of the F_(k/2)(jf/2, l1/2, l2/2, ji/2) coefficient                                  
       */

double FK(int jf, int l1, int l2, int ji, int k){
  double value;
  double cg,w6j;
  int temp;
  temp = (jf-ji)/2 - 1;
  value = PHASE(temp)*sqrt((l1+1)*(l2+1)*(ji+1));
  cg = clebsch_gordan(l1, l2, k, 2, -2, 0);
  value*= cg;
  temp = (ji + ji + l1 + l2)/2;
  w6j=wigner_6j(ji, ji, k, l2, l1, jf);
  value*= PHASE(temp)*w6j;
  //printf("cg(%i,%i,%i,1,-1,0)=%g\n",l1/2,l2/2,k/2,cg);
  //printf("wigner_6j(%i,%i,%i,%i,%i,%i)=%g\n",ji/2,ji/2,k/2,l2/2,l1/2,jf/2,w6j);
  //printf("F%i(%i,%i)=%g\n",k/2,l1/2,l1/2,value);
  return value;
}

       /*
       ** returns the value of the rho_(k/2)(ji/2) coefficient                                  
       */

double rhoK(int ji, double sigma, int k){
  double value;
  int m,temp;
  double sum,cg,pm;
  sum = 0.0;
  value = 0.0;
  for(m=-ji;m<=ji;m+=2)
    sum += exp(-pow(0.5*(double)m/sigma,2.0)/2.0);
  //printf("Pm(%i)=%g\n",ji/2,sum);
  for(m=-ji;m<=ji;m+=2){
    temp=(ji-m)/2;
    cg = clebsch_gordan(ji, ji, k, m, -m, 0);
    //printf("rhoK: cg(%i,%i,%i,%i,%i,0)=%g\n",ji/2,ji/2,k/2,m/2,-m/2,cg);
    pm=exp(-pow(0.5*(double)m/sigma,2.0)/2.0);
    //printf("rhoK: pm=%g\n",pm);
    value+=PHASE(temp)*cg*pm;
  }
  value *= sqrt(ji+1.0)/sum;
  //printf("rho%i(%i)=%g\n",k/2,ji/2,value);
  return value;
}

       /*
       ** returns the value of the a_k coefficients for angular distributions                                  
       */

double aK(int ji, int l1, int l2, int jf, int k, double delta, double sigma){
  double alphaK;
  double FK11,FK12,FK22;
  double value;
  k*=2;

  alphaK=rhoK(ji,sigma,k);
  FK11=FK(jf, l1, l1, ji, k);
  FK12=FK(jf, l1, l2, ji, k);
  FK22=FK(jf, l2, l2, ji, k);
  //printf("F%i(%i,%i)(%i->%i)=%g\n",k/2,l1/2,l1/2,ji/2,jf/2,FK11);
  //printf("F%i(%i,%i)(%i->%i)=%g\n",k/2,l1/2,l2/2,ji/2,jf/2,FK12);
  //printf("F%i(%i,%i)(%i->%i)=%g\n",k/2,l2/2,l2/2,ji/2,jf/2,FK22);
  value=(FK11 + 2.0*delta*FK12 + pow(delta,2.)*FK22)/(1 + pow(delta,2.0));
  value*=alphaK;
  return value;
}

       /*
       ** returns the value of the a_k coefficients for angular correlations                                  
       */

double caK(int ji, int l11, int l21, int j, int l12, int l22, 
           int jf, double delta1, double delta2, int k){
  double FKi11,FKi12,FKi22;
  double FKf11,FKf12,FKf22;
  double value;
  k*=2;

  FKi11=FK(ji, l11, l11, j, k);
  FKi12=FK(ji, l11, l21, j, k);
  FKi22=FK(ji, l21, l21, j, k);
  FKf11=FK(jf, l12, l12, j, k);
  FKf12=FK(jf, l12, l22, j, k);
  FKf22=FK(jf, l22, l22, j, k);
  value=(FKi11 + 2.0*delta1*FKi12 + pow(delta1,2.)*FKi22)/(1 + pow(delta1,2.0));
  value*=(FKf11 + 2.0*delta2*FKf12 + pow(delta2,2.)*FKf22)/(1 + pow(delta2,2.0));
  return value;
}
