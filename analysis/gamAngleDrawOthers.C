#include "gamAngleDraw.h"

void gamAngleDrawOthers(void) {

Float_t norm[20][2];
Float_t normNew[20][20][2];

TH1D *hgndva0[50];
Float_t binLow;
Float_t binHigh;
char * name("misc");

Int_t numAngles=5;
const int  numGam = 8;
Double_t angMin = 65.0;
Double_t angRange = 100.0;
FILE * fitFileOut;
TCanvas *cfit;
TCanvas *crat;
TCanvas *cc[100];
TGraphErrors * gr[100];
TGraphErrors *grAve[100];
TGraphErrors *ga2a4;
Double_t xAve[100],xAve2[100],xAve3[100],xAve4[100];
Double_t yAve[100],yAve2[100],yAve3[100],yAve4[100];
Double_t xAveErr[100],xAve2Err[100],xAve3Err[100],xAve4Err[100];
Double_t yAveErr[100],yAve2Err[100],yAve3Err[100],yAve4Err[100];
Double_t a2[100];
Double_t a2err[100];
Double_t a4[100];
Double_t a4err[100];

Double_t mean[100]={171.0,292.0,638.0,755.0,1190.0,2044.0,2680.0,3142.0,1848.0,1432.0};
Double_t sigma[100]={1.0,1.0,1.0,1.0,1.5,2.0,2.0,2.5,1.5,1.5};
Double_t offset[100]={10.0,10.0,10.0,10.0,10.0,10.0,10.0,10.0,10.0,10.0};
Double_t fitLow[100]={160.0,280.0,625.0,740.0,1170.0,2025.0,2640.0,3100.0,1838.0,1420.0};
Double_t fitHigh[100]={185.0,305.0,655.0,770.0,1196.0,2065.0,2710.0,3200.0,1860.0,1440.0};
Double_t fixWidth[100]={0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0};
Int_t fitType[100]={1,1,1,1,1,1,1,1,1,1};
Int_t rebinFactor[100]={1,1,1,1,1,2,2,2,4,4};//4=1keV,8=2keV
Float_t maxGraphY[100]={1000,1000,500,500,500,200,300,300,600,600};
Double_t mean2[100]={0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0};

Float_t nfact[20];

for (Int_t i=0;i<numAngles;i++) {
  if (numAngles==0) {
    norm[i][0] = 1.0;
    norm[i][1] = 0.000001;
  } else if (numAngles==2) {
    norm[i][0] = norm2[i][0];
    norm[i][1] = norm2[i][1];
  } else if (numAngles==3) {
    norm[i][0] = norm3[i][0];
    norm[i][1] = norm3[i][1];
  } else if (numAngles==4) {
    norm[i][0] = norm4[i][0];
    norm[i][1] = norm4[i][1];
  } else if (numAngles==5) {
    norm[i][0] = norm5[i][0];
    norm[i][1] = norm5[i][1];
  } else if (numAngles==6) {
    norm[i][0] = norm6[i][0];
    norm[i][1] = norm6[i][1];
  } else if (numAngles==10) {
    norm[i][0] = norm10[i][0];
    norm[i][1] = norm10[i][1];
  } else if (numAngles==20) {
    norm[i][0] = norm20[i][0];
    norm[i][1] = norm20[i][1];
  }
}
Double_t angVal[20] = {75,105,121,133,143,165};

/*********************************************/
cfit = new TCanvas("cfit","cfit",1400,900);
if (numAngles<10) {cfit->Divide(4,4);}
else if (numAngles==10) {cfit->Divide(5,2);}
else if (numAngles>10) {cfit->Divide(5,4);}

crat = new TCanvas("crat","crat",1000,1000);
for (Int_t whichGam=0;whichGam<numGam;whichGam++) {
  for(Int_t k=0;k<12;k++) {//energy
    if (mean[whichGam]>=meanCal[k] &&
        mean[whichGam]<meanCal[k+1]) {
        nfact[k] = (mean[whichGam]-meanCal[k])/
                (meanCal[k+1]-meanCal[k]);
                printf("nfact %f",nfact[k]);
        for (Int_t j=0;j<numAngles;j++) {
          normNew[whichGam][j][0] = normCal[j][k]
          + nfact[k]*(normCal[j][k+1]-normCal[j][k]);
          printf("normNew[][][] vs norm: %1.4f %1.4f\n",normNew[whichGam][j][0],norm[j][0]);
        }
      }
    }

  fitFileOut = fopen (Form("gamAngleFits%.0f.dat",mean[whichGam]), "w+");
  cc[whichGam]= new TCanvas(Form("cc%d",whichGam),Form("cc%d",whichGam),1200,900);
  cc[whichGam]->cd();
  cc[whichGam]->Divide(2,3);
  if (numAngles>5) {cc[whichGam]->Clear(); cc[whichGam]->Divide(3,3);}
  if (numAngles==10) {cc[whichGam]->Clear(); cc[whichGam]->Divide(2,5);}
  if (numAngles>10) {cc[whichGam]->Clear(); cc[whichGam]->Divide(4,5);}
  for (Int_t i = 0;i<numAngles; i++) {
    hgndva0[i] = new TH1D(Form("hgang%s_%d",name,i),Form("hgang%s_%d",name,i),4096,0,4096);
    binLow = angVal[i];//angMin + (angRange/(Float_t)numAngles) * (Float_t)i;
    binHigh = angVal[i+1];//angMin + (angRange/(Float_t)numAngles) + (angRange/(Float_t)numAngles) * (Float_t)i;
    hgAddBackVsAngle0->ProjectionX(Form("hgang%s_%d",name,i),binLow,binHigh);
    fprintf(fitFileOut, "%f ", (binHigh+binLow)/2.0);
    cc[whichGam]->cd(i+1);
    if (numAngles!=10) {
      hgndva0[i]->Scale(1./norm[i][0]);
      //if ( (whichGam==8||whichGam==6) && i==0)
        //hgndva0[i]->Scale(1./norm[i][0]);
    } else {
      hgndva0[i]->Scale(1./normNew[whichGam][i][0]);
    }
    if (rebinFactor[whichGam]>1) hgndva0[i]->Rebin(rebinFactor[whichGam]);

    if (fitType[whichGam]==0) {
      if (i==0 && whichGam==2) {
        fitGaussP1(hgndva0[i],mean[whichGam],3,fitLow[whichGam]-8,fitHigh[whichGam]+8,fitFileOut);
      } else {
        fitGauss(hgndva0[i],mean[whichGam],3,fitLow[whichGam],fitHigh[whichGam],fitFileOut);
      }
    }

    if (fitType[whichGam]==1)
      fitGaussP0(hgndva0[i],mean[whichGam],sigma[whichGam],
                offset[whichGam],fitLow[whichGam],fitHigh[whichGam],
                fixWidth[whichGam],
                fitFileOut);

    TCanvas *tempCan;
    if (fitType[whichGam]==2)
      fit2GaussP1(hgndva0[i],mean[whichGam],5,mean2[whichGam],5,fitLow[whichGam],
      fitHigh[whichGam],tempCan,fitFileOut);

    hgndva0[i]->GetXaxis()->SetRangeUser(fitLow[whichGam]-20,fitHigh[whichGam]+20);
    hgndva0[i]->GetYaxis()->SetRangeUser(0,maxGraphY[whichGam]);
    hgndva0[i]->Draw("same");
  }

  fflush(fitFileOut);
  fclose(fitFileOut);

  //Fitting
  ifstream inFile;
  inFile.open(Form("gamAngleFits%.0f.dat",mean[whichGam]));
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
      x[index] = (TMath::Cos(TMath::Pi()*angleData[index][0]/180.0));
      y[index] = (Double_t)angleData[index][1];///(Double_t)norm[index][0];
      xerr[index] = 0.001;
      tempErr1 = (Double_t)((angleData[index][2]/angleData[index][1])*(angleData[index][2]/angleData[index][1]));
      tempErr2 = (Double_t)((norm[index][1]/norm[index][0])*(norm[index][1]/norm[index][0]));
      yerr[index] = y[index] * TMath::Sqrt(tempErr1 + tempErr2) / 2.0;
      average+=angleData[index][1];
      printf("%f %f\n",angleData[index][0],angleData[index][1]/norm[index][0]);
      index++;
  }
  printf("... done reading fit file\n");
  } else { printf("... failed to read fit file\n");
  }
  average/=((Double_t)index-1);
