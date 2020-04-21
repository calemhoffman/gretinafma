{
TCanvas *cc = new TCanvas("cc","cc",1200,600);
TFile ff("pyTorchOutAverageFatF.root");
TTree *tf = pytree;
TH1F *hf_5k = new TH1F("hf_5k","hf_5k",4000,0,4000);
TH1F *hf_4k = new TH1F("hf_4k","hf_4k",4000,0,4000);
TH1F *hf_3k = new TH1F("hf_3k","hf_3k",4000,0,4000);
tf->Draw("py_ge>>hf_5k","py_mlreturn>0.7","");
tf->Draw("py_ge>>hf_4k","py_mlreturn>0.81","");
tf->Draw("py_ge>>hf_3k","py_mlreturn>0.875","");
hf_5k->SetLineColor(kBlack); hf_5k->SetLineWidth(2);
hf_4k->SetLineColor(kBlack); hf_4k->SetLineWidth(3);
hf_3k->SetLineColor(kBlack); hf_3k->SetLineWidth(3);
fitGaussP0(hf_5k,1293,3,10,1250,1350);
fitGaussP0(hf_5k,1190,3,10,1150,1225);
fitGaussP0(hf_5k,3142,6,5,3100,3200);
fitGaussP0(hf_5k,383,2,10,365,395);
printf("Integral hf_5k: %.0f\n",hf_5k->Integral());

TFile fa("gamAlpha.root");
TH1F *ha = hgAddBack0;
fitGaussP0(ha,1293,3,10,1250,1350);
fitGaussP0(ha,1190,3,10,1150,1225);
fitGaussP0(ha,3142,6,5,3100,3200);
fitGaussP0(ha,383,2,10,365,395);
ha->SetLineColor(kRed+2); ha->SetLineWidth(2);

ha->SetStats(0); hf_5k->SetStats(0);
ha->SetTitle(""); hf_5k->SetTitle("");
ha->GetXaxis()->SetRangeUser(1000,2000);
hf_5k->SetFillColor(kGray+2); hf_5k->SetFillStyle(3013);
ha->SetXTitle("gamma-ray energy [keV]");
ha->SetYTitle("counts / keV");
ha->Draw("hist"); hf_5k->Draw("same hist");

//should use TPaveText -> AddText();
TPaveText *label_key_a = new TPaveText(1600,700,1950,800);
label_key_a->AddText("manually gated");
label_key_a->SetTextColor(kRed+2); label_key_a->SetTextSize(0.05);
label_key_a->SetFillStyle(0); label_key_a->SetShadowColor(0);
label_key_a->SetLineColor(0);
TPaveLabel *label_key_f = new TPaveLabel(1600,600,1950,700,"model output [k>0.7]");
label_key_f->SetTextColor(kBlack); label_key_f->SetTextSize(0.5);
label_key_f->SetFillStyle(0); label_key_f->SetShadowColor(0);
label_key_f->SetBorderSize(0);
label_key_f->SetLineColor(0);
TPaveLabel *label_key_1293 = new TPaveLabel(1300,700,1500,800,"1293-keV line known in ^{38}S");
label_key_1293->SetTextColor(kBlack); label_key_1293->SetTextSize(0.3);
label_key_1293->SetFillStyle(0); label_key_1293->SetShadowColor(0);
label_key_1293->SetLineColor(0);label_key_1293->SetBorderSize(0);

TPaveLabel *label_key_1535 = new TPaveLabel(1540,300,1740,400,"1535-keV line known in ^{38}S");
label_key_1535->SetTextColor(kBlack); label_key_1535->SetTextSize(0.3);
label_key_1535->SetFillStyle(0); label_key_1535->SetShadowColor(0);
label_key_1535->SetLineColor(0);label_key_1535->SetBorderSize(0);

TPaveLabel *label_key_1848 = new TPaveLabel(1750,125,1950,225,"^{33}P");
label_key_1848->SetTextColor(kRed+2); label_key_1848->SetTextSize(0.3);
label_key_1848->SetFillStyle(0); label_key_1848->SetShadowColor(0);
label_key_1848->SetLineColor(0); label_key_1848->SetLineWidth(0);
label_key_1848->SetLineStyle(0);label_key_1848->SetBorderSize(0);


TPaveLabel *label_key_1190 = new TPaveLabel(1090,75,1290,175,"^{38}Cl");
label_key_1190->SetTextColor(kRed+2); label_key_1190->SetTextSize(0.3);
label_key_1190->SetFillStyle(0); label_key_1190->SetShadowColor(0);
label_key_1190->SetLineColor(0);label_key_1190->SetBorderSize(0);


label_key_a->Draw(); label_key_f->Draw(); label_key_1293->Draw();label_key_1190->Draw();
label_key_1535->Draw();label_key_1848->Draw();
///////////////////////////////-/-----/-/----/-/-'/---------------------'
TFile fb("gamBeta.root");
TH1F *hb = hgAddBack0;

fitGaussP0(hb,1293,3,10,1250,1350);
fitGaussP0(hb,1190,3,10,1150,1225);
fitGaussP0(hb,3142,6,5,3100,3200);
fitGaussP0(hb,383,2,10,365,395);
fitGaussP0(hf_4k,1293,3,10,1250,1350);
fitGaussP0(hf_4k,1190,3,10,1150,1225);
fitGaussP0(hf_4k,3142,6,5,3100,3200);
fitGaussP0(hf_4k,383,2,10,365,395);

hb->SetLineColor(kBlue+2); hb->SetLineWidth(2);
hb->SetStats(0); hf_4k->SetStats(0);
hb->SetTitle(""); hf_4k->SetTitle("");
hb->GetXaxis()->SetRangeUser(1000,2000);
hf_4k->GetXaxis()->SetRangeUser(1000,2000);
//hf_4k->SetFillColor(kGray+2); hf_4k->SetFillStyle(3013);
hb->SetFillColor(kBlue+2); hb->SetFillStyle(3001);
hb->SetXTitle("gamma-ray energy [keV]");
hb->SetYTitle("counts / keV");
hf_4k->SetXTitle("gamma-ray energy [keV]");
hf_4k->SetYTitle("counts / keV");
hf_4k->Draw("hist"); hb->Draw("same hist");

//label_key_f->SetText("model output [k>0.81]")
label_key_f = new TPaveLabel(1700,550,1950,650,"model output [k>0.81]");
label_key_f->SetTextColor(kBlack); label_key_f->SetTextSize(0.5);
label_key_f->SetFillStyle(0); label_key_f->SetShadowColor(0);
label_key_f->SetBorderSize(0);
label_key_f->SetLineColor(0);
label_key_a->SetY1(550); label_key_a->SetY2(650); label_key_a->SetTextColor(kBlue+2);
label_key_1293->SetY1(575);label_key_1293->SetX1(1300); label_key_1293->SetY2(675);
label_key_1535->SetY1(250);label_key_1535->SetX1(1600); label_key_1535->SetY2(350);
label_key_1190->SetY1(50); label_key_1190->SetY2(150);label_key_1190->SetTextColor(kBlue+2);
label_key_1848->SetY1(50); label_key_1848->SetY2(150);label_key_1848->SetTextColor(kBlue+2);
label_key_a->Draw(); label_key_f->Draw(); label_key_1293->Draw();label_key_1190->Draw();
label_key_1535->Draw();label_key_1848->Draw();

}
