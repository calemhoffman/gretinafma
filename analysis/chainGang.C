#include <TChain.h>
#include <TString.h>
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
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TTreeReaderArray.h>
#include <TFile.h>
#include <TEventList.h>

#define LCRC 0

TChain *chain;
TString fileName;
Int_t goodRun[30] = {0,0,0,0,0,
		     0,0,1,1,1,
		     1,1,1,1,1,
		     1,1,1,0,1,
		     1,1,1,1,1,
		     1,1,1,1,1};

void chainGang(void) {
chain = new TChain("ctree");

for (Int_t rn = 7; rn<30; rn++) {
  if (goodRun[rn]==1) {
		if (LCRC==1) {
    	fileName.Form("/lcrc/project/HELIOS/gretinafma/root_data/cal_%d.root",rn);
    	chain->Add(fileName);
		} else {
			fileName.Form("../../data/root_data/cal_%d.root",rn);
	    chain->Add(fileName);
		}
  }
 }

}
