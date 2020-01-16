void gamAngleDraw(void) {

  Float_t norm[20][2];
  Float_t norm2[20][2] = {
    {1.293463,0.020594},
    {1.706537,0.020594}
  };
  Float_t norm3[20][2] = {
    {0.868276,0.040579},
    {1.851177,0.015443},
    {1.280547,0.025136}
  };
  Float_t norm4[20][2] = {
    {0.683712,0.041636},
    {1.478270,0.007585},
    {1.833276,0.011514},
    {1.004742,0.022537}
  };
  Float_t norm5[20][2] = {
    {0.578897,0.025807},
    {1.216419,0.007089},
    {1.714124,0.016332},
    {1.630528,0.021915},
    {0.860033,0.005352}
  };
  Float_t norm10[20][2] = {
    {0.347027,0.018562},
    {0.728425,0.062301},
    {1.004681,0.066472},
    {1.132854,0.008935},
    {1.534160,0.029074},
    {1.610138,0.001785},
    {1.784186,0.008608},
    {1.186193,0.025840},
    {1.019464,0.015773},
    {0.652872,0.020197}
  };
  Float_t norm20[20][2] = {
    {0.174728,0.016217},
    {0.487643,0.020574},
    {0.680728,0.025886},
    {0.701192,0.091305},
    {0.836235,0.083967},
    {1.083899,0.037965},
    {1.111538,0.004841},
    {1.073191,0.014980},
    {1.302851,0.035245},
    {1.640658,0.027917},
    {1.582540,0.000352},
    {1.527958,0.007617},
    {1.826271,0.014346},
    {1.612676,0.006718},
    {1.218695,0.025787},
    {1.035260,0.028353},
    {1.071676,0.017489},
    {0.880006,0.018471},
    {0.693773,0.020737},
    {0.458479,0.019816}
  };

TH1D *hgndva0[50];
Float_t binLow;
Float_t binHigh;
char * name("scan01");

Int_t numAngles=10;
const int numGam=7;
FILE * fitFileOut;
TCanvas *cfit;
TCanvas *crat;
TCanvas *cc[10];
TGraphErrors * gr[10];
TGraphErrors *grAve[10];
Double_t xAve[10];
Double_t yAve[10];
Double_t xAveErr[10];
Double_t yAveErr[10];

Double_t mean[10]={755.0,292.0,1190.0,171.0,3142.0,2970.0,2680.0};
Double_t fitLow[10]={745.0,282.0,1175.0,155.0,3110.0,2950.0,2640};
Double_t fitHigh[10]={765.0,302.0,1200.0,181.0,3170.0,3000.0,2700};
// Double_t mean[10]={1292.0,1535.0,849.0,2668.0,1575,1610.0,385.0,440.0,2322.0};
// Double_t fitLow[10]={1260.0,1515.0,840.0,2640.0,1555,1590.0,375.0,430.0,2300.0};
// Double_t fitHigh[10]={1304.0,1555.0,860.0,2700.0,1590,1620.0,395.0,450.0,2342.0};
// Double_t mean[10]={1412,1432};
// Double_t fitLow[10]={1400,1420};
// Double_t fitHigh[10]={1420,1442};


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
  } else if (numAngles==10) {
    norm[i][0] = norm10[i][0];
    norm[i][1] = norm10[i][1];
  } else if (numAngles==20) {
    norm[i][0] = norm20[i][0];
    norm[i][1] = norm20[i][1];
  }
}

