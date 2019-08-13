

     /*******************************************************************************************
      ****** PROGRAM : HFLEDAnalyzer.C **********************                                  ***
      *******************************************************                                  ***
      ***                                                                                      ***
      *** Author : Ersel Bedri Erkurt                                                          ***
      *** Date   : 2018                                                                        ***
      *** Place  : ITU & CERN                                                                  ***
      *** Program was written with C++ and ROOT                                                ***
      ***                                                                                      ***
      *** This program creates some text files of results of some characteristics of PMTs,     ***
      *** and shows us the reults of some analyses of those as Ntuples and Histograms.         ***
      ***                                                                                      ***
      *** #Analyses for LED runs                                                               ***
      *** a - Channels vs GAIN for DB0 and DB1 at 650V                                         ***
      *** b - Channels vs GAIN for DB0 and DB1 at 700V                                         ***
      *** c - GAIN vs HVs                                                                      ***
      *** d - Gain Correlation vs HVs                                                          ***
      *** e - Gain Correlation for DBs                                                         ***
      *** f - Gains Correlation at HVs in different DBs                                        ***
      *** g - TTreeofGAINs                                                                     ***
      *** h - NtuplesofGAINs                                                                   ***
      *** j - NtuplesofGAINsfor650V                                                            ***
      *** k - NtuplesofGAINsfor700V                                                            ***
      *** l - TTreeofGAINsforHVs                                                               ***
      *** m - NtuplesofGAINsforHVs                                                             ***
      *** n - GAINforHVsandDBs                                                                 ***
      *** p - Gain Correlation in different DBs at 650V                                        ***
      *** r - Gain Correlation in different DBs at 700V                                        ***
      *** s - Gain Correlation in different HVs at DB1                                         ***
      *** t - Gain Correlation in different HVs at DB0                                         ***
      ***                                                                                      ***
      ********************************************************************************************/

#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TF1.h>
#include <iomanip>
#include <TROOT.h>
#include <TRint.h>
#include <TChain.h>
#include <TF1.h>
#include <TMath.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

char rootfile[200];
int qie,depth,ieta;
double GAINfor650,GAINfor700;
double GAINfor650DB0,GAINfor700DB0,GAINfor650DB1,GAINfor700DB1;
double GAIN650DB0,GAIN650DB1,GAIN700DB0,GAIN700DB1;                                                                                                                              
double calib,GAIN;
double GAINfor650db0,GAINfor700db0,GAINfor650db1,GAINfor700db1;
double LEDMEAN650,PEDMEAN650,LEDRMS650,PEDRMS650,TRUEMEAN650,TRUERMS650,NPE650,Charge650,GAIN650,Rel_TRUEMEAN650,Rel_NPE650,Rel_Charge650,Rel_GAIN650,calib650;
int qie650,ieta650,depth650;
double TRUEMEAN700,TRUERMS700,PEDMEAN700,LEDMEAN700,LEDRMS700,PEDRMS700,NPE700,Rel_NPE700,Charge700,Rel_Charge700,GAIN700,Rel_TRUEMEAN700,Rel_GAIN700,calib700;
int qie700,ieta700,depth700;
int runno;

typedef struct {

  double LEDMEAN650[48];
  double PEDMEAN650[48];
  double LEDRMS650[48];
  double PEDRMS650[48]; 
  double TRUEMEAN650[48]; 
  double TRUERMS650[48];
  double  NPE650[48]; 
  double Charge650[48]; 
  double GAIN650[48];
  double Rel_TRUEMEAN650[48]; 
  double Rel_NPE650[48];
  double  Rel_Charge650[48];
  double Rel_GAIN650[48];
  int qie650[48];
  int ieta650[48];
  int depth650[48];
  double calib650[48];

} HFLED650;

HFLED650 B904LED650;

typedef struct {

  double LEDMEAN700[48];
  double PEDMEAN700[48];
  double LEDRMS700[48];
  double PEDRMS700[48];
  double TRUEMEAN700[48];
  double TRUERMS700[48];
  double  NPE700[48];
  double Charge700[48];
  double GAIN700[48];
  double Rel_TRUEMEAN700[48];
  double Rel_NPE700[48];
  double  Rel_Charge700[48];
  double Rel_GAIN700[48];
  int qie700[48];
  int ieta700[48];
  int depth700[48];
  double calib700[48];


} HFLED700;

HFLED700 B904LED700;


