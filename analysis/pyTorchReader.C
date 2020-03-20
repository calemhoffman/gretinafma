
ifstream inFile;
Float_t e0[1e6]
Float_t e1[1e6]
Float_t e2[1e6]
Float_t e3[1e6]
Float_t e4[1e6]
Float_t e5[1e6]
Float_t e6[1e6];
Float_t m[1e6];
Float_t ge[1e6];
Float_t gid[1e6];
Float_t glabel[1e6];
Int_t gmult[1e6];
Float_t mlreturn[1e6];
Int_t index[1e6];
Int_t number = 0;

void pyTorchReader() {

inFile.open(Form("../machine_learning/code/s38.csv");

if( inFile.is_open() ) {
  while (1) {
    if (!inFile.good()) break;
    inFile >> index[number] >> e0[number] >> e1[number] >> e2[number]
     >> e3[number] >> e4[number] >> e5[number] >> e6[number]
     >> x[number] >> m[number] >> gmult[number] >> ge[number]
     >> gid[number] >> glabel[number];
    number++;
}
printf("... done reading fit file\n");
} else { printf("... failed to read fit file\n");
}
}
