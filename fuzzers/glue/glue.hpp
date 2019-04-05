
#pragma once

// the idea of this is to have all the
// conversions in one place, so one doesn't
// have to do those ugly casts everywhere

#include "libtorrent/span.hpp"
#include "libtorrent/string_view.hpp"
#include <string>
#include <cstdint>

struct Glue
{
  Glue(const std::uint8_t* Data, std::size_t Size)
    : m_Data(reinterpret_cast<const char*>(Data))
    , m_Size(Size)
  {}
  Glue(const char* Data, std::size_t Size)
    : m_Data(Data)
    , m_Size(Size)
  {}
  const char* const m_Data;
  const std::size_t m_Size;

  libtorrent::string_view getStringView() const
  {
    return { getConstChar(), m_Size };
  }

  const char* getConstChar() const
  {
    return reinterpret_cast<const char*>(m_Data);
  }

  libtorrent::span<const char> getSpan() const
  {
    return { getConstChar(),
             static_cast<libtorrent::span<const char>::difference_type>(
               m_Size) };
  }
  std::string getStdString() const { return {First(),Last()};}
  const char* First() const { return getConstChar(); }
  const char* Last() const { return getConstChar() + m_Size; }
};

// this is what each of the fuzzer targets is to implement
void
Fuzz(Glue glue);
