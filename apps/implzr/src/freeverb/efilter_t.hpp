class _FV3_(efilter)
{
public:
  _FV3_(efilter)();
  virtual _FV3_(~efilter)();
  _fv3_float_t	processL(_fv3_float_t input);
  _fv3_float_t	processR(_fv3_float_t input);
  void	setLPF(_fv3_float_t val);
  _fv3_float_t	getLPF();
  void	setHPF(_fv3_float_t val);
  _fv3_float_t	getHPF();
private:
  _FV3_(efilter)(const _FV3_(efilter)& x );
  void updateP(IIR * iir, _fv3_float_t pole);
  _fv3_float_t processP(IIR * iir, _fv3_float_t input);
  void updateZ(IIR * iir, _fv3_float_t pole);
  _fv3_float_t processZ(IIR * iir, _fv3_float_t input);
  _fv3_float_t hpfCof, lpfCof;
  IIR lpfL, lpfR, hpfL, hpfR;
};
