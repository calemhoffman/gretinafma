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
  Int_t lowRunNumber=77;
  Int_t highRunNumber=89;
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


   for (Int_t index=lowRunNumber;index<=highRunNumber;index++) {
    runN=index;
    printf("Starting sort of run number: %d\n",runN);
  TFile * fNameIn = new TFile(Form("/Users/calemhoffman/Research/anl/gretinafma/data/root_data/devel/run%d.root",runN));
  if (fNameIn == 0) printf("Error: file read in fail\n");
  TTree * tree = (TTree *) fNameIn->FindObjectAny("tree");
 
  
  tree->SetBranchAddress("runNumber",&runNumber);
  tree->SetBranchAddress("numHits",&numHits);
  tree->SetBranchAddress("left",left);
  tree->SetBranchAddress("right",right);
  tree->SetBranchAddress("up",up);
  tree->SetBranchAddress("down",down);
  tree->SetBranchAddress("e1",e1);
  tree->SetBranchAddress("e2",e2);
  tree->SetBranchAddress("e3",e3);
  tree->SetBranchAddress("e3",e3);
  tree->SetBranchAddress("tac",tac);
  tree->SetBranchAddress("fmaDeltaTime",fmaDeltaTime);
  tree->SetBranchAddress("fmaMult",fmaMult);
  tree->SetBranchAddress("gammaMult",&gammaMult);
  tree->SetBranchAddress("gammaEnergy",gammaEnergy);
  tree->SetBranchAddress("gammaTimestamp",gammaTimestamp);
  tree->SetBranchAddress("deltaTime",deltaTime);

  TFile * calFile = new TFile(Form("cal_%d.root",runN),"RECREATE");
  TTree * ctree = new TTree("ctree", "Cal Tree");

  Int_t run;
  Int_t hits;
  Float_t l,r,u,d,x,y;
  Float_t e[3];
  Int_t gmult;
  Float_t genergy[100];
  Float_t dtime[100];

  //Generic
  ctree->Branch("run", &run, "run/I");
  ctree->Branch("hits",&hits,"hits/I");
  //Positions
  ctree->Branch("l",&l,"l/F");
  ctree->Branch("r",&r,"r/F");
  ctree->Branch("u",&u,"u/F");
  ctree->Branch("d",&d,"d/F");
  ctree->Branch("x",&x,"x/F");
  ctree->Branch("y",&y,"y/F");
  //Energies
  ctree->Branch("e",e,"e[3]/F");
  //Gammas
  ctree->Branch("gmult",&gmult,"gmult/I");
  ctree->Branch("genergy",genergy,"genergy[gmult]/F");
  ctree->Branch("dtime",dtime,"dtime[gmult]/F");

  //Read Cals In
  ifstream inFile;
  inFile.open("fma_ecal.dat");
  Int_t lineRead=0;
  Int_t runNumberRead;
  Int_t detIndexRead;
  Double_t calibrationOffset[300][10];
  Double_t calibrationLinear[300][10];
  Double_t calibrationXOffset[300][10];
  Int_t tempInt1=0;
  Int_t tempInt2=0;
  Double_t tempDouble1=0,tempDouble2=0, tempDouble3=0;
  if( inFile.is_open() ) {
    while (1) {
      inFile >> tempInt1 >> tempInt2 >> tempDouble1 >> tempDouble2 >> tempDouble3;
      runNumberRead=tempInt1;
      detIndexRead=tempInt2;
      calibrationOffset[runNumberRead][detIndexRead]=tempDouble1;
      calibrationLinear[runNumberRead][detIndexRead]=tempDouble2;
      calibrationXOffset[runNumberRead][detIndexRead]=tempDouble3;
      lineRead++;
      if (!inFile.good()) break;
    }
    inFile.close();
    printf("... done reading cal file\n");
  }else{
    printf("... failed to read cal file\n");
    return;
  }
  Double_t xCalOffset[300];
  Double_t xCalScale[300];
  inFile.open("fma_xcal.dat");
  lineRead=0; tempInt1=0; tempDouble1=0; tempDouble2=0;
  if( inFile.is_open() ) {
    while (1) {
      inFile >> tempInt1 >> tempDouble1 >> tempDouble2;
      runNumberRead=tempInt1;
      xCalOffset[runNumberRead]=tempDouble1;
      xCalScale[runNumberRead]=tempDouble2;
      lineRead++;
      if (!inFile.good()) break;
    }
    inFile.close();
    printf("... done reading cal file\n");
  }else{
    printf("... failed to read cal file\n");
    return;
  } 

  //Read Cuts In // NEEDS TO LOOP OVER MULT ??
  /* TCutG * cut; */
  /* TFile * cutFileIn = new TFile("cuts.root"); */
  /* Bool_t isCutFileOpen = cutFileIn->IsOpen(); */

  /* if (isCutFileOpen) { */
  /*   cut = (TCutG *) cutFileIn->FindObjectAny("cut_gen_dtge"); */
  /* } */
  
   //Process Events
  Int_t nEntries = tree->GetEntries();
  printf("nEntries: %d\n",nEntries);

  for (Int_t entryNumber=0;entryNumber<=nEntries; entryNumber++) {
    tree->GetEntry(entryNumber);
   
    run=runN;
    hits=numHits;
    if (left[0]>=-500) {
      l = left[0];
    } else {
      l = left[0]+6560.0;
    }

    if (right[0]>=-500) {
      r = right[0]/0.934829;
    } else {
      r = (right[0]+6560.0)/0.934829;
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
    
    x = (l-r)-xCalOffset[runN];
    y = (u-d);

    if (e1[0]>=0) {
      e[0] = (e1[0]-calibrationXOffset[run][0])*calibrationLinear[run][0]+calibrationOffset[run][0];
    } else {
      e[0] = (e1[0]-calibrationXOffset[run][0]+6560.0)*calibrationLinear[run][0]+calibrationOffset[run][0];
    }
    if (e2[0]>=0) {
      e[1] = (e2[0]-calibrationXOffset[run][1])*calibrationLinear[run][1]+calibrationOffset[run][1];
    } else {
      e[1] = (e2[0]-calibrationXOffset[run][1]+6560.0)*calibrationLinear[run][1]+calibrationOffset[run][1];
    }
    if (e3[0]>=0) {
      e[2] = e3[0] + calibrationOffset[run][2];
    } else {
      e[2] = (e3[0] + 6560.0)+calibrationOffset[run][2];
    }

    gmult = gammaMult;
    for (Int_t i=0;i<gmult;i++) {
      genergy[i] = gammaEnergy[i];
      dtime[i] = deltaTime[i];
    }

     if (entryNumber<1)
      printf("entryNumber:%d \n l:%4.0f r:%4.0f u:%4.0f d:%4.0f \n x:%4.0f y:%4.0f\n e1:%4.2f e2:%4.2f e3:%4.2f gammaMult:%d gammaEnergy[0]:%4.1f\n\n",
	     entryNumber,l,r,u,d,x,y,e[0],e[1],e[2],gammaMult,gammaEnergy[0]);


     ctree->Fill();

  } //entryNumber Loop
  ctree->Write();
  //printf("Run Number: %d\n",runNumber);
  /* printf("left: %f\n",left[0]); */
   }

}
