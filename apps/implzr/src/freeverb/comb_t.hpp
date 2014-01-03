class _FV3_(comb)
{
public:
  _FV3_(comb)();
  virtual _FV3_(~comb)();
  void setsize(long size);
  long getsize();
  _fv3_float_t	process(_fv3_float_t inp);
  void mute();
  void setdamp(_fv3_float_t val);
  _fv3_float_t	getdamp();
  void	setfeedback(_fv3_float_t val);
  _fv3_float_t	getfeedback();
private:
  _FV3_(comb)(const _FV3_(comb)& x);
  _FV3_(comb)& operator=(const _FV3_(comb)& x);
  _fv3_float_t	*buffer;
  _fv3_float_t	feedback;
  _fv3_float_t	filterstore;
  _fv3_float_t	damp1;
  _fv3_float_t	damp2;
  long bufsize;
  long bufidx;
};
