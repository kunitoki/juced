class _FV3_(stenh)
{
 public:
  _FV3_(stenh)();
  virtual _FV3_(~stenh)();
  void setCurrentFs(long fs);
  long getCurrentFs();
  void mute();
  void processreplace(_fv3_float_t *inputL, _fv3_float_t *inputR,
		      _fv3_float_t *outputL, _fv3_float_t *outputR,
		      long numsamples);
  void setChValL(_fv3_float_t value);
  void setChValR(_fv3_float_t value);
  void setBPF_LPF(_fv3_float_t value);
  void setBPF_HPF(_fv3_float_t value);
  void setBRF_LPF(_fv3_float_t value);
  void setBRF_HPF(_fv3_float_t value);
  void setBPFDepth(_fv3_float_t msec);
  void setBRFDepth(_fv3_float_t msec);
  void setOverallDepth(_fv3_float_t msec);
  void setDiffusion(_fv3_float_t value);
  void setWidth(_fv3_float_t value);
  void setDry(_fv3_float_t value);
  void setThreshold(_fv3_float_t value);
 private:
  _FV3_(stenh)(const _FV3_(stenh)& x);
  _FV3_(stenh)& operator=(const _FV3_(stenh)& x);
  void updateNRT();
  
  long currentfs;
  _fv3_float_t Depth1, Depth2, Depth3;
  _fv3_float_t chvL, chvR, diffusion, width, dry;
  _fv3_float_t levelSum, levelDiff;
  _FV3_(efilter) bpf, lpf, hpf;
  _FV3_(delay) delayV, delayU, delayF;
  _FV3_(scomp) compS, compD;
};
