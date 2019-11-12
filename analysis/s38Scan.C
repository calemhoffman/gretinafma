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

#define numHistScan 50

TH1F * hscan[numHistScan];
TH1F *hscanR[5];
TH1F *hscanC[5];

void s38Scan(void){
  for (Int_t i=0;i<5;i++)
  {
    hscanR[i] = new TH1F(Form("hscanR%d",i),Form("hscanR%d",i),4096,0,4096);
    hscanC[i] = new TH1F(Form("hscanC%d",i),Form("hscanC%d",i),4096,0,4096);
  }

  TFile * inFile = new TFile("gamFile.root");
  if (inFile==0) {printf("In File Did Not Open\n"); return;}
  TCanvas *can = new TCanvas("can","can",1600,1000);
  can->Clear();

  //fit parameters
  double fitLow=1285;
  double fitHigh=1305;
  double mean=1292;
  double sigma=5;
  Int_t intgrl[numHistScan];

//Fill
  for (Int_t i=0;i<numHistScan;i++) {
    hscan[i] = (TH1F *)inFile->Get(Form("hscan%d",i));
    fitGaussP1(hscan[i],mean,sigma,fitLow,fitHigh);
    hscan[i]->GetXaxis()->SetRangeUser(fitLow-100,fitHigh+100);
  }

//Sums
  for (Int_t i=0;i<7;i++) {
    hscanR[0]->Add(hscan[i]);
    hscanR[1]->Add(hscan[10+i]);
    hscanR[2]->Add(hscan[20+i]);
  }
  hscanC[0]->Add(hscan[0]);hscanC[0]->Add(hscan[1]);
  hscanC[0]->Add(hscan[2]);hscanC[0]->Add(hscan[3]);
  hscanC[1]->Add(hscan[4]);hscanC[1]->Add(hscan[5]);
  hscanC[1]->Add(hscan[6]);
  hscanC[2]->Add(hscan[7]);hscanC[2]->Add(hscan[8]);
  hscanC[2]->Add(hscan[9]);

  for (Int_t i=0;i<3;i++) {
    fitGaussP1(hscanR[i],mean,sigma,fitLow,fitHigh);
    hscanR[i]->GetXaxis()->SetRangeUser(fitLow-100,fitHigh+100);
    fitGaussP1(hscanC[i],mean,sigma,fitLow,fitHigh);
    hscanC[i]->GetXaxis()->SetRangeUser(fitLow-100,fitHigh+100);
  }
//Draws
  can->Clear(); can->Divide(2,4);
  for (Int_t i=0;i<3;i++) {
    can->cd(i*2+1); hscanR[i]->Draw("");
    can->cd(i*2+2); hscanC[i]->Draw("");
    if (i==0) {
      can->cd(7); hscanR[i]->Draw();
      can->cd(8); hscanC[i]->Draw();
    }
    can->cd(7); hscanR[i]->Draw("same");
    can->cd(8); hscanC[i]->Draw("same");
  }
}
