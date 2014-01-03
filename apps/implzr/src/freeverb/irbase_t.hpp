class _FV3_(irbase)
{
 public:
  _FV3_(irbase)(){};
  virtual _FV3_(~irbase)(){};
  virtual void loadImpulse(_fv3_float_t * inputL, _fv3_float_t * inputR,
			   long size) = 0;
  virtual void loadImpulse(_fv3_float_t * inputL, _fv3_float_t * inputR,
			   long size, unsigned fftflags) = 0;
  virtual void unloadImpulse() = 0;  
  virtual void processreplace(_fv3_float_t *inputL, _fv3_float_t *inputR,
			      _fv3_float_t *outputL, _fv3_float_t *outputR,
			      long numsamples, unsigned options) = 0;
  virtual void muteAll() = 0;
  virtual void setwet(_fv3_float_t db) = 0;
  virtual _fv3_float_t getwet() = 0;
  virtual void setdry(_fv3_float_t db) = 0;
  virtual _fv3_float_t getdry() = 0;
  virtual void setwidth(_fv3_float_t value) = 0;
  virtual _fv3_float_t getwidth() = 0;
  virtual void setLPF(_fv3_float_t value) = 0;
  virtual _fv3_float_t getLPF() = 0;
  virtual void setHPF(_fv3_float_t value) = 0;
  virtual _fv3_float_t getHPF() = 0;
  virtual long getSampleSize() = 0;
  virtual long getLatency() = 0;
 private:
  _FV3_(irbase)(const _FV3_(irbase)& x);
  _FV3_(irbase)& operator=(const _FV3_(irbase)& x);
};
