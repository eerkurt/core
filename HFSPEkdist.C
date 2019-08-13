void SPEkdist() {

  Int_t runno;

  ifstream in1;
  in1.open("/Users/core/Desktop/!!!THESIS!!!/PMT ANALYSIS /PMTTESTANALYSIS/txt/B904/spe_runlist.txt",ios::in);

  while(in1>>runno) {  

  stringstream pathname1;
  pathname1<<runno<<"_SPEkdist.root";
  TString dir = gSystem->UnixPathName(gInterpreter->GetCurrentMacroName());
  dir.ReplaceAll("./SPEkdist.C","SPENtuples/");
  TString fullpathname1 = dir+pathname1.str().c_str();
  TFile *f1 = new TFile(fullpathname1,"RECREATE");
  pathname1.str("");
 
  TH1D *kdist = new TH1D("kdsit","SPE k distribution",48,0.5,0.9);
 
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
