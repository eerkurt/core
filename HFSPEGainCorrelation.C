#include <iostream>
#include <fstream>

using namespace std;
int runno;

void HFSPEGainCorrelation() {


  TFile *f = new TFile("HFSPEGainCorrelation.root","RECREATE");
  gStyle->SetOptStat("menrMR");

  TCanvas *c1 = new TCanvas("Gain Correlation","Gain Correlation",600,400);
  
  TH2F *hGAIN = new TH2F("Gain Correlation","Gain Correlation",1680,0,2700000,1680,0,2700000);
  hGAIN->SetMarkerStyle(8);
  hGAIN->SetMarkerColor(kRed);
  hGAIN->GetXaxis()->SetTitle("GAIN650");
  hGAIN->GetYaxis()->SetTitle("GAIN700");
  
  ifstream myin;
  myin.open("/Users/core/Desktop/!!!THESIS!!!/PMT ANALYSIS /PMTTESTANALYSIS/txt/B904/spe_runlist.txt",ios::in);
  if(!(myin.good())){ cout<<"There is no available spe_runlist.txt"<<endl;}

  TChain *chain = new TChain("TreeofGAINsforHVs");
 
  while(myin>>runno) 
    {
      chain->AddFile(Form("/Users/core/Desktop/!!!THESIS!!!/PMT ANALYSIS /PMTTESTANALYSIS/SORTING/HFSPE/SPENtuples/%d_HFSPE.root",runno));

      int nentries = (int)chain->GetEntries(0);
      cout<<"entries   "<<nentries<<endl;
    
      TLeaf *GAIN650 = chain->GetLeaf("GAIN650");
      TLeaf *GAIN700 = chain->GetLeaf("GAIN700");
  
      int count = 0;

      if(runno==3012 || runno ==3030 || runno==3046 || runno==2995) {
	for (int i=0; i<24; i++) {

	  count++;
	  GAIN650->GetBranch()->GetEntry(i);
	  GAIN700->GetBranch()->GetEntry(i);
	  hGAIN->Fill(GAIN650->GetValue(0),GAIN700->GetValue(0));
	  cout<<count<<"_"<<GAIN650->GetValue(0)<<endl;
	  cout<<count<<"_"<<GAIN700->GetValue(0)<<endl;

	}
      }
      else if(runno==3096) { continue; }
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
