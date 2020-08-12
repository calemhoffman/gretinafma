{ //script to load and draw spectra related to cuts for ml
  //e.g., e1e3, e0x, xa, etc...
  Int_t ci = 1756; // color index
  TColor *color = new TColor(ci, 0.1, 0.2, 0.3);
  TFile fTotal("cal28full.root");
  TTree *ct = ctree;
  ct;
  ct->SetAlias("m","((e[0]+e[2])*dtime*dtime)/1.0e4");

  TFile fml("pyTorchOutNewV.root");
  TTree *pt = pytree;
  pt;

  //general styles and canvas
  gStyle->SetPalette(kGreyScale);
  TCanvas *cc = new TCanvas("cc","cc",1200,600);


//histograms
  Float_t trans=0.25;
  Float_t mlcut[5]={0.0,0.3,0.5,0.8,1.0};

  TH2F *he1xc = new TH2F("he1xc","; x; e0",600,-1000,1000,400,600,3000);
  ct->Draw("e[0]:x>>he1xc","Entry$<1e7&&e[1]>200&&dtime>70&&dtime<85&&cut_lr_fig","col");
  he1xc->SetStats(0);he1xc->GetZaxis()->SetRangeUser(1,1e2);
  TH2F *he1xp0 = new TH2F("he1xp0","; x; e0",600,-1000,1000,400,600,3000);
  pt->Draw("py_e[0]:py_x>>he1xp0",Form("Entry$<1e5&&py_mlreturn>%f",mlcut[0]),"same");
  he1xp0->SetStats(0); he1xp0->SetMarkerStyle(20);
  he1xp0->SetMarkerColorAlpha(kGray+1, trans);
  TH2F *he1xp1 = new TH2F("he1xp1","; x; e0",600,-1000,1000,400,600,3000);
  pt->Draw("py_e[0]:py_x>>he1xp1",Form("Entry$<1e5&&py_mlreturn>%f",mlcut[1]),"same");
  he1xp1->SetStats(0); he1xp1->SetMarkerStyle(20);
  he1xp1->SetMarkerColorAlpha(kYellow+1, trans);
  TH2F *he1xp2 = new TH2F("he1xp2","; x; e0",600,-1000,1000,400,600,3000);
  pt->Draw("py_e[0]:py_x>>he1xp2",Form("Entry$<1e5&&py_mlreturn>%f",mlcut[2]),"same");
  he1xp2->SetStats(0); he1xp2->SetMarkerStyle(20);
  he1xp2->SetMarkerColorAlpha(kCyan, trans);
  TH2F *he1xp3 = new TH2F("he1xp3","; x; e0",600,-1000,1000,400,600,3000);
  pt->Draw("py_e[0]:py_x>>he1xp3",Form("Entry$<1e5&&py_mlreturn>%f",mlcut[3]),"same");
  he1xp3->SetStats(0); he1xp3->SetMarkerStyle(20);
  he1xp3->SetMarkerColorAlpha(kMagenta-4, trans);

/*
  TH2F *hmxc = new TH2F("hmxc","; x; m",600,-1000,1000,250,500,3000);
  ct->Draw("m:x>>hmxc","Entry$<1e7&&e[1]>200&&dtime>70&&dtime<85&&cut_lr_fig","col");
  hmxc->SetStats(0);hmxc->GetZaxis()->SetRangeUser(1,1e2);
  TH2F *hmxp0 = new TH2F("hmxp0","; x; m",600,-1000,1000,250,500,3000);
  pt->Draw("py_m:py_x>>hmxp0",Form("Entry$<1e5&&py_mlreturn>%f&&cut_mx_figpy",mlcut[0]),"same");
  hmxp0->SetStats(0); hmxp0->SetMarkerStyle(20);
  hmxp0->SetMarkerColorAlpha(kGray+1, trans);
  TH2F *hmxp1 = new TH2F("hmxp1","; x; m",600,-1000,1000,250,500,3000);
  pt->Draw("py_m:py_x>>hmxp1",Form("Entry$<1e5&&py_mlreturn>%f&&cut_mx_figpy",mlcut[1]),"same");
  hmxp1->SetStats(0); hmxp1->SetMarkerStyle(20);
  hmxp1->SetMarkerColorAlpha(kYellow+1, trans);
  TH2F *hmxp2 = new TH2F("hmxp2","; x; m",600,-1000,1000,250,500,3000);
  pt->Draw("py_m:py_x>>hmxp2",Form("Entry$<1e5&&py_mlreturn>%f&&cut_mx_figpy",mlcut[2]),"same");
  hmxp2->SetStats(0); hmxp2->SetMarkerStyle(20);
  hmxp2->SetMarkerColorAlpha(kCyan, trans);
  TH2F *hmxp3 = new TH2F("hmxp3","; x; m",600,-1000,1000,250,500,3000);
  pt->Draw("py_m:py_x>>hmxp3",Form("Entry$<1e5&&py_mlreturn>%f&&cut_mx_figpy",mlcut[3]),"same");
  hmxp3->SetStats(0); hmxp3->SetMarkerStyle(20);
  hmxp3->SetMarkerColorAlpha(kMagenta-4, trans);

//redraws and cleanup
cc->Clear(); cc->Divide(2,1);
cc->cd(1);
hmxc->Rebin2D(); hmxc->SetMinimum(2); hmxc->SetMaximum(200);
hmxc->Draw("col");
cut_mx_fig->SetLineColor(kGray+1); cut_mx_fig->SetLineWidth(2);
cut_mx_fig->Draw("same");

cc->cd(2);
hmxc->Draw("col");
hmxp0->Draw("same");
hmxp1->Draw("same"); hmxp2->Draw("same"); hmxp3->Draw("same");
*/
//TCanvas *cc = new TCanvas("cc","cc",1200,600);
cc->Clear(); cc->Divide(2,1);
cc->cd(1);
he1xc->Rebin2D(); he1xc->SetMinimum(2); he1xc->SetMaximum(200);
he1xc->Draw("col");
// cut_e1x_NEW->SetLineColor(kGray+1); cut_e1x_NEW->SetLineWidth(2);
// cut_e1x_NEW->Draw("same");

cc->cd(2);
he1xc->Draw("col");
he1xp0->Draw("same");
he1xp1->Draw("same"); he1xp2->Draw("same"); he1xp3->Draw("same");
}
