//
// Created by morteza on 30-06-2018.
//

#ifndef PROJECT_MDLPAR_HPP
#define PROJECT_MDLPAR_HPP

struct STMMPar;

struct MMPar {
  u8    k;         // Context size
  u64   w;         // Width of count-min-log sketch
  u8    d;         // Depth of count-min-log sketch
  u8    ir;        // Inverted repeat
  float alpha;
  float gamma;
  Container cont;  // Tbl 64, Tbl 32, LogTbl 8, Sketch 4
  shared_ptr<STMMPar> child;

  MMPar (u8 k_, u64 w_, u8 d_, u8 ir_, float a_, float g_)
    : k(k_), w(w_), d(d_), ir(ir_), alpha(a_), gamma(g_),
      cont(Container::TABLE_64), child(nullptr) {}
  MMPar (u8 k_, u8 ir_, float a_, float g_) : MMPar(k_, 0, 0, ir_, a_, g_) {}
};

struct STMMPar {
  u8    k;
  u8    thresh;
  u8    ir;
  float alpha;
  float gamma;
  u8    miss;
  bool  enabled;
//  shared_ptr<MMPar> parent; //todo. check if necessary

  STMMPar (u8 k_, u8 t_, u8 ir_, float a_, float g_)
    : k(k_), thresh(t_), ir(ir_), alpha(a_), gamma(g_), miss(0), enabled(true){}
};

struct ProbPar {
  float  alpha;
  double sAlpha;
  u64    mask;
  u8     shl;
  u64    l;
  u8     numSym;
  u64    r;
  u8     revNumSym;

  ProbPar () = default;
  ProbPar (float a, u64 m, u8 sh) : alpha(a), mask(m), shl(sh),
    sAlpha(static_cast<double>(CARDINALITY*alpha)) {}
  void config (u8);//todo
  void config (u64);//todo
  void config (char, u64);
  void config_ir (u8);//todo
  void config_ir (u64, u64);//todo
  void config_ir (char, u64, u64);
};

inline void ProbPar::config (u8 nsym) {//todo
  numSym = nsym;
}

inline void ProbPar::config (u64 ctx) {//todo
  l = ctx<<2u;
}

inline void ProbPar::config (char c, u64 ctx) {
  numSym = NUM[static_cast<u8>(c)];
  l      = ctx<<2u;
}

inline void ProbPar::config_ir (u8 nsym) {//todo
  numSym    = nsym;
  revNumSym = static_cast<u8>(3 - nsym);
}

inline void ProbPar::config_ir (u64 ctx, u64 ctxIr) {//todo
  l = ctx<<2u;
  r = ctxIr>>2u;
}

inline void ProbPar::config_ir (char c, u64 ctx, u64 ctxIr) {
  numSym    = NUM[static_cast<u8>(c)];
  l         = ctx<<2u;
  revNumSym = REVNUM[static_cast<u8>(c)];    // = 3 - numSym
  r         = ctxIr>>2u;
}

#endif //PROJECT_MDLPAR_HPP