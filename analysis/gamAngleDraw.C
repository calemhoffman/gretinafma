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

Int_t numAngles=4;
const int numGam=8;
FILE * fitFileOut;
TCanvas *cfit;
TCanvas *crat;
TCanvas *cc[10];
TGraphErrors * gr[10];
TGraphErrors *grAve[10];
Double_t xAve[100],xAve2[100],xAve3[100],xAve4[100];
Double_t yAve[100],yAve2[100],yAve3[100],yAve4[100];
Double_t xAveErr[100],xAve2Err[100],xAve3Err[100],xAve4Err[100];
Double_t yAveErr[100],yAve2Err[100],yAve3Err[100],yAve4Err[100];

// Double_t mean[10]={755.0,292.0,1190.0,171.0,3142.0,2970.0,2680.0};
// Double_t fitLow[10]={745.0,282.0,1175.0,155.0,3110.0,2950.0,2640};
// Double_t fitHigh[10]={765.0,302.0,1200.0,181.0,3170.0,3000.0,2700};
Double_t mean[10]={1292.0,1535.0,849.0,2668.0,1575,1610.0,384.5,2322.0};
Double_t fitLow[10]={1270.0,1520.0,840.0,2640.0,1555,1600.0,375.0,2314.0};
Double_t fitHigh[10]={1320.0,1550.0,860.0,2700.0,1590,1620.0,390.0,2334.0};
Int_t fitType[10]={1,1,1,1,1,1,1,0};
Int_t rebinFactor[10]={1,1,1,2,2,2,1,2};
Float_t maxGraphY[10]={100,80,80,25,50,50,50,30};
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
cfit->Divide(4,2);
crat = new TCanvas("crat","crat",1000,1000);
for (Int_t whichGam=0;whichGam<numGam;whichGam++) {
  fitFileOut = fopen (Form("gamAngleFits%.0f.dat",mean[whichGam]), "w+");
  cc[whichGam]= new TCanvas(Form("cc%d",whichGam),Form("cc%d",whichGam),1200,900);
  cc[whichGam]->cd();
  cc[whichGam]->Divide(2,3);
  if (numAngles>5) cc[whichGam]->Divide(3,3);
  if (numAngles>=10) cc[whichGam]->Divide(5,5);

  for (Int_t i = 0;i<numAngles; i++) {
    hgndva0[i] = new TH1D(Form("hgang%s_%d",name,i),Form("hgang%s_%d",name,i),4096,0,4096);
    binLow = 65.0 + (100.0/(Float_t)numAngles) * (Float_t)i;
    binHigh = 65.0 + (100.0/(Float_t)numAngles) + (100.0/(Float_t)numAngles) * (Float_t)i;
    hgAddBackVsAngle0->ProjectionX(Form("hgang%s_%d",name,i),binLow,binHigh);
    fprintf(fitFileOut, "%f ", (binHigh+binLow)/2.0);
    cc[whichGam]->cd(i+1);
    hgndva0[i]->Scale(1./norm[i][0]);
    if (rebinFactor[whichGam]>1) hgndva0[i]->Rebin(rebinFactor[whichGam]);

    if (fitType[whichGam]==0)
      fitGauss(hgndva0[i],mean[whichGam],3,fitLow[whichGam],fitHigh[whichGam],fitFileOut);

    if (fitType[whichGam]==1)
      fitGaussP1(hgndva0[i],mean[whichGam],3,fitLow[whichGam],fitHigh[whichGam],fitFileOut);

    hgndva0[i]->GetXaxis()->SetRangeUser(fitLow[whichGam]-50,fitHigh[whichGam]+50);
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
  average/=(Double_t)index;
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
  gr[whichGam]->GetYaxis()->SetRangeUser(0,2);
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

  // Double_t * para4 = new Double_t[3];
  // para4[0] = 200.0;
  // para4[1] = 0.5;
  // para4[2] = 0.1;
  //
  // TF1 * l4fit = new TF1("l4fit", "[0]*(1 + [1]*ROOT::Math::legendre(2,x) + [2]*ROOT::Math::legendre(4,x))",-1,1);//+ROOT::Math::legendre([2],x))",-1,1);
  // l4fit->SetParameters(para4);
  // gr[whichGam]->Fit(l4fit);
  //
  // const Double_t* para4E = l4fit->GetParErrors();
  // const Double_t* para4A = l4fit->GetParameters();
  // l4fit->SetLineColor(kRed);
  // l4fit->GetYaxis()->SetRangeUser(0,2);
  // l4fit->GetXaxis()->SetRangeUser(-1,1);
// printf("average %f\n",average);
//gr[whichGam]->Draw("ALP");
  l2fit->Draw("same");
  //l4fit->Draw("same");
  cfit->Update();
  cfit->cd();

  if (numAngles==4 || numAngles==5) {
    xAve[whichGam] = (Double_t)mean[whichGam];//(/3.;
    yAve[whichGam] = (y[numAngles-1])/(y[0]);
    xAveErr[whichGam] = 0.0001;
    yAveErr[whichGam] =
    TMath::Sqrt(yerr[numAngles-1]*yerr[numAngles-1]+yerr[0]*yerr[0])/2.;
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
    grAve[0]->SetMarkerStyle(20);
    grAve[0]->SetMarkerSize(2);
    grAve[1] = new TGraphErrors(numGam,xAve2,yAve2,xAve2Err,yAve2Err);
    grAve[1]->SetMarkerStyle(21);
    grAve[1]->SetMarkerColor(kRed);
    grAve[1]->SetMarkerSize(2);
    grAve[2] = new TGraphErrors(numGam,xAve3,yAve3,xAve3Err,yAve3Err);
    grAve[2]->SetMarkerStyle(22);
    grAve[2]->SetMarkerColor(kBlue);
    grAve[2]->SetMarkerSize(2);

    if (numAngles==5) {
      xAve4[whichGam] = (Double_t)mean[whichGam];//(/3.;
      yAve4[whichGam] = (y[numAngles-1])/(y[3]);
      xAve4Err[whichGam] = 0.0001;
      yAve4Err[whichGam] =
      TMath::Sqrt(yerr[numAngles-1]*yerr[numAngles-1]+yerr[3]*yerr[3])/2.;
      grAve[3] = new TGraphErrors(numGam,xAve4,yAve4,xAve4Err,yAve4Err);
      grAve[3]->SetMarkerStyle(23);
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
    grAve[0]->SetMarkerStyle(20);
    grAve[0]->SetMarkerSize(2);
  }
}
  crat->cd();
  if (numAngles==4 || numAngles==5 || numAngles==10) {
    grAve[0]->GetYaxis()->SetRangeUser(0.5,2);
    grAve[0]->GetXaxis()->SetRangeUser(0,4000);
    grAve[0]->SetTitle("Yield Ratios");
    grAve[0]->Draw("AP");
    if (numAngles==4 || numAngles==5) {
      grAve[1]->Draw("P");
      grAve[2]->Draw("P");
    }
    if (numAngles==5) {grAve[3]->Draw("P");}
  }
}
