{ //script to load and draw spectra related to cuts for ml
  //e.g., e1e3, e0x, xa, etc...
  Int_t ci_blu = 1756; // color index
  Int_t ci_yel = 1757; // color index
  Int_t ci_pur = 1758; // color index
  Int_t ci_gre = 1759; // color index
  TColor *clr_blu = new TColor(ci_blu, 44.0/255.0, 189.0/255.0, 254.0/255.0);
  TColor *clr_yel = new TColor(ci_yel, 245.0/255.0, 177.0/255.0, 76.0/255.0);
  TColor *clr_pur = new TColor(ci_pur, 243.0/255.0, 160.0/255.0, 242.0/255.0);
  TColor *clr_gre = new TColor(ci_gre, 161.0/255.0, 164.0/255.0, 167.0/255.0);
  TFile fTotal("cal28full.root");
  TTree *ct = ctree;
  ct;
  ct->SetAlias("m","((e[0]+e[2])*dtime*dtime)/1.0e4");
  ct->SetAlias("m2","((e[0]+e[1]+e[2])*dtime*dtime)/1.0e4");

  //TFile fml("pyTorchOutNewV.root");
  TFile fml("pyTorchOutAverageFatQb.root");
  TTree *pt = pytree;
  pt;
  pt->SetAlias("py_m2","((py_e[0]+py_e[1]+py_e[2])*py_dt*py_dt)/1.0e4");

  //general styles and canvas
  gStyle->SetPalette(kGreyScale);
  TCanvas *cc = new TCanvas("cc","cc",1200,600);


//histograms
  Float_t trans=0.25;
  //Float_t mlcut[5]={0.0,0.3,0.5,0.8,1.0};
  Float_t mlcut[5]={0.0,0.25,0.6,0.8,1.0};

  TH2F *he1xc = new TH2F("he1xc","; x [arb. units]; E_{1} [arb. units]",250,-1000,1000,400,0,4000);
  ct->Draw("e[0]:x>>he1xc","Entry$<1e9&&e[1]>200&&dtime>70&&dtime<85&&cut_lr_fig","col");
  he1xc->SetStats(0);he1xc->GetZaxis()->SetRangeUser(1,1e2);
  TH2F *he1xp0 = new TH2F("he1xp0","; x [arb. units]; E_{1} [arb. units]",250,-1000,1000,400,0,4000);
  pt->Draw("py_e[0]:py_x>>he1xp0",Form("Entry$<1e5&&py_mlreturn>%f&&py_mlreturn<=%f",mlcut[0],mlcut[1]),"same");
  he1xp0->SetStats(0); he1xp0->SetMarkerStyle(20);
  he1xp0->SetMarkerColorAlpha(ci_gre, trans);
  TH2F *he1xp1 = new TH2F("he1xp1","; x [arb. units]; E_{1} [arb. units]",250,-1000,1000,400,0,4000);
  pt->Draw("py_e[0]:py_x>>he1xp1",Form("Entry$<1e5&&py_mlreturn>%f",mlcut[1]),"same");
  he1xp1->SetStats(0); he1xp1->SetMarkerStyle(20);
  he1xp1->SetMarkerColorAlpha(ci_yel, trans);
  TH2F *he1xp2 = new TH2F("he1xp2","; x [arb. units]; E_{1} [arb. units]",250,-1000,1000,400,0,4000);
  pt->Draw("py_e[0]:py_x>>he1xp2",Form("Entry$<1e5&&py_mlreturn>%f",mlcut[2]),"same");
  he1xp2->SetStats(0); he1xp2->SetMarkerStyle(20);
  he1xp2->SetMarkerColorAlpha(ci_blu, trans);
  TH2F *he1xp3 = new TH2F("he1xp3","; x [arb. units]; E_{1} [arb. units]",250,-1000,1000,400,0,4000);
  pt->Draw("py_e[0]:py_x>>he1xp3",Form("Entry$<1e5&&py_mlreturn>%f",mlcut[3]),"same");
  he1xp3->SetStats(0); he1xp3->SetMarkerStyle(20);
  he1xp3->SetMarkerColorAlpha(ci_pur, trans);


  // TH2F *hmxc = new TH2F("hmxc","; x; m",600,-1000,1000,400,0,5000);
  // ct->Draw("m2:x>>hmxc","Entry$<1e9&&e[1]>200&&dtime>70&&dtime<85&&cut_lr_fig","col");
  // hmxc->SetStats(0);hmxc->GetZaxis()->SetRangeUser(1,1e2);
  // TH2F *hmxp0 = new TH2F("hmxp0","; x; m",600,-1000,1000,400,0,5000);
  // pt->Draw("py_m:py_x>>hmxp0",Form("Entry$<1e6&&py_mlreturn>%f",mlcut[0]),"same");
  // hmxp0->SetStats(0); hmxp0->SetMarkerStyle(20);
  // hmxp0->SetMarkerColorAlpha(ci_gre, trans);
  // TH2F *hmxp1 = new TH2F("hmxp1","; x; m",600,-1000,1000,400,0,5000);
  // pt->Draw("py_m:py_x>>hmxp1",Form("Entry$<1e5&&py_mlreturn>%f",mlcut[1]),"same");
  // hmxp1->SetStats(0); hmxp1->SetMarkerStyle(20);
  // hmxp1->SetMarkerColorAlpha(ci_yel, trans);
  // TH2F *hmxp2 = new TH2F("hmxp2","; x; m",600,-1000,1000,400,0,5000);
  // pt->Draw("py_m:py_x>>hmxp2",Form("Entry$<1e5&&py_mlreturn>%f",mlcut[2]),"same");
  // hmxp2->SetStats(0); hmxp2->SetMarkerStyle(20);
  // hmxp2->SetMarkerColorAlpha(ci_blu, trans);
  // TH2F *hmxp3 = new TH2F("hmxp3","; x; m",600,-1000,1000,400,0,5000);
  // pt->Draw("py_m:py_x>>hmxp3",Form("Entry$<1e5&&py_mlreturn>%f",mlcut[3]),"same");
  // hmxp3->SetStats(0); hmxp3->SetMarkerStyle(20);
  // hmxp3->SetMarkerColorAlpha(ci_pur, trans);

//redraws and cleanup
cc->Clear(); cc->Divide(2,1);
// cc->cd(1);
// hmxc->Rebin2D(); hmxc->SetMinimum(1); hmxc->SetMaximum(5e3);
// hmxc->Draw("col");
// // cut_mx_good->SetLineColor(kGray+1); cut_mx_fig->SetLineWidth(2);
// // cut_mx_good->Draw("same");
//
// cc->cd(2);
// hmxc->Draw("col");
// hmxp0->Draw("same");
// hmxp1->Draw("same"); hmxp2->Draw("same"); hmxp3->Draw("same");

TCanvas *cc2 = new TCanvas("cc2","cc2",1200,600);
cc2->Clear(); cc2->Divide(2,1);
cc2->cd(1);gPad->SetLogz();
he1xc->GetXaxis()->SetRangeUser(-1000,-1000);
he1xc->GetYaxis()->SetRangeUser(600,3000);
he1xc->GetXaxis()->SetLabelSize(0);
he1xc->GetXaxis()->SetTickLength(0);
he1xc->GetYaxis()->SetLabelSize(0);
he1xc->GetYaxis()->SetTickLength(0);
// he1e3c->SetXTitle("E_{2} [arb. units]")
// he1e3c->SetYTitle("E_{1} [arb. units]")
he1xc->GetXaxis()->CenterTitle();
he1xc->GetYaxis()->CenterTitle();

//he1xc->Rebin2D();
he1xc->SetMinimum(1); he1xc->SetMaximum(1e3);
he1xc->Draw("col");

// cut_e0x_s38->SetLineColor(kGray+1); cut_e0x_s38->SetLineWidth(2);
// cut_e0x_s38->Draw("same");

cc2->cd(2);gPad->SetLogz();
he1xp0->SetMinimum(1);he1xp0->SetMaximum(100);
he1xp1->SetMinimum(1);he1xp1->SetMaximum(100);
he1xp2->SetMinimum(1);he1xp2->SetMaximum(100);
he1xp3->SetMinimum(1);he1xp3->SetMaximum(100);
he1xc->Draw("col");
he1xp0->Draw("same");
he1xp1->Draw("same");
he1xp2->Draw("same");
he1xp3->Draw("same");
}
