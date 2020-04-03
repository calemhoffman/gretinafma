{
  TCanvas *cc = new TCanvas("cc","cc",1200,600);
  // TFile fd("pyTorchOutAverageFatD.root");
  // TTree *td = pytree;
  // TH1F *hd = new TH1F("hd","hd",4000,0,4000);
  // hd->SetLineColor(kRed);
  // td->Draw("py_ge>>hd","py_mlreturn>0.4","");

  // TFile fc("pyTorchOutAverageFatC.root");
  // TTree *tc = pytree;
  // TH1F *hc = new TH1F("hc","hc",4000,0,4000);
  // tc->Draw("py_ge>>hc","py_mlreturn>0.55","same");

  TFile fe("pyTorchOutAverageFatE.root");
  TTree *te = pytree;
  TH1F *he = new TH1F("he","he",4000,0,4000);
  te->Draw("py_ge>>he","py_mlreturn>0.71","same");
  he->SetLineColor(kBlack); he->SetLineWidth(2);


  TFile ff("pyTorchOutAverageFatF.root");
  TTree *tf = pytree;
  TH1F *hf = new TH1F("hf","hf",4000,0,4000);
  tf->Draw("py_ge>>hf","py_mlreturn>0.64","same");
  hf->SetLineColor(kRed); hf->SetLineWidth(2);

  TFile fg("pyTorchOutAverageFatG.root");
  TTree *tg = pytree;
  TH1F *hg = new TH1F("hg","hg",4000,0,4000);
  tg->Draw("py_ge>>hg","py_mlreturn>0.64","same");
  hg->SetLineColor(kBlue); hg->SetLineWidth(2);

  TFile fh("pyTorchOutAverageFatH.root");
  TTree *th = pytree;
  TH1F *hh = new TH1F("hh","hh",4000,0,4000);
  th->Draw("py_ge>>hh","py_mlreturn>0.83","same");
  hh->SetLineColor(kGreen+2); hh->SetLineWidth(2);

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
