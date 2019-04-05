#include "glue/glue.hpp"
#include "libtorrent/magnet_uri.hpp"

void
Fuzz(Glue Data)
{
  libtorrent::error_code ec;
  auto ignored = libtorrent::parse_magnet_uri(Data.getStringView(), ec);
}
