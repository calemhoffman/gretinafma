#include "shell.h"

/*   fac[n] = (n-1)! / 10^n  */
   
static double fac[152] = {0,1.0,
    1.000000000000000e-01,2.000000000000000e-02,6.000000000000000e-03,
    2.400000000000000e-03,1.200000000000000e-03,7.200000000000000e-04,
    5.040000000000000e-04,4.032000000000000e-04,3.628800000000000e-04,
    3.628800000000000e-04,3.991680000000000e-04,4.790016000000000e-04,
    6.227020799999999e-04,8.717829119999999e-04,1.307674368000000e-03,
    2.092278988800000e-03,3.556874280959999e-03,6.402373705727999e-03,
    1.216451004088320e-02,2.432902008176640e-02,5.109094217170943e-02,
    1.124000727777607e-01,2.585201673888497e-01,6.204484017332392e-01,
    1.551121004333098e+00,4.032914611266055e+00,1.088886945041835e+01,
    3.048883446117137e+01,8.841761993739698e+01,2.652528598121909e+02,
    8.222838654177918e+02,2.631308369336934e+03,8.683317618811881e+03,
    2.952327990396040e+04,1.033314796638614e+05,3.719933267899010e+05,
    1.376375309122634e+06,5.230226174666008e+06,2.039788208119743e+07,
    8.159152832478972e+07,3.345252661316379e+08,1.405006117752879e+09,
    6.041526306337380e+09,2.658271574788448e+10,1.196222208654801e+11,
    5.502622159812086e+11,2.586232415111681e+12,1.241391559253607e+13,
    6.082818640342673e+13,3.041409320171336e+14,1.551118753287382e+15,
    8.065817517094384e+15,4.274883284060023e+16,2.308436973392412e+17,
    1.269640335365827e+18,7.109985878048630e+18,4.052691950487719e+19,
    2.350561331282877e+20,1.386831185456897e+21,8.320987112741385e+21,
    5.075802138772245e+22,3.146997326038792e+23,1.982608315404439e+24,
    1.268869321858841e+25,8.247650592082466e+25,5.443449390774428e+26,
    3.647111091818867e+27,2.480035542436829e+28,1.711224524281412e+29,
    1.197857166996989e+30,8.504785885678619e+30,6.123445837688606e+31,
    4.470115461512682e+32,3.307885441519385e+33,2.480914081139538e+34,
    1.885494701666049e+35,1.451830920282858e+36,1.132428117820629e+37,
    8.946182130782970e+37,7.156945704626376e+38,5.797126020747365e+39,
    4.753643337012840e+40,3.945523969720657e+41,3.314240134565352e+42,
    2.817104114380549e+43,2.422709538367272e+44,2.107757298379527e+45,
    1.854826422573984e+46,1.650795516090845e+47,1.485715964481761e+48,
    1.352001527678402e+49,1.243841405464130e+50,1.156772507081641e+51,
    1.087366156656743e+52,1.032997848823905e+53,9.916779348709492e+53,
    9.619275968248208e+54,9.426890448883244e+55,9.332621544394412e+56,
    9.332621544394412e+57,9.425947759838356e+58,9.614466715035122e+59,
    9.902900716486175e+60,1.029901674514562e+62,1.081396758240290e+63,
    1.146280563734708e+64,1.226520203196137e+65,1.324641819451828e+66,
    1.443859583202493e+67,1.588245541522742e+68,1.762952551090244e+69,
    1.974506857221073e+70,2.231192748659812e+71,2.543559733472186e+72,
    2.925093693493014e+73,3.393108684451896e+74,3.969937160808719e+75,
    4.684525849754288e+76,5.574585761207603e+77,6.689502913449123e+78,
    8.094298525273439e+79,9.875044200833596e+80,1.214630436702532e+82,
    1.506141741511140e+83,1.882677176888925e+84,2.372173242880046e+85,
    3.012660018457658e+86,3.856204823625802e+87,4.974504222477285e+88,
    6.466855489220470e+89,8.471580690878815e+90,1.118248651196004e+92,
    1.487270706090685e+93,1.992942746161518e+94,2.690472707318048e+95,
    3.659042881952546e+96,5.012888748274988e+97,6.917786472619484e+98,
    9.615723196941083e+99,134.6201247571752e+99,1898.143759076170e+99,
    26953.64137888161e+99,385437.0717180071e+99,5550293.832739302e+99,
    80479260.57471988e+99,1174997204.390910e+99,17272458904.54638e+99,
    255632391787.2865e+99,3808922637630.568e+99,57133839564458.52e+99};

       /*
       ** The function                                 
       **           clebsch_gordan()                   
       ** returns the value of the Clebsch-Gordan coefficient                                  
       ** <j1/2, m1/2, j2/2, m2/2 | j3/2, m3/2> 
       */

