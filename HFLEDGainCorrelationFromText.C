
      /*******************************************************************************************
      ****** PROGRAM : HFLEDGainCorrelationFromText.C *******                                  ***
      *******************************************************                                  ***
      ***                                                                                      ***
      *** Author : Ersel Bedri Erkurt                                                          ***
      *** Date   : 2018                                                                        ***
      *** Place  : ITU & CERN                                                                  ***
      ***                                                                                      ***
      *** Program was written with C++ and ROOT                                                ***
      ***                                                                                      ***
      *** This program creates one text file, namely ALLLEDGAINs.txt, and one root file,       ***
      *** namely HFLEDGainCorrelationFromText.root, and makes a correlation with               ***
      *** PMT gain values in terms of different HVs from data within %d_LEDGAINHV.txt          ***
      ***                                                                                      ***
      ***                                                                                      ***
      ********************************************************************************************/

#include <iostream>

#include <iostream>
#include <fstream>

using namespace std;

void HFLEDGainCorrelationFromText() {

  int count =0;
  double GAIN650Sums=0, GAIN650Mean;
  double GAIN700Sums=0, GAIN700Mean;
  double GAIN650,GAIN700;
  char list[200];
  int runno;

  ofstream out;
  out.open("/Users/core/Desktop/!!!THESIS!!!/PMT ANALYSIS /PMTTESTANALYSIS/SORTING/HFLED/LEDNtuples/ALLLEDGAINs.txt",ios::out);

  TFile *f = new TFile("HFLEDGainCorrelationFromText.root","RECREATE");
  TCanvas *c1= new TCanvas("GAIN Correlation","GAIN Correlation",600,400);

  TH2D *hGAIN = new TH2D("GAIN Correlation","GAIN Correlation",1728,0,2700000,1728,0,2700000);
  hGAIN->SetMarkerColor(kRed);
  hGAIN->SetMarkerStyle(8);
  hGAIN->GetXaxis()->SetTitle("GAIN650");
  hGAIN->GetYaxis()->SetTitle("GAIN700");

  ifstream input;
  input.open("/Users/core/Desktop/!!!THESIS!!!/PMT ANALYSIS /PMTTESTANALYSIS/txt/B904/led_runlist.txt",ios::in);

  while(input>>runno) {

    sprintf(list,"/Users/core/Desktop/!!!THESIS!!!/PMT ANALYSIS /PMTTESTANALYSIS/SORTING/HFLED/LEDNtuples/%d_LEDGAINHV.txt",runno);
    
    ifstream in;
    stringstream ntuplesrunno;
    ntuplesrunno<<list;
    in.open(ntuplesrunno.str().c_str(),ios::in);
    ntuplesrunno.str("");


    ifstream in1;
    in1.open("LEDRunConf.txt");
  
    while(in>>GAIN650>>GAIN700) {
     
      count++;     
      cout<<count<<"___"<<runno<<"_"<<"GAIN650 = "<<GAIN650<<endl;
      GAIN650Sums += GAIN650;
      cout<<count<<"___"<<runno<<"_"<<"GAIN700 = "<<GAIN700<<endl;
      GAIN700Sums += GAIN700;

      hGAIN->Fill(GAIN650,GAIN700);
      out<<GAIN650<<setw(18)<<GAIN700<<endl;

    }

    cout<<"GAIN650Sumsfor_"<<runno<<"_"<<GAIN650Sums<<endl;
    cout<<"GAIN700Sumsfor_"<<runno<<"_"<<GAIN700Sums<<endl;

  }  
  
  GAIN650Mean = GAIN650Sums/count;
  GAIN700Mean = GAIN700Sums/count;

  cout<<"GAIN650Mean = "<<GAIN650Mean<<endl;
  cout<<"GAIN700Mean = "<<GAIN700Mean<<endl;

  c1->cd();
  hGAIN->Draw();

  f->cd();
  c1->Write();
  }
