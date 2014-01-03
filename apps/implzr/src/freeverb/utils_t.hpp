class _FV3_(utils)
{
 public:
  static _fv3_float_t dB2R(_fv3_float_t dB);
  static _fv3_float_t R2dB(_fv3_float_t real);
  static long ms2sample(_fv3_float_t msec, long fs);
  static void mute(_fv3_float_t * f, long t);
  static long checkPow2(long i);
  static bool isPrime(long number);
};
