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

void fmaMain(Int_t runNumber=0){
  
  int option;
  printf(" ========= fmaMain ============== \n");
  printf(" ================================ \n");
  printf(" ---- GEBSort -> runXXX.root-----  \n");
  printf(" ================================ \n");
  //printf(" 0 = XXX \n");
  printf(" 1 = draw ic spectra   \n");
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
    
    fileName.Form("/Users/calemhoffman/Research/anl/gretinafma/data/root_data/run%d.root",runNumber);
    chain->Add(fileName);
    chain->GetListOfFiles()->Print();
    
    fmaDraw(chain);
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

      for (Int_t runNumberIndex=99;runNumberIndex<295;runNumberIndex++) {
	runNumber=runNumberIndex;
	chain = new TChain("tree");
	fileName.Form("/Users/calemhoffman/Research/anl/gretinafma/data/root_data/run%d.root",runNumber);
	chain->Add(fileName);
	chain->GetListOfFiles()->Print();
	fmaFit(chain,runNumber,fitFileOut);
      }
    }

    fflush(fitFileOut);
    fclose(fitFileOut);
  }

    
  if( option == 3 ) fmaCalibrate();

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
