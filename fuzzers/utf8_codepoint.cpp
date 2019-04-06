#include "glue/glue.hpp"
#include "libtorrent/utf8.hpp"

void
Fuzz(Glue Data)
{
  auto ignored = libtorrent::parse_utf8_codepoint(Data.getStringView());
}
