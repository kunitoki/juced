class _FV3_(irmodel) : public _FV3_(irbase)
{
 public:
  _FV3_(irmodel)();
  virtual _FV3_(~irmodel)();  
  virtual void loadImpulse(_fv3_float_t * inputL, _fv3_float_t * inputR,
			   long size);
  virtual void loadImpulse(_fv3_float_t * inputL, _fv3_float_t * inputR,
			   long size, unsigned fftflags);
  virtual void unloadImpulse();  
  virtual void processreplace(_fv3_float_t *inputL, _fv3_float_t *inputR,
			      _fv3_float_t *outputL, _fv3_float_t *outputR,
			      long numsamples, unsigned options);
  virtual void muteAll();
  virtual void setwet(_fv3_float_t db);
  virtual _fv3_float_t getwet();
  virtual void setdry(_fv3_float_t db);
  virtual _fv3_float_t getdry();
  virtual void setwidth(_fv3_float_t value);
  virtual _fv3_float_t getwidth();
  virtual void setLPF(_fv3_float_t value);
  virtual _fv3_float_t getLPF();
  virtual void setHPF(_fv3_float_t value);
  virtual _fv3_float_t getHPF();
  virtual long getSampleSize();
  virtual long getLatency();
 private:
  _FV3_(irmodel)(const _FV3_(irmodel)& x);
  _FV3_(irmodel)& operator=(const _FV3_(irmodel)& x);
  void processSquare(_fv3_float_t *inputL, _fv3_float_t *inputR,
		     _fv3_float_t *outputL, _fv3_float_t *outputR);
  void allocImpulse(long numsaples);
  void freeImpulse();
  void update();
  void allocFFT(long numsamples, unsigned fftflags);
  void freeFFT();
  
  long sampleSize, impulseSize;
  _fv3_float_t *impulseL, *impulseR;
  _fv3_float_t *fftImpulseL, *fftImpulseR;

  long currentProcessSampleSize;
  _FFTW_(plan) planRevL, planRevR;
  _fv3_float_t *fftRevL, *fftRevR;
  _FFTW_(plan) planOrigL, planOrigR;
  _fv3_float_t *fftOrigL, *fftOrigR;
  
  long current;
  _fv3_float_t *delaylineL, *delaylineR;
  long fifoSize;
  _fv3_float_t *fifoL, *fifoR;
  _fv3_float_t wet,wetdB,wet1,wet2;

  _FV3_(delay) delayL, delayR;
  _fv3_float_t dry,drydB;
  _fv3_float_t width;

  _FV3_(efilter) filter;
};
