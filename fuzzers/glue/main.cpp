#include "glue.hpp"
#include "slurp.hpp"

int
main(int argc, char* argv[])
{
  for (int i = 1; i < argc; ++i) {
    const auto garbage = slurp(argv[i]);
    Fuzz(Glue{ garbage.data(), garbage.size() });
  }
}
