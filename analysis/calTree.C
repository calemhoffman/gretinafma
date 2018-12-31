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
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TTreeReaderArray.h>

void calTree() {
  TFile * fNameIn = new TFile("/Users/calemhoffman/Research/anl/gretinafma/data/root_data/devel/run200.root");
  if (fNameIn == 0) printf("Error: file read in fail\n");
  TTree * tree = (TTree *) fNameIn->FindObjectAny("tree");
  
  Int_t runNumber;
  Int_t numHits;
  Float_t left[numHits];
  Float_t right[numHits];
  Float_t up[numHits];
  Float_t down[numHits];
  Float_t e1[numHits];
  Float_t e2[numHits];
  Float_t e3[numHits];
  Float_t gammaEnergy[numHits];
  Float_t deltaTime[numHits];
  
  tree->SetBranchAddress("runNumber",&runNumber);
  tree->SetBranchAddress("left",left);
  tree->SetBranchAddress("right",right);
  tree->SetBranchAddress("up",up);
  tree->SetBranchAddress("down",down);
  tree->SetBranchAddress("e1",e1);
  tree->SetBranchAddress("e2",e2);
  tree->SetBranchAddress("e3",e3);
  tree->SetBranchAddress("gammaEnergy",gammaEnergy);
  tree->SetBranchAddress("deltaTime",deltaTime);

  TTree * calTree = new TTree("calTree", "Cal Tree");

  calTree->Branch("runNumber", &runNumber, "runNumber/I");
  
  Int_t nEntries = tree->GetEntries();
  printf("nEntries: %d\n",nEntries);

  for (Int_t entryNumber=0;entryNumber<=nEntries; entryNumber++) {
    tree->GetEntry(entryNumber);

    

  } //entryNumber Loop
 
  printf("Run Number: %d\n",runNumber);
  printf("left: %f\n",left[0]);
  
};
