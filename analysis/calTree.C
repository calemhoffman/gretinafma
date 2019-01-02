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
  TFile * fNameIn = new TFile("/Users/calemhoffman/Research/anl/gretinafma/data/root_data/devel/run220.root");
  if (fNameIn == 0) printf("Error: file read in fail\n");
  TTree * tree = (TTree *) fNameIn->FindObjectAny("tree");
  
  Int_t runNumber;
  Int_t numHits=1;
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
  tree->SetBranchAddress("numHits",&numHits);
  tree->SetBranchAddress("left",left);
  tree->SetBranchAddress("right",right);
  tree->SetBranchAddress("up",up);
  tree->SetBranchAddress("down",down);
  /* tree->SetBranchAddress("e1",e1); */
  /* tree->SetBranchAddress("e2",e2); */
  /* tree->SetBranchAddress("e3",e3); */
  /* tree->SetBranchAddress("gammaEnergy",gammaEnergy); */
  /* tree->SetBranchAddress("deltaTime",deltaTime); */

  TFile * calFile = new TFile("cal.root","RECREATE");
  TTree * ctree = new TTree("ctree", "Cal Tree");

  Int_t run;
  Int_t hits;
  Float_t l,r,u,d,x,y;

  ctree->Branch("run", &run, "run/I");
  ctree->Branch("hits",&hits,"hits/I");
  ctree->Branch("l",&l,"l/F");
  ctree->Branch("r",&r,"r/F");
  ctree->Branch("u",&u,"u/F");
  ctree->Branch("d",&d,"d/F");
  ctree->Branch("x",&x,"x/F");
  ctree->Branch("y",&y,"y/F");
  
  /* Tree->Branch("right",right); */
  /* tree->Branch("up",up); */
  /* tree->Branch("down",down); */
  /* tree->Branch("e1",e1); */
  /* tree->Branch("e2",e2); */
  /* tree->Branch("e3",e3); */
  /* tree->Branch("gammaEnergy",gammaEnergy); */
  /* tree->Branch("deltaTime",deltaTime); */
  
  Int_t nEntries = tree->GetEntries();
  printf("nEntries: %d\n",nEntries);

  for (Int_t entryNumber=0;entryNumber<=nEntries; entryNumber++) {
    tree->GetEntry(entryNumber);
   
    run=runNumber;
    hits=numHits;
    if (left[0]>=-500) {
      l = left[0];
    } else {
      l = left[0]+6560.0;
    }

    if (right[0]>=-500) {
      r = right[0];
    } else {
      r = right[0]+6560.0;
    }

    if (up[0]>=-500) {
      u = up[0];
    } else {
      u = up[0]+6560.0;
    }

    if (down[0]>=-500) {
    d = down[0];
    } else {
      d = down[0]+6560.0;
    }
    
    x = (l-r);
    y = (u-d);


     if (entryNumber<10)
      printf("entryNumber:%d l:%4.0f r:%4.0f u:%4.0f d:%4.0f x:%4.0f y:%4.0f\n",
	     entryNumber,l,r,u,d,x,y);

     
    ctree->Fill();

  } //entryNumber Loop
  ctree->Write();
  //printf("Run Number: %d\n",runNumber);
  /* printf("left: %f\n",left[0]); */

}
