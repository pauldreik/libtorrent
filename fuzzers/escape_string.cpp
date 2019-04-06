#include "libtorrent/aux_/escape_string.hpp"
#include "glue/glue.hpp"

void
Fuzz(Glue Data)
{
  auto ignored = libtorrent::escape_string(Data.getStringView());
}
