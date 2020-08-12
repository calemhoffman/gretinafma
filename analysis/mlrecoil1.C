{ //e1e3, e1e2 only
  //script to load and draw spectra related to cuts for ml
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

//cut values
Float_t mlcut[5]={0.0,0.3,0.5,0.8,1.0};
//histograms
  Float_t trans=0.25;
  /*
  TH2F *he1e3c = new TH2F("he1e3c","; e2; e0",600,0,4000,400,600,3000);
  ct->Draw("e[0]:e[2]>>he1e3c","Entry$<1e7&&e[1]>200&&dtime>70&&dtime<85","col");
  he1e3c->SetStats(0);he1e3c->GetZaxis()->SetRangeUser(1,1e2);
  TH2F *he1e3p0 = new TH2F("he1e3p0","; e2; e0",600,0,4000,400,600,3000);
  pt->Draw("py_e[0]:py_e[2]>>he1e3p0",Form("Entry$<1e5&&py_mlreturn>%f&&cut_e1e3_figpy",mlcut[0]),"same");
  he1e3p0->SetStats(0); he1e3p0->SetMarkerStyle(20);
  he1e3p0->SetMarkerColorAlpha(kGray+1, trans);
  TH2F *he1e3p1 = new TH2F("he1e3p1","; e2; e0",600,0,4000,400,600,3000);
  pt->Draw("py_e[0]:py_e[2]>>he1e3p1",Form("Entry$<1e5&&py_mlreturn>%f&&cut_e1e3_figpy",mlcut[1]),"same");
  he1e3p1->SetStats(0); he1e3p1->SetMarkerStyle(20);
  he1e3p1->SetMarkerColorAlpha(kYellow+1, trans);
  TH2F *he1e3p2 = new TH2F("he1e3p2","; e2; e0",600,0,4000,400,600,3000);
  pt->Draw("py_e[0]:py_e[2]>>he1e3p2",Form("Entry$<1e5&&py_mlreturn>%f&&cut_e1e3_figpy",mlcut[2]),"same");
  he1e3p2->SetStats(0); he1e3p2->SetMarkerStyle(20);
  he1e3p2->SetMarkerColorAlpha(kCyan, trans);
  TH2F *he1e3p3 = new TH2F("he1e3p3","; e2; e0",600,0,4000,400,600,3000);
  pt->Draw("py_e[0]:py_e[2]>>he1e3p3",Form("Entry$<1e5&&py_mlreturn>%f&&cut_e1e3_figpy",mlcut[3]),"same");
  he1e3p3->SetStats(0); he1e3p3->SetMarkerStyle(20);
  he1e3p3->SetMarkerColorAlpha(kMagenta-4, trans); // he1e3p60->SetMarkerColor(kBlue);
*/
  TH2F *he1e2c = new TH2F("he1e2c","; e1; e0",600,200,2500,400,600,3000);
  ct->Draw("e[0]:e[1]>>he1e2c","Entry$<1e7&&e[1]>200&&dtime>70&&dtime<85","col");
  he1e2c->SetStats(0);he1e2c->GetZaxis()->SetRangeUser(1,1e2);
  TH2F *he1e2p0 = new TH2F("he1e2p0","; e1; e0",600,200,2500,400,600,3000);
  pt->Draw("py_e[0]:py_e[1]>>he1e2p0",Form("Entry$<1e5&&py_mlreturn>%f&&cut_e1e2_figpy",mlcut[0]),"same");
  he1e2p0->SetStats(0); he1e2p0->SetMarkerStyle(20);
  he1e2p0->SetMarkerColorAlpha(kGray+1, trans);
  TH2F *he1e2p1 = new TH2F("he1e2p1","; e1; e0",600,200,2500,400,600,3000);
  pt->Draw("py_e[0]:py_e[1]>>he1e2p1",Form("Entry$<1e5&&py_mlreturn>%f&&cut_e1e2_figpy",mlcut[1]),"same");
  he1e2p1->SetStats(0); he1e2p1->SetMarkerStyle(20);
  he1e2p1->SetMarkerColorAlpha(kYellow+1, trans);
  TH2F *he1e2p2 = new TH2F("he1e2p2","; e1; e0",600,200,2500,400,600,3000);
  pt->Draw("py_e[0]:py_e[1]>>he1e2p2",Form("Entry$<1e5&&py_mlreturn>%f&&cut_e1e2_figpy",mlcut[2]),"same");
  he1e2p2->SetStats(0); he1e2p2->SetMarkerStyle(20);
  he1e2p2->SetMarkerColorAlpha(kCyan, trans);
  TH2F *he1e2p3 = new TH2F("he1e2p3","; e1; e0",600,200,2500,400,600,3000);
  pt->Draw("py_e[0]:py_e[1]>>he1e2p3",Form("Entry$<1e5&&py_mlreturn>%f&&cut_e1e2_figpy",mlcut[3]),"same");
  he1e2p3->SetStats(0); he1e2p3->SetMarkerStyle(20);
  he1e2p3->SetMarkerColorAlpha(kMagenta-4, trans); // he1e2p60->SetMarkerColor(kBlue);


//redraws and cleanup
/*
cc->Clear(); cc->Divide(2,1);
cc->cd(1);
he1e3c->Rebin2D(); he1e3c->SetMinimum(2); he1e3c->SetMaximum(1e3);
he1e3c->Draw("col");
cut_e1e3_fig->SetFillColorAlpha(kGray+1,0.5);
cut_e1e3_fig->SetLineWidth(2); cut_e1e3_fig->SetLineColor(kGray+1);
cut_e1e3_fig->Draw("same");
//cut_e1e3_NEW->Draw("same");
cc->Update();
cc->cd(2);
//TCanvas *cc1 = new TCanvas("cc1","cc1",600,600);
he1e3c->Draw("col");he1e3p0->Draw("same");
he1e3p1->Draw("same"); he1e3p2->Draw("same"); he1e3p3->Draw("same");
cc->Update();
*/

TCanvas *cc2 = new TCanvas("cc2","cc2",1200,600);
cc2->Clear();cc2->Divide(2,1);
cc2->cd(1);
he1e2c->Rebin2D(); he1e2c->SetMinimum(2); he1e2c->SetMaximum(1e3);
he1e2c->Draw("col");
cut_e1e2_fig->SetFillColorAlpha(kGray+1,0.5);
cut_e1e2_fig->SetLineWidth(2); cut_e1e2_fig->SetLineColor(kGray+1);
cut_e1e2_fig->Draw("same");
cc2->Update();
cc2->cd(2);
//TCanvas *cc1 = new TCanvas("cc1","cc1",600,600);
he1e2c->Draw("col");he1e2p0->Draw("same");
he1e2p1->Draw("same"); he1e2p2->Draw("same"); he1e2p3->Draw("same");
cc2->Update();
//
// TCanvas *cc3 = new TCanvas("cc3","cc3",600,600);

}
