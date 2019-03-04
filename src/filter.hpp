#ifndef PROJECT_FILTER_HPP
#define PROJECT_FILTER_HPP

#include <memory>
#include "par.hpp"

namespace smashpp {
class Filter {
 public:
  uint64_t nSegs;

  explicit Filter(const Param&);
  void smooth_seg(const Param&);
  void merge_extract_seg(uint32_t, std::string, std::string) const;
  void aggregate_mid_pos(uint32_t, std::string, std::string) const;
  void aggregate_final_pos(std::string, std::string) const;

 private:
  WType wtype;
  uint32_t wsize;
  std::string message;
  std::vector<float> window;
  struct Position {
    uint64_t beg;
    uint64_t end;
    Position(uint64_t b, uint64_t e) : beg(b), end(e) {}
  };

  void set_wsize(const Param&);
  void show_info(const Param&) const;
  void make_window();
  void hamming();
  void hann();
  void blackman();
  void triangular();  // Bartlett window
  void welch();
  void sine();
  void nuttall();
  template <bool SaveFilter>
  void smooth_seg_rect(const Param&);
  template <bool SaveFilter>
  void smooth_seg_non_rect(const Param&);
  // bool is_mergable (const Position&, const Position&) const;
#ifdef BENCH
  template <typename Iter, typename Value>
  void shift_left_insert(Iter, Value);
#endif
};
}  // namespace smashpp

#endif  // PROJECT_FILTER_HPP