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

TH1F * hscan[1000];
FILE * fitFileOut;

TH2F *hScanData;
  

int gamScanFit(void) {
  //Get the scan fill data - mathes the loops in fmaCuts.C
  Float_t x[1000];
  Float_t y[1000];

  for (Int_t i=0;i<=30;i++) {
    for (Int_t j=0;j<=30;j++) {
      Int_t id = i*30+j;
      x[id] = (j*200+100);
      y[id] = (i*200+100);
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

  for (Int_t i=0;i<1000;i++) {
    //pull histo
    hscan[i] = (TH1F *)inFile->Get(Form("hscan_%d",i));
    //get integral to determine binning [CHECK]
    Int_t intgrl = hscan[i]->Integral(100,7000);
    if (intgrl<1e5)
      hscan[i]->Rebin();
    if (intgrl<1e4)
      hscan[i]->Rebin();
    if (intgrl<1e3)
      hscan[i]->Rebin();

    //try some fitting
    double fitLow=660;
    double fitHigh=680;
    double mean=670;
    double sigma=10;

   
    if (intgrl>1e2) {
      fprintf(fitFileOut, "%d ", i);
      fitGaussP1(hscan[i],mean,sigma,fitLow,fitHigh,fitFileOut);
      //      can->SaveAs(Form("fit_%d.pdf",i));
    }
  }


  return 0;
}
