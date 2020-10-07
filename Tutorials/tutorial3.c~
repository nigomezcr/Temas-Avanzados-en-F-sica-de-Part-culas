//Third Tutorial: Filling a histogram with data from file

void tutorial3()
{
  //Define de histogram
  TH1F *hist = new TH1F("hist", " Histogram", 50, 0, 1);
  //Create a canvas to put the histogram on
  TCanvas *c = new TCanvas();

  //Open file
  fstream file;
  file.open("data.txt", ios::in);

  //Fill the histogram with the file values
  double value;
  while(1)
    {
      file >> value;
      hist -> Fill(value);
      if(file.eof()) break;
    }

  file.close();
  
  


  //Label de axes
  hist -> GetXaxis() -> SetTitle("Number");
  hist -> GetYaxis() -> SetTitle("Entries");

  //Draw the histogram
  hist -> Draw();
}
