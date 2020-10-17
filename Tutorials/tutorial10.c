//Tenth tutorial: Adding error bars to a plot

void tutorial10()
{
  TCanvas *c = new TCanvas();

  TGraphErrors *gr = new TGraphErrors();

  fstream file;
  file.open("data3.txt", ios::in);

  double x, y, ex, ey;
  int n = 0;

  while(1)
  {
    //Write from file the points
    file >> x >> y >> ex >> ey;

    //Use the points in the graph
    n = gr -> GetN();
    
    //position of points and errors
    gr -> SetPoint(n, x, y);
    gr -> SetPointError(n, ex, ey);

    if(file.eof()) break;
  }
  

  //Make a fit
  TF1 *fit = new TF1("fit", "pol1", 0, 5);
  

  //Draw
  gr -> GetXaxis() -> SetTitle("Y valures");
  gr -> GetYaxis() -> SetTitle("X values");
  gr -> Draw("A*");
  gr -> Fit("fit");

}

