
ifstream inFile;
Float_t e0[50000000];
Float_t e1[50000000];
Float_t e2[50000000];
Float_t e3[50000000];
Float_t e4[50000000];
Float_t e5[50000000];
Float_t e6[50000000];
Float_t x[50000000];
Float_t m[50000000];
Float_t dt[50000000];
Float_t ge[50000000];
Float_t ga[50000000];
Float_t gid[50000000];
Float_t glabel[50000000];
Int_t gmult[50000000];
Float_t mlreturn[50000000];
Float_t cre[50000000];
Float_t ix[50000000];
Float_t iy[50000000];
Float_t iz[50000000];
Int_t event[50000000];
Int_t number = 0;

#define TRAIN 0 //1 for training to spit out ml stuff

TTree *pytree;

TH1F *hg[5];
TH2F *hgg[5];

Float_t mlCutMin[5] = {0.8,0.85,0.89,0.895,0.9};//New for NewW
//Float_t mlCutMin[5] = {0.35,0.38,0.4,0.5,0.8};//New for NewV
//Float_t mlCutMin[5] = {0.25,0.3,0.6,0.81,0.875};//five cuts for AveFat

//old 0.25,0.5,0.7,0.81,0.875
//Float_t mlCutMin[5] = {0.22,0.25,0.6,0.765,0.805};//five cuts for AveSkin
//Float_t mlCutMin[5] = {0.0,0.2,0.4,0.6,0.8};//five cuts for base
Float_t mlCutMax[5] = {1.0,1.0,1.0,1.0,1.0};
Float_t modelCheckValue = 0.5;