double clebsch_gordan(int j1, int j2, int j3, int m1, int m2, int m3)
{
  double value;       /* The return value */
  int jt1, jt2, jt3, jt4, jt5; /* ang. mom. relations */
  int jw1, jw2, jw3, jw4, jw5, jw6;
  int jz1, jz2, jz3, jz4, jz5, jz6, jz7, jz8, jz9, jz10;

    /* Local variables */

  int     loop_min, loop_max, phase, loop;

  value = 0.0;              /* initialization */

  if(m3!=(m1+m2)) return value;

       /* Test of angular projection relations */

  if((j1 < abs(m1)) || (j2 < abs(m2)) || (j3 < abs(m3)))  return  value;

       /* Test of angular momentum relations  */

  if((j3 > (j1+j2)) || (j3 < abs(j1-j2))) return value;

       /* Definition of loop parameters */

  jt1 = j1 - j3 + m2;
  jt2 = j2 - j3 - m1;
  jt3 = j1 - m1;
  jt4 = j2 + m2;
  jt5 = j1 + j2 - j3;

        /* Loop limits */

  loop_min = MAX( MAX(jt1, jt2) , 0);
  loop_max = MIN( MIN(jt3, jt4) , jt5);

          /* Loop test */

  if( loop_min > loop_max) return  value;

  for (loop = loop_min; loop <= loop_max; loop+=2){
    jw1 = loop/2 + 1;
    jw2 = (jt5 - loop)/2 + 1; 
    jw3 = (jt3 - loop)/2 + 1;
    jw4 = (jt4 - loop)/2 + 1;
    jw5 = (loop - jt2)/2 + 1;
    jw6 = (loop - jt1)/2 + 1;
           /*  test for maximum factorials   */
    if((jw1>FAC_LIM)||(jw2>FAC_LIM)||(jw3>FAC_LIM)||(jw4>FAC_LIM)||(jw5>FAC_LIM)||(jw6>FAC_LIM)){
      printf("\n\nTermination from VCC. - too large factorials\n");
      exit(1);
    }
    phase = PHASE(loop/2);
    value += phase/(fac[jw1]*fac[jw2]*fac[jw3]*fac[jw4]*fac[jw5]*fac[jw6]);
  }
  jz1 = (j1 + j2 - j3)/2 + 1;
  jz2 = (j1 + j3 - j2)/2 + 1;
  jz3 = (j2 + j3 - j1)/2 + 1;
  jz4 = (j1 + m1)/2 + 1;
  jz5 = (j1 - m1)/2 + 1;
  jz6 = (j2 + m2)/2 + 1;
  jz7 = (j2 - m2)/2 + 1;
  jz8 = (j3 + m3)/2 + 1;
  jz9 = (j3 - m3)/2 + 1;
  jz10= (j1 + j2 + j3 + 2)/2 + 1;
           /*  test for maximum factorials   */
  if((jz1>FAC_LIM)||(jz2>FAC_LIM)||(jz3>FAC_LIM)||(jz4>FAC_LIM)||(jz5>FAC_LIM)){
    printf("\n\nTermination from VCC. - too large factorials\n");
    exit(1);
  }
  if((jz6>FAC_LIM)||(jz7>FAC_LIM)||(jz8>FAC_LIM)||(jz9>FAC_LIM)||(jz10>FAC_LIM)){
    printf("\n\nTermination from VCC. - too large factorials\n");
    exit(1);
  }
  value *=sqrt(((double)j3+1.0)*fac[jz1]*fac[jz2]*fac[jz3]*fac[jz4]*fac[jz5]
               *fac[jz6]*fac[jz7]*fac[jz8]*fac[jz9]/fac[jz10]);
  value /=sqrt(10.0);

  if(fabs(value)<SMALLNUM)value=0.0;

  return (value);
} /* End: function clebsch_gordan() */

       /*
       ** The function               
       **      double fac_ratio()    
       ** calculates and returns the ratio (n! / m!).           
       */

double fac_ratio(int m, int n)
{
  int i, high;
  double value;

  value = 1.0;      /* initialization */
  if( n == m)    return (value);          /* Return for n equal m */
  high = MAX(n,m); 
  for (i = MIN(n,m)+1; i <= high; i++) value*= i;
  if (n < m) return (1.0/value);       /* Return for n less  m  */
  return (value);                  /* Return for n greater than m */
} /* End: function fac_ratio() */

       /*
       ** The function               
       **      double wigner_6j()    
       ** returns the value of the Wigner 6j-Symbol coefficient                                  
       ** {j1/2, j2/2, j3/2; l1/2, l2/2, l3/2}
       */

