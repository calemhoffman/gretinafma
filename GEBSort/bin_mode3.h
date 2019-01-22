/*-----------------------------------------------------*/
// Class to hold the DGSEVENT data
// Will be passed to TTree
#include "TMath.h"

class evtList {
 public:

  //Constructor
 evtList(int maxHits) {
    //All variables to be included in the TTree
    this->maxHits = maxHits;
    runNumber;
    numHits = maxHits;
    left = new float[maxHits];//raw energies for each
    right = new float[maxHits];
    up = new float[maxHits];
    down = new float[maxHits];
    e1 = new float[maxHits];
    e2 = new float[maxHits];
    e3 = new float[maxHits];
    tac = new float[maxHits];
    fmaDeltaTime = new float[maxHits];//trigger TS in seconds
    fmaMult = new int[10];
    gammaEnergy = new float[maxHits];
    gammaTimestamp = new float[maxHits];
    deltaTime = new float[maxHits];
    
};
  
  //Reset Function
  void Reset() {
    runNumber=TMath::QuietNaN();
    numHits=TMath::QuietNaN();
    gammaMult=TMath::QuietNaN();
    gebMult=TMath::QuietNaN();

    for (int i=0;i<maxHits;i++) {
      left[i] = TMath::QuietNaN();
      right[i] = TMath::QuietNaN();
      up[i] = TMath::QuietNaN();
      down[i] = TMath::QuietNaN();
      e1[i] = TMath::QuietNaN();
      e2[i] = TMath::QuietNaN();
      e3[i] = TMath::QuietNaN();
      tac[i] = TMath::QuietNaN();
      fmaDeltaTime[i] = TMath::QuietNaN();
      gammaEnergy[i] = TMath::QuietNaN();
      gammaTimestamp[i] = TMath::QuietNaN();
      deltaTime[i] = TMath::QuietNaN();
    }
    
    for (int i=0;i<10;i++)
      fmaMult[i] = TMath::QuietNaN();
    return;
  };
  
  //Members
  int maxHits;
  int runNumber;
  int numHits;
  float *left,*right,*up,*down; //ppac positions
  float *e1,*e2,*e3; //IC energies
  float *tac; //RF-PPAC TOF tac (may not be good)
  float *fmaDeltaTime;//TS from trigger (?)
  int *fmaMult;
  int gammaMult;
  float *gammaEnergy;
  float *gammaTimestamp;
  float *deltaTime;
  int gebMult;//New
  int *crysType;                                             /* typically: abcd1234 */
  int *crsyId;
  int *crsyNum;
  float *crysTot_e;
  long long int *crysTimestamp;
  long long *crsyTrigtime;
  float *crysT0;
  float *crysCfd;
  float *crysChisq;
  float *crysNormChisq;
  float *crysBaseline;
  unsigned int *crysTpad;
  float ** intX;
  float ** intY;
  float ** intZ;
  float ** intE;       /* here e refers to the fraction */
  int ** intSeg;                /* segment hit */
  float ** intSegEnery;         /* energy of hit segment */
  /* to ensure 8-byte alignment of struct */
  // DCR_INTPTS intpts[MAX_INTPTS];
  
};
