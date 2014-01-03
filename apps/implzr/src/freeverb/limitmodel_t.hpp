class _FV3_(limitmodel)
{
 public:
  _FV3_(limitmodel)();
  virtual _FV3_(~limitmodel)();
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
  void setCeiling(_fv3_float_t dB);
  _fv3_float_t getCeiling();
  long getLatency();
  _fv3_float_t getCGain();
  void mute();
  void processreplace(_fv3_float_t *inputL, _fv3_float_t *inputR,
		      _fv3_float_t *outputL, _fv3_float_t *outputR,
		      long numsamples);
  _fv3_float_t getEnv();
  void printconfig();
 private:
  _FV3_(limitmodel)(const _FV3_(limitmodel)& x);
  _FV3_(limitmodel)& operator=(const _FV3_(limitmodel)& x);
  void update();
  void updateNRT();
  long currentfs;
  _fv3_float_t RMS, Lookahead;
  _fv3_float_t Attack, Release, Threshold, Ceiling;
  _FV3_(slimit) limitL, limitR;
  _FV3_(delay) lookaL, lookaR;
  _fv3_float_t currentGain;
};
