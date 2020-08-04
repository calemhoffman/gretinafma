void fp2(int lo, int hi) {

  c1->Clear();
  c1->Divide(2,3);

  c1->cd(1);
  lr->Draw("colz");
  c1->cd(2);
  ud->Draw("colz");
  c1->cd(3);
  ede1->Draw("colz");
  c1->cd(4);
  ede2->Draw("colz");
  c1->cd(5);
  ede12->Draw("colz");
  c1->cd(6);
  erftof->Draw("colz");

} 
