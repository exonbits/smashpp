//
// Created by morteza on 15-03-2018.
//

#ifndef SMASHPP_TABLE64_HPP
#define SMASHPP_TABLE64_HPP

#include <vector>
#include "def.hpp"
using std::vector;
using std::ifstream;
using std::ofstream;

class Table64 : public DS
{
public:
  Table64          () = default;
  explicit Table64 (u8);
  void config      (u8);
  void update      (u32);               // Update table
//  void  query      (std::array<u64,4>&, u8, u32);   // Query count of ctx
  u64  query       (u32)       const;   // Query count of ctx
  u64  getTotal    ()          const;   // Total count of all items in the table
  u64  countMty    ()          const;   // Number of empty cells in the table
  u64  maxTblVal   ()          const;
  void dump        (ofstream&) const;
  void load        (ifstream&) const;
  void print       ()          const;
  
private:
  vector<u64> tbl;                      // Table of 64 bit counters
  u8          k;                        // Ctx size
  u64         tot;                      // Total # elements so far
};

#endif //SMASHPP_TABLE64_HPP