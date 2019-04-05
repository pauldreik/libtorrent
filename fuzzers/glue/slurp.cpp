#include "slurp.hpp"
#include <cassert>
#include <fstream>
#include <sstream>
std::string
slurp(const char* filename)
{
  std::ifstream in(filename);
  assert(in);
  std::stringstream sstr;
  sstr << in.rdbuf();
  return sstr.str();
}
