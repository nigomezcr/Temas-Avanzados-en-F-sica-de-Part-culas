//First Tutorial: Creating a first histogram

void main()
{
  //Define de histogram
  TH1F *hist1 = new TH1F("hist1", "First Histogram", 100, 0, 100);

  //Fill it
  hist1 -> Fill(10);
  hist1 -> Fill(90);  

  //Create a canvas to put the histogram on
  TCanvas *c1 = new TCanvas();

  //Label de axes
  hist1 -> GetXaxis() -> SetTitle("X axis");
  hist1 -> GetYaxis() -> SetTitle("Y axis");

  //Draw the histogram
  hist1 -> Draw();
}