/*********************************************/
cfit = new TCanvas("cfit","cfit",1400,700);
crat = new TCanvas("crat","crat",1000,1000);
for (Int_t whichGam=0;whichGam<numGam;whichGam++) {
  fitFileOut = fopen (Form("gamAngleFits%.0f.dat",mean[whichGam]), "w+");
  cc[whichGam]= new TCanvas(Form("cc%d",whichGam),Form("cc%d",whichGam),1200,900);
  cc[whichGam]->cd();
  if (numAngles<10) cc[whichGam]->Divide(3,3);
  if (numAngles>=10) cc[whichGam]->Divide(5,5);

  for (Int_t i = 0;i<numAngles; i++) {
    hgndva0[i] = new TH1D(Form("hgang%s_%d",name,i),Form("hgang%s_%d",name,i),4096,0,4096);
    binLow = 65.0 + (100.0/(Float_t)numAngles) * (Float_t)i;
    binHigh = 65.0 + (100.0/(Float_t)numAngles) + (100.0/(Float_t)numAngles) * (Float_t)i;
    hgAddBackVsAngle0->ProjectionX(Form("hgang%s_%d",name,i),binLow,binHigh);
    fprintf(fitFileOut, "%f ", (binHigh+binLow)/2.0);
    if (whichGam==8) hgndva0[i]->Rebin();
    cc[whichGam]->cd(i+1);
    hgndva0[i]->Scale(1./norm[i][0]);
    fitGaussP1(hgndva0[i],mean[whichGam],3,fitLow[whichGam],fitHigh[whichGam],fitFileOut);
//fitGauss(hgndva0[i],mean[whichGam],3,fitLow[whichGam],fitHigh[whichGam],fitFileOut);
    hgndva0[i]->GetXaxis()->SetRangeUser(fitLow[whichGam]-50,fitHigh[whichGam]+50);
    hgndva0[i]->GetYaxis()->SetRangeUser(0,200);
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
      yerr[index] = y[index] * TMath::Sqrt(tempErr1 + tempErr2);
      average+=angleData[index][1];
      printf("%f %f\n",angleData[index][0],angleData[index][1]/norm[index][0]);
      index++;
  }
  printf("... done reading fit file\n");
  } else { printf("... failed to read fit file\n");
  }
  average/=(Double_t)index;
//adding in averging to put all ang dist on same plot.
for (Int_t i=0;i<index-1;i++) {
  y[i] = y[i]/average;
  yerr[i] = yerr[i]/average;
}

  cfit->cd();
  gr[whichGam] = new TGraphErrors(numAngles,x,y,xerr,yerr);
  if (whichGam==0) {gr[whichGam]->Draw("ALP");}
  gr[whichGam]->SetMarkerColor(kGreen+2+whichGam);
  gr[whichGam]->SetMarkerStyle(21+whichGam);
  gr[whichGam]->GetXaxis()->SetRangeUser(-1,1);
  gr[whichGam]->GetYaxis()->SetRangeUser(0,2);
  if (whichGam==0) {gr[whichGam]->Draw("ALP");}
  else {gr[whichGam]->Draw("LP");}

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

  Double_t * para4 = new Double_t[3];
  para4[0] = 200.0;
  para4[1] = 0.5;
  para4[2] = 0.1;

  TF1 * l4fit = new TF1("l4fit", "[0]*(1 + [1]*ROOT::Math::legendre(2,x) + [2]*ROOT::Math::legendre(4,x))",-1,1);//+ROOT::Math::legendre([2],x))",-1,1);
  l4fit->SetParameters(para4);
  gr[whichGam]->Fit(l4fit);

  const Double_t* para4E = l4fit->GetParErrors();
  const Double_t* para4A = l4fit->GetParameters();
  l4fit->SetLineColor(kRed);
  l4fit->GetXaxis()->SetRangeUser(-1,1);
// printf("average %f\n",average);
//gr[whichGam]->Draw("ALP");
  l2fit->Draw("same");
  l4fit->Draw("same");
  cfit->Update();
  cfit->cd();

  if (numAngles==10) {
    // xAve[whichGam] = (y[1]+y[2]+y[3])/3.;
    xAve[whichGam] = (Double_t)whichGam;//(/3.;
    yAve[whichGam] = (y[9]+y[8]+y[7])/(y[1]+y[2]+y[3]);
    xAveErr[whichGam] = 0.0001;//TMath::Sqrt(yerr[1]*yerr[1]+yerr[2]*yerr[2]+yerr[3]*yerr[3])/3.;
    yAveErr[whichGam] = TMath::Sqrt(yerr[9]*yerr[9]+yerr[8]*yerr[8]+yerr[7]*yerr[7])/3.;
  }
}
  crat->cd();
  grAve[0] = new TGraphErrors(numGam,xAve,yAve,xAveErr,yAveErr);
  grAve[0]->SetMarkerStyle(20);
  grAve[0]->Draw("AP");
}
