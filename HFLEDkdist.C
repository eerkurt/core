


 /*******************************************************************************************
 ****** PROGRAM : HFLEDkdist.C *************************                                  ***
 *******************************************************                                  ***
 ***                                                                                      ***
 *** Author : Ersel Bedri Erkurt                                                          ***
 *** Date   : 2018                                                                        ***
 *** Place  : ITU & CERN                                                                  ***
 *** Program was written with C++ and ROOT                                                ***
 ***                                                                                      ***
 *** This program creates one root file, namely %_kdist.root, and one text file,          ***
 *** namely %_kdist.txt, of results of k values of PMTs as Histograms.                    ***
 ***                                                                                      ***
 ********************************************************************************************/


void kdist() {

  Int_t runno;

  ifstream in1;
  in1.open("/Users/core/Desktop/!!!THESIS!!!/PMT ANALYSIS /PMTB904/PMTTESTANALYSIS/txt/B904/led_runlist.txt",ios::in);

  while(in1>>runno) {  

  stringstream pathname1;
  pathname1<<runno<<"_kdist.root";
  TString dir = gSystem->UnixPathName(gInterpreter->GetCurrentMacroName());
  dir.ReplaceAll("./kdist.C","LEDNtuples/");
  TString fullpathname1 = dir+pathname1.str().c_str();
  TFile *f1 = new TFile(fullpathname1,"RECREATE");
  pathname1.str("");
 
  TH1D *kdist = new TH1D("kdsit","k distribution",48,0.5,0.9);
 
  Int_t qie,db;
  Double_t k;

  stringstream pathname;
  pathname<<runno<<"_kdist.txt";
  TString fullpathname = dir+pathname.str().c_str();
  ifstream in;
  in.open(fullpathname,ios::in);
  pathname.str("");

  while(in>>runno>>qie>>db>>k) {

    cout<<k<<endl;

    kdist->Fill(k);
    kdist->SetLineColor(2);
    kdist->GetXaxis()->SetTitle("k values");

  }

  kdist->Draw();

  f1->Write();


  }
}
