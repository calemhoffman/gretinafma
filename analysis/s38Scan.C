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
  TCanvas *can = new TCanvas("can","can",1200,900);
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

  //Fits - need params for all 6 spectra
  //s38
  //1292
  mean=1292;sigma=3;fitLow=1250;fitHigh=1350;
  for (Int_t i=0;i<3;i++) {
    hscanR[i]->GetXaxis()->SetRangeUser(fitLow-100,fitHigh+100);
    hscanC[i]->GetXaxis()->SetRangeUser(fitLow-100,fitHigh+100);
    hscanR[i]->SetLineColor(i+1);
    hscanC[i]->SetLineColor(i+1);
  }
  fitGaussP1(hscanR[0],mean,sigma,fitLow,fitHigh);
  fitLow=1240;fitHigh=1400;fitGaussP1(hscanR[1],mean,sigma,fitLow,fitHigh);
  sigma=2;fitLow=1275;fitHigh=1305;fitGaussP1(hscanR[2],mean,sigma,fitLow,fitHigh);

  sigma=3;fitLow=1250;fitHigh=1350;fitGaussP1(hscanC[0],mean,sigma,fitLow,fitHigh);
  fitGaussP1(hscanC[1],mean,sigma,fitLow,fitHigh);
  //fitGaussP1(hscanC[2],mean,sigma,fitLow,fitHigh);
  fit2GaussP1(hscanC[2],1292,2,1300,2,1250,1350,0);

  //1533
  mean=1534;sigma=3;fitLow=1490;fitHigh=1560;
  for (Int_t i=0;i<3;i++) {
    hscanR[i]->GetXaxis()->SetRangeUser(fitLow-100,fitHigh+100);
    hscanC[i]->GetXaxis()->SetRangeUser(fitLow-100,fitHigh+100);
    hscanR[i]->SetLineColor(i+1);
    hscanC[i]->SetLineColor(i+1);
  }
  fitGaussP1(hscanR[0],mean,sigma,fitLow,fitHigh);
  fitGaussP1(hscanR[1],mean,sigma,fitLow,fitHigh);
  fitLow=1510;fitHigh=1548;fitGaussP1(hscanR[2],mean,sigma,fitLow,fitHigh);

  fitLow=1490;fitHigh=1560;fitGaussP1(hscanC[0],mean,sigma,fitLow,fitHigh);
  fitGaussP1(hscanC[1],mean,sigma,fitLow,fitHigh);
  fitGaussP1(hscanC[2],mean,sigma,fitLow,fitHigh);

  //33P - 1432
  mean=1432;sigma=3;fitLow=1300;fitHigh=1530;
  for (Int_t i=0;i<3;i++) {
    hscanR[i]->GetXaxis()->SetRangeUser(fitLow-100,fitHigh+100);
    hscanC[i]->GetXaxis()->SetRangeUser(fitLow-100,fitHigh+100);
    hscanR[i]->SetLineColor(i+1);
    hscanC[i]->SetLineColor(i+1);
  }
  fitGaussP1(hscanR[0],mean,sigma,fitLow,fitHigh);
  fitLow=1325;fitHigh=1525;
  fitGaussP1(hscanR[1],mean,sigma,fitLow,fitHigh);
  fitLow=1416;fitHigh=1470;fitGaussP1(hscanR[2],mean,sigma,fitLow,fitHigh);

  fitGaussP1(hscanC[0],mean,sigma,fitLow,fitHigh);
  fitGaussP1(hscanC[1],mean,sigma,fitLow,fitHigh);
  fitGaussP1(hscanC[2],mean,sigma,fitLow,fitHigh);

  //33P - 1848
  mean=1848;sigma=3;fitLow=1750;fitHigh=1950;
  for (Int_t i=0;i<3;i++) {
    hscanR[i]->GetXaxis()->SetRangeUser(fitLow-100,fitHigh+100);
    hscanC[i]->GetXaxis()->SetRangeUser(fitLow-100,fitHigh+100);
    hscanR[i]->SetLineColor(i+1);
    hscanC[i]->SetLineColor(i+1);
  }
  fitGaussP1(hscanR[0],mean,sigma,fitLow,fitHigh);
  fitGaussP1(hscanR[1],mean,sigma,fitLow,fitHigh);
  fitGaussP1(hscanR[2],mean,sigma,fitLow,fitHigh);

  fitGaussP1(hscanC[0],mean,sigma,fitLow,fitHigh);
  fitGaussP1(hscanC[1],mean,sigma,fitLow,fitHigh);
  fitGaussP1(hscanC[2],mean,sigma,fitLow,fitHigh);

  //38Cl - 755
  mean=755;sigma=1.5;fitLow=700;fitHigh=800;
  for (Int_t i=0;i<3;i++) {
    hscanR[i]->GetXaxis()->SetRangeUser(fitLow-100,fitHigh+100);
    hscanC[i]->GetXaxis()->SetRangeUser(fitLow-100,fitHigh+100);
    hscanR[i]->SetLineColor(i+1);
    hscanC[i]->SetLineColor(i+1);
  }
  fitGaussP1(hscanR[0],mean,sigma,fitLow,fitHigh);
  fitGaussP1(hscanR[1],mean,sigma,fitLow,fitHigh);
  fitGaussP1(hscanR[2],mean,sigma,fitLow,fitHigh);

  fitGaussP1(hscanC[0],mean,sigma,fitLow,fitHigh);
  fitGaussP1(hscanC[1],mean,sigma,fitLow,fitHigh);
  fitGaussP1(hscanC[2],mean,sigma,fitLow,fitHigh);

  //38Cl - 3142
  mean=3142;sigma=3;fitLow=3100;fitHigh=3200;
  for (Int_t i=0;i<3;i++) {
    hscanR[i]->GetXaxis()->SetRangeUser(fitLow-100,fitHigh+100);
    hscanC[i]->GetXaxis()->SetRangeUser(fitLow-100,fitHigh+100);
    hscanR[i]->SetLineColor(i+1);
    hscanC[i]->SetLineColor(i+1);
  }
  fitGaussP1(hscanR[0],mean,sigma,fitLow,fitHigh);
  fitGaussP1(hscanR[1],mean,sigma,fitLow,fitHigh);
  fitGaussP1(hscanR[2],mean,sigma,fitLow,fitHigh);

  fitGaussP1(hscanC[0],mean,sigma,fitLow,fitHigh);
  fitGaussP1(hscanC[1],mean,sigma,fitLow,fitHigh);
  fitGaussP1(hscanC[2],mean,sigma,fitLow,fitHigh);

  //38Ar - 1643
  mean=1643;sigma=3;fitLow=1620;fitHigh=1662;
  for (Int_t i=0;i<3;i++) {
    hscanR[i]->GetXaxis()->SetRangeUser(fitLow-100,fitHigh+100);
    hscanC[i]->GetXaxis()->SetRangeUser(fitLow-100,fitHigh+100);
    hscanR[i]->SetLineColor(i+1);
    hscanC[i]->SetLineColor(i+1);
  }
  fitGaussP1(hscanR[0],mean,sigma,fitLow,fitHigh);
  fitGaussP1(hscanR[1],mean,sigma,fitLow,fitHigh);
  fitGaussP1(hscanR[2],mean,sigma,fitLow,fitHigh);

  fitGaussP1(hscanC[0],mean,sigma,fitLow,fitHigh);
  fitGaussP1(hscanC[1],mean,sigma,fitLow,fitHigh);
  fitGaussP1(hscanC[2],mean,sigma,fitLow,fitHigh);

  //38Ar - 2168
  mean=2168;sigma=3;fitLow=2140;fitHigh=2200;
  for (Int_t i=0;i<3;i++) {
    hscanR[i]->GetXaxis()->SetRangeUser(fitLow-100,fitHigh+100);
    hscanC[i]->GetXaxis()->SetRangeUser(fitLow-100,fitHigh+100);
    hscanR[i]->SetLineColor(i+1);
    hscanC[i]->SetLineColor(i+1);
  }
  fitGaussP1(hscanR[0],mean,sigma,fitLow,fitHigh);
  fitGaussP1(hscanR[1],mean,sigma,fitLow,fitHigh);
  fitGaussP1(hscanR[2],mean,sigma,fitLow,fitHigh);

  fitGaussP1(hscanC[0],mean,sigma,fitLow,fitHigh);
  fitGaussP1(hscanC[1],mean,sigma,fitLow,fitHigh);
  fitGaussP1(hscanC[2],mean,sigma,fitLow,fitHigh);

