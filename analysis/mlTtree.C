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
#include <sys/utsname.h>

//does this automagically now
Int_t LCRC=1; //0 local, 1 lcrc

struct utsname sysinfo;

TChain *chain;
TString fileName;
Int_t goodRun[30] =
	{0,0,0,0,0,
 	0,0,1,0,0, //7 only
 	0,0,0,0,0,
 	0,0,0,0,0,
 	0,0,0,0,0,
 	0,0,0,0,0};
 // {0,0,0,0,0,
 // 0,0,1,1,1,
 // 1,1,1,1,1,
 // 1,1,1,0,1,
 // 1,1,1,1,1,
 // 1,1,1,1,1};
TCanvas *c2;

//list stuff
TEventList * elist_mlTtree;
Int_t eventListYN=0;//is there a list?

//New TTree Stuff
TTree * mltree;
Int_t recoilID=10;
TString recoilName[10];

Int_t run;
Int_t hits;
Float_t l,r,u,d,x,y;
Float_t e[10];
Float_t e1,e2,e3,e12,e13,e23,e123;
Int_t gmult;
Float_t genergy[100];
Float_t dtime[100];
Int_t gtime[100][100];

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

//Cuts for histos
TCutG *all_z_e1e3,*all_aq_e0x,*all_tof_dtge;
TCutG *cut_ar38_dtge;
TCutG *cut_ar38_g600,*cut_ar38_g1600,*cut_ar38_g1800,*cut_ar38_g2100;
TCutG *cut_cl38_dtge;
TCutG *cut_cl38_g200,*cut_cl38_g700,*cut_cl38_g1100,*cut_cl38_g2600,*cut_cl38_g3100;
TCutG *cut_s38_dtge;
TCutG *cut_s38_g1200,*cut_s38_g1500,*cut_s38_g800;
TCutG *cut_p33_g1400,*cut_p33_g1800,*cut_p33_g2300;
//finals
TCutG *cut_e1e3_s38,*cut_e0x_s38,*cut_lr_s38,*cut_ud_s38,*cut_dtge_s38;
TCutG *cut_e1e3_cl38,*cut_e0x_cl38,*cut_lr_cl38,*cut_ud_cl38,*cut_dtge_cl38;
TCutG *cut_e1e3_ar38,*cut_e0x_ar38,*cut_lr_ar38,*cut_ud_ar38,*cut_dtge_ar38;
TCutG *cut_e1e3_p33,*cut_e0x_p33,*cut_lr_p33,*cut_ud_p33,*cut_dtge_p33;
//Histos
TH2F *he0x,*he1e3;
TH2F *hdtge,*hlr,*hud;

TH1F *hg_tot;
TH1F *hg_ar38; TH1F *hg_cl38;
TH1F * hg_p33; TH1F *hg_s38;

