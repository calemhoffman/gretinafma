// Manipulation
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

#define numRecoilProcess 1 //1-s38, 2-s38+cl38, etc.

TFile *gamFileIn;
TString fileName;

TTree * gtree[10];
Int_t recoilID[10];
Int_t run;
Int_t hits;
Float_t l,r,u,d,x,y;
Float_t e[10];
Int_t gmult;
Float_t genergy[100];
Float_t dtime[100];
Int_t gebMult;
Int_t crysId[100];
Int_t crysNum[100];
Float_t crysTot_e[100];
Float_t crysT0[100];
Float_t crysPolAngle[100];
Float_t intMaxX[100];
Float_t intMaxY[100];
Float_t intMaxZ[100];
Float_t intMaxE[100];
Int_t intMaxSeg[100];
Float_t intMaxSegE[100];

Int_t nEntries[10];

//Histograms
TString rName[5] = {"s38","cl38","ar38","p33","all"};
TH1F *hg[5];
TH2F *hgg[5];

void gamDraw(void) {
  //Initialize items
  Int_t ch=6000;
  Int_t rg=ch;
  for (Int_t recNum = 0; recNum<numRecoilProcess; recNum++) {
    hg[recNum] = new TH1F(Form("hg%d",recNum),
			  Form("%s hg%d; Gamma Energy [keV]",rName[recNum].Data(),recNum),
			  ch,0,rg);

    hgg[recNum] = new TH2F(Form("hgg%d",recNum),
			  Form("%s hgg%d; Gamma Energy [keV; Gamma Energy [keV]",rName[recNum].Data(),recNum),
			   ch/2,0,rg,ch/2,0,rg);
  }
  
  //Pull the TTrees of interest
  fileName.Form("/Users/calemhoffman/Research/anl/gretinafma/gretinafma_git/analysis/gamFile.root");
  gamFileIn = new TFile(fileName);
  gDirectory->ls();

  Int_t maxEntries=0;
  for (Int_t nt = 0; nt<numRecoilProcess; nt++) {
    gtree[nt] = (TTree *) gDirectory->FindObjectAny(Form("gtree%d",nt));
    nEntries[nt] = gtree[nt]->GetEntries();
    if (nEntries[nt]>maxEntries) maxEntries=nEntries[nt];
    printf("Entries for TTree %d: %d\n",nt,nEntries[nt]);
    printf("Max is: %d\n",maxEntries);
    //Set Branch Addresses (all for now)
    gtree[nt]->SetBranchAddress("recoilID",recoilID);
    //Generic
    gtree[nt]->SetBranchAddress("run", &run);
    gtree[nt]->SetBranchAddress("hits",&hits);
    //Positions
    gtree[nt]->SetBranchAddress("l",&l);
    gtree[nt]->SetBranchAddress("r",&r);
    gtree[nt]->SetBranchAddress("u",&u);
    gtree[nt]->SetBranchAddress("d",&d);
    gtree[nt]->SetBranchAddress("x",&x);
    gtree[nt]->SetBranchAddress("y",&y);
    //Energies
    gtree[nt]->SetBranchAddress("e",e);
    //Gammas - a bunch more to add...
    gtree[nt]->SetBranchAddress("gmult",&gmult);
    gtree[nt]->SetBranchAddress("genergy",genergy);
    gtree[nt]->SetBranchAddress("dtime",dtime);
    //Gamma breakdown
    gtree[nt]->SetBranchAddress("gebMult",&gebMult);
    gtree[nt]->SetBranchAddress("crysId",crysId);
    gtree[nt]->SetBranchAddress("crysNum",crysNum);
    gtree[nt]->SetBranchAddress("crysTot_e",crysTot_e);
    gtree[nt]->SetBranchAddress("crysT0",crysT0);
    gtree[nt]->SetBranchAddress("crysPolAngle",crysPolAngle);
    gtree[nt]->SetBranchAddress("intMaxX",intMaxX);
    gtree[nt]->SetBranchAddress("intMaxY",intMaxY);
    gtree[nt]->SetBranchAddress("intMaxZ",intMaxZ);
    gtree[nt]->SetBranchAddress("intMaxE",intMaxE);
    gtree[nt]->SetBranchAddress("intMaxSeg",intMaxSeg);
    gtree[nt]->SetBranchAddress("intMaxSegE",intMaxSegE);
  }

  //Apply Any EventLists
  //Loop - process and fill
  for (Int_t entryNumber=0;entryNumber<maxEntries; entryNumber++) {
    for (Int_t nTree=0; nTree<numRecoilProcess; nTree++) {
      if (entryNumber<nEntries[nTree]) {
	gtree[nTree]->GetEntry(entryNumber);
	for (Int_t gMult=0;gMult< gmult; gMult++) { /* need to apply dtge */
	  hg[nTree]->Fill(genergy[gMult]); //g fill
	  for (Int_t iMult=gMult+1; iMult<gmult; iMult++) {
	    hgg[nTree]->Fill(genergy[gMult],genergy[iMult]);
	    hgg[nTree]->Fill(genergy[iMult],genergy[gMult]);
	  }//gg fill
	}
      }//nEntries[] if
    }//nTree loop
  }//entry loop

  //Analyze histograms
  
  //Save and Draw

  //Cleanup
  

}
