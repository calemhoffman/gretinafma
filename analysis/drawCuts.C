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

TChain *chain;
TString fileName;
Int_t goodRun[30] = {0,0,0,0,0,
		     0,0,1,1,1,
		     1,1,1,1,1,
		     1,1,1,0,1,
		     1,1,1,1,1,
		     1,1,1,1,1};
TCanvas *c1;

//Cuts for histos
TCutG *all_z_e1e3;
TCutG *all_aq_e0x;
TCutG *cut_ar38_dtge;
TCutG *cut_cl38_dtge;
TCutG *cut_s38_dtge;
TCutG *cut_s38_g1200,*cut_s38_g1500,*cut_s38_g800;

//Histos
TH2F *he0x,*he1e3;
TH2F *hdtge,*hlr,*hud;

Int_t run;
Int_t hits;
Float_t l,r,u,d,x,y;
Float_t e[10];
Int_t gmult;
Float_t genergy[100];
Float_t dtime[100];

/* main */
void drawCuts(void) {
  
  chain = new TChain("ctree");
  
  for (Int_t rn = 7; rn<30; rn++) {
    if (goodRun[rn]==1) {
      fileName.Form("/Users/calemhoffman/Research/anl/gretinafma/data/root_data/cal_%d.root",rn);
      chain->Add(fileName);
    }
  }
  
  all_z_e1e3 = (TCutG *) gDirectory->FindObjectAny("all_z_e1e3");
  all_aq_e0x = (TCutG *) gDirectory->FindObjectAny("all_aq_e0x");
  cut_ar38_dtge = (TCutG *) gDirectory->FindObjectAny("cut_ar38_dtge");
  cut_cl38_dtge = (TCutG *) gDirectory->FindObjectAny("cut_cl38_dtge");
  cut_s38_dtge = (TCutG *) gDirectory->FindObjectAny("cut_s38_dtge");
  cut_s38_g1200 = (TCutG *) gDirectory->FindObjectAny("cut_s38_g1200");
  cut_s38_g1500 = (TCutG *) gDirectory->FindObjectAny("cut_s38_g1500");
  cut_s38_g800 = (TCutG *) gDirectory->FindObjectAny("cut_s38_g800");
  
  //Generic
  chain->SetBranchAddress("run", &run);
  chain->SetBranchAddress("hits",&hits);
  //Positions
  chain->SetBranchAddress("l",&l);
  chain->SetBranchAddress("r",&r);
  chain->SetBranchAddress("u",&u);
  chain->SetBranchAddress("d",&d);
  chain->SetBranchAddress("x",&x);
  chain->SetBranchAddress("y",&y);
  //Energies
  chain->SetBranchAddress("e",e);
  //Gammas
  chain->SetBranchAddress("gmult",&gmult);
  chain->SetBranchAddress("genergy",genergy);
  chain->SetBranchAddress("dtime",dtime);
  
  //histograms define
  he0x = new TH2F("he0x","he0x; e0; x",1500,-1000,500,1000,0,3000);
  he1e3 = new TH2F("he1e3","he1e3; e3; e1",1000,0,3000,1000,0,3000);
  hdtge = new TH2F("hdtge","hdtge; dt; ge",10000,0,10000,75,0,150);
  hlr = new TH2F("hlr","hlr; l; r",1000,0,4000,1000,0,4000);
  hud = new TH2F("hud","hud; u; d",1000,0,4000,1000,0,4000);
  
  Int_t nEntries = chain->GetEntries();
  printf("nEntries: %d\n",nEntries);
  Float_t counter=0;
  
  for (Int_t entryNumber=0;entryNumber<nEntries; entryNumber++) {
    //chain->GetEntry(all_elist_x->GetEntry(entryNumber));
    chain->GetEntry(entryNumber);
    
    if (((Float_t)entryNumber/(Float_t)nEntries)>counter)
      {      
	printf("^_^_^_%4.1f_^_^_^\n",counter*100);
	counter=counter+0.1;
      }
    //Fill recoil stuff
    for (Int_t gMult=0;gMult< gmult; gMult++) {
      if (cut_s38_g1200->IsInside(genergy[gMult],dtime[gMult])
	  || cut_s38_g1500->IsInside(genergy[gMult],dtime[gMult])
	  || cut_s38_g800->IsInside(genergy[gMult],dtime[gMult]) ) {
	he0x->Fill(x,e[0]);
	he1e3->Fill(e[2],e[0]);
	hlr->Fill(r,l);
	hud->Fill(d,u);
	
	hdtge->Fill(genergy[gMult],dtime[gMult]);
      }
    }
    
  }
  
  c1 = new TCanvas("c1","c1",1000,1000);
  c1->Clear();
  //c1->Divide(2,1);
  //c1->cd(1); he0x->Draw("colz");all_aq_e0x->Draw("same");
  //c1->cd(2); he1e3->Draw("colz");all_z_e1e3->Draw("same");
  hdtge->Draw("colz");
  
}
