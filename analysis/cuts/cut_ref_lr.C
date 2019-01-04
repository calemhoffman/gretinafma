{
//========= Macro generated from object: cut_ref_lr/cut_ref_lr
//========= by ROOT version6.15/01
   
   cutg = new TCutG("cut_ref_lr",11);
   cutg->SetVarX("r");
   cutg->SetVarY("l");
   cutg->SetTitle("cut_ref_lr");
   cutg->SetFillStyle(1000);

   ci = TColor::GetColor("#0000ff");
   cutg->SetLineColor(ci);
   cutg->SetLineWidth(6);
   cutg->SetPoint(0,2814.47,2201.86);
   cutg->SetPoint(1,2555.78,2458.07);
   cutg->SetPoint(2,2280.92,2737.58);
   cutg->SetPoint(3,2018.19,2993.79);
   cutg->SetPoint(4,1941.39,2846.27);
   cutg->SetPoint(5,2022.23,2706.52);
   cutg->SetPoint(6,2232.42,2481.37);
   cutg->SetPoint(7,2559.82,2170.81);
   cutg->SetPoint(8,2713.42,2031.06);
   cutg->SetPoint(9,2725.55,2000);
   cutg->SetPoint(10,2814.47,2201.86);
   /* cutg->Draw(""); */
}
