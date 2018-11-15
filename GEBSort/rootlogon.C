{
printf("rootlogon.C\n");

//gROOT->ProcessLine(".L GSUtil.cc++");
//printf("GSUtil_cc.so compiled\n");

//gROOT->ProcessLine(".x bar.cc");
//printf(".x bar.cc executed\n");

 TCanvas *c1 = new TCanvas("c1","c1");


gROOT->ProcessLine(".L fp.cc");
gROOT->ProcessLine(".L fp2.cc");
gROOT->ProcessLine(".L gz.cc");

gStyle->SetPalette(53);

}
