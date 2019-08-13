
 /*******************************************************************************************
 ****** PROGRAM : HFB904LEDGain.C **********************                                  ***
 *******************************************************                                  ***
 ***                                                                                      ***
 *** Author : Ersel Bedri Erkurt                                                          ***
 *** Date   : 2018                                                                        ***
 *** Place  : ITU & CERN                                                                  ***
 ***                                                                                      ***
 *** Program was written with C++ and ROOT                                                ***
 ***                                                                                      ***
 *** This program creates one text file, namely B904LEDGAIN.txt, from TTree,              ***
 *** namely HFLEDInfo                                                                     ***
 ***                                                                                      ***
 ***                                                                                      ***
 ***                                                                                      ***
 ********************************************************************************************/


#include <iostream>
#include <fstream>

using namespace std;


void HFB904LEDGain() {

  char rootfile[100];
  int runno;

  ofstream out;
  out.open("/txt/B904LEDGAIN.txt",ios::out);
  
  ifstream input;
  input.open("/txt/led_runlist.txt",ios::in);
  if(!(input.good())) { cout<<"There is no led_runlist.txt"<<endl; }
 
  while(input>>runno) {
 
    sprintf(rootfile,"/HFLED/LEDNtuples/%d_LEDNtuples.root",runno);
  
    TFile *f = new TFile(rootfile);

    TTree *tree = f->Get("HFLEDInfo");
    //    tree->Print();

    int nentries =  tree->GetEntries();
    cout<<nentries<<endl;
    
    TLeaf *leaf650 = (TLeaf*)tree->GetLeaf("GAIN650");
    TLeaf *leaf700 = (TLeaf*)tree->GetLeaf("GAIN700");

    for(int i=0; i<nentries; i++) {
    
      leaf650->GetBranch()->GetEntry(i);
      leaf700->GetBranch()->GetEntry(i);
      
      out<<runno<<setw(18)<<leaf650->GetValue()<<setw(20)<<leaf700->GetValue()<<endl;
    
    }
  }
}