void HFLEDInfo() {
  
  stringstream outfile11;
  outfile11<<runno<<"_LEDNtuples.root";
  TFile *f6 = new TFile(outfile11.str().c_str(),"RECREATE");
  outfile11.str("");
  
  TTree *tree1 = new TTree("HFLEDInfo","HFLEDInfo");

  ifstream in;
  stringstream hfledinfo;
  hfledinfo<<runno<<"_HFLED650Info.txt";
  in.open(hfledinfo.str().c_str(),ios::in);
  if(!(in.good())) {cout<<"There is no hfledinfo.txt"<<endl;}
  hfledinfo.str("");

  ifstream in1;
  stringstream hfledinfo1;
  hfledinfo1<<runno<<"_HFLED700Info.txt";
  in1.open(hfledinfo1.str().c_str(),ios::in);
  if(!(in1.good())) {cout<<"There is no hfledinfo.txt"<<endl;}
  hfledinfo1.str("");

  int i = -1;
  while(in>>LEDMEAN650>>PEDMEAN650>>LEDRMS650>>PEDRMS650>>TRUEMEAN650>>TRUERMS650>>NPE650>>Charge650>>GAIN650>>Rel_TRUEMEAN650>>Rel_NPE650>>Rel_Charge650>>Rel_GAIN650>>qie650>>ieta650>>depth650>>calib650) {


    //    cout<<GAIN650<<endl;


    tree1->Branch("B904LED650Info",&B904LED650,"LEDMEAN650[48]/D:PEDMEAN650[48]/D:LEDRMS650[48]/D:PEDRMS650[48]/D:TRUEMEAN650[48]/D:TRUERMS650[48]/D:NPE650[48]/D:Charge650[48]/D:GAIN650[48]/D:Rel_TRUEMEAN650[48]/D:Rel_NPE650[48]/D:Rel_Charge650[48]/D:Rel_GAIN650[48]/D:qie650[48]/I:ieta650[48]/I:depth650[48]/I:calib650[48]/D");
    
    i++;
    B904LED650.LEDMEAN650[i] = LEDMEAN650;
    B904LED650.PEDMEAN650[i] = PEDMEAN650;
    B904LED650.LEDRMS650[i] = LEDRMS650;
    B904LED650.PEDRMS650[i] = PEDRMS650;
    B904LED650.TRUEMEAN650[i] = TRUEMEAN650;
    B904LED650.TRUERMS650[i] = TRUERMS650;
    B904LED650.NPE650[i] = NPE650;
    B904LED650.Charge650[i] = Charge650;
    B904LED650.GAIN650[i] = GAIN650;
    B904LED650.Rel_TRUEMEAN650[i] = Rel_TRUEMEAN650;
    B904LED650.Rel_NPE650[i] = Rel_NPE650;
    B904LED650.Rel_Charge650[i] = Rel_Charge650;
    B904LED650.Rel_GAIN650[i] = Rel_GAIN650;
    B904LED650.qie650[i] = qie650;
    B904LED650.ieta650[i] = ieta650;
    B904LED650.depth650[i] = depth650;
    B904LED650.calib650[i] = calib650;

  }

  int j = -1;
  while(in1>>LEDMEAN700>>PEDMEAN700>>LEDRMS700>>PEDRMS700>>TRUEMEAN700>>TRUERMS700>>NPE700>>Charge700>>GAIN700>>Rel_TRUEMEAN700>>Rel_NPE700>>Rel_Charge700>>Rel_GAIN700>>qie700>>ieta700>>depth700>>calib700) {


    //  cout<<GAIN700<<endl;
    //    cout<<qie700<<endl;

    tree1->Branch("B904LED700Info",&B904LED700,"LEDMEAN700[48]/D:PEDMEAN700[48]/D:LEDRMS700[48]/D:PEDRMS700[48]/D:TRUEMEAN700[48]/D:TRUERMS700[48]/D:NPE700[48]/D:Charge700[48]/D:GAIN700[48]/D:Rel_TRUEMEAN700[48]/D:Rel_NPE700[48]/D:Rel_Charge700[48]/D:Rel_GAIN700[48]/D:qie700[48]/I:ieta700[48]/I:depth700[48]/I:calib700[48]/D");

    j++;
    B904LED700.LEDMEAN700[j] = LEDMEAN700;
    B904LED700.PEDMEAN700[j] = PEDMEAN700;
    B904LED700.LEDRMS700[j] = LEDRMS700;
    B904LED700.PEDRMS700[j] = PEDRMS700;
    B904LED700.TRUEMEAN700[j] = TRUEMEAN700;
    B904LED700.TRUERMS700[j] =TRUERMS700;
    B904LED700.NPE700[j] = NPE700;
    B904LED700.Charge700[j] = Charge700;
    B904LED700.GAIN700[j] = GAIN700;
    B904LED700.Rel_TRUEMEAN700[j] = Rel_TRUEMEAN700;
    B904LED700.Rel_NPE700[j] = Rel_NPE700;
    B904LED700.Rel_Charge700[j] = Rel_Charge700;
    B904LED700.Rel_GAIN700[j] = Rel_GAIN700;
    B904LED700.qie700[j] = qie700;
    B904LED700.ieta700[j] = ieta700;
    B904LED700.depth700[j] = depth700;
    B904LED700.calib700[j] = calib700;


  }

  tree1->Fill();


  f6->Write();

}