/* main */
void mlTtree(void) {
	uname(&sysinfo);
	TString lcrcCheck("Darwin");
	if (sysinfo.sysname == lcrcCheck) LCRC=0;
	printf("%s: %d\n",sysinfo.sysname,LCRC);
  //TwoChains!
  chain = new TChain("ctree");
  for (Int_t rn = 7; rn<30; rn++) {
    if (goodRun[rn]==1) {
			if (LCRC == 1) {
				fileName.Form("/lcrc/project/HELIOS/gretinafma/root_data/cal_%d.root",rn);
			} else {
				fileName.Form("/Users/calemhoffman/Research/anl/gretinafma/data/root_data/cal_%d.root",rn);
			}
			chain->Add(fileName);
    }
  }
  chain->GetListOfFiles()->Print();
  //Listomania - need to see if list exists then get events accordingly
  TFile *listFile = new TFile("eventLists.root");
	Int_t numElistEntries=0;
	if (listFile) {
  	listFile->GetObject("elist_mlTtree",elist_mlTtree);
		if (elist_mlTtree) {
			eventListYN=1;
  		numElistEntries = elist_mlTtree->GetN();
  		printf("Number of ElistEntries: %d \n",numElistEntries);
		}
	}

	gDirectory->pwd();
  gROOT->cd();
  gDirectory->pwd();

  //General cuts, already applied if with eventList (some in calTree as well).
  all_z_e1e3 = (TCutG *) gDirectory->FindObjectAny("all_z_e1e3");
  all_aq_e0x = (TCutG *) gDirectory->FindObjectAny("all_aq_e0x");
  all_tof_dtge = (TCutG *) gDirectory->FindObjectAny("all_tof_dtge");
  //AR
  cut_dtge_ar38 = (TCutG *) gDirectory->FindObjectAny("cut_dtge_ar38");
  cut_e1e3_ar38 = (TCutG *) gDirectory->FindObjectAny("cut_e1e3_ar38");
  cut_e0x_ar38 = (TCutG *) gDirectory->FindObjectAny("cut_e0x_ar38");
  cut_lr_ar38 = (TCutG *) gDirectory->FindObjectAny("cut_lr_ar38");
  cut_ud_ar38 = (TCutG *) gDirectory->FindObjectAny("cut_ud_ar38");
  cut_ar38_g600 = (TCutG *) gDirectory->FindObjectAny("cut_ar38_g600");
  cut_ar38_g1600 = (TCutG *) gDirectory->FindObjectAny("cut_ar38_g1600");
  cut_ar38_g1800 = (TCutG *) gDirectory->FindObjectAny("cut_ar38_g1800");
  cut_ar38_g2100 = (TCutG *) gDirectory->FindObjectAny("cut_ar38_g2100");
  //CL
  cut_dtge_cl38 = (TCutG *) gDirectory->FindObjectAny("cut_dtge_cl38");
  cut_e1e3_cl38 = (TCutG *) gDirectory->FindObjectAny("cut_e1e3_cl38");
  cut_e0x_cl38 = (TCutG *) gDirectory->FindObjectAny("cut_e0x_cl38");
  cut_lr_cl38 = (TCutG *) gDirectory->FindObjectAny("cut_lr_cl38");
  cut_ud_cl38 = (TCutG *) gDirectory->FindObjectAny("cut_ud_cl38");
  cut_cl38_g200 = (TCutG *) gDirectory->FindObjectAny("cut_cl38_g200");
  cut_cl38_g700 = (TCutG *) gDirectory->FindObjectAny("cut_cl38_g700");
  cut_cl38_g1100 = (TCutG *) gDirectory->FindObjectAny("cut_cl38_g1100");
  cut_cl38_g2600 = (TCutG *) gDirectory->FindObjectAny("cut_cl38_g2600");
  cut_cl38_g3100 = (TCutG *) gDirectory->FindObjectAny("cut_cl38_g3100");
  //S
  cut_dtge_s38 = (TCutG *) gDirectory->FindObjectAny("cut_dtge_s38");
  cut_e1e3_s38 = (TCutG *) gDirectory->FindObjectAny("cut_e1e3_s38");
  cut_e0x_s38 = (TCutG *) gDirectory->FindObjectAny("cut_e0x_s38");
  cut_lr_s38 = (TCutG *) gDirectory->FindObjectAny("cut_lr_s38");
  cut_ud_s38 = (TCutG *) gDirectory->FindObjectAny("cut_ud_s38");
  cut_s38_g1200 = (TCutG *) gDirectory->FindObjectAny("cut_s38_g1200");
  cut_s38_g1500 = (TCutG *) gDirectory->FindObjectAny("cut_s38_g1500");
  cut_s38_g800 = (TCutG *) gDirectory->FindObjectAny("cut_s38_g800");
  //P33
  cut_p33_g1400 = (TCutG *) gDirectory->FindObjectAny("cut_p33_g1400");
  cut_p33_g1800 = (TCutG *) gDirectory->FindObjectAny("cut_p33_g1800");
  cut_p33_g2300 = (TCutG *) gDirectory->FindObjectAny("cut_p33_g2300");
  cut_dtge_p33 = (TCutG *) gDirectory->FindObjectAny("cut_dtge_p33");
  cut_e1e3_p33 = (TCutG *) gDirectory->FindObjectAny("cut_e1e3_p33");
  cut_e0x_p33 = (TCutG *) gDirectory->FindObjectAny("cut_e0x_p33");
  cut_lr_p33 = (TCutG *) gDirectory->FindObjectAny("cut_lr_p33");
  cut_ud_p33 = (TCutG *) gDirectory->FindObjectAny("cut_ud_p33");

  TFile * mlFile = new TFile("mlTree.root","RECREATE");
  mltree = new TTree(Form("mltree"),Form("ML Tree"));
  mltree->Branch("l",&l,"l/F");
  mltree->Branch("r",&r,"r/F");
  mltree->Branch("u",&u,"u/F");
  mltree->Branch("d",&d,"d/F");
  mltree->Branch("x",&x,"x/F");
  mltree->Branch("y",&y,"y/F");
	mltree->Branch("e",e,"e[10]/F");
  mltree->Branch("e1",&e1,"e1/F");
	mltree->Branch("e2",&e2,"e2/F");
	mltree->Branch("e3",&e3,"e3/F");
	mltree->Branch("e12",&e12,"e12/F");
	mltree->Branch("e13",&e13,"e13/F");
	mltree->Branch("e23",&e23,"e23/F");
	mltree->Branch("e123",&e123,"e123/F");
	mltree->Branch("recoilID",&recoilID,"recoilID/I");
  mltree->Branch("gmult",&gmult,"gmult/I");
  mltree->Branch("genergy",genergy,"genergy[gmult]/F");
  mltree->Branch("dtime",dtime,"dtime[gmult]/F");
	mltree->Branch("gtime",gtime,"gtime[gmult][100]/I");

  chain->SetBranchAddress("run", &run);
  chain->SetBranchAddress("hits",&hits);
  chain->SetBranchAddress("l",&l);
  chain->SetBranchAddress("r",&r);
  chain->SetBranchAddress("u",&u);
  chain->SetBranchAddress("d",&d);
  chain->SetBranchAddress("x",&x);
  chain->SetBranchAddress("y",&y);
  chain->SetBranchAddress("e",e);
  chain->SetBranchAddress("gmult",&gmult);
  chain->SetBranchAddress("genergy",genergy);
  chain->SetBranchAddress("dtime",dtime);
	chain->SetBranchAddress("gtime",gtime);
  chain->SetBranchAddress("gebMult",&gebMult);
  chain->SetBranchAddress("crysId",crysId);
  chain->SetBranchAddress("crysNum",crysNum);
  chain->SetBranchAddress("crysTot_e",crysTot_e);
  chain->SetBranchAddress("crysT0",crysT0);
  chain->SetBranchAddress("crysPolAngle",crysPolAngle);
  chain->SetBranchAddress("intMaxX",intMaxX);
  chain->SetBranchAddress("intMaxY",intMaxY);
  chain->SetBranchAddress("intMaxZ",intMaxZ);
  chain->SetBranchAddress("intMaxE",intMaxE);
  chain->SetBranchAddress("intMaxSeg",intMaxSeg);
  chain->SetBranchAddress("intMaxSegE",intMaxSegE);

  //histograms define
  he0x = new TH2F("he0x","he0x; e0; x",1500,-1000,500,1000,0,3000);
  he1e3 = new TH2F("he1e3","he1e3; e3; e1",1000,0,3000,1000,0,3000);
  hdtge = new TH2F("hdtge","hdtge; dt; ge",10000,0,10000,75,0,150);
  hlr = new TH2F("hlr","hlr; l; r",1000,0,4000,1000,0,4000);
  hud = new TH2F("hud","hud; u; d",1000,0,4000,1000,0,4000);

  Int_t ch=6000;
  Int_t rg=ch;
  hg_tot = new TH1F("hg_tot","Ungated hg_tot; Energy [keV]",ch,0,rg);
  hg_p33 = new TH1F("hg_p33","hg_p33; Energy [keV]",ch,0,rg);
  hg_ar38 = new TH1F("hg_ar38","hg_ar38; Energy [keV]",ch,0,rg);
  hg_cl38 = new TH1F("hg_cl38","hg_cl38; Energy [keV]",ch,0,rg);
  hg_s38 = new TH1F("hg_s38","hg_s38; Energy [keV]",ch,0,rg);

  Int_t nEntries = chain->GetEntries();
  printf("nEntries: %d\n",nEntries);
  Float_t counter=0;
	Int_t numEntries=0;

	if (eventListYN==1) {
		numEntries = numElistEntries;
		printf("***Using an eventList\n");
	} else {
		numEntries = nEntries;
		printf("***No Event Lists");
	}

  for (Int_t entryNumber=0;entryNumber<numEntries; entryNumber++) {
		if (eventListYN==1) {
    	chain->GetEntry(elist_mlTtree->GetEntry(entryNumber));
		} else {
			chain->GetEntry(entryNumber);
		}
    if (((Float_t)entryNumber/(Float_t)numEntries)>counter) {
			printf("^_^_^_%4.1f_^_^_^%4.0f\n",counter*100,(Float_t)entryNumber);
			counter=counter+0.1;
    }
		//Pass the e's
		e1=e[0]; e2=e[1]; e3=e[2]; e12=e[3]; e13=e[4]; e23=e[5]; e123=e[6];
    recoilID=10;
  	/* s38 */
  	if ( (cut_e1e3_s38->IsInside(e[2],e[0]))
 		&& (cut_e0x_s38->IsInside(x,e[0]))
 		&& (cut_lr_s38->IsInside(r,l))
 		&& (cut_ud_s38->IsInside(d,u)) ) {
    	recoilID=0;
			mltree->Fill();
    	/* for (Int_t gMult=0;gMult< gmult; gMult++) { */
    	/* 	if ( (cut_dtge_s38->IsInside(genergy[gMult],dtime[gMult])) ) { */
    	/* 	  // hdtge->Fill(genergy[gMult],dtime[gMult]); */
    	/* 	  hg_s38->Fill(genergy[gMult]); */
    	/* 	} */
    	/* } */
  	}
  	/* cl38 */
  	if ( (cut_e1e3_cl38->IsInside(e[2],e[0]))
 		&& (cut_e0x_cl38->IsInside(x,e[0]))
 		&& (cut_lr_cl38->IsInside(r,l))
 		&& (cut_ud_cl38->IsInside(d,u)) ) {
    	recoilID=1;
			mltree->Fill();
      /* for (Int_t gMult=0;gMult< gmult; gMult++) { */
      /* 	if ( (cut_dtge_cl38->IsInside(genergy[gMult],dtime[gMult])) ) { */
      /* 	  // hdtge->Fill(genergy[gMult],dtime[gMult]); */
      /* 	  hg_cl38->Fill(genergy[gMult]); */
      /* 	  } */
      /* } */
  	} /* cl38 */
 		/* ar38 */
  	if ( (cut_e1e3_ar38->IsInside(e[2],e[0]))
 		&& (cut_e0x_ar38->IsInside(x,e[0]))
 		&& (cut_lr_ar38->IsInside(r,l))
 		&& (cut_ud_ar38->IsInside(d,u)) ) {
      recoilID=2;
			mltree->Fill();
      /* for (Int_t gMult=0;gMult< gmult; gMult++) { */
      /* 	if ( (cut_dtge_ar38->IsInside(genergy[gMult],dtime[gMult])) ) { */
      /* 	  //hdtge->Fill(genergy[gMult],dtime[gMult]); */
      /* 	  hg_ar38->Fill(genergy[gMult]); */
      /* 	} */
      /* } */
  	} /* ar38 */
  	/* p33 */
  	if ( (cut_e1e3_p33->IsInside(e[2],e[0]))
 		&& (cut_e0x_p33->IsInside(x,e[0]))
 		&& (cut_lr_p33->IsInside(r,l))
 		&& (cut_ud_p33->IsInside(d,u)) ) {
    	recoilID=3;
			mltree->Fill();
      /* for (Int_t gMult=0;gMult< gmult; gMult++) { */
      /* 	if ( (cut_dtge_p33->IsInside(genergy[gMult],dtime[gMult])) ) { */
      /* 	  //hdtge->Fill(genergy[gMult],dtime[gMult]); */
      /* 	  hg_p33->Fill(genergy[gMult]); */
      /* 	} */
      /* } */
  	} /* p33 */
		if (recoilID==10) mltree->Fill();
  }//end entry loop
  //cleanup
  //  for (Int_t i=0;i<4;i++)
  mltree->Write();
  mlFile->Close();
}
