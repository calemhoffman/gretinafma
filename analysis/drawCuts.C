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
TCanvas *cc;

//list stuff
TEventList * elist_all;

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

Int_t run;
Int_t hits;
Float_t l,r,u,d,x,y;
Float_t e[10];
Int_t gmult;
Float_t genergy[100];
Float_t dtime[100];

/* main */
void drawCuts(void) {

  //TwoChains!
  chain = new TChain("ctree");
  for (Int_t rn = 7; rn<30; rn++) {
    if (goodRun[rn]==1) {
      fileName.Form("/Users/calemhoffman/Research/anl/gretinafma/data/root_data/cal_%d.root",rn);
      chain->Add(fileName);
    }
  }
  chain->GetListOfFiles()->Print();

  //Listomania
  TFile *listFile = new TFile("eventLists.root");
  listFile->GetObject("elist_all",elist_all);
  Int_t numElistEntries = elist_all->GetN();
  printf("Number of ElistEntries: %d \n",numElistEntries);
  gDirectory->pwd();
  gROOT->cd();
  gDirectory->pwd();
  //elist_all = elist_temp;
  // listFile->Close();

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

  for (Int_t entryNumber=0;entryNumber<numElistEntries; entryNumber++) {
  //for (Int_t entryNumber=0;entryNumber<nEntries; entryNumber++) {
    chain->GetEntry(elist_all->GetEntry(entryNumber));
    //chain->GetEntry(entryNumber);

    if (((Float_t)entryNumber/(Float_t)nEntries)>counter)
      {
	printf("^_^_^_%4.1f_^_^_^\n",counter*100);
	counter=counter+0.1;
      }
    //Fill recoil stuff
    he0x->Fill(x,e[0]);
    he1e3->Fill(e[2],e[0]);
    hlr->Fill(r,l);
    hud->Fill(d,u);
    for (Int_t gMult=0;gMult< gmult; gMult++) {
      hdtge->Fill(genergy[gMult],dtime[gMult]);
    }

    /* s38 */
    if ( (cut_e1e3_s38->IsInside(e[2],e[0]))
	 && (cut_e0x_s38->IsInside(x,e[0]))
	 && (cut_lr_s38->IsInside(r,l))
	 && (cut_ud_s38->IsInside(d,u)) ) {

      for (Int_t gMult=0;gMult< gmult; gMult++) {
	if ( (cut_dtge_s38->IsInside(genergy[gMult],dtime[gMult])) ) {
	  // hdtge->Fill(genergy[gMult],dtime[gMult]);
	  hg_s38->Fill(genergy[gMult]);
	}
      }

    }

    /* cl38 */
    if ( (cut_e1e3_cl38->IsInside(e[2],e[0]))
	 && (cut_e0x_cl38->IsInside(x,e[0]))
	 && (cut_lr_cl38->IsInside(r,l))
	 && (cut_ud_cl38->IsInside(d,u)) ) {

      for (Int_t gMult=0;gMult< gmult; gMult++) {
	if ( (cut_dtge_cl38->IsInside(genergy[gMult],dtime[gMult])) ) {
	  // hdtge->Fill(genergy[gMult],dtime[gMult]);
	  hg_cl38->Fill(genergy[gMult]);
	  }
      }

    } /* cl38 */

   /* ar38 */
    if ( (cut_e1e3_ar38->IsInside(e[2],e[0]))
	 && (cut_e0x_ar38->IsInside(x,e[0]))
	 && (cut_lr_ar38->IsInside(r,l))
	 && (cut_ud_ar38->IsInside(d,u)) ) {

      for (Int_t gMult=0;gMult< gmult; gMult++) {
	if ( (cut_dtge_ar38->IsInside(genergy[gMult],dtime[gMult])) ) {
	  //hdtge->Fill(genergy[gMult],dtime[gMult]);
	  hg_ar38->Fill(genergy[gMult]);
	}
      }

    } /* ar38 */


    /* p33 */
    if ( (cut_e1e3_p33->IsInside(e[2],e[0]))
	 && (cut_e0x_p33->IsInside(x,e[0]))
	 && (cut_lr_p33->IsInside(r,l))
	 && (cut_ud_p33->IsInside(d,u)) ) {

      for (Int_t gMult=0;gMult< gmult; gMult++) {
	if ( (cut_dtge_p33->IsInside(genergy[gMult],dtime[gMult])) ) {
	  //hdtge->Fill(genergy[gMult],dtime[gMult]);
	  hg_p33->Fill(genergy[gMult]);
	}
      }

    } /* p33 */

  }

  cc = new TCanvas("cc","cc",1000,1000);
  cc->Clear();
  //cc->Divide(2,1);
  //cc->cd(1); he0x->Draw("colz");all_aq_e0x->Draw("same");
  //cc->cd(2); he1e3->Draw("colz");all_z_e1e3->Draw("same");
  // hdtge->Draw("colz");
  hg_ar38->Draw(""); hg_cl38->Draw("same"); hg_s38->Draw("same"); hg_p33->Draw("same");

}
