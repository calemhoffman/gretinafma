#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define   FAC_LIM    150 
#define   MAX(a,b)   ( ((a) > (b)) ? (a) : (b) )
#define   MIN(a,b)   ( ((a) < (b)) ? (a) : (b) )
#define   PHASE(a)   (1 - 2 * (abs(a) % 2))
#define   SMALLNUM   1.0E-10

double clebsch_gordan(int j1, int j2, int j3, int m1, int m2, int m3);
       /*
       ** returns the value of the Clebsch-Gordan coefficient                                  
       ** <j1/2, m1/2, j2/2, m2/2 | j3/2, m3/2> 
       */

double wigner_6j(int j1, int j2, int j3, int l1, int l2, int l3);
       /*
       ** returns the value of the Wigner 6j-Symbol coefficient                                  
       ** {j1/2, j2/2, j3/2; l1/2, l2/2, l3/2}
       */

double fac_ratio(int m, int n);
       /*
       ** calculates and returns the ratio (n! / m!).           
       */

double delta(int j1, int j2, int j3);

       /*
       ** returns the value of the B_(k/2)(j/2) coefficient                                  
       */

double BK(int j, int k);

       /*
       ** returns the value of the F_(k/2)(jf/2, l1/2, l2/2, ji/2) coefficient                                  
       */

double FK(int jf, int l1, int l2, int ji, int k);

       /*
       ** returns the value of the rho_(k/2)(ji/2) coefficient                                  
       */

double rhoK(int ji, double sigma, int k);

       /*
       ** returns the value of the a_k coefficients                                  
       */

double aK(int ji, int l1, int l2, int jf, int k, double delta, double sigma);

       /*
       ** returns the value of the ca_k coefficients                                  
       */

double caK(int ji, int l11, int l12, int j, int l21, int l22, int jf, double delta1, double delta2, int k);
