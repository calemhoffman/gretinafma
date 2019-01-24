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

void fmaCalibrate(FILE * calFileOut=NULL) {
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
  Double_t centroid1[300][10];
  Double_t centroid1Error[300][10];
  Double_t centroid2[300][10];
  Double_t centroid2Error[300][10];
  Double_t temp;
  Double_t calibrationLinear[300][10];
  Double_t normLinear[3]={1750,1500,2500};
  Double_t calibrationOffset[300][10];
  Double_t normOffset[3]={2500,1750,0};
  Double_t calibrationXOffset[300][10];
  
  //Reset
  for (Int_t resetID1=0;resetID1<300;resetID1++) {
    runNumber[resetID1]=TMath::QuietNaN();
    for (Int_t resetID2=0;resetID2<10;resetID2++) {
      centroid1[resetID1][resetID2] = TMath::QuietNaN();
      centroid1Error[resetID1][resetID2]=TMath::QuietNaN();
      calibrationLinear[resetID1][resetID2]=TMath::QuietNaN();
      centroid2[resetID1][resetID2] = TMath::QuietNaN();
      centroid2Error[resetID1][resetID2]=TMath::QuietNaN();
      calibrationOffset[resetID1][resetID2]=TMath::QuietNaN();
      calibrationXOffset[resetID1][resetID2]=TMath::QuietNaN();
    }
  }
  
  if( inFile.is_open() ) {
    while (1) {
      if (tempCounter<2)
	inFile >> runNumber[lineRead] >> centroid1[lineRead][tempCounter] >> centroid1Error[lineRead][tempCounter]
	       >> temp >> temp >> centroid2[lineRead][tempCounter] >> centroid2Error[lineRead][tempCounter]
	  >> temp >> temp;

      if (tempCounter==2)
	inFile >> runNumber[lineRead] >> temp >> temp >> centroid1[lineRead][tempCounter] >> centroid1Error[lineRead][tempCounter]
	       >> temp >> temp ;
      
      if (!inFile.good()) break;
      if (lineRead<10 && tempCounter<2) printf("%d %d %d %4.1f %4.1f \n",lineRead,tempCounter,runNumber[lineRead],centroid1[lineRead][tempCounter],centroid2[lineRead][tempCounter]);
      if (lineRead<10 && tempCounter==2) printf("%d %d %d %4.1f \n",lineRead,tempCounter,runNumber[lineRead],centroid1[lineRead][tempCounter]); 
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
      if (detIndex<2)
	{
	  calibrationLinear[runNumberIndex][detIndex]
	    =(normOffset[detIndex]-normLinear[detIndex])/(centroid2[runNumberIndex][detIndex]-centroid1[runNumberIndex][detIndex]);
	  calibrationOffset[runNumberIndex][detIndex] = normLinear[detIndex];
	  calibrationXOffset[runNumberIndex][detIndex] = centroid1[runNumberIndex][detIndex];
	} else {
	calibrationLinear[runNumberIndex][detIndex] = 0;
	calibrationOffset[runNumberIndex][detIndex] = (normLinear[detIndex]-centroid1[runNumberIndex][detIndex]);
	calibrationXOffset[runNumberIndex][detIndex] = 0;
      }
      /* calibrationFactor[runNumberIndex][detIndex]=centroid[runNumberIndex][detIndex] / normFactor[detIndex]; */
      if (runNumberIndex<10)
	printf("run %d | cal factors | %1.4f %1.4f %1.4f\n",runNumber[runNumberIndex],calibrationOffset[runNumberIndex][detIndex],
	       calibrationLinear[runNumberIndex][detIndex], calibrationXOffset[runNumberIndex][detIndex]);

      fprintf(calFileOut, "%d %d %2.5f %2.5f %2.5f\n", runNumber[runNumberIndex],detIndex,calibrationOffset[runNumberIndex][detIndex],
	      calibrationLinear[runNumberIndex][detIndex], calibrationXOffset[runNumberIndex][detIndex]);
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
