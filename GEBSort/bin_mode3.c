#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <math.h>
#include <string.h>
#include <assert.h>

#include "Rtypes.h"
#include "TROOT.h"
#include "TFile.h"
#include "TRandom.h"
#include "TH1.h"
#include "TH2.h"
#include "TObjArray.h"
#include "TObject.h"
#include "TKey.h"
#include "TSystem.h"
#include "TCutG.h"
#include "TTree.h"
#include "gdecomp.h"

#include "veto_pos.h"
#include "GEBSort.h"
#include "GTmode3.h"

#define MAXINT   2147483647

#define DEBUGTWOCOMPLEMENT 1

/* pointers to ROOT spectra */

TH2F *eCC_a;
TH2F *eCC_b;
TH2F *eCC_c;
TH2F *eCC_d;
TH2F *eSeg;

TH1D *mode3_hitpat;
TH1D *mode3_hitpat_chan;

TH1D *h1_chan0;
TH1D *h1_module_id;
TH2F *h2_chan;

TH1D *h1_left, *h1_right, *h1_up, *h1_down, *h1_de1, *h1_de2, *h1_de3, *h1_rftof, *h1_sumlr, *h1_sumud, *h1_de12, *h1_etot, *h1_x, *h1_y; 

TH2F *h2_ede1, *h2_ede1g, *h2_ede2, *h2_ede12, *h2_lr, *h2_ud, *h2_erftof, *h2_erftofg, *h2_xde1; 


TH1D *h1_sumehi, *h1_tgppac, *h1_tgppacg;
TH2F *h2_xehi1, *h2_xehi1g;
TH2F *h2_de1ehi, *h2_de1ehig;

TH1D *h1_ng;

/* parameters */

extern PARS Pars;
extern EXCHANGE exchange;

extern  int nCCenergies; 
extern  float CCenergies[MAX_GAMMA_RAYS];
extern  unsigned long long int CCtimestamps[MAX_GAMMA_RAYS]; //DS
extern  int CCids[MAX_GAMMA_RAYS];

TCutG *z1, *z2, *z3, *z4, *z5;
TH1D *h1_ehiz1,  *h1_ehiz2,   *h1_ehiz3,  *h1_ehiz4,  *h1_ehiz5;

TH1D *h1_gg_dt;
TH2F *h2_gg, *h2_gg_z1, *h2_gg_z2, *h2_gg_z3, *h2_gg_z4, *h2_gg_z5;


/* ----------------------------------------------------------------- */

