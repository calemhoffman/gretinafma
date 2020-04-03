
ifstream inFile;
Float_t e0[10000000];
Float_t e1[10000000];
Float_t e2[10000000];
Float_t e3[10000000];
Float_t e4[10000000];
Float_t e5[10000000];
Float_t e6[10000000];
Float_t x[10000000];
Float_t m[10000000];
Float_t dt[10000000];
Float_t ge[10000000];
Float_t gid[10000000];
Float_t glabel[10000000];
Int_t gmult[10000000];
Float_t mlreturn[10000000];
Int_t event[10000000];
Int_t number = 0;

TTree *pytree;

TH2F *hgg;

Float_t mlCutMin = 0.8;
Float_t mlCutMax = 1.0;
Float_t modelCheckValue = 0.8;

void pyTorchReader() {

  hgg = new TH2F("hgg","hgg;ge;ge",4000,0,4000,4000,0,4000);

//inFile.open(Form("../machine_learning/code/PyTreeAverageSkinny_train.csv"));
inFile.open(Form("../machine_learning/code/output/pyTreeAverageFatH_tester.csv"));

  if( inFile.is_open() ) {
    while (1) {
      if (!inFile.good()) break;
      inFile >> event[number] >> e0[number] >> e1[number] >> e2[number]
       >> e3[number] >> e4[number] >> e5[number] >> e6[number]
       >> x[number] >> m[number] >> dt[number] >> gmult[number] >> ge[number]
       >> gid[number] >> glabel[number] >> mlreturn[number];
      if (number<1) { printf("%d[%d] %f %f %f\n",
       event[number],number,e0[number],e1[number],e2[number]);
       printf("%f %f %f %f\n",
       e3[number],e4[number],e5[number],e6[number]);
       printf("%f %f %d %f\n",
       x[number],m[number],gmult[number],ge[number]);
       printf("%f %f %f\n\n\n",gid[number],glabel[number],mlreturn[number]);
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
  Float_t py_mlreturn[100];
  Float_t py_gid[100];
  Float_t py_glabel[100];

  for (Int_t i=0;i<100;i++) {
    if (i<10) py_e[i]=0;
    py_m[i] = 0;
    py_ge[i] = 0;
    py_mlreturn[i] = 0;
    py_dt[i] = 0;
    py_gid[i] = -100;
    py_glabel[i] = -100;
  }

  TFile *fileOut = new TFile("pyTorchOutAverageFatH.root","RECREATE");
  pytree = new TTree("pytree","pytree");
  pytree->Branch("py_e",py_e,"py_e[10]/F");
  pytree->Branch("py_x",&py_x,"py_x/F");
  pytree->Branch("py_gmult",&py_gmult,"py_gmult/I");
  pytree->Branch("py_m",py_m,"py_m[py_gmult]/F");
  pytree->Branch("py_dt",py_dt,"py_dt[py_gmult]/F");
  pytree->Branch("py_ge",py_ge,"py_ge[py_gmult]/F");
  pytree->Branch("py_mlreturn",py_mlreturn,"py_mlreturn[py_gmult]/F");
  pytree->Branch("py_gid",py_gid,"py_gid[py_gmult]/F");
  pytree->Branch("py_glabel",py_glabel,"py_glabel[py_gmult]/F");

  for (Int_t i=0;i<number-2;i++) {
    //fill all the zeros
    py_e[0] = e0[i]; py_e[1] = e1[i]; py_e[2] = e2[i];
    py_x = x[i];
    py_m[0] = m[i];
    py_ge[0] = ge[i];
    py_mlreturn[0] = mlreturn[i];
    py_dt[0] = dt[i];
    py_gmult = 1;//gmult[i];
    py_glabel[0] = glabel[i];
    py_gid[0] = gid[i];

    for (Int_t j=i+1;j<i+gmult[i];j++) {
      if ( (TMath::Abs(py_e[0]-e0[j])<0.1) && (gmult[i]==gmult[j]) ) {
        py_m[py_gmult] = m[j];
        py_ge[py_gmult] = ge[j];
        py_mlreturn[py_gmult] = mlreturn[j];
        py_dt[py_gmult] = dt[j];
        py_gid[py_gmult] = gid[j];
        py_glabel[py_gmult] = glabel[j];
        py_gmult++;
      }
    }
    //fill tree and histograms
    pytree->Fill();
    //ADD gamma-gamma here
    //TODO - may need to pass dtime here to get cleaer coincidence
    //in root file now, so do TCUTG
    if (py_gmult>1) {
      for (Int_t i=0;i<py_gmult;i++){
        if (py_mlreturn[i]>mlCutMin && py_mlreturn[i]<mlCutMax) {
          for (Int_t j=i+1;j<py_gmult;j++) {
            if (py_mlreturn[j]>mlCutMin && py_mlreturn[j]<mlCutMax) {
              hgg->Fill(py_ge[i],py_ge[j]);
              hgg->Fill(py_ge[j],py_ge[i]);
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
      py_mlreturn[k] = 0;
      py_dt[k] = 0;
      py_gid[k] = -100;
      py_glabel[k] = -100;
    }
    py_gmult=0;
  }

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


  pytree->Write();
  hgg->Write();
  fileOut->Write();
  fileOut->Close();

//  TFile *fIn = new TFile("")

}
