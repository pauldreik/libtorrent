#include "libtorrent/upnp.hpp"
#include "glue/glue.hpp"
#include "libtorrent/xml_parse.hpp"
void
Fuzz(Glue Data)
{
  using namespace std::placeholders;

  libtorrent::parse_state s;
  libtorrent::xml_parse(
    Data.getStringView(),
    std::bind(&libtorrent::find_control_url, _1, _2, std::ref(s)));
}
