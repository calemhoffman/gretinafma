{
  Float_t gates[100][3] =  //e, low, high
  {{1293,1286,1299},//0 x
  {1535,1529,1540},//1 x
  {850,845,854},//2 x
  {2668,2658,2680},//3 x
  {384,380,387},//4 x
  {438,435,442},//5 x
  {559,554,563},//6 x
  {760,756,762},//7 - may have cl contam x
  {780,776,783},//8 x
  {810,804,814},//9 not sure about this One x
  {822,819,824},//10 weak x
  {830,826,834},//11 x
  {887,883,890},//12 x
  {1020,1014,1023},//13 doubled w/ 1013?cl38 1020 too x
  {1067,1063,1072},//14 not sure about this one x
  {1457,1452,1459},//15 x
  {1512,1505,1516},//16 x
  {1577,1572,1582},//17 x
  {1609,1605,1614},//18 x
  {1617,1614,1621},//19 x
  {1625,1621,1630},//20 x
  {1675,1664,1677},//21 centroid seems off for hg3
  {1950,1944,1959},//22
  {2057,2050,2061},//23
  {2323,2312,2330},//24
  {2365,2358,2371},//25
  {2385,2378,2392},//26
  {2804,2792,2806},//27
  {2225,2220,2230}//28
  }; //end gates
  Int_t numgammas=28;

  Float_t levels[100] = {0.0,1293,2806,2827,3375,3615,
    3657,3677,3999,4336,4437,4478,5064,5278,5456,6006,
    6014,6346,6605,7082,7963,8730,
    3515};
Int_t numlevels= 16;
Float_t diff=0;
  for (Int_t i=0;i<numlevels+1;i++) {
    for (Int_t j=0;j<numlevels+1;j++) {
      diff = TMath::Abs(levels[j]-levels[i]);
      for (Int_t k=0;k<numgammas+1;k++) {
        if ((TMath::Abs(diff-gates[k][0]))<4) {
          printf("j: %.0f i:%.0f d: %.0f g: %.0f\n",
          levels[j],levels[i],diff,gates[k][0]);
        }
      }
    }
  }

  diff=0;
  Float_t test=1293+1512+810+1355+383;
    for (Int_t i=0;i<numlevels+1;i++) {
        diff = TMath::Abs(test-levels[i]);
        //for (Int_t k=0;k<29;k++) {
        //  if ((TMath::Abs(diff-gates[k][0]))<4) {
            printf("i:%.0f d: %.0f\n",
            levels[i],diff);
            for (Int_t k=0;k<numgammas+1;k++) {
              if ((TMath::Abs(diff-gates[k][0]))<4) {
                printf("**********\n") ;
              }
            }
      }


}
