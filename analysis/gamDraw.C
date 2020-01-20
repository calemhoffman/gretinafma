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

//#include "AutoFit.C"

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
Int_t gtime[100][100];
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
//TH1F *hgDop[5];
TH1F *hgAddBack[5],*hgAdd2Back[5];
TH2F *hgg[5];//og gamma-gamma
//TH2F *hggDop[5],
TH2F *hggAddBack[5];
//TH2F *hggRDC0[5];
Float_t angleSpread=15.0;
TH2F *hgNoDopVsAngle[5];//raw data vs. angles
TH2F *hgDopVsAngle[5];//Dop corr vs. angles
TH2F *hgAddBackVsAngle[5];//best gam vs. angles
TH1I *hMults[5];
TH1I *hEventType[5];
#define numScan 50
TH1F *hscan[numScan]; //gam scans
TH2F *hxVg;
TH2F *he0Vg;
TH2F *he2Vg;
TH2F *hdtVg;
TH2F *he0x,*he1e3,*he1e2,*he2e3,*hdtge;
//Cuts
TCutG *cut_dtge[10];
TCutG *cut_e1e3_scan[10];
TCutG *cut_e1e3_s38;

void gamDraw(void) {
  //Get preloaded stuff, i.e. cuts
  cut_dtge[0] = (TCutG *) gDirectory->FindObjectAny("cut_dtge_s38");
  cut_dtge[1] = (TCutG *) gDirectory->FindObjectAny("cut_dtge_cl38");
  cut_dtge[2] = (TCutG *) gDirectory->FindObjectAny("cut_dtge_ar38");
  cut_dtge[3] = (TCutG *) gDirectory->FindObjectAny("cut_dtge_p33");
  cut_e1e3_s38 = (TCutG *) gDirectory->FindObjectAny("cut_e1e3_s38");

  for (Int_t i=0;i<5;i++)
    cut_e1e3_scan[i] = (TCutG *) gDirectory->FindObjectAny(Form("cut_e1e3_scan%d",i));

  //Initialize items
  Int_t ch=4096;
  Int_t rg=ch;
  for (Int_t i=0;i<numScan;i++)
    hscan[i] = new TH1F(Form("hscan%d",i),Form("hscan%d",i),ch,0,rg);

  hxVg = new TH2F("hxVg","hxVg; x; g",1000,-2000,2000,4000,0,4000);
  he0Vg = new TH2F("he0Vg","he0Vg; e0; g",1000,0,4000,4000,0,4000);
  he2Vg = new TH2F("he2Vg","he2Vg; e2; g",1000,0,4000,4000,0,4000);
  hdtVg = new TH2F("hdtVg","hdtVg; dt; g",1000,0,4000,4000,0,4000);

  he0x = new TH2F("he0x","he0x; e0; x",1500,-1000,500,1000,0,3000);
  he1e3 = new TH2F("he1e3","he1e3; e1; e3",1000,0,3000,1000,0,3000);
  he1e2 = new TH2F("he1e2","he1e2; e1; e2",1000,0,3000,1000,0,3000);
  he2e3 = new TH2F("he2e3","he2e3; e2; e3",1000,0,3000,1000,0,3000);
  hdtge = new TH2F("hdtge","hdtge; ge; dt",10000,0,10000,75,0,150);
  for (Int_t recNum = 0; recNum<numRecoilProcess; recNum++) {
    hMults[recNum] = new TH1I(Form("hMults%d",recNum),Form("hMults%d",recNum),100,0,100);
    hEventType[recNum] = new TH1I(Form("hEventType%d",recNum),Form("hEventType%d",recNum),10,0,10);

    hg[recNum] = new TH1F(Form("hg%d",recNum),
			  Form("%s hg%d; Gamma Energy [keV]",rName[recNum].Data(),recNum),
			  ch,0,rg);

    hgg[recNum] = new TH2F(Form("hgg%d",recNum),
			  Form("%s hgg%d; Gamma Energy [keV]; Gamma Energy [keV]",rName[recNum].Data(),recNum),
			  ch,0,rg,ch,0,rg);

    // hgDop[recNum] = new TH1F(Form("hgDop%d",recNum),
   // 			Form("%s hgDop%d; Gamma Energy [keV]",rName[recNum].Data(),recNum),
   // 			ch,0,rg);
    //
    // hggDop[recNum] = new TH2F(Form("hggDop%d",recNum),
   // 			Form("%s hggDop%d; Gamma Energy [keV]; Gamma Energy [keV]",rName[recNum].Data(),recNum),
   // 			ch,0,rg,ch,0,rg);
    //
    hgAddBack[recNum] = new TH1F(Form("hgAddBack%d",recNum),
       	Form("%s hgAddBack%d; Gamma Energy [keV]",rName[recNum].Data(),recNum),
       	ch,0,rg);
    hgAdd2Back[recNum] = new TH1F(Form("hgAdd2Back%d",recNum),
        Form("%s hgAdd2Back%d; Gamma Energy [keV]",rName[recNum].Data(),recNum),
        ch,0,rg);

    hggAddBack[recNum] = new TH2F(Form("hggAddBack%d",recNum),
       	Form("%s hggAddBack%d; Gamma Energy [keV]; Gamma Energy [keV]",rName[recNum].Data(),recNum),
       	ch,0,rg,ch,0,rg);

    // hggRDC0[recNum] = new TH2F(Form("hggRDC0%d",recNum),
    //    	Form("%s hggRDC0%d; Gamma Energy 90 [keV]; Gamma Energy off [keV]",rName[recNum].Data(),recNum),
    //    	ch,0,rg,ch,0,rg);
    //
    hgNoDopVsAngle[recNum] = new TH2F(Form("hgNoDopVsAngle%d",recNum),
       	Form("%s hgNoDopVsAngle%d; Gamma Energy [keV]; Angle [degrees]",
        rName[recNum].Data(),recNum),
        ch,0,rg,180,0,180);
    hgDopVsAngle[recNum] = new TH2F(Form("hgDopVsAngle%d",recNum),
       	Form("%s hgDopVsAngle%d; Gamma Energy [keV]; Angle [degrees]",
        rName[recNum].Data(),recNum),
        ch,0,rg,180,0,180);

    hgAddBackVsAngle[recNum] = new TH2F(Form("hgAddBackVsAngle%d",recNum),
       	Form("%s hgAddBackVsAngle%d; Gamma Energy [keV]; Angle [degrees]",
        rName[recNum].Data(),recNum),
        ch*4,0,rg,180,0,180);
   }

  //Pull the TTrees of interest
  fileName.Form("gamTree.root");
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
    gtree[nt]->SetBranchAddress("gtime",gtime);
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
//Int_t nTreeNum = 0; //only for s38 to start
Float_t beta = 0.03375; //s38 from Fits

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
Float_t crysTotAdd2Back[100];//Add2back + Dopp corrected
Float_t radAddBackTest = 10; // distance between points for addback in cm
Int_t addBackDopNum = 0;

//Loop to calculate everything
for (Int_t entryNumber=0;entryNumber<maxEntries; entryNumber++) {
  for (Int_t nTreeNum=0;nTreeNum<numRecoilProcess;nTreeNum++) {
  if (entryNumber<nEntries[nTreeNum]) {
    gtree[nTreeNum]->GetEntry(entryNumber); //One and only pull of entries ??
    hMults[nTreeNum]->Fill(gebMult);//histo mults
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
      crysTotAdd2Back[gebMultNum] = crysTot_e[gebMultNum];
      addBackDopNum = gebMultNum;
      hEventType[nTreeNum]->Fill(1);
      if (crysTotE[gebMultNum]>0) hEventType[nTreeNum]->Fill(2);
    //  if (crysTotAddBack[gebMultNum]>0) {
      for (Int_t j=gebMultNum+1; j < gebMult; j++ ) {
        r2 = (intMaxX[gebMultNum] - intMaxX[j])*(intMaxX[gebMultNum] - intMaxX[j])
        +(intMaxY[gebMultNum] - intMaxY[j])*(intMaxY[gebMultNum] - intMaxY[j])
        +(intMaxZ[gebMultNum] - intMaxZ[j])*(intMaxZ[gebMultNum] - intMaxZ[j]);
        radDiff[gebMultNum][j] = TMath::Sqrt(r2);

        // printf("I,J: %d,%d radDiff: %f e[i]: %f, e[j]: %f\n",
        // gebMultNum,j,
        // radDiff[gebMultNum][j],
        // crysTot_e[gebMultNum], crysTot_e[j]);

        if ( (radDiff[gebMultNum][j] <= radAddBackTest) && (gtime[gebMultNum][j]<40) ){
          hEventType[nTreeNum]->Fill(3);
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

            if ( (radDiff[j][k] <= radAddBackTest / 3.) && (gtime[j][k]<40) ) {
              hEventType[nTreeNum]->Fill(4);
              crysTotAdd2Back[gebMultNum] += crysTot_e[k];
              //crysTot_e[k] = 0;
            }//radDiff if
          }// k++

        } //radDiff if
      } //j++
      //printf("** crysTotAddBack: %f\n\n",crysTotAddBack[gebMultNum]);
      crysTotAddBack[gebMultNum] = crysTotAddBack[gebMultNum]/modCCdopfac[gebMultNum];//DOPPLER
      crysTotAddBack[gebMultNum] = crysTotAddBack[gebMultNum] - (0.002*x);//X CORRECTION (from hxVg spectrum)
      crysTotAddBack[gebMultNum] = crysTotAddBack[gebMultNum] + (e[0]-1625)*0.002488;//e[0] from he0Vg specrum
      crysTotAdd2Back[gebMultNum] = crysTotAdd2Back[gebMultNum]/modCCdopfac[gebMultNum];//[addBackDopNum];
      //printf("** crysTotAddBack w/ Dop: %f\n\n",crysTotAddBack[gebMultNum]);
  //  } //if e>0
    } //gebMultNum

//Loop over segment multiplicity for histofill
    for (Int_t gebMultNum=0; gebMultNum < gebMult; gebMultNum++) {
      if ( /*(cut_e1e3_scan[1]->IsInside(e[2],e[0]))*/
          cut_e1e3_s38->IsInside(e[2],e[0]) ) {//e1e3 scan cut
            if (cut_dtge[nTreeNum]->IsInside(genergy[gebMultNum],dtime[gebMultNum])) {
              he0x->Fill(x,e[0]) ;
              he1e3->Fill(e[2],e[0]);he1e2->Fill(e[1],e[0]);he2e3->Fill(e[2],e[1]);
              hdtge->Fill(genergy[gebMultNum],dtime[gebMultNum]);
              hg[nTreeNum]->Fill(genergy[gebMultNum]); //g fill
              //hgDop[nTreeNum]->Fill(crysTotDop[gebMultNum]); //dop fill

              if (crysTotAddBack[gebMultNum] > 0) {
                if ((modCCang[gebMultNum]*180./TMath::Pi())>60.0 && (modCCang[gebMultNum]*180./TMath::Pi())<180.0) {
                  hgAddBack[nTreeNum]->Fill(crysTotAddBack[gebMultNum]); //ab fill
                  hgAddBackVsAngle[nTreeNum]->Fill(crysTotAddBack[gebMultNum],
                  modCCang[gebMultNum]*180./TMath::Pi());
                }
              }

              if (crysTotAdd2Back[gebMultNum] > 0) {
                if ((modCCang[gebMultNum]*180./TMath::Pi())>60.0 && (modCCang[gebMultNum]*180./TMath::Pi())<180.0) {
                  hgAdd2Back[nTreeNum]->Fill(crysTotAdd2Back[gebMultNum]); //a2b fill
                }
              }

              hgNoDopVsAngle[nTreeNum]->Fill(crysTotE[gebMultNum],modCCang[gebMultNum]*180./TMath::Pi());
              hgDopVsAngle[nTreeNum]->Fill(crysTotAddBack[gebMultNum],
              modCCang[gebMultNum]*180./TMath::Pi());


                for (Int_t iMult=gebMultNum+1; iMult<gebMult; iMult++) {
                  if (gtime[gebMultNum][iMult]<40) {
                    hgg[nTreeNum]->Fill(genergy[gebMultNum],genergy[iMult]);
                    hgg[nTreeNum]->Fill(genergy[iMult],genergy[gebMultNum]);
                    // hggDop[nTreeNum]->Fill(crysTotDop[gebMultNum],crysTotDop[iMult]);
                    // hggDop[nTreeNum]->Fill(crysTotDop[iMult],crysTotDop[gebMultNum]);
                    if (crysTotAddBack[gebMultNum] > 0 && crysTotAddBack[iMult] > 0) {
                      if ((modCCang[gebMultNum]*180./TMath::Pi())>60.0 && (modCCang[gebMultNum]*180./TMath::Pi())<180.0
                        && (modCCang[iMult]*180./TMath::Pi())>60.0 && (modCCang[iMult]*180./TMath::Pi())<180.0 ) {
                          hggAddBack[nTreeNum]->Fill(crysTotAddBack[gebMultNum],crysTotAddBack[iMult]);
                          hggAddBack[nTreeNum]->Fill(crysTotAddBack[iMult],crysTotAddBack[gebMultNum]);
                            ;//RDC0 stuff, is this right??? Is all g-g right??
                          if ( (90.0-angleSpread < modCCang[gebMultNum]*180./TMath::Pi())
                            && (modCCang[gebMultNum]*180./TMath::Pi() < 90.0+angleSpread)
                            && (130.0-angleSpread < modCCang[iMult]*180./TMath::Pi())
                            && (modCCang[iMult]*180./TMath::Pi() < 130.0+angleSpread) )
                            ;  // hggRDC0[nTreeNum]->Fill(crysTotAddBack[gebMultNum],crysTotAddBack[iMult]);
                          if ( (90.0-angleSpread < modCCang[iMult]*180./TMath::Pi())
                            && (modCCang[iMult]*180./TMath::Pi() < 90.0+angleSpread)
                            && (130.0-angleSpread < modCCang[gebMultNum]*180./TMath::Pi())
                            && (modCCang[gebMult]*180./TMath::Pi() < 130.0+angleSpread) )
                            ;  // hggRDC0[nTreeNum]->Fill(crysTotAddBack[iMult],crysTotAddBack[gebMultNum]);
                      }
                    }
                  }//gtime if
                }//gg fill
          } //cut_dtge
    }//gebMultNum - fills
  } //e1e3 scan cuts
  } //nTreeNum
  //Work on only the AddBack for 38S and hscans
  // nTreeNum = 0;
  // Int_t scanCounter=0;
  // for (Int_t firstLoop=0; firstLoop<10; firstLoop++) {//e[0]
  //   for (Int_t secondLoop=0; secondLoop<10; secondLoop++) {//e[1]
  //     for (Int_t thirdLoop=0; thirdLoop<10; thirdLoop++) {//e[2]
  //       if ( (e[0]>firstLoop*500 && e[0]<firstLoop*500+500)
  //         && (e[1]>secondLoop*500 && e[1]<secondLoop*500+500)
  //         && (e[2]>thirdLoop*500 && e[2]<thirdLoop*500+500) ) {
  //           for (Int_t gebMultNum=0; gebMultNum < gebMult; gebMultNum++) {
  //             scanCounter = firstLoop + secondLoop*10 + thirdLoop*100;
  //             hscan[scanCounter]->Fill(crysTotAddBack[gebMultNum]);
  //           } //gebMultNum
  //       }//if
  //     }//3loop
  //   }//2loop
  // }//1loop
  //Loop over scans, either cuts or ranges
  Int_t scanCounter=0;
  Int_t xmin=0;
  Int_t xmax=0;
  nTreeNum=0;
  for (Int_t gebMultNum=0; gebMultNum < gebMult; gebMultNum++) {
    if ( cut_dtge[nTreeNum]->IsInside(genergy[gebMultNum],dtime[gebMultNum]) ) {
      for (Int_t firstLoop=0;firstLoop<5;firstLoop++) {
        if ( cut_e1e3_scan[firstLoop]->IsInside(e[2],e[0]) ) {
          for (Int_t secondLoop=0; secondLoop<10; secondLoop++) {
            xmin=-600 + (secondLoop*100); xmax=-500 + (secondLoop*100);
            scanCounter = firstLoop*10 + secondLoop;
            if ( (x>xmin) && (x<=xmax) )
              hscan[scanCounter]->Fill(crysTotAddBack[gebMultNum]);
          }
        }
      }
    }
  } //gebMultNum

  //resolution checks
  for (Int_t gebMultNum=0; gebMultNum < gebMult; gebMultNum++) {
    if ( cut_dtge[nTreeNum]->IsInside(genergy[gebMultNum],dtime[gebMultNum]) ) {
      if (crysTotAddBack[gebMultNum] > 0) {
        if ((modCCang[gebMultNum]*180./TMath::Pi())>60.0 && (modCCang[gebMultNum]*180./TMath::Pi())<180.0) {
          if ( cut_e1e3_scan[0]->IsInside(e[2],e[0]) ) {
            hxVg->Fill(x,crysTotAddBack[gebMultNum]);
            he0Vg->Fill(e[0],crysTotAddBack[gebMultNum]);
            he2Vg->Fill(e[2],crysTotAddBack[gebMultNum]);
            //hdtVg->Fill(dtime,crysTotAddBack[gebMultNum]);
          }
        }
      }
    }
  }
//  if () printf("another 1 million\n");
  }//entry loop
}

//Pull the TTrees of interest
fileName.Form("gamFile.root");
gamFileOut = new TFile(fileName,"RECREATE");
gDirectory->ls();

  for (Int_t i=0;i<numRecoilProcess;i++) {
    hg[i]->Write();
    //hgDop[i]->Write()
    hgAddBack[i]->Write(); hgAdd2Back[i]->Write();
    hgg[i]->Write();
    //hggDop[i]->Write();
    hggAddBack[i]->Write(); //hggRDC0[i]->Write();
    hgNoDopVsAngle[i]->Write(); hgDopVsAngle[i]->Write(); hgAddBackVsAngle[i]->Write();
    hMults[i]->Write(); hEventType[i]->Write();
  }
  for (Int_t i=0;i<numScan;i++)
    hscan[i]->Write();

  hxVg->Write();he0Vg->Write(); he2Vg->Write();

  he0x->Write(); he1e3->Write(); hdtge->Write();
  he1e2->Write(); he2e3->Write();

//Cleanup
gamFileIn->Close();
//gamFileOut->Close();
}
