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

  hgg1->ProjectionX();
  hgg1->ProjectionY();


  wrspe("hgg1_px","hgg_cl38_px.spe");
  wrspe("hgg1_py","hgg_cl38_py.spe");
  TH1F *htotal_cl38 = new TH1F("htotal_cl38","Total Projection",4096,0,4096);
  htotal_cl38->Add(hgg1_px);
  htotal_cl38->Add(hgg1_py);
  wrspe("htotal_cl38","hgg1_cl38_pxpy.spe");
  wrspe("hg1","hg1_cl38_gce.spe");
  wrRadmat("hgg1");

}
