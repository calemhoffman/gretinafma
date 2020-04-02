{
  TCanvas *cc = new TCanvas("cc","cc",1200,600);
  TFile fd("pyTorchOutAverageFatD.root");
  TTree *td = pytree;
  TH1F *hd = new TH1F("hd","hd",4000,0,4000);
  hd->SetLineColor(kRed);
  td->Draw("py_ge>>hd","py_mlreturn>0.4","");

  // TFile fc("pyTorchOutAverageFatC.root");
  // TTree *tc = pytree;
  // TH1F *hc = new TH1F("hc","hc",4000,0,4000);
  // tc->Draw("py_ge>>hc","py_mlreturn>0.55","same");

  TFile fe("pyTorchOutAverageFatE.root");
  TTree *te = pytree;
  TH1F *he = new TH1F("he","he",4000,0,4000);
  te->Draw("py_ge>>he","py_mlreturn>0.4","same");

  // TFile fe("pyTorchOutAverageFatE.root");
  // TTree *te = pytree;
  // TH1F *he;
  // te->Draw("py_ge>>he(4000,0,4000)","py_mlreturn>0.5","same");
  //
  // TFile fb("pyTorchOutAverageFatB.root");
  // TTree *tb = pytree;
  // TH1F *hb;
  // tb->Draw("py_ge>>hb(4000,0,4000)","py_mlreturn>0.5","same");

//
  // cc->Clear(); cc->cd();
  // fc.cd();
  // hc->SetLineColor(0); hc->Draw();
  // fd.cd();
  // hd->SetLineColor(1); hd->Draw("same");
  // fe.cd();
  // he->SetLineColor(2); he->Draw("same");

}