//adding in averging to put all ang dist on same plot.
for (Int_t i=0;i<index-1;i++) {
  y[i] = y[i]/average;
  yerr[i] = yerr[i]/average;
}

  cfit->cd();
  cfit->cd(whichGam+1);
  gr[whichGam] = new TGraphErrors(numAngles,x,y,xerr,yerr);
  //if (whichGam==0) {gr[whichGam]->Draw("ALP");}
  if (whichGam < 4) {
    gr[whichGam]->SetMarkerColor(kGreen+whichGam);
    gr[whichGam]->SetMarkerStyle(20+whichGam);
  } else if (whichGam>=4 && whichGam<8) {
    gr[whichGam]->SetMarkerColor(kBlue+whichGam-4);
    gr[whichGam]->SetMarkerStyle(20+whichGam-4);
  } else if (whichGam>=8 && whichGam<12) {
    gr[whichGam]->SetMarkerColor(kRed+whichGam-8);
    gr[whichGam]->SetMarkerStyle(20+whichGam-8);
  }
  gr[whichGam]->SetTitle(Form("%.0f keV",mean[whichGam]));
  gr[whichGam]->GetXaxis()->SetRangeUser(-1,1);
  gr[whichGam]->GetYaxis()->SetRangeUser(0.4,1.8);
  gr[whichGam]->Draw("ALP");

  Double_t * para2 = new Double_t[3];
  para2[0] = 100.0;
  para2[1] = 0.5;
  para2[3] = 2;

