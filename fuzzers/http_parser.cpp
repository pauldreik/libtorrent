#include "glue/glue.hpp"

#include "libtorrent/http_parser.hpp"

void
Fuzz(Glue Data)
{
  libtorrent::http_parser parser(1);
  bool error = false;
  parser.incoming(Data.getSpan(), error);
}