void pyTorchReader() {
for (Int_t ii=0;ii<5;ii++) {
  hgg[ii] = new TH2F(Form("hgg%d",ii),Form("hgg%d [ml>%.3f];ge;ge",ii,mlCutMin[ii]),
  4000,0,4000,4000,0,4000);
  hg[ii] = new TH1F(Form("hg%d",ii),Form("hg%d [ml>%.3f];ge;ge",ii,mlCutMin[ii]),
  4000,0,4000);
}

//inFile.open(Form("../machine_learning/code/PyTreeAverageSkinny_train.csv"));
inFile.open(Form("../machine_learning/code/output/pyTreeNew_tester.csv"));

  if( inFile.is_open() ) {
    while (1) {
      if (!inFile.good()) break;
      inFile >> event[number] >> e0[number] >> e1[number] >> e2[number]
       >> e3[number] >> e4[number] >> e5[number] >> e6[number]
       >> x[number] >> m[number] >> dt[number] >> gmult[number] >> ge[number]
       >> ga[number] >> gid[number] >> glabel[number] >> cre[number]
       >> ix[number] >> iy[number] >> iz[number] >> mlreturn[number];
      if (number<5) { printf("%d[%d] %f %f %f\n",
       event[number],number,e0[number],e1[number],e2[number]);
       printf("%f %f %f %f\n",
       e3[number],e4[number],e5[number],e6[number]);
       printf("%f %f %f %d %f\n",
       x[number],m[number],dt[number], gmult[number],ge[number]);
       printf("%f %f %f %f\n",ga[number],gid[number],glabel[number],cre[number]);
       printf("%f %f %f %f\n\n",ix[number],iy[number],iz[number],mlreturn[number]);
      }
      number++;
  }
  printf("... done reading file\n");
  } else { printf("... failed to read file\n");
  }
  printf("%d entries read\n",number-1);
  inFile.close();

  Float_t py_e[10];
  Float_t py_x = 0;
  Int_t py_gmult = 0;
  Float_t py_m[100];
  Float_t py_dt[100];
  Float_t py_ge[100];
  Float_t py_ga[100];
  Float_t py_mlreturn[100];
  Float_t py_gid[100];
  Float_t py_glabel[100];
  Float_t py_cre[100];
  Float_t py_ix[100];
  Float_t py_iy[100];
  Float_t py_iz[100];
  Float_t py_creab[100];

  for (Int_t i=0;i<100;i++) {
    if (i<10) py_e[i]=0;
    py_m[i] = 0;
    py_ge[i] = 0;
    py_ga[i] = 0;
    py_mlreturn[i] = 0;
    py_dt[i] = 0;
    py_gid[i] = -100;
    py_glabel[i] = -100;
    py_cre[i] = 0;
    py_ix[i] = 0;
    py_iy[i] = 0;
    py_iz[i] = 0;
    py_creab[i] = 0;
  }

  TFile *fileOut = new TFile("pyTorchOutNew.root","RECREATE");
  pytree = new TTree("pytree","pytree");
  pytree->Branch("py_e",py_e,"py_e[10]/F");
  pytree->Branch("py_x",&py_x,"py_x/F");
  pytree->Branch("py_gmult",&py_gmult,"py_gmult/I");
  pytree->Branch("py_m",py_m,"py_m[py_gmult]/F");
  pytree->Branch("py_dt",py_dt,"py_dt[py_gmult]/F");
  pytree->Branch("py_ge",py_ge,"py_ge[py_gmult]/F");
  pytree->Branch("py_ga",py_ga,"py_ga[py_gmult]/F");
  pytree->Branch("py_mlreturn",py_mlreturn,"py_mlreturn[py_gmult]/F");
  pytree->Branch("py_gid",py_gid,"py_gid[py_gmult]/F");
  pytree->Branch("py_glabel",py_glabel,"py_glabel[py_gmult]/F");
  pytree->Branch("py_cre",py_cre,"py_cre[py_gmult]/F");
  pytree->Branch("py_ix",py_ix,"py_ix[py_gmult]/F");
  pytree->Branch("py_iy",py_iy,"py_iy[py_gmult]/F");
  pytree->Branch("py_iz",py_iz,"py_iz[py_gmult]/F");
  pytree->Branch("py_creab",py_creab,"py_creab[py_gmult]/F");

  for (Int_t i=0;i<number-2;i++) {
    //fill all the zeros
    py_e[0] = e0[i]; py_e[1] = e1[i]; py_e[2] = e2[i];
    py_x = x[i];
    py_m[0] = m[i];
    py_ge[0] = ge[i];
    py_ga[0] = ga[i];
    py_mlreturn[0] = mlreturn[i];
    py_dt[0] = dt[i];
    py_gmult = 1;//gmult[i];
    py_glabel[0] = glabel[i];
    py_gid[0] = gid[i];
    py_cre[0] = cre[i];
    py_ix[0] = ix[i];
    py_iy[0] = iy[i];
    py_iz[0] = iz[i];

    for (Int_t j=i+1;j<i+gmult[i];j++) {
      if ( (TMath::Abs(py_e[0]-e0[j])<0.1) && (gmult[i]==gmult[j]) ) {
        py_m[py_gmult] = m[j];
        py_ge[py_gmult] = ge[j];
        py_ga[py_gmult] = ga[j];
        py_mlreturn[py_gmult] = mlreturn[j];
        py_dt[py_gmult] = dt[j];
        py_gid[py_gmult] = gid[j];
        py_glabel[py_gmult] = glabel[j];
        py_cre[py_gmult] = cre[j];
        py_ix[py_gmult] = ix[j];
        py_iy[py_gmult] = iy[j];
        py_iz[py_gmult] = iz[j];
        py_gmult++;
      }
    }
    //ADDBACK - could add the py_mlreturn cut here and loop all addback
    Float_t radAddBackTest = 10.0;//radius for AB
    Int_t addBackDopNum = 0;
    Float_t r2=0;
    Float_t radDiff[100][100];
    Float_t modCCdopfac[100];
    Float_t beta = 0.03375; //s38 from Fits
    Float_t mlreturnAB=0.2;
    //Float_t inRad[100];
    //second gmult loop to calc addback
    for (Int_t gebMultNum=0;gebMultNum<py_gmult;gebMultNum++) {

      addBackDopNum = gebMultNum;
      py_creab[gebMultNum] = 0;//py_cre[gebMultNum];
      //DOPPLER calculate
      modCCdopfac[gebMultNum] = TMath::Sqrt(1. - beta*beta) /
      (1.0 - beta * TMath::Cos(py_ga[gebMultNum]/180.*TMath::Pi()));

      if (py_mlreturn[gebMultNum] > mlreturnAB) {
        //AB
        py_creab[gebMultNum] = py_cre[gebMultNum];
        for (Int_t j=gebMultNum+1; j < py_gmult; j++ ) {
          r2 = (py_ix[gebMultNum] - py_ix[j])*(py_ix[gebMultNum] - py_ix[j])
            +(py_iy[gebMultNum] - py_iy[j])*(py_iy[gebMultNum] - py_iy[j])
            +(py_iz[gebMultNum] - py_iz[j])*(py_iz[gebMultNum] - py_iz[j]);
          radDiff[gebMultNum][j] = TMath::Sqrt(r2);
          // printf("I,J: %d,%d radDiff: %f, e[i]: %f, e[j]: %f\n",
          // gebMultNum,j,
          // radDiff[gebMultNum][j],
          // py_cre[gebMultNum], py_cre[j]);
          if ( (radDiff[gebMultNum][j] <= radAddBackTest) /*dtime check*/ )
          {
            py_creab[gebMultNum] += py_cre[j];
            if (py_cre[j] > py_cre[gebMultNum]) addBackDopNum = j;
            py_cre[j] = 0;
          } //radDiff if
        } //j++
        //printf("** py_creab[%d,%d]: %f\n\n",gebMultNum,addBackDopNum,py_creab[gebMultNum]);
      } //mlreturn
      if (py_creab[gebMultNum]!=0) {
      py_creab[gebMultNum] = py_creab[gebMultNum]/modCCdopfac[gebMultNum];//DOPPLER ** addBackDopNum should be used
      //printf("** py_creab(dop)[%d,%d]: %f\n\n",gebMultNum,addBackDopNum,py_creab[gebMultNum]);
      //crysTotAddBack[gebMultNum] = crysTotAddBack[gebMultNum] - (0.002*x);//X CORRECTION (from hxVg spectrum)
      //crysTotAddBack[gebMultNum] = crysTotAddBack[gebMultNum] + (e[0]-1625)*0.002488;//e[0] from he0Vg specrum
      }
    }//py_mult
    //fill tree and histograms
    pytree->Fill();
    //ADD gamma-gamma here
    //TODO - may need to pass dtime here to get cleaer coincidence
    //in root file now, so do TCUTG
    for (Int_t k=0;k<py_gmult;k++){
      for (Int_t l=0;l<5;l++) {
        if (py_mlreturn[k]>mlCutMin[l] && py_mlreturn[k]<mlCutMax[l]) {
          hg[l]->Fill(py_ge[k]);
        }
      }
    }

    if (py_gmult>1) {
      for (Int_t k=0;k<py_gmult;k++){
        for (Int_t j=k+1;j<py_gmult;j++) {
          for (Int_t l=0;l<5;l++) {
            if (py_mlreturn[k]>mlCutMin[l] && py_mlreturn[k]<mlCutMax[l]) {
              if (py_mlreturn[j]>mlCutMin[l] && py_mlreturn[j]<mlCutMax[l]) {
                hgg[l]->Fill(py_ge[k],py_ge[j]);
                hgg[l]->Fill(py_ge[j],py_ge[k]);
              }
            }
          }
        }
      }
    }
    //set event number
    i+=py_gmult-1;
    //cleanup
    for (Int_t k=0;k<100;k++) {
      if (k<10) {
        py_e[k]=0;
      }
      py_m[k] = 0;
      py_ge[k] = 0;
      py_ga[k] = 0;
      py_mlreturn[k] = 0;
      py_dt[k] = 0;
      py_gid[k] = -100;
      py_glabel[k] = -100;
      py_cre[k] = 0;
      py_ix[k] = 0;
      py_iy[k] = 0;
      py_iz[k] = 0;
      py_creab[k] = 0;
    }
    py_gmult=0;
  }

if (TRAIN==1) {
  //printf("%lld\n",pytree->GetEntries());
  Int_t truepos=0;
  Int_t falseneg=0;
  Int_t falsepos=0;
  Int_t trueneg=0;
  ULong64_t pyEntryNumber = pytree->GetEntries();
  printf("%lld entries\n",pyEntryNumber);
  printf("#modelcheck tp fn fp tn sum acc prec rec F1\n");
  for (Int_t mlSlice=0;mlSlice<20;mlSlice++) {
    // Float_t mlSliceMin = (Float_t)mlSlice*0.05;
    // Float_t mlScliceMax = mlSliceMin+0.05;
    modelCheckValue = 1.0 - (Float_t)mlSlice*0.05;
    //printf("SliceLimit: %f\n",modelCheckValue);
    printf("%.2f ",modelCheckValue);
    truepos=0;
    falseneg=0;
    falsepos=0;
    trueneg=0;
    for (Int_t entry=0;entry<pyEntryNumber;entry++) {
      pytree->GetEntry(entry);
      for (Int_t entry2=0;entry2<py_gmult;entry2++) {
        //printf("%f %f\n",py_gid[entry2],py_mlreturn[entry2]);
        if ( (py_gid[entry2]==1) && (py_mlreturn[entry2]>=modelCheckValue) ) truepos++;
        if ( (py_gid[entry2]==1) && (py_mlreturn[entry2]<modelCheckValue) ) falseneg++;
        if ( (py_gid[entry2]==0) && (py_mlreturn[entry2]>=modelCheckValue) ) falsepos++;
        if ( (py_gid[entry2]==0) && (py_mlreturn[entry2]<modelCheckValue) ) trueneg++;
      }
    }
    // printf("tp: %d, fn: %d, fp: %d, tn: %d\n",
    //         truepos,falseneg,falsepos,trueneg);
    printf("%d %d %d %d ",
    truepos,falseneg,falsepos,trueneg);

    Float_t accuracy = 0, precision = 0, recall=0, F1 = 0;
    Float_t sum=(Float_t)truepos+(Float_t)falseneg+(Float_t)falsepos+(Float_t)trueneg;
    accuracy = ( (Float_t)truepos+(Float_t)trueneg ) /
    ( sum );
    precision = ( (Float_t)truepos ) /
    ( (Float_t)truepos+(Float_t)falsepos );
    recall = ( (Float_t)truepos ) /
    ( (Float_t)truepos+(Float_t)falseneg );
    F1 = (2.0 * precision * recall) / (precision + recall);
    // printf("sum: %.0f, accuracy: %.3f, precision: %.3f, recall: %.3f, F1: %.3f\n\n",
    // sum,accuracy,precision,recall,F1);
    printf("%.0f %.3f %.3f %.3f %.3f\n",
    sum,accuracy,precision,recall,F1);
  }
}

  pytree->Write();
  for (Int_t i=0;i<5;i++) {
    hgg[i]->Write();
    hg[i]->Write();
  }
  fileOut->Write();
  fileOut->Close();

//  TFile *fIn = new TFile("")

}
