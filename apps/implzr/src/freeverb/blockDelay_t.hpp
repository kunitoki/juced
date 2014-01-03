class _FV3_(blockDelay)
{
public:
  _FV3_(blockDelay)();
  virtual _FV3_(~blockDelay)();
  void setBlock(long size, long n);
  _fv3_float_t * at(_fv3_float_t * i, long prev);
  _fv3_float_t * get(long prev);
  void push(_fv3_float_t * i);
  void mute();
 private:
  _FV3_(blockDelay)(const _FV3_(blockDelay)& x);
  _FV3_(blockDelay)& operator=(const _FV3_(blockDelay)& x);
  void freeF();
  _fv3_float_t * f;
  long N, blockSize, cur;
};
