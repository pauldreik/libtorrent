#include "glue/glue.hpp"
#include "libtorrent/config.hpp"
#include "libtorrent/error_code.hpp"
#include "libtorrent/utf8.hpp"
#include <cstdint>

void
Fuzz(Glue Data)
{
  libtorrent::error_code ec;
  libtorrent::utf8_wchar(Data.getStringView(), ec);
}