int
sup_mode3 ()
{
  /* declarations */

  char str1[STRLEN], str2[STRLEN];
  int i;

  TH1D *mkTH1D (char *, char *, int, double, double);
  TH2F *mkTH2F (char *, char *, int, double, double, int, double, double);
  int test_convert();

#if(0)
  for (i = 0; i < 20; i++)
    {
      printf ("%15u 0x%8.8x --> ", i, i);
      printf ("%15i 0x%8.8x \n", twoscomp_to_int_24 ((unsigned int) i), twoscomp_to_int_24 ((unsigned int) i));
    }
  if (1)
    exit (0);
#endif

  /* initialize */

  /*----------------*/
  /* define spectra */

  sprintf (str1, "eCC_a");
  sprintf (str2, "eCC_a");
  eCC_a = mkTH2F (str1, str2, NCRYSTALS, 1, NCRYSTALS, ELENGTH, 1, ELENGTH);
  eCC_a->SetXTitle (str1);

  sprintf (str1, "eCC_b");
  sprintf (str2, "eCC_b");
  eCC_b = mkTH2F (str1, str2, NCRYSTALS, 1, NCRYSTALS, ELENGTH, 1, ELENGTH);
  eCC_b->SetXTitle (str1);

  sprintf (str1, "eCC_c");
  sprintf (str2, "eCC_c");
  eCC_c = mkTH2F (str1, str2, NCRYSTALS, 1, NCRYSTALS, ELENGTH, 1, ELENGTH);
  eCC_c->SetXTitle (str1);

  sprintf (str1, "eCC_d");
  sprintf (str2, "eCC_d");
  eCC_d = mkTH2F (str1, str2, NCRYSTALS, 1, NCRYSTALS, ELENGTH, 1, ELENGTH);
  eCC_d->SetXTitle (str1);

  sprintf (str1, "eSeg");
  sprintf (str2, "eSeg");
  eSeg = mkTH2F (str1, str2, NSEG, 1, NSEG, ELENGTH, 1, ELENGTH);
  eSeg->SetXTitle (str1);

  sprintf (str1, "mode3_hitpat");
  sprintf (str2, "mode3_hitpat");
  mode3_hitpat = mkTH1D (str1, str2, NCRYSTALS, 1, NCRYSTALS);
  mode3_hitpat->SetXTitle ("chystal ID");
  mode3_hitpat->SetYTitle ("counts");

  /* this one should be trivially flat  */
  /* because we read all segments out; but  */
  /* we have the spectrum just to verify this */

  sprintf (str1, "mode3_hitpat_chan");
  sprintf (str2, "mode3_hitpat_chan");
  mode3_hitpat_chan = mkTH1D (str1, str2, 45, 0, 44);
  mode3_hitpat_chan->SetXTitle ("channel ID");
  mode3_hitpat_chan->SetYTitle ("counts");

  h1_chan0 = mkTH1D ("chan0","chan0",10000,0,10000);
  h1_module_id = mkTH1D ("module","module",10000,0,10000);
 
  h2_chan = mkTH2F ("chan","chan",10000,0,10000,10,0,10);

  h1_left = mkTH1D ("l","l",10000,0,10000);
  h1_right = mkTH1D ("r","r",10000,0,10000); 
  h1_up = mkTH1D ("up","up",10000,0,10000);
  h1_down = mkTH1D ("down","down",10000,0,10000);
  h1_sumlr = mkTH1D ("sumlr","sumlr",10000,0,10000);
  h1_sumud = mkTH1D ("sumud","sumud",10000,0,10000);

  h1_x = mkTH1D ("x","x",10000,0,10000);
  h1_y = mkTH1D ("y","y",10000,0,10000);

  h1_de1 = mkTH1D ("de1","de1",10000,0,10000);
  h1_de2 = mkTH1D ("de2","de2",10000,0,10000);
  h1_de3 = mkTH1D ("de3","de3",10000,0,10000);
  h1_de12 = mkTH1D ("de12","de12",10000,0,10000);
  h1_etot = mkTH1D ("etot","etot",10000,0,10000);
  h1_rftof = mkTH1D ("rftof","rftof",10000,0,10000);

  h2_lr = mkTH2F ("lr","lr",1000,0,10000,1000,0,10000);
  h2_ud = mkTH2F ("ud","ud",1000,0,10000,1000,0,10000);

  h2_ede1 = mkTH2F ("ede1","ede1",1000,0,10000,1000,0,10000);
  h2_ede1g = mkTH2F ("ede1g","ede1g",1000,0,10000,1000,0,10000);
  h2_ede2 = mkTH2F ("ede2","ede2",1000,0,10000,1000,0,10000);
  h2_ede12 = mkTH2F ("ede12","ede12",1000,0,10000,1000,0,10000);
  h2_xde1 = mkTH2F ("xde1","xde1",1000,0,10000,1000,0,10000);

  h2_erftof = mkTH2F ("erftof","erftof",1000,0,10000,1000,0,10000);
  h2_erftofg = mkTH2F ("erftofg","erftofg",1000,0,10000,1000,0,10000);

  h1_sumehi = mkTH1D ("sumehi","sumehi",10000,0,10000);
  h1_tgppac = mkTH1D ("tgppac","tgppac",20000,-10000,10000);
  h1_tgppacg = mkTH1D ("tgppacg","tgppacg",20000,-10000,10000);
  h2_xehi1 = mkTH2F ("xehi1","xehi1",1000,0,10000,10000,0,10000);
  h2_xehi1g = mkTH2F ("xehi1g","xehi1g",1000,0,10000,10000,0,10000);

  h2_de1ehi = mkTH2F ("de1ehi","de1ehi",1000,0,10000,10000,0,10000);
  h2_de1ehig = mkTH2F ("de1ehig","de1ehig",1000,0,10000,10000,0,10000);

  h1_ng = mkTH1D ("ng","ng",10000,0,10000);

  h1_ehiz1 = mkTH1D ("ehiz1","ehiz1",10000,0,10000);
  h1_ehiz2 = mkTH1D ("ehiz2","ehiz2",10000,0,10000);
  h1_ehiz3 = mkTH1D ("ehiz3","ehiz3",10000,0,10000);
  h1_ehiz4 = mkTH1D ("ehiz4","ehiz4",10000,0,10000);
  h1_ehiz5 = mkTH1D ("ehiz5","ehiz5",10000,0,10000);

  h1_gg_dt = mkTH1D ("gg_dt","gg_dt",2000,-1000,1000);
  h2_gg = mkTH2F ("gg","gg",2500,0,5000,2500,0,5000);
  h2_gg_z1 = mkTH2F ("gg_z1","gg_z1",2500,0,5000,2500,0,5000);
  h2_gg_z2 = mkTH2F ("gg_z2","gg_z2",2500,0,5000,2500,0,5000);
  h2_gg_z3 = mkTH2F ("gg_z3","gg_z3",2500,0,5000,2500,0,5000);
  h2_gg_z4 = mkTH2F ("gg_z4","gg_z4",2500,0,5000,2500,0,5000);
  h2_gg_z5 = mkTH2F ("gg_z5","gg_z5",2500,0,5000,2500,0,5000);

  /* list what we have */

//  Pars.wlist = gDirectory->GetList ();
//  Pars.wlist->Print ();

#if(0)
  /* test 32 bit to 24 bit converter */

  test_convert();
#endif

// window



// = new TCUT("eftof");

 TFile *g = new TFile("ede1b.root","read");

 z1 = (TCutG*) g->Get("z1");
 z2 = (TCutG*) g->Get("z2");
 z3 = (TCutG*) g->Get("z3");
 z4 = (TCutG*) g->Get("z4");
 z5 = (TCutG*) g->Get("z5");

 g->Close();

  return (0);

}

