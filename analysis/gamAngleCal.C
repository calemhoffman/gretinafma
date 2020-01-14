#include <TROOT.h>
#include <TChain.h>
#include <TTree.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TStyle.h>
#include <TH2F.h>
#include <TH1F.h>
#include <TF1.h>
#include <TMath.h>
#include <TSpectrum.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <fstream>
#include <TProof.h>

//#include "AutoFit.C"

TCanvas *cc;
Float_t normFactor[20][2];
TH1D *hg[50];
Float_t binLow;
Float_t binHigh;
char * name("Cal");
Int_t numAngles=10;
Double_t maxYvalue=0;
FILE * fitFileOut;
TH2F *hgg;

void gamAngleCal(void) {
  // TFile * inFile = new TFile("gamCalFile.root");
  // if (inFile==0) {printf("In File Did Not Open\n"); return;}
  // hgg = (TH2F *)inFile->Get("hgAddBackVsAngle0");
  // inFile->Close();

  for (Int_t i=0;i<20;i++) {
    normFactor[i][0]=1;
    normFactor[i][1]=0.0001;
  }


  Double_t mean[10]={121.5,344,1408};
  Double_t fitLow[10]={100,320,1390};
  Double_t fitHigh[10]={140,360,1440};

  cc = new TCanvas("cc","cc",1200,900);
  cc->Clear();
  cc->Divide(4,3);

  for (Int_t whichGam=0;whichGam<3;whichGam++) {
    //fprintf(fitFileOut, "// %f \n", mean[whichGam]);
    fitFileOut = fopen ("gamAngleCal.dat", "w+");
    for (Int_t i = 0;i<numAngles; i++) {
      cc->cd(i+1);
      hg[i] = new TH1D(Form("hg%s_%d",name,i),Form("hg%s_%d",name,i),4096,0,4096);
      binLow = 65.0 + (100.0/(Float_t)numAngles) * (Float_t)i;
      binHigh = 65.0 + (100.0/(Float_t)numAngles) + (100.0/(Float_t)numAngles) * (Float_t)i;
      hgAddBackVsAngle0->ProjectionX(Form("hg%s_%d",name,i),binLow,binHigh);

      fprintf(fitFileOut, "%f ", (binHigh+binLow)/2.0);
      fitGaussP1(hg[i],mean[whichGam],1,fitLow[whichGam],fitHigh[whichGam],fitFileOut);
  //fitGauss(hgndva0[i],mean[whichGam],3,fitLow[whichGam],fitHigh[whichGam],fitFileOut);

      hg[i]->GetXaxis()->SetRangeUser(fitLow[whichGam]-50,fitHigh[whichGam]+50);
      hg[i]->GetYaxis()->SetRangeUser(0,100000);
      hg[i]->Draw();

    }

    fflush(fitFileOut);
    fclose(fitFileOut);

    //Fitting
    ifstream inFile;
    inFile.open("gamAngleCal.dat");
    Float_t angleData[100][10];
    Int_t index=0;
    Double_t x[100];
    Double_t xerr[100];
    Double_t y[100];
    Double_t yerr[100];
    Double_t tempErr1=0;
    Double_t tempErr2=0;
    Double_t average=0;

    if( inFile.is_open() ) {
      while (1) {
        if (!inFile.good()) break;
        inFile >> angleData[index][0] >> angleData[index][1] >> angleData[index][2] >> angleData[index][3] >>
        angleData[index][4] >> angleData[index][5] >> angleData[index][6];
        printf("%f %f\n",angleData[index][0],angleData[index][1]/normFactor[index][0]);
        average+=angleData[index][1];
        index++;
      }
      printf("... done reading fit file\n");
    } else {
      printf("... failed to read fit file\n");
    }

    average/=(Double_t)index;

    for (Int_t index2=0;index2<index-1;index2++) {
      x[index2] = (TMath::Cos(TMath::Pi()*angleData[index2][0]/180.0));
      y[index2] = (Double_t)angleData[index2][1]/(Double_t)normFactor[index2][0]/average;
      xerr[index2] = 0.001;
      tempErr1 = (Double_t)((angleData[index2][2]/angleData[index2][1])*(angleData[index2][2]/angleData[index2][1]));
      tempErr2 = (Double_t)((normFactor[index2][1]/normFactor[index2][0])*(normFactor[index2][1]/normFactor[index2][0]));
      yerr[index2] = y[index2] * TMath::Sqrt(tempErr1 + tempErr2);
    }

    TGraphErrors * gr = new TGraphErrors(numAngles,x,y,xerr,yerr);
    cc->cd(12);
    gr->Draw("ALP");
    gr->SetMarkerColor(4);
    gr->SetMarkerStyle(21);
    gr->GetXaxis()->SetRangeUser(-1,1);
    //gr->GetYaxis()->SetRangeUser(0,1000);
    gr->Draw("ALP");
    cc->Update();
    cc->SaveAs(Form("can%d.pdf",whichGam));
  }
}
