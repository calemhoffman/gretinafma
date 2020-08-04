void gz(int lo, int hi) {

  c1->Clear();
  c1->Divide(1,5);

  c1->cd(1);
  ehiz1->GetXaxis()->SetRange(lo, hi);
  ehiz1->Draw();
  c1->cd(2);
  ehiz2->GetXaxis()->SetRange(lo, hi);
  ehiz2->Draw();
  c1->cd(3);
  ehiz3->GetXaxis()->SetRange(lo, hi);
  ehiz3->Draw();
  c1->cd(4);
  ehiz4->GetXaxis()->SetRange(lo, hi);
  ehiz4->Draw();
  c1->cd(5);
  ehiz5->GetXaxis()->SetRange(lo, hi);
  ehiz5->Draw();

} 
