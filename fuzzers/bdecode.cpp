#include "libtorrent/bdecode.hpp"
#include "glue/glue.hpp"
#include "libtorrent/torrent_info.hpp"

void
Fuzz(Glue Data)
{
  libtorrent::bdecode_node e;
  libtorrent::error_code ec;
  int ret = libtorrent::bdecode(Data.First(), Data.Last(), e, ec);
  if (0 == ret) {
    libtorrent::torrent_info info(e, ec);
  }
}
