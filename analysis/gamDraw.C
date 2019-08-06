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
TFile *gamFileOut;
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
  fileName.Form("/Users/calemhoffman/Research/anl/gretinafma/gretinafma/analysis/gamTree.root");
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

//User Ins
Int_t nTreeNum = 0; //only for s38 to start
Float_t beta = 0.033;

//Apply EventLists

//Calcs Variables
Float_t r1 = 0; //
Float_t r2 = 0;
Float_t intRad[100];
//Float_t beamdir[3] = {0,0,1};
Float_t modCCang[100];
Float_t modCCdopfac[100];
//Float_t iMaxX,iMaxY,iMaxZ;
Float_t radDiff[100][100];
//Float_t gEnergy[100];//orig genergy
Float_t crysTotE[100];//original Seg energies
Float_t crysTotDop[100];//Dopp corrected
Float_t crysTotAddBack[100];//Addback + Dopp corrected
Float_t radAddBackTest = 10; // distance between points for addback in cm

//Loop to calculate everything
for (Int_t entryNumber=0;entryNumber<maxEntries; entryNumber++) {
  if (entryNumber<nEntries[nTreeNum]) {
    gtree[nTreeNum]->GetEntry(entryNumber); //One and only pull of entries ??

//Loop over Segment Multiplicity
    for (Int_t gebMultNum=0; gebMultNum < gebMult; gebMultNum++) {
//PASS INFO
      crysTotE[gebMultNum] = crysTot_e[gebMultNum];
      //gEnergy[gebMultNum] = genergy[gebMultNum];

//DOPPLER
      intRad[gebMultNum] = (intMaxZ[gebMultNum]) /
        (TMath::Sqrt(intMaxX[gebMultNum]*intMaxX[gebMultNum]
          + intMaxY[gebMultNum]*intMaxY[gebMultNum]
          + intMaxZ[gebMultNum]*intMaxZ[gebMultNum]));

      modCCang[gebMultNum] = TMath::ACos(intRad[gebMultNum]);
      modCCdopfac[gebMultNum] = TMath::Sqrt(1. - beta*beta) /
      (1.0 - beta * TMath::Cos(modCCang[gebMultNum]));
      crysTotDop[gebMultNum] = crysTotE[gebMultNum]/modCCdopfac[gebMultNum];

//ADDBACK
      crysTotAddBack[gebMultNum] = crysTot_e[gebMultNum];
      // if (crysTotAddBack[gebMultNum]>0) {
      for (Int_t j=gebMultNum+1; j < gebMult; j++ ) {
        r2 = (intMaxX[gebMultNum] - intMaxX[j])*(intMaxX[gebMultNum] - intMaxX[j])
        +(intMaxY[gebMultNum] - intMaxY[j])*(intMaxY[gebMultNum] - intMaxY[j])
        +(intMaxZ[gebMultNum] - intMaxZ[j])*(intMaxZ[gebMultNum] - intMaxZ[j]);
        radDiff[gebMultNum][j] = TMath::Sqrt(r2);

        // printf("I,J: %d,%d radDiff: %f e[i]: %f, e[j]: %f\n",
        // gebMultNum,j,
        // radDiff[gebMultNum][j],
        // crysTot_e[gebMultNum], crysTot_e[j]);

        if (radDiff[gebMultNum][j] <= radAddBackTest) {
          crysTotAddBack[gebMultNum] += crysTot_e[j];
          crysTot_e[j] = 0;
        } //radDiff if
      } //j++
      //printf("** crysTotAddBack: %f\n\n",crysTotAddBack[gebMultNum]);
      crysTotAddBack[gebMultNum] = crysTotAddBack[gebMultNum]/modCCdopfac[gebMultNum];
      //printf("** crysTotAddBack w/ Dop: %f\n\n",crysTotAddBack[gebMultNum]);
    // } //if e>0
    } //gebMultNum

//Loop over segment multiplicity for histofill
    for (Int_t gebMultNum=0; gebMultNum < gebMult; gebMultNum++) {
            if (cut_dtge[nTreeNum]->IsInside(genergy[gebMultNum],dtime[gebMultNum])) {

              hg[nTreeNum]->Fill(genergy[gebMultNum]); //g fill
              hgDop[nTreeNum]->Fill(crysTotDop[gebMultNum]); //dop fill

              if (crysTotAddBack[gebMultNum] > 0)
                hgAddBack[nTreeNum]->Fill(crysTotAddBack[gebMultNum]); //ab fill

              hgNoDopVsAngle[nTreeNum]->Fill(crysTotE[gebMultNum],modCCang[gebMultNum]*180./TMath::Pi());
              hgDopVsAngle[nTreeNum]->Fill(crysTotDop[gebMultNum],
                modCCang[gebMultNum]*180./TMath::Pi());

            //     for (Int_t iMult=gMult+1; iMult<gmult; iMult++) {
            //  hgg[nTree]->Fill(genergy[gMult],genergy[iMult]);
            //  hgg[nTree]->Fill(genergy[iMult],genergy[gMult]);
            //     }//gg fill
          } //cut_dtge
    }//gebMultNum - fills
  }//entry loop
}

//Pull the TTrees of interest
fileName.Form("/Users/calemhoffman/Research/anl/gretinafma/gretinafma/analysis/gamFile.root");
gamFileOut = new TFile(fileName,"RECREATE");
gDirectory->ls();

  for (Int_t i=0;i<numRecoilProcess;i++) {
    hg[i]->Write(); hgg[i]->Write();
    hgDop[i]->Write(); hgAddBack[i]->Write();
  }

//Cleanup
//gamFileIn->Close();
//gamFileOut->Close();
}
