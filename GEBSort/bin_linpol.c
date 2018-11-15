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

#define NBINS 180
#define RAD2DEG 0.01745329
#define TEST3DUNIFORM 0


unsigned int seed;

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


/* pointers to ROOT spectra */


TH1D *lp_pol_ang;
TH1D *lp_compton_ang;
TH1D *lp_plane_ang;
TH1D *lp_plane_ang_r;
#if(TEST3DUNIFORM)
TH2F *SMAP_uni;
#endif

/* parameters */

extern PARS Pars;
extern EXCHANGE exchange;



/*-----------------------------------------------------*/

int
ranInsideCirle (double *u0, double *u1)
{
  /* declarations */

  double rr;

  rr = 2;
  while (rr > 1)
    {
      *u0 = 2 * (drand48 () - 0.5);
      *u1 = 2 * (drand48 () - 0.5);
      rr = (*u0) * (*u0) + (*u1) * (*u1);
    };

  /* done */

  return (0);


};

/*-----------------------------------------------------*/

int
ranVectorOnSphere (double *x0, double *x1, double *x2)
{

  /* see section 21.5.1 in Numerical Recipes book, page 1129 */
  /* generating vector on sphere is non trivial */

  /* declarations */

  double u0, u1;

  /* get a point within a cirle */

  ranInsideCirle (&u0, &u1);

  /* generate random points on sphere */

  *x0 = 2 * u0 * sqrt (1 - u0 * u0 - u1 * u1);
  *x1 = 2 * u1 * sqrt (1 - u0 * u0 - u1 * u1);
  *x2 = 1 - 2 * (u0 * u0 + u1 * u1);

  /* done */

  return (0);

};

/*-----------------------------------------------------*/

int
crossprod (double u1, double u2, double u3, double v1, double v2, double v3, double *s1, double *s2, double *s3)
{

  *s1 = u2 * v3 - u3 * v2;
  *s2 = u3 * v1 - u1 * v3;
  *s3 = u1 * v2 - u2 * v1;

  return (0);

};

/*-----------------------------------------------------*/

int
crossprod_alt (double a1, double b1, double c1, double a2, double b2, double c2, double *s1, double *s2, double *s3)
{

  /* CRC 22 ed, page 556 */

  *s1 = b1 * c2 - c1 * b2;
  *s2 = c1 * a1 - a1 * c2;
  *s3 = a1 * b2 - b1 * a2;

  return (0);

}


/*-----------------------------------------------------*/

double
dotproductangle (double u1, double u2, double u3, double v1, double v2, double v3)
{

  double polarAngle, dp;

  dp = u1 * v1 + u2 * v2 + u3 * v3;
  if (dp < -1.0)
    dp = -1.0;
  if (dp > 1.0)
    dp = 1.0;
  polarAngle = acos (dp);

  assert (polarAngle >= 0 && polarAngle <= (2 * M_PI));


  return (polarAngle);

}

/*-----------------------------------------------------*/

double
normvector (double *u1, double *u2, double *u3)
{

  double rr;

  rr = (*u1) * (*u1) + (*u2) * (*u2) + (*u3) * (*u3);
  rr = sqrt (rr);
  *u1 /= rr;
  *u2 /= rr;
  *u3 /= rr;

  return (rr);

}


/*-----------------------------------------------------*/

