class _FV3_(compmodel)
{
 public:
  _FV3_(compmodel)();
  virtual _FV3_(~compmodel)();
  void setCurrentFs(long fs);
  long getCurrentFs();
  void setRMS(_fv3_float_t msec);
  _fv3_float_t getRMS();
  void setLookahead(_fv3_float_t msec);
  _fv3_float_t getLookahead();
  void setAttack(_fv3_float_t msec);
  _fv3_float_t getAttack();
  void setRelease(_fv3_float_t msec);
  _fv3_float_t getRelease();
  void setThreshold(_fv3_float_t dB);
  _fv3_float_t getThreshold();
  void setSoftKnee(_fv3_float_t dB);
  _fv3_float_t getSoftKnee();
  void setRatio(_fv3_float_t value);
  _fv3_float_t getRatio();
  long getLatency();
  _fv3_float_t getCGain();
  void mute();
  void processreplace(_fv3_float_t *inputL, _fv3_float_t *inputR,
		      _fv3_float_t *outputL, _fv3_float_t *outputR,
		      long numsamples);
  _fv3_float_t getEnv();
  void printconfig();
 private:
  _FV3_(compmodel)(const _FV3_(compmodel)& x);
  _FV3_(compmodel)& operator=(const _FV3_(compmodel)& x);
  void update();
  void updateNRT();
  long currentfs;
  _fv3_float_t RMS, Lookahead;
  _fv3_float_t Attack, Release, Threshold, Ratio, SoftKnee;
  _FV3_(scomp) compL, compR;
  _FV3_(delay) lookaL, lookaR;
  _fv3_float_t currentGain;
};
