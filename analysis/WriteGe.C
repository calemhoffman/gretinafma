{
  /*
  Int_t det=15;
  // cDG2->Clear(); cDG2->Divide(2,2);
  for (Int_t i=0;i<4;i++) {
    //  cDG2->cd(i+1);

    wrspe(Form("hGeEnergy_%d_%d",det,i),Form("../gamma/hGeEnergy_%d_%d.spe",det,i));
  }


  for (Int_t i=0;i<16;i++) {
    //  cDG2->cd(i+1);
    if (i==0||i==2||i==4||i==8||i==10) {
      wrspe(Form("hClvrDirtyEnergy_%d",i),Form("../gamma/hClvrDirtyEnergy_%d.spe",i));
      wrspe(Form("hClvrCleanEnergy_%d",i),Form("../gamma/hClvrCleanEnergy_%d_six.spe",i));
    }
  }
  */

  //TString gate("0");
  // TString name("s38")

  hggAddBack0->ProjectionX();
  hggAddBack0->ProjectionY();
  wrspe("hggAddBack0_px","hgg_s38_px.spe");
  wrspe("hggAddBack0_py","hgg_s38_py.spe");
  TH1F *htotal_s38 = new TH1F("htotal_s38","Total Projection",4096,0,4096);
  htotal_s38->Add(hggAddBack0_px);
  htotal_s38->Add(hggAddBack0_py);
  wrspe("htotal_s38","hggAddBack_s38_pxpy.spe");
  wrspe("hg0","hg0_s38_gce.spe");
  wrRadmat("hggAddBack0");

}
