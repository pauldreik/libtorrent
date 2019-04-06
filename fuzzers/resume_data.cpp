

#include "glue/glue.hpp"
#include "libtorrent/add_torrent_params.hpp"
#include "libtorrent/read_resume_data.hpp"
#include <cstdint>

void
Fuzz(Glue Data)
{
  libtorrent::error_code ec;
  auto ignored = libtorrent::read_resume_data(Data.getStringView(), ec);
}
