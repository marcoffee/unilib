// This file is part of UniLib.
//
// Copyright 2014 by Institute of Formal and Applied Linguistics, Faculty of
// Mathematics and Physics, Charles University in Prague, Czech Republic.
//
// UniLib is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as
// published by the Free Software Foundation, either version 3 of
// the License, or (at your option) any later version.
//
// UniLib is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with UniLib.  If not, see <http://www.gnu.org/licenses/>.

// UniLib version: 0.9.9
// Unicode version: 6.3.0

#pragma once

#include <cstddef>
#include <string>

namespace ufal {
namespace unilib {

class unicode {
  enum : uint8_t {
    _Lu = 1, _Ll = 2, _Lt = 3, _Lm = 4, _Lo = 5,
    _Mn = 6, _Mc = 7, _Me = 8,
    _Nd = 9, _Nl = 10, _No = 11,
    _Pc = 12, _Pd = 13, _Ps = 14, _Pe = 15, _Pi = 16, _Pf = 17, _Po = 18,
    _Sm = 19, _Sc = 20, _Sk = 21, _So = 22,
    _Zs = 23, _Zl = 24, _Zp = 25,
    _Cc = 26, _Cf = 27, _Cs = 28, _Co = 29, _Cn = 30
  };

 public:
  enum : uint32_t {
    Lu = 1 << _Lu, Ll = 1 << _Ll, Lt = 1 << _Lt, Lut = Lu | Lt, LC = Lu | Ll | Lt,
      Lm = 1 << _Lm, Lo = 1 << _Lo, L = Lu | Ll | Lt | Lm | Lo,
    Mn = 1 << _Mn, Mc = 1 << _Mc, Me = 1 << _Me, M = Mn | Mc | Me,
    Nd = 1 << _Nd, Nl = 1 << _Nl, No = 1 << _No, N = Nd | Nl | No,
    Pc = 1 << _Pc, Pd = 1 << _Pd, Ps = 1 << _Ps, Pe = 1 << _Pe, Pi = 1 << _Pi,
      Pf = 1 << _Pf, Po = 1 << _Po, P = Pc | Pd | Ps | Pe | Pi | Pf | Po,
    Sm = 1 << _Sm, Sc = 1 << _Sc, Sk = 1 << _Sk, So = 1 << _So, S = Sm | Sc | Sk | So,
    Zs = 1 << _Zs, Zl = 1 << _Zl, Zp = 1 << _Zp, Z = Zs | Zl | Zp,
    Cc = 1 << _Cc, Cf = 1 << _Cf, Cs = 1 << _Cs, Co = 1 << _Co, Cn = 1 << _Cn, C = Cc | Cf | Cs | Co | Cn
  };

  static inline uint32_t category(char32_t chr);

  static inline char32_t uppercase(char32_t chr);

  static inline char32_t lowercase(char32_t chr);

 private:
  static const char32_t CHARS = 0x110000;
  static const int32_t DEFAULT_CAT = Cn;

  static const uint8_t category_index[CHARS >> 8];
  static const uint8_t category_block[][256];
  static const uint8_t othercase_index[CHARS >> 8];
  static const int32_t othercase_block[][256];
};

uint32_t unicode::category(char32_t chr) {
  return chr < CHARS ? 1 << category_block[category_index[chr >> 8]][chr & 0xFF] : DEFAULT_CAT;
}

char32_t unicode::uppercase(char32_t chr) {
  return chr < CHARS && category(chr) & Ll ? chr + othercase_block[othercase_index[chr >> 8]][chr & 0xFF] : chr;
}

char32_t unicode::lowercase(char32_t chr) {
  return chr < CHARS && category(chr) & Lut ? chr + othercase_block[othercase_index[chr >> 8]][chr & 0xFF] : chr;
}

} // namespace unilib
} // namespace ufal