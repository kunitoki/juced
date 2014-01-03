class _FV3_(firfilter)
{
 public:
  static void lpf(_fv3_float_t h[], const long N, const long WINDOW,
		  const _fv3_float_t fc, const _fv3_float_t param);
  static void hpf(_fv3_float_t h[], const long N, const long WINDOW,
		  const _fv3_float_t fc, const _fv3_float_t param);
  static void bef(_fv3_float_t h[], const long N, const long WINDOW,
		  const _fv3_float_t fc1, const _fv3_float_t fc2,
		  const _fv3_float_t param);
  static void bpf(_fv3_float_t h[], const long N, const long WINDOW,
		  const _fv3_float_t fc1, const _fv3_float_t fc2,
		  const _fv3_float_t param);
};
