#include "libtorrent/gzip.hpp"
#include "glue/glue.hpp"

void
Fuzz(Glue Data)
{
  libtorrent::error_code ec;
  std::vector<char> out;
  const int maximum_size = 100000;
  libtorrent::inflate_gzip(Data.getStringView(), out, maximum_size, ec);
}
