#include <iostream>
#include <fstream>
#include <cmath>
#include <array>
#include <vector>
#include <string>
#include <random>

#include "CLI11.hpp"

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

double computeDiskIntegrationError(const Pointset &P)
{
  //.. do something
  return 0.0;
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
  CLI::App app{"whitenoise"};
  
  //Params
  int nbSPP = 1024;
  app.add_option("-n,--nbSpp", nbSPP, "Number of samples");
  std::string outputPTS="out_" + std::to_string(nbSPP)+".pts";
  app.add_option("-o,--outpout", outputPTS, "Output file (ascii format)");
  size_t seed;
  app.add_option("--seed", seed, "Seed");
  bool integrationOnly=false;
  app.add_flag("--integrationOnly",integrationOnly,"Only computes the integration");
  CLI11_PARSE(app, argc, argv);

  
  Pointset WN = whitenoise2D(nbSPP,seed);
  
  if (integrationOnly)
    std::cout<<computeDiskIntegrationError(WN)<<std::endl;
  else
    exportPointset(WN, outputPTS);
  
  return 0;
}
