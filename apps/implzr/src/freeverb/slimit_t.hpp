class _FV3_(slimit)
{
 public:
  _FV3_(slimit)();
  virtual _FV3_(~slimit)();
  void setRMS(long value);
  long getRMS();
  void setLookahead(long value);
  long getLookahead();
  void setAttack(long value);
  long getAttack();
  void setRelease(long value);
  long getRelease();
  void setThreshold(_fv3_float_t value);
  _fv3_float_t getThreshold();
  void setCeiling(_fv3_float_t value);
  _fv3_float_t getCeiling();
  
  _fv3_float_t process(_fv3_float_t input);
  _fv3_float_t getEnv();
  void mute();
 private:
  _FV3_(slimit)(const _FV3_(slimit)& x);
  _FV3_(slimit)& operator=(const _FV3_(slimit)& x);
  void update();
  long lookahead, attack, release;
  _fv3_float_t Lookahead, Attack, Release;
  _fv3_float_t attackDelta, releaseDelta, theta, laDelta;
  _fv3_float_t Threshold, Ceiling;
  
  _fv3_float_t gain;
  _fv3_float_t env, rmsf, delta, peak, dsig;
  _fv3_float_t log_env, R1, C_T2, C_2T, R2;
  _FV3_(rms) Rms;

  _fv3_float_t * buffer;
  long bufidx, bufsize;
};
