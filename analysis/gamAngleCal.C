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

TCanvas *cc[20];
Float_t normFactor[20][2];
TH1D *hg[50];
Float_t binLow;
Float_t binHigh;
char * name("Cal");
Int_t numAngles=6;
Double_t maxYvalue=0;
FILE * fitFileOut;
TH2F *hgg;
int const gamN=12;

void gamAngleCal(void) {
  // TFile * inFile = new TFile("gamCalFile.root");
  // if (inFile==0) {printf("In File Did Not Open\n"); return;}
  // hgg = (TH2F *)inFile->Get("hgAddBackVsAngle0");
  // inFile->Close();

  Double_t finalNorm[20][20];//whichGam, data
  Double_t finalErr[20][20];
  TGraphErrors * gr[20];

  for (Int_t i=0;i<20;i++) {
    normFactor[i][0]=1;
    normFactor[i][1]=0.0001;
  }


  Double_t mean[20]={121.5,245,344,444.0,779.0,964.1,1112.0,1408,2598,3009,3202,3452};
  Double_t sig[20]={1,1.0,1.0,1.0,1.1,1.2,1.3,1.5,2,2,2,2.2};
  Double_t fitLow[20]={115,230,320,424.0,759.0,950,1092,1390,2578,2990,3170,3415};
  Double_t fitHigh[20]={130,260,360,464.0,799.0,980,1132.0,1440,2618,3029,3225,3485};


  for (Int_t whichGam=0;whichGam<gamN;whichGam++) {
    //fprintf(fitFileOut, "// %f \n", mean[whichGam]);
    fitFileOut = fopen (Form("gamAngleCal%d.dat",whichGam), "w+");
    cc[whichGam] = new TCanvas(Form("cc%d",whichGam),Form("cc%d",whichGam),1200,900);
    cc[whichGam]->Clear();
    cc[whichGam]->Divide(4,3);
    for (Int_t i = 0;i<numAngles; i++) {
      cc[whichGam]->cd(i+1);
      hg[i] = new TH1D(Form("hg%s_%d",name,i),Form("hg%s_%d",name,i),4096,0,4096);
      binLow = 65.0 + (100.0/(Float_t)numAngles) * (Float_t)i;
      binHigh = 65.0 + (100.0/(Float_t)numAngles) + (100.0/(Float_t)numAngles) * (Float_t)i;
      if (mean[whichGam]<1500) {
        hgAddBackVsAngle0->ProjectionX(Form("hg%s_%d",name,i),binLow,binHigh);
      } else {
        hgAddBackVsAngle1->ProjectionX(Form("hg%s_%d",name,i),binLow,binHigh);
      }
      fprintf(fitFileOut, "%f ", (binHigh+binLow)/2.0);
      fitGaussP1(hg[i],mean[whichGam],sig[whichGam],fitLow[whichGam],fitHigh[whichGam],fitFileOut);
  //fitGauss(hgndva0[i],mean[whichGam],3,fitLow[whichGam],fitHigh[whichGam],fitFileOut);

      hg[i]->GetXaxis()->SetRangeUser(fitLow[whichGam]-50,fitHigh[whichGam]+50);
      hg[i]->GetYaxis()->SetRangeUser(0,300);
      hg[i]->Draw();

    }

    fflush(fitFileOut);
    fclose(fitFileOut);

    //Fitting
    ifstream inFile;
    inFile.open(Form("gamAngleCal%d.dat",whichGam));
    Float_t angleData[100][20];
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
      x[index2] = angleData[index2][0];//(TMath::Cos(TMath::Pi()*angleData[index2][0]/180.0));
      y[index2] = (Double_t)angleData[index2][1]/average;//(Double_t)angleData[6][1];//average;
      xerr[index2] = 0.001;
      tempErr1 = (Double_t)((angleData[index2][2]/angleData[index2][1])*(angleData[index2][2]/angleData[index2][1]));
      tempErr2 = (Double_t)((normFactor[index2][1]/normFactor[index2][0])*(normFactor[index2][1]/normFactor[index2][0]));
      yerr[index2] = y[index2] * TMath::Sqrt(tempErr1 + tempErr2);
      finalNorm[whichGam][index2] = y[index2];
      finalErr[whichGam][index2] = yerr[index2];
    }

    gr[whichGam] = new TGraphErrors(numAngles,x,y,xerr,yerr);
    cc[whichGam]->cd(12);
    gr[whichGam]->Draw("ALP");
    gr[whichGam]->SetMarkerColor(kBlue+whichGam);
    gr[whichGam]->SetMarkerStyle(21);
    gr[whichGam]->GetXaxis()->SetRangeUser(60,180);
    //gr->GetYaxis()->SetRangeUser(0,1000);
    gr[whichGam]->Draw("ALP");
    cc[whichGam]->Update();
    cc[whichGam]->SaveAs(Form("can%d.pdf",whichGam));
  }
  //calculate norm values and rms
  TGraph *gdep[20];
  Double_t averageNorm[20];
  Double_t averageNormErr[20];
  Double_t xdep[20],ydep[20];
  for (Int_t angleN=0;angleN<numAngles;angleN++) {
    for (Int_t whichGam=0;whichGam<gamN;whichGam++) {
      averageNorm[angleN] += finalNorm[whichGam][angleN];
      xdep[whichGam] = (Double_t)mean[whichGam];
      ydep[whichGam] = finalNorm[whichGam][angleN];
    }
    averageNorm[angleN]/=5.0;
    for (Int_t whichGam=0;whichGam<gamN;whichGam++) {
      averageNormErr[angleN] =
      (averageNorm[angleN] - finalNorm[whichGam][angleN])*
      (averageNorm[angleN] - finalNorm[whichGam][angleN]);
    }
    averageNormErr[angleN] = TMath::Sqrt(averageNormErr[angleN]/5.0);
    if (angleN==0) {
      printf("Float_t norm[20][2] = { {%f,%f},\n",averageNorm[angleN],averageNormErr[angleN]);
    } else {
    printf("{%f,%f},\n",averageNorm[angleN],averageNormErr[angleN]);
    }
    gdep[angleN] = new TGraph(gamN,xdep,ydep);
  }
  printf("{1,1}};\n");

  printf("\n\nFloat_t normNew[20][20] = {\n");
  for (Int_t angleN=0;angleN<numAngles;angleN++) {
    printf("{");
    for (Int_t whichGam=0;whichGam<gamN;whichGam++) {
      printf("%f",finalNorm[whichGam][angleN]);
      if (whichGam<gamN-1) printf(",");
    }

    if (angleN==numAngles-1) {
      printf("}");
    } else {
      printf("},\n");
    }
  }
  printf("};\n");

  printf("\n\nmeanCal[20] = {");
  for (Int_t i=0;i<gamN;i++) {
    printf("%.1f",mean[i]);
    if (i<gamN-1) printf(",\n");
  }
  printf("};\n\n");

  TCanvas *cgraph = new TCanvas("cgraph","cgraph",800,800);
  for (Int_t whichGam=0;whichGam<gamN;whichGam++) {
    if (whichGam==0) gr[whichGam]->Draw("ALP");
    if (whichGam>0) gr[whichGam]->Draw("LP");
  }

  TCanvas *cdep = new TCanvas("cdep","cdep",600,600);
  cdep->cd();
  for (Int_t i=0;i<numAngles;i++) {
    gdep[i]->SetMarkerColor(kBlue+i);
    gdep[i]->SetMarkerSize(1);
    gdep[i]->SetLineColor(kBlue+i);
    gdep[i]->GetYaxis()->SetRangeUser(0,2);
    gdep[i]->SetLineWidth(3);
    if (i==0) {gdep[i]->Draw("ALP"); }
    else {gdep[i]->Draw("LP");}

  }


}
