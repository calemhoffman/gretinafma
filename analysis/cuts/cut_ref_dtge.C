{
//========= Macro generated from object: cut_ref_dtge/cut_ref_dtge
//========= by ROOT version6.15/01
   
   cutg = new TCutG("cut_ref_dtge",15);
   cutg->SetVarX("genergy");
   cutg->SetVarY("dtime");
   cutg->SetTitle("cut_ref_dtge");
   cutg->SetFillStyle(1000);

    ci = TColor::GetColor("#0000ff");
   cutg->SetLineColor(ci);
   cutg->SetLineWidth(6);
   cutg->SetPoint(0,5991.44,91.1638);
   cutg->SetPoint(1,5471.45,94.5259);
   cutg->SetPoint(2,3061.17,94.7845);
   cutg->SetPoint(3,1219.82,93.4914);
   cutg->SetPoint(4,296.085,91.1638);
   cutg->SetPoint(5,14.6818,87.0259);
   cutg->SetPoint(6,14.6818,50.819);
   cutg->SetPoint(7,173.736,51.3362);
   cutg->SetPoint(8,338.907,58.8362);
   cutg->SetPoint(9,1189.23,60.9052);
   cutg->SetPoint(10,3091.76,62.1983);
   cutg->SetPoint(11,4407.01,61.9397);
   cutg->SetPoint(12,5520.39,61.1638);
   cutg->SetPoint(13,6009.79,64.0086);
   cutg->SetPoint(14,5991.44,91.1638);
   /* cutg->Draw(""); */
}
