


void gamAngleDraw(void) {
  Float_t norm[20][2] =
  { {0.187,0.019},
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

    for (Int_t i=0;i<20;i++) {
      norm[i][0]=1;
      norm[i][1]=0.0001;
    }

TH1D *hgndva0[50];
Float_t binLow;
Float_t binHigh;
char * name("scan01");

Int_t numAngles=5;

FILE * fitFileOut;
fitFileOut = fopen ("gamAngleFits.dat", "w+");
//
const int whichGam=4;//0-1292,1-1535,2-849,3-2670,4-1575
Double_t mean[10]={1292.0,1535.0,849.0,2668.0,1575};
Double_t fitLow[10]={1280.0,1525.0,845.0,2640.0,1555};
Double_t fitHigh[10]={1310.0,1545.0,855.0,2700.0,1590};

for (Int_t i = 0;i<numAngles; i++) {
  hgndva0[i] = new TH1D(Form("hgang%s_%d",name,i),Form("hgang%s_%d",name,i),4096,0,4096);
  binLow = 65.0 + (100.0/(Float_t)numAngles) * (Float_t)i;
  binHigh = 65.0 + (100.0/(Float_t)numAngles) + (100.0/(Float_t)numAngles) * (Float_t)i;
  hgAddBackVsAngle0->ProjectionX(Form("hgang%s_%d",name,i),binLow,binHigh);
  if (whichGam==3 || whichGam==4) hgndva0[i]->Rebin(2);
// cic_e1d->cd(1);
  fprintf(fitFileOut, "%f ", (binHigh+binLow)/2.0);
//fitGaussP1(hgndva0[i],mean[whichGam],3,fitLow[whichGam],fitHigh[whichGam],fitFileOut);
fitGauss(hgndva0[i],mean[whichGam],3,fitLow[whichGam],fitHigh[whichGam],fitFileOut);
}

TCanvas *cc = new TCanvas("cc","cc",1200,900);
cc->Clear(); cc->Divide(4,3);
for (Int_t i = 0;i<numAngles;i++) {
  cc->cd(i+1);
  hgndva0[i]->GetXaxis()->SetRangeUser(fitLow[whichGam]-50,fitHigh[whichGam]+50);
  hgndva0[i]->GetYaxis()->SetRangeUser(0,20);
  hgndva0[i]->Draw();
  wrspe(Form("hgang%s_%d",name,i),Form("angDist/hgang%s_%d.spe",name,i));
}

fflush(fitFileOut);
fclose(fitFileOut);

//Fitting
ifstream inFile;
inFile.open("gamAngleFits.dat");
Float_t angleData[100][10];
Int_t index=0;
Double_t x[100];
Double_t xerr[100];
Double_t y[100];
Double_t yerr[100];
Double_t tempErr1=0;
Double_t tempErr2=0;

if( inFile.is_open() ) {
  while (1) {
    if (!inFile.good()) break;
    inFile >> angleData[index][0] >> angleData[index][1] >> angleData[index][2] >> angleData[index][3] >>
    angleData[index][4] >> angleData[index][5] >> angleData[index][6];

    x[index] = (TMath::Cos(TMath::Pi()*angleData[index][0]/180.0));
    y[index] = (Double_t)angleData[index][1]/(Double_t)norm[index][0];
    xerr[index] = 0.001;
    tempErr1 = (Double_t)((angleData[index][2]/angleData[index][1])*(angleData[index][2]/angleData[index][1]));
    tempErr2 = (Double_t)((norm[index][1]/norm[index][0])*(norm[index][1]/norm[index][0]));
    yerr[index] = y[index] * TMath::Sqrt(tempErr1 + tempErr2);

    printf("%f %f\n",angleData[index][0],angleData[index][1]/norm[index][0]);
    index++;
  }
  printf("... done reading fit file\n");

} else { printf("... failed to read fit file\n"); }
TGraphErrors * gr = new TGraphErrors(numAngles,x,y,xerr,yerr);
cc->cd(12);
gr->Draw("ALP");
gr->SetMarkerColor(4);
gr->SetMarkerStyle(21);
gr->GetXaxis()->SetRangeUser(-1,1);
gr->GetYaxis()->SetRangeUser(0,1000);
gr->Draw("ALP");
cc->Update();

TCanvas *cfit = new TCanvas("cfit","cfit",1400,700);
cfit->cd();
gr->Draw("ALP");
Double_t * para2 = new Double_t[3];
para2[0] = 100.0;
para2[1] = 0.5;
para2[3] = 2;

// func->SetParameters(0,3.1,1.e-6,-1.5,0,100);
// func->SetParLimits(3,-10,4);
// func->FixParameter(4,0);

TF1 * l2fit = new TF1("l2fit", "[0]*(1 + [1]*ROOT::Math::legendre([2],x))",-1,1);//+ROOT::Math::legendre([2],x))",-1,1);
//l2fit->SetParameters(450,0.5);//,4,0.0);
l2fit->SetParameters(para2);
l2fit->FixParameter(2,2);
//l2fit->SetParLimits(0,-2,2);
l2fit->SetParLimits(1,-1,1);
//l2fit->SetParLimits(2,-1,1);

gr->Fit(l2fit);
const Double_t* para2E = l2fit->GetParErrors();
const Double_t* para2A = l2fit->GetParameters();
l2fit->GetXaxis()->SetRangeUser(-1,1);
l2fit->Draw("same");


Double_t * para4 = new Double_t[3];
para4[0] = 200.0;
para4[1] = 0.5;
para4[2] = 0.1;

TF1 * l4fit = new TF1("l4fit", "[0]*(1 + [1]*ROOT::Math::legendre(2,x) + [2]*ROOT::Math::legendre(4,x))",-1,1);//+ROOT::Math::legendre([2],x))",-1,1);
// l2fit->SetParameters(450,0.5,0.05);//,4,0.0);
l4fit->SetParameters(para4);
gr->Fit(l4fit);

const Double_t* para4E = l4fit->GetParErrors();
const Double_t* para4A = l4fit->GetParameters();
l4fit->SetLineColor(kRed);
l4fit->GetXaxis()->SetRangeUser(-1,1);
l4fit->Draw("same");

cfit->Update();

}
