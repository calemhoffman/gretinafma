void mlPeakFitter(Int_t opt=1){
  //TFile fIn("pyTorchOut.root");
  TTree *tree = (TTree *)gDirectory->FindObjectAny("pytree");
  TH1F *hge[20];
  for (Int_t i=0;i<20;i++) {
    hge[i] = new TH1F(Form("hge%d",i),Form("hge%d",i),4000,0,4000);
  }
  TCanvas *cc = new TCanvas("cc","cc",800,600);
  Float_t mlcut=0;
  for (Int_t j=0;j<20;j++) {
     mlcut = 0.95 -(Float_t)j*0.05;
    if (opt==0) {
      tree->Draw(Form("ge>>hge%d",j),"","");
      j=20;
    } else {
      tree->Draw(Form("py_ge>>hge%d",j),Form("py_mlreturn>%f",mlcut),"");
    }
  }

  FILE * fitFileOut;
  fitFileOut = fopen (Form("mlPeakFitter.out"), "w+");
  fprintf(fitFileOut,"\#s38 1293\n");
  for (Int_t j=0;j<20;j++) {
    mlcut = 0.95 -(Float_t)j*0.05;
    fprintf(fitFileOut,"%.2f %d ",mlcut,j);
    fitGaussP0(hge[j],1293,3,1000,1200,1400,0,fitFileOut);
  }
  fprintf(fitFileOut,"\n\#s38 1535\n");
  for (Int_t j=0;j<20;j++) {
    mlcut = 0.95 -(Float_t)j*0.05;
    fprintf(fitFileOut,"%.2f %d ",mlcut,j);
    fitGaussP0(hge[j],1535,3,1000,1500,1600,0,fitFileOut);
  }
  fprintf(fitFileOut,"\n\#s38 383\n");
  for (Int_t j=0;j<20;j++) {
    mlcut = 0.95 -(Float_t)j*0.05;
    fprintf(fitFileOut,"%.2f %d ",mlcut,j);
    fitGaussP0(hge[j],383,1,1000,375,395,0,fitFileOut);
  }
  fprintf(fitFileOut,"\n\#s38 2320\n");
  for (Int_t j=0;j<20;j++) {
    mlcut = 0.95 -(Float_t)j*0.05;
    fprintf(fitFileOut,"%.2f %d ",mlcut,j);
    fitGaussP0(hge[j],2320,5,1000,2290,2350,0,fitFileOut);
  }
  fprintf(fitFileOut,"\n\#cl38 637\n");
  for (Int_t j=0;j<20;j++) {
    mlcut = 0.95 -(Float_t)j*0.05;
    fprintf(fitFileOut,"%.2f %d ",mlcut,j);
    fitGaussP0(hge[j],637,2,1000,620,655,0,fitFileOut);
  }
  fprintf(fitFileOut,"\n\#cl38 292\n");
  for (Int_t j=0;j<20;j++) {
    mlcut = 0.95 -(Float_t)j*0.05;
    fprintf(fitFileOut,"%.2f %d ",mlcut,j);
    fitGaussP0(hge[j],292,1,1000,285,297,0,fitFileOut);
  }
  fprintf(fitFileOut,"\n\#cl38 2044\n");
  for (Int_t j=0;j<20;j++) {
    mlcut = 0.95 -(Float_t)j*0.05;
    fprintf(fitFileOut,"%.2f %d ",mlcut,j);
    fitGaussP0(hge[j],2044,4,1000,2030,2060,0,fitFileOut);
  }
  fprintf(fitFileOut,"\n\#p33 1848\n");
  for (Int_t j=0;j<20;j++) {
    mlcut = 0.95 -(Float_t)j*0.05;
    fprintf(fitFileOut,"%.2f %d ",mlcut,j);
    fitGaussP0(hge[j],1848,3,1000,1830,1870,0,fitFileOut);
  }
  fprintf(fitFileOut,"\n\#p33 1432\n");
  for (Int_t j=0;j<20;j++) {
    mlcut = 0.95 -(Float_t)j*0.05;
    fprintf(fitFileOut,"%.2f %d ",mlcut,j);
    fitGaussP0(hge[j],1432,3,1000,1420,1442,0,fitFileOut);
  }

  //cc->SaveAs("cc.pdf");
  fflush(fitFileOut);
  fclose(fitFileOut);
  //fIn.Close();
  cc->cd();
  cc->Update();
}