//Draws
  can->Clear(); can->Divide(2,4);
  for (Int_t i=0;i<3;i++) {
    can->cd(i*2+1); hscanR[i]->Draw("");
    can->cd(i*2+2); hscanC[i]->Draw("");
  }
  can->cd(7); hscanR[2]->Draw(); hscanR[1]->Draw("same"); hscanR[0]->Draw("same");
  can->cd(8); hscanC[1]->Draw(); hscanC[2]->Draw("same"); hscanC[0]->Draw("same");


fitLow=2000;fitHigh=4000;
  for (Int_t i=0;i<3;i++) {
    hscanR[i]->GetXaxis()->SetRangeUser(fitLow,fitHigh);
    hscanC[i]->GetXaxis()->SetRangeUser(fitLow,fitHigh);
    hscanR[i]->SetLineColor(i+1);
    hscanC[i]->SetLineColor(i+1);
  }

  intgrl[0] = hscanR[0]->Integral(fitLow,fitHigh);
  intgrl[2] = hscanR[2]->Integral(fitLow,fitHigh);
  float scaleFactor = (Float_t)intgrl[0]/(Float_t)intgrl[2];
  hscanR[2]->Scale(scaleFactor);

  can->Clear(); can->Divide(2,3);
  can->cd(1); hscanR[0]->Draw(); can->cd(3); hscanR[2]->Draw("hist");
  can->cd(2); hscanC[0]->Draw(); can->cd(4); hscanC[2]->Draw();
  can->cd(5); hscanR[2]->Draw("hist"); hscanR[0]->Draw("same");
  can->cd(6); hscanC[2]->Draw(); hscanC[0]->Draw("same");



}
