{
//========= Macro generated from object: cut_mg_good/cut_mg_good
//========= by ROOT version6.18/04

   cutg = new TCutG("cut_mg_good",9);
   cutg->SetVarX("(e[0]+e[2])*dtime*dtime/1.0e4");
   cutg->SetVarY("gAddBack");
   cutg->SetTitle("cut_mg_good");
   cutg->SetFillStyle(1000);
   cutg->SetPoint(0,1901.86,119.089);
   cutg->SetPoint(1,2066.91,214.533);
   cutg->SetPoint(2,2170.54,919.352);
   cutg->SetPoint(3,2170.54,4024.96);
   cutg->SetPoint(4,1433.59,4017.62);
   cutg->SetPoint(5,1237.84,515.55);
   cutg->SetPoint(6,1122.69,258.584);
   cutg->SetPoint(7,1136.12,119.089);
   cutg->SetPoint(8,1901.86,119.089);
}