int
sup_linpol ()
{
  /* declarations */

  char str1[STRLEN], str2[STRLEN];
  TH1D *mkTH1D (char *, char *, int, double, double);
  TH2F *mkTH2F (char *, char *, int, double, double, int, double, double);
#if(TEST3DUNIFORM)
  float sX, sY, polAng, aziAng, rr;
  double xx, yy, zz;
  int i;
#endif

  /* prototype */

  int get_a_seed (unsigned int *);
  float findAzimuthFromCartesian (float, float, float);
  float findPolarFromCartesian (float, float, float, float *);

  sprintf (str1, "lp_pol_ang");
  sprintf (str2, "lp_pol_ang");
  lp_pol_ang = mkTH1D (str1, str2, NBINS, 0, 180);
  sprintf (str1, "angle");
  lp_pol_ang->SetXTitle (str1);
  sprintf (str1, "yield");
  lp_pol_ang->SetYTitle (str1);

  sprintf (str1, "lp_compton_ang");
  sprintf (str2, "lp_compton_ang");
  lp_compton_ang = mkTH1D (str1, str2, NBINS, 0, 180);
  sprintf (str1, "angle");
  lp_compton_ang->SetXTitle (str1);
  sprintf (str1, "yield");
  lp_compton_ang->SetYTitle (str1);

  sprintf (str1, "lp_plane_ang");
  sprintf (str2, "lp_plane_ang");
  lp_plane_ang = mkTH1D (str1, str2, NBINS, 0, 180);
  sprintf (str1, "angle");
  lp_plane_ang->SetXTitle (str1);
  sprintf (str1, "yield");
  lp_plane_ang->SetYTitle (str1);


  sprintf (str1, "lp_plane_ang_r");
  sprintf (str2, "lp_plane_ang_r");
  lp_plane_ang_r = mkTH1D (str1, str2, NBINS, 0, 180);
  sprintf (str1, "angle");
  lp_plane_ang_r->SetXTitle (str1);
  sprintf (str1, "yield");
  lp_plane_ang_r->SetYTitle (str1);

#if(TEST3DUNIFORM)
  sprintf (str1, "SMAP_uni");
  sprintf (str2, "SMAP_uni");
  SMAP_uni = mkTH2F (str1, str2, 720, -180, 180, 360, 0, 180);
  sprintf (str1, "Azimuth");
  SMAP_uni->SetXTitle (str1);
  sprintf (str1, "Polar");
  SMAP_uni->SetYTitle (str1);
#endif

  /* list what we have */

  printf (" we have define the following spectra:\n");

  Pars.wlist = gDirectory->GetList ();
  Pars.wlist->Print ();

  /* initialize random number generator */

  get_a_seed (&seed);
  srand (seed);

#if(TEST3DUNIFORM)

  /* generate a uniform worldmap:: test uniformity */

  for (i = 0; i < 10000000; i++)
    {
      ranVectorOnSphere (&xx, &yy, &zz);
      polAng = findPolarFromCartesian ((float) xx, (float) yy, (float) zz, &rr);
      aziAng = findAzimuthFromCartesian ((float) xx, (float) yy, (float) zz);
      sX = aziAng * sinf (polAng) / RAD2DEG;
      sY = polAng / RAD2DEG;    /* + 1.5; */
      printf ("__ %f,%f\n", sX, sY);
      if (sX >= -180 && sX <= 180 && sY >= 0 && sY <= 180)
        SMAP_uni->Fill (sX, sY, 1);
    };

#endif

  return (0);

};

/* ----------------------------------------------------------------- */

