#include "glue/glue.hpp"
#include "libtorrent/file_storage.hpp"

void
Fuzz(Glue Data)
{
  libtorrent::file_storage fs;
  fs.add_file(Data.getStdString(), 1);
}
