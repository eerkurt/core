

   /*******************************************************************************************
   ****** PROGRAM : AllHFLEDkdist.C **********************                                  ***
   *******************************************************                                  ***
   ***                                                                                      ***
   *** Author : Ersel Bedri Erkurt                                                          ***
   *** Date   : 2018                                                                        ***
   *** Place  : ITU & CERN                                                                  ***
   *** Program was written with C++ and ROOT                                                ***
   *** This program creates a distribution of k values for one run, 48 HF PMTs              ***
   ***                                                                                      ***
   ***                                                                                      ***
   ********************************************************************************************/

void HFLEDkdist() {

  Int_t runno;
  char rootfile[100];

  TH1D *allkdist = new TH1D("kdist","all kdist",50,0,2);

  ifstream in;
  in.open("",ios::in);
  
  while(in>>runno) {

  sprintf(rootfile,"/Users/core/Desktop/!!!THESIS!!!/PMT ANALYSIS /PMTB904/PMTTESTANALYSIS/SORTING/HFLED/LEDNtuples/%d_kdist.root",runno);  
  TFile *f1 = new TFile(rootfile);

  TH1D *kdist = (TH1D*)f1->Get("kdsit");

  Double_t k = kdist->GetMean();

  allkdist->Fill(k);
  allkdist->SetLineColor(2);
  allkdist->GetXaxis()->SetTitle("k value");
   
  cout<<k<<endl;

  }

  allkdist->Draw();
}
