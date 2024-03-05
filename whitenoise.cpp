#include <iostream>
#include <fstream>
#include <cmath>
#include <array>
#include <vector>
#include <string>
#include <random>


using Sample = std::array<double,2>;
using Pointset = std::vector<Sample>;

void exportPointset(const Pointset &P, const std::string & filename)
{
  std::ofstream ofs;
  ofs.open (filename, std::ofstream::out | std::ofstream::app);
  for(auto &s: P)
    ofs << s[0]<<" "<<s[1]<<std::endl;
  
  ofs.close();
}


Pointset whitenoise2D(size_t N, size_t seed = 12345)
{
  std::default_random_engine generator(seed);
  std::uniform_real_distribution<double> distribution(0.0,1.0);
  
  Pointset P(N);
  for(auto i=0; i < N; ++i)
    P[i] = { distribution(generator),distribution(generator) };

  return P;
}

int main(int argc, char ** argv)
{
  
  Pointset WN = whitenoise2D(1024);
  
  exportPointset(WN, "WN-1024.pts");
  
  return 0;
}
