#include <iostream>
#include <chrono>


double dosomething()
{
  double v=0.0;
  for(auto i=0;  i < 2<<12; ++i)
    v+= std::sqrt(i);
  return v;
}

int main(int argc, char**argv)
{
   
  std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();

  
  std::cout<<"val = "<<dosomething()<<std::endl;
  
  std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
  auto time_span = std::chrono::duration_cast< std::chrono::microseconds >(t2 - t1);
  std::cout << "It took me " << time_span.count()<< " milliseconds."<<std::endl;
  
  
}
