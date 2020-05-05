{
  //5k, ~0.25(4.8k),0.54,0.64
  //lowest cut 0.22,0.25,0.25
  //4k, 0.6, 0.74, 0.81
  //3k 0.765, 0.835,0.875
  //no backgrounds, >0.81, >0.85, >0.88
  TCanvas *cc = new TCanvas("cc","cc",1200,600);
  // TFile fk("pyTorchOutAverageSkinK.root");
  // TTree *tk = pytree;
  // TH1F *hk = new TH1F("hk","hk",4000,0,4000);
  // tk->Draw("py_ge>>hk","py_mlreturn>0.22","");
  // hk->SetLineColor(kBlack); hk->SetLineWidth(2);
  // fitGaussP0(hk,1293,3,10,1250,1350);
  // fitGaussP0(hk,1190,3,10,1150,1225);
  // fitGaussP0(hk,3142,6,5,3100,3200);
  // printf("Integral hk: %.0f\n",hk->Integral());

  // TFile fj("pyTorchOutAverageAverageJ.root");
  // TTree *tj = pytree;
  // TH1F *hj = new TH1F("hj","hj",4000,0,4000);
  // tj->Draw("py_ge>>hj","py_mlreturn>0.88","same");
  // hj->SetLineColor(kRed); hj->SetLineWidth(2);
  // fitGaussP0(hj,1293,3,10,1250,1350);
  // fitGaussP0(hj,1190,3,10,1150,1225);
  // fitGaussP0(hj,3142,6,5,3100,3200);
  // printf("Integral hj: %.0f\n",hj->Integral());
  TFile fn("pyTorchOutAverageFatN.root");
  TTree *tn = pytree;
  TH1F *hn = new TH1F("hn","hn",4000,0,4000);
  tn->Draw("py_ge>>hn","py_mlreturn>0.4","same");
  hn->SetLineColor(kRed); hn->SetLineWidth(2);
  fitGaussP0(hn,1293,3,10,1250,1350);
  fitGaussP0(hn,1190,3,10,1150,1225);
  fitGaussP0(hn,3142,6,5,3100,3200);
  printf("Integral hn: %.0f\n",hn->Integral());

  TFile ff("pyTorchOutAverageFatF.root");
  TTree *tf = pytree;
  TH1F *hf = new TH1F("hf","hf",4000,0,4000);
  tf->Draw("py_ge>>hf","py_mlreturn>0.6","same");
  hf->SetLineColor(kBlue); hf->SetLineWidth(2);
  fitGaussP0(hf,1293,3,10,1250,1350);
  fitGaussP0(hf,1190,3,10,1150,1225);
  fitGaussP0(hf,3142,6,5,3100,3200);
  printf("Integral hf: %.0f\n",hf->Integral());

  //hk->Draw("hist");
  hn->Draw("hist"); hf->Draw("same hist");

  // TFile fi("pyTorchOutAverageAverageI.root");
  // TTree *ti = pytree;
  // TH1F *hi = new TH1F("hi","hi",4000,0,4000);
  // ti->Draw("py_ge>>hi","py_mlreturn>0.75","");
  // hi->SetLineColor(kBlack); hi->SetLineWidth(2);

  // TFile fd("pyTorchOutAverageFatD.root");
  // TTree *td = pytree;
  // TH1F *hd = new TH1F("hd","hd",4000,0,4000);
  // hd->SetLineColor(kRed);
  // td->Draw("py_ge>>hd","py_mlreturn>0.4","");

  // TFile fc("pyTorchOutAverageFatC.root");
  // TTree *tc = pytree;
  // TH1F *hc = new TH1F("hc","hc",4000,0,4000);
  // tc->Draw("py_ge>>hc","py_mlreturn>0.55","same");

  // TFile fe("pyTorchOutAverageFatE.root");
  // TTree *te = pytree;
  // TH1F *he = new TH1F("he","he",4000,0,4000);
  // te->Draw("py_ge>>he","py_mlreturn>0.71","same");
  // he->SetLineColor(kBlack); he->SetLineWidth(2);
  //
  //


  //
  // TFile fg("pyTorchOutAverageFatG.root");
  // TTree *tg = pytree;
  // TH1F *hg = new TH1F("hg","hg",4000,0,4000);
  // tg->Draw("py_ge>>hg","py_mlreturn>0.64","same");
  // hg->SetLineColor(kBlue); hg->SetLineWidth(2);
  //
  // TFile fh("pyTorchOutAverageFatH.root");
  // TTree *th = pytree;
  // TH1F *hh = new TH1F("hh","hh",4000,0,4000);
  // th->Draw("py_ge>>hh","py_mlreturn>0.83","same");
  // hh->SetLineColor(kGreen+2); hh->SetLineWidth(2);

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
