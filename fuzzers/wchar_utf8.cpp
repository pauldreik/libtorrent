#include "glue/glue.hpp"
#include "libtorrent/config.hpp"
#include "libtorrent/error_code.hpp"
#include "libtorrent/utf8.hpp"
#include "libtorrent/version.hpp"
#include <cstdint>

void
Fuzz(Glue Data)
{
  libtorrent::error_code ec;
  libtorrent::wchar_utf8(Data.getStdWString(), ec);
}
