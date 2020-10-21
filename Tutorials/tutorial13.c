//Thirteenth tutorial: Exporting plots

void tutorial13()
{
	TCanvas *c = new TCanvas();

	//Define a function
	TF1 *func1 = new TF1("function1", "[0] + [1]*x", 0, 30);
	TF1 *func2 = new TF1("function2", "exp(-[1]*x)*[0]*sin(x)", 0, 10*TMath::Pi());

	func1 -> SetTitle("Functions");

	//Construct the function
	func1 -> SetParameter(0,-2);
	func1 -> SetParameter(1,0.2);
	func2 -> SetParameter(0,2);
	func2 -> SetParameter(1,0.1);


	//Plot it
	func1 -> SetLineColor(kBlue);
	func2 -> SetLineColor(kRed);	
	func1 -> GetXaxis() -> SetTitle("x");
	func1 -> GetYaxis() -> SetTitle("f(x)");
	func1 ->Draw("");
	func2 ->Draw("same");

//Put a legend
  TLegend *legend = new TLegend(0.1,0.7,0.4,0.9);
  legend -> SetBorderSize(2);
  legend -> AddEntry(func1, "Line", "l");
  legend -> AddEntry(func2, "Exp sine", "l");
  //legend -> Draw();

//To Save the graph
	c -> Print("functions.pdf");
	//c -> Print("functions.tex");



} 
