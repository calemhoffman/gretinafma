{
//========= Macro generated from object: cut_ref_e1e2/cut_ref_e1e2
//========= by ROOT version6.15/01
   
   TCutG *cutg = new TCutG("cut_ref_e1e2",19);
   cutg->SetVarX("e[1]");
   cutg->SetVarY("e[0]");
   cutg->SetTitle("cut_ref_e1e2");
   cutg->SetFillStyle(1000);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#0000ff");
   cutg->SetLineColor(ci);
   cutg->SetLineWidth(6);
   cutg->SetPoint(0,1116.81,2077.64);
   cutg->SetPoint(1,1023.85,2077.64);
   cutg->SetPoint(2,934.923,1992.24);
   cutg->SetPoint(3,769.2,1813.66);
   cutg->SetPoint(4,619.644,1635.09);
   cutg->SetPoint(5,522.635,1510.87);
   cutg->SetPoint(6,437.753,1386.65);
   cutg->SetPoint(7,360.954,1246.89);
   cutg->SetPoint(8,316.491,1177.02);
   cutg->SetPoint(9,308.407,1045.03);
   cutg->SetPoint(10,320.534,1006.21);
   cutg->SetPoint(11,409.458,1091.61);
   cutg->SetPoint(12,542.846,1246.89);
   cutg->SetPoint(13,728.779,1472.05);
   cutg->SetPoint(14,850.04,1611.8);
   cutg->SetPoint(15,938.965,1712.73);
   cutg->SetPoint(16,1048.1,1836.96);
   cutg->SetPoint(17,1137.03,1992.24);
   cutg->SetPoint(18,1116.81,2077.64);
   /* cutg->Draw(""); */
}
