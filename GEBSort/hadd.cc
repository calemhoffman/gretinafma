/*

  This macro will add histograms from a list of root files and write them
  to a target root file. The target file is newly created and must not be
  identical to one of the source files.

  Author: Sven A. Schmidt, sven.schmidt@cern.ch
  Date:   13.2.2001

  This code is based on the hadd.C example by Rene Brun and Dirk Geppert,
  which had a problem with directories more than one level deep.
  (see macro hadd_old.C for this previous implementation).
  
  The macro from Sven has been enhanced by 
     Anne-Sylvie Nicollerat <Anne-Sylvie.Nicollerat@cern.ch>
   to automatically add Trees (via a chain of trees).
  
  To use this macro, modify the file names in function hadd.
  
  NB: This macro is provided as a tutorial.
      Use $ROOTSYS/bin/hadd to merge many histogram files

 */


#include <string.h>
#include "TChain.h"
#include "TFile.h"
#include "TH1.h"
#include "TTree.h"
#include "TKey.h"
#include <iostream>

TList *FileList;
TFile *Target;

void MergeRootfile( TDirectory *target, TList *sourcelist );


void hadd() {
   // in an interactive ROOT session, edit the file names
   // Target and FileList, then
   // root > .L hadd.C
   // root > hadd()

  Target = TFile::Open( "ROOT_FILES/sum_100.root", "RECREATE" );

  FileList = new TList();

//FileList->Add( TFile::Open("./ROOT_FILES/run3.root") );
//FileList->Add( TFile::Open("./ROOT_FILES/run38.root") );

// diak 1



//FileList->Add( TFile::Open("./ROOT_FILES/run7.root") );
//FileList->Add( TFile::Open("./ROOT_FILES/run8.root") );
//FileList->Add( TFile::Open("./ROOT_FILES/run9.root") );
//FileList->Add( TFile::Open("./ROOT_FILES/run10.root") );
//FileList->Add( TFile::Open("./ROOT_FILES/run11.root") );
//FileList->Add( TFile::Open("./ROOT_FILES/run12.root") );
//FileList->Add( TFile::Open("./ROOT_FILES/run13.root") );
//FileList->Add( TFile::Open("./ROOT_FILES/run14.root") );
//FileList->Add( TFile::Open("./ROOT_FILES/run15.root") );

// disk 2
/* BEFORE TARGET POSITION CHANGE, cuts in nuclei not optimized */
//FileList->Add( TFile::Open("./ROOT_FILES/run78.root") );
//FileList->Add( TFile::Open("./ROOT_FILES/run79.root") );
//FileList->Add( TFile::Open("./ROOT_FILES/run81.root") );
//FileList->Add( TFile::Open("./ROOT_FILES/run82.root") );
//FileList->Add( TFile::Open("./ROOT_FILES/run83.root") );
//FileList->Add( TFile::Open("./ROOT_FILES/run84.root") );
//FileList->Add( TFile::Open("./ROOT_FILES/run85.root") );
//FileList->Add( TFile::Open("./ROOT_FILES/run86.root") );
//FileList->Add( TFile::Open("./ROOT_FILES/run87.root") );
//FileList->Add( TFile::Open("./ROOT_FILES/run88.root") );
//FileList->Add( TFile::Open("./ROOT_FILES/run89.root") );
//FileList->Add( TFile::Open("./ROOT_FILES/run90.root") );
//FileList->Add( TFile::Open("./ROOT_FILES/run91.root") );
//FileList->Add( TFile::Open("./ROOT_FILES/run92.root") );
//FileList->Add( TFile::Open("./ROOT_FILES/run93.root") );
//FileList->Add( TFile::Open("./ROOT_FILES/run94.root") );

/* AFTER TARGET POSITION CHANGE, cuts in nuclei made with run99 */
//FileList->Add( TFile::Open("./ROOT_FILES/run99.root") );
FileList->Add( TFile::Open("./ROOT_FILES/run100.root") );
FileList->Add( TFile::Open("./ROOT_FILES/run101.root") );
FileList->Add( TFile::Open("./ROOT_FILES/run102.root") );
FileList->Add( TFile::Open("./ROOT_FILES/run103.root") );
FileList->Add( TFile::Open("./ROOT_FILES/run104.root") );
FileList->Add( TFile::Open("./ROOT_FILES/run105.root") );
FileList->Add( TFile::Open("./ROOT_FILES/run106.root") );
FileList->Add( TFile::Open("./ROOT_FILES/run107.root") );
FileList->Add( TFile::Open("./ROOT_FILES/run108.root") );
FileList->Add( TFile::Open("./ROOT_FILES/run109.root") );

FileList->Add( TFile::Open("./ROOT_FILES/run110.root") );
FileList->Add( TFile::Open("./ROOT_FILES/run111.root") );
FileList->Add( TFile::Open("./ROOT_FILES/run112.root") );
FileList->Add( TFile::Open("./ROOT_FILES/run113.root") );
FileList->Add( TFile::Open("./ROOT_FILES/run114.root") );
FileList->Add( TFile::Open("./ROOT_FILES/run115.root") );
FileList->Add( TFile::Open("./ROOT_FILES/run116.root") );
FileList->Add( TFile::Open("./ROOT_FILES/run117.root") );
FileList->Add( TFile::Open("./ROOT_FILES/run118.root") );
FileList->Add( TFile::Open("./ROOT_FILES/run119.root") );

FileList->Add( TFile::Open("./ROOT_FILES/run120.root") );
FileList->Add( TFile::Open("./ROOT_FILES/run121.root") );
FileList->Add( TFile::Open("./ROOT_FILES/run122.root") );
FileList->Add( TFile::Open("./ROOT_FILES/run123.root") );
FileList->Add( TFile::Open("./ROOT_FILES/run124.root") );
FileList->Add( TFile::Open("./ROOT_FILES/run125.root") );
FileList->Add( TFile::Open("./ROOT_FILES/run126.root") );
FileList->Add( TFile::Open("./ROOT_FILES/run127.root") );
FileList->Add( TFile::Open("./ROOT_FILES/run128.root") );
FileList->Add( TFile::Open("./ROOT_FILES/run129.root") );

FileList->Add( TFile::Open("./ROOT_FILES/run130.root") );
FileList->Add( TFile::Open("./ROOT_FILES/run131.root") );
FileList->Add( TFile::Open("./ROOT_FILES/run132.root") );
FileList->Add( TFile::Open("./ROOT_FILES/run133.root") );
FileList->Add( TFile::Open("./ROOT_FILES/run134.root") );
FileList->Add( TFile::Open("./ROOT_FILES/run136.root") );
FileList->Add( TFile::Open("./ROOT_FILES/run137.root") );
FileList->Add( TFile::Open("./ROOT_FILES/run138.root") );
FileList->Add( TFile::Open("./ROOT_FILES/run139.root") );

FileList->Add( TFile::Open("./ROOT_FILES/run140.root") );
FileList->Add( TFile::Open("./ROOT_FILES/run141.root") );
FileList->Add( TFile::Open("./ROOT_FILES/run142.root") );
FileList->Add( TFile::Open("./ROOT_FILES/run143.root") );
FileList->Add( TFile::Open("./ROOT_FILES/run144.root") );
FileList->Add( TFile::Open("./ROOT_FILES/run145.root") );
FileList->Add( TFile::Open("./ROOT_FILES/run146.root") );
FileList->Add( TFile::Open("./ROOT_FILES/run147.root") );
FileList->Add( TFile::Open("./ROOT_FILES/run148.root") );
FileList->Add( TFile::Open("./ROOT_FILES/run149.root") );

FileList->Add( TFile::Open("./ROOT_FILES/run150.root") );
FileList->Add( TFile::Open("./ROOT_FILES/run151.root") );
FileList->Add( TFile::Open("./ROOT_FILES/run152.root") );
FileList->Add( TFile::Open("./ROOT_FILES/run153.root") );
FileList->Add( TFile::Open("./ROOT_FILES/run154.root") );
FileList->Add( TFile::Open("./ROOT_FILES/run155.root") );
FileList->Add( TFile::Open("./ROOT_FILES/run156.root") );
FileList->Add( TFile::Open("./ROOT_FILES/run157.root") );
FileList->Add( TFile::Open("./ROOT_FILES/run158.root") );

FileList->Add( TFile::Open("./ROOT_FILES/run161.root") );
FileList->Add( TFile::Open("./ROOT_FILES/run162.root") );
FileList->Add( TFile::Open("./ROOT_FILES/run163.root") );
//FileList->Add( TFile::Open("./ROOT_FILES/run164.root") );
//FileList->Add( TFile::Open("./ROOT_FILES/run165.root") );
//FileList->Add( TFile::Open("./ROOT_FILES/run167.root") );
//FileList->Add( TFile::Open("./ROOT_FILES/run168.root") );
//FileList->Add( TFile::Open("./ROOT_FILES/run169.root") );

  MergeRootfile( Target, FileList );

}   