/* ----------------------------------------------------------------- */

int
exit_bin_mode3 ()
{

  return (0);

};


/* ----------------------------------------------------------------- */

int
bin_mode3 (GEB_EVENT * GEB_event)
{

  /* for some documentation, see: */
  /* evince ~/d6/keep/2017_GT_mode3_format.odp  */

  /* declarations */

  GTEVENT Event;
  unsigned int t1, t2, t3, t4;
  int ii, i, nBadTestPat = 0;
  volatile unsigned int *bit32Pointer;
  unsigned short int *bit16Pointer;
  FILE *fp1 = NULL, *fp2 = NULL;
  char str[128];
  int pos = 0, ncrystal = 0, sppos = 0, ccpos = 0;
  unsigned int tempE;
  int rawE;
  int gtheaders=0, newcrystal=0;

  /* prototypes */

  int GebTypeStr (int type, char str[]);
  int c24bit32bit (unsigned int);
  void pprint_32 (char *, unsigned int);
  int twoscomp_to_int_24 (unsigned int );

 float de1,de2,de3,de12,etot, left,right,up,down,rftof, sumlr, sumud, x, y;
 unsigned long long int ppacts;
 long long int tgppac;

  if (Pars.CurEvNo <= Pars.NumToPrint)
    printf ("entered bin_mode3 @ event number: %i \n", Pars.CurEvNo);


  de1=0; de2=0; de3=0; de12=0; etot=0; left=0; right=0; up=0; down=0; rftof=0; sumlr=0; sumud=0; x=0; y=0;
  ppacts=0; tgppac=0;

  for (ii = 0; ii < GEB_event->mult; ii++)
    {

      /* pos keeps record of how far we have */
      /* proceeded in the payload */
      /* and count how many crystals in payload */

      pos = 0;
      ncrystal = 0;

      if (GEB_event->ptgd[ii]->type == GEB_TYPE_RAW || GEB_event->ptgd[ii]->type == GEB_TYPE_GT_MOD29)
        {

          if (Pars.CurEvNo <= Pars.NumToPrint)
            {
              GebTypeStr (GEB_event->ptgd[ii]->type, str);
              printf ("\nbin_mode3: %2i> %2i, %s, TS=%lli, 0x%llx; ", ii, GEB_event->ptgd[ii]->type, str,
                      GEB_event->ptgd[ii]->timestamp, GEB_event->ptgd[ii]->timestamp);
              printf ("payload length: %i bytes\n", GEB_event->ptgd[ii]->length);
            }

          /* byteswap the entire payload */

          bit32Pointer = (unsigned int *) GEB_event->ptinp[ii];
          for (i = 0; i < GEB_event->ptgd[ii]->length / 4; i++)
            {
              t1 = (*(bit32Pointer + i) & 0x000000ff) << 24;
              t2 = (*(bit32Pointer + i) & 0x0000ff00) << 8;
              t3 = (*(bit32Pointer + i) & 0x00ff0000) >> 8;
              t4 = (*(bit32Pointer + i) & 0xff000000) >> 24;
              *(bit32Pointer + i) = t1 + t2 + t3 + t4;
            };

          /* inside the payload we have the a number */
          /* of header/trace data sets. These are the  */
          /* crystals that were in coincidence. Here  */
          /* we loop over these header/trace data sets. */
          /* We may have data from more than one crystal  */
          /* in this payload. Thus, there will be at  */
          /* least 40 traces, but there can also be  */
          /* 80, 120... etc. Be sure MAXPAYLOADSIZE  */
          /* is big enough to handle GT mode3 payloads. */

          /* loop over the header/traces of the mode 3 data */

          while (pos < GEB_event->ptgd[ii]->length)
            {

              /* start of event (Event.len known from last event) */

              if (pos == 0)
                bit32Pointer = (unsigned int *) GEB_event->ptinp[ii];
              else
                bit32Pointer += (Event.len / 4);

              /* check the EOE situation */

              if (*bit32Pointer != EOE)
                {
                  nBadTestPat++;

                  if (nBadTestPat == 10)
                    printf ("** suspending warnings about bad EOE markers...\n");

                  if (nBadTestPat < 10)
                    {
                      printf ("ooops: bit32Pointer=%8.8x after event # %i trace # %i\n", *bit32Pointer, Pars.CurEvNo,
                              ncrystal);
                      fflush (stdout);
                      exit (1);
                    };

                };

            if ( (gtheaders%40) == 0)
               {
               ncrystal++;
               newcrystal=1;
               }
             gtheaders++;
//             printf("%i %i %i\n", gtheaders, ncrystal, newcrystal);
                
              /* fill event header, skip EOE */

              bit16Pointer = (unsigned short int *) (bit32Pointer + 1);
              for (i = 0; i < HDRLENWORDS; i++)
                {
                  Event.hdr[i] = *(bit16Pointer + i);
                };

              /* debug list */

              if (Pars.CurEvNo <= Pars.NumToPrint)
                  {
                  printf("\n---------\nnew GTheader at pos=%i or %i words (%i):\n",pos,pos/2, pos/2+8);
                for (i = 0; i < HDRLENWORDS; i++)
                  printf ("Event.hdr[%2i]=0x%4.4x, %6i\n", i, Event.hdr[i], Event.hdr[i]);
                  };

              /* eventlength/tracelength in bytes */
              /* the +4 comes from the EOE 4 bit word */

              Event.len = 4 * (Event.hdr[1] & 0x7ff) + 4;
              Event.traceLen = Event.len - HDRLENBYTES - sizeof (unsigned int);

              if (Pars.CurEvNo <= Pars.NumToPrint)
                {
                  printf ("Event.len=%4i, Event.traceLen=%4i (in Bytes)\n", Event.len, Event.traceLen);
                  printf ("Event.len=%4i, Event.traceLen=%4i (in 16 bit words)\n", Event.len / sizeof (short int),
                          Event.traceLen / sizeof (short int));
                  printf ("Event.len=%4i, Event.traceLen=%4i (in 32 bit words)\n", Event.len / sizeof (int),
                          Event.traceLen / sizeof (int));
                };


              /* check the next EOE is there */
              /* before we go on (unless last set) */

              pos += Event.len;

              if (Pars.CurEvNo <= Pars.NumToPrint && pos < GEB_event->ptgd[ii]->length)
                printf ("next start: 0x%8.8x, pos= %i\n", *(bit32Pointer + (Event.len / 4)), pos);

              /* potential debug info */

              if (*(bit32Pointer + (Event.len / 4)) != EOE && pos < GEB_event->ptgd[ii]->length)
                {
                  printf ("next EOE not found at pointer %p, seek manually\n", bit32Pointer + (Event.len / 4));
                  printf ("Event.len=%i, Event.traceLen=%i\n", Event.len, Event.traceLen);
                  i = 1;
                  while (i < (Event.len + 10))
                    {
                      printf ("%3i has 0x%8.8x\n", 4 * i, *(bit32Pointer + i));
                      fflush (stdout);
                      if (*(bit32Pointer + i) == EOE)
                        {
                          printf ("found it\n");
                          break;
                        };
                      i++;
                    };
                  i--;
                  printf ("%3i has 0x%8.8x\n", i, *(bit32Pointer + i));
                };

              /* extract the Board IDs etc */
              /* chan_id is 0-9 on digitizer */

              Event.chan_id = (Event.hdr[0] & 0x000f);
              Event.digitizer_id = (Event.hdr[0] >> 4) & 0x0003;
              Event.crystal_id = (Event.hdr[0] >> 6) & 0x0003;
              Event.module_id = (Event.hdr[0] >> 8) & 0x00ff;   /* zhu use 0x00ff, tl use 0x001f */ 


              /* construct detector/channel/segment ID */

              Event.ge_id = Event.module_id * 4 + Event.crystal_id;
              mode3_hitpat->Fill (Event.ge_id, 1);

              Event.channel = Event.digitizer_id * 10 + Event.chan_id;
              mode3_hitpat_chan->Fill (Event.channel, 1);

              Event.seg_id = Event.ge_id * 40 + Event.channel;

              if (Pars.CurEvNo <= Pars.NumToPrint)
                {
                  printf ("0x%4.4x ", Event.hdr[0]);
                  printf ("module_id = %i ", Event.module_id);
                  printf ("crystal_id = %i ", Event.crystal_id);
                  printf ("digitizer_id = %i ", Event.digitizer_id);
                  printf ("chan_id = %i ", Event.chan_id);
                  printf ("ge_id = %i ", Event.ge_id);
                  printf ("channel = %i ", Event.channel);
                  if (((int) (Event.channel) % 10) == 9)
                    printf (" -> is CC");
                  else
                    printf (" -> is segment");
                  printf ("\n");
                };

              /* count the crystals we have processed */



                  if (Pars.CurEvNo <= Pars.NumToPrint)
                  if (newcrystal==1)
                    {
                      newcrystal=0;

                  /* write first few superpulse traces out */
                  /* open files here, fill later */

                      if (fp1 != NULL)
                        fclose (fp1);
                      if (fp2 != NULL)
                        fclose (fp2);

                      sprintf (str, "superpulse_%3.3i_%2.2i_%2.2i.xy", Pars.CurEvNo, ii, ncrystal);
                      printf ("open %s at Event.chan_id = %i\n", str, Event.chan_id);
                      fp1 = fopen (str, "w");
                      sppos = 0;

                      sprintf (str, "CCpulse_%3.3i_%2.2i_%2.2i.xy", Pars.CurEvNo, ii, ncrystal);
                      printf ("open %s at Event.chan_id = %i\n", str, Event.chan_id);
                      fp2 = fopen (str, "w");
                      ccpos = 0;

                    };

              if (Pars.CurEvNo <= Pars.NumToPrint)
                printf ("ncrystal=%i\n", ncrystal);

              /* copy trace into 16 bit words */
              /* bit16Pointer points first word after first EOE */

              for (i = 0; i < (Event.traceLen / 2); i++)
                if (((int) (Event.chan_id) % 10) == 9)
                  Event.trace[i] = *(bit16Pointer + i + HDRLENWORDS);
                else
                  {
                    Event.trace[i] = *(bit16Pointer + i + HDRLENWORDS);
                    Event.trace[i] = -(short int) Event.trace[i];
                  };


              if ((Pars.CurEvNo <= Pars.NumToPrint))
                if (fp1 != NULL && fp2 != NULL)
                  {
                    assert (fp1 != NULL);
                    if (((int) (Event.chan_id) % 10) != 9)
                      {
                        for (i = 0; i < (Event.traceLen / 2); i++)
                          fprintf (fp1, "%i %i\n", sppos++, Event.trace[i]);
                      }
                    else
                      {
                        for (i = 0; i < (Event.traceLen / 2); i++)
                          fprintf (fp2, "%i %i\n", ccpos++, Event.trace[i]);
                      }

                    printf ("wrote trace to %s\n", str);
                    fflush (fp1);
                    fflush (fp2);
                  };

              /* extract the energies like Shoufei does in muxTest.cc */
              /* needs some translating.... */

              tempE = (((unsigned int) Event.hdr[6]) & 0x00ff) << 16;
              tempE += (unsigned int) Event.hdr[5] & 0xffff;
              if (Pars.CurEvNo <= Pars.NumToPrint)
                pprint_32 ("two's comp tempE  :: ", tempE);

              rawE = twoscomp_to_int_24 (tempE);
//              rawE =c24bit32bit(tempE);
              if (Pars.CurEvNo <= Pars.NumToPrint)
                pprint_32 ("rawE              :: ", rawE);

              /* change the sign as the the Digs are neg */

              if (rawE <= 0)
                rawE = -rawE;
              if (Pars.CurEvNo <= Pars.NumToPrint)
                 pprint_32 ("rawE (sign change):: ", rawE);

              /* downscale */

              Event.ehi = (int) ((float) rawE / Mvalue);
              if (Pars.CurEvNo <= Pars.NumToPrint)
                printf ("Event.ehi= %15i 0x%8.8x\n", Event.ehi, Event.ehi);

              /* for the energy extraction method from: */
              /* http://gretina.lbl.gov/tools-etc/GEBHeaderTypes.pdf */
              /* see svn version 733 */


              /* bin central contact (four gains) and segments  energies */

              Event.ehi /= 10;
              if (Pars.CurEvNo <= Pars.NumToPrint)
                printf ("Event.ehi=%i (gain changed)\n", Event.ehi);

              if (Event.ehi > 10 && Event.ehi < ELENGTH)
                {

                  if ((Event.chan_id % 10) != 9)
                    if (Event.seg_id < NSEG)
                      eSeg->Fill ((double) Event.seg_id, (double) Event.ehi, 1);

                  if (Event.channel == 9)
                    eCC_a->Fill ((double) Event.ge_id, (double) Event.ehi, 1);
                  if (Event.channel == 19)
                    eCC_b->Fill ((double) Event.ge_id, (double) Event.ehi, 1);
                  if (Event.channel == 29)
                    eCC_c->Fill ((double) Event.ge_id, (double) Event.ehi, 1);
                  if (Event.channel == 39)
                    eCC_d->Fill ((double) Event.ge_id, (double) Event.ehi, 1);

                };

              /* extract LED external time, per documentation, works */

              Event.LEDts = (unsigned long long int) Event.hdr[2] +
                ((unsigned long long int) Event.hdr[3] << 16) + ((unsigned long long int) Event.hdr[4] << 32);
              if (Pars.CurEvNo <= Pars.NumToPrint)
                printf ("Event.LEDts = %20lli\n", Event.LEDts);

              /* extract CFD external time, per documentation, seems odd...not working? */

              Event.CFDts = (unsigned long long int) Event.hdr[7] +
                ((unsigned long long int) Event.hdr[8] << 16) + ((unsigned long long int) Event.hdr[9] << 32);
              if (Pars.CurEvNo <= Pars.NumToPrint)
                printf ("Event.CFDts = %20lli\n", Event.CFDts);


     if ((Event.module_id==31)&&(Event.chan_id==0)) { h1_chan0->Fill(Event.ehi); right=Event.ehi; h1_right->Fill(right); };
      if ((Event.module_id==31)&&(Event.chan_id==1)) { up=Event.ehi; h1_up->Fill(up); }
      if ((Event.module_id==31)&&(Event.chan_id==2)) { de3=Event.ehi; h1_de3->Fill(de3); };
      if ((Event.module_id==31)&&(Event.chan_id==3)) { left=Event.ehi; h1_left->Fill(left); ppacts=Event.LEDts; };
      if ((Event.module_id==31)&&(Event.chan_id==5)) { down=Event.ehi; h1_down->Fill(down); };
      if ((Event.module_id==31)&&(Event.chan_id==6)) { de1=Event.ehi; h1_de1->Fill(de1); };
      if ((Event.module_id==31)&&(Event.chan_id==7)) { de2=Event.ehi; h1_de2->Fill(de2); };
      if ((Event.module_id==31)&&(Event.chan_id==9)) { rftof=Event.ehi; h1_rftof->Fill(rftof); };

    if (Event.module_id==31) h2_chan->Fill(Event.ehi,Event.chan_id);
    h1_module_id->Fill(Event.module_id);

            };                  /* while (pos<=GEB_event->ptgd[ii]->length) */


        };                      /* if(GEB_event->ptgd[ii]->type == GEB_TYPE_RAW) */


 

 

    };



      h2_lr->Fill(left, right);
      h2_ud->Fill(up, down);
  
      if ((left>0)&&(right>0)) {
        sumlr=left+right;
        h1_sumlr->Fill(sumlr);
        x=left-right+5000;
        h1_x->Fill(x);
      };

      if ((up>0)&&(down>0)) {
        sumud=up+down;
        h1_sumud->Fill(sumud);
        y=up-down+5000;
        h1_y->Fill(y);
      };


      if ((de1>0)&&(de2>0)&&(de3>0)) {
	etot=de1+de3;
        de12=de1+de2;
        h2_ede1->Fill(etot,de1);
        h2_ede2->Fill(etot,de2);
        h2_ede12->Fill(etot,de12);
        h1_de12->Fill(de12);
        h1_etot->Fill(etot);
        h2_xde1->Fill(x,de1);
      };

    h2_erftof->Fill(etot, rftof);

    if (de1>1400) h2_erftofg->Fill(etot, rftof);

    for (i=0; i<nCCenergies; i++) {
      //printf ("---CCenergies[%i]=%7.2f\n", i, CCenergies[i]);
      h1_sumehi->Fill(CCenergies[i]);
    };

    h1_ng->Fill(nCCenergies);

   
    for (i=0; i<nCCenergies; i++) {
       tgppac=CCtimestamps[i]-Event.LEDts;
       h1_tgppac->Fill(tgppac);
       h2_xehi1->Fill(x, CCenergies[i]);
       h2_de1ehi->Fill(de1, CCenergies[i]);
       if ((tgppac>-80)&&(tgppac<-40)) {
         h2_ede1g->Fill(etot,de1);
	 //if ((de1>1200)&&(de2>10)&&(de3>10)) {
         h1_tgppacg->Fill(tgppac);
         h2_xehi1g->Fill(x, CCenergies[i]);
         h2_de1ehig->Fill(de1, CCenergies[i]);
 
         if (z1->IsInside(etot,de1)) {h1_ehiz1->Fill(CCenergies[i]);};
         if (z2->IsInside(etot,de1)) {h1_ehiz2->Fill(CCenergies[i]);};
         if (z3->IsInside(etot,de1)) {h1_ehiz3->Fill(CCenergies[i]);};
         if (z4->IsInside(etot,de1)) {h1_ehiz4->Fill(CCenergies[i]);};
         if (z5->IsInside(etot,de1)) {h1_ehiz5->Fill(CCenergies[i]);};

	 //};
	if (nCCenergies > 1){
		for (int j=0; j<i; j++){
			h1_gg_dt->Fill(CCtimestamps[i] - CCtimestamps[j]);
				//if (CCtimestamps[i] - CCtimestamps[j] > -40 && CCtimestamps[i] - CCtimestamps[j] < 40){
					h2_gg->Fill(CCenergies[i], CCenergies[j]);
					h2_gg->Fill(CCenergies[j], CCenergies[i]);
         				if (z1->IsInside(etot,de1)) {
						h2_gg_z1->Fill(CCenergies[i], CCenergies[j]);
						h2_gg_z1->Fill(CCenergies[j], CCenergies[i]);
					}
         				if (z2->IsInside(etot,de1)) {
						h2_gg_z2->Fill(CCenergies[i], CCenergies[j]);
						h2_gg_z2->Fill(CCenergies[j], CCenergies[i]);
					}
         				if (z3->IsInside(etot,de1)) {
						h2_gg_z3->Fill(CCenergies[i], CCenergies[j]);
						h2_gg_z3->Fill(CCenergies[j], CCenergies[i]);
					}
         				if (z4->IsInside(etot,de1)) {
						h2_gg_z4->Fill(CCenergies[i], CCenergies[j]);
						h2_gg_z4->Fill(CCenergies[j], CCenergies[i]);
					}
         				if (z5->IsInside(etot,de1)) {
						h2_gg_z5->Fill(CCenergies[i], CCenergies[j]);
						h2_gg_z5->Fill(CCenergies[j], CCenergies[i]);
					}

				//}
		}
	}
     };
    };




 nCCenergies=0;

  /* done */

  if (Pars.CurEvNo <= Pars.NumToPrint)
    printf ("exit bin_mode3\n");

  return (0);

}