/*void HFLEDGAINAnalysisforHVandDB() {

  if(runno == 3013 || runno == 3031 || runno == 3045 || runno == 2996) {

    TTree *tree4 = new TTree("GAINforHVsandDBs","GAIN for HVs and DBs");

    TCanvas *c6 = new TCanvas("GAIN Correlation in different HVs at DBs","GAIN Correlation in different HVs at DBs",600,400);

    TH2D *GAINHV1 = new TH2D("GAIN Correlation in different HVs at DB0","GAIN Correlation in different HVs at DB0",48,0,2700000,48,0,2700000);

    stringstream runnumber2;
    runnumber2<<runno<<"_LEDGAINHVDB_map.txt";
    ifstream myin;
    myin.open(runnumber2.str().c_str(),ios::in);
    runnumber2.str("");

    while(myin>>GAIN650DB0>>GAIN700DB0>>qie>>ieta>>depth) {

      tree4->Branch("GAIN650DB0",&GAIN650DB0,"GAIN650DB0/D");
      tree4->Branch("GAIN700DB0",&GAIN700DB0,"GAIN700DB0/D");

      GAINHV1->Fill(GAIN650DB0,GAIN700DB0);
      GAINHV1->SetMarkerColor(kRed);
      GAINHV1->SetFillColor(2);
      GAINHV1->SetMarkerStyle(8);
      GAINHV1->GetXaxis()->SetTitle("GAIN650DB0");
      GAINHV1->GetYaxis()->SetTitle("GAIN700DB0");

      tree4->Fill();
    }

    c6->cd();
    GAINHV1->Draw();
    c6->Write();
    
  }
    
    else{

  TTree *tree4 = new TTree("GAINforHVsandDBs","GAIN for HVs and DBs");

  TCanvas *c5 = new TCanvas("GAIN Correlation in different DBs at HVs","GAIN Correlation in different DBs at HVs",600,400);
  TCanvas *c6 = new TCanvas("GAIN Correlation in different HVs at DBs","GAIN Correlation in different HVs at DBs",600,400);

  TH2D *GAIN650 = new TH2D("GAIN Correlation in different DBs for 650","GAIN Correlation in different DBs for 650",24,0,2700000,24,0,2700000);
  TH2D *GAIN700 = new TH2D("GAIN Correlation in different DBs for 700","GAIN Correlation in different DBs for 700",24,0,2700000,24,0,2700000);
  TH2D *GAINHV2 = new TH2D("GAIN Correlation in different HVs at DB1","GAIN Correlation in different HVs at DB1",48,0,2700000,48,0,2700000);
  TH2D *GAINHV1 = new TH2D("GAIN Correlation in different HVs at DB0","GAIN Correlation in different HVs at DB0",48,0,2700000,48,0,2700000);

  stringstream runnumber2;
  runnumber2<<runno<<"_LEDGAINHVDB_map.txt";
  ifstream myin;
  myin.open(runnumber2.str().c_str(),ios::in);
  runnumber2.str("");

  while(myin>>GAIN650DB0>>GAIN700DB0>>GAIN650DB1>>GAIN700DB1>>qie>>ieta>>depth) {
    
    tree4->Branch("GAIN650DB0",&GAIN650DB0,"GAIN650DB0/D");
    tree4->Branch("GAIN650DB1",&GAIN650DB1,"GAIN650DB1/D");
    tree4->Branch("GAIN700DB0",&GAIN700DB0,"GAIN700DB0/D");
    tree4->Branch("GAIN700DB1",&GAIN700DB1,"GAIN700DB1/D");
     
    //GAIN Correlation in different DBs for 650V                                                                                                                                                 
    GAIN650->Fill(GAIN650DB0,GAIN650DB1);
    GAIN650->SetMarkerColor(kRed);
    GAIN650->SetFillColor(3);
    GAIN650->SetMarkerStyle(8);
    GAIN650->GetXaxis()->SetTitle("GAIN650DB0");
    GAIN650->GetYaxis()->SetTitle("GAIN650DB1");
    //GAIN Correlation in different DBs for 700V 
    GAIN700->Fill(GAIN700DB0,GAIN700DB1);
    GAIN700->SetMarkerColor(kBlue);
    GAIN700->SetFillColor(2);
    GAIN700->SetMarkerStyle(8);
    GAIN700->GetXaxis()->SetTitle("GAIN700DB0");
    GAIN700->GetYaxis()->SetTitle("GAIN700DB1");
    
    //GAIN Correlation in different HV for DB0                                                                                                                                                       
    GAINHV1->Fill(GAIN650DB0,GAIN700DB0);
    GAINHV1->SetMarkerColor(kRed);
    GAINHV1->SetFillColor(2);
    GAINHV1->SetMarkerStyle(8);
    GAINHV1->GetXaxis()->SetTitle("GAIN650DB0");
    GAINHV1->GetYaxis()->SetTitle("GAIN700DB0");
    //GAIN Correlation in different HV for DB1                                                                                                                                                       
    GAINHV2->Fill(GAIN650DB1,GAIN700DB1);
    GAINHV2->SetMarkerColor(kBlue);
    GAINHV2->SetFillColor(3);
    GAINHV2->SetMarkerStyle(8);
    GAINHV2->GetXaxis()->SetTitle("GAIN650DB1");
    GAINHV2->GetYaxis()->SetTitle("GAIN700DB1");
    
    tree4->Fill(); 
  }

  c5->cd();
  GAIN650->Draw();
  GAIN700->Draw("same");

  c6->cd();
  GAINHV1->Draw();
  GAINHV2->Draw("same");
  
  c5->Write();
  c6->Write();

  //tree1->Write();

    }

}
*/
void HFLEDGAINAnalysisforHV() {

  double GAIN650,GAIN700;

  TCanvas *c7 = new TCanvas("GAINCorrelation","GAINCorrelation",600,400);

  TTree *tree2 = new TTree("TreeofGAINsforHVs","The Tree of gain of pmt's for HVs");
  TNtuple *ntuple = new TNtuple("NtupleofGAINsforHVs","GAIN for HVs","GAIN650:GAIN700");
  TH2F *GAINforHV = new TH2F("GAINCorrelationindifferentHVs","GAINCorrelation in different HVs",96,0,2700000,96,0,2700000);

  tree2->Branch("GAIN650",&GAIN650,"GAIN650/D");
  tree2->Branch("GAIN700",&GAIN700,"GAIN700/D");

  stringstream runnumber3;
  runnumber3<<runno<<"_LEDGAINHV.txt";
  ifstream myin2;
  myin2.open(runnumber3.str().c_str(),ios::in);
  runnumber3.str("");

  while(myin2>>GAIN650>>Rel_GAIN650>>GAIN700>>Rel_GAIN700) {

    GAINforHV->Fill(GAIN650,GAIN700);
    GAINforHV->SetFillColor(2);
    GAINforHV->SetMarkerColor(kRed);
    GAINforHV->SetMarkerStyle(8);
    GAINforHV->GetXaxis()->SetTitle("GAIN650");
    GAINforHV->GetYaxis()->SetTitle("GAIN700");

    tree2->Fill();
    ntuple->Fill(GAIN650,GAIN700);
  }

  c7->cd();
  GAINforHV->Draw();

  c7->Write();
  //tree2->Write();
  //ntuple-Write();
} 

