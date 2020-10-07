//Tutorial 4: Plotting data file in  graph

void tutorial4()
{
  //Create graph
  TGraph *gr = new TGraph();

  //Select points style and size
  gr -> SetMarkerStyle(4);
  gr -> SetLineWidth(2);
  gr -> SetLineColor(kRed);

  gr -> SetTitle("Graph");
  gr -> GetXaxis() -> SetTitle("X values");
  gr -> GetYaxis() -> SetTitle("Y values");

  //Open File
  fstream file;
  file.open("data2.txt", ios::in);

  //Fill graph with file data
  while(1)
    {
      double x, y;
      file >> x >> y;
      gr-> SetPoint(gr -> GetN(),x,y);
      if (file.eof()) break ; 
    }

  //Create Canvas
  TCanvas *c1 = new TCanvas();

  //Draw the graph
  gr -> Draw("AL*");
}
