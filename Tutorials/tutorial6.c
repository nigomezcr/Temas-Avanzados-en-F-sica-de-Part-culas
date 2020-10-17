//Sixth Tutorial: Generating and filling a gaussian distribution

void tutorial6()
{
  //Define de histogram
  TH1F *hist = new TH1F("hist", " Histogram", 100, 0, 10);

  //Create a canvas to put the histogram on
  TCanvas *c = new TCanvas();

  //Declare Random Generator
  TRandom2 *rand = new TRandom2(3);

  //Print in file to store rnd #
  fstream file;
  file.open("data.txt", ios::out);

  //Generating numbers
  for(int i = 0; i < 10000; i++)
  {
    //Generate random numbers with gaussian distribution with mean 5 and std dev 1
    double r = rand->Gaus(5,1);
    file << r << endl;
  }

  file.close();

  //Open the same file with the distribution 
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
  hist -> GetXaxis() -> SetTitle("Rand Number");
  hist -> GetYaxis() -> SetTitle("Entries");

  //Draw the histogram
  hist -> Draw();
}