int
bin_linpol (GEB_EVENT * GEB_event)
{

  /* declarations */

  char str[128];
  int pass, i, j, nn;
  TRACKED_GAMMA_HIT *grh;
  double rr, dp, doppler_factor, rr_scat;
  double x1, y1, z1;

  double polarAngle, comptonAngle, planeAngle;

  double n0_x, n0_y, n0_z;
  double n1_x, n1_y, n1_z;
  double n2_x, n2_y, n2_z;

  double nv_pp_x, nv_pp_y, nv_pp_z;
  double nv_csp_x, nv_csp_y, nv_csp_z;

  /* prototypes */

  int GebTypeStr (int type, char str[]);

  if (Pars.CurEvNo <= Pars.NumToPrint)
    printf ("entered bin_linpol:\n");


  if (Pars.linpol_mode == 0)
    {
      printf ("you must specify the linpol_mode\n");
      exit (1);
    };

  pass = 0;
  while (pass < 2)
    {

      /*--------------------------------*/
      /* determine the 'beam' direction */
      /*--------------------------------*/


      if (pass == 0)
        {

          if (Pars.linpol_mode == LINPOL_BEAM)
            {

              if (Pars.CurEvNo <= Pars.NumToPrint)
                printf ("using LINPOL_BEAM\n");

              /* beam direction normal vector */
              /* trivial for now... */

              n0_x = 0;
              n0_y = 0;
              n0_z = 1.0;
              rr = normvector (&n0_x, &n0_y, &n0_z);

            }
          else if (Pars.linpol_mode == LINPOL_SOURCE)
            {

              if (Pars.CurEvNo <= Pars.NumToPrint)
                printf ("using LINPOL_SOURCE\n");

              /* use direction of the (first) source gamma ray */

              nn = 0;
              for (i = 0; i < GEB_event->mult; i++)
                {

                  if (GEB_event->ptgd[i]->type == GEB_TYPE_TRACK)
                    {
                      grh = (TRACKED_GAMMA_HIT *) GEB_event->ptinp[i];
                      for (j = 0; j < grh->ngam; j++)
                        {
                          if (grh->gr[j].fom > Pars.linpol_FOMlo && grh->gr[j].fom < Pars.linpol_FOMhi)
                            if (abs (Pars.linpol_source_e - grh->gr[j].esum) < Pars.linpol_source_de)
                              {
                                /* we found the other gamma ray */
                                n0_x = grh->gr[j].x0 - Pars.target_x;
                                n0_y = grh->gr[j].y0 - Pars.target_y;
                                n0_z = grh->gr[j].z0 - Pars.target_z;
                                rr = normvector (&n0_x, &n0_y, &n0_z);
                                nn++;
                              };
                        };
                    };

                };

              /*if we didn't find the 'other' gamma ray, quit */

              if (nn != 1)
                return (0);

            }
        };


      if (pass == 1)
        {
          if (Pars.CurEvNo <= Pars.NumToPrint)
            printf ("using LINPOL_RANDOM\n");

          ranVectorOnSphere (&n0_x, &n0_y, &n0_z);
          rr = normvector (&n0_x, &n0_y, &n0_z);
        };

      /* loop through the coincidence event */

      nn = 0;
      for (i = 0; i < GEB_event->mult; i++)
        {

          if (GEB_event->ptgd[i]->type == GEB_TYPE_TRACK)
            {

              if (Pars.CurEvNo <= Pars.NumToPrint)
                {
                  GebTypeStr (GEB_event->ptgd[i]->type, str);
                  printf ("bin_linpol, %2i> %2i, %s, TS=%lli\n", i, GEB_event->ptgd[i]->type, str,
                          GEB_event->ptgd[i]->timestamp);
                }

              grh = (TRACKED_GAMMA_HIT *) GEB_event->ptinp[i];


              /* process all gamma rays with at */
              /* least two interaction points */

              for (j = 0; j < grh->ngam; j++)
                if (grh->gr[j].ndet >= 2)
                  if (grh->gr[j].fom > Pars.linpol_FOMlo && grh->gr[j].fom < Pars.linpol_FOMhi)
                    {

                      /* print tracked gamma rays */

                      if (Pars.CurEvNo <= Pars.NumToPrint)
                        {

                          printf ("number of gamma rays: %i\n", grh->ngam);
                          printf ("esum=%6.3f, ", grh->gr[j].esum);
                          printf ("ndet (#interactions)=%2i, ", grh->gr[j].ndet);
                          printf ("fom=%6.3f, ", grh->gr[j].fom);
                          printf ("tracked=%i\n", grh->gr[j].tracked);
                          printf ("1'th hit: (%6.3f, %6.3f, %6.3f), e= %6.3f\n", grh->gr[j].x0, grh->gr[j].y0,
                                  grh->gr[j].z0, grh->gr[j].e0);
                          printf ("2'nd hit: (%6.3f, %6.3f, %6.3f), e= %6.3f\n", grh->gr[j].x1, grh->gr[j].y1,
                                  grh->gr[j].z1, grh->gr[j].e1);

                        };

                      /* first interaction point normal vector */

                      n1_x = grh->gr[j].x0 - Pars.target_x;
                      n1_y = grh->gr[j].y0 - Pars.target_y;
                      n1_z = grh->gr[j].z0 - Pars.target_z;
                      rr = normvector (&n1_x, &n1_y, &n1_z);

                      /* second interaction point normal vector */

                      n2_x = grh->gr[j].x1 - grh->gr[j].x0;
                      n2_y = grh->gr[j].y1 - grh->gr[j].y0;
                      n2_z = grh->gr[j].z1 - grh->gr[j].z0;
                      rr_scat = normvector (&n2_x, &n2_y, &n2_z);

                      /* find gamma ray angle */

                      polarAngle = dotproductangle (n0_x, n0_y, n0_z, n1_x, n1_y, n1_z);
                      if (Pars.CurEvNo <= Pars.NumToPrint)
                        printf ("polar angle of gamma ray (wrt beam axis): %5.2f (deg)\n", polarAngle / M_PI * 180);

                      /* doppler correct the gamma ray energy */

                      rr = 1.0 - Pars.beta * Pars.beta;
                      doppler_factor = sqrt (rr) / (1.0 - Pars.beta * cos (polarAngle));
                      grh->gr[j].esum /= doppler_factor;

                      /* find compton scatter angle */

                      comptonAngle = dotproductangle (n1_x, n1_y, n1_z, n2_x, n2_y, n2_z);
                      if (Pars.CurEvNo <= Pars.NumToPrint)
                        printf ("compton scattering angle: %5.2f (deg)\n", comptonAngle / M_PI * 180);

                      /*------------------------*/
                      /* use polarization plane */
                      /*------------------------*/

                      /* Normal vector for polarization plane */
                      /* The polarization plane is normal to reaction plane */
                      /* Hence the double cross product */

                      crossprod (n0_x, n0_y, n0_z, n1_x, n1_y, n1_z, &x1, &y1, &z1);
                      crossprod (x1, y1, z1, n1_x, n1_y, n1_z, &nv_pp_x, &nv_pp_y, &nv_pp_z);

                      /* normal vector for Compton scattering plane */

                      crossprod (n1_x, n1_y, n1_z, n2_x, n2_y, n2_z, &nv_csp_x, &nv_csp_y, &nv_csp_z);

                      /* angle between polarization plane */
                      /* and Compton scattering plane */

                      planeAngle = dotproductangle (nv_pp_x, nv_pp_y, nv_pp_z, nv_csp_x, nv_csp_y, nv_csp_z);

                      if (Pars.CurEvNo <= Pars.NumToPrint)
                        printf ("[1]angle between planes: %5.2f (deg)\n", planeAngle / M_PI * 180);


                      /* bin angles */

                      if ((float) rr_scat >= Pars.linpol_rrlo)
                        if ((float) rr_scat <= Pars.linpol_rrhi)
                          if ((float) polarAngle >= Pars.linpol_polrangelo)
                            if ((float) polarAngle <= Pars.linpol_polrangehi)
                              if (abs (Pars.linpol_ee - grh->gr[j].esum) <= Pars.linpol_de)
                                if ((float) comptonAngle >= Pars.linpol_comptonrangelo)
                                  if ((float) comptonAngle <= Pars.linpol_comptonrangehi)
                                    {
                                      if (pass == 0)
                                        {
                                          lp_pol_ang->Fill (polarAngle / M_PI * 180, 1);
                                          lp_compton_ang->Fill (comptonAngle / M_PI * 180, 1);
                                          lp_plane_ang->Fill (planeAngle / M_PI * 180, 1);
                                        };
                                      if (pass == 1)
                                        lp_plane_ang_r->Fill (planeAngle / M_PI * 180, 1);
                                    };

                    };


            };


        };

//      printf ("%i -> ", pass);
      pass++;
//      printf ("%i\n", pass);

    };


  /* done */

  if (Pars.CurEvNo <= Pars.NumToPrint)
    printf ("exit bin_linpol\n");

  return (0);

}
