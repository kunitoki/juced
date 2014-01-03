class _FV3_(src)
{
 public:
  _FV3_(src)();
  virtual _FV3_(~src)();
  void setSRCFactor(long factor, long converter_type);
  void setSRCFactor(long factor);
  long getSRCFactor();
  long getLatency();
  long usrc(_fv3_float_t *inputL, _fv3_float_t *inputR,
	    _fv3_float_t *outputL, _fv3_float_t *outputR,
	    long numsamples);
  long dsrc(_fv3_float_t *inputL, _fv3_float_t *inputR,
	     _fv3_float_t *outputL, _fv3_float_t *outputR,
	     long numsamples);
 private:
  _FV3_(src)(const _FV3_(src)& x);
  _FV3_(src)& operator=(const _FV3_(src)& x);
  void process(_SRC_(SRC_STATE) * state, _SRC_(SRC_DATA) * data);
  void freeSRC();
  long filloutSRC();
  long overSamplingFactor;
  _SRC_(SRC_STATE) *src_stateL, *src_stateR;
  _SRC_(SRC_STATE) *src_stateLV, *src_stateRV;
  _SRC_(SRC_DATA) src_dataL, src_dataR;
  _SRC_(SRC_DATA) src_dataLV, src_dataRV;
  long src_errorL, src_errorR;
  long src_channels;
  long src_converter;
  long latency;
};
