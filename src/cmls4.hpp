//
// Created by morteza on 27-02-2018.
//

#ifndef SMASHPP_CMLS4_HPP
#define SMASHPP_CMLS4_HPP

#include "def.hpp"

class CMLS4    // Count-min-log sketch, 4 bits per counter
{
 public:
  CMLS4            () : w(DEF_W), d(DEF_D), uhashShift(0), tot(0) {}
  CMLS4            (u64, u8);
  void config      (u64, u8);
  void update      (u64);             // Update sketch
  u16  query       (u64)       const; // Query count of ctx
	void dump        (ofstream&) const;
	void load        (ifstream&) const;
#ifdef DEBUG
  u64  get_total   ()          const; // Total count of all items in the sketch
  u64  count_empty ()          const; // Number of empty cells in the sketch
  u8   max_sk_val  ()          const;
  void print       ()          const;
#endif
  
 private:
  u64         w;                    // Width of sketch
  u8          d /*:BIT_D*/;         // Depth of sketch
  vector<u64> ab;                   // Coefficients of hash functions
  u8          uhashShift;           // Universal hash shift(G-M). (a*x+b)>>(G-M)
  vector<u8>  sk;                   // Sketch
  u64         tot;                  // Total # elements, so far
  
  u8   read_cell   (u64)     const; // Read each cell of the sketch
  void set_a_b     ();              // Set coeffs a, b of hash fns (a*x+b) %P %w
  u64  hash        (u8, u64) const; // MUST provide pairwise independence
  u8   min_log_ctr (u64)     const; // Find min log value in the sketch
#ifdef DEBUG
  void printAB     ()        const;
#endif
};

static constexpr u8 CTR[512] {
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
   1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,
   2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,
   3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,
   4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,
   5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,
   6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,
   7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,
   8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,
   9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,
  10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
  11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11,
  12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
  13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13,
  14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14,
  15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,  // End of 256
   0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15,
   0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15,
   0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15,
   0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15,
   0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15,
   0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15,
   0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15,
   0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15,
   0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15,
   0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15,
   0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15,
   0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15,
   0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15,
   0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15,
   0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15,
   0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15
};
static constexpr u8 INC_CTR[512] {
  16,  17,  18,  19,  20,  21,  22,  23,  24,  25,  26,  27,  28,  29,  30,  31,
  32,  33,  34,  35,  36,  37,  38,  39,  40,  41,  42,  43,  44,  45,  46,  47,
  48,  49,  50,  51,  52,  53,  54,  55,  56,  57,  58,  59,  60,  61,  62,  63,
  64,  65,  66,  67,  68,  69,  70,  71,  72,  73,  74,  75,  76,  77,  78,  79,
  80,  81,  82,  83,  84,  85,  86,  87,  88,  89,  90,  91,  92,  93,  94,  95,
  96,  97,  98,  99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111,
 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127,
 128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143,
 144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159,
 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175,
 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191,
 192, 193, 194, 195, 196, 197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207,
 208, 209, 210, 211, 212, 213, 214, 215, 216, 217, 218, 219, 220, 221, 222, 223,
 224, 225, 226, 227, 228, 229, 230, 231, 232, 233, 234, 235, 236, 237, 238, 239,
 240, 241, 242, 243, 244, 245, 246, 247, 248, 249, 250, 251, 252, 253, 254, 255,
 241, 242, 243, 244, 245, 246, 247, 248, 249, 250, 251, 252, 253, 254, 255, 255,
   1,   2,   3,   3,   5,   6,   7,   7,   9,  10,  11,  11,  13,  14,  15,  15,
  17,  18,  19,  19,  21,  22,  23,  23,  25,  26,  27,  27,  29,  30,  31,  31,
  33,  34,  35,  35,  37,  38,  39,  39,  41,  42,  43,  43,  45,  46,  47,  47,
  49,  50,  51,  51,  53,  54,  55,  55,  57,  58,  59,  59,  61,  62,  63,  63,
  65,  66,  67,  67,  69,  70,  71,  71,  73,  74,  75,  75,  77,  78,  79,  79,
  81,  82,  83,  83,  85,  86,  87,  87,  89,  90,  91,  91,  93,  94,  95,  95,
  97,  98,  99,  99, 101, 102, 103, 103, 105, 106, 107, 107, 109, 110, 111, 111,
 113, 114, 115, 115, 117, 118, 119, 119, 121, 122, 123, 123, 125, 126, 127, 127,
 129, 130, 131, 131, 133, 134, 135, 135, 137, 138, 139, 139, 141, 142, 143, 143,
 145, 146, 147, 147, 149, 150, 151, 151, 153, 154, 155, 155, 157, 158, 159, 159,
 161, 162, 163, 163, 165, 166, 167, 167, 169, 170, 171, 171, 173, 174, 175, 175,
 177, 178, 179, 179, 181, 182, 183, 183, 185, 186, 187, 187, 189, 190, 191, 191,
 193, 194, 195, 195, 197, 198, 199, 199, 201, 202, 203, 203, 205, 206, 207, 207,
 209, 210, 211, 211, 213, 214, 215, 215, 217, 218, 219, 219, 221, 222, 223, 223,
 225, 226, 227, 227, 229, 230, 231, 231, 233, 234, 235, 235, 237, 238, 239, 239,
 241, 242, 243, 243, 245, 246, 247, 247, 249, 250, 251, 251, 253, 254, 255, 255
};

#endif //SMASHPP_CMLS4_HPP