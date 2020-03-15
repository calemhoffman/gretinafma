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

Int_t WriteYN = 0;

//Need files and histograms

void gamGam() {
  // Int_t lowRunNumber=50;
  // Int_t highRunNumber=295;
  Int_t lowRunNumber=100;
  Int_t highRunNumber=101;
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
  Int_t gDeltaTime[100][100];
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
	  	tree->SetBranchAddress("tac",tac);
	  	tree->SetBranchAddress("fmaDeltaTime",fmaDeltaTime);
	  	tree->SetBranchAddress("fmaMult",fmaMult);
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

	  	TFile * ggFile = new TFile(Form("/lcrc/project/HELIOS/gretinafma/root_data/gg_%d.root",runN),"RECREATE");
	  	TTree * ggtree = new TTree("ggtree", "Gamma-Gamma Tree");

	  	Int_t run;
	  	Int_t hits;
	  	Float_t l,r,u,d,x,y;
	  	Float_t e[10];
	  	Int_t gmult;
	  	Float_t genergy[100];
	  	Float_t dtime[100];
	  	Int_t gtime[100][100];

		  //Generic
		  ggtree->Branch("run", &run, "run/I");
		  ggtree->Branch("hits",&hits,"hits/I");
		  //Positions
		  ggtree->Branch("l",&l,"l/F");
		  ggtree->Branch("r",&r,"r/F");
		  ggtree->Branch("u",&u,"u/F");
		  ggtree->Branch("d",&d,"d/F");
		  ggtree->Branch("x",&x,"x/F");
		  ggtree->Branch("y",&y,"y/F");
		  //Energies
		  ggtree->Branch("e",e,"e[10]/F");
		  //Gammas - a bunch more to add...
		  ggtree->Branch("gmult",&gmult,"gmult/I");
		  ggtree->Branch("genergy",genergy,"genergy[gmult]/F");
		  ggtree->Branch("dtime",dtime,"dtime[gmult]/F");
		  ggtree->Branch("gtime",gtime,"gtime[gmult][100]/I");
		  //Gamma breakdown
		  ggtree->Branch("gebMult",&gebMult,"gebMult/I");
		  //ggtree->Branch("crysType",crysType,"crysType[gebMult]/I"); //leaving out for now
		  ggtree->Branch("crysId",crysId,"crysId[gebMult]/I");
		  ggtree->Branch("crysNum",crysNum,"crysNum[gebMult]/I");
		  ggtree->Branch("crysTot_e",crysTot_e,"crysTot_e[gebMult]/F");
		  //ggtree->Branch("crysTimestamp",crysTimestamp,"crysTimestamp[gebMult]/L");
		  //ggtree->Branch("crysTrigtime",crysTrigtime,"crysTrigtime[gebMult]/D");
		  ggtree->Branch("crysT0",crysT0,"crysT0[gebMult]/F");
		  //ggtree->Branch("crysCfd",crysCfd,"crysCfd[gebMult]/F");
		  //ggtree->Branch("crysChisq",crysChisq,"crysChisq[gebMult]/F");
		  //ggtree->Branch("crysNormChisq",crysNormChisq,"crysNormChisq[gebMult]/F");
		  //ggtree->Branch("crysBaseline",crysBaseline,"crysBaseline[gebMult]/F");
		  //ggtree->Branch("crysTpad",crysTpad,"crysTpad[gebMult]/i");
		  ggtree->Branch("crysPolAngle",crysPolAngle,"crysPolAngle[gebMult]/F");
		  ggtree->Branch("intMaxX",intMaxX,"intMaxX[gebMult]/F");
		  ggtree->Branch("intMaxY",intMaxY,"intMaxY[gebMult]/F");
		  ggtree->Branch("intMaxZ",intMaxZ,"intMaxZ[gebMult]/F");
		  ggtree->Branch("intMaxE",intMaxE,"intMaxE[gebMult]/F");
		  ggtree->Branch("intMaxSeg",intMaxSeg,"intMaxSeg[gebMult]/I");
		  ggtree->Branch("intMaxSegE",intMaxSegE,"intMaxSegE[gebMult]/F");

			//User Ins
			//Int_t nTreeNum = 0; //only for s38 to start
			Float_t beta = 0.03375; //s38 from Fits

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

	  	for (Int_t entryNumber=0;entryNumber<=nEntries; entryNumber++) {
	    	tree->GetEntry(entryNumber);
				if (gebMult > 1) { //no need to move forward if not mult of 2 or greater
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
					  hEventType->Fill(1);
					  if (crysTotE[gebMultNum]>0) hEventType->Fill(2);
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
					      hEventType->Fill(3);
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
					          hEventType->Fill(4);
					          crysTotAdd2Back[gebMultNum] += crysTot_e[k];
					          //crysTot_e[k] = 0;
					        }//radDiff if
					      }// k++
					   	} //radDiff if
					  } //j++
			      crysTotAddBack[gebMultNum] = crysTotAddBack[gebMultNum]/modCCdopfac[gebMultNum];
			      crysTotAdd2Back[gebMultNum] = crysTotAdd2Back[gebMultNum]/modCCdopfac[gebMultNum];//[addBackDopNum];
					} //gebMultNum

					//Loop over segment multiplicity for histofill
					for (Int_t gebMultNum=0; gebMultNum < gebMult; gebMultNum++) {
            hg->Fill(genergy[gebMultNum]); //g fill
            hgDop->Fill(crysTotDop[gebMultNum]); //dop fill
            if (crysTotAddBack[gebMultNum] > 0) {
              if ((modCCang[gebMultNum]*180./TMath::Pi())>60.0 && (modCCang[gebMultNum]*180./TMath::Pi())<180.0) {
              	hgAddBack->Fill(crysTotAddBack[gebMultNum]); //ab fill
              }
            }
            if (crysTotAdd2Back[gebMultNum] > 0) {
              if ((modCCang[gebMultNum]*180./TMath::Pi())>60.0 && (modCCang[gebMultNum]*180./TMath::Pi())<180.0) {
                hgAdd2Back->Fill(crysTotAdd2Back[gebMultNum]); //a2b fill
              }
            }
            hgNoDopVsAngle->Fill(crysTotE[gebMultNum],modCCang[gebMultNum]*180./TMath::Pi());
            hgDopVsAngle->Fill(crysTotAddBack[gebMultNum],
            modCCang[gebMultNum]*180./TMath::Pi());
            for (Int_t iMult=gebMultNum+1; iMult<gebMult; iMult++) {
              if (gtime[gebMultNum][iMult]<40) {
                hgg->Fill(genergy[gebMultNum],genergy[iMult]);
                hgg->Fill(genergy[iMult],genergy[gebMultNum]);
                hggDop->Fill(crysTotDop[gebMultNum],crysTotDop[iMult]);
                hggDop->Fill(crysTotDop[iMult],crysTotDop[gebMultNum]);
                if (crysTotAddBack[gebMultNum] > 0 && crysTotAddBack[iMult] > 0) {
                  if ((modCCang[gebMultNum]*180./TMath::Pi())>60.0 && (modCCang[gebMultNum]*180./TMath::Pi())<180.0) {
                    hggAddBack->Fill(crysTotAddBack[gebMultNum],crysTotAddBack[iMult]);
                    hggAddBack->Fill(crysTotAddBack[iMult],crysTotAddBack[gebMultNum]);
                  }
                }
              }//gtime if
            }//gg fill
  				}//gebMultNum - fills


		     	if (entryNumber<1)
		      	printf("entryNumber:%d \n gammaMult:%d gammaEnergy[0]:%4.1f\n\n",
			     	entryNumber,gammaMult,gammaEnergy[0]);

		     	//Should setup a few of the basic cuts here to limit file size / save time later.
		    	if ( WriteYN == 1 ) {
		       ggtree->Fill();
		     	}

				} //gmult > 1
	  	} //entryNumber Loop
	  	ggtree->Write();
	  	ggFile->Close();
		} //if for which runs to include
	} //loop over runs
} //end of ends