double wigner_6j(int j1, int j2, int j3, int l1, int l2, int l3)
{
  double value, omega;       /* The return value */
  int temp;   /* interchange parameters */
  int jt1, jt2, jt3, jt4, jt5, jt6, jt7; /* ang. mom. relations */
  int jw1, jw2, jw3, jw4, jw5, jw6, jw7, jw8;

    /* Local variables */

  int     loop_min, loop_max, phase, loop;

  value = 0.0;              /* initialization */

  jt1 = j1 + j2 + j3;
  jt2 = j1 + l2 + l3;
  jt3 = l1 + j2 + l3;
  jt4 = l1 + l2 + j3;

  jt5 = j1 + j2 + l1 + l2;
  jt6 = j1 + j3 + l1 + l3;
  jt7 = j2 + j3 + l2 + l3;

       /* Test of angular momentum relations  */

  if(((j1+j2)<j3)||((j1+l2)<l3)||((l1+j2)<l3)||((l1+l2)<j3)){
    //printf("a+b<c\n");
    return value ;
  }

  if((abs(j1-j2)>j3)||(abs(j1-l2)>l3)||(abs(l1-j2)>l3)||(abs(l1-l2)>j3)){
    //printf("|a-b|>c\n");
    return value ;
  }

  if(((jt1 % 2)!=0)||((jt2 % 2)!=0)||((jt3 % 2)!=0)||((jt4 % 2)!=0)){
    //printf("(a+b+c) odd\n");
    return value ;
  }
        /* Loop limits */

  loop_min = MAX( MAX( MAX(jt1, jt2), jt3), jt4);
  loop_max = MIN( MIN(jt5, jt6), jt7);

          /* Loop test */

  if( loop_min > loop_max) return  value;

  if(j3 == 0){
    temp = jt2/2;
    value = PHASE(temp)/sqrt((j1+1.0)*(l2+1.0));
  }
  else if(l3 == 0){
    temp=jt1/2;
    value=PHASE(temp)/sqrt((j1+1.0)*(j2+1.0));
  }
  else{
    omega = 0.0;
    for(loop = loop_min; loop <= loop_max; loop += 2){
      jw1 = loop/2 + 2;
      jw2 = (loop - jt1)/2 + 1;
      jw3 = (loop - jt2)/2 + 1;
      jw4 = (loop - jt3)/2 + 1;
      jw5 = (loop - jt4)/2 + 1;
      jw6 = (jt5 - loop)/2 + 1;
      jw7 = (jt6 - loop)/2 + 1;
      jw8 = (jt7 - loop)/2 + 1;
      if((loop % 4) == 0) phase = 1.0;
      else phase = -1.0;
           /*  test for maximum factorials   */
      if((jw1>FAC_LIM)||(jw2>FAC_LIM)||(jw3>FAC_LIM)||(jw4>FAC_LIM)){
        //printf("\n\nTermination from VCC. - too large factorials\n");
        exit(1);
      }
      if((jw5>FAC_LIM)||(jw6>FAC_LIM)||(jw7>FAC_LIM)||(jw8>FAC_LIM)){
        //printf("\n\nTermination from VCC. - too large factorials\n");
        exit(1);
      }
      omega += phase*fac[jw1]/(fac[jw2]*fac[jw3]*fac[jw4]*fac[jw5]*fac[jw6]
                    *fac[jw7]*fac[jw8]);
    }
    value = omega*delta(j1,j2,j3)*delta(j1,l2,l3)*delta(l1,j2,l3)*delta(l1,l2,j3)*10.0;
  }
  return value;
}

double delta(int j1, int j2, int j3){
  int jw1,jw2,jw3,jw4;
  double value;

  jw1=(j1 + j2 - j3)/2 + 1;
  jw2=(j1 - j2 + j3)/2 + 1;
  jw3=(j3 + j2 - j1)/2 + 1;
  jw4=(j1 + j2 + j3 + 2)/2 + 1;
       /*  test for maximum factorials   */
  if((jw1>FAC_LIM)||(jw2>FAC_LIM)||(jw3>FAC_LIM)||(jw4>FAC_LIM)){
    //printf("\n\nTermination from VCC. - too large factorials\n");
    exit(1);
  }
  value = sqrt(fac[jw1]*fac[jw2]*fac[jw3]/(fac[jw4]*10.0));
  return value;
}

