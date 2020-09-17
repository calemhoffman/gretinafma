{
  TCanvas *cc = new TCanvas("cc","cc",1200,700);
  //TFile f("pyTorchOutNewW.root");
//  TFile f("pyTorchOutNewV.root");
  TFile f("pyTorchOutAverageFatQb.root");
//TFile f("pyTorchOutAverageFatF.root");
//TFile f("pyTorchOutAverageSkinK.root");
//TFile f("pyTorchOutAverageFatF_base.root");
TH2F *hgg[5];
TH1F *hg[5];
TH1D *hg_px[5];
TH1D *hg_py[5];
//
TH1D *hc[100];//coincidence 1-ds
TH1D *hs[100];//summed spectra
Float_t gates[100][3] =  //e, low, high
{{1293,1286,1299},//0 x
{1535,1529,1540},//1 x
{850,845,854},//2 x
{2668,2658,2680},//3 x
{384,380,387},//4 x
{438,435,442},//5 x
{559,554,563},//6 x
{760,756,762},//7 - may have cl contam x
{780,776,783},//8 x
{810,804,814},//9 not sure about this One x
{822,819,824},//10 weak x
{830,826,834},//11 x
{887,883,890},//12 x
{1020,1014,1023},//13 doubled w/ 1013?cl38 1020 too x
{1067,1063,1072},//14 not sure about this one x
{1457,1452,1459},//15 x
{1512,1507,1516},//16 x
{1577,1572,1582},//17 x
{1609,1605,1614},//18 x
{1617,1614,1621},//19 x
{1625,1621,1630},//20 x
{1675,1664,1677},//21 centroid seems off for hg3
{1950,1944,1959},//22
{2057,2050,2061},//23
{2323,2312,2330},//24
{2365,2358,2371},//25
{2385,2378,2392},//26
{2804,2792,2806},//27
{720,718,722},//28 doubtful
{2015,2105,2125},
{2224,2220,2230}
}; //end gates
Int_t coin = 31;//number of hc's
Int_t sums = 1; //number of summed spectra
Int_t hggID =0;//which hgg F/K/Q? 0.25,0.3,0.6,0.81,0.875
//V? 0.35,0.38,0.4,0.5,0.8
//W 0.8,0.85,0.89,0.895,0.9
Int_t mlval=38;

for (Int_t i=0;i<5;i++) {
  //get hists
  hg_px[i] = new TH1D(Form("hg_px%d",i),Form("hg_px%d",i),4000,0,4000);
  hg_py[i] = new TH1D(Form("hg_py%d",i),Form("hg_py%d",i),4000,0,4000);
  hgg[i] = (TH2F *)gDirectory->FindObjectAny(Form("hgg%d",i));
  hg[i] = (TH1F *)gDirectory->FindObjectAny(Form("hg%d",i));
  hgg[i]->ProjectionX(Form("hg_px%d",i));
  hgg[i]->ProjectionY(Form("hg_py%d",i));
  hg_px[i]->GetXaxis()->SetRangeUser(10,4000);
  hg_py[i]->GetXaxis()->SetRangeUser(10,4000);

  for (Int_t j=0;j<coin;j++) {
    if (i==hggID){
      hc[j] = new TH1D(Form("hc%.0f",gates[j][0]),Form("hc%.0f hgg%d",gates[j][0],i),4000,0,4000);

      hgg[i]->ProjectionX(Form("hc%.0f",gates[j][0]),gates[j][1]+0.0,gates[j][2]-0.0);
      //
      hc[j]->SetLineColor(40+j);hc[j]->SetFillColor(40+j);
      hc[j]->SetFillStyle(1001);hc[j]->SetFillColorAlpha(40+j,0.2);
      hc[j]->GetXaxis()->SetRangeUser(10,4000);
      //write_ascii(Form("hc%.0f",gates[j][0]));
      //gROOT->ProcessLine(Form(".! mv hc%.0f.ascii ascii/hc%.0f_ml%d_1keV.ascii",gates[j][0],gates[j][0],mlval));
      //
    }
  }

  hg[i]->SetLineColor(40+i); hg_py[i]->SetLineColor(40+i);
  hg_px[i]->SetLineColor(40+i);
  hg[i]->SetFillColor(40+i); hg_py[i]->SetFillColor(40+i);
  hg_px[i]->SetFillColor(40+i);
  hg[i]->SetFillStyle(1001); hg_py[i]->SetFillStyle(1001);
  hg_px[i]->SetFillStyle(1001);
  hg[i]->SetFillColorAlpha(40+i,0.3); hg_py[i]->SetFillColorAlpha(40+i,0.3);
  hg_px[i]->SetFillColorAlpha(40+i,0.3);

  // for (Int_t j=0;j<coin;j++) {
  //   if (i==hggID) {
  //   write_ascii(Form("hc%.0f",gates[j][0]));
  //   gROOT->ProcessLine(Form(".! mv hc%.0f.ascii ascii/hc%.0f_ml%d_1keV.ascii",gates[j][0],gates[j][0],mlval));
  //   hc[j]->Rebin();
  //   write_ascii(Form("hc%.0f",gates[j][0]));
  //   gROOT->ProcessLine(Form(".! mv hc%.0f.ascii ascii/hc%.0f_ml%d_2keV.ascii",gates[j][0],gates[j][0],mlval));
  //   hc[j]->Rebin();
  //   write_ascii(Form("hc%.0f",gates[j][0]));
  //   gROOT->ProcessLine(Form(".! mv hc%.0f.ascii ascii/hc%.0f_ml%d_4keV.ascii",gates[j][0],gates[j][0],mlval));
  //   }
  // }
}

//fitting
// printf("--------Fitting of the full singles-------\n");
// for (Int_t i=0;i<5;i++) fitGaussP0(hg[i],1293,3,10,1250,1350);
// printf("--------Fitting of the px-------\n");
// for (Int_t i=0;i<5;i++) fitGaussP0(hg_px[i],1293,3,10,1250,1350);
//printf("--------Fitting of the 1293 proj-------\n");
//for (Int_t i=0;i<5;i++) fitGaussP0(hg1293[i],1535,3,1,1500,1560);
// printf("--------Fitting of the py-------\n");
// for (Int_t i=0;i<5;i++) fitGaussP0(hg_py[i],1293,3,10,1250,1350);

cc->Clear(); //cc->Divide(1,4);
//hc[0]->Draw("hist");
//Sum spectra
hs[0] = new TH1D("hs0","Sum of All",4000,0,4000);
for (Int_t i=0;i<coin;i++) {hs[0]->Add(hc[i]);}
hs[0]->GetXaxis()->SetRangeUser(10,4000);
hs[0]->Draw();

hs[1] = new TH1D("hs1","Sum of 1293,1535",4000,0,4000);
for (Int_t i=0;i<2;i++) {hs[1]->Add(hc[i]);}
// write_ascii(Form("hs1"));
// gROOT->ProcessLine(Form(".! mv hs1.ascii ascii/hs1_ml%d_1keV.ascii",mlval));
// hs[1]->Rebin();
// write_ascii(Form("hs1"));
// gROOT->ProcessLine(Form(".! mv hs1.ascii ascii/hs1_ml%d_2keV.ascii",mlval));
// hs[1]->Rebin();
// write_ascii(Form("hs1"));
// gROOT->ProcessLine(Form(".! mv hs1.ascii ascii/hs1_ml%d_4keV.ascii",mlval));
//
hs[2] = new TH1D("hs2","Sum of 1293,850,1535",4000,0,4000);
for (Int_t i=0;i<3;i++) {hs[2]->Add(hc[i]);}
// write_ascii(Form("hs2"));
// gROOT->ProcessLine(Form(".! mv hs2.ascii ascii/hs2_ml%d_1keV.ascii",mlval));
// hs[2]->Rebin();
// write_ascii(Form("hs2"));
// gROOT->ProcessLine(Form(".! mv hs2.ascii ascii/hs2_ml%d_2keV.ascii",mlval));
// hs[2]->Rebin();
// write_ascii(Form("hs2"));
// gROOT->ProcessLine(Form(".! mv hs2.ascii ascii/hs2_ml%d_4keV.ascii",mlval));

hs[3] = new TH1D("hs3","Sum of 1293,850,1535,2668",4000,0,4000);
for (Int_t i=0;i<4;i++) {hs[3]->Add(hc[i]);}
// write_ascii(Form("hs3"));
// gROOT->ProcessLine(Form(".! mv hs3.ascii ascii/hs3_ml%d_1keV.ascii",mlval));
// hs[3]->Rebin();
// write_ascii(Form("hs3"));
// gROOT->ProcessLine(Form(".! mv hs3.ascii ascii/hs3_ml%d_2keV.ascii",mlval));
// hs[3]->Rebin();
// write_ascii(Form("hs3"));
// gROOT->ProcessLine(Form(".! mv hs3.ascii ascii/hs3_ml%d_4keV.ascii",mlval));

hs[4] = new TH1D("hs4","Sum of 1293,850,1535,2668,1617,2385",4000,0,4000);
for (Int_t i=0;i<4;i++) {hs[4]->Add(hc[i]);}
hs[4]->Add(hc[19]); hs[4]->Add(hc[26]);
// write_ascii(Form("hs4"));
// gROOT->ProcessLine(Form(".! mv hs4.ascii ascii/hs4_ml%d_1keV.ascii",mlval));
// hs[4]->Rebin();
// write_ascii(Form("hs4"));
// gROOT->ProcessLine(Form(".! mv hs4.ascii ascii/hs4_ml%d_2keV.ascii",mlval));
// hs[4]->Rebin();
// write_ascii(Form("hs4"));
// gROOT->ProcessLine(Form(".! mv hs4.ascii ascii/hs4_ml%d_4keV.ascii",mlval));

//look at 850+2668 for 1617 2385
hs[5] = new TH1D("hs5","Sum of 850,2668",4000,0,4000);
hs[5]->Add(hc[2]); hs[5]->Add(hc[3]);
// write_ascii(Form("hs5"));
// gROOT->ProcessLine(Form(".! mv hs5.ascii ascii/hs5_ml%d_1keV.ascii",mlval));
// hs[5]->Rebin();
// write_ascii(Form("hs5"));
// gROOT->ProcessLine(Form(".! mv hs5.ascii ascii/hs5_ml%d_2keV.ascii",mlval));
// hs[5]->Rebin();
// write_ascii(Form("hs5"));
// gROOT->ProcessLine(Form(".! mv hs5.ascii ascii/hs5_ml%d_4keV.ascii",mlval));

//look at 1577,1950,1019,559,1625 for 4437 level (1067 possible too)
hs[6] = new TH1D("hs6","Sum 1577,1950",4000,0,4000);
hs[6]->Add(hc[17]); hs[6]->Add(hc[22]);
hs[8] = new TH1D("hs8","1019,559,1625",4000,0,4000);
hs[8]->Add(hc[13]);
hs[8]->Add(hc[6]); hs[8]->Add(hc[20]);
hs[10] = new TH1D("hs10","Sum 1577,1950,1019,559,1625",4000,0,4000);
hs[10]->Add(hc[17]); hs[10]->Add(hc[22]); hs[10]->Add(hc[13]);
hs[10]->Add(hc[6]); hs[10]->Add(hc[20]);
//780,1609,760,438out of 4437 level
hs[7] = new TH1D("hs7","Sum 1609,780,760,438",4000,0,4000);
hs[7]->Add(hc[18]); hs[6]->Add(hc[8]); hs[6]->Add(hc[7]);
hs[7]->Add(hc[5]);

//draws
for (Int_t i=0;i<coin;i++) {
  //cc->cd(i+1);
  //hc[i]->Rebin(2);
  //hc[i]->Draw("hist same");
}

for (Int_t i=0;i<coin;i++) hc[i]->Rebin(2);

}
