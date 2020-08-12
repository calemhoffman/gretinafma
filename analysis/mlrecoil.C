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
  TCanvas *cc = new TCanvas("cc","cc",600,600);


//histograms
  Float_t trans=0.25;
  TH2F *he1e3c = new TH2F("he1e3c","; e2; e0",600,0,4000,400,600,3000);
  ct->Draw("e[0]:e[2]>>he1e3c","Entry$<1e7&&e[1]>200&&dtime>70&&dtime<85","col");
  he1e3c->SetStats(0);he1e3c->GetZaxis()->SetRangeUser(1,1e2);
  TH2F *he1e3p0 = new TH2F("he1e3p0","; e2; e0",600,0,4000,400,600,3000);
  pt->Draw("py_e[0]:py_e[2]>>he1e3p0","Entry$<1e5&&py_mlreturn>0.0","same");
  he1e3p0->SetStats(0); he1e3p0->SetMarkerStyle(20);
  he1e3p0->SetMarkerColorAlpha(kGray+1, trans);
  TH2F *he1e3p1 = new TH2F("he1e3p1","; e2; e0",600,0,4000,400,600,3000);
  pt->Draw("py_e[0]:py_e[2]>>he1e3p1","Entry$<1e5&&py_mlreturn>0.3","same");
  he1e3p1->SetStats(0); he1e3p1->SetMarkerStyle(20);
  he1e3p1->SetMarkerColorAlpha(kYellow+1, trans);
  TH2F *he1e3p2 = new TH2F("he1e3p2","; e2; e0",600,0,4000,400,600,3000);
  pt->Draw("py_e[0]:py_e[2]>>he1e3p2","Entry$<1e5&&py_mlreturn>0.5","same");
  he1e3p2->SetStats(0); he1e3p2->SetMarkerStyle(20);
  he1e3p2->SetMarkerColorAlpha(kCyan, trans);
  TH2F *he1e3p3 = new TH2F("he1e3p3","; e2; e0",600,0,4000,400,600,3000);
  pt->Draw("py_e[0]:py_e[2]>>he1e3p3","Entry$<1e5&&py_mlreturn>0.8","same");
  he1e3p3->SetStats(0); he1e3p3->SetMarkerStyle(20);
  he1e3p3->SetMarkerColorAlpha(kMagenta-4, trans); // he1e3p60->SetMarkerColor(kBlue);

  TH2F *he1e2c = new TH2F("he1e2c","; e1; e0",600,200,2500,400,600,3000);
  ct->Draw("e[0]:e[1]>>he1e2c","Entry$<1e7&&e[1]>200&&dtime>70&&dtime<85","col");
  he1e2c->SetStats(0);he1e2c->GetZaxis()->SetRangeUser(1,1e2);
  TH2F *he1e2p1 = new TH2F("he1e2p1","; e1; e0",600,200,2500,400,600,3000);
  pt->Draw("py_e[0]:py_e[1]>>he1e2p1","Entry$<1e5&&py_mlreturn>0.3","same");
  he1e2p1->SetStats(0); he1e2p1->SetMarkerStyle(20);
  he1e2p1->SetMarkerColorAlpha(kYellow+1, trans);
  TH2F *he1e2p2 = new TH2F("he1e2p2","; e1; e0",600,200,2500,400,600,3000);
  pt->Draw("py_e[0]:py_e[1]>>he1e2p2","Entry$<1e5&&py_mlreturn>0.5","same");
  he1e2p2->SetStats(0); he1e2p2->SetMarkerStyle(20);
  he1e2p2->SetMarkerColorAlpha(kCyan, trans);
  TH2F *he1e2p3 = new TH2F("he1e2p3","; e1; e0",600,200,2500,400,600,3000);
  pt->Draw("py_e[0]:py_e[1]>>he1e2p3","Entry$<1e5&&py_mlreturn>0.8","same");
  he1e2p3->SetStats(0); he1e2p3->SetMarkerStyle(20);
  he1e2p3->SetMarkerColorAlpha(kMagenta-4, trans); // he1e2p60->SetMarkerColor(kBlue);

  TH2F *he1xc = new TH2F("he1xc","; x; e0",600,-1000,1000,400,600,3000);
  ct->Draw("e[0]:x>>he1xc","Entry$<1e7&&e[1]>200&&dtime>70&&dtime<85&&l>7&&r>0","col");
  he1xc->SetStats(0);he1xc->GetZaxis()->SetRangeUser(1,1e2);
  TH2F *he1xp1 = new TH2F("he1xp1","; x; e0",600,-1000,1000,400,600,3000);
  pt->Draw("py_e[0]:py_x>>he1xp1","Entry$<1e5&&py_mlreturn>0.3","same");
  he1xp1->SetStats(0); he1xp1->SetMarkerStyle(20);
  he1xp1->SetMarkerColorAlpha(kYellow+1, trans);
  TH2F *he1xp2 = new TH2F("he1xp2","; x; e0",600,-1000,1000,400,600,3000);
  pt->Draw("py_e[0]:py_x>>he1xp2","Entry$<1e5&&py_mlreturn>0.5","same");
  he1xp2->SetStats(0); he1xp2->SetMarkerStyle(20);
  he1xp2->SetMarkerColorAlpha(kCyan, trans);
  TH2F *he1xp3 = new TH2F("he1xp3","; x; e0",600,-1000,1000,400,600,3000);
  pt->Draw("py_e[0]:py_x>>he1xp3","Entry$<1e5&&py_mlreturn>0.8","same");
  he1xp3->SetStats(0); he1xp3->SetMarkerStyle(20);
  he1xp3->SetMarkerColorAlpha(kMagenta-4, trans);

  TH2F *hmxc = new TH2F("hmxc","; x; m",600,-1000,1000,400,0,4000);
  ct->Draw("m:x>>hmxc","Entry$<1e7&&e[1]>200&&dtime>70&&dtime<85&&l>0&&r>0","col");
  hmxc->SetStats(0);hmxc->GetZaxis()->SetRangeUser(1,1e2);
  TH2F *hmxp0 = new TH2F("hmxp0","; x; m",600,-1000,1000,400,0,4000);
  pt->Draw("py_m:py_x>>hmxp0","Entry$<1e5&&py_mlreturn>0.0","same");
  hmxp0->SetStats(0); hmxp0->SetMarkerStyle(20);
  hmxp0->SetMarkerColorAlpha(kGray+1, trans);
  TH2F *hmxp1 = new TH2F("hmxp1","; x; m",600,-1000,1000,400,0,4000);
  pt->Draw("py_m:py_x>>hmxp1","Entry$<1e5&&py_mlreturn>0.3","same");
  hmxp1->SetStats(0); hmxp1->SetMarkerStyle(20);
  hmxp1->SetMarkerColorAlpha(kYellow+1, trans);
  TH2F *hmxp2 = new TH2F("hmxp2","; x; m",600,-1000,1000,400,0,4000);
  pt->Draw("py_m:py_x>>hmxp2","Entry$<1e5&&py_mlreturn>0.5","same");
  hmxp2->SetStats(0); hmxp2->SetMarkerStyle(20);
  hmxp2->SetMarkerColorAlpha(kCyan, trans);
  TH2F *hmxp3 = new TH2F("hmxp3","; x; m",600,-1000,1000,400,0,4000);
  pt->Draw("py_m:py_x>>hmxp3","Entry$<1e5&&py_mlreturn>0.8","same");
  hmxp3->SetStats(0); hmxp3->SetMarkerStyle(20);
  hmxp3->SetMarkerColorAlpha(kMagenta-4, trans);

