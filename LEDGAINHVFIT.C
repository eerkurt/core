
using namespace std;
char rootfile[200];

Double_t func(Double_t *x, Double_t *par) {

  Int_t n = 10;
  Double_t f;
  f = TMath::Power((par[0]*x[0]),(par[1]*n));
  return f;

}

void LEDGAINHV(Int_t runno) {

  //sprintf(rootfile,"/Users/core/Desktop/!!!THESIS!!!/PMT ANALYSIS /PMTTESTANALYSIS/BURNINat4HVs/HFLED/LEDBURNIN_ROOTFILES/Run_%d.root",runno);
  sprintf(rootfile,"/Users/core/Desktop/!!!THESIS!!!/PMT ANALYSIS /PMTB904/PMTTESTANALYSIS/SORTING/HFLED/LED_ROOTFILES/Run_%d.root",runno);
  TFile *f = new TFile(rootfile);  

  stringstream rootname;
  rootname<<"LEDGAINHV.root";
  TString dir = gSystem->UnixPathName(gInterpreter->GetCurrentMacroName());
  dir.ReplaceAll("./LEDGAINHVFIT.C","LEDNtuples/");
  TString fullpathname = dir+rootname.str().c_str();
  TFile *f2 = new TFile(fullpathname,"RECREATE");
  rootname.str("");

  stringstream runnoname;
  runnoname<<runno<<"_GAINHV";
  TDirectory *subf = f2->mkdir(runnoname.str().c_str());
  runnoname.str("");
  subf->cd();
  

  ifstream in;
  in.open("/Users/core/Desktop/!!!THESIS!!!/PMT ANALYSIS /PMTB904/PMTTESTANALYSIS/txt/B904/map.txt",ios::in);

  Int_t HV[] = {600,650,700,750};
  Int_t qie,ieta,depth;
  TH2D *GAINHV;

  if(runno == 3013 || runno == 3031 || runno == 3045 || runno == 2996) {

  while(in>>qie>>ieta>>depth) {

    for(Int_t db=0; db<1; db++) {

      stringstream histname;
      histname<<"ch_"<<qie<<"db_"<<db;
      GAINHV  = new TH2D(histname.str().c_str(),histname.str().c_str(),1000,550,800,1000,0,3000000);
      histname.str("");

      for(Int_t hv=0; hv<4; hv++) {

        stringstream pedname;
        stringstream ledname;
        TString HFLEDname;
        TString HFPEDname;
        HFLEDname.Form("/Analyzer/QIEsSumLED%d_QiECh_%d_DBOX_%d_eta_%d_D_%d",HV[hv],qie,db,ieta,depth);
        HFPEDname.Form("/Analyzer/QIEsSumPED%d_QiECh_%d_DBOX_%d_eta_%d_D_%d",HV[hv],qie,db,ieta,depth);
        pedname<<HFPEDname;
        ledname<<HFLEDname;

        TH1F *histled = (TH1F*)f->Get(ledname.str().c_str());
        TH1F *histped = (TH1F*)f->Get(pedname.str().c_str());

        ledname.str("");
        pedname.str("");

        if(histled && histped)  {

          Double_t LEDMEAN;
          Double_t PEDMEAN;
          Double_t LEDRMS;
          Double_t PEDRMS;

          LEDMEAN = histled->GetMean();
          PEDMEAN = histped->GetMean();
          LEDRMS = histled->GetRMS();
          PEDRMS = histped->GetRMS();

          Double_t TRUEMEAN = LEDMEAN - PEDMEAN;
          Double_t TRUERMS = sqrt(pow(LEDRMS,2)-pow(PEDRMS,2));
	  Double_t NPE = 1.15*(pow(TRUEMEAN,2)/pow(TRUERMS,2));// 1.15+-0.05 = ENF(Excess Noise Factor)
          //Double_t NPE = 1.15*(pow(LEDMEAN,2)/pow(LEDRMS,2));
          Double_t Charge = NPE*1.6*pow(10,(-19));
          Double_t GAIN = (TRUEMEAN*2.6)*pow(10,(-15))/Charge;
          //Double_t GAIN = LEDMEAN/NPE;
          //Double_t GAIN = LEDMEAN;


	  if(GAIN>0) {

	    GAINHV->Fill(HV[hv],GAIN);
	    GAINHV->SetMarkerColor(2);
	    GAINHV->SetMarkerStyle(8);

	  }
        }
      }

      GAINHV->Draw();

    }
  }
  }

  else{

  while(in>>qie>>ieta>>depth) {

    for(Int_t db=0; db<2; db++) {

      stringstream histname;
      histname<<"ch_"<<qie<<"db_"<<db;     
      GAINHV  = new TH2D(histname.str().c_str(),histname.str().c_str(),1000,550,800,1000,0,3000000);
      histname.str("");

      for(Int_t hv=0; hv<4; hv++) {

	stringstream pedname;
	stringstream ledname;
	TString HFLEDname;
	TString HFPEDname;
	HFLEDname.Form("/Analyzer/QIEsSumLED%d_QiECh_%d_DBOX_%d_eta_%d_D_%d",HV[hv],qie,db,ieta,depth);
	HFPEDname.Form("/Analyzer/QIEsSumPED%d_QiECh_%d_DBOX_%d_eta_%d_D_%d",HV[hv],qie,db,ieta,depth);
	pedname<<HFPEDname;
	ledname<<HFLEDname;

	TH1F *histled = (TH1F*)f->Get(ledname.str().c_str());
	TH1F *histped = (TH1F*)f->Get(pedname.str().c_str());

	ledname.str("");
	pedname.str("");

	if(histled && histped)  {

	  Double_t LEDMEAN;
	  Double_t PEDMEAN;
	  Double_t LEDRMS;
	  Double_t PEDRMS;

	  LEDMEAN = histled->GetMean();
	  PEDMEAN = histped->GetMean();
	  LEDRMS = histled->GetRMS();
	  PEDRMS = histped->GetRMS();

	  Double_t TRUEMEAN = LEDMEAN - PEDMEAN;
	  Double_t TRUERMS = sqrt(pow(LEDRMS,2)-pow(PEDRMS,2));
	  Double_t NPE = 1.15*(pow(TRUEMEAN,2)/pow(TRUERMS,2));// 1.15+-0.05 = ENF(Excess Noise Factor)
	  //Double_t NPE = 1.15*(pow(LEDMEAN,2)/pow(LEDRMS,2));
	  Double_t Charge = NPE*1.6*pow(10,(-19));
	  Double_t GAIN = (TRUEMEAN*2.6)*pow(10,(-15))/Charge;
	  //Double_t GAIN = LEDMEAN/NPE;	
	  //Double_t GAIN = LEDMEAN;


	    if(GAIN>0) {

	      GAINHV->Fill(HV[hv],GAIN);
	      GAINHV->SetMarkerColor(2);
	      GAINHV->SetMarkerStyle(8);
	    
	    }
	}
      }
      
      GAINHV->Draw();
      
    }
  }
  }

  f2->Write();
  
}

