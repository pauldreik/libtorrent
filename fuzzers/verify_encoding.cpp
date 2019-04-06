#include "glue/glue.hpp"
#include "libtorrent/torrent_info.hpp"

void
Fuzz(Glue Data)
{
  std::string str = Data.getStdString();
  libtorrent::verify_encoding(str);
}
