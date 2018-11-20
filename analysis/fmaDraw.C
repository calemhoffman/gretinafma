#include <TROOT.h>
#include <TSystem.h>
#include <TStyle.h>
#include <TTree.h>
#include <TFile.h>
#include <TSelector.h>
#include <TMath.h>
#include <TBenchmark.h>
#include <TH2F.h>
#include <TH1F.h>
#include <TF1.h>
#include <TCanvas.h>
#include <TGraph2D.h>
#include <TGraph.h>
#include <TCutG.h>
#include <TRandom.h>
#include <string>
#include <fstream>
#include <math.h>
#include <TRandom.h>
#include <TDatime.h>
#include <TObjArray.h>

void fmaDraw(TTree *tree) {

  printf("==========================================================\n");
  printf("================ draw all fma spectra  ===================\n");
  printf("==========================================================\n");
  TBenchmark gClock;  
  gClock.Reset(); gClock.Start("gTimer");

  int totnumEntry = tree->GetEntries();
  printf("============== Total TTree Entries: %10lld \n", tree->GetEntries());

  gClock.Stop("gTimer");
  double gTime =  gClock.GetRealTime("gTimer");
  printf("=========== Finsihed, total runTime : %7.0f sec \n", gTime);
  
}
