// Tutorial 5: Generating Random Numbers

void tutorial5()
{
  //Create histogram
  TH1F *hist = new TH1F("hist", "Histogram", 100, 0, 100);
  
  //Declare random generator
  TRandom2 *rand = new TRandom2(0); //() is seed=1 by default, with 0 seed we have random seed 

  //Generate numbers and fill histogram
  for(int i = 0 ; i < 10000 ; i++ )
    {
      double r = rand->Rndm()*100;
      cout << r << endl;
      hist->Fill(r);      
    }

  //Create Canvas
  TCanvas *c1 = new TCanvas();
  hist->GetYaxis()->SetRangeUser(0,1000);
  hist->Draw();

}
