{
  TH1 *pj[50];
  FILE * fitFileOut = fopen ("dtgeFit.dat", "w+");
TCanvas *cc;// = new TCanvas("cc","cc",800,800);

for (Int_t i=0;i<1;i++) {
cc = new TCanvas(Form("cc%d",i),Form("cc%d",i),900,900);
cc->Clear(); cc->Divide(5,5);

}

for (Int_t i=25;i<50;i++) {

  hdtge->ProjectionX(Form("px%d",i),i,i+1);
  pj[i] = (TH1D *)gDirectory->FindObjectAny(Form("px%d",i));
  pj[i]->GetXaxis()->SetRangeUser(300,3000);
  pj[i]->SetTitle(Form("g%d",i));
  //gSystem->GetObject(Form("px%d",i),pj[i]);

  // //1292
  // cc[0]->cd(); cc[0]->cd(i-24);
  // fprintf(fitFileOut,"%d %d %d ",0,2*i,2*(i+1));
  // pj[i]->GetXaxis()->SetRangeUser(1200,1350);
  // fitGaussP1(pj[i],1293,3,1282,1303,fitFileOut);
  //
  // //1535
  // cc[1]->cd(); cc[1]->cd(i-24);
  // fprintf(fitFileOut,"%d %d %d ",1,2*i,2*(i+1));
  // pj[i]->GetXaxis()->SetRangeUser(1400,1600);
  // fitGaussP1(pj[i],1535,3,1520,1550,fitFileOut);

  //2670
  cc->cd(); cc->cd(i-24);
  fprintf(fitFileOut,"%d %d %d ",2,2*i,2*(i+1));
  pj[i]->Rebin();
  pj[i]->GetXaxis()->SetRangeUser(2500,2800);
  fitGaussP1(pj[i],2666,5,2620,2720,fitFileOut);

  //385
  // cc->cd(); cc->cd(i-24);
  // fprintf(fitFileOut,"%d %d %d ",3,2*i,2*(i+1));
  // pj[i]->GetXaxis()->SetRangeUser(350,420);
  // fitGaussP1(pj[i],385,1,375,395,fitFileOut);

  //385
  // cc->cd(); cc->cd(i-24);
  // fprintf(fitFileOut,"%d %d %d ",3,2*i,2*(i+1));
  // pj[i]->GetXaxis()->SetRangeUser(350,420);
  // fitGaussP1(pj[i],385,1,375,395,fitFileOut);


}

fflush(fitFileOut);
fclose(fitFileOut);

}
