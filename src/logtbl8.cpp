//
// Created by morteza on 15-03-2018.
//

#include <algorithm>
#include <fstream>
#include "logtbl8.hpp"
using std::cerr;

LogTable8::LogTable8 (u8 k_) {
  config(k_);
}

void LogTable8::config (u8 k_) {
  k   = k_;
  tot = 0;
  try { tbl.resize(4<<(k<<1)); }    // 4<<2k = 4*2^2k = 4*4^k = 4^(k+1)
  catch (std::bad_alloc& b) {
    cerr << "Error: failed memory allocation.";
    throw EXIT_FAILURE;
  }
}

void LogTable8::update (u32 ctx) {
  if (!(tot++ % POW2[tbl[ctx]]))
    ++tbl[ctx];
}

u64 LogTable8::query (u32 ctx) const {
  return POW2[tbl[ctx]] - 1;
}

u64 LogTable8::getTotal () const {
  return tot;
}

u64 LogTable8::countMty () const {
  return static_cast<u64>(std::count(tbl.begin(), tbl.end(), 0));
}

u32 LogTable8::maxTblVal () const {
  return *std::max_element(tbl.begin(), tbl.end());
}

void LogTable8::dump (ofstream& ofs) const {
  ofs.write((const char*) &tbl[0], tbl.size());
//  ofs.close();
}

void LogTable8::load (ifstream& ifs) const {
  ifs.read((char*) &tbl[0], tbl.size());
}

void LogTable8::printTbl () const {
  for (auto c : tbl)
    cerr << static_cast<u16>(c) << '\n';
}