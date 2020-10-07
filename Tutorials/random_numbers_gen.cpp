#include<iostream>
#include<random>
#include<fstream>

int main(void)
{
  const int N = 1000;
  const int seed = 1;
  //std::random_device rd; 
  std::mt19937 gen(seed); //declarando al generador
  std::uniform_real_distribution<double> dis(0,1);

  std::ofstream fout("data.txt");
  
  for(int n = 0; n <= N; ++n)
    {
      double r=dis(gen);
      fout << r << "\n";  
    }

  fout.close();

  return 0;

}
