{
  TCanvas *cc = new TCanvas("cc","cc",1200,700);
TFile f("pyTorchOutAverageFatF.root");
//TFile f("pyTorchOutAverageSkinK.root");
//TFile f("pyTorchOutAverageFatF_base.root");
TH2F *hgg[5];
TH1F *hg[5];
TH1D *hg_px[5];
TH1D *hg_py[5];
TH1D *hg1293[5];

for (Int_t i=0;i<5;i++) {
  //get hists
  hg_px[i] = new TH1D(Form("hg_px%d",i),Form("hg_px%d",i),4000,0,4000);
  hg_py[i] = new TH1D(Form("hg_py%d",i),Form("hg_py%d",i),4000,0,4000);
  hg1293[i] = new TH1D(Form("hg1293_%d",i),Form("1293 hg1293_%d",i),4000,0,4000);
  hgg[i] = (TH2F *)gDirectory->FindObjectAny(Form("hgg%d",i));
  hg[i] = (TH1F *)gDirectory->FindObjectAny(Form("hg%d",i));
  hgg[i]->ProjectionX(Form("hg_px%d",i));
  hgg[i]->ProjectionY(Form("hg_py%d",i));
  hgg[i]->ProjectionX(Form("hg1293_%d",i),1287,1298);
  hg[i]->SetLineColor(40+i); hg_py[i]->SetLineColor(40+i);
  hg_px[i]->SetLineColor(40+i);hg1293[i]->SetLineColor(40+i);
  hg[i]->SetFillColor(40+i); hg_py[i]->SetFillColor(40+i);
  hg_px[i]->SetFillColor(40+i);hg1293[i]->SetFillColor(40+i);
  hg[i]->SetFillStyle(1001); hg_py[i]->SetFillStyle(1001);
  hg_px[i]->SetFillStyle(1001);hg1293[i]->SetFillStyle(1001);
  hg[i]->SetFillColorAlpha(40+i,0.3); hg_py[i]->SetFillColorAlpha(40+i,0.3);
  hg_px[i]->SetFillColorAlpha(40+i,0.3);hg1293[i]->SetFillColorAlpha(40+i,0.3);
}

//fitting
printf("--------Fitting of the full singles-------\n");
for (Int_t i=0;i<5;i++) fitGaussP0(hg[i],1293,3,10,1250,1350);
printf("--------Fitting of the px-------\n");
for (Int_t i=0;i<5;i++) fitGaussP0(hg_px[i],1293,3,10,1250,1350);
printf("--------Fitting of the 1293 proj-------\n");
for (Int_t i=0;i<5;i++) fitGaussP0(hg1293[i],1535,3,1,1500,1560);
// printf("--------Fitting of the py-------\n");
// for (Int_t i=0;i<5;i++) fitGaussP0(hg_py[i],1293,3,10,1250,1350);


hg1293[0]->Draw("hist");
for (Int_t i=1;i<5;i++) hg1293[i]->Draw("same hist");

//TCanvas *cfit = new TCanvas("cfit","cfit",1250,700);
fitNGauss(hg[2],30,"fit_para.txt");

}
