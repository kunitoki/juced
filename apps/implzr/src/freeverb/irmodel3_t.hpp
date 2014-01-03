class _FV3_(irmodel3) : public _FV3_(irbase)
{
 public:
  _FV3_(irmodel3)();
  virtual _FV3_(~irmodel3)();
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

  //
  virtual void loadImpulse(_fv3_float_t * inputL, _fv3_float_t * inputR,
			   long size, unsigned fftflags, long fragSize);
  virtual void loadImpulse(_fv3_float_t * inputL, _fv3_float_t * inputR,
			   long size, unsigned fftflags, long sFragSize,
			   long factor);
  virtual void resume();
  virtual void suspend();
  
  void setInitialDelay(long numsamples);
  long getInitialDelay();
  
  long getSFragmentSize();
  long getSFragmentCount();
  long getLFragmentSize();
  long getLFragmentCount();
  void printconfig();
protected:
  _FV3_(irmodel3)(const _FV3_(irmodel3)& x);
  _FV3_(irmodel3)& operator=(const _FV3_(irmodel3)& x);
  virtual void processZL(_fv3_float_t *inputL, _fv3_float_t *inputR,
			 _fv3_float_t *outputL, _fv3_float_t *outputR,
			 long numsamples, unsigned options);
  void allocSwap(long ssize, long lsize);
  void freeImpulse();
  void allocFragments(std::vector<_FV3_(frag)*> *to,
		      _fv3_float_t *inputL, _fv3_float_t *inputR,
		      long fragSize, long num, long rest,
		      unsigned fftflags);
  void freeFragments();
  void update();
  
  _fv3_float_t wet, wetdB, wet1, wet2;
  _fv3_float_t dry, drydB;
  _fv3_float_t width;
  
  long fifoSize, impulseSize;
  _fv3_float_t *fifoL, *fifoR;

  long sFragmentSize, lFragmentSize;
  _fv3_float_t *sRevL, *sRevR, *lRevL, *lRevR;
  _fv3_float_t *sifftL, *sifftR, *lifftL, *lifftR;
  _fv3_float_t *sSwapL, *sSwapR, *lSwapL, *lSwapR;
  _fv3_float_t *restL, *restR;

  std::vector<_FV3_(frag)*> sFragments, lFragments;
  _FV3_(blockDelay) sBlockDelayL, sBlockDelayR;
  _FV3_(blockDelay) lBlockDelayL, lBlockDelayR;

  long Lcursor, Scursor, Lstep;
  _fv3_float_t *sFrameL, *sFrameR, *lFrameL, *lFrameR;
  _fv3_float_t *sOnlyL, *sOnlyR;

  long initialDelay;
  _FV3_(delay) ZLdelayL, ZLdelayR;
  _FV3_(delay) ZLdelayWL, ZLdelayWR;

  _FV3_(efilter) filter;
};
