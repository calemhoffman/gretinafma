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
#include "GTMerge.h"


typedef struct PAYLOAD
{
  char p[MAXDATASIZE];
} PAYLOAD;

typedef struct TRACK_STRUCT
{
  int n;
  GEBDATA *gd;
  PAYLOAD *payload;
} TRACK_STRUCT;

#define PPLO 1
#define PPHI 2
#define BBLO 3
#define BBHI 4

/* pointers to ROOT spectra */


TH1D *angcor_raw_pp;
TH1D *angcor_raw_pb;
TH1D *angcor_raw_bb;
TH1D *isotropic;

/* parameters */

extern PARS Pars;
extern EXCHANGE exchange;

#define NBINS 180

int nn_sp[100];

/*-----------------------------------------------------*/

int
exit_angcor ()
{

  int i;
  double mm = 0;

  for (i = 0; i < 100; i++)
    mm += nn_sp[i];
  mm /= 100;
  for (i = 0; i < 100; i++)
    if (nn_sp[i] > 0)
      printf ("nn_sp[%2i]=%10i, %i, %5.1f%%\n", i, nn_sp[i], nn_sp[i], (float) nn_sp[i] / mm);

  return (0);

};

/*-----------------------------------------------------*/

int
sup_angcor ()
{
  /* declarations */

  int i;
  char str1[STRLEN], str2[STRLEN];
  TH1D *mkTH1D (char *, char *, int, double, double);
  TH2F *mkTH2F (char *, char *, int, double, double, int, double, double);

  sprintf (str1, "angcor_raw_pp");
  sprintf (str2, "angcor_raw_pp");
  angcor_raw_pp = mkTH1D (str1, str2, NBINS, 0, 180);
  sprintf (str1, "angle");
  angcor_raw_pp->SetXTitle (str1);
  sprintf (str1, "yield");
  angcor_raw_pp->SetYTitle (str1);

  sprintf (str1, "angcor_raw_pb");
  sprintf (str2, "angcor_raw_pb");
  angcor_raw_pb = mkTH1D (str1, str2, NBINS, 0, 180);
  sprintf (str1, "angle");
  angcor_raw_pb->SetXTitle (str1);
  sprintf (str1, "yield");
  angcor_raw_pb->SetYTitle (str1);

  sprintf (str1, "angcor_raw_bb");
  sprintf (str2, "angcor_raw_bb");
  angcor_raw_bb = mkTH1D (str1, str2, NBINS, 0, 180);
  sprintf (str1, "angle");
  angcor_raw_bb->SetXTitle (str1);
  sprintf (str1, "yield");
  angcor_raw_bb->SetYTitle (str1);

  sprintf (str1, "isotropic");
  sprintf (str2, "isotropic");
  isotropic = mkTH1D (str1, str2, NBINS, 0, 180);
  sprintf (str1, "angle");
  isotropic->SetXTitle (str1);
  sprintf (str1, "yield");
  isotropic->SetYTitle (str1);


  /* list what we have */

  printf (" we have defined the following spectra:\n");


  Pars.wlist = gDirectory->GetList ();
  Pars.wlist->Print ();

  printf (" angcor peaks      %7.1f and %7.1f\n", Pars.GGLOp, Pars.GGHIp);
  printf (" angcor background %7.1f and %7.1f\n", Pars.GGLOb, Pars.GGHIb);
  printf (" angcor gate width %7.1f peak\n", Pars.GGWp);
  printf (" angcor gate width %7.1f background\n", Pars.GGWb);
  printf ("ctype[1]: %6.1f ... %6.1f\n", Pars.GGLOp - Pars.GGWp, Pars.GGLOp + Pars.GGWp);
  printf ("ctype[2]: %6.1f ... %6.1f\n", Pars.GGHIp - Pars.GGWp, Pars.GGHIp + Pars.GGWp);
  printf ("ctype[3]: %6.1f ... %6.1f\n", Pars.GGLOb - Pars.GGWb, Pars.GGLOb + Pars.GGWb);
  printf ("ctype[4]: %6.1f ... %6.1f\n", Pars.GGHIb - Pars.GGWb, Pars.GGHIb + Pars.GGWb);

  printf ("Note: always run through bin_mode1 before \n");
  printf ("using this function so that dopper \n");
  printf ("corrections can be handled properly\n");

  for (i = 0; i < 100; i++)
    nn_sp[i] = 0;

  return (0);

};

/* ----------------------------------------------------------------- */

