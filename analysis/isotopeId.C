{
  Int_t runN=77;
  Float_t scaleF=1.15;
  
  TString cuts;
  cuts.Form("gcut1||gcut2||gcut3||gcut4");
  //TFile f("../../data/root_data/devel/run200.root");
  TFile f(Form("cal_%d.root",runN));
  
  TCanvas *cCan;
  cCan = new TCanvas("cCan","cCan",1400,800);
  cCan->Clear(); cCan->Divide(3,2);
  
  cCan->cd(1);//gPad->SetLogz(1);
  ctree->Draw("e[0]:e[1]>>he1e2(500,0,4000,500,0,4000)",cuts,"colz");
  cut_ref_e1e2->Draw("same");
  cCan->cd(2);//gPad->SetLogz(1);
  ctree->Draw("e[0]:e[2]>>he1e3(500,0,4000,500,0,4000)",cuts,"colz");
  cut_ref_e1e3->Draw("same");
  cCan->cd(3);//gPad->SetLogz(1);
  ctree->Draw("e[0]:e[0]+e[2]>>he1e13(1000,0,8000,500,0,4000)",cuts,"colz");
  cut_ref_e1e13->Draw("same");

  cCan->cd(4);
  ctree->Draw("e[0]>>he1(500,0,4000)","e[2]>800&&e[2]<1000","");
  hist_ref_e1__1->SetLineColor(2); hist_ref_e1__1->Scale(scaleF); hist_ref_e1__1->Draw("same");
  cCan->cd(5);
  ctree->Draw("e[1]>>he2(500,0,4000)","e[2]>800&&e[2]<1000","");
  hist_ref_e2__2->SetLineColor(2); hist_ref_e2__2->Scale(scaleF); hist_ref_e2__2->Draw("same");
  cCan->cd(6);
  ctree->Draw("e[2]>>he3(500,0,4000)","e[0]>1400&&e[0]<1600","");
  hist_ref_e3__3->SetLineColor(2); hist_ref_e3__3->Scale(scaleF); hist_ref_e3__3->Draw("same");
  cCan->SaveAs(Form("figures/cCan1_r%d.pdf",runN));
  cCan->SaveAs(Form("figures/cCan1_r%d.C",runN));
	         
  TCanvas *cCan2;
  cCan2 = new TCanvas("cCan2","cCan2",1200,800);
  cCan2->Clear(); cCan2->Divide(2,2);
 
  cCan2->cd(1);gPad->SetLogz(1);
  ctree->Draw("dtime:genergy>>hdtGe(1000,0,6000,75,0,150)","","colz");
  gcut1->Draw("same"); gcut2->Draw("same"); gcut3->Draw("same"); gcut4->Draw("same");
  cut_ref_dtge->Draw("same");
  //ctree->Draw("e[0]:(l+r/0.934829)>>he1xsum(1000,0,10000,500,0,4000)",cuts,"colz");
  
  cCan2->cd(2);//gPad->SetLogz(1);
  ctree->Draw("e[0]:x>>he1x(1000,-2500,2500,500,0,4000)",cuts,"colz");
  cut_ref_e1x->Draw("same");
  cCan2->cd(3);
  ctree->Draw("x>>hx(1000,-2500,2500)",cuts,"");

  cCan2->cd(4);gPad->SetLogz(1);
  ctree->Draw("l:r>>hlr(500,0,4000,500,0,4000)",cuts,"colz");
  cut_ref_lr->Draw("same");

  cCan2->SaveAs(Form("figures/cCan2_r%d.pdf",runN));
  cCan2->SaveAs(Form("figures/cCan2_r%d.C",runN));

  /* TCanvas *cCan; */
  /* cCan = new TCanvas("cCan","cCan",800,800); */
  /* cCan->Clear(); cCan->Divide(2,2); */
  
  /* cCan->cd(1);gPad->SetLogz(1); */
  /* ctree->Draw("e1:e3>>he1e3(500,0,4000,500,0,4000)",cuts,"colz"); */
  
  /* cCan->cd(2);gPad->SetLogz(1); */
  /* ctree->Draw("deltaTime:gammaEnergy>>hdtGe(1000,0,6000,75,0,150)",cuts,"colz"); */
  
  /* cCan->cd(3);gPad->SetLogz(1); */
  /* ctree->Draw("e1:(left-right/0.934829)>>he1x(1000,-2500,2500,500,0,4000)",cuts,"colz"); */
  
  /* cCan->cd(4);gPad->SetLogz(1); */
  /* ctree->Draw("left/0.934829:right>>hlr(500,0,4000,500,0,4000)",cuts,"colz"); */

}
