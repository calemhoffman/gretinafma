{

  TCanvas *c_ic_energy = new TCanvas("c_ic_energy","c_in_energy",1000,1000);


  //histo
  TH2F *he1e3 = new TH2F("he1e3","ion chamber e1 vs e3; e3 [ch]; e1 [ch]",1000,0,5000,1000,0,5000);
  TH2F *he2e3 = new TH2F("he2e3","ion chamber e2 vs e3; e3 [ch]; e2 [ch]",1000,0,5000,1000,0,5000);

  
  c_ic_energy->Clear(); c_ic_energy->Divide(2,2);

  c_ic_energy->cd(1);
  tree->Draw("e1:e3>>he1e3","","col");
  c_ic_energy->cd(2);
  tree->Draw("e2:e3>>he2e3","","col");


}
