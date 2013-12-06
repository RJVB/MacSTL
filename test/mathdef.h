/*	mathdef.h:	constant definitions
 */

#ifndef _MATHDEF_H
#define _MATHDEF_H

#ifndef M_LN2
#	define M_LN2	0.69314718055994530942
#endif
#ifndef M_SQRT2
#	define M_SQRT2	1.41421356237309504880
#endif

#if	defined(E) && !defined(M_E)
#	define M_E E
#elif !defined(M_E)
#	define M_E		2.7182818284590452354
#endif

#ifndef M_LOG2E
#	define M_LOG2E	1.4426950408889634074
#endif
#ifndef M_LOG10E
#	define M_LOG10E	0.43429448190325182765
#endif
#ifndef M_LN10
#	define M_LN10	2.30258509299404568402
#endif
#ifndef M_SQRT1_2
#	define M_SQRT1_2	0.70710678118654752440
#endif

/*	approximations provided by SUN */
#ifndef M_PI
#	define M_PI	3.14159265358979323846
#endif
#ifndef M_2PI
#	define M_2PI	6.28318530717958647692
#endif
#ifndef M_PI_2
#	define M_PI_2	1.57079632679489661923
#endif
#ifndef M_PI_4
#	define M_PI_4	0.78539816339744830962
#endif
#ifndef M_PI_8
#	define M_PI_8	0.392699081698724154810
#endif
#ifndef M_1_PI
#	define M_1_PI	0.31830988618379067154
#endif
#ifndef M_2_PI
#	define M_2_PI	0.63661977236758134308
#endif
#ifndef M_2_SQRTPI
#	define M_2_SQRTPI	1.12837916709551257390
#endif

/* approximation obtained by acos( -1.0) on a SUN/4 -- not as precise as they seem!!! (20040820)	*/
#ifndef __M_PI
#	define __M_PI	3.141592653589793115997963468544185161590576172
#endif
#ifndef __M_2PI
#	define __M_2PI	6.283185307179586231995926937088370323181152344
#endif
#ifndef __M_PI_2
#	define __M_PI_2	1.570796326794896557998981734272092580795288086
#endif
#ifndef __M_PI_4
#	define __M_PI_4	0.785398163397448278999490867136046290397644043
#endif
#ifndef __M_PI_8
#	define __M_PI_8	0.392699081698724139499745433568023145198822021
#endif
#ifndef __M_1_PI
#	define __M_1_PI	0.318309886183790691216444201927515678107738495
#endif
#ifndef __M_2_PI
#	define __M_2_PI	0.636619772367581382432888403855031356215476990
#endif
#ifndef __M_2_SQRTPI
#	define __M_2_SQRTPI	1.128379167095512558560699289955664426088333130
#endif

/* The above constants are not adequate for computation using `long double's.
   Therefore we provide as an extension constants with similar names as a
   GNU extension.  Provide enough digits for the 128-bit IEEE quad.  */
#ifdef __GNUC__
# define M_El		2.7182818284590452353602874713526625L  /* e */
# define M_LOG2El	1.4426950408889634073599246810018922L  /* log_2 e */
# define M_LOG10El	0.4342944819032518276511289189166051L  /* log_10 e */
# define M_LN2l		0.6931471805599453094172321214581766L  /* log_e 2 */
# define M_LN10l	2.3025850929940456840179914546843642L  /* log_e 10 */
# define M_PIl		3.1415926535897932384626433832795029L  /* pi */
# define M_PI_2l	1.5707963267948966192313216916397514L  /* pi/2 */
# define M_PI_4l	0.7853981633974483096156608458198757L  /* pi/4 */
# define M_1_PIl	0.3183098861837906715377675267450287L  /* 1/pi */
# define M_2_PIl	0.6366197723675813430755350534900574L  /* 2/pi */
# define M_2_SQRTPIl	1.1283791670955125738961589031215452L  /* 2/sqrt(pi) */
# define M_SQRT2l	1.4142135623730950488016887242096981L  /* sqrt(2) */
# define M_SQRT1_2l	0.7071067811865475244008443621048490L  /* 1/sqrt(2) */
#endif

#endif
