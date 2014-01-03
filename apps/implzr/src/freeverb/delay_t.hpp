class _FV3_(delay)
{
 public:
  _FV3_(delay)();
  virtual _FV3_(~delay)();
  void setsize(long size);
  long getsize();
  _fv3_float_t	process(_fv3_float_t input);
  void	mute();
  void	setfeedback(_fv3_float_t val);
  _fv3_float_t	getfeedback();
 private:
  _FV3_(delay)(const _FV3_(delay)& x);
  _FV3_(delay)& operator=(const _FV3_(delay)& x);
  _fv3_float_t	feedback;
  _fv3_float_t	*buffer;
  long bufsize;
  long bufidx;
};
