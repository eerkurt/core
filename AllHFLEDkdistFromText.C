

   /*******************************************************************************************
   ****** PROGRAM : AllHFLEDkdistFromText.C **************                                  ***
   *******************************************************                                  ***
   ***                                                                                      ***
   *** Author : Ersel Bedri Erkurt                                                          ***
   *** Date   : 2018                                                                        ***
   *** Place  : CERN & ITU                                                                  ***
   *** Program was written with C++ and ROOT                                                ***
   *** This program makes a distribution of all k values of 1728 HF PMTs from %_kdist.txt,  ***
   *** and also makes a gaus fit                                                            *** 
   ***                                                                                      ***
   ***                                                                                      ***
   ********************************************************************************************/

void AllHFLEDkdistFromText() {

  Int_t runno,qie,db;
  Double_t k;

  stringstream pathname1;
  pathname1<<"AllLEDkdist.root";
  TString dir1 = gSystem->UnixPathName(gInterpreter->GetCurrentMacroName());
  dir1.ReplaceAll("./AllkdistFromText.C","LEDNtuples/");
  TString fullpathname1 = dir1+pathname1.str().c_str();
  TFile *f1 = new TFile(fullpathname1,"RECREATE");

  TCanvas *c1 = new TCanvas("k dist","All LED k distribution",600,800);
  TH1D *allkdist = new TH1D("k dist","All LED k distribution",1728,0,2);

  TF1 *fit = new TF1("fit1","gaus",0,2);

  ifstream in;
  in.open("/Users/core/Desktop/!!!THESIS!!!/PMT ANALYSIS /PMTB904/PMTTESTANALYSIS/txt/B904/led_runlist.txt",ios::in);
  while(in>>runno) {
 
  stringstream pathname;
  pathname<<runno<<"_kdist.txt";
  TString dir = gSystem->UnixPathName(gInterpreter->GetCurrentMacroName());
  dir.ReplaceAll("./AllkdistFromText.C","LEDNtuples/");
  TString fullpathname = dir+pathname.str().c_str();
  ifstream in;
  in.open(fullpathname,ios::in);
  
  while(in>>runno>>qie>>db>>k) {

    allkdist->Fill(k);
    allkdist->SetLineColor(2);
    allkdist->GetXaxis()->SetTitle("k value");
    
  }
  }
  
  c1->cd();
  gStyle->SetOptStat(1111111);
  allkdist->Draw();
  fit->SetLineColor(kBlue);
  allkdist->Fit(fit,"R");
  // TF1 fit1 = (TF1*)allkdist->GetFunction("gaus");
  //  fit1->SetLineColor(kBlue);
  fit->Draw("same");

  
  c1->Write();
  f1->Write();
  
}
