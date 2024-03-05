#include <iostream>
#include <array>
#include <random>
#include <stdlib.h>


std::array<size_t,6> diceRand(size_t n)
{
  std::random_device hwseed;
  srand(hwseed());
  std::array<size_t,6> stats = {0,0,0,0,0,0};
  for(auto i =0 ; i < n; ++i)
    stats[rand()%6]++;
  return stats;
}



void analyze(const std::array<size_t, 6> &stats, size_t n)
{
  double maxerror = 0.0;
  for(auto i=0; i < 6; ++i)
  {
    std::cout<<"val "<<i<<": "<<stats[i]/(double)(n)<<std::endl;
    maxerror = std::max(maxerror, std::abs(stats[i]/double(n) - 1.0/6.0));
  }
  std::cout<<"Error max = "<< maxerror<< std::endl<< std::endl;
}

int main(int argc, char**argv)
{
  std::cout<<"Modulo dice:"<<std::endl;
  const size_t N = 2<<24;
  auto result = diceRand(N);
  analyze(result,N);
  

  //....
  
  return 0;
}
