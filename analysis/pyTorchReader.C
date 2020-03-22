
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
Float_t ge[10000000];
Float_t gid[10000000];
Float_t glabel[10000000];
Int_t gmult[10000000];
Float_t mlreturn[10000000];
Int_t event[10000000];
Int_t number = 0;

TTree *pytree;

void pyTorchReader() {



inFile.open(Form("../machine_learning/code/total.csv"));

  if( inFile.is_open() ) {
    while (1) {
      if (!inFile.good()) break;
      inFile >> event[number] >> e0[number] >> e1[number] >> e2[number]
       >> e3[number] >> e4[number] >> e5[number] >> e6[number]
       >> x[number] >> m[number] >> gmult[number] >> ge[number]
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
  Float_t py_ge[100];
  Float_t py_mlreturn[100];

  for (Int_t i=0;i<100;i++) {
    if (i<10) py_e[i]=0;
    py_m[i] = 0;
    py_ge[i] = 0;
    py_mlreturn[i] = 0;
  }

  TFile *fileOut = new TFile("pyTorchOut.root","RECREATE");
  pytree = new TTree("pytree","pytree");
  pytree->Branch("py_e",py_e,"py_e[10]/F");
  pytree->Branch("py_x",&py_x,"py_x/F");
  pytree->Branch("py_gmult",&py_gmult,"py_gmult/I");
  pytree->Branch("py_m",py_m,"py_m[py_gmult]/F");
  pytree->Branch("py_ge",py_ge,"py_ge[py_gmult]/F");
  pytree->Branch("py_mlreturn",py_mlreturn,"py_mlreturn[py_gmult]/F");

  for (Int_t i=0;i<number-2;i++) {
    //fill all the zeros
    py_e[0] = e0[i]; py_e[1] = e1[i]; py_e[2] = e2[i];
    py_x = x[i];
    py_m[0] = m[i];
    py_ge[0] = ge[i];
    py_mlreturn[0] = mlreturn[i];
    py_gmult = 1;//gmult[i];

    for (Int_t j=i+1;j<i+gmult[i];j++) {
      if ( (TMath::Abs(py_e[0]-e0[j])<0.1) && (gmult[i]==gmult[j]) ) {
        py_m[py_gmult] = m[j];
        py_ge[py_gmult] = ge[j];
        py_mlreturn[py_gmult] = mlreturn[j];
        py_gmult++;
      }
    }
    //fill tree and histograms
    pytree->Fill();
    //ADD gamma-gamma here

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
    }
    py_gmult=0;
  }

  pytree->Write();
  fileOut->Write();
  fileOut->Close();
}
