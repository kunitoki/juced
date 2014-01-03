class _FV3_(firwindow)
{
 public:
  static void Square(_fv3_float_t w[], const long N);
  static void Hamming(_fv3_float_t w[], const long N);
  static void Hanning(_fv3_float_t w[], const long N);
  static void Blackman(_fv3_float_t w[], const long N);
  static _fv3_float_t i_zero(const _fv3_float_t x);
  static void Kaiser(_fv3_float_t w[], const long N,
		     const _fv3_float_t beta);
  static _fv3_float_t KaiserBeta(const _fv3_float_t dB);
  static void CosROW(_fv3_float_t w[], const long N,
		     const _fv3_float_t fc, const _fv3_float_t alpha);

  static void Sinc(_fv3_float_t sinc[], const long N, const _fv3_float_t fc);
};
