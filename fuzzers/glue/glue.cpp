#include "glue.hpp"

extern "C" int
LLVMFuzzerTestOneInput(const std::uint8_t* Data, std::size_t Size);

extern "C" int
LLVMFuzzerTestOneInput(const std::uint8_t* Data, std::size_t Size)
{
  Fuzz(Glue(Data, Size));
  return 0;
}
