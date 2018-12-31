{
  TString cuts;
  cuts.Form("");
  TFile f("../../data/root_data/devel/run220.root");
  
  TCanvas *cCan;
  cCan = new TCanvas("cCan","cCan",800,800);
  cCan->Clear(); cCan->Divide(2,2);
  
  cCan->cd(1);gPad->SetLogz(1);
  tree->Draw("e1:e3>>he1e3(500,0,4000,500,0,4000)",cuts,"colz");
  
  cCan->cd(2);gPad->SetLogz(1);
  tree->Draw("deltaTime:gammaEnergy>>hdtGe(1000,0,6000,75,0,150)",cuts,"colz");
  
  cCan->cd(3);gPad->SetLogz(1);
  tree->Draw("e1:(left-right/0.934829)>>he1x(1000,-2500,2500,500,0,4000)",cuts,"colz");
  
  cCan->cd(4);gPad->SetLogz(1);
  tree->Draw("left/0.934829:right>>hlr(500,0,4000,500,0,4000)",cuts,"colz");
  
  cCan->Update();
}