int
bin_angcor (GEB_EVENT * GEB_event)
{

  /* declarations */

  char str[128];
  int i, j, k = 0, l, nn, isParsGGLOp, isParsGGHIp, isParsGGLOb, isParsGGHIb;
  int cType[MAX_GAMMA_RAYS];
  float xx[MAX_GAMMA_RAYS], yy[MAX_GAMMA_RAYS], zz[MAX_GAMMA_RAYS], ee[MAX_GAMMA_RAYS];
  TRACKED_GAMMA_HIT *grh;
  float dd, dotProduct, polang;

  static float xx_o[MAX_GAMMA_RAYS], yy_o[MAX_GAMMA_RAYS], zz_o[MAX_GAMMA_RAYS];
  static int cType_o[MAX_GAMMA_RAYS];
  static int nn_o;

  /* prototypes */

  int GebTypeStr (int type, char str[]);
  int print_tracked_gamma_rays (FILE *, TRACKED_GAMMA_HIT *);

  if (GEB_event->mult <= 2)
    return (0);

  if (Pars.CurEvNo <= Pars.NumToPrint)
    printf ("entered bin_angcor: mult=%i\n", GEB_event->mult);


  /*----------------------*/
  /* angular correlations */
  /*----------------------*/

  nn = 0;
  for (i = 0; i < GEB_event->mult; i++)
    {

      if (Pars.CurEvNo <= Pars.NumToPrint)
        {
          GebTypeStr (GEB_event->ptgd[i]->type, str);
          printf ("bin_angcor, %2i> %2i, %s, TS=%lli\n", i, GEB_event->ptgd[i]->type, str,
                  GEB_event->ptgd[i]->timestamp);
        }

      if (GEB_event->ptgd[i]->type == GEB_TYPE_TRACK)
        {

          grh = (TRACKED_GAMMA_HIT *) GEB_event->ptinp[i];
          if (Pars.CurEvNo <= Pars.NumToPrint)
            print_tracked_gamma_rays (stdout, grh);

          /*-----------------------------*/
          /* prepare angular correlation */
          /*-----------------------------*/

          if (grh->ngam >= 2)
            for (j = 0; j < grh->ngam; j++)
              {


                isParsGGLOp = ((grh->gr[j].esum > (Pars.GGLOp - Pars.GGWp))
                               && (grh->gr[j].esum < (Pars.GGLOp + Pars.GGWp)));
                isParsGGHIp = ((grh->gr[j].esum > (Pars.GGHIp - Pars.GGWp))
                               && (grh->gr[j].esum < (Pars.GGHIp + Pars.GGWp)));
                isParsGGLOb = ((grh->gr[j].esum > (Pars.GGLOb - Pars.GGWb))
                               && (grh->gr[j].esum < (Pars.GGLOb + Pars.GGWb)));
                isParsGGHIb = ((grh->gr[j].esum > (Pars.GGHIb - Pars.GGWb))
                               && (grh->gr[j].esum < (Pars.GGHIb + Pars.GGWb)));

                if (isParsGGLOp || isParsGGHIp || isParsGGLOb || isParsGGHIb)
                  {
                    if (Pars.CurEvNo <= Pars.NumToPrint)
                      {
                        printf ("__e %5.1f", grh->gr[j].esum);
                        printf (" [%i]", isParsGGLOp);
                        printf (" [%i]", isParsGGHIp);
                        printf (" [%i]", isParsGGLOb);
                        printf (" [%i]", isParsGGHIb);
                        printf ("\n");

                      }
                    xx[nn] = grh->gr[j].x0;
                    yy[nn] = grh->gr[j].y0;
                    zz[nn] = grh->gr[j].z0;
                    ee[nn] = grh->gr[j].esum;
                    if (isParsGGLOp)
                      cType[nn] = PPLO;
                    else if (isParsGGHIp)
                      cType[nn] = PPHI;
                    else if (isParsGGLOb)
                      cType[nn] = BBLO;
                    else if (isParsGGHIb)
                      cType[nn] = BBHI;

                    nn++;
                    if (Pars.CurEvNo <= Pars.NumToPrint)
                      printf ("nn=%i\n", nn);
                  }

              };


        };

    };

  /*----------------------------*/
  /* update angular correlation */
  /* ignore any target offsets for now */
  /*----------------------------*/

  /*only if nn==2 do we have two of peak or background */

  nn_sp[nn]++;
  if (nn < 2)
    return (0);

  for (k = 0; k < nn; k++)
    for (l = k + 1; l < nn; l++)
      {

        if (Pars.CurEvNo <= Pars.NumToPrint)
          printf ("nn=%i ctypes: %i %i\n", nn, cType[k], cType[l]);

        /* bin the angle between the two gamma rays */

        dd = xx[k] * xx[k] + yy[k] * yy[k] + zz[k] * zz[k];
        dd = sqrtf (dd);
        xx[k] /= dd;
        yy[k] /= dd;
        zz[k] /= dd;

        dd = xx[l] * xx[l] + yy[l] * yy[l] + zz[l] * zz[l];
        dd = sqrtf (dd);
        xx[l] /= dd;
        yy[l] /= dd;
        zz[l] /= dd;

        dotProduct = xx[k] * xx[l] + yy[k] * yy[l] + zz[k] * zz[l];
        if (dotProduct < -1.0)
          dotProduct = -1.0;
        if (dotProduct > 1.0)
          dotProduct = 1.0;
        polang = 57.2958 * acosf (dotProduct);
        if (Pars.CurEvNo <= Pars.NumToPrint)
          printf ("polang=%f\n", polang);

        /* update current event spectra */

        if ((cType[k] == PPLO && cType[l] == PPHI) || (cType[k] == PPHI && cType[l] == PPLO))
          {
            if (Pars.CurEvNo <= Pars.NumToPrint)
              printf ("**update pp\n");
            angcor_raw_pp->Fill ((double) polang, 1);
          };
        if ((cType[k] == PPLO && cType[l] == BBHI) || (cType[k] == BBHI && cType[l] == PPLO))
          {
            if (Pars.CurEvNo <= Pars.NumToPrint)
              printf ("**update pb, 1\n");
            angcor_raw_pb->Fill ((double) polang, 1);
          };
        if ((cType[k] == PPHI && cType[l] == BBLO) || (cType[k] == BBLO && cType[l] == PPHI))
          {
            if (Pars.CurEvNo <= Pars.NumToPrint)
              printf ("**update pb, 2\n");
            angcor_raw_pb->Fill ((double) polang, 1);
          };
        if ((cType[k] == BBLO && cType[l] == BBHI) || (cType[k] == BBHI && cType[l] == BBLO))
          {
            if (Pars.CurEvNo <= Pars.NumToPrint)
              printf ("**update bb\n");
            angcor_raw_bb->Fill ((double) polang, 1);
          };

      };

  for (k = 0; k < nn; k++)
    for (l = 0; l < nn_o; l++)
      {

        /* make the uncorrelated distribution */
        /* from last uncorrelated event, four combinations */

        dotProduct = xx[k] * xx_o[l] + yy[k] * yy_o[l] + zz[k] * zz_o[l];
        polang = 57.2958 * acosf (dotProduct);
        if (dotProduct < -1.0)
          dotProduct = -1.0;
        if (dotProduct > 1.0)
          dotProduct = 1.0;
        isotropic->Fill ((double) polang, 1);

        dotProduct = xx[k] * xx_o[l] + yy[k] * yy_o[l] + zz[k] * zz_o[l];
        if (dotProduct < -1.0)
          dotProduct = -1.0;
        if (dotProduct > 1.0)
          dotProduct = 1.0;
        polang = 57.2958 * acosf (dotProduct);
        isotropic->Fill ((double) polang, 1);

        dotProduct = xx[l] * xx_o[l] + yy[l] * yy_o[l] + zz[l] * zz_o[l];
        if (dotProduct < -1.0)
          dotProduct = -1.0;
        if (dotProduct > 1.0)
          dotProduct = 1.0;
        polang = 57.2958 * acosf (dotProduct);
        isotropic->Fill ((double) polang, 1);

        dotProduct = xx[l] * xx_o[l] + yy[l] * yy_o[l] + zz[l] * zz_o[l];
        if (dotProduct < -1.0)
          dotProduct = -1.0;
        if (dotProduct > 1.0)
          dotProduct = 1.0;
        polang = 57.2958 * acosf (dotProduct);
        isotropic->Fill ((double) polang, 1);

      };

  /* save this one for next time */

  for (k = 0; k < nn; k++)
    {
      xx_o[k] = xx[k];
      yy_o[k] = yy[k];
      zz_o[k] = zz[k];
      cType_o[k] = cType[k];
    };
  nn_o = nn;

  /* done */

  if (Pars.CurEvNo <= Pars.NumToPrint)
    printf ("exit bin_angcor\n");

  return (0);

}
