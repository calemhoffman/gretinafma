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

void fmaFit(TTree *tree, Int_t runNumber = 0, FILE * fitFileOut = NULL) {

  printf("==========================================================\n");
  printf("================= fit all fma spectra  ===================\n");
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
  Div[0]=2; Div[1]=2;
  TCanvas * cic_e2d = new TCanvas("cic_e2d", "cic_e2d", 0, 0, size[0]*Div[0], size[1]*Div[1]);
  cic_e2d->Divide(Div[0],Div[1]);
  for( int i = 1; i <= Div[0]+Div[1] ; i++){
    cic_e2d->cd(i)->SetGrid();
  }

  /**///======================================================== Histograms
  TH1F ** hic_e1  = new TH1F*[300]; //array of runs
  TH1F ** hic_e2  = new TH1F*[300]; //array of runs
  TH1F ** hic_e3  = new TH1F*[300]; //array of runs
  TH2F ** hic_e1e3 = new TH2F*[300]; //array of runs?
  
  //  Int_t runNumber=0;//should be set from ttree or in loop
  TString name[3];
  TString title[3];
  for (Int_t i=1;i<4;i++) {
    name[i-1].Form("hic_e%d_%d",i,runNumber);
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

  TString name2d;
  TString title2d;
  name2d.Form("hic_e1e3_%d",runNumber);
  title2d.Form("hic_e1e3_%d; e3; e1",runNumber);
  hic_e1e3[runNumber] = new TH2F(name2d,title2d,500,10,5010,500,10,5010);

 /**///======================================================== Cuts?
  TCutG* cutG[10]; //!
  TFile * inFileCut = new TFile("fmaCuts.root");
  Int_t numberCuts = 0 ;
  TObjArray * cutList;
  TString cutName;
  Bool_t isCutFileOpen;
  vector<int> countFromCut;
  Int_t cutOption=0;
  isCutFileOpen = inFileCut->IsOpen();
  
  if(isCutFileOpen){
    cutList = (TObjArray *) inFileCut->FindObjectAny("cutList");
    numberCuts = cutList->GetEntries();
    printf("=========== found %d cutG in %s \n", numberCuts, inFileCut->GetName());
    
    for(int numCutIndex = 0; numCutIndex < numberCuts ; numCutIndex++){
      printf(" cut name : %s , VarX: %s, VarY: %s, numPoints: %d \n",
	     cutList->At(numCutIndex)->GetName(),
	     ((TCutG*)cutList->At(numCutIndex))->GetVarX(),
	     ((TCutG*)cutList->At(numCutIndex))->GetVarY(),
	     ((TCutG*)cutList->At(numCutIndex))->GetN());
      cutG[numCutIndex] = (TCutG *)cutList->At(numCutIndex);
      cutName.Form("%s",cutList->At(numCutIndex)->GetName());
    }
    inFileCut->Close();
  } else {
    cutName.Form("");
    //printf(" ======== create cuts file ?? 1:0 (y/n) ========\n");
    
    //int temp = scanf("%d",&cutOption);
    //if (cutOption == 1) {
      //fmaCuts(inFileCut);
    //}
  }
  
  /**///======================================================== Draws
  TString varX,varY,draw;
  cutList = new TObjArray();
  
  for (Int_t i=1;i<4;i++) {
    varX.Form("e%d",i);
    draw.Form("%s>>hic_e%d_%d",varX.Data(),i,runNumber);
    cic_e1d->cd(i);
    tree->Draw(draw,cutName,"");
  }
  
  cic_e2d->cd();
  cic_e2d->Clear();
  varX.Form("e3"); varY.Form("e1");
  draw.Form("%s:%s>>hic_%s%s_%d",
	    varY.Data(),varX.Data(),
	    varY.Data(),varX.Data(),
	    runNumber);
  tree->Draw(draw,cutName,"col");

  /**///======================================================== Fits
 
  //fprintf(fitFileOut, "#runNumber   counts   err   mean   err   sigma   err\n");
  Double_t mean=1750; Double_t fitLow=1500; Double_t fitHigh=2000;

  cic_e1d->cd(1);
  fprintf(fitFileOut, "%d ", runNumber);
  fitGauss(hic_e1[runNumber],mean,50,fitLow,fitHigh,fitFileOut);
  hic_e1[runNumber]->GetXaxis()->SetRangeUser(fitLow,fitHigh);
 
  mean=1425; fitLow=1000; fitHigh=2000;
  cic_e1d->cd(2);
  fprintf(fitFileOut, "%d ", runNumber);
  fitGauss(hic_e2[runNumber],mean,50,fitLow,fitHigh,fitFileOut);
  hic_e2[runNumber]->GetXaxis()->SetRangeUser(fitLow,fitHigh);

  mean=2250; fitLow=1250; fitHigh=3300;
  cic_e1d->cd(3);
  fprintf(fitFileOut, "%d ", runNumber);
  fitGauss(hic_e3[runNumber],mean,100,fitLow,fitHigh,fitFileOut);
  hic_e3[runNumber]->GetXaxis()->SetRangeUser(fitLow,fitHigh);

  fprintf(fitFileOut, "\n");
  /**///======================================================== Cleanup
  cic_e1d->Modified();
  cic_e1d->Update();
  cic_e1d->Print(Form("figures/cic_e1d_%d.pdf",runNumber),"pdf");
  cic_e2d->Modified();
  cic_e2d->Update();
  
  gSystem->ProcessEvents();
	 
  gClock.Stop("gTimer");
  double gTime =  gClock.GetRealTime("gTimer");
  printf("=========== Finsihed, total runTime : %7.0f sec \n", gTime);
  
}
