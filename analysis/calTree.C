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

TCutG *cut_ar38_e1x;
TCutG *cut_ar38_dtge;
TCutG *cut_ar38_e1e3;
TCutG *cut_ar38_e1e2;
TCutG *cut_ar38_e2e3;
TCutG *cut_cl38_e1x;
TCutG *cut_cl38_dtge;
TCutG *cut_cl38_e1e3;
TCutG *cut_cl38_e1e2;
TCutG *cut_cl38_e2e3;
TCutG *cut_s38_e1x;
TCutG *cut_s38_dtge;
TCutG *cut_s38_e1e3;
TCutG *cut_s38_e1e2;
TCutG *cut_s38_e2e3;
TCutG *all_aq_e0x;
TCutG *all_z_e1e3;

void calTree() {
  Int_t lowRunNumber=50;
  Int_t highRunNumber=295;
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

Int_t goodRun[300] = {0,0,0,0,0,0,0,0,0,0,//0
		      0,0,0,0,0,0,0,0,0,0,//10
		      0,0,0,0,0,0,0,0,0,0,//20
		      0,0,0,0,0,0,0,0,0,0,//30
		      0,0,0,0,0,0,0,0,0,0,//40
		      0,0,0,0,0,0,0,0,0,0,//50
		      0,0,0,0,0,0,0,0,0,0,//60
		      0,0,0,0,0,0,0,1,1,1,//70
		      1,1,1,1,1,1,1,1,1,1,//80
		      1,1,1,1,1,0,0,0,0,1,//90
		      1,1,1,1,1,1,1,1,1,1,//100
		      1,1,1,1,1,1,1,1,1,1,//110
		      1,1,1,1,0,1,1,1,1,1,//120
		      1,1,1,1,1,0,0,0,1,1,//130
		      1,1,1,1,1,1,0,0,0,0,//140
		      1,1,1,1,1,1,1,1,1,1,//150
		      0,1,1,1,1,1,0,1,1,0,//160
		      1,1,1,1,1,0,0,0,0,0,//170
		      0,0,0,0,0,0,0,0,0,0,//180
		      0,0,0,0,0,0,1,1,1,0,//190
		      1,0,1,1,1,1,1,1,1,1,//200
		      0,0,1,1,1,1,1,1,1,1,//210
		      1,0,0,1,1,1,1,1,1,0,//220
		      1,1,1,1,1,1,1,1,1,0,//230
		      1,1,1,1,1,1,0,0,1,1,//240
		      1,1,1,1,1,1,1,1,1,1,//250
		      0,1,1,1,1,1,1,1,1,1,//260
		      1,1,1,1,1,1,1,1,1,1,//270
		      0,1,1,1,1,1,1,1,1,1,//280
		      1,1,1,0,0,0,0,0,0,0};//290

  //Get Cuts
  cut_ar38_e1x = (TCutG *) gDirectory->FindObjectAny("cut_ar38_e1x");
  cut_ar38_dtge = (TCutG *) gDirectory->FindObjectAny("cut_ar38_dtge");
  cut_ar38_e1e3 = (TCutG *) gDirectory->FindObjectAny("cut_ar38_e1e3");
  cut_ar38_e1e2 = (TCutG *) gDirectory->FindObjectAny("cut_ar38_e1e2");
  cut_ar38_e2e3 = (TCutG *) gDirectory->FindObjectAny("cut_ar38_e2e3");
  cut_cl38_e1x = (TCutG *) gDirectory->FindObjectAny("cut_cl38_e1x");
  cut_cl38_dtge = (TCutG *) gDirectory->FindObjectAny("cut_cl38_dtge");
  cut_cl38_e1e3 = (TCutG *) gDirectory->FindObjectAny("cut_cl38_e1e3");
  cut_cl38_e1e2 = (TCutG *) gDirectory->FindObjectAny("cut_cl38_e1e2");
  cut_cl38_e2e3 = (TCutG *) gDirectory->FindObjectAny("cut_cl38_e2e3");
  cut_s38_e1x = (TCutG *) gDirectory->FindObjectAny("cut_s38_e1x");
  cut_s38_dtge = (TCutG *) gDirectory->FindObjectAny("cut_s38_dtge");
  cut_s38_e1e3 = (TCutG *) gDirectory->FindObjectAny("cut_s38_e1e3");
  cut_s38_e1e2 = (TCutG *) gDirectory->FindObjectAny("cut_s38_e1e2");
  cut_s38_e2e3 = (TCutG *) gDirectory->FindObjectAny("cut_s38_e2e3");
  all_z_e1e3 = (TCutG *) gDirectory->FindObjectAny("all_z_e1e3");
  all_aq_e0x = (TCutG *) gDirectory->FindObjectAny("all_aq_e0x");
  
   for (Int_t index=lowRunNumber;index<=highRunNumber;index++) {
    runN=index;
    if (goodRun[runN]==1) {
    printf("Starting sort of run number: %d\n",runN);
  TFile * fNameIn = new TFile(Form("/lcrc/project/HELIOS/gretinafma/root_data/run%d.root",runN));

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

  TFile * calFile = new TFile(Form("/lcrc/project/HELIOS/gretinafma/root_data/cal_%d.root",runN),"RECREATE");
  TTree * ctree = new TTree("ctree", "Cal Tree");

  Int_t run;
  Int_t hits;
  Float_t l,r,u,d,x,y;
  Float_t e[10];
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
  ctree->Branch("e",e,"e[10]/F");
  //Gammas - a bunch more to add...
  ctree->Branch("gmult",&gmult,"gmult/I");
  ctree->Branch("genergy",genergy,"genergy[gmult]/F");
  ctree->Branch("dtime",dtime,"dtime[gmult]/F");
  //Gamma breakdown
  ctree->Branch("gebMult",&gebMult,"gebMult/I");
  //ctree->Branch("crysType",crysType,"crysType[gebMult]/I"); //leaving out for now
  ctree->Branch("crysId",crysId,"crysId[gebMult]/I");
  ctree->Branch("crysNum",crysNum,"crysNum[gebMult]/I");
  ctree->Branch("crysTot_e",crysTot_e,"crysTot_e[gebMult]/F");
  //ctree->Branch("crysTimestamp",crysTimestamp,"crysTimestamp[gebMult]/L");
  //ctree->Branch("crysTrigtime",crysTrigtime,"crysTrigtime[gebMult]/D");
  ctree->Branch("crysT0",crysT0,"crysT0[gebMult]/F");
  //ctree->Branch("crysCfd",crysCfd,"crysCfd[gebMult]/F");
  //ctree->Branch("crysChisq",crysChisq,"crysChisq[gebMult]/F");
  //ctree->Branch("crysNormChisq",crysNormChisq,"crysNormChisq[gebMult]/F");
  //ctree->Branch("crysBaseline",crysBaseline,"crysBaseline[gebMult]/F");
  //ctree->Branch("crysTpad",crysTpad,"crysTpad[gebMult]/i");
  ctree->Branch("crysPolAngle",crysPolAngle,"crysPolAngle[gebMult]/F");
  ctree->Branch("intMaxX",intMaxX,"intMaxX[gebMult]/F");
  ctree->Branch("intMaxY",intMaxY,"intMaxY[gebMult]/F");
  ctree->Branch("intMaxZ",intMaxZ,"intMaxZ[gebMult]/F");
  ctree->Branch("intMaxE",intMaxE,"intMaxE[gebMult]/F");
  ctree->Branch("intMaxSeg",intMaxSeg,"intMaxSeg[gebMult]/I");
  ctree->Branch("intMaxSegE",intMaxSegE,"intMaxSegE[gebMult]/F");


  
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

  for (Int_t i=0;i<3;i++) {
  printf("Det: %d, Offset: %4.4f, Linear: %4.4f, XOffset: %4.4f\n",
	 detIndexRead,
	 calibrationOffset[runN][i],
	 calibrationLinear[runN][i],
	 calibrationXOffset[runN][i]);
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

    e[3] = e[0]+e[1];
    e[4] = e[0]+e[2];
    e[5] = e[1]+e[2];
    e[6] = e[0]+e[1]+e[2];
    
    gmult = gammaMult;
    for (Int_t i=0;i<gmult;i++) {
      genergy[i] = gammaEnergy[i];
      dtime[i] = deltaTime[i];
    }

     if (entryNumber<1)
      printf("entryNumber:%d \n l:%4.0f r:%4.0f u:%4.0f d:%4.0f \n x:%4.0f y:%4.0f\n e1:%4.2f e2:%4.2f e3:%4.2f gammaMult:%d gammaEnergy[0]:%4.1f\n\n",
	     entryNumber,l,r,u,d,x,y,e[0],e[1],e[2],gammaMult,gammaEnergy[0]);
     
     //Should setup a few of the basic cuts here to limit file size / save time later.
     //     if ( cut_ar38_e1x->IsInside(x,e[0]) || /* basic eVx cut first */
     //	  cut_cl38_e1x->IsInside(x,e[0]) ||
     //	  cut_s38_e1x->IsInside(x,e[0])) {
     if ( all_aq_e0x->IsInside(x,e[0])
	  && all_z_e1e3->IsInside(e[2],e[0]) ) {
       ctree->Fill();
     }
     
  } //entryNumber Loop
  ctree->Write();
  calFile->Close();
  //printf("Run Number: %d\n",runNumber);
  /* printf("left: %f\n",left[0]); */
    }
   }
   
}
   
