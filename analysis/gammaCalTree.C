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
#include <TFile.h>

#define maxEntryToSort 1e8
#define SOURCE 0 //0 - Eu, 1 - ???

TH1F *hg[5];//original gamma
TH1F *hgDop[5],*hgAddBack[5],*hgAdd2Back[5];
TH2F *hgg[5];//og gamma-gamma
TH2F *hggDop[5],*hggAddBack[5];
TH2F *hgAddBackVsAngle[5];//best gam vs. angles
TH1I *hMults[5];
TH1I *hEventType[5];
TString rName[5] = {"all"};

TFile *gamFileIn;
TFile *gamFileOut;
TString fileName;

void gammaCalTree() {
  Int_t runN;
  Int_t runNumber;
  Int_t numHits=1;
  Float_t left[numHits];
  Float_t right[numHits];
  Float_t up[numHits];
  Float_t down[numHits];
  Float_t e1[numHits];
  Float_t e2[numHits];
  Float_t e3[numHits];
  Float_t tac[numHits];
  Float_t fmaDeltaTime[numHits];
  Int_t fmaMult[10];
  Int_t gammaMult;
  Float_t gammaEnergy[100];
  Float_t gammaTimestamp[100];
  Float_t deltaTime[100];
  Int_t gDeltaTime[100];
  Int_t gebMult;
  Int_t crysType[100];
  Int_t crysId[100];
  Int_t crysNum[100];
  Float_t crysTot_e[100];
  long long int crysTimestamp[100];
  double crysTrigtime[100];
  Float_t crysT0[100];
  Float_t crysCfd[100];
  Float_t crysChisq[100];
  Float_t crysNormChisq[100];
  Float_t crysBaseline[100];
  unsigned int crysTpad[100];
  Float_t crysPolAngle[100];
  Float_t intMaxX[100];
  Float_t intMaxY[100];
  Float_t intMaxZ[100];
  Float_t intMaxE[100];
  Int_t intMaxSeg[100];
  Float_t intMaxSegE[100];

  //Initialize items
  Int_t ch=4096;
  Int_t rg=ch;
  for (Int_t recNum = 0; recNum<2; recNum++) {
    hMults[recNum] = new TH1I(Form("hMults%d",recNum),Form("hMults%d",recNum),100,0,100);
    hEventType[recNum] = new TH1I(Form("hEventType%d",recNum),Form("hEventType%d",recNum),10,0,10);

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
    hgAdd2Back[recNum] = new TH1F(Form("hgAdd2Back%d",recNum),
        Form("%s hgAdd2Back%d; Gamma Energy [keV]",rName[recNum].Data(),recNum),
        ch,0,rg);

    hggAddBack[recNum] = new TH2F(Form("hggAddBack%d",recNum),
       	Form("%s hggAddBack%d; Gamma Energy [keV]; Gamma Energy [keV]",rName[recNum].Data(),recNum),
       	ch,0,rg,ch,0,rg);

    hgAddBackVsAngle[recNum] = new TH2F(Form("hgAddBackVsAngle%d",recNum),
        Form("%s hgAddBackVsAngle%d; Gamma Energy [keV]; Angle [degrees]",
        rName[recNum].Data(),recNum),
        ch,0,rg,180,0,180);
   }

  Int_t goodRun[2] = {0,0};//303 (152Eu), 304 (??)

  for (Int_t index=0;index<=2;index++) {
    runN=303+index;
    printf("Starting sort of run number: %d\n",runN);
    if (goodRun[index]==SOURCE) {
      //TFile * fNameIn = new TFile(Form("/lcrc/project/HELIOS/gretinafma/data/run%d.root",runN));
      TFile * fNameIn = new TFile(Form("/Users/calemhoffman/Research/anl/gretinafma/data/source_data/run%d.root",runN));

      if (fNameIn == 0) printf("Error: file read in fail\n");
      TTree * tree = (TTree *) fNameIn->FindObjectAny("tree");

      tree->SetBranchAddress("runNumber",&runNumber);
      tree->SetBranchAddress("numHits",&numHits);
      // tree->SetBranchAddress("left",left);
      // tree->SetBranchAddress("right",right);
      // tree->SetBranchAddress("up",up);
      // tree->SetBranchAddress("down",down);
      // tree->SetBranchAddress("e1",e1);
      // tree->SetBranchAddress("e2",e2);
      // tree->SetBranchAddress("e3",e3);
      // tree->SetBranchAddress("e3",e3);
      // tree->SetBranchAddress("tac",tac);
      // tree->SetBranchAddress("fmaDeltaTime",fmaDeltaTime);
      // tree->SetBranchAddress("fmaMult",fmaMult);
      tree->SetBranchAddress("gammaMult",&gammaMult);
      tree->SetBranchAddress("gammaEnergy",gammaEnergy);
      tree->SetBranchAddress("gammaTimestamp",gammaTimestamp);
      tree->SetBranchAddress("deltaTime",deltaTime);
      tree->SetBranchAddress("gDeltaTime",gDeltaTime);
      tree->SetBranchAddress("gebMult",&gebMult);
      tree->SetBranchAddress("crysType",crysType);
      tree->SetBranchAddress("crysId",crysId);
      tree->SetBranchAddress("crysNum",crysNum);
      tree->SetBranchAddress("crysTot_e",crysTot_e);
      tree->SetBranchAddress("crysPolAngle",crysPolAngle);
      tree->SetBranchAddress("intMaxX",intMaxX);
      tree->SetBranchAddress("intMaxY",intMaxY);
      tree->SetBranchAddress("intMaxZ",intMaxZ);
      tree->SetBranchAddress("intMaxE",intMaxE);
      tree->SetBranchAddress("intMaxSeg",intMaxSeg);
      tree->SetBranchAddress("intMaxSegE",intMaxSegE);
      tree->SetBranchAddress("crysTimestamp",crysTimestamp);
      tree->SetBranchAddress("crysTrigtime",crysTrigtime);
      tree->SetBranchAddress("crysT0",crysT0);

      //User Ins
      //Int_t nTreeNum = 0; //only for s38 to start
      Float_t beta = 0.0;//0.03375; //s38 from Fits
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
      Float_t crysTotAdd2Back[100];//Add2back + Dopp corrected
      Float_t radAddBackTest = 10; // distance between points for addback in cm
      Int_t addBackDopNum = 0;

     //Process Events
     Int_t nEntries = tree->GetEntries();
     printf("nEntries: %d\n",nEntries);
     Int_t entrySorted = 0;
      for (Int_t entryNumber=0;entryNumber<=nEntries; entryNumber++) {
        if (entryNumber <= maxEntryToSort) {
          tree->GetEntry(entryNumber);
          entrySorted = entryNumber;
          hMults[index]->Fill(gebMult);//histo mults
          for (Int_t gebMultNum=0;gebMultNum<gebMult; gebMultNum++) {
      //PASS INFO
          crysTotE[gebMultNum] = crysTot_e[gebMultNum];
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
          crysTotAdd2Back[gebMultNum] = crysTot_e[gebMultNum];
          addBackDopNum = gebMultNum;
          hEventType[index]->Fill(1);
            if (crysTotE[gebMultNum]>0) hEventType[index]->Fill(2);
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
                hEventType[index]->Fill(3);
                crysTotAddBack[gebMultNum] += crysTot_e[j];
                crysTotAdd2Back[gebMultNum] += crysTot_e[j];
                if (crysTot_e[j] > crysTot_e[gebMultNum]) addBackDopNum = j;
                crysTot_e[j] = 0;
      //Add2Back - did not improve anything
                for (Int_t k=j+1;k<gebMult;k++){
                  r2 = (intMaxX[gebMultNum] - intMaxX[j])*(intMaxX[gebMultNum] - intMaxX[j])
                  +(intMaxY[gebMultNum] - intMaxY[j])*(intMaxY[gebMultNum] - intMaxY[j])
                  +(intMaxZ[gebMultNum] - intMaxZ[j])*(intMaxZ[gebMultNum] - intMaxZ[j]);
                  radDiff[j][k] = TMath::Sqrt(r2);

                  if (radDiff[j][k] <= radAddBackTest / 3.) {
                    hEventType[index]->Fill(4);
                    crysTotAdd2Back[gebMultNum] += crysTot_e[k];
                    //crysTot_e[k] = 0;
                  }//radDiff if
                }// k++
              } //radDiff if
            } //j++
          //printf("** crysTotAddBack: %f\n\n",crysTotAddBack[gebMultNum]);
          crysTotAddBack[gebMultNum] = crysTotAddBack[gebMultNum]/modCCdopfac[gebMultNum];
          crysTotAdd2Back[gebMultNum] = crysTotAdd2Back[gebMultNum]/modCCdopfac[gebMultNum];//[addBackDopNum];
          //printf("** crysTotAddBack w/ Dop: %f\n\n",crysTotAddBack[gebMultNum]);
          }
//Loop over segment multiplicity for histofill
    for (Int_t gebMultNum=0; gebMultNum < gebMult; gebMultNum++) {

              hg[index]->Fill(gammaEnergy[gebMultNum]); //g fill
              hgDop[index]->Fill(crysTotDop[gebMultNum]); //dop fill

              if (crysTotAddBack[gebMultNum] > 0) {
                if ((modCCang[gebMultNum]*180./TMath::Pi())>60.0 && (modCCang[gebMultNum]*180./TMath::Pi())<180.0) {
                  hgAddBack[index]->Fill(crysTotAddBack[gebMultNum]); //ab fill
                  hgAddBackVsAngle[index]->Fill(crysTotAddBack[gebMultNum],
                  modCCang[gebMultNum]*180./TMath::Pi());
                }
              }

              if (crysTotAdd2Back[gebMultNum] > 0) {
                if ((modCCang[gebMultNum]*180./TMath::Pi())>60.0 && (modCCang[gebMultNum]*180./TMath::Pi())<180.0) {
                  hgAdd2Back[index]->Fill(crysTotAdd2Back[gebMultNum]); //a2b fill
                }
              }
                for (Int_t iMult=gebMultNum+1; iMult<gebMult; iMult++) {
                  hgg[index]->Fill(gammaEnergy[gebMultNum],gammaEnergy[iMult]);
                  hgg[index]->Fill(gammaEnergy[iMult],gammaEnergy[gebMultNum]);
                  hggDop[index]->Fill(crysTotDop[gebMultNum],crysTotDop[iMult]);
                  hggDop[index]->Fill(crysTotDop[iMult],crysTotDop[gebMultNum]);
                  if (crysTotAddBack[gebMultNum] > 0 && crysTotAddBack[iMult] > 0) {
                    if ((modCCang[gebMultNum]*180./TMath::Pi())>60.0 && (modCCang[gebMultNum]*180./TMath::Pi())<180.0) {
                      hggAddBack[index]->Fill(crysTotAddBack[gebMultNum],crysTotAddBack[iMult]);
                      hggAddBack[index]->Fill(crysTotAddBack[iMult],crysTotAddBack[gebMultNum]);
                    }
                  }
                }//gg fill
    }//gebMultNum - fills

      } //max entry check
    } //entryNumber Loop
      printf("Finished sorting Entry %d out of %d\n",entrySorted,nEntries);
    }//if >0
  }//for runs

  fileName.Form("/Users/calemhoffman/Research/anl/gretinafma/gretinafma/analysis/gamCalFile.root");
  gamFileOut = new TFile(fileName,"RECREATE");
  gDirectory->ls();

    for (Int_t i=0;i<2;i++) {
      hg[i]->Write(); hgDop[i]->Write(); hgAddBack[i]->Write(); hgAdd2Back[i]->Write();
      hgg[i]->Write(); hggDop[i]->Write(); hggAddBack[i]->Write();
      hMults[i]->Write(); hEventType[i]->Write(); hgAddBackVsAngle[i]->Write();
    }

}//gammaCalTree
