//Ninth Tutorial: Beautifying plots

void tutorial9()
{
  //Define de histogram
  TH1F *hist = new TH1F("hist", " Histogram", 200, 0, 12);

  //Create a canvas to put the histogram on
  TCanvas *c = new TCanvas();


  //Declare Random Generator
  TRandom2 *rand = new TRandom2(3);

  //Print in file to store rnd #
  fstream file;
  file.open("data.txt", ios::out);

  //Generating numbers
  for(int i = 0; i < 40000; i++)
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
  TF1 *fit= new TF1("fit", "gaus", 0, 12);
  
  //If we can impose some paramiters in the fitting
  fit -> SetParameter(0,40); //bins
  fit -> SetParameter(1, 5);    //mean
  fit -> SetParameter(2, 2);    //std dev
  fit -> SetLineWidth(3);
  //fit -> SetLineColor(kBlue);
  fit -> SetLineStyle(1);

  //Label de axes
  hist -> GetXaxis() -> SetTitle("Rand Number");
  hist -> GetYaxis() -> SetTitle("Entries");
  hist -> GetXaxis() -> SetTitleSize(0.05);
  hist -> GetYaxis() -> SetTitleSize(0.05);
  hist -> GetXaxis() -> SetLabelSize(0.05);
  hist -> GetYaxis() -> SetLabelSize(0.05);


  //Draw the histogram
  c -> SetTickx();
  c -> SetTicky();
  //c -> SetGridx();
  //c -> SetGridy();
  hist -> SetStats(0);  
  hist -> SetFillColor(kGreen-9);
  hist -> Draw();
  hist -> Fit("fit", "RQ"); //fit with our function 
  

  
  //Put a legend
  TLegend *legend = new TLegend(0.5,0.6,0.8,0.8);
  legend -> SetBorderSize(0);
  legend -> AddEntry(hist, "Measured Data", "f");
  legend -> AddEntry(fit, "Fit Function", "l");
  legend -> Draw();


}
