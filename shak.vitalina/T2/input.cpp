#include "input.hpp"
#include "stream_guard.hpp"
#include "delimiter.hpp"
#include <iomanip>
#include <string>

using check = shak::DelimiterIO;
std::istream &shak::operator>>(std::istream &in, ChrLit &&dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  in >> check{'\''} >> dest.ref >> check{'\''};
  return in;
}

std::istream &shak::operator>>(std::istream &in, RatLsp &&dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  long long n = 0;
  unsigned long long d = 0;
  in >> check{'('} >> check{':'} >> check{'N'} >> n;
  in >> check{':'} >> check{'D'} >> d;
  in >> check{':'} >> check{')'};
  if (in)
  {
    dest.ref.first = n;
    dest.ref.second = d;
  }
  return in;
}

std::istream &shak::operator>>(std::istream &in, Str &&dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  std::getline(in >> check{'"'}, dest.ref, '"');
  return in;
}
