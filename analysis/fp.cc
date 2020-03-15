void fp(int lo, int hi) {

  c1->Clear();
  c1->Divide(4,4);

  c1->cd(1);
  l->Draw();
  c1->cd(2);
  r->Draw();
  c1->cd(3);
  sumlr->Draw();
  c1->cd(4);
  x->Draw();

  c1->cd(5);
  up->Draw();
  c1->cd(6);
  down->Draw();
  c1->cd(7);
  sumud->Draw();
  c1->cd(8);
  y->Draw();


  c1->cd(9);
  de1->Draw();
  c1->cd(10);
  de2->Draw();
  c1->cd(11);
  de3->Draw();
  c1->cd(12);
  rftof->Draw();

  c1->cd(13);
  de12->Draw();
  c1->cd(14);
  etot->Draw();



} 
