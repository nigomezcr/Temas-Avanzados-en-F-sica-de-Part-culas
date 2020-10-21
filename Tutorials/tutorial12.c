//Twelfth tutorial: Creating user defined functions

void tutorial12()
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
	func1 ->Draw("");
	func2 ->Draw("same");

//Put a legend
  TLegend *legend = new TLegend(0.2,0.8,0.4,0.9);
  legend -> SetBorderSize(2);
  legend -> AddEntry(func1, "Line", "l");
  legend -> AddEntry(func2, "Exp sine", "l");
  legend -> Draw();

} 
