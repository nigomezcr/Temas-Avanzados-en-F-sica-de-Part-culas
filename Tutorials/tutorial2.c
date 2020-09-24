//Tutorial 2: Creating a first graph

void tutorial2()
{
  //Choose data points
  double x[5] = {1,2,3,4,5};
  double y[5] = {1,4,9,16,25};

  //Create graph
  TGraph *gr1 = new TGraph(5,x,y);

  //Select points style and size
  gr1 -> SetMarkerStyle(4);
  gr1 -> SetMarkerSize(2);

  //Create Canvas
  TCanvas *c1 = new TCanvas();

  //Draw the graph
  gr1 -> Draw("AL*");
}
