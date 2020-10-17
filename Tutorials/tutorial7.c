//Seventh Tutorial: Fitting Distributions

void tutorial7()
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

  //As an example consider a new function
  TF1 *fit= new TF1("fit", "gaus", 4, 6);
  
  //If we can impose some paramiters in the fitting
  fit -> SetParameter(0,40); //bins
  fit -> SetParameter(1, 5);    //mean
  fit -> SetParameter(2, 2);    //std dev


  //Label de axes
  hist -> GetXaxis() -> SetTitle("Rand Number");
  hist -> GetYaxis() -> SetTitle("Entries");

  //Draw and fit the histogram
  hist -> Draw();
  //hist -> Fit("gaus");  
  hist -> Fit("fit", "R"); //fit with our function in range R (4,6)

  //For extracting the parameters out of the fitting
  double mean = fit -> GetParameter(1);
  double sigma = fit -> GetParameter(2);
  std::cout << mean/sigma << "\n";

}
