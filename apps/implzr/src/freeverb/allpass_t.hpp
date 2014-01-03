class _FV3_(allpass)
{
 public:
  _FV3_(allpass)();
  virtual _FV3_(~allpass)();
  void setsize(long size);
  long getsize();
  _fv3_float_t	process(_fv3_float_t inp);
  void mute();
  void setfeedback(_fv3_float_t val);
  _fv3_float_t	getfeedback();
 private:
  _FV3_(allpass)(const _FV3_(allpass)& x);
  _FV3_(allpass)& operator=(const _FV3_(allpass)& x);
  _fv3_float_t	feedback;
  _fv3_float_t	*buffer;
  long bufsize;
  long bufidx;
};