void LEDGAINHVFIT() {

  Int_t runno; 
  Double_t Constant;
  Double_t k;
  Double_t k_mean;
  Int_t n = 25;
  Int_t m = 2;


  stringstream rootname;
  rootname<<"LEDGAINHVFIT.root";
  TString dir = gSystem->UnixPathName(gInterpreter->GetCurrentMacroName());
  dir.ReplaceAll("./LEDGAINHVFIT.C","LEDNtuples/");
  TString fullpathname = dir+rootname.str().c_str();
  TFile *f = new TFile(fullpathname,"RECREATE");
  rootname.str("");  

  
  ifstream in1;
  in1.open("/Users/core/Desktop/!!!THESIS!!!/PMT ANALYSIS /PMTB904/PMTTESTANALYSIS/txt/B904/led_runlist.txt",ios::in);

  while(in1>>runno) {   


  LEDGAINHV(runno);

  cout<<runno<<endl;

  TFile *f3 = new TFile("/Users/core/Desktop/!!!THESIS!!!/PMT ANALYSIS /PMTB904/PMTTESTANALYSIS/SORTING/HFLED/LEDNtuples/LEDGAINHV.root","OPEN");

  stringstream runnoname;
  runnoname<<runno<<"_GAINHV";
  TDirectory *f1 = (TDirectory*)f3->Get(runnoname.str().c_str());
  runnoname.str("");

  stringstream runnoname1;
  runnoname1<<runno<<"_GAINHVFIT";
  TDirectory *subf = f->mkdir(runnoname1.str().c_str());
  subf->cd();

  TCanvas *c1 = new TCanvas("c1","LEDGAINHVFIT",600,800);
  TH2D *GAINHV = new TH2D("h1","GAINvsHV",1000,550,800,1000,0,3000000);

  TF1 *fit = new TF1("fit1",func,550,800,2);
  fit->SetParameters(7.e-3,0.75);
  fit->SetParNames("Constant","k value");

  stringstream outname;
  outname<<runno<<"_kdist.txt";
  ofstream out;
  out.open(dir+outname.str().c_str(),ios::out);
  outname.str("");

  stringstream histname;

  if(runno == 3013 || runno == 3031 || runno == 3045 || runno == 2996) {

  for(Int_t db = 0; db<1; db++) {

    for(Int_t qie = 1; qie<n; qie++) {

      histname<<"ch_"<<qie<<"db_"<<db;
      GAINHV = (TH2D*)f1->Get(histname.str().c_str());
      histname.str("");

      //      gStyle->SetOptFit(1111);
      c1->cd();
      gStyle->SetOptFit(1111);
      GAINHV->Fit("fit1");

      TF1 *fitResults = GAINHV->GetFunction("fit1");          
      k = fitResults->GetParameter(1);

      out<<runno<<setw(10)<<qie<<setw(10)<<db<<setw(15)<<k<<endl;

      c1->Write();

    }
  }
  }

  else {

    for(Int_t db = 0; db<2; db++) {

	  for(Int_t qie = 1; qie<n; qie++) {

	    histname<<"ch_"<<qie<<"db_"<<db;
	    GAINHV = (TH2D*)f1->Get(histname.str().c_str());
	    histname.str("");

	    //	    gStyle->SetOptFit(1111);
	    c1->cd();
            gStyle->SetOptFit(1111);
	    GAINHV->Fit("fit1");

	    TF1 *fitResults = GAINHV->GetFunction("fit1");
	    k = fitResults->GetParameter(1);

	    out<<runno<<setw(10)<<qie<<setw(10)<<db<<setw(15)<<k<<endl;
	    
	    c1->Write();

	  }
    }  
  }    
 }
}
