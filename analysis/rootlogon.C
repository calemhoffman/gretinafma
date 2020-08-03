{
  printf("rootlogon.C\n");
  gROOT->ProcessLine(".L GSUtil_new_cc.so");
  printf("GSUtil_new_cc.so loaded\n");
  gROOT->ProcessLine(".L AutoFit.C");


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
  gStyle->SetPalette(1,0);
  gStyle->SetNumberContours(50);                     // pretty and useful palette
  gStyle->SetHistLineWidth(2);                    // a thicker histogram line
  gStyle->SetFrameFillColor(10);                  // a different frame colour
  gStyle->SetTitleFillColor(33);                 // title colour to highlight it
  gStyle->SetTitleW(.46);                         // Title Width
  gStyle->SetTitleH(.07);                        // Title height
  gStyle->SetHistMinimumZero(true);               // Suppresses Histogram Zero Supression

  /* gROOT->ProcessLine(".x gcut1.C"); gcut1; */
  /* gROOT->ProcessLine(".x gcut2.C"); gcut2; */
  /* gROOT->ProcessLine(".x gcut3.C"); gcut3; */
  /* gROOT->ProcessLine(".x gcut4.C"); gcut4; */
  /* gROOT->ProcessLine(".x cuts/cut_ref_e1e2.C"); cut_ref_e1e2; */
  /* gROOT->ProcessLine(".x cuts/cut_ref_e1e3.C"); cut_ref_e1e3; */
  /* gROOT->ProcessLine(".x cuts/cut_ref_e1e13.C"); cut_ref_e1e13; */
  /* gROOT->ProcessLine(".x cuts/cut_ref_e1x.C"); cut_ref_e1x; */
  /* gROOT->ProcessLine(".x cuts/cut_ref_lr.C"); cut_ref_lr; */
  /* gROOT->ProcessLine(".x cuts/cut_ref_dtge.C"); cut_ref_dtge; */
  /* gROOT->ProcessLine(".x hist_ref_e1.C");hist_ref_e1__1; */
  /* gROOT->ProcessLine(".x hist_ref_e2.C");hist_ref_e2__2; */
  /* gROOT->ProcessLine(".x hist_ref_e3.C");hist_ref_e3__3; */
  /* gROOT->ProcessLine(".x cuts/cut_ref2_e1e2.C"); cut_ref2_e1e2; */
  /* gROOT->ProcessLine(".x cuts/cut_ref2_e1x.C"); cut_ref2_e1x; */
  /* gROOT->ProcessLine(".x cuts/cut_ref2_lr.C"); cut_ref2_lr; */
  /* gROOT->ProcessLine(".x cuts/cut_ar38_dtge.C"); cut_ar38_dtge; */
  /* gROOT->ProcessLine(".x cuts/cut_ar38_e1e3.C"); cut_ar38_e1e3; */
  /* gROOT->ProcessLine(".x cuts/cut_ar38_e12e3.C"); cut_ar38_e12e3; */
  /* gROOT->ProcessLine(".x cuts/cut_ar38_e1e2.C"); cut_ar38_e1e2; */
  /* gROOT->ProcessLine(".x cuts/cut_ar38_e2e3.C"); cut_ar38_e2e3; */
  /* gROOT->ProcessLine(".x cuts/cut_ar38_e12e123.C"); cut_ar38_e12e123; */
  /* gROOT->ProcessLine(".x cuts/cut_ar38_e1x.C"); cut_ar38_e1x; */
  gROOT->ProcessLine(".x cuts/cut_ar38_g600.C"); cut_ar38_g600;
  gROOT->ProcessLine(".x cuts/cut_ar38_g1600.C"); cut_ar38_g1600;
  gROOT->ProcessLine(".x cuts/cut_ar38_g1800.C"); cut_ar38_g1800;
  gROOT->ProcessLine(".x cuts/cut_ar38_g2100.C"); cut_ar38_g2100;
  /* gROOT->ProcessLine(".x cuts/cut_cl38_dtge.C"); cut_cl38_dtge; */
  /* gROOT->ProcessLine(".x cuts/cut_cl38_e1e3.C"); cut_cl38_e1e3; */
  /* gROOT->ProcessLine(".x cuts/cut_cl38_e1e2.C"); cut_cl38_e1e2; */
  /* gROOT->ProcessLine(".x cuts/cut_cl38_e2e3.C"); cut_cl38_e2e3; */
  /* gROOT->ProcessLine(".x cuts/cut_cl38_e1x.C"); cut_cl38_e1x; */
  gROOT->ProcessLine(".x cuts/cut_cl38_g200.C"); cut_cl38_g200;
  gROOT->ProcessLine(".x cuts/cut_cl38_g700.C"); cut_cl38_g700;
  gROOT->ProcessLine(".x cuts/cut_cl38_g1100.C"); cut_cl38_g1100;
  gROOT->ProcessLine(".x cuts/cut_cl38_g2600.C"); cut_cl38_g2600;
  gROOT->ProcessLine(".x cuts/cut_cl38_g3100.C"); cut_cl38_g3100;

  /* gROOT->ProcessLine(".x cuts/cut_s38_dtge.C"); cut_s38_dtge; */
  /* gROOT->ProcessLine(".x cuts/cut_s38_e1e3.C"); cut_s38_e1e3; */
  /* gROOT->ProcessLine(".x cuts/cut_s38_e1e2.C"); cut_s38_e1e2;  */
  /* gROOT->ProcessLine(".x cuts/cut_s38_e2e3.C"); cut_s38_e2e3; */
  /* gROOT->ProcessLine(".x cuts/cut_s38_e1x.C"); cut_s38_e1x; */
  gROOT->ProcessLine(".x cuts/cut_e1e3_ar38.C"); cut_e1e3_ar38;
  gROOT->ProcessLine(".x cuts/cut_e0x_ar38.C"); cut_e0x_ar38;
  gROOT->ProcessLine(".x cuts/cut_lr_ar38.C"); cut_lr_ar38;
  gROOT->ProcessLine(".x cuts/cut_ud_ar38.C"); cut_ud_ar38;
  gROOT->ProcessLine(".x cuts/cut_dtge_ar38.C"); cut_dtge_ar38;

  gROOT->ProcessLine(".x cuts/cut_e1e3_cl38.C"); cut_e1e3_cl38;
  gROOT->ProcessLine(".x cuts/cut_e0x_cl38.C"); cut_e0x_cl38;
  gROOT->ProcessLine(".x cuts/cut_lr_cl38.C"); cut_lr_cl38;
  gROOT->ProcessLine(".x cuts/cut_ud_cl38.C"); cut_ud_cl38;
  gROOT->ProcessLine(".x cuts/cut_dtge_cl38.C"); cut_dtge_cl38;

  gROOT->ProcessLine(".x cuts/cut_e1e3_s38.C"); cut_e1e3_s38;
  gROOT->ProcessLine(".x cuts/cut_e0x_s38.C"); cut_e0x_s38;
  gROOT->ProcessLine(".x cuts/cut_lr_s38.C"); cut_lr_s38;
  gROOT->ProcessLine(".x cuts/cut_ud_s38.C"); cut_ud_s38;
  gROOT->ProcessLine(".x cuts/cut_dtge_s38.C"); cut_dtge_s38;
  gROOT->ProcessLine(".x cuts/cut_dtge_feb10.C"); cut_dtge_feb10;
  gROOT->ProcessLine(".x cuts/cut_dtge_Ave.C"); cut_dtge_Ave;
  gROOT->ProcessLine(".x cuts/cut_dtge_Skin1.C"); cut_dtge_Skin1;
  gROOT->ProcessLine(".x cuts/cut_dtge_Skin2.C"); cut_dtge_Skin2;
  gROOT->ProcessLine(".x cuts/cut_e2e3_s38.C"); cut_e2e3_s38;
  gROOT->ProcessLine(".x cuts/cut_e1e2_s38.C"); cut_e1e2_s38;
  gROOT->ProcessLine(".x cuts/cut_e1e2_ml.C"); cut_e1e2_ml;
  gROOT->ProcessLine(".x cuts/cut_e2e3_ml.C"); cut_e2e3_ml;
  gROOT->ProcessLine(".x cuts/cut_e1e3_scan0.C"); cut_e1e3_scan0;
  gROOT->ProcessLine(".x cuts/cut_e1e3_scan1.C"); cut_e1e3_scan1;
  gROOT->ProcessLine(".x cuts/cut_e1e3_scan2.C"); cut_e1e3_scan2;
  gROOT->ProcessLine(".x cuts/cut_e1e3_scan3.C"); cut_e1e3_scan3;
  gROOT->ProcessLine(".x cuts/cut_e1e3_scan4.C"); cut_e1e3_scan4;
  gROOT->ProcessLine(".x cuts/cut_e1e3_scan15.C"); cut_e1e3_scan15;
  gROOT->ProcessLine(".x cuts/cut_e1e3_scan25.C"); cut_e1e3_scan25;
  gROOT->ProcessLine(".x cuts/cut_e1e3_jan0.C"); cut_e1e3_jan0;
  gROOT->ProcessLine(".x cuts/cut_e1e3_ml.C"); cut_e1e3_ml;
  gROOT->ProcessLine(".x cuts/cut_e1e3_NEW.C"); cut_e1e3_NEW;
  // gROOT->ProcessLine(".x cuts/cut_e2e3_NEW.C"); cut_e2e3_NEW;
  gROOT->ProcessLine(".x cuts/cut_e1e3_Ave.C"); cut_e1e3_Ave;
  gROOT->ProcessLine(".x cuts/cut_e1e3_Skin.C"); cut_e1e3_Skin;
  gROOT->ProcessLine(".x cuts/cut_e1e3_Skinniest.C"); cut_e1e3_Skinniest;
  gROOT->ProcessLine(".x cuts/cut_e1e3_Skinnier.C"); cut_e1e3_Skinnier;
  gROOT->ProcessLine(".x cuts/cut_mx_test.C"); cut_mx_test;
  gROOT->ProcessLine(".x cuts/cut_mg_good.C"); cut_mg_good;
  gROOT->ProcessLine(".x cuts/cut_mx_good.C"); cut_mx_good;
  gROOT->ProcessLine(".x cuts/cut_mx_tight.C"); cut_mx_tight;


  gROOT->ProcessLine(".x cuts/cut_p33_g1400.C"); cut_p33_g1400;
  gROOT->ProcessLine(".x cuts/cut_p33_g1800.C"); cut_p33_g1800;
  gROOT->ProcessLine(".x cuts/cut_p33_g2300.C"); cut_p33_g2300;

  //gROOT->ProcessLine(".x cuts/cut_e1e3_no33p.C"); cut_e1e3_no33p;
  gROOT->ProcessLine(".x cuts/cut_e1e3_p33.C"); cut_e1e3_p33;
  gROOT->ProcessLine(".x cuts/cut_e0x_p33.C"); cut_e0x_p33;
  gROOT->ProcessLine(".x cuts/cut_lr_p33.C"); cut_lr_p33;
  gROOT->ProcessLine(".x cuts/cut_ud_p33.C"); cut_ud_p33;
  gROOT->ProcessLine(".x cuts/cut_dtge_p33.C"); cut_dtge_p33;

  gROOT->ProcessLine(".x cuts/cut_s38_g800.C"); cut_s38_g800;
  gROOT->ProcessLine(".x cuts/cut_s38_g1200.C"); cut_s38_g1200;
  gROOT->ProcessLine(".x cuts/cut_s38_g1500.C"); cut_s38_g1500;

  gROOT->ProcessLine(".x cuts/all_aq_e0x.C"); all_aq_e0x;
  gROOT->ProcessLine(".x cuts/all_z_e1e3.C"); all_z_e1e3;
  gROOT->ProcessLine(".x cuts/all_tof_dtge.C"); all_tof_dtge;
  gROOT->ProcessLine(".x cuts/cut_all_aq.C"); cut_all_aq;
  gROOT->ProcessLine(".x cuts/cut_all_z.C"); cut_all_z;

  //  TBrowser *b = new TBrowser()

}
