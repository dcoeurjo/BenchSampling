#include <iostream>
#include <fstream>
#include "CLI11.hpp"


int main(int argc, char**argv)
{
  CLI::App app{"pts2svg"};
  
  //Params
  double radius=0.2;
  app.add_option("-r", radius, "Disks radius");
  
  std::string inputPTS;
  app.add_option("-i,--input", inputPTS, "Input point cloud (ascii format)");
  
  std::string outputSVG= "output.svg";
  app.add_option("-o,--outpout", outputSVG, "Output file (svg format)");
  CLI11_PARSE(app, argc, argv);
  
  
  std::ofstream outfile(outputSVG);
  outfile<<"<svg height=\"1\" viewBox=\"0 0 1 1\" width=\"1.\" xmlns=\"http://www.w3.org/2000/svg\">  <style type=\"text/css\">  <![CDATA[    circle {    fill: black;    }  ]]>  </style>  <g>"<<std::endl;
  
  
  std::ifstream in(inputPTS);
  double x,y;
  while (in.good())
  {
    in>>x>>y;
    outfile<< " <circle cx=\""+ std::to_string(x)  +"\" cy=\""+ std::to_string(y)  +"\" r=\""+ std::to_string(radius) + "\" />"<<std::endl;

  }
  in.close();
  
  outfile<<"</g> </svg>"<<std::endl;
  
  outfile.close();
  
  return 0;
}
