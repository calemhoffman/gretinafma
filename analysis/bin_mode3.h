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
    //gDeltaTime = new float[maxHits][100];

    crysType = new int[maxHits];
    crysId = new int[maxHits];
    crysNum = new int[maxHits];
    crysTot_e = new float[maxHits];
    crysTimestamp = new long long int[maxHits];
    crysTrigtime = new long long[maxHits];
    crysT0 = new float[maxHits];
    crysCfd = new float[maxHits];
    crysChisq = new float[maxHits];
    crysNormChisq = new float[maxHits];
    crysBaseline = new float[maxHits];
    crysTpad = new unsigned int[maxHits];
    crysPolAngle = new float[maxHits];

    intMaxX = new float[maxHits];
    intMaxY = new float[maxHits];
    intMaxZ = new float[maxHits];
    intMaxE = new float[maxHits];
    intMaxSeg = new int[maxHits];
    intMaxSegE = new float[maxHits];
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
      for (int j=0;j<100;j++)
        gDeltaTime[i][j] = TMath::QuietNaN();

      crysType[i] = TMath::QuietNaN();
      crysId[i] = TMath::QuietNaN();
      crysNum[i] = TMath::QuietNaN();
      crysTot_e[i] = TMath::QuietNaN();
      crysTimestamp[i] = TMath::QuietNaN();
      crysTrigtime[i] = TMath::QuietNaN();
      crysT0[i] = TMath::QuietNaN();
      crysCfd[i] = TMath::QuietNaN();
      crysChisq[i] = TMath::QuietNaN();
      crysNormChisq[i] = TMath::QuietNaN();
      crysBaseline[i] = TMath::QuietNaN();
      crysTpad[i] = TMath::QuietNaN();
      crysPolAngle[i] = TMath::QuietNaN();

      intMaxX[i] = TMath::QuietNaN();
      intMaxY[i] = TMath::QuietNaN();
      intMaxZ[i] = TMath::QuietNaN();
      intMaxE[i] = TMath::QuietNaN();
      intMaxSeg[i] = TMath::QuietNaN();
      intMaxSegE[i] = TMath::QuietNaN();

      //not initializing as expected...
      for (int j=0;j<20;j++) {
      	intX[i][j] = TMath::QuietNaN();
      	intY[i][j] = TMath::QuietNaN();
      	intZ[i][j] = TMath::QuietNaN();
       	intE[i][j] = TMath::QuietNaN();
       	intSeg[i][j] = TMath::QuietNaN();
       	intSegEnergy[i][j] = TMath::QuietNaN();
      }
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
  int gDeltaTime[100][100];
  //------------------//
  int gebMult;//New
  int *crysType;                                             /* typically: abcd1234 */
  int *crysId;
  int *crysNum;
  float *crysTot_e;
  long long int *crysTimestamp;
  long long *crysTrigtime;
  float *crysT0;
  float *crysCfd;
  float *crysChisq;
  float *crysNormChisq;
  float *crysBaseline;
  unsigned int *crysTpad;
  float *crysPolAngle;
  float *intMaxX;
  float *intMaxY;
  float *intMaxZ;
  float *intMaxE;       /* here e refers to the fraction */
  int *intMaxSeg;                /* segment hit */
  float *intMaxSegE;
  //-------------------//
  float intX[100][20];
  float intY[100][20];
  float intZ[100][20];
  float intE[100][20];       /* here e refers to the fraction */
  int intSeg[100][20];                /* segment hit */
  float intSegEnergy[100][20];         /* energy of hit segment */
  /* to ensure 8-byte alignment of struct */
  // DCR_INTPTS intpts[MAX_INTPTS];

};