void MergeRootfile( TDirectory *target, TList *sourcelist ) {

  cout << "Target path: " << target->GetPath() << endl;
  TString path( (char*)strstr( target->GetPath(), ":" ) );
  path.Remove( 0, 2 );

  TFile *first_source = (TFile*)sourcelist->First();
  first_source->cd( path );
  TDirectory *current_sourcedir = gDirectory;

  // loop over all keys in this directory
  TChain *globChain = 0;
  TIter nextkey( current_sourcedir->GetListOfKeys() );
  TKey *key;
  while ( (key = (TKey*)nextkey())) {

    // read object from first source file
    first_source->cd( path );
    TObject *obj = key->ReadObj();

    if ( obj->IsA()->InheritsFrom( "TH1" ) ) {
      // descendant of TH1 -> merge it

      cout << "Merging histogram " << obj->GetName() << endl;
      TH1 *h1 = (TH1*)obj;

      // loop over all source files and add the content of the
      // correspondant histogram to the one pointed to by "h1"
      TFile *nextsource = (TFile*)sourcelist->After( first_source );
      while ( nextsource ) {
        
        // make sure we are at the correct directory level by cd'ing to path
        nextsource->cd( path );
        TH1 *h2 = (TH1*)gDirectory->Get( h1->GetName() );
        if ( h2 ) {
          h1->Add( h2 );
          delete h2; // don't know if this is necessary, i.e. if 
                     // h2 is created by the call to gDirectory above.
        }

        nextsource = (TFile*)sourcelist->After( nextsource );
      }
    }
    else if ( obj->IsA()->InheritsFrom( "TTree" ) ) {
      
      // loop over all source files create a chain of Trees "globChain"
      const char* obj_name= obj->GetName();

      globChain = new TChain(obj_name);
      globChain->Add(first_source->GetName());
      TFile *nextsource = (TFile*)sourcelist->After( first_source );
      const char* file_name = nextsource->GetName();
      cout << "file name  " << file_name << endl;
     while ( nextsource ) {
     	  
       globChain->Add(nextsource->GetName());
       nextsource = (TFile*)sourcelist->After( nextsource );
     }

    } else if ( obj->IsA()->InheritsFrom( "TDirectory" ) ) {
      // it's a subdirectory

      cout << "Found subdirectory " << obj->GetName() << endl;

      // create a new subdir of same name and title in the target file
      target->cd();
      TDirectory *newdir = target->mkdir( obj->GetName(), obj->GetTitle() 
);

      // newdir is now the starting point of another round of merging
      // newdir still knows its depth within the target file via
      // GetPath(), so we can still figure out where we are in the recursion
      MergeRootfile( newdir, sourcelist );

    } else {

      // object is of no type that we know or can handle
      cout << "Unknown object type, name: " 
           << obj->GetName() << " title: " << obj->GetTitle() << endl;
    }

    // now write the merged histogram (which is "in" obj) to the target file
    // note that this will just store obj in the current directory level,
    // which is not persistent until the complete directory itself is stored
    // by "target->Write()" below
    if ( obj ) {
      target->cd();

      //!!if the object is a tree, it is stored in globChain...
	if(obj->IsA()->InheritsFrom( "TTree" ))
	  globChain->Write( key->GetName() );
	else
	obj->Write( key->GetName() );
    }

  } // while ( ( TKey *key = (TKey*)nextkey() ) )

  // save modifications to target file
  target->Write();

}
