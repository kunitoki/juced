class _FV3_(nrev)
{
 public:
  _FV3_(nrev)();
  virtual _FV3_(~nrev)();
  void resetfs(long fs);
  long getCurrentFs();
  void setOverSamplingFactor(long factor, long converter_type);
  void setOverSamplingFactor(long factor);
  long getOverSamplingFactor();
  void setInitialDelay(long numsamples);
  long getInitialDelay();
  long getLatency();
  void setDefault();
  void setDefaultFeedback();
  void mute();
  void processreplace(_fv3_float_t *inputL, _fv3_float_t *inputR,
		       _fv3_float_t *outputL, _fv3_float_t *outputR,
		       long numsamples);
  void setroomsize(_fv3_float_t value);
  _fv3_float_t	getroomsize();
  void setfeedback(_fv3_float_t value);
  _fv3_float_t	getfeedback();
  void setdamp(_fv3_float_t value);
  _fv3_float_t	getdamp();
  void setdamp2(_fv3_float_t value);
  _fv3_float_t	getdamp2();
  void setdamp3(_fv3_float_t value);
  _fv3_float_t	getdamp3();
  void setwet(_fv3_float_t value);
  _fv3_float_t	getwet();
  void setdry(_fv3_float_t value);
  _fv3_float_t	getdry();
  void setwidth(_fv3_float_t value);
  _fv3_float_t	getwidth();
  void printconfig();
 private:
  _FV3_(nrev)(const _FV3_(nrev)& x);
  _FV3_(nrev)& operator=(const _FV3_(nrev)& x);
  long currentfs;
  long f_(long def, _fv3_float_t factor);
  long p_(long def, _fv3_float_t factor);
  void update();
  void allocFilter(long ncomb, long nallpass);
  void freeFilter();
  void setFilter(_fv3_float_t factor);

  _fv3_float_t roomsize, feedback;
  _fv3_float_t damp, damp2, damp3;
  _fv3_float_t wetReal, wet, wet1,wet2;
  _fv3_float_t dryReal, dry;
  _fv3_float_t width;
  long numcombs;
  long numallpasses;
  _FV3_(comb) *combL;
  _FV3_(comb) *combR;
  _FV3_(allpass) *allpassL;
  _FV3_(allpass) *allpassR;
  _FV3_(src) SRC;

  long initialDelay;
  _FV3_(delay) delayL, delayR;
  _FV3_(delay) delayWL, delayWR;
};