// func->SetParameters(0,3.1,1.e-6,-1.5,0,100);
// func->SetParLimits(3,-10,4);
// func->FixParameter(4,0);

  TF1 * l2fit = new TF1("l2fit", "[0]*(1 + [1]*ROOT::Math::legendre([2],x))",-1,1);//+ROOT::Math::legendre([2],x))",-1,1);
  l2fit->SetParameters(para2);
  l2fit->FixParameter(2,2);
  l2fit->SetParLimits(1,-1,1);

  gr[whichGam]->Fit(l2fit);
  const Double_t* para2E = l2fit->GetParErrors();
  const Double_t* para2A = l2fit->GetParameters();
  l2fit->GetXaxis()->SetRangeUser(-1,1);
//from here
  Double_t * para4 = new Double_t[3];
  para4[0] = 1.0;
  para4[1] = 1;
  para4[2] = -1;

  TF1 * l4fit = new TF1("l4fit", "[0]*(1 + [1]*ROOT::Math::legendre(2,x) + [2]*ROOT::Math::legendre(4,x))",-1,0);//+ROOT::Math::legendre([2],x))",-1,1);
  l4fit->SetParameters(para4);
  gr[whichGam]->Fit(l4fit);

  const Double_t* para4E = l4fit->GetParErrors();
  const Double_t* para4A = l4fit->GetParameters();
  if (a2[whichGam]>-5 && a2[whichGam]<5) {
    a2[whichGam] = para4A[1];
    a4[whichGam] = para4A[2];
    a2err[whichGam] = para4E[1]/2.0;
    a4err[whichGam] = para4E[2]/2.0;
  } else {
    a2[whichGam] = 0;//para4A[1];
    a4[whichGam] = 0;//para4A[2];
    a2err[whichGam] = 0;//para4E[1];
    a4err[whichGam] = 0;//para4E[2];
  }
  l4fit->SetLineColor(kRed);
  l4fit->GetYaxis()->SetRangeUser(0,2);
  l4fit->GetXaxis()->SetRangeUser(-1,1);
gr[whichGam]->Draw("ALP");
  l4fit->Draw("same");
