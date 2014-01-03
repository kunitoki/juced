class _FV3_(frag)
{
 public:
  _FV3_(frag)();
  virtual _FV3_(~frag)();
  long getSampleSize();
  void registerImpulse(_fv3_float_t * L, _fv3_float_t * R, long size);
  void registerImpulse(_fv3_float_t * L, _fv3_float_t * R, long size,
		       unsigned fftflags);
  void processR2HC(_fv3_float_t * iL, _fv3_float_t * iR,
		   _fv3_float_t * oL, _fv3_float_t * oR);
  void processHC2R(_fv3_float_t * iL, _fv3_float_t * iR,
		   _fv3_float_t * oL, _fv3_float_t * oR);
  void processMULT(_fv3_float_t * iL, _fv3_float_t * iR,
		   _fv3_float_t * oL, _fv3_float_t * oR);
private:
  _FV3_(frag)(const _FV3_(frag)& x);
  _FV3_(frag)& operator=(const _FV3_(frag)& x);
  void allocImpulse(long size);
  void freeImpulse();
  void allocFFT(long size, unsigned fftflags);
  void freeFFT();
  void convertR2SIMD(_fv3_float_t * in, _fv3_float_t * out, long halfsize);
  void convertSIMD2R(_fv3_float_t * in, _fv3_float_t * out, long halfsize);
  void multMONO(_fv3_float_t * iL, _fv3_float_t * fL,
		_fv3_float_t * oL, long count)
#ifdef __GNUC__
    __attribute__((noinline))
#endif
    ;
  
  long isFFTValid;
  long sampleSize;

  _fv3_float_t *impulseL, *impulseR;
  _fv3_float_t *fftImpulseL, *fftImpulseR;
  
  _FFTW_(plan) planRevL, planRevR;
  _FFTW_(plan) planOrigL, planOrigR;
  _fv3_float_t *fftOrigL, *fftOrigR;
};
