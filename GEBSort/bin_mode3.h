/*-----------------------------------------------------*/
// Class to hold the DGSEVENT data
// Will be passed to TTree
class evtList {
 public:

  //Constructor
 evtList(int maxHits) {
    //All variables to be included in the TTree
    this->maxHits = maxHits;
    numHits = maxHits;
    runNumber;
  };
  
  //Reset Function
  void Reset() {
    for (int i=0;(i<numHits&&i<maxHits);i++) {
      runNumber=0;
    }
    return;
  };

  //Members
  int maxHits;
  int numHits;
  int runNumber;
};
