

   /*******************************************************************************************
   ****** PROGRAM : HFLEDGainCorrelation.C ***************                                  ***
   *******************************************************                                  ***
   ***                                                                                      ***
   *** Author : Ersel Bedri Erkurt                                                          ***
   *** Date   : 2018                                                                        ***
   *** Place  : ITU & CERN                                                                  ***
   ***                                                                                      ***
   *** Program was written with C++ and ROOT                                                ***
   ***                                                                                      ***  
   *** This program creates one root file, namely %_HFLED.root, and makes a correlation     ***
   *** with PMT gain values in terms of different HVs                                       ***
   ***                                                                                      ***
   ***                                                                                      ***
   ********************************************************************************************/

#include <iostream>
#include <fstream>

using namespace std;
int runno;

void HFLEDGainCorrelation() {

  TFile *f = new TFile("HFLEDGainCorrelation.root","RECREATE");

  gStyle->SetOptStat("menrMR");
  TCanvas *c1 = new TCanvas("Gain Correlation","Gain Correlation",600,400);
  
  TH2F *hGAIN = new TH2F("Gain Correlation","Gain Correlation",1728,0,2700000,1728,0,2700000);
  hGAIN->SetMarkerStyle(8);
  hGAIN->SetMarkerColor(kRed);
  hGAIN->GetXaxis()->SetTitle("GAIN650");
  hGAIN->GetYaxis()->SetTitle("GAIN700");
  
  ifstream myin;
  myin.open("",ios::in);
  if(!(myin.good())){ cout<<"There is no available deneme.txt"<<endl;}

  TChain *chain = new TChain("TreeofGAINsforHVs");
 
  while(myin>>runno) 
    {
      chain->AddFile(Form("HFLED/LEDNtuples/%d_HFLED.root",runno));
    
      int nentries = (int)chain->GetEntries(0);
      cout<<"entries   "<<nentries<<endl;
    
      TLeaf *GAIN650 = chain->GetLeaf("GAIN650");
      TLeaf *GAIN700 = chain->GetLeaf("GAIN700");
  
      int count = 0;

      if(runno==3031 || runno ==3013 || runno==3045 || runno==2996) {
	for (int i=0; i<24; i++) {

	  count++;
	  GAIN650->GetBranch()->GetEntry(i);
	  GAIN700->GetBranch()->GetEntry(i);
	  hGAIN->Fill(GAIN650->GetValue(0),GAIN700->GetValue(0));
	  cout<<count<<"_"<<GAIN650->GetValue(0)<<endl;
	  cout<<count<<"_"<<GAIN700->GetValue(0)<<endl;

	}
      }
      else{
	for (int i=0; i<48; i++) {

	  count++;
	  GAIN650->GetBranch()->GetEntry(i);
	  GAIN700->GetBranch()->GetEntry(i);
	  hGAIN->Fill(GAIN650->GetValue(0),GAIN700->GetValue(0));
	  cout<<count<<"_"<<GAIN650->GetValue(0)<<endl;
	  cout<<count<<"_"<<GAIN700->GetValue(0)<<endl;

    
	}
      }
      c1->cd();
      hGAIN->Draw();
     
    }
  f->cd();
  c1->Write();

  f->Write();
}
