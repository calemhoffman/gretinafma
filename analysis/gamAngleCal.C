void gamAngleCal(void) {
  Float_t norm[20][2];

    for (Int_t i=0;i<20;i++) {
      norm[i][0]=1;
      norm[i][1]=0.0001;
    }

TH1D *hgndva0[50];
Float_t binLow;
Float_t binHigh;
char * name("Cal");

Int_t numAngles=5;
Double_t maxYvalue=0;
FILE * fitFileOut;
fitFileOut = fopen ("gamAngleCal.dat", "w+");
//
const int whichGam=0;//0-1292,1-1535,2-849,3-2670,4-1575
Double_t mean[10]={344,1535.0,849.0,2668.0,1575};
Double_t fitLow[10]={320,1525.0,845.0,2640.0,1555};
Double_t fitHigh[10]={360,1545.0,855.0,2700.0,1590};

for (Int_t i = 0;i<numAngles; i++) {
  hgndva0[i] = new TH1D(Form("hgang%s_%d",name,i),Form("hgang%s_%d",name,i),4096,0,4096);
  binLow = 65.0 + (100.0/(Float_t)numAngles) * (Float_t)i;
  binHigh = 65.0 + (100.0/(Float_t)numAngles) + (100.0/(Float_t)numAngles) * (Float_t)i;
  hgAddBackVsAngle0->ProjectionX(Form("hgang%s_%d",name,i),binLow,binHigh);

  fprintf(fitFileOut, "%f ", (binHigh+binLow)/2.0);
  fitGaussP1(hgndva0[i],mean[whichGam],3,fitLow[whichGam],fitHigh[whichGam],fitFileOut);
//fitGauss(hgndva0[i],mean[whichGam],3,fitLow[whichGam],fitHigh[whichGam],fitFileOut);
}

TCanvas *cc = new TCanvas("cc","cc",1200,900);
cc->Clear(); cc->Divide(4,3);
for (Int_t i = 0;i<numAngles;i++) {
  cc->cd(i+1);
  hgndva0[i]->GetXaxis()->SetRangeUser(fitLow[whichGam]-50,fitHigh[whichGam]+50);
  hgndva0[i]->GetYaxis()->SetRangeUser(0,20000);
  hgndva0[i]->Draw();
  wrspe(Form("hgang%s_%d",name,i),Form("angDist/hgang%s_%d.spe",name,i));
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
    printf("%f %f\n",angleData[index][0],angleData[index][1]/norm[index][0]);
    average+=angleData[index][1];
    index++;
  }
  printf("... done reading fit file\n");

} else { printf("... failed to read fit file\n"); }

average/=(Double_t)index;

for (Int_t index2=0;index2<index-1;index2++) {
  x[index2] = (TMath::Cos(TMath::Pi()*angleData[index2][0]/180.0));
  y[index2] = (Double_t)angleData[index2][1]/(Double_t)norm[index2][0]/average;
  xerr[index2] = 0.001;
  tempErr1 = (Double_t)((angleData[index2][2]/angleData[index2][1])*(angleData[index2][2]/angleData[index2][1]));
  tempErr2 = (Double_t)((norm[index2][1]/norm[index2][0])*(norm[index2][1]/norm[index2][0]));
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
}
