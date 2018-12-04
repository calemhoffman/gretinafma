#include <TROOT.h>
#include <TChain.h>
#include <TTree.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TStyle.h>
#include <TH2F.h>
#include <TH1F.h>
#include <TF1.h>
#include <TMath.h>
#include <TSpectrum.h>
#include <TGraph.h>
#include <fstream>
#include <TProof.h>

#include "fmaDraw.C"
#include "fmaFit.C"
#include "fmaCalibrate.C"

///define globals....
//gROOT or gSystem FindObjAny("name")
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

void fmaMain(Int_t runNumber=0){
  
  int option;
  printf(" ========= fmaMain ============== \n");
  printf(" ================================ \n");
  printf(" ---- GEBSort -> runXXX.root-----  \n");
  printf(" ================================ \n");
  //printf(" 0 = XXX \n");
  printf(" 1 = draw ic spectra (& cuts)  \n");
  printf(" 2 = fit ic spectra    \n");
  printf(" ================================ \n");
  printf(" ===requires fma_fits.dat file=== \n");
  printf(" 3 = calibrate ic spectra    \n");
  printf(" ================================ \n");
  printf(" Choose action : ");
  int temp = scanf("%d", &option);

  //==================================================== data files
  TChain * chain = new TChain("tree");
  TString fileName;
  
  if ( option == 1 ) {
    if (runNumber==0) {
      printf(" ================ enter run number:  \n");
      int tempRunNumber = scanf("%d", &runNumber);
    }
    
    fileName.Form("/Users/calemhoffman/Research/anl/gretinafma/data/root_data/devel/run%d.root",runNumber);
    chain->Add(fileName);
    chain->GetListOfFiles()->Print();
    
    fmaDraw(chain,runNumber);
    printf(" ================================== \n");
  }
    
  if( option == 2 ) {
    FILE * fitFileOut;
    fitFileOut = fopen ("fma_fits.dat", "w+");
    if (runNumber!=0) {
      fileName.Form("/Users/calemhoffman/Research/anl/gretinafma/data/root_data/run%d.root",runNumber);
      chain->Add(fileName);
      chain->GetListOfFiles()->Print();
      fmaFit(chain,runNumber,fitFileOut);
    } else {

      for (Int_t runNumberIndex=50;runNumberIndex<300;runNumberIndex++) {
	runNumber=runNumberIndex;
	if (goodRun[runNumber]!=0) {
	  chain = new TChain("tree");
	  fileName.Form("/Users/calemhoffman/Research/anl/gretinafma/data/root_data/run%d.root",runNumber);
	  chain->Add(fileName);
	  chain->GetListOfFiles()->Print();
	  fmaFit(chain,runNumber,fitFileOut);
	}
      }
      
    }

    fflush(fitFileOut);
    fclose(fitFileOut);
  }

    
  if( option == 3 ) {
    FILE * calFileOut;
    calFileOut = fopen ("fma_cal.dat", "w+");
    fmaCalibrate(calFileOut);

    fflush(calFileOut);
    fclose(calFileOut);
  }
  /*
   TString rootfileSim="transfer.root";
      
   if( option == 2 ) {
      printf("=============== creating smaller tree.\n");
      chain->Process("../AutoCali/Cali_littleTree_trace.C+");
      Check_e_x("temp.root", eThreshold);
   }
   
   if( option == 3 ) {
      int det = -1; 
      printf(" Choose detID (-1 for all): ");
      temp = scanf("%d", &det);
      if( det > -1 ){
         GetCoinTimeCorrectionCutG("temp.root", det);
      }else{
         for(int iDet = 0; iDet < 24; iDet ++){
            GetCoinTimeCorrectionCutG("temp.root", iDet);
         }
      }
      gROOT->ProcessLine(".q");
   }
   
   if( option == 4 ) {
      TFile *caliFile = new TFile ("temp.root", "read");
      if( !caliFile->IsOpen() ){
			printf("!!!!!!!!!!! no temp.root, please run step 2.!!!!!!!\n");
			return;
		}
      TTree * caliTree = (TTree*) caliFile->Get("tree");
      
      TFile *fs = new TFile (rootfileSim, "read"); 
      
      if(fs->IsOpen()){
         
         int eCdet = -1; 
         printf(" Choose detID (-1 for all & make new root): ");
         temp = scanf("%d", &eCdet);
         Cali_compareF(caliTree, fs, eCdet, eThreshold);
         
         if( eCdet == -1) {
            chain->Process("../AutoCali/Cali_e_trace.C+");
            gROOT->ProcessLine(".q");
         }
      }else{
         printf("!!!!! cannot open transfer.root !!!!! \n");
         return;
      }
   }
   
   if( option == 5 ) {
      chain->Process("../AutoCali/Cali_e_trace.C+");
      
   }
  */
}
