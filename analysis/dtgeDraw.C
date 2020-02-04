{
  TH1 *pj[50];
  FILE * fitFileOut = fopen ("dtgeFit.dat", "w+");


for (Int_t i=25;i<50;i++) {
  hdtge->ProjectionX(Form("px%d",i),i,i+1);
  pj[i] = (TH1D *)gDirectory->FindObjectAny(Form("px%d",i));
  //gSystem->GetObject(Form("px%d",i),pj[i]);
  fprintf(fitFileOut,"%d %d ",2*i,2*(i+1));
  fitGaussP1(pj[i],1293,3,1282,1303,fitFileOut);
}

fflush(fitFileOut);
fclose(fitFileOut);

}
