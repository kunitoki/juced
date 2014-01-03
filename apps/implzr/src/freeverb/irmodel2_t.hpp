class _FV3_(irmodel2) : public _FV3_(irbase)
{
 public:
  _FV3_(irmodel2)();
  virtual _FV3_(~irmodel2)();
  virtual void loadImpulse(_fv3_float_t * inputL, _fv3_float_t * inputR,
			   long size);
  virtual void loadImpulse(_fv3_float_t * inputL, _fv3_float_t * inputR,
			   long size,
			   unsigned fftflags);
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
  virtual _fv3_float_t	getHPF();
  virtual long getSampleSize();
  virtual long getLatency();

  //
  void loadImpulse(_fv3_float_t * inputL, _fv3_float_t * inputR, long size,
			   unsigned fftflags, long fragSize);
  void setInitialDelay(long numsamples);
  long getInitialDelay();
  long getFragmentSize();
private:
  _FV3_(irmodel2)(const _FV3_(irmodel2)& x);
  _FV3_(irmodel2)& operator=(const _FV3_(irmodel2)& x);
  void processSquare(_fv3_float_t *inputL, _fv3_float_t *inputR,
		     _fv3_float_t *outputL, _fv3_float_t *outputR,
		     unsigned options);
  void processZL(_fv3_float_t *inputL, _fv3_float_t *inputR,
		 _fv3_float_t *outputL, _fv3_float_t *outputR,
		 long numsamples, unsigned options);
  void allocImpulse(long numsaples);
  void freeImpulse();
  void freeFragments();
  void update();
  
  _fv3_float_t wet, wetdB, wet1, wet2;
  _fv3_float_t dry, drydB;
  _fv3_float_t width;

  long fifoSize, impulseSize, fragmentSize;
  _fv3_float_t *fifoL, *fifoR;
  _fv3_float_t *revL, *revR;
  _fv3_float_t *ifftL, *ifftR;
  _fv3_float_t *swapL, *swapR;
  _fv3_float_t *restL, *restR;
  
  std::vector<_FV3_(frag)*> fragments;
  _FV3_(delay) delayL, delayR;
  _FV3_(blockDelay) bdL, bdR;
  _FV3_(efilter) filter;

  long initialDelay;
  _FV3_(delay) delayWL, delayWR;

  long ZLstart;
  _fv3_float_t *ZLframeL, *ZLframeR;
  _fv3_float_t *ZLonlyL, *ZLonlyR;
  _FV3_(delay) ZLdelayL, ZLdelayR;
  _FV3_(delay) ZLdelayWL, ZLdelayWR;
};
