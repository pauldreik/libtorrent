#include "glue/glue.hpp"
#include "libtorrent/bdecode.hpp"

void
Fuzz(Glue Data)
{
  libtorrent::bdecode_errors::error_code_enum ec;
  std::int64_t val;
  libtorrent::parse_int(Data.First(), Data.Last(), ':', val, ec);
}
