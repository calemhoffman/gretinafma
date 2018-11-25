#include <TROOT.h>
#include <TSystem.h>
#include <TStyle.h>
#include <TTree.h>
#include <TFile.h>
#include <TSelector.h>
#include <TMath.h>
#include <TBenchmark.h>
#include <TH2F.h>
#include <TH1F.h>
#include <TF1.h>
#include <TCanvas.h>
#include <TGraph2D.h>
#include <TGraph.h>
#include <TCutG.h>
#include <TRandom.h>
#include <string>
#include <fstream>
#include <math.h>
#include <TRandom.h>
#include <TDatime.h>
#include <TObjArray.h>
#include <TMath.h>

void fmaCalibrate(void) {
  printf("==========================================================\n");
  printf("================= calibrate ic spectra ===================\n");
  printf("==========================================================\n");
  TBenchmark gClock;  
  gClock.Reset(); gClock.Start("gTimer");
  
  /**///======================================================== read fit file in
  ifstream inFile;
  inFile.open("fma_fits.dat");
  Int_t lineRead=0;
  Int_t runNumber[300];
  Int_t tempCounter=0;
  Double_t centroid[300][10];
  Double_t centroidError[300][10];
  Double_t temp;
  Double_t calibrationFactor[300][10];
  Double_t normFactor[3]={2000,1500,2500};
  
  //Reset
  for (Int_t resetID1=0;resetID1<300;resetID1++) {
    runNumber[resetID1]=TMath::QuietNaN();
    for (Int_t resetID2=0;resetID2<10;resetID2++) {
      centroid[resetID1][resetID2] = TMath::QuietNaN();
      centroidError[resetID1][resetID2]=TMath::QuietNaN();
      calibrationFactor[resetID1][resetID2]=TMath::QuietNaN();
    }
  }
  
  if( inFile.is_open() ) {
    while (1) {
      inFile >> runNumber[lineRead] >> temp >> temp >>  centroid[lineRead][tempCounter] >> centroidError[lineRead][tempCounter] >> temp >> temp;
      if (!inFile.good()) break;
      if (lineRead<10) printf("%d %d %d %4.4f %4.4f \n",lineRead,tempCounter,runNumber[lineRead],centroid[lineRead][tempCounter],centroidError[lineRead][tempCounter]);
      tempCounter++; if (tempCounter==3) {lineRead++; tempCounter=0;}
    }
    printf("... done reading fit file\n");
  }else{
    printf("... failed to read fit file\n");
    return;
  }
  inFile.close();

  /**///======================================================== get cal factor
 
  for (Int_t runNumberIndex=0;runNumberIndex<lineRead;runNumberIndex++) {
    for (Int_t detIndex=0;detIndex<3;detIndex++) {
      calibrationFactor[runNumberIndex][detIndex]=centroid[runNumberIndex][detIndex] / normFactor[detIndex];
      printf("run %d, cal factor %1.4f\n",runNumber[runNumberIndex],calibrationFactor[runNumberIndex][detIndex]);
    }
  }
  
  //No need to linear fit yet but for future
  //-----Does a linear fit to two arrays of numbers----//
  /* void linearfit(Int_t nParams=2, Double_t *x=0,Double_t *y=0) { */
  /*   TLinearFitter *lf=new TLinearFitter(nParams); */
  /*   TVectorD params; */
  /*   lf->SetFormula("1++x"); */
  /*   lf->AssignData(nParams,1,x,y); */
  /*   lf->Eval(); */
  /*   lf->GetParameters(params); */
  /*   printf("Offset = %3.5f , Slope = %3.5f\n",params(0),params(1)); */
  /*   printf("Chisqr = %f\n",lf->GetChisquare()); */
    
  /*   Double_t rms=0; */
  /*   for (Int_t i=0;i<nParams;i++){ */
  /*     Double_t temprms = params(1)*x[i]+params(0) - y[i]; */
  /*     temprms = temprms*temprms; */
  /*     rms+=temprms; */
  /*   } */
  /*   rms = TMath::Sqrt(rms / nParams); */
  /*   printf("RMS is %3.6f\n",rms); */
  /* } //end Linear fit */
 
  gClock.Stop("gTimer");
  double gTime =  gClock.GetRealTime("gTimer");
  printf("=========== Finsihed Calibrate in %7.0f sec \n", gTime);
}