void HFLEDGAINAnalysis() {


  sprintf(rootfile,"/Users/core/Desktop/!!!THESIS!!!/PMT ANALYSIS /PMTTESTANALYSIS/SORTING/HFLED/LED_ROOTFILES/Run_%d.root",runno);
  TFile *f = new TFile(rootfile);

  stringstream outfile3;
  outfile3<<runno<<"_HFLED.root";
  TFile *f5 = new TFile(outfile3.str().c_str(),"RECREATE");
  outfile3.str("");
  
  gStyle->SetOptStat("nemrRM"); // "nemr" is the default 
   
  TCanvas *c1 = new TCanvas("c1","Ch vs Gain 650V",600,400);
  TCanvas *c2 = new TCanvas("c2","Ch vs Gain 700V",600,400);
  TCanvas *c3 = new TCanvas("c3","PMT Gains at different HVs",600,400);
  //TCanvas *c4 = new TCanvas("GAIN Correlation vs HV","GAIN Correlation vs HV",600,400);

  int HV[] = {650,700};

  //TH3F *GAINHVCorr;
  //  TH2F *HistGains[2];
  //TH2F *HistGain[2][2];
  TH2F *GAINHV;
  TH2F *HistGains650;
  TH2F* HistGains700;
  TH2F *HistGain6500;
  TH2F *HistGain6501;
  TH2F *HistGain7000;
  TH2F *HistGain7001;

  // TH2F *GAIN_650;
  // TH2F *GAIN_700; 
  //  TH3F *GAINHVCorr2;
  //TH3F *GAINHVCorr1;
  
  TTree *tree = new TTree("TreeofGAINs","The Tree of Anaylsises");
  TNtuple *ntuple = new TNtuple("NtupleofGAINs","GAIN","GAIN");
  TNtuple *ntuple1 = new TNtuple("NtupleofGAINsfor650","ntuple for pmt's gain","Gain650");
  TNtuple *ntuple2 = new TNtuple("NtupleofGAINsfor700","ntuple for pmt's gain","Gain700");
  

  tree->Branch("GAIN",&GAIN,"GAIN/D");

  //GAIN_650 = new TH2F("h1","GAIN 650V",48,500,800,48,0,2700000);
  // GAIN_700 = new TH2F("h2","GAIN 700V",48,500,800,48,0,2700000);
  GAINHV = new TH2F("h3","Gain vs HV",96,500,800,96,0,2700000);
  HistGains650 = new TH2F("histgains650","Ch vs Gain 650",48,0,50,48,0,2700000);
  HistGains700 = new TH2F("histgains700","Ch vs Gain 700",48,0,50,48,0,2700000);
  HistGain6500 = new TH2F("histgain6500","Ch vs Gain 650 DB0",48,0,50,48,0,2700000);
  HistGain6501 = new TH2F("histgain6501","Ch vs Gain 650 DB1",48,0,50,48,0,2700000);
  HistGain7000 = new TH2F("histgain7000","Ch vs Gain 700 DB0",48,0,50,48,0,2700000);
  HistGain7001 = new TH2F("histgain7001","Ch vs Gain 700 DB1",48,0,50,48,0,2700000);

  //  GAINHVCorr = new TH3F("GAIN Correlation vs HVs","GAIN Correlation vs HVs",96,0,2700000,96,0,2700000,96,500,800);
  // GAINHVCorr1 = new TH3F("GAIN Correlation vs 650","GAIN Correlation vs 650",96,0,2700000,96,0,2700000,96,500,800);
  //GAINHVCorr2 = new TH3F("GAIN Correlation vs 700","GAIN Correlation vs 700",96,0,2700000,96,0,2700000,96,500,800);


  /*  stringstream voltage_db;
  stringstream voltage;
  for(int hv=0;hv<2;hv++) {
    for(int db=0; db<2; db++) {
      voltage_db<<HV[hv]<<"_"<<db<<"GainVsChannel";
      voltage<<HV[hv]<<"Gain Vs Channel";
      HistGain[hv][db]= new TH2F(voltage_db.str().c_str(),voltage_db.str().c_str(),48,0,50,48,0,2700000);
      HistGains[hv]= new TH2F(voltage.str().c_str(),voltage.str().c_str(),48,0,50,48,0,2700000);
      voltage_db.str("");
      voltage.str("");
    }
  }
  */

  stringstream runnumber1;
  runnumber1<<runno<<"_LEDGAINALL.txt";
  ofstream myfile;
  myfile.open(runnumber1.str().c_str());
  runnumber1.str("");

  stringstream runnumber2;
  runnumber2<<runno<<"_LEDGAINHVDB_map.txt";
  ofstream myfile2;
  myfile2.open(runnumber2.str().c_str());  
  runnumber2.str("");


  stringstream runnumber3;
  runnumber3<<runno<<"_LEDGAINHV.txt";
  ofstream myfile3;
  myfile3.open(runnumber3.str().c_str());
  runnumber3.str("");


  stringstream runnumber4;
  runnumber4<<runno<<"_HFLED650Info.txt";
  ofstream myfile4;
  myfile4.open(runnumber4.str().c_str());
  runnumber4.str("");
  

  stringstream runnumber5;
  runnumber5<<runno<<"_HFLED700Info.txt";
  ofstream myfile5;
  myfile5.open(runnumber5.str().c_str());
  runnumber5.str("");  
  
  int count = 0;
  
  ifstream ink;
  ink.open("//Users/core/Desktop/!!!THESIS!!!/PMT ANALYSIS /PMTTESTANALYSIS/txt/B904/Calib_constant.txt",ios::in); 
  if(!(ink.good())) { cout<<"There is no Calib_constant.txt"<<endl; }
  
  ifstream input("/Users/core/Desktop/!!!THESIS!!!/PMT ANALYSIS /PMTTESTANALYSIS/txt/B904/map.txt",ios::in);
  if (input.fail()){cout<<"map.txt is not available"<<endl;}
  
  if(runno == 3013 || runno == 3031 || runno == 3045 || runno == 2996) {

    while( input>>qie>>ieta>>depth ) {

      for(int db=0;db<1;db++) {

	ink>>calib;

	for(int hv=0;hv<2;hv++) {

	  // count++;                                                                                                                           
	  // cout<<count;                                                                                                                                                         

	  TString histnameLED,histnamePED;
	  stringstream ledname,pedname;
	  histnameLED.Form("/Analyzer/QIEsSumLED%d_QiECh_%d_DBOX_%d_eta_%d_D_%d",HV[hv],qie,db,ieta,depth);
	  histnamePED.Form("/Analyzer/QIEsSumPED%d_QiECh_%d_DBOX_%d_eta_%d_D_%d",HV[hv],qie,db,ieta,depth);
	  pedname<<histnamePED;
	  ledname<<histnameLED;

	  //      cout<<histnameLED<<endl; 
	  TH1F *HistLED = (TH1F*)f->Get(ledname.str().c_str());
	  TH1F *HistPED = (TH1F*)f->Get(pedname.str().c_str());
	  ledname.str("");
	  pedname.str("");
	  //      cout<<ledname.str().c_str()<<endl;                                                                                   
	  if(HistLED && HistPED) {

	    double LEDMEAN;
	    double PEDMEAN;
	    double LEDRMS;
	    double PEDRMS;

	    LEDMEAN = HistLED->GetMean();
	    PEDMEAN = HistPED->GetMean();
	    LEDRMS = HistLED->GetRMS();
	    PEDRMS = HistPED->GetRMS();


	    double TRUEMEAN = LEDMEAN - PEDMEAN;
	    double TRUERMS = sqrt(pow(LEDRMS,2)-pow(PEDRMS,2));
	    double NPE = 1.15*(pow(TRUEMEAN,2)/pow(TRUERMS,2));// 1.15+-0.05 = ENF(Excess Noise Factor)                                                                                
	    double Charge = NPE*1.6*pow(10,(-19));
	    GAIN = (TRUEMEAN*2.6)*pow(10,(-15))/Charge;

	    double Rel_TRUEMEAN = (LEDMEAN-PEDMEAN)/calib;
	    double Rel_NPE = 1.15*(pow(Rel_TRUEMEAN,2)/pow(TRUERMS,2));
	    double Rel_Charge = Rel_NPE*1.6*pow(10,(-19));
	    double Rel_GAIN = (Rel_TRUEMEAN*2.6*10000)/(Rel_NPE*1.6);


	    if(hv==0) {
	      myfile4.width(7);
	      myfile4<<LEDMEAN<<setw(10)<<PEDMEAN<<setw(10)<<LEDRMS<<setw(10)<<PEDRMS<<setw(10)<<TRUEMEAN<<setw(10)<<TRUERMS<<setw(10)<<NPE<<setw(14)<<Charge<<setw(13)<<GAIN<<setw(13)<<Rel_TRUEMEAN<<setw(10)<<Rel_NPE<<setw(14)<<Rel_Charge<<setw(15)<<Rel_GAIN<<setw(8)<<qie<<setw(4)<<ieta<<setw(4)<<depth<<setw(10)<<calib<<endl;
	    }

	    if(hv==1) {
	      myfile5.width(7);
	      myfile5<<LEDMEAN<<setw(10)<<PEDMEAN<<setw(10)<<LEDRMS<<setw(10)<<PEDRMS<<setw(10)<<TRUEMEAN<<setw(10)<<TRUERMS<<setw(10)<<NPE<<setw(14)<<Charge<<setw(13)<<GAIN<<setw(13)<<Rel_TRUEMEAN<<setw(10)<<Rel_NPE<<setw(14)<<Rel_Charge<<setw(15)<<Rel_GAIN<<setw(8)<<qie<<setw(4)<<ieta<<setw(4)<<depth<<setw(10)<<calib<<endl;
	    }


	      if (GAIN>0) {

		/*		if(hv==0) {
		HistGains650->Fill(qie+(db*24),GAIN);
		HistGains650->SetFillColor(3);
		HistGains650->SetMarkerStyle(8);
		HistGains650->GetXaxis()->SetTitle("Channel");
		HistGains650->GetYaxis()->SetTitle("Gain");
		}

		if{hv==1){
		  HistGains700->Fill(qie+(db*24),GAIN);
		  HistGains700->SetFillColor(3);
		  HistGains700->SetMarkerStyle(8);
		  HistGains700->GetXaxis()->SetTitle("Channel");
		  HistGains700->GetYaxis()->SetTitle("Gain");
		  }*/

		if (hv==0) {
		  GAINfor650=GAIN;
		  myfile3.width(7);
		  myfile3<<GAINfor650;
		}
		if (hv==1) {
		  GAINfor700=GAIN;
		  myfile3.width(13);
		  myfile3<<GAINfor700<<endl;
		}

		if(hv==0){
		  ntuple1->Fill(GAIN);}
		if(hv==1){
		  ntuple2->Fill(GAIN);}

		HistGain[hv][db]->Fill(qie+(db*24),GAIN);
		HistGain[hv][db]->SetMarkerStyle(8);
		HistGain[hv][db]->SetMarkerColor(kBlue);
		HistGain[hv][db]->SetFillColor(38);
		if(db==1) {
		  HistGain[hv][db]->SetMarkerColor(kRed);
		  HistGain[hv][db]->SetFillColor(46);
		}

		GAINHV->Fill(HV[hv],GAIN);
		GAINHV->SetMarkerStyle(8);
		GAINHV->SetMarkerColor(kRed);
		GAINHV->SetFillColor(2);

		/*	if(hv==0){
		  GAIN_650->Fill(650,GAIN);
		  GAIN_650->SetMarkerStyle(8);
		  GAIN_650->SetMarkerColor(kRed);
		  GAIN_650->SetFillColor(2);}

		if(hv==1){
		  GAIN_700->Fill(700,GAIN);
		  GAIN_700->SetMarkerStyle(8);
		  GAIN_700->SetMarkerColor(kBlue);
		  GAIN_700->SetFillColor(3);}
		*/

		if(hv==0 && db==0){
		  GAINfor650DB0=GAIN;
		  myfile2.width(7);
		  myfile2<<GAINfor650DB0;}
		if(hv==0 && db==1){
		  GAINfor650DB1=GAIN;
		  myfile2.width(13);
		  myfile2<<GAINfor650DB1;}
		if(hv==1 && db==0){
		  GAINfor700DB0=GAIN;
		  myfile2.width(13);
		  myfile2<<GAINfor700DB0;}
		if(hv==1 && db==1){
		  GAINfor700DB1=GAIN;
		  myfile2.width(13);
		  myfile2<<GAINfor700DB1;}


		myfile<<GAIN<<endl;

		/*
		GAINHVCorr->Fill(GAINfor650,GAINfor700,HV[hv]);
		GAINHVCorr->SetFillColor(1);
		GAINHVCorr->SetMarkerColor(kRed);
		GAINHVCorr->SetMarkerStyle(8);
		GAINHVCorr->GetXaxis()->SetTitle("GAINfor650V");
		GAINHVCorr->GetYaxis()->SetTitle("GAINfor700V");
		GAINHVCorr->GetZaxis()->SetTitle("HVs");
		

		  if(hv==1){
		    GAINHVCorr1->Fill(GAINfor650,GAINfor700,700);
		    GAINHVCorr1->SetFillColor(2);
		    GAINHVCorr1->SetMarkerColor(kBlue);
		    GAINHVCorr1->SetMarkerStyle(8); }

		  if(hv==0){
		    GAINHVCorr2->Fill(GAINfor650,GAINfor700,650);
		    GAINHVCorr2->SetFillColor(3);
		    GAINHVCorr2->SetMarkerColor(kGreen);
		    GAINHVCorr2->SetMarkerStyle(8);
		  }
		*/
		  ntuple->Fill(GAIN);
		  tree->Fill();
	      }
	  }
	}
      }
	       	

	  myfile2.width(13);
	  myfile2<<qie;
	  myfile2.width(13);
	  myfile2<<ieta;
	  myfile2.width(13);
	  myfile2<<depth<<endl;
    }
      
      //superimpose two histograms into one histogram
      c1->cd();
      HistGains[0]->Draw("AXIS");
      // HistGain6500->Draw("same");
      // HistGain6501->Draw("same");

      c2->cd();
      HistGains[1][db]->Draw("AXIS");
      HistGain7000->Draw("same");
      HistGain7001->Draw("same");

      c3->cd();
      GAINHV->Draw("AXIS");
      //      GAIN_650->Draw("same");
      // GAIN_700->Draw("same");

      /*      c4->cd();
      GAINHVCorr->Draw("AXIS");
      GAINHVCorr1->Draw("same");
      GAINHVCorr2->Draw("same");
      */

      /*      //save canvases as pdf                          
      stringstream voltage1;
      voltage1<<runno<<"_GAIN_650V.pdf";
      c1->SaveAs(voltage1.str().c_str());
      voltage1.str("");

      stringstream voltage2;
      voltage2<<runno<<"_GAIN_700V.pdf";
      c2->SaveAs(voltage2.str().c_str());
      voltage2.str("");

      stringstream voltage3;
      voltage3<<runno<<"_GAIN_vs_HVs.pdf";
      c3->SaveAs(voltage3.str().c_str());
      voltage3.str("");
      */

      c1->Write();
      c2->Write();
      c3->Write();
      //  c4->Write();

      //   f5->Write();

  }

  else {

  while( input>>qie>>ieta>>depth ) {

    for(int db=0;db<2;db++) {

      ink>>calib;

      for(int hv=0;hv<2;hv++) {

	// count++;                                                                                                                                                          
	// cout<<count;                                                                                                                                                          

    
	TString histnameLED,histnamePED;
	stringstream ledname,pedname;
	histnameLED.Form("/Analyzer/QIEsSumLED%d_QiECh_%d_DBOX_%d_eta_%d_D_%d",HV[hv],qie,db,ieta,depth);
	histnamePED.Form("/Analyzer/QIEsSumPED%d_QiECh_%d_DBOX_%d_eta_%d_D_%d",HV[hv],qie,db,ieta,depth);
	pedname<<histnamePED;
	ledname<<histnameLED;

	//      cout<<histnameLED<<endl;                                                                                                                                             
	TH1F *HistLED = (TH1F*)f->Get(ledname.str().c_str());
	TH1F *HistPED = (TH1F*)f->Get(pedname.str().c_str());
	ledname.str("");
	pedname.str("");
	//      cout<<ledname.str().c_str()<<endl;                                                                                                                                   
      
	if(HistLED && HistPED) {
	
	  double LEDMEAN;
	  double PEDMEAN;
	  double LEDRMS;
	  double PEDRMS;

	  LEDMEAN = HistLED->GetMean();
	  PEDMEAN = HistPED->GetMean();
	  LEDRMS = HistLED->GetRMS();
	  PEDRMS = HistPED->GetRMS();


	  double TRUEMEAN = LEDMEAN - PEDMEAN;
	  double TRUERMS = sqrt(pow(LEDRMS,2)-pow(PEDRMS,2));
	  double NPE = 1.15*(pow(TRUEMEAN,2)/pow(TRUERMS,2));// 1.15+-0.05 = ENF(Excess Noise Factor)
       	  double Charge = NPE*1.6*pow(10,(-19));
	  GAIN = (TRUEMEAN*2.6)*pow(10,(-15))/Charge;

	  //count++;
	  //cout<<count<<"_"<<"GAIN = "<<GAIN<<endl;
	  // cout<<count<<"_"<<"TRUEMEAN"<<TRUEMEAN<<endl;
	 
	  double Rel_TRUEMEAN = (LEDMEAN-PEDMEAN)/calib;
	  double Rel_NPE = 1.15*(pow(Rel_TRUEMEAN,2)/pow(TRUERMS,2));
	  double Rel_Charge = Rel_NPE*1.6*pow(10,(-19));
	  double Rel_GAIN = (Rel_TRUEMEAN*2.6*10000)/(Rel_NPE*1.6);
	  

	  if(hv==0) {
	    myfile4.width(7);
	    myfile4<<LEDMEAN<<setw(10)<<PEDMEAN<<setw(10)<<LEDRMS<<setw(10)<<PEDRMS<<setw(10)<<TRUEMEAN<<setw(10)<<TRUERMS<<setw(10)<<NPE<<setw(14)<<Charge<<setw(13)<<GAIN<<setw(13)<<Rel_TRUEMEAN<<setw(10)<<Rel_NPE<<setw(14)<<Rel_Charge<<setw(15)<<Rel_GAIN<<setw(8)<<qie<<setw(4)<<ieta<<setw(4)<<depth<<setw(10)<<calib<<endl; 
	  }

	  if(hv==1) {
	    myfile5.width(7);
	    myfile5<<LEDMEAN<<setw(10)<<PEDMEAN<<setw(10)<<LEDRMS<<setw(10)<<PEDRMS<<setw(10)<<TRUEMEAN<<setw(10)<<TRUERMS<<setw(10)<<NPE<<setw(14)<<Charge<<setw(13)<<GAIN<<setw(13)<<Rel_TRUEMEAN<<setw(10)<<Rel_NPE<<setw(14)<<Rel_Charge<<setw(15)<<Rel_GAIN<<setw(8)<<qie<<setw(4)<<ieta<<setw(4)<<depth<<setw(10)<<calib<<endl;
	  }

      	  if (GAIN>0) {

	    HistGains[hv]->Fill(qie+(db*24),GAIN);
	    HistGains[hv]->SetFillColor(3);
	    HistGains[hv]->SetMarkerStyle(8);
	    HistGains[hv]->GetXaxis()->SetTitle("Channel");
	    HistGains[hv]->GetYaxis()->SetTitle("Gain");

	    if (hv==0) {
		GAINfor650=GAIN;
		myfile3.width(7);
		myfile3<<GAINfor650;
	    }
	    if (hv==1) {
		GAINfor700=GAIN;
		myfile3.width(13);
		myfile3<<GAINfor700<<endl;
	    }

	    if(hv==0){
	      ntuple1->Fill(GAIN);}
	    if(hv==1){
	      ntuple2->Fill(GAIN);}

	    HistGain[hv][db]->Fill(qie+(db*24),GAIN);
	    HistGain[hv][db]->SetMarkerStyle(8);
	    HistGain[hv][db]->SetMarkerColor(kBlue);
	    HistGain[hv][db]->SetFillColor(38);
	    if(db==1) {
	      HistGain[hv][db]->SetMarkerColor(kRed);
	      HistGain[hv][db]->SetFillColor(46);
	    }

	    GAINHV->Fill(HV[hv],GAIN);
	    GAINHV->SetMarkerStyle(8);
	    GAINHV->SetMarkerColor(kRed);
	    GAINHV->SetFillColor(2);

	    /*	    if(hv==0){
	      GAIN_650->Fill(650,GAIN);
	      GAIN_650->SetMarkerStyle(8);
	      GAIN_650->SetMarkerColor(kRed);
	      GAIN_650->SetFillColor(2);}

	    if(hv==1){
	      GAIN_700->Fill(700,GAIN);
	      GAIN_700->SetMarkerStyle(8);
	      GAIN_700->SetMarkerColor(kBlue);
	      GAIN_700->SetFillColor(3);}
	    */

	    if(hv==0 && db==0){
	      GAINfor650DB0=GAIN;
	      myfile2.width(7);
	      myfile2<<GAINfor650DB0;}
	    if(hv==0 && db==1){
	      GAINfor650DB1=GAIN;
	      myfile2.width(13);
	      myfile2<<GAINfor650DB1;}
	    if(hv==1 && db==0){
	      GAINfor700DB0=GAIN;
	      myfile2.width(13);
	      myfile2<<GAINfor700DB0;}
	    if(hv==1 && db==1){
	      GAINfor700DB1=GAIN;
	      myfile2.width(13);
	      myfile2<<GAINfor700DB1;}


	    myfile<<GAIN<<endl;

	    /*
	    GAINHVCorr->Fill(GAINfor650,GAINfor700,HV[hv]);
	    GAINHVCorr->SetFillColor(1);
	    GAINHVCorr->SetMarkerColor(kRed);
	    GAINHVCorr->SetMarkerStyle(8);
	    GAINHVCorr->GetXaxis()->SetTitle("GAINfor650V");
	    GAINHVCorr->GetYaxis()->SetTitle("GAINfor700V");
	    GAINHVCorr->GetZaxis()->SetTitle("HVs");


	    if(hv==1){
	      GAINHVCorr1->Fill(GAINfor650,GAINfor700,700);
	      GAINHVCorr1->SetFillColor(2);
	      GAINHVCorr1->SetMarkerColor(kBlue);
	      GAINHVCorr1->SetMarkerStyle(8); }

	    if(hv==0){
	      GAINHVCorr2->Fill(GAINfor650,GAINfor700,650);
	      GAINHVCorr2->SetFillColor(3);
	      GAINHVCorr2->SetMarkerColor(kGreen);
	      GAINHVCorr2->SetMarkerStyle(8);
	    }
	    */
	    ntuple->Fill(GAIN);
	    tree->Fill();

	
	  }
	}
      }
    }

    myfile2.width(13);
    myfile2<<qie;
    myfile2.width(13);
    myfile2<<ieta;
    myfile2.width(13);
    myfile2<<depth<<endl;
  
  }

  //superimpose two histograms into one histogram                                                                                                                          
  c1->cd();
  HistGains[0]->Draw("AXIS");
  HistGain[0][0]->Draw("same");
  HistGain[0][1]->Draw("same");

  c2->cd();
  HistGains[1]->Draw("AXIS");
  HistGain[1][0]->Draw("same");
  HistGain[1][1]->Draw("same");

  c3->cd();
  GAINHV->Draw("AXIS");
  //  GAIN_650->Draw("same");
  //GAIN_700->Draw("same");

  /*
  c4->cd();
  GAINHVCorr->Draw("AXIS");
  GAINHVCorr1->Draw("same");
  GAINHVCorr2->Draw("same");
  */
  /*
  //save canvases as pdf                                                                                                                                                       
  stringstream voltage1;
  voltage1<<runno<<"_LEDGAIN_650V.pdf";
  c1->SaveAs(voltage1.str().c_str());
  voltage1.str("");

  stringstream voltage2;
  voltage2<<runno<<"_LEDGAIN_700V.pdf";
  c2->SaveAs(voltage2.str().c_str());
  voltage2.str("");

  stringstream voltage3;
  voltage3<<runno<<"_LEDGAIN_vs_HVs.pdf";
  c3->SaveAs(voltage3.str().c_str());
  voltage3.str("");
  */

  //write canvases into rootfile f1                                                                                                                                            
  c1->Write();
  c2->Write();
  c3->Write();
  //  c4->Write();
  //tree->Write();
  //ntuple1->Write();
  //ntuple2->Write();
  //f5->Write();

  }


}

void HFLEDAnalyzer() {


  ifstream myinput;                                                                                                                                           
  myinput.open("/Users/core/Desktop/!!!THESIS!!!/PMT ANALYSIS /PMTTESTANALYSIS/txt/B904/led_runlist.txt",ios::in); 
  if(!(myinput.good())) {cout<<"There is no avaliable led_runlist.txt"<<endl;}                                                  

  while(myinput>>runno) {   

 
    HFLEDGAINAnalysis(); 
    HFLEDGAINAnalysisforHV();
    //  HFLEDGAINAnalysisforHVandDB();
    HFLEDInfo();


  }
}
