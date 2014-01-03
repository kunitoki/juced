class _FV3_(rms)
{
 public:
  _FV3_(rms)();
  virtual _FV3_(~rms)();
  void setsize(long size);
  long getsize();
  _fv3_float_t process(_fv3_float_t inp);
  void	mute();
 private:
  _FV3_(rms)(const _FV3_(rms)& x);
  _FV3_(rms)& operator=(const _FV3_(rms)& x);
  _fv3_float_t *buffer;
  _fv3_float_t sum;
  _fv3_float_t bufs;
  long bufsize;
  long bufidx;
};
