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

TH2F *hscan2d[10];

void gamScanPlot(void) {

  hscan2d[0] = new TH2F(Form("hscan2d_%d",0),Form("scan2d_%d",0),6000,0,6000,6000,0,6000);

    /**///======================================================== Cals
  //Read in cal file to array, do draws w/ cals
  TString cal[300][10];
  ifstream inFile;
  inFile.open("scan_fits_cl38.dat");
  Int_t lineRead=0;
  Int_t runNumberRead;
  Int_t detIndexRead;
  Int_t tempInt[100];
  Double_t tempDouble[100];

    for (Int_t i=0;i<100;i++) {
      tempInt[i] = 0;
      tempDouble[i] = 0;
    }
  
  if( inFile.is_open() ) {
    while (1) {
      inFile >> tempInt[0] >> tempDouble[0] >> tempDouble[1]
	     >> tempDouble[2] >> tempDouble[3]
	     >> tempDouble[4] >> tempDouble[5]
	     >> tempDouble[6] >> tempDouble[7];

      if (tempDouble[0] > 0) {
	hscan2d[0]->SetBinContent((int)tempDouble[6],(int)tempDouble[7],tempDouble[0]);
      }
    
      lineRead++;
      if (!inFile.good()) break;
    }
    inFile.close();
    printf("... done reading file\n");
  }else{
    
    printf("... failed to read file\n");
    return;
  }
  

}
