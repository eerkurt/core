

   /*******************************************************************************************
   ****** PROGRAM : HFB904LEDInfo.C **********************                                  ***
   *******************************************************                                  ***
   ***                                                                                      ***
   *** Author : Ersel Bedri Erkurt                                                          ***
   *** Date   : 2018                                                                        ***
   *** Place  : ITU & CERN                                                                  *** 
   *** This program was written with C++ and ROOT                                           ***
   ***                                                                                      ***
   *** This program gets some informations about some characteristics of PMTs               ***
   *** from B904LEDGAIN.txt, crates a text file, namely B904LEDInfo.txt                     ***
   ***                                                                                      ***
   ***                                                                                      ***
   ********************************************************************************************/

#include <iostream>
#include <fstream>

using namespace std;

void HFB904LEDInfo() {

  char conf[100];
  char baseno[100];
  int Base[6];
  string PMT[8];
  int runno,confi,runnon[8];
  double GAIN650[8],GAIN700[8],calib[8],Rel_GAIN650[8],Rel_GAIN700[8];

  ofstream out;
  out.open("/txt/B904/B904LEDInfo.txt",ios::out);

  ifstream ins;
  ins.open("/txt/B904/B904LEDGAIN.txt",ios::in);


  for (int no=94; no<134; no++) {

    sprintf(conf,"/Users/Erkurt/Desktop/!!!THESIS!!!/BURNIN Thesis/Configurations/Conf%d.txt",no);
    cout<<"------"<<conf<<"-----"<<endl;

    ifstream inp;
    inp.open("/Users/Erkurt/Desktop/!!!THESIS!!!/BURNIN Thesis/txt/B904/ledconf.txt");
    if(!(inp.good())) { cout<<" There is no ledconf.txt"<<endl; }

    while(inp>>runno>>confi) {
      if(confi==no) {
	cout<<confi<<setw(5)<<no<<endl;

	ifstream in;
	in.open(conf);
	if(in.fail()) { cout<<"There is no available Conf*.txt"<<endl; }

	stringstream runnumber;
	runnumber<<runno<<"_LEDNtuples.root";
	TString dir = gSystem->UnixPathName(gInterpreter->GetCurrentMacroName());
	dir.ReplaceAll("./GetB904LEDInfo.C","HFLED/LEDNtuples/");
	TString rootfile = dir+runnumber.str().c_str();
	runnumber.str("");

	TFile *f = new TFile(rootfile);

	TTree *tree = (TTree*)f->Get("HFLEDInfo");

	TLeaf *LEDMEAN650 = (TLeaf*)tree->GetLeaf("LEDMEAN650");
	TLeaf *PEDMEAN650 = (TLeaf*)tree->GetLeaf("PEDMEAN650");
	TLeaf *calib650 = (TLeaf*)tree->GetLeaf("calib650");

	TLeaf *LEDMEAN700 = (TLeaf*)tree->GetLeaf("LEDMEAN700");
        TLeaf *PEDMEAN700 = (TLeaf*)tree->GetLeaf("PEDMEAN700");
        TLeaf *calib700 = (TLeaf*)tree->GetLeaf("calib700");

	if(no==98 || no==103 || no==109 || no==114) {

	  for(int j=0; j<3; j++) {

	    in>>Base[j];
	    sprintf(baseno,"/Users/Erkurt/Desktop/!!!THESIS!!!/BURNIN Thesis/Baseboards/Baseboard%d.txt",Base[j]);

	    ifstream input[6];
	    input[j].open(baseno);
	    cout<<baseno<<endl;
	    if(!(input[j].good())) {  cout<<"There is no available Baseboard*.txt"<<endl; }

	    int PMTNo=0;

	    for(int i=0; i<8; i++) {

	      PMTNo++;

	      input[j]>>PMT[i];
	      
	      ins>>runnon[i]>>GAIN650[i]>>GAIN700[i];	      

	      LEDMEAN650->GetBranch()->GetEntry(i);
	      PEDMEAN650->GetBranch()->GetEntry(i);
	      calib650->GetBranch()->GetEntry(i);

	      LEDMEAN700->GetBranch()->GetEntry(i);
              PEDMEAN700->GetBranch()->GetEntry(i);
              calib700->GetBranch()->GetEntry(i);

	      double RelResponse650 = ((LEDMEAN650->GetValue())-(PEDMEAN650->GetValue()))/(calib650->GetValue());
              double RelResponse700 = ((LEDMEAN700->GetValue())-(PEDMEAN700->GetValue()))/(calib700->GetValue());

              out.width(7);
	      out<<no<<setw(10)<<runnon[i]<<setw(10)<<Base[j]<<setw(10)<<PMT[i]<<setw(4)<<PMTNo<<setw(18)<<GAIN650[i]<<setw(18)<<GAIN700[i]<<setw(18)<<RelResponse650<<setw(18)<<RelResponse700<<endl;

	    }
	  }
	}

	else {
	  for(int j=0; j<6; j++) {

	    in>>Base[j];

	    sprintf(baseno,"/Users/Erkurt/Desktop/!!!THESIS!!!/BURNIN Thesis/Baseboards/Baseboard%d.txt",Base[j]);

	    ifstream input[6];
	    input[j].open(baseno);
	    cout<<baseno<<endl;
	    if(!(input[j].good())) {  cout<<"There is no available Baseboard*.txt"<<endl; }

	    int PMTNo = 0;

	    for(int i=0; i<8; i++) {

	      PMTNo++;

	      input[j]>>PMT[i];
	      
      	      ins>>runnon[i]>>GAIN650[i]>>GAIN700[i];

	      LEDMEAN650->GetBranch()->GetEntry(i);
	      PEDMEAN650->GetBranch()->GetEntry(i);
	      calib650->GetBranch()->GetEntry(i);

	      LEDMEAN700->GetBranch()->GetEntry(i);
              PEDMEAN700->GetBranch()->GetEntry(i);
              calib700->GetBranch()->GetEntry(i);

	      double RelResponse650 = ((LEDMEAN650->GetValue())-(PEDMEAN650->GetValue()))/(calib650->GetValue());
              double RelResponse700 = ((LEDMEAN700->GetValue())-(PEDMEAN700->GetValue()))/(calib700->GetValue());

              out.width(7);
	      out<<no<<setw(10)<<runnon[i]<<setw(10)<<Base[j]<<setw(10)<<PMT[i]<<setw(4)<<PMTNo<<setw(18)<<GAIN650[i]<<setw(18)<<GAIN700[i]<<setw(18)<<RelResponse650<<setw(18)<<RelResponse700<<endl;

	    }
	  }
	}


      }
    }
  }
}
