//Fourteenth tutorial: Storing and loading objects with TFile

void tutorial14()
{
	//Define a File class to store the histogram on (create and edit)
	TFile *file = new TFile("output.root", "RECREATE");

	TH1F *hist = new TH1F("hist", "Histrogram", 100, 0, 100);

	hist -> Fill(10);
	hist -> Fill(90);

	file -> Write();

	file -> Close();  
}
