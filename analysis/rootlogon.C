{
  printf("rootlogon.C\n");
  // gROOT->ProcessLine(".L GSUtil_new_cc.so");
  //printf("GSUtil_new_cc.so loaded\n");

 
  // Set ROOT defaults
  gStyle->SetLineWidth(2);
  gStyle->SetCanvasBorderMode(0);
  gStyle->SetPadBorderMode(0);
  gStyle->SetPadColor(0);
  gStyle->SetFrameBorderMode(0);
  gStyle->SetFrameLineWidth(2);
  gStyle->SetCanvasColor(0);
  gStyle->SetOptDate(4);
  gStyle->GetAttDate()->SetTextFont(62);
  gStyle->GetAttDate()->SetTextSize(0.02);
  gStyle->GetAttDate()->SetTextAngle(0);
  gStyle->GetAttDate()->SetTextAlign(11);
  gStyle->GetAttDate()->SetTextColor(1);
  gStyle->SetDateX(0);
  gStyle->SetDateY(0);

  gROOT->SetStyle("Plain");                       // plain histogram style
  gStyle->SetOptStat("nemruoi");                  // expanded stats box
  gStyle->SetPadTickX(1);                         // tic marks on all axes
  gStyle->SetPadTickY(1);                         //
  gStyle->SetOptFit(1111);                        // the results of the fits
  //gStyle->SetPadGridX(kTRUE);                     // draw horizontal and vertical grids
  //gStyle->SetPadGridY(kTRUE);
  gStyle->SetPalette(53,0);
  gStyle->SetNumberContours(99);                     // pretty and useful palette
  gStyle->SetHistLineWidth(1);                    // a thicker histogram line
  gStyle->SetFrameFillColor(10);                  // a different frame colour   
  gStyle->SetTitleFillColor(33);                 // title colour to highlight it
  gStyle->SetTitleW(.46);                         // Title Width
  gStyle->SetTitleH(.07);                        // Title height
  gStyle->SetHistMinimumZero(true);               // Suppresses Histogram Zero Supression

  gROOT->ProcessLine(".x gcut1.C"); gcut1;
  gROOT->ProcessLine(".x gcut2.C"); gcut2;
  gROOT->ProcessLine(".x gcut3.C"); gcut3;
  gROOT->ProcessLine(".x gcut4.C"); gcut4;
  gROOT->ProcessLine(".x cuts/cut_ref_e1e2.C"); cut_ref_e1e2;
  gROOT->ProcessLine(".x cuts/cut_ref_e1e3.C"); cut_ref_e1e3;
  gROOT->ProcessLine(".x cuts/cut_ref_e1e13.C"); cut_ref_e1e13;
  gROOT->ProcessLine(".x cuts/cut_ref_e1x.C"); cut_ref_e1x;
  gROOT->ProcessLine(".x cuts/cut_ref_lr.C"); cut_ref_lr;
  gROOT->ProcessLine(".x cuts/cut_ref_dtge.C"); cut_ref_dtge;
  gROOT->ProcessLine(".x hist_ref_e1.C");hist_ref_e1__1;
  gROOT->ProcessLine(".x hist_ref_e2.C");hist_ref_e2__2;
  gROOT->ProcessLine(".x hist_ref_e3.C");hist_ref_e3__3;
  gROOT->ProcessLine(".x cuts/cut_ref2_e1e2.C"); cut_ref2_e1e2;
  gROOT->ProcessLine(".x cuts/cut_ref2_e1x.C"); cut_ref2_e1x;
  gROOT->ProcessLine(".x cuts/cut_ref2_lr.C"); cut_ref2_lr;
  gROOT->ProcessLine(".x cuts/cut_ar38_dtge.C"); cut_ar38_dtge;
  gROOT->ProcessLine(".x cuts/cut_ar38_e1e3.C"); cut_ar38_e1e3;
  gROOT->ProcessLine(".x cuts/cut_ar38_e12e3.C"); cut_ar38_e12e3;
  gROOT->ProcessLine(".x cuts/cut_ar38_e1e2.C"); cut_ar38_e1e2;
  gROOT->ProcessLine(".x cuts/cut_ar38_e2e3.C"); cut_ar38_e2e3;
  gROOT->ProcessLine(".x cuts/cut_ar38_e12e123.C"); cut_ar38_e12e123;
  gROOT->ProcessLine(".x cuts/cut_ar38_e1x.C"); cut_ar38_e1x;
  gROOT->ProcessLine(".x cuts/cut_ar38_g600.C"); cut_ar38_g600;
  gROOT->ProcessLine(".x cuts/cut_ar38_g1600.C"); cut_ar38_g1600;
  gROOT->ProcessLine(".x cuts/cut_ar38_g1800.C"); cut_ar38_g1800;
  gROOT->ProcessLine(".x cuts/cut_ar38_g2100.C"); cut_ar38_g2100;
  
  //  TBrowser *b = new TBrowser()

}
