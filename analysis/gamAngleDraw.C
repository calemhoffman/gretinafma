{
Int_t binNum = 12;
TH1D *hgndva0[50];
Float_t binLow;
Float_t binHigh;
TCanvas *cc = new TCanvas("cc","cc",1200,900);
cc->Clear(); cc->Divide(4,3);
for (Int_t i = 0;i< 12; i++) {

hgndva0[i] = new TH1D(Form("hgndva0_%d",i),Form("hgndva0_%d",i),4096,0,4096);

binLow = 65 + 10 * (Float_t)i;
binHigh = 75 + 10 * (Float_t)i;

hgAddBackVsAngle0->ProjectionX(Form("hgndva0_%d",i),binLow,binHigh);

cc->cd(i+1);
hgndva0[i]->GetXaxis()->SetRangeUser(1000,1800);
hgndva0[i]->GetYaxis()->SetRangeUser(0,5000);
//fitGauss(hgndva0[i],mean,100,fitLow,fitHigh,fitFileOut);
hgndva0[i]->Draw();
wrspe(Form("hgndva0_%d",i),Form("angDist/hgndva0_%d.spe",i));
}


}
