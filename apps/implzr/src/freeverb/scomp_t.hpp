class _FV3_(scomp)
{
 public:
  _FV3_(scomp)();
  virtual _FV3_(~scomp)();
  void setRMS(long value);
  long getRMS();
  void setAttack(long value);
  long getAttack();
  void setRelease(long value);
  long getRelease();
  void setThreshold(_fv3_float_t value);
  _fv3_float_t getThreshold();
  void setSoftKnee(_fv3_float_t dB);
  _fv3_float_t getSoftKnee();
  void setRatio(_fv3_float_t value);
  _fv3_float_t getRatio();
  
  _fv3_float_t process(_fv3_float_t input);
  _fv3_float_t getEnv();
  void mute();
 private:
  _FV3_(scomp)(const _FV3_(scomp)& x);
  _FV3_(scomp)& operator=(const _FV3_(scomp)& x);
  void update();
  long attack;
  _fv3_float_t Attack;
  long release;
  _fv3_float_t Release;
  _fv3_float_t Threshold, threshold_log;
  _fv3_float_t Ratio, r;
  _fv3_float_t SoftKnee, log_soft, lowClip, highClip;
  
  _fv3_float_t attackDelta;
  _fv3_float_t releaseDelta;
  _fv3_float_t currentRatio;
  _fv3_float_t gain;
  _fv3_float_t env, rmsf, theta;
  _FV3_(rms) Rms;
};