//to here

  l2fit->Draw("same");

  cfit->Update();
  cfit->cd();

  if (numAngles==4 || numAngles==5 || numAngles==6) {
    xAve[whichGam] = (Double_t)mean[whichGam];//(/3.;
    yAve[whichGam] = (y[numAngles-2])/(y[2]);
    xAveErr[whichGam] = 0.0001;
    yAveErr[whichGam] =
    TMath::Sqrt(yerr[numAngles-2]*yerr[numAngles-2]+yerr[2]*yerr[2])/2.;
    xAve2[whichGam] = (Double_t)mean[whichGam];//(/3.;
    yAve2[whichGam] = (y[numAngles-1])/(y[1]);
    xAve2Err[whichGam] = 0.0001;
    yAve2Err[whichGam] =
    TMath::Sqrt(yerr[numAngles-1]*yerr[numAngles-1]+yerr[2]*yerr[2])/2.;
    xAve3[whichGam] = (Double_t)mean[whichGam];//(/3.;
    yAve3[whichGam] = (y[numAngles-1])/(y[2]);
    xAve3Err[whichGam] = 0.0001;
    yAve3Err[whichGam] =
    TMath::Sqrt(yerr[numAngles-1]*yerr[numAngles-1]+yerr[2]*yerr[2])/2.;

    grAve[0] = new TGraphErrors(numGam,xAve,yAve,xAveErr,yAveErr);
    grAve[0]->SetMarkerStyle(24);
    grAve[0]->SetMarkerSize(2);
    grAve[1] = new TGraphErrors(numGam,xAve2,yAve2,xAve2Err,yAve2Err);
    grAve[1]->SetMarkerStyle(21);
    grAve[1]->SetMarkerColor(kRed);
    grAve[1]->SetMarkerSize(2);
    grAve[2] = new TGraphErrors(numGam,xAve3,yAve3,xAve3Err,yAve3Err);
    grAve[2]->SetMarkerStyle(22);
    grAve[2]->SetMarkerColor(kBlue);
    grAve[2]->SetMarkerSize(2);

    if (numAngles==5 || numAngles==6) {
      xAve4[whichGam] = (Double_t)mean[whichGam];//(/3.;
      yAve4[whichGam] = (y[numAngles-1])/(y[3]);
      xAve4Err[whichGam] = 0.0001;
      yAve4Err[whichGam] =
      TMath::Sqrt(yerr[numAngles-1]*yerr[numAngles-1]+yerr[3]*yerr[3])/2.;
      grAve[3] = new TGraphErrors(numGam,xAve4,yAve4,xAve4Err,yAve4Err);
      grAve[3]->SetMarkerStyle(25);
      grAve[3]->SetMarkerColor(kGreen+2);
      grAve[3]->SetMarkerSize(2);
    }
  }

  if (numAngles==10) {
    Int_t low1=2;
    Int_t high1=9;
    // xAve[whichGam] = (y[1]+y[2]+y[3])/3.;
    xAve[whichGam] = (Double_t)mean[whichGam];//(/3.;
    yAve[whichGam] = (y[high1]+y[high1-1]+y[high1-2])/
                    (y[low1]+y[low1+1]+y[low1+2]);
    xAveErr[whichGam] = 0.0001;//TMath::Sqrt(yerr[1]*yerr[1]+yerr[2]*yerr[2]+yerr[3]*yerr[3])/3.;
    yAveErr[whichGam] =
    TMath::Sqrt(yerr[high1]*yerr[high1]+yerr[high1-1]*yerr[high1-1]
      +yerr[high1-2]*yerr[high1-2]
    +yerr[low1]*yerr[low1]+yerr[low1+1]*yerr[low1+1]
    +yerr[low1+2]*yerr[low1+2])/6.;
    grAve[0] = new TGraphErrors(numGam,xAve,yAve,xAveErr,yAveErr);
    grAve[0]->SetMarkerStyle(24);
    grAve[0]->SetMarkerSize(2);
  }
}
TLegend *leg;
  crat->cd();
  crat->Clear(); crat->Divide(1,2);
  crat->cd(1);
  if (numAngles==4 || numAngles==5 || numAngles==6) {
    grAve[1]->GetYaxis()->SetRangeUser(0,2);
    grAve[1]->GetXaxis()->SetRangeUser(0,4000);
    grAve[1]->SetTitle("Yield Ratios");
    grAve[1]->Draw("AP");
    grAve[0]->Draw("P");
    leg = new TLegend(0.1,0.7,0.48,0.9);
    leg->AddEntry(grAve[1],"4/1","p");
    leg->AddEntry(grAve[2],"4/2","p");
    if (numAngles==5 || numAngles==6)
    leg->AddEntry(grAve[3],"4/3","p");
    leg->AddEntry(grAve[0],"3/2","p");
    leg->Draw();
    if (numAngles==4 || numAngles==5 || numAngles==6) {
      grAve[2]->Draw("P");
//      grAve[2]->Draw("P");
    }
    if (numAngles==5 || numAngles==6) {grAve[3]->Draw("P");}
    //if (numAngles==6) {grAve[4]->Draw("P");}
  }
  crat->cd(2);
  ga2a4 = new TGraphErrors(numGam,a4,a2,a4err,a2err);
  ga2a4->GetXaxis()->SetTitle("a4");
  ga2a4->GetYaxis()->SetTitle("a2");
  ga2a4->SetMarkerStyle(20);
  ga2a4->SetMarkerColor(kRed);
  ga2a4->Draw("AP");

  printf("#energy a2 a2err a4 a4err\n");
    for (Int_t i=0;i<numGam;i++) {
      printf("%.0f %f %f %f %f\n",xAve[i],a2[i],a2err[i],a4[i],a4err[i]);

    }
}
