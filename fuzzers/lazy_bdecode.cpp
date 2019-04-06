#include "glue/glue.hpp"
#include "libtorrent/error_code.hpp"
#include "libtorrent/lazy_entry.hpp"

void
Fuzz(Glue Data)
{
  libtorrent::error_code ec;
  libtorrent::lazy_entry ret;
  int pos;
  lazy_bdecode(Data.First(), Data.Last(), ret, ec, &pos);
}
