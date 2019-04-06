#include "glue/glue.hpp"
#include "libtorrent/torrent_info.hpp"

void
Fuzz(Glue Data)
{
  std::string out;
  libtorrent::sanitize_append_path_element(out, Data.getStringView());
}
