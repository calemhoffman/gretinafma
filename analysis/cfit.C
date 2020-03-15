void cfit()
{
//=========Macro generated from canvas: cfit/cfit
//=========  (Mon Feb 17 16:17:18 2020) by ROOT version 6.18/04
   TCanvas *cfit = new TCanvas("cfit", "cfit",0,45,1400,748);
   gStyle->SetOptFit(1);
   cfit->ToggleEventStatus();
   cfit->ToggleToolTips();
   cfit->Range(0,0,1,1);
   cfit->SetFillColor(0);
   cfit->SetBorderMode(0);
   cfit->SetBorderSize(2);
   cfit->SetTickx(1);
   cfit->SetTicky(1);
   cfit->SetFrameFillColor(10);
   cfit->SetFrameBorderMode(0);
  
// ------------>Primitives in pad: cfit_1
   TPad *cfit_1 = new TPad("cfit_1", "cfit_1",0.01,0.51,0.24,0.99);
   cfit_1->Draw();
   cfit_1->cd();
   cfit_1->Range(-1.185084,-0.25,0.5656063,2.25);
   cfit_1->SetFillColor(0);
   cfit_1->SetBorderMode(0);
   cfit_1->SetBorderSize(2);
   cfit_1->SetTickx(1);
   cfit_1->SetTicky(1);
   cfit_1->SetFrameFillColor(10);
   cfit_1->SetFrameBorderMode(0);
   cfit_1->SetFrameFillColor(10);
   cfit_1->SetFrameBorderMode(0);
   
   Double_t Graph0_fx1001[5] = {
   0.258819,
   -0.08715574,
   -0.4226183,
   -0.7071068,
   -0.9063078};
   Double_t Graph0_fy1001[5] = {
   1.09673,
   1.074411,
   1.105625,
   1.247304,
   1.47593};
   Double_t Graph0_fex1001[5] = {
   0.001,
   0.001,
   0.001,
   0.001,
   0.001};
   Double_t Graph0_fey1001[5] = {
   0.05363824,
   0.03062909,
   0.02605564,
   0.02939503,
   0.0421562};
   TGraphErrors *gre = new TGraphErrors(5,Graph0_fx1001,Graph0_fy1001,Graph0_fex1001,Graph0_fey1001);
   gre->SetName("Graph0");
   gre->SetTitle("1292 keV");
   gre->SetFillStyle(1000);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#00ff00");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(20);
   
   TH1F *Graph_Graph01001 = new TH1F("Graph_Graph01001","1292 keV",100,-1.02402,0.3765317);
   Graph_Graph01001->SetMinimum(0);
   Graph_Graph01001->SetMaximum(2);
   Graph_Graph01001->SetDirectory(0);
   Graph_Graph01001->SetStats(0);
   Graph_Graph01001->GetXaxis()->SetRange(2,101);
   Graph_Graph01001->GetXaxis()->SetTitleOffset(1);
   Graph_Graph01001->GetYaxis()->SetTitleOffset(1);
   Graph_Graph01001->GetZaxis()->SetTitleOffset(1);
   gre->SetHistogram(Graph_Graph01001);
   
   
   TF1 *l2fit1002 = new TF1("l2fit","[0]*(1 + [1]*ROOT::Math::legendre([2],x))",-1.010015,0.3905373, TF1::EAddToList::kNo);
   l2fit1002->SetFillColor(19);
   l2fit1002->SetFillStyle(0);
   l2fit1002->SetLineWidth(3);
   l2fit1002->SetChisquare(3.99129);
   l2fit1002->SetNDF(3);
   l2fit1002->GetXaxis()->SetTitleOffset(1);
   l2fit1002->GetYaxis()->SetTitleOffset(1);
   l2fit1002->SetParameter(0,1.198981);
   l2fit1002->SetParError(0,0.01492881);
   l2fit1002->SetParLimits(0,0,0);
   l2fit1002->SetParameter(1,0.2612474);
   l2fit1002->SetParError(1,0.03023284);
   l2fit1002->SetParLimits(1,-1,1);
   l2fit1002->SetParameter(2,2);
   l2fit1002->SetParError(2,0);
   l2fit1002->SetParLimits(2,2,2);
   l2fit1002->SetParent(gre);
   gre->GetListOfFunctions()->Add(l2fit1002);
   
   TPaveStats *ptstats = new TPaveStats(0.62,0.755,0.98,0.995,"brNDC");
   ptstats->SetName("stats");
   ptstats->SetBorderSize(1);
   ptstats->SetFillColor(0);
   ptstats->SetTextAlign(12);
   TText *ptstats_LaTex = ptstats->AddText("#chi^{2} / ndf = 3.991 / 3");
   ptstats_LaTex = ptstats->AddText("Prob  = 0.2624");
   ptstats_LaTex = ptstats->AddText("p0       = 1.199 #pm 0.01493 ");
   ptstats_LaTex = ptstats->AddText("p1       = 0.2612 #pm 0.03023 ");
   ptstats_LaTex = ptstats->AddText("p2       =     2 #pm     0 ");
   ptstats->SetOptStat(0);
   ptstats->SetOptFit(1111);
   ptstats->Draw();
   gre->GetListOfFunctions()->Add(ptstats);
   ptstats->SetParent(gre->GetListOfFunctions());
   gre->Draw("alp");
   
   TF1 *l2fit1003 = new TF1("l2fit","[0]*(1 + [1]*ROOT::Math::legendre([2],x))",-1,1, TF1::EAddToList::kDefault);
   l2fit1003->SetFillColor(19);
   l2fit1003->SetFillStyle(0);
   l2fit1003->SetLineWidth(3);
   l2fit1003->SetChisquare(3.99129);
   l2fit1003->SetNDF(3);
   l2fit1003->GetXaxis()->SetRange(1,100);
   l2fit1003->GetXaxis()->SetTitleOffset(1);
   l2fit1003->GetYaxis()->SetTitleOffset(1);
   l2fit1003->SetParameter(0,1.198981);
   l2fit1003->SetParError(0,0.01492881);
   l2fit1003->SetParLimits(0,0,0);
   l2fit1003->SetParameter(1,0.2612474);
   l2fit1003->SetParError(1,0.03023284);
   l2fit1003->SetParLimits(1,-1,1);
   l2fit1003->SetParameter(2,2);
   l2fit1003->SetParError(2,0);
   l2fit1003->SetParLimits(2,2,2);
   l2fit1003->Draw("same");
   
   TPaveText *pt = new TPaveText(0.01,0.925,0.47,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(1);
   pt->SetFillColor(33);
   TText *pt_LaTex = pt->AddText("1292 keV");
   pt->Draw();
   cfit_1->Modified();
   cfit->cd();
  
// ------------>Primitives in pad: cfit_2
   TPad *cfit_2 = new TPad("cfit_2", "cfit_2",0.26,0.51,0.49,0.99);
   cfit_2->Draw();
   cfit_2->cd();
   cfit_2->Range(-1.185084,-0.25,0.5656063,2.25);
   cfit_2->SetFillColor(0);
   cfit_2->SetBorderMode(0);
   cfit_2->SetBorderSize(2);
   cfit_2->SetTickx(1);
   cfit_2->SetTicky(1);
   cfit_2->SetFrameFillColor(10);
   cfit_2->SetFrameBorderMode(0);
   cfit_2->SetFrameFillColor(10);
   cfit_2->SetFrameBorderMode(0);
   
   Double_t Graph0_fx1004[5] = {
   0.258819,
   -0.08715574,
   -0.4226183,
   -0.7071068,
   -0.9063078};
   Double_t Graph0_fy1004[5] = {
   1.130542,
   1.097982,
   1.11753,
   1.158411,
   1.495535};
   Double_t Graph0_fex1004[5] = {
   0.001,
   0.001,
   0.001,
   0.001,
   0.001};
   Double_t Graph0_fey1004[5] = {
   0.06123803,
   0.03692054,
   0.03139539,
   0.03323934,
   0.0508999};
   gre = new TGraphErrors(5,Graph0_fx1004,Graph0_fy1004,Graph0_fex1004,Graph0_fey1004);
   gre->SetName("Graph0");
   gre->SetTitle("1535 keV");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#00cc00");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(21);
   
   TH1F *Graph_Graph01004 = new TH1F("Graph_Graph01004","1535 keV",100,-1.02402,0.3765317);
   Graph_Graph01004->SetMinimum(0);
   Graph_Graph01004->SetMaximum(2);
   Graph_Graph01004->SetDirectory(0);
   Graph_Graph01004->SetStats(0);
   Graph_Graph01004->GetXaxis()->SetRange(2,101);
   Graph_Graph01004->GetXaxis()->SetTitleOffset(1);
   Graph_Graph01004->GetYaxis()->SetTitleOffset(1);
   Graph_Graph01004->GetZaxis()->SetTitleOffset(1);
   gre->SetHistogram(Graph_Graph01004);
   
   
   TF1 *l2fit1005 = new TF1("l2fit","[0]*(1 + [1]*ROOT::Math::legendre([2],x))",-1.010015,0.3905373, TF1::EAddToList::kNo);
   l2fit1005->SetFillColor(19);
   l2fit1005->SetFillStyle(0);
   l2fit1005->SetLineWidth(3);
   l2fit1005->SetChisquare(14.99936);
   l2fit1005->SetNDF(3);
   l2fit1005->GetXaxis()->SetTitleOffset(1);
   l2fit1005->GetYaxis()->SetTitleOffset(1);
   l2fit1005->SetParameter(0,1.184114);
   l2fit1005->SetParError(0,0.01757682);
   l2fit1005->SetParLimits(0,0,0);
   l2fit1005->SetParameter(1,0.2119264);
   l2fit1005->SetParError(1,0.03654319);
   l2fit1005->SetParLimits(1,-1,1);
   l2fit1005->SetParameter(2,2);
   l2fit1005->SetParError(2,0);
   l2fit1005->SetParLimits(2,2,2);
   l2fit1005->SetParent(gre);
   gre->GetListOfFunctions()->Add(l2fit1005);
   
   ptstats = new TPaveStats(0.62,0.755,0.98,0.995,"brNDC");
   ptstats->SetName("stats");
   ptstats->SetBorderSize(1);
   ptstats->SetFillColor(0);
   ptstats->SetTextAlign(12);
   ptstats_LaTex = ptstats->AddText("#chi^{2} / ndf =    15 / 3");
   ptstats_LaTex = ptstats->AddText("Prob  = 0.001817");
   ptstats_LaTex = ptstats->AddText("p0       = 1.184 #pm 0.01758 ");
   ptstats_LaTex = ptstats->AddText("p1       = 0.2119 #pm 0.03654 ");
   ptstats_LaTex = ptstats->AddText("p2       =     2 #pm     0 ");
   ptstats->SetOptStat(0);
   ptstats->SetOptFit(1111);
   ptstats->Draw();
   gre->GetListOfFunctions()->Add(ptstats);
   ptstats->SetParent(gre->GetListOfFunctions());
   gre->Draw("alp");
   
   TF1 *l2fit1006 = new TF1("l2fit","[0]*(1 + [1]*ROOT::Math::legendre([2],x))",-1,1, TF1::EAddToList::kDefault);
   l2fit1006->SetFillColor(19);
   l2fit1006->SetFillStyle(0);
   l2fit1006->SetLineWidth(3);
   l2fit1006->SetChisquare(14.99936);
   l2fit1006->SetNDF(3);
   l2fit1006->GetXaxis()->SetRange(1,100);
   l2fit1006->GetXaxis()->SetTitleOffset(1);
   l2fit1006->GetYaxis()->SetTitleOffset(1);
   l2fit1006->SetParameter(0,1.184114);
   l2fit1006->SetParError(0,0.01757682);
   l2fit1006->SetParLimits(0,0,0);
   l2fit1006->SetParameter(1,0.2119264);
   l2fit1006->SetParError(1,0.03654319);
   l2fit1006->SetParLimits(1,-1,1);
   l2fit1006->SetParameter(2,2);
   l2fit1006->SetParError(2,0);
   l2fit1006->SetParLimits(2,2,2);
   l2fit1006->Draw("same");
   
   pt = new TPaveText(0.01,0.925,0.47,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(1);
   pt->SetFillColor(33);
   pt_LaTex = pt->AddText("1535 keV");
   pt->Draw();
   cfit_2->Modified();
   cfit->cd();
  
// ------------>Primitives in pad: cfit_3
   TPad *cfit_3 = new TPad("cfit_3", "cfit_3",0.51,0.51,0.74,0.99);
   cfit_3->Draw();
   cfit_3->cd();
   cfit_3->Range(-1.185084,-0.25,0.5656063,2.25);
   cfit_3->SetFillColor(0);
   cfit_3->SetBorderMode(0);
   cfit_3->SetBorderSize(2);
   cfit_3->SetTickx(1);
   cfit_3->SetTicky(1);
   cfit_3->SetFrameFillColor(10);
   cfit_3->SetFrameBorderMode(0);
   cfit_3->SetFrameFillColor(10);
   cfit_3->SetFrameBorderMode(0);
   
   Double_t Graph0_fx1007[5] = {
   0.258819,
   -0.08715574,
   -0.4226183,
   -0.7071068,
   -0.9063078};
   Double_t Graph0_fy1007[5] = {
   1.249269,
   1.049647,
   1.091031,
   1.20834,
   1.401712};
   Double_t Graph0_fex1007[5] = {
   0.001,
   0.001,
   0.001,
   0.001,
   0.001};
   Double_t Graph0_fey1007[5] = {
   0.0975149,
   0.046057,
   0.04713758,
   0.0437392,
   0.06213178};
   gre = new TGraphErrors(5,Graph0_fx1007,Graph0_fy1007,Graph0_fex1007,Graph0_fey1007);
   gre->SetName("Graph0");
   gre->SetTitle("850 keV");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#009900");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(22);
   
   TH1F *Graph_Graph01007 = new TH1F("Graph_Graph01007","850 keV",100,-1.02402,0.3765317);
   Graph_Graph01007->SetMinimum(0);
   Graph_Graph01007->SetMaximum(2);
   Graph_Graph01007->SetDirectory(0);
   Graph_Graph01007->SetStats(0);
   Graph_Graph01007->GetXaxis()->SetRange(2,101);
   Graph_Graph01007->GetXaxis()->SetTitleOffset(1);
   Graph_Graph01007->GetYaxis()->SetTitleOffset(1);
   Graph_Graph01007->GetZaxis()->SetTitleOffset(1);
   gre->SetHistogram(Graph_Graph01007);
   
   
   TF1 *l2fit1008 = new TF1("l2fit","[0]*(1 + [1]*ROOT::Math::legendre([2],x))",-1.010015,0.3905373, TF1::EAddToList::kNo);
   l2fit1008->SetFillColor(19);
   l2fit1008->SetFillStyle(0);
   l2fit1008->SetLineWidth(3);
   l2fit1008->SetChisquare(4.43383);
   l2fit1008->SetNDF(3);
   l2fit1008->GetXaxis()->SetTitleOffset(1);
   l2fit1008->GetYaxis()->SetTitleOffset(1);
   l2fit1008->SetParameter(0,1.175729);
   l2fit1008->SetParError(0,0.02358057);
   l2fit1008->SetParLimits(0,0,0);
   l2fit1008->SetParameter(1,0.2143221);
   l2fit1008->SetParError(1,0.04716348);
   l2fit1008->SetParLimits(1,-1,1);
   l2fit1008->SetParameter(2,2);
   l2fit1008->SetParError(2,0);
   l2fit1008->SetParLimits(2,2,2);
   l2fit1008->SetParent(gre);
   gre->GetListOfFunctions()->Add(l2fit1008);
   
   ptstats = new TPaveStats(0.62,0.755,0.98,0.995,"brNDC");
   ptstats->SetName("stats");
   ptstats->SetBorderSize(1);
   ptstats->SetFillColor(0);
   ptstats->SetTextAlign(12);
   ptstats_LaTex = ptstats->AddText("#chi^{2} / ndf = 4.434 / 3");
   ptstats_LaTex = ptstats->AddText("Prob  = 0.2183");
   ptstats_LaTex = ptstats->AddText("p0       = 1.176 #pm 0.02358 ");
   ptstats_LaTex = ptstats->AddText("p1       = 0.2143 #pm 0.04716 ");
   ptstats_LaTex = ptstats->AddText("p2       =     2 #pm     0 ");
   ptstats->SetOptStat(0);
   ptstats->SetOptFit(1111);
   ptstats->Draw();
   gre->GetListOfFunctions()->Add(ptstats);
   ptstats->SetParent(gre->GetListOfFunctions());
   gre->Draw("alp");
   
   TF1 *l2fit1009 = new TF1("l2fit","[0]*(1 + [1]*ROOT::Math::legendre([2],x))",-1,1, TF1::EAddToList::kDefault);
   l2fit1009->SetFillColor(19);
   l2fit1009->SetFillStyle(0);
   l2fit1009->SetLineWidth(3);
   l2fit1009->SetChisquare(4.43383);
   l2fit1009->SetNDF(3);
   l2fit1009->GetXaxis()->SetRange(1,100);
   l2fit1009->GetXaxis()->SetTitleOffset(1);
   l2fit1009->GetYaxis()->SetTitleOffset(1);
   l2fit1009->SetParameter(0,1.175729);
   l2fit1009->SetParError(0,0.02358057);
   l2fit1009->SetParLimits(0,0,0);
   l2fit1009->SetParameter(1,0.2143221);
   l2fit1009->SetParError(1,0.04716348);
   l2fit1009->SetParLimits(1,-1,1);
   l2fit1009->SetParameter(2,2);
   l2fit1009->SetParError(2,0);
   l2fit1009->SetParLimits(2,2,2);
   l2fit1009->Draw("same");
   
   pt = new TPaveText(0.01,0.925,0.47,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(1);
   pt->SetFillColor(33);
   pt_LaTex = pt->AddText("850 keV");
   pt->Draw();
   cfit_3->Modified();
   cfit->cd();
  
// ------------>Primitives in pad: cfit_4
   TPad *cfit_4 = new TPad("cfit_4", "cfit_4",0.76,0.51,0.99,0.99);
   cfit_4->Draw();
   cfit_4->cd();
   cfit_4->Range(-1.185084,-0.25,0.5656063,2.25);
   cfit_4->SetFillColor(0);
   cfit_4->SetBorderMode(0);
   cfit_4->SetBorderSize(2);
   cfit_4->SetTickx(1);
   cfit_4->SetTicky(1);
   cfit_4->SetFrameFillColor(10);
   cfit_4->SetFrameBorderMode(0);
   cfit_4->SetFrameFillColor(10);
   cfit_4->SetFrameBorderMode(0);
   
   Double_t Graph0_fx1010[5] = {
   0.258819,
   -0.08715574,
   -0.4226183,
   -0.7071068,
   -0.9063078};
   Double_t Graph0_fy1010[5] = {
   1.220398,
   0.9258922,
   0.9757832,
   1.4533,
   1.424627};
   Double_t Graph0_fex1010[5] = {
   0.001,
   0.001,
   0.001,
   0.001,
   0.001};
   Double_t Graph0_fey1010[5] = {
   0.1301684,
   0.06777551,
   0.05603751,
   0.1213637,
   0.1195006};
   gre = new TGraphErrors(5,Graph0_fx1010,Graph0_fy1010,Graph0_fex1010,Graph0_fey1010);
   gre->SetName("Graph0");
   gre->SetTitle("2668 keV");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#006600");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(23);
   
   TH1F *Graph_Graph01010 = new TH1F("Graph_Graph01010","2668 keV",100,-1.02402,0.3765317);
   Graph_Graph01010->SetMinimum(0);
   Graph_Graph01010->SetMaximum(2);
   Graph_Graph01010->SetDirectory(0);
   Graph_Graph01010->SetStats(0);
   Graph_Graph01010->GetXaxis()->SetRange(2,101);
   Graph_Graph01010->GetXaxis()->SetTitleOffset(1);
   Graph_Graph01010->GetYaxis()->SetTitleOffset(1);
   Graph_Graph01010->GetZaxis()->SetTitleOffset(1);
   gre->SetHistogram(Graph_Graph01010);
   
   
   TF1 *l2fit1011 = new TF1("l2fit","[0]*(1 + [1]*ROOT::Math::legendre([2],x))",-1.010015,0.3905373, TF1::EAddToList::kNo);
   l2fit1011->SetFillColor(19);
   l2fit1011->SetFillStyle(0);
   l2fit1011->SetLineWidth(3);
   l2fit1011->SetChisquare(7.928462);
   l2fit1011->SetNDF(3);
   l2fit1011->GetXaxis()->SetTitleOffset(1);
   l2fit1011->GetYaxis()->SetTitleOffset(1);
   l2fit1011->SetParameter(0,1.151536);
   l2fit1011->SetParError(0,0.04151643);
   l2fit1011->SetParLimits(0,0,0);
   l2fit1011->SetParameter(1,0.3932848);
   l2fit1011->SetParError(1,0.0833595);
   l2fit1011->SetParLimits(1,-1,1);
   l2fit1011->SetParameter(2,2);
   l2fit1011->SetParError(2,0);
   l2fit1011->SetParLimits(2,2,2);
   l2fit1011->SetParent(gre);
   gre->GetListOfFunctions()->Add(l2fit1011);
   
   ptstats = new TPaveStats(0.62,0.755,0.98,0.995,"brNDC");
   ptstats->SetName("stats");
   ptstats->SetBorderSize(1);
   ptstats->SetFillColor(0);
   ptstats->SetTextAlign(12);
   ptstats_LaTex = ptstats->AddText("#chi^{2} / ndf = 7.928 / 3");
   ptstats_LaTex = ptstats->AddText("Prob  = 0.04751");
   ptstats_LaTex = ptstats->AddText("p0       = 1.152 #pm 0.04152 ");
   ptstats_LaTex = ptstats->AddText("p1       = 0.3933 #pm 0.08336 ");
   ptstats_LaTex = ptstats->AddText("p2       =     2 #pm     0 ");
   ptstats->SetOptStat(0);
   ptstats->SetOptFit(1111);
   ptstats->Draw();
   gre->GetListOfFunctions()->Add(ptstats);
   ptstats->SetParent(gre->GetListOfFunctions());
   gre->Draw("alp");
   
   TF1 *l2fit1012 = new TF1("l2fit","[0]*(1 + [1]*ROOT::Math::legendre([2],x))",-1,1, TF1::EAddToList::kDefault);
   l2fit1012->SetFillColor(19);
   l2fit1012->SetFillStyle(0);
   l2fit1012->SetLineWidth(3);
   l2fit1012->SetChisquare(7.928462);
   l2fit1012->SetNDF(3);
   l2fit1012->GetXaxis()->SetRange(1,100);
   l2fit1012->GetXaxis()->SetTitleOffset(1);
   l2fit1012->GetYaxis()->SetTitleOffset(1);
   l2fit1012->SetParameter(0,1.151536);
   l2fit1012->SetParError(0,0.04151643);
   l2fit1012->SetParLimits(0,0,0);
   l2fit1012->SetParameter(1,0.3932848);
   l2fit1012->SetParError(1,0.0833595);
   l2fit1012->SetParLimits(1,-1,1);
   l2fit1012->SetParameter(2,2);
   l2fit1012->SetParError(2,0);
   l2fit1012->SetParLimits(2,2,2);
   l2fit1012->Draw("same");
   
   pt = new TPaveText(0.01,0.925,0.47,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(1);
   pt->SetFillColor(33);
   pt_LaTex = pt->AddText("2668 keV");
   pt->Draw();
   cfit_4->Modified();
   cfit->cd();
  
// ------------>Primitives in pad: cfit_5
   TPad *cfit_5 = new TPad("cfit_5", "cfit_5",0.01,0.01,0.24,0.49);
   cfit_5->Draw();
   cfit_5->cd();
   cfit_5->Range(-1.185084,-0.25,0.5656063,2.25);
   cfit_5->SetFillColor(0);
   cfit_5->SetBorderMode(0);
   cfit_5->SetBorderSize(2);
   cfit_5->SetTickx(1);
   cfit_5->SetTicky(1);
   cfit_5->SetFrameFillColor(10);
   cfit_5->SetFrameBorderMode(0);
   cfit_5->SetFrameFillColor(10);
   cfit_5->SetFrameBorderMode(0);
   
   Double_t Graph0_fx1013[5] = {
   0.258819,
   -0.08715574,
   -0.4226183,
   -0.7071068,
   -0.9063078};
   Double_t Graph0_fy1013[5] = {
   1.575852,
   1.515659,
   1.075886,
   0.9650577,
   0.867545};
   Double_t Graph0_fex1013[5] = {
   0.001,
   0.001,
   0.001,
   0.001,
   0.001};
   Double_t Graph0_fey1013[5] = {
   0.2471838,
   0.1707134,
   0.1021831,
   0.09690907,
   0.1183374};
   gre = new TGraphErrors(5,Graph0_fx1013,Graph0_fy1013,Graph0_fex1013,Graph0_fey1013);
   gre->SetName("Graph0");
   gre->SetTitle("2322 keV");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#0000ff");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(20);
   
   TH1F *Graph_Graph01013 = new TH1F("Graph_Graph01013","2322 keV",100,-1.02402,0.3765317);
   Graph_Graph01013->SetMinimum(0);
   Graph_Graph01013->SetMaximum(2);
   Graph_Graph01013->SetDirectory(0);
   Graph_Graph01013->SetStats(0);
   Graph_Graph01013->GetXaxis()->SetRange(2,101);
   Graph_Graph01013->GetXaxis()->SetTitleOffset(1);
   Graph_Graph01013->GetYaxis()->SetTitleOffset(1);
   Graph_Graph01013->GetZaxis()->SetTitleOffset(1);
   gre->SetHistogram(Graph_Graph01013);
   
   
   TF1 *l2fit1014 = new TF1("l2fit","[0]*(1 + [1]*ROOT::Math::legendre([2],x))",-1.010015,0.3905373, TF1::EAddToList::kNo);
   l2fit1014->SetFillColor(19);
   l2fit1014->SetFillStyle(0);
   l2fit1014->SetLineWidth(3);
   l2fit1014->SetChisquare(4.962126);
   l2fit1014->SetNDF(3);
   l2fit1014->GetXaxis()->SetTitleOffset(1);
   l2fit1014->GetYaxis()->SetTitleOffset(1);
   l2fit1014->SetParameter(0,1.108595);
   l2fit1014->SetParError(0,0.05716232);
   l2fit1014->SetParLimits(0,0,0);
   l2fit1014->SetParameter(1,-0.3788637);
   l2fit1014->SetParError(1,0.1156311);
   l2fit1014->SetParLimits(1,-1,1);
   l2fit1014->SetParameter(2,2);
   l2fit1014->SetParError(2,0);
   l2fit1014->SetParLimits(2,2,2);
   l2fit1014->SetParent(gre);
   gre->GetListOfFunctions()->Add(l2fit1014);
   
   ptstats = new TPaveStats(0.62,0.755,0.98,0.995,"brNDC");
   ptstats->SetName("stats");
   ptstats->SetBorderSize(1);
   ptstats->SetFillColor(0);
   ptstats->SetTextAlign(12);
   ptstats_LaTex = ptstats->AddText("#chi^{2} / ndf = 4.962 / 3");
   ptstats_LaTex = ptstats->AddText("Prob  = 0.1746");
   ptstats_LaTex = ptstats->AddText("p0       = 1.109 #pm 0.05716 ");
   ptstats_LaTex = ptstats->AddText("p1       = -0.3789 #pm 0.1156 ");
   ptstats_LaTex = ptstats->AddText("p2       =     2 #pm     0 ");
   ptstats->SetOptStat(0);
   ptstats->SetOptFit(1111);
   ptstats->Draw();
   gre->GetListOfFunctions()->Add(ptstats);
   ptstats->SetParent(gre->GetListOfFunctions());
   gre->Draw("alp");
   
   TF1 *l2fit1015 = new TF1("l2fit","[0]*(1 + [1]*ROOT::Math::legendre([2],x))",-1,1, TF1::EAddToList::kDefault);
   l2fit1015->SetFillColor(19);
   l2fit1015->SetFillStyle(0);
   l2fit1015->SetLineWidth(3);
   l2fit1015->SetChisquare(4.962126);
   l2fit1015->SetNDF(3);
   l2fit1015->GetXaxis()->SetRange(1,100);
   l2fit1015->GetXaxis()->SetTitleOffset(1);
   l2fit1015->GetYaxis()->SetTitleOffset(1);
   l2fit1015->SetParameter(0,1.108595);
   l2fit1015->SetParError(0,0.05716232);
   l2fit1015->SetParLimits(0,0,0);
   l2fit1015->SetParameter(1,-0.3788637);
   l2fit1015->SetParError(1,0.1156311);
   l2fit1015->SetParLimits(1,-1,1);
   l2fit1015->SetParameter(2,2);
   l2fit1015->SetParError(2,0);
   l2fit1015->SetParLimits(2,2,2);
   l2fit1015->Draw("same");
   
   pt = new TPaveText(0.01,0.925,0.47,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(1);
   pt->SetFillColor(33);
   pt_LaTex = pt->AddText("2322 keV");
   pt->Draw();
   cfit_5->Modified();
   cfit->cd();
  
// ------------>Primitives in pad: cfit_6
   TPad *cfit_6 = new TPad("cfit_6", "cfit_6",0.26,0.01,0.49,0.49);
   cfit_6->Draw();
   cfit_6->cd();
   cfit_6->Range(-1.185084,-0.25,0.5656063,2.25);
   cfit_6->SetFillColor(0);
   cfit_6->SetBorderMode(0);
   cfit_6->SetBorderSize(2);
   cfit_6->SetTickx(1);
   cfit_6->SetTicky(1);
   cfit_6->SetFrameFillColor(10);
   cfit_6->SetFrameBorderMode(0);
   cfit_6->SetFrameFillColor(10);
   cfit_6->SetFrameBorderMode(0);
   
   Double_t Graph0_fx1016[5] = {
   0.258819,
   -0.08715574,
   -0.4226183,
   -0.7071068,
   -0.9063078};
   Double_t Graph0_fy1016[5] = {
   1.514586,
   0.985448,
   1.128227,
   1.028472,
   1.343268};
   Double_t Graph0_fex1016[5] = {
   0.001,
   0.001,
   0.001,
   0.001,
   0.001};
   Double_t Graph0_fey1016[5] = {
   0.2081627,
   0.09939249,
   0.08656504,
   0.09758058,
   0.1363929};
   gre = new TGraphErrors(5,Graph0_fx1016,Graph0_fy1016,Graph0_fex1016,Graph0_fey1016);
   gre->SetName("Graph0");
   gre->SetTitle("1576 keV");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#0000cc");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(21);
   
   TH1F *Graph_Graph01016 = new TH1F("Graph_Graph01016","1576 keV",100,-1.02402,0.3765317);
   Graph_Graph01016->SetMinimum(0);
   Graph_Graph01016->SetMaximum(2);
   Graph_Graph01016->SetDirectory(0);
   Graph_Graph01016->SetStats(0);
   Graph_Graph01016->GetXaxis()->SetRange(2,101);
   Graph_Graph01016->GetXaxis()->SetTitleOffset(1);
   Graph_Graph01016->GetYaxis()->SetTitleOffset(1);
   Graph_Graph01016->GetZaxis()->SetTitleOffset(1);
   gre->SetHistogram(Graph_Graph01016);
   
   
   TF1 *l2fit1017 = new TF1("l2fit","[0]*(1 + [1]*ROOT::Math::legendre([2],x))",-1.010015,0.3905373, TF1::EAddToList::kNo);
   l2fit1017->SetFillColor(19);
   l2fit1017->SetFillStyle(0);
   l2fit1017->SetLineWidth(3);
   l2fit1017->SetChisquare(7.795598);
   l2fit1017->SetNDF(3);
   l2fit1017->GetXaxis()->SetTitleOffset(1);
   l2fit1017->GetYaxis()->SetTitleOffset(1);
   l2fit1017->SetParameter(0,1.125118);
   l2fit1017->SetParError(0,0.04948789);
   l2fit1017->SetParLimits(0,0,0);
   l2fit1017->SetParameter(1,0.1170538);
   l2fit1017->SetParError(1,0.1061764);
   l2fit1017->SetParLimits(1,-1,1);
   l2fit1017->SetParameter(2,2);
   l2fit1017->SetParError(2,0);
   l2fit1017->SetParLimits(2,2,2);
   l2fit1017->SetParent(gre);
   gre->GetListOfFunctions()->Add(l2fit1017);
   
   ptstats = new TPaveStats(0.62,0.755,0.98,0.995,"brNDC");
   ptstats->SetName("stats");
   ptstats->SetBorderSize(1);
   ptstats->SetFillColor(0);
   ptstats->SetTextAlign(12);
   ptstats_LaTex = ptstats->AddText("#chi^{2} / ndf = 7.796 / 3");
   ptstats_LaTex = ptstats->AddText("Prob  = 0.05043");
   ptstats_LaTex = ptstats->AddText("p0       = 1.125 #pm 0.04949 ");
   ptstats_LaTex = ptstats->AddText("p1       = 0.1171 #pm 0.1062 ");
   ptstats_LaTex = ptstats->AddText("p2       =     2 #pm     0 ");
   ptstats->SetOptStat(0);
   ptstats->SetOptFit(1111);
   ptstats->Draw();
   gre->GetListOfFunctions()->Add(ptstats);
   ptstats->SetParent(gre->GetListOfFunctions());
   gre->Draw("alp");
   
   TF1 *l2fit1018 = new TF1("l2fit","[0]*(1 + [1]*ROOT::Math::legendre([2],x))",-1,1, TF1::EAddToList::kDefault);
   l2fit1018->SetFillColor(19);
   l2fit1018->SetFillStyle(0);
   l2fit1018->SetLineWidth(3);
   l2fit1018->SetChisquare(7.795598);
   l2fit1018->SetNDF(3);
   l2fit1018->GetXaxis()->SetRange(1,100);
   l2fit1018->GetXaxis()->SetTitleOffset(1);
   l2fit1018->GetYaxis()->SetTitleOffset(1);
   l2fit1018->SetParameter(0,1.125118);
   l2fit1018->SetParError(0,0.04948789);
   l2fit1018->SetParLimits(0,0,0);
   l2fit1018->SetParameter(1,0.1170538);
   l2fit1018->SetParError(1,0.1061764);
   l2fit1018->SetParLimits(1,-1,1);
   l2fit1018->SetParameter(2,2);
   l2fit1018->SetParError(2,0);
   l2fit1018->SetParLimits(2,2,2);
   l2fit1018->Draw("same");
   
   pt = new TPaveText(0.01,0.925,0.47,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(1);
   pt->SetFillColor(33);
   pt_LaTex = pt->AddText("1576 keV");
   pt->Draw();
   cfit_6->Modified();
   cfit->cd();
  
// ------------>Primitives in pad: cfit_7
   TPad *cfit_7 = new TPad("cfit_7", "cfit_7",0.51,0.01,0.74,0.49);
   cfit_7->Draw();
   cfit_7->cd();
   cfit_7->Range(0,0,1,1);
   cfit_7->SetFillColor(0);
   cfit_7->SetBorderMode(0);
   cfit_7->SetBorderSize(2);
   cfit_7->SetTickx(1);
   cfit_7->SetTicky(1);
   cfit_7->SetFrameFillColor(10);
   cfit_7->SetFrameBorderMode(0);
   cfit_7->Modified();
   cfit->cd();
  
// ------------>Primitives in pad: cfit_8
   TPad *cfit_8 = new TPad("cfit_8", "cfit_8",0.76,0.01,0.99,0.49);
   cfit_8->Draw();
   cfit_8->cd();
   cfit_8->Range(0,0,1,1);
   cfit_8->SetFillColor(0);
   cfit_8->SetBorderMode(0);
   cfit_8->SetBorderSize(2);
   cfit_8->SetTickx(1);
   cfit_8->SetTicky(1);
   cfit_8->SetFrameFillColor(10);
   cfit_8->SetFrameBorderMode(0);
   cfit_8->Modified();
   cfit->cd();
   cfit->Modified();
   cfit->cd();
   cfit->SetSelected(cfit);
   cfit->ToggleToolBar();
}
