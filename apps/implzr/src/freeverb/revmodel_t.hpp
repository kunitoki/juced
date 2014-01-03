class _FV3_(revmodel)
{
public:
  _FV3_(revmodel)();
  virtual _FV3_(~revmodel)();
  void resetfs(long fs);
  long getCurrentFs();
  void setOverSamplingFactor(long factor, long converter_type);
  void setOverSamplingFactor(long factor);
  long getOverSamplingFactor();
  void setInitialDelay(long numsamples);
  long getInitialDelay();
  long getLatency();
  void mute();
  void processreplace(_fv3_float_t *inputL, _fv3_float_t *inputR,
		      _fv3_float_t *outputL, _fv3_float_t *outputR,
		      long numsamples);
  void setroomsize(_fv3_float_t value);
  _fv3_float_t	getroomsize();
  void setdamp(_fv3_float_t value);
  _fv3_float_t	getdamp();
  void setwet(_fv3_float_t value);
  _fv3_float_t	getwet();
  void setdry(_fv3_float_t value);
  _fv3_float_t	getdry();
  void setwidth(_fv3_float_t value);
  _fv3_float_t	getwidth();
  void printconfig();
private:
  _FV3_(revmodel)(const _FV3_(revmodel)& x);
  _FV3_(revmodel)& operator=(const _FV3_(revmodel)& x);
  long currentfs;
  long f_(long def, _fv3_float_t factor);
  void allocFilter(long ncomb, long nallpass);
  void freeFilter();
  void setFilter(_fv3_float_t factor);
  void setAllpass();
  _fv3_float_t roomsize, damp;
  _fv3_float_t wet, wet1, wet2, dry, width;
  long numcombs;
  long numallpasses;
  _FV3_(comb) *combL;
  _FV3_(comb) *combR;
  _FV3_(allpass) *allpassL;
  _FV3_(allpass) *allpassR;
  long defaultfs;
  _FV3_(src) SRC;
  
  long initialDelay;
  _FV3_(delay) delayL, delayR;
  _FV3_(delay) delayWL, delayWR;
};
