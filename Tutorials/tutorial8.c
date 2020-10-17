//Eighth Tutorial: Adding Legend to Canvas

void tutorial8()
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
  TF1 *fit= new TF1("fit", "gaus", 0, 10);
  
  //If we can impose some paramiters in the fitting
  fit -> SetParameter(0,40); //bins
  fit -> SetParameter(1, 5);    //mean
  fit -> SetParameter(2, 2);    //std dev


  //Label de axes
  hist -> GetXaxis() -> SetTitle("Rand Number");
  hist -> GetYaxis() -> SetTitle("Entries");

  //Draw the histogram
  hist -> Draw();
  hist -> Fit("fit", "RQ"); //fit with our function 


  
  //Put a legend
  TLegend *legend = new TLegend(0.7,0.7,0.9,0.9);
  legend->AddEntry(hist, "Measured Data", "l");
  legend->AddEntry(fit, "Fit Function", "l");
  legend->Draw();


}
