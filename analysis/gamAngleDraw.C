


void gamAngleDraw(void) {

  Float_t norm[20][2] = { {0.187,0.019},
    {0.460,	0.044},
  {0.606,	0.068},
  {0.629,	0.005},
  {0.854,	0.025},
  {0.909,	0.003},
  {1.000,	0.000},
  {0.646,	0.008},
  {0.561,	0.008},
  {0.351,	0.011},
  {0.119,	0.006} };
Int_t binNum = 12;
TH1D *hgndva0[50];
Float_t binLow;
Float_t binHigh;
char * name("scan01");

FILE * fitFileOut;
fitFileOut = fopen ("gamAngleFits.dat", "w+");
//

Double_t mean=1292; Double_t fitLow=1250; Double_t fitHigh=1310;

for (Int_t i = 0;i< 11; i++) {

  hgndva0[i] = new TH1D(Form("hgang%s_%d",name,i),Form("hgang%s_%d",name,i),4096,0,4096);

binLow = 65 + 10 * (Float_t)i;
binHigh = 75 + 10 * (Float_t)i;

 hgAddBackVsAngle0->ProjectionX(Form("hgang%s_%d",name,i),binLow,binHigh);


// cic_e1d->cd(1);
fprintf(fitFileOut, "%f ", (binHigh+binLow)/2.0);
 //fitGaussP1(hgndva0[i],mean,50,fitLow,fitHigh,fitFileOut);
 fitGauss(hgndva0[i],mean,50,fitLow,fitHigh,fitFileOut);
}
TCanvas *cc = new TCanvas("cc","cc",1200,900);

cc->Clear(); cc->Divide(4,3);
for (Int_t i = 0;i<11;i++) {

cc->cd(i+1);
hgndva0[i]->GetXaxis()->SetRangeUser(fitLow-50,fitHigh+50);
hgndva0[i]->GetYaxis()->SetRangeUser(0,110);
hgndva0[i]->Draw();
 wrspe(Form("hgang%s_%d",name,i),Form("angDist/hgang%s_%d.spe",name,i));
}

fflush(fitFileOut);
fclose(fitFileOut);

ifstream inFile;
inFile.open("gamAngleFits.dat");
Float_t angleData[100][10];
Int_t index=0;
Double_t x[100];
Double_t xerr[100];
Double_t y[100];
Double_t yerr[100];

if( inFile.is_open() ) {
  while (1) {
    if (!inFile.good()) break;
    inFile >> angleData[index][0] >> angleData[index][1] >> angleData[index][2] >> angleData[index][3] >>
    angleData[index][4] >> angleData[index][5] >> angleData[index][6];

    x[index] = (Double_t)angleData[index][0];
    y[index] = (Double_t)angleData[index][1]/(Double_t)norm[index][0];

    printf("%f %f\n",angleData[index][0],angleData[index][1]/norm[index][0]);
    index++;
  }
  printf("... done reading fit file\n");

} else { printf("... failed to read fit file\n"); }
TGraphErrors * gr = new TGraphErrors(11,x,y);
cc->cd(12);

gr->SetMarkerColor(4);
  gr->SetMarkerStyle(21);
  gr->Draw("ALP");



}