//redraws and cleanup
cc->Clear(); //cc->Divide(2,2);'
he1e3c->Rebin2D(); he1e3c->SetMinimum(2); he1e3c->SetMaximum(1e3);
he1e3c->Draw("col");
//cut_e1e3_NEW->Draw("same");
cc->Update();

TCanvas *cc1 = new TCanvas("cc1","cc1",600,600);
he1e3c->Draw("colz");he1e3p0->Draw("same");
he1e3p1->Draw("same"); he1e3p2->Draw("same"); he1e3p3->Draw("same");

TCanvas *cc2 = new TCanvas("cc2","cc2",600,600);
cc2->Clear();
hmxc->Rebin2D(); hmxc->SetMinimum(2); hmxc->SetMaximum(1e3);
hmxc->Draw("colz");

TCanvas *cc3 = new TCanvas("cc3","cc3",600,600);
hmxc->Draw("colz");
hmxp0->Draw("same");
hmxp1->Draw("same"); hmxp2->Draw("same"); hmxp3->Draw("same");
// cc->cd(2);
// // he1e2c->Draw("colz");he1e2p1->Draw("same"); he1e2p2->Draw("same"); he1e2p3->Draw("same");
// he1xc->Draw("colz");he1xp1->Draw("same"); he1xp2->Draw("same"); he1xp3->Draw("same");
//
// cc->cd(3);
// hmxc->Draw("colz");hmxp0->Draw("same");
// hmxp1->Draw("same"); hmxp2->Draw("same"); hmxp3->Draw("same");
//
// cc->cd(4);
//
//   cc->Update();
//   cc->SaveAs("mlrecoil.png");




}
