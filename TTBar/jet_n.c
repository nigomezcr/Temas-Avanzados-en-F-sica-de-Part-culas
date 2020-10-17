void jet_n()
{

  TFile *file = TFile::Open("Data_8TeV.root"); 

  TTree *tree = (TTree*) file->Get("mini");
 
  TCanvas *canvas = new TCanvas("Canvas", "", 800, 600);
 
  TH1F *hist_njets = new TH1F("Jets Number", "Jets n", 10, 0, 10);

  UInt_t jet_n;  
  Float_t mcw;


  tree->SetBranchAddress("mcWeight", &mcw);
  tree->SetBranchAddress("jet_n", &jet_n);

	int nentries, nbytes, i;
	nentries = (Int_t)tree->GetEntries();

	for (i = 0; i < nentries; i++)
	{
    nbytes = tree->GetEntry(i);   
    hist_njets->Fill(jet_n, mcw); 
	}


  //Label de axes
  hist_njets -> GetXaxis() -> SetTitle("Number");
  hist_njets -> GetYaxis() -> SetTitle("Events");

  //Draw the histogram
  hist_njets -> Draw();
  canvas -> Draw();

}
