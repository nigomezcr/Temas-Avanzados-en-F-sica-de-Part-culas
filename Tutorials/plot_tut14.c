//Plot histogram created on tutorial 14 using TFile

void plot_tut14()
{
	//Define a File class to READ the histogram
	TFile *file = new TFile("output.root", "READ");

	TH1F *hist = (TH1F*)file -> Get("hist");

	hist -> Draw();

	//file -> Close();

}
