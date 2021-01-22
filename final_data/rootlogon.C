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

  gROOT->ProcessLine(".x cuts/cut_e1e3_Ave.C"); cut_e1e3_Ave;
  gROOT->ProcessLine(".x cuts/cut_e1e2_s38.C"); cut_e1e2_s38;
  gROOT->ProcessLine(".x cuts/cut_e0x_s38.C"); cut_e0x_s38;
  //gROOT->ProcessLine(".x cuts/cut_dtge_Ave.C"); cut_dtge_Ave;
  gROOT->ProcessLine(".x cuts/cut_mx_good.C"); cut_mx_good;
  gROOT->ProcessLine(".x cuts/cut_lr_fig.C"); cut_lr_fig;

}
