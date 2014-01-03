class _FV3_(irmodels) : public _FV3_(irbase)
{
 public:
  _FV3_(irmodels)();
  virtual _FV3_(~irmodels)();
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
  virtual _fv3_float_t	getLPF();
  virtual void setHPF(_fv3_float_t value);
  virtual _fv3_float_t getHPF();
  virtual long getSampleSize();
  virtual long getLatency();
 private:
  _FV3_(irmodels)(const _FV3_(irmodels)& x);
  _FV3_(irmodels)& operator=(const _FV3_(irmodels)& x);

  void allocImpulse(long size);
  void freeImpulse();
  void update();

  _fv3_float_t *impulseL, *impulseR;
  _fv3_float_t *delayL, *delayR;
  long impulseSize, current;
  
  _fv3_float_t wet, wetdB, wet1, wet2, dry, drydB, width;

  _FV3_(efilter) filter;
};
