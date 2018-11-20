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

void fmaDraw(TTree *tree) {

  printf("==========================================================\n");
  printf("================ draw all fma spectra  ===================\n");
  printf("==========================================================\n");
  TBenchmark gClock;  
  gClock.Reset(); gClock.Start("gTimer");

  /**///======================================================== TTree
  int totnumEntry = tree->GetEntries();
  printf("============== Total TTree Entries: %10lld \n", tree->GetEntries());

  /**///======================================================== Canvas
  Int_t Div[2] = {3,1};  //x,y
  Int_t size[2] = {500,500}; //x,y
  TCanvas * cic_e1d = new TCanvas("cic_e1d", "cic_e1d", 0, 0, size[0]*Div[0], size[1]*Div[1]);
  cic_e1d->Divide(Div[0],Div[1]);
  for( int i = 1; i <= Div[0]+Div[1] ; i++){
    cic_e1d->cd(i)->SetGrid();
  }

  /**///======================================================== Histograms
  TH1F ** hic_e1  = new TH1F*[300]; //array of runs
  TH1F ** hic_e2  = new TH1F*[300]; //array of runs
  TH1F ** hic_e3  = new TH1F*[300]; //array of runs
  
  Int_t runNumber=0;//should be set from ttree or in loop
  TString name[3];
  TString title[3];
  for (Int_t i=1;i<4;i++) {
    name[i-1].Form("hic_e%d[%d]",i,runNumber);
    title[i-1].Form("hic_e%d[%d]; energy [arb. units]",i,runNumber);
  }
  
  hic_e1[runNumber]  = new TH1F(name[0] , title[0] , 1000, 50, 3500);
  hic_e2[runNumber]  = new TH1F(name[1] , title[1] , 1000, 50, 3500);
  hic_e3[runNumber]  = new TH1F(name[2] , title[2] , 1000, 50, 3500);
  hic_e1[runNumber]->Reset();
  hic_e2[runNumber]->Reset();
  hic_e3[runNumber]->Reset();
  hic_e1[runNumber]->SetTitle(title[0]);
  hic_e2[runNumber]->SetTitle(title[1]);
  hic_e3[runNumber]->SetTitle(title[2]);
  
  /**///======================================================== Draws
  for (Int_t i=1;i<4;i++) {
    TString draw;
    draw.Form("e%d>>hic_e%d[%d]",i,i,runNumber);
    cic_e1d->cd(i);
    tree->Draw(draw,"","");
  }
  /**///======================================================== Cleanup
  cic_e1d->Modified();
  cic_e1d->Update();
  
  gSystem->ProcessEvents();
	 
  gClock.Stop("gTimer");
  double gTime =  gClock.GetRealTime("gTimer");
  printf("=========== Finsihed, total runTime : %7.0f sec \n", gTime);
  
}
