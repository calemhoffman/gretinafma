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

TFile * lNameIn;
TFile * fNameIn;
TEventList * all_elist_x;
TEventList * elist;
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

void fmaCuts(void) {
  TBenchmark gClock;  
  gClock.Reset(); gClock.Start("gTimer");
 
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
  
  Int_t runN=7;

  Int_t run;
  Int_t hits;
  Float_t l,r,u,d,x,y;
  Float_t e[10];
  Int_t gmult;
  Float_t genergy[100];
  Float_t dtime[100];

   //Get List
  lNameIn = new TFile("eventLists.root");
  lNameIn->GetObject("all_elist_x",all_elist_x); 
  Int_t nElistEntry = all_elist_x->GetN(); 
  printf("nElistEntry: %d ",nElistEntry);

  fNameIn = new TFile(Form("/Users/calemhoffman/Research/anl/gretinafma/gretinafma_git/analysis/cal_%d.root",runN));
  if (fNameIn == 0) {printf("Error: file read in fail\n"); return;}
  TTree * ctree = (TTree *) fNameIn->Get("ctree");

  //Generic
  ctree->SetBranchAddress("run", &run);
  ctree->SetBranchAddress("hits",&hits);
  //Positions
  ctree->SetBranchAddress("l",&l);
  ctree->SetBranchAddress("r",&r);
  ctree->SetBranchAddress("u",&u);
  ctree->SetBranchAddress("d",&d);
  ctree->SetBranchAddress("x",&x);
  ctree->SetBranchAddress("y",&y);
  //Energies
  ctree->SetBranchAddress("e",e);
  //Gammas
  ctree->SetBranchAddress("gmult",&gmult);
  ctree->SetBranchAddress("genergy",genergy);
  ctree->SetBranchAddress("dtime",dtime);

  //----------- generate the histograms --------//
  //Need - all params vs. egamma
  //varios egammas
  //dtegamma vs mult
  //e's vs x
  //l,r,u,d stuff??

  //single gammas
  TH1F *hg_tot; TH1F *hg_ar38; TH1F *hg_cl38; TH1F *hg_s38;
  TH1F *hg_x; TH1F *hg_z; TH1F *hg_t;

  //histos for gamma scans
  TH1F *hscan[1000];
  
  TH2F *he1e2; TH2F *he1e3; TH2F *he2e3;
  TH2F *he1e12; TH2F *he1e13; TH2F *he2e13;
  TH2F *he1e123; TH2F *he2e123; TH2F *he3e123;
  TH2F *he12e123; TH2F *he23e123; TH2F *he13e123;

  //gg
  TH2F *hgg_ar38; TH2F *hgg_cl38; TH2F *hgg_s38;

  Int_t ch = 8000;
  Int_t rg = 8000;

  hg_tot = new TH1F("hg_tot","Ungated hg_tot; Energy [keV]",ch,0,rg);
  hg_x = new TH1F("hg_x","Ungated hg_x; Energy [keV]",ch,0,rg);
  hg_z = new TH1F("hg_z","Ungated hg_z; Energy [keV]",ch,0,rg);
  hg_t = new TH1F("hg_t","Ungated hg_t; Energy [keV]",ch,0,rg);
  hg_ar38 = new TH1F("hg_ar38","Ungated hg_ar38; Energy [keV]",ch,0,rg);
  hg_cl38 = new TH1F("hg_cl38","Ungated hg_cl38; Energy [keV]",ch,0,rg);
  hg_s38 = new TH1F("hg_s38","Ungated hg_s38; Energy [keV]",ch,0,rg);

  ch=4000;
  rg=4000;
  
  for (Int_t id1=0;id1<1000;id1++)
    hscan[id1] = new TH1F(Form("hscan_%d",id1),Form("hscan_%d",id1),ch,0,rg);

  	//SCANNING HERE FOR NOW
	for (Int_t id1=0;id1<=30;id1++) {
	  for (Int_t id2=0;id2<=30;id2++) {
	    Float_t temp1 = (float)id1*200;
	    Float_t temp2 = (float)id1*200+200;
	    Float_t temp3 = (float)id2*200;
	    Float_t temp4 = (float)id2*200+200;
	    Int_t tempID = id1*30+id2;
	    hscan[tempID]->SetTitle(Form("id:%d, 1:%4.0f, 2:%4.0f, 3:%4.0f, 4:%4.0f\n",
					 tempID,temp1,temp2,temp3,temp4));

	

	  }
	}
  
  ch=600;
  rg=6000;

  he1e2 = new TH2F("he1e2","he1e2; e2; e1",ch,0,rg,ch,0,rg);
  he1e3 = new TH2F("he1e3","he1e3; e3; e1",ch,0,rg,ch,0,rg);
  he2e3 = new TH2F("he2e3","he2e3; e3; e2",ch,0,rg,ch,0,rg);

  he1e12 = new TH2F("he1e12","he1e12; e12; e1",2*ch,0,2*rg,ch,0,rg);
  he1e13 = new TH2F("he1e13","he1e13; e13; e1",2*ch,0,2*rg,ch,0,rg);
  he2e13 = new TH2F("he2e13","he2e13; e13; e2",2*ch,0,2*rg,ch,0,rg);

  he1e123 = new TH2F("he1e123","he1e123; e123; e1",3*ch,0,3*rg,ch,0,rg);
  he2e123 = new TH2F("he2e123","he2e123; e123; e2",3*ch,0,3*rg,ch,0,rg);
  he3e123 = new TH2F("he3e123","he3e123; e123; e3",3*ch,0,3*rg,ch,0,rg);
  
  he12e123 = new TH2F("he12e123","he12e123; e123; e12",3*ch,0,3*rg,2*ch,0,2*rg);
  he23e123 = new TH2F("he23e123","he23e123; e123; e23",3*ch,0,3*rg,2*ch,0,2*rg);
  he13e123 = new TH2F("he13e123","he13e123; e123; e13",3*ch,0,3*rg,2*ch,0,2*rg);

  ch=4000;
  rg=8000;
  hgg_ar38 = new TH2F("hgg_ar38","hgg_ar38",ch,0,rg,ch,0,rg);
  hgg_cl38 = new TH2F("hgg_cl38","hgg_cl38",ch,0,rg,ch,0,rg);
  hgg_s38 = new TH2F("hgg_s38","hgg_s38",ch,0,rg,ch,0,rg);
  
  //----------- process the tree ---------------//
  Int_t nEntries = ctree->GetEntries();
  printf("nEntries: %d\n",nEntries);

  Float_t counter=0;
  printf("0----------25----------50----------75----------100\n");
  for (Int_t entryNumber=0;entryNumber<nElistEntry/*nEntries*/; entryNumber++) {
    ctree->GetEntry(all_elist_x->GetEntry(entryNumber));
 
    if (((Float_t)entryNumber/(Float_t)nElistEntry)>counter)
     {
       printf("^_^_^_\n");
       counter=counter+0.125;
     }
    /* //Fill outside of gates */
    for (Int_t iMult=0;iMult<gmult;iMult++) {
      hg_tot->Fill(genergy[iMult]);

      if ( cut_ar38_dtge->IsInside(genergy[iMult],dtime[iMult]) ||
	   cut_cl38_dtge->IsInside(genergy[iMult],dtime[iMult]) ||
	   cut_s38_dtge->IsInside(genergy[iMult],dtime[iMult]) ) {
	hg_t->Fill(genergy[iMult]);

	//SCANNING HERE FOR NOW
	/* for (Int_t id1=0;id1<=30;id1++) { */
	/*   for (Int_t id2=0;id2<=30;id2++) { */
	/*     Float_t temp1 = (float)id1*200; */
	/*     Float_t temp2 = (float)id1*200+200; */
	/*     Float_t temp3 = (float)id2*200; */
	/*     Float_t temp4 = (float)id2*200+200; */
	/*     Int_t tempID = id1*30+id2; */
	/*     if ( (e[0]>temp1&&e[0]<temp2)&&(e[2]>temp3&&e[2]<temp4) ) */
	/*       hscan[tempID]->Fill(genergy[iMult]);	     */
	/*   } */
	/* } */
	he1e2->Fill(e[1],e[0]);
	he1e3->Fill(e[2],e[0]);
	he2e3->Fill(e[2],e[1]);//
	he1e12->Fill(e[0]+e[1],e[0]);
	he1e13->Fill(e[0]+e[2],e[0]);
	he2e13->Fill(e[0]+e[2],e[1]);//
	he1e123->Fill(e[0]+e[1]+e[2],e[0]);
	he2e123->Fill(e[0]+e[1]+e[2],e[1]);
	he3e123->Fill(e[0]+e[1]+e[2],e[2]);//
	he12e123->Fill(e[0]+e[1]+e[2],e[0]+e[1]);
	he23e123->Fill(e[0]+e[1]+e[2],e[1]+e[2]);
	he13e123->Fill(e[0]+e[1]+e[2],e[0]+e[2]);//	
      }//cut_ar38_dtge

      if ( cut_ar38_e1x->IsInside(x,e[0]) ||
	   cut_cl38_e1x->IsInside(x,e[0]) ||
	   cut_s38_e1x->IsInside(x,e[0])) {
    	hg_x->Fill(genergy[iMult]);
      }//cut_ar38_e1x

      if ( (cut_ar38_e1e3->IsInside(e[2],e[0]) &&
	    cut_ar38_e1e2->IsInside(e[1],e[0]) &&
	    cut_ar38_e2e3->IsInside(e[2],e[1])) ||
	   (cut_cl38_e1e3->IsInside(e[2],e[0]) &&
	    cut_cl38_e1e2->IsInside(e[1],e[0]) &&
	    cut_cl38_e2e3->IsInside(e[2],e[1])) ||
	   (cut_s38_e1e3->IsInside(e[2],e[0]) &&
	    cut_s38_e1e2->IsInside(e[1],e[0]) &&
	    cut_s38_e2e3->IsInside(e[2],e[1])) ) {
    	hg_z->Fill(genergy[iMult]);
      }//cut_ar38_z
      
      if ( cut_ar38_dtge->IsInside(genergy[iMult],dtime[iMult]) &&
    	   cut_ar38_e1x->IsInside(x,e[0]) &&
    	   cut_ar38_e1e3->IsInside(e[2],e[0]) &&
    	   cut_ar38_e1e2->IsInside(e[1],e[0]) &&
    	   cut_ar38_e2e3->IsInside(e[2],e[1]) ) {
	
    	hg_ar38->Fill(genergy[iMult]);
	for (Int_t j=iMult+1;j<gmult;j++) {
	  hgg_ar38->Fill(genergy[iMult],genergy[j]);
	  hgg_ar38->Fill(genergy[j],genergy[iMult]);
	}
      }
      
      if ( cut_cl38_dtge->IsInside(genergy[iMult],dtime[iMult]) &&
	   cut_cl38_e1x->IsInside(x,e[0]) &&
	   cut_cl38_e1e3->IsInside(e[2],e[0]) &&
	   cut_cl38_e1e2->IsInside(e[1],e[0]) &&
	   cut_cl38_e2e3->IsInside(e[2],e[1]) ) {
	
	hg_cl38->Fill(genergy[iMult]);
	for (Int_t j=iMult+1;j<gmult;j++) {
	  hgg_cl38->Fill(genergy[iMult],genergy[j]);
	  hgg_cl38->Fill(genergy[j],genergy[iMult]);
	}
      }
      if ( cut_s38_dtge->IsInside(genergy[iMult],dtime[iMult]) &&
	   cut_s38_e1x->IsInside(x,e[0]) &&
	   cut_s38_e1e3->IsInside(e[2],e[0]) &&
	   cut_s38_e1e2->IsInside(e[1],e[0]) &&
	   cut_s38_e2e3->IsInside(e[2],e[1]) ) {
	
	hg_s38->Fill(genergy[iMult]);
	for (Int_t j=iMult+1;j<gmult;j++) {
	  hgg_s38->Fill(genergy[iMult],genergy[j]);
	  hgg_s38->Fill(genergy[j],genergy[iMult]);
	}
	  
	

      }//s38 
    }//iMult
  }//EntryLoop
  
  TCanvas *cCan1 = new TCanvas("cCan1","cCan1",1550,500);
  cCan1->Clear(); cCan1->Divide(3,1);
  cCan1->cd(1); he1e2->Draw("colz");
  cCan1->cd(2); he1e3->Draw("colz");
  cCan1->cd(3); he2e3->Draw("colz");
  hg_ar38->SetLineColor(kRed);
  hg_cl38->SetLineColor(kBlue);
  hg_s38->SetFillColor(kBlack);
  cCan1->Clear(); hg_ar38->Draw(); hg_cl38->Draw("same"); hg_s38->Draw("same");
  
  gClock.Stop("gTimer");
  double gTime =  gClock.GetRealTime("gTimer");
  printf("=========== Finsihed, total runTime : %7.0f sec \n", gTime);
  printf("=========== Or, %7.1f sec / 1M events\n", gTime/((double)nEntries)*1e6);
}
