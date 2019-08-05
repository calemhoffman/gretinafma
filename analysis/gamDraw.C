// Manipulation
#include <TROOT.h>
#include <TSystem.h>
#include <TStyle.h>
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

#include "AutoFit.C"

#define numRecoilProcess 1 //1-s38, 2-s38+cl38, etc.
#define RUNLOOP 0

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
TH1F *hg[5];//original gamma
TH1F *hgDop[5],*hgAddBack[5];
TH2F *hgg[5];//og gamma-gamma
TH2F *hggDop[5],*hggAddBack[5];
TH2F *hgNoDopVsAngle[5];//raw data vs. angles
TH2F *hgDopVsAngle[5];//Dop corr vs. angles
//Cuts
TCutG *cut_dtge[10];

void gamDraw(void) {
  //Get preloaded stuff, i.e. cuts
  cut_dtge[0] = (TCutG *) gDirectory->FindObjectAny("cut_dtge_s38");
  cut_dtge[1] = (TCutG *) gDirectory->FindObjectAny("cut_dtge_cl38");
  cut_dtge[2] = (TCutG *) gDirectory->FindObjectAny("cut_dtge_ar38");
  cut_dtge[3] = (TCutG *) gDirectory->FindObjectAny("cut_dtge_p33");

  //Initialize items
  Int_t ch=4096;
  Int_t rg=ch;
  for (Int_t recNum = 0; recNum<numRecoilProcess; recNum++) {
    hg[recNum] = new TH1F(Form("hg%d",recNum),
			  Form("%s hg%d; Gamma Energy [keV]",rName[recNum].Data(),recNum),
			  ch,0,rg);

    hgg[recNum] = new TH2F(Form("hgg%d",recNum),
			  Form("%s hgg%d; Gamma Energy [keV]; Gamma Energy [keV]",rName[recNum].Data(),recNum),
			  ch,0,rg,ch,0,rg);

    hgDop[recNum] = new TH1F(Form("hgDop%d",recNum),
   			Form("%s hgDop%d; Gamma Energy [keV]",rName[recNum].Data(),recNum),
   			ch,0,rg);

    hggDop[recNum] = new TH2F(Form("hggDop%d",recNum),
   			Form("%s hggDop%d; Gamma Energy [keV]; Gamma Energy [keV]",rName[recNum].Data(),recNum),
   			ch,0,rg,ch,0,rg);

    hgAddBack[recNum] = new TH1F(Form("hgAddBack%d",recNum),
       	Form("%s hgAddBack%d; Gamma Energy [keV]",rName[recNum].Data(),recNum),
       	ch,0,rg);

    hggAddBack[recNum] = new TH2F(Form("hggAddBack%d",recNum),
       	Form("%s hggAddBack%d; Gamma Energy [keV]; Gamma Energy [keV]",rName[recNum].Data(),recNum),
       	ch,0,rg,ch,0,rg);

    hgNoDopVsAngle[recNum] = new TH2F(Form("hgNoDopVsAngle%d",recNum),
       	Form("%s hgNoDopVsAngle%d; Gamma Energy [keV]; Angle [degrees]",
        rName[recNum].Data(),recNum),
        ch,0,rg,180,0,180);
    hgDopVsAngle[recNum] = new TH2F(Form("hgDopVsAngle%d",recNum),
       	Form("%s hgDopVsAngle%d; Gamma Energy [keV]; Angle [degrees]",
        rName[recNum].Data(),recNum),
        ch,0,rg,180,0,180);

  }

  //Pull the TTrees of interest
  fileName.Form("/Users/calemhoffman/Research/anl/gretinafma/gretinafma_git/analysis/gamFile.root");
  gamFileIn = new TFile(fileName,"UPDATE");
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
  /**** only if necessary ****/
 if (RUNLOOP == 1) {
   for (Int_t entryNumber=0;entryNumber<maxEntries; entryNumber++) {
     for (Int_t nTree=0; nTree<numRecoilProcess; nTree++) {
 if (entryNumber<nEntries[nTree]) {
   gtree[nTree]->GetEntry(entryNumber);
   for (Int_t gMult=0;gMult< gmult; gMult++) { /* need to apply dtge */
     if (cut_dtge[nTree]->IsInside(genergy[gMult],dtime[gMult])) {
       hg[nTree]->Fill(genergy[gMult]); //g fill
       for (Int_t iMult=gMult+1; iMult<gmult; iMult++) {
   hgg[nTree]->Fill(genergy[gMult],genergy[iMult]);
   hgg[nTree]->Fill(genergy[iMult],genergy[gMult]);
       }//gg fill
     }//dtge cut if
   }//gMult++
 }//nEntries[] if
     }//nTree loop
   }//entry loop
 }
 //
 // else { //RUNLOOP
 //   for (Int_t i=0;i<numRecoilProcess;i++) {
 //     hg[i] = (TH1F *) gDirectory->FindObjectAny(Form("hg%d",i));
 //   }
 // }

// //Doppler
// //User Ins
Int_t nTreeNum = 0; //only for s38 to start
Float_t beta = 0.033;

//Calcs
Float_t r1 = 0; //
Float_t r2 = 0;
Float_t intRad[100];
//Float_t beamdir[3] = {0,0,1};
Float_t modCCang[100];
Float_t modCCdopfac[100];
//Float_t iMaxX,iMaxY,iMaxZ;
Float_t radDiff[100][100];
Float_t crysTotAddBack[100];
Float_t radAddBackTest = 10; // distance between points for addback in cm
for (Int_t entryNumber=0;entryNumber<maxEntries; entryNumber++) {
  if (entryNumber<nEntries[nTreeNum]) {
    gtree[nTreeNum]->GetEntry(entryNumber);


    //loop to calc doppler etc, then fill in separate loop.
    for (Int_t multNumber=0; multNumber < gebMult; multNumber++) {

      intRad[multNumber] = (intMaxZ[multNumber]) /
        (TMath::Sqrt(intMaxX[multNumber]*intMaxX[multNumber]
          + intMaxY[multNumber]*intMaxY[multNumber]
          + intMaxZ[multNumber]*intMaxZ[multNumber]));
      modCCang[multNumber] = TMath::ACos(intRad[multNumber]);
      modCCdopfac[multNumber] = TMath::Sqrt(1. - beta*beta) /
      (1.0 - beta * TMath::Cos(modCCang[multNumber]));

      //For AddBack Calculate the distance between all other max points
      //if radius less than param then add up the TotalE then apply Doppler
      //Doppler from which angle though...

      //to start set all AddBacks as Tot_e (zero added values as we go)
      crysTotAddBack[multNumber] = crysTot_e[multNumber];

      for (Int_t j=multNumber+1; j < gebMult; j++ ) {

        r2 = (intMaxX[multNumber] - intMaxX[j])*(intMaxX[multNumber] - intMaxX[j])
        +(intMaxY[multNumber] - intMaxY[j])*(intMaxY[multNumber] - intMaxY[j])
        +(intMaxZ[multNumber] - intMaxZ[j])*(intMaxZ[multNumber] - intMaxZ[j]);
        radDiff[multNumber][j] = TMath::Sqrt(r2);

//printf("I,J: %d,%d X1: %f X2: %f Y1: %f Y2: %f Z1: %f Z2: %f R2: %f radDiff: %f\n\n",
// intMaxX[multNumber], intMaxX[j],
// intMaxY[multNumber], intMaxY[j],
// intMaxZ[multNumber], intMaxZ[j],

// printf("I,J: %d,%d radDiff: %f e[i]: %f, e[j]: %f\n",
//       multNumber,j,
//       radDiff[multNumber][j],
//     crysTot_e[multNumber], crysTot_e[j]);

        if (radDiff[multNumber][j] <= radAddBackTest) {
            crysTotAddBack[multNumber] += crysTot_e[j];

      //CANT DO THIS!!! Will Zero Out the Dop !!
      crysTot_e[j] = 0;

        } //radDiff if
      } //j++
// printf("** crysTotAddBack: %f\n\n",crysTotAddBack[multNumber]);

// **** to be moved to new loop _____
      if (cut_dtge[nTreeNum]->IsInside(genergy[multNumber],dtime[multNumber])) {
        hg[nTreeNum]->Fill(genergy[multNumber]); //g fill
        hgDop[nTreeNum]->Fill(crysTot_e[multNumber]/modCCdopfac[multNumber]); //dop fill
        if (crysTotAddBack[multNumber] > 0)
          hgAddBack[nTreeNum]->Fill(crysTotAddBack[multNumber]/modCCdopfac[multNumber]); //ab fill

        hgNoDopVsAngle[nTreeNum]->Fill(crysTot_e[multNumber],modCCang[multNumber]*180./TMath::Pi());
        hgDopVsAngle[nTreeNum]->Fill(crysTot_e[multNumber]/modCCdopfac[multNumber],
          modCCang[multNumber]*180./TMath::Pi());
      }
// **** to be moved to new loop ^^^^
    }


  }//entry loop
}

  // //Analyze histograms
  // FILE * fitFileOut;
  // fitFileOut = fopen ("gamFits.dat", "w+");
  // TCanvas *cc = new TCanvas("cc","fit can",1000,1000);
  // cc->Clear(); cc->Divide(2,2);
  //
  // Double_t mean,sigma,fitLow,fitHigh;
  //
  // //ar38 - 1643
  // mean = 1643;
  // sigma = 5;
  // fitLow = 1620;
  // fitHigh = 1660;
  //
  // for (Int_t ifit=0;ifit<numRecoilProcess;ifit++) {
  //   cc->cd(ifit+1);
  //   fitGaussP1(hg[ifit],mean,sigma,fitLow,fitHigh,fitFileOut);
  //   hg[ifit]->GetXaxis()->SetRangeUser(fitLow-100,fitHigh+100);
  // }
  // cc->Modified(); cc->Update();
  //
  // //Save and Draw
  for (Int_t i=0;i<numRecoilProcess;i++) {
    hg[i]->Write(); hgg[i]->Write();
    hgDop[i]->Write(); hgAddBack[i]->Write();
  }
  // //Cleanup


}
