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

#include "AutoFit.C"

#define numHistScan 10000

TH1F * hscan[numHistScan];
FILE * fitFileOut;

TH2F *hScanData;

Float_t bins=80;
Float_t delta=40;
  

int gamScanFit(void) {
  //Get the scan fill data - mathes the loops in fmaCuts.C
  Float_t x[numHistScan];
  Float_t y[numHistScan];

  for (Int_t i=0;i<=bins;i++) {
    for (Int_t j=0;j<=bins;j++) {
      Int_t id = i*bins+j;
      x[id] = (j*delta+delta/2.0);
      y[id] = (i*delta+delta/2.0);
    }
  }

  //2d out  histo
  hScanData = new TH2F("hScanData","hScanData",600,0,6000,600,0,6000);

  
  //canvas
   TCanvas *can = new TCanvas("can","can",1200,500);

   // open text fit file to fill up
   fitFileOut = fopen ("scan_fits.dat", "w+");
     
  //open file read in hist, fit it, spit out results
  TFile * inFile = new TFile("g.root");
  if (inFile == 0) {printf("In File Did Not Open\n"); return 1;}

  //try some fitting
    /* double fitLow=660; */
    /* double fitHigh=680; */
    /* double mean=670; */
    /* double sigma=10; */
    /* Int_t intgrl[numHistScan]; */
     double fitLow=285;
    double fitHigh=298;
    double mean=292;
    double sigma=5;
    Int_t intgrl[numHistScan];
    
  for (Int_t i=0;i<numHistScan;i++) {
    //pull histo
    hscan[i] = (TH1F *)inFile->Get(Form("hscan_%d",i));
    //get integral to determine binning [CHECK]
    intgrl[i] = hscan[i]->Integral(100,7000);
    if (intgrl[i]<1e5)
      hscan[i]->Rebin();
    if (intgrl[i]<1e4)
      hscan[i]->Rebin();
    if (intgrl[i]<1e3)
      hscan[i]->Rebin();

    
    if (intgrl[i]>1e2) {
      fprintf(fitFileOut, "%d ", i);
      fitGaussP1(hscan[i],mean,sigma,fitLow,fitHigh,fitFileOut,x[i],y[i]);
      //      can->SaveAs(Form("fit_%d.pdf",i));
    }
    printf("%d\n\n",i);
  }

  fprintf(fitFileOut, "\n");
  //try some fitting
  /* fitLow=1800; */
  /* fitHigh=1845; */
  /* mean=1823; */
  /* sigma=10; */
  fitLow=2020;
  fitHigh=2070;
  mean=2044;
  sigma=8;

 for (Int_t i=0;i<numHistScan;i++) {
  
   if (intgrl[i]>1e2) {
     fprintf(fitFileOut, "%d ", i);
     fitGaussP1(hscan[i],mean,sigma,fitLow,fitHigh,fitFileOut,x[i],y[i]);
     //      can->SaveAs(Form("fit_%d.pdf",i));
   } 
 }

  fprintf(fitFileOut, "\n");
  //try some fitting
  /* fitLow=2150; */
  /* fitHigh=2190; */
  /* mean=2168; */
  /* sigma=10; */
  fitLow=1120;
  fitHigh=1150;
  mean=1133;
  sigma=6;

 for (Int_t i=0;i<numHistScan;i++) {
  
   if (intgrl[i]>1e2) {
     fprintf(fitFileOut, "%d ", i);
     fitGaussP1(hscan[i],mean,sigma,fitLow,fitHigh,fitFileOut,x[i],y[i]);
     //      can->SaveAs(Form("fit_%d.pdf",i));
   } 
 }


  fprintf(fitFileOut, "\n");
  //try some fitting
  fitLow=1277;
  fitHigh=1302;
  mean=1292;
  sigma=4;

 for (Int_t i=0;i<numHistScan;i++) {
   hscan[i]->Rebin();
   if (intgrl[i]>1e1) {
     fprintf(fitFileOut, "%d ", i);
     fitGaussP1(hscan[i],mean,sigma,fitLow,fitHigh,fitFileOut,x[i],y[i]);
     //      can->SaveAs(Form("fit_%d.pdf",i));
   } 
 }
 
  fprintf(fitFileOut, "\n");
  //try some fitting
  fitLow=2359;
  fitHigh=2395;
  mean=2375;
  sigma=7;

 for (Int_t i=0;i<numHistScan;i++) {
   hscan[i]->Rebin();
   if (intgrl[i]>1e1) {
     fprintf(fitFileOut, "%d ", i);
     fitGaussP1(hscan[i],mean,sigma,fitLow,fitHigh,fitFileOut,x[i],y[i]);
     //      can->SaveAs(Form("fit_%d.pdf",i));
   } 
 }

  return 0;
}
