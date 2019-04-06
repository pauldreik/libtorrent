#include "glue/glue.hpp"
#include "libtorrent/aux_/escape_string.hpp"

void
Fuzz(Glue Data)
{
  auto ignored = libtorrent::convert_to_native(Data.getStdString());
}
