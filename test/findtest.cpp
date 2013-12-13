/*!
 *  @file findtest.cpp
 *  macstl-106
 *
 *  Created by René J.V. Bertin on 20111105.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdarg.h>
#include <math.h>

#include <iostream>
#include <valarray>
#ifdef __APPLE__
#include <macstl/mach.h>
#endif
#include <macstl/valarray.h>
#include <boost/circular_buffer.hpp>
#define USE_SSE_AUTO
#include "sse_mathfun.h"

#include "timing.h"
#include "timing.c"
#include "StreamEx.h"

#ifdef SAMPLELENGTH
#	define N	SAMPLELENGTH
#else
#	define N	50000000
#endif
#define SHIFTN	5

#define BSCACHES

int bisect_find_nop( double *xa, int n, double x, int &idxLo, int &idxHi )
{ int klo, khi, k;
#ifdef BSCACHES
  static int pklo = 1, pklh = 1, delta = 1;
#endif
	return 1;
}

int bisect_find( double *xa, int n, double x, int &idxLo, int &idxHi )
{ int klo, khi, k;
#ifdef BSCACHES
  static int pklo = 1, pklh = 1, delta = 1;
	if( xa[pklo] <= x && xa[pklh] > x ){
		klo = pklo, khi = pklh;
	}
	else if( pklo+delta < n && xa[pklo+delta] <= x && pklh+delta < n && xa[pklh+delta] > x ){
		klo = pklo+delta, khi = pklh+delta;
		pklo = klo, pklh = khi;
	}
	else if( pklo-delta > -1 && xa[pklo-delta] <= x && pklh-delta > -1 && xa[pklh-delta] > x ){
		klo = pklo-delta, khi = pklh-delta;
		pklo = klo, pklh = khi;
	}
	else
#endif
	{
		klo= 0, khi= n-1;
		while( khi-klo > 1 ){
			k= (khi+klo) >> 1;
			if( xa[k] > x ){
				khi= k;
			}
			else{
				klo= k;
			}
		}
		idxLo = klo, idxHi = khi;
#ifdef BSCACHES
		{ int d = abs(klo-pklo);
			if( d && d != delta ){
				if( d < (n >>1) ){
					delta = d;
				}
			}
		}
		pklo = klo, pklh = khi;
#endif
	}
	return xa[klo] <= x;
}

int va_find( double *xa, int n, double x, int &idx )
{ stdext::refarray<double> vxa(xa,n);
#if 1
  double *val = std::find(vxa.begin(), vxa.end(), x);
	if( val ){
		idx = (int) (val - xa);
		return *val == x;
	}
	else{
		return 0;
	}
#else
  stdext::valarray<double> veq = vxa[vxa==x];
	if( veq.size() && veq[0] == x ){
		idx = 0;
		return 1;
	}
	else{
		return 0;
	}
#endif
}

double ssum( double *xa, int n )
{ register int i;
  register double sum = 0.0;
	for( i = 0 ; i < n ; i++ ){
		sum += *xa++;
	}
	return sum;
}

double ssum2( double *xa, size_t n, double *xb, size_t n2 )
{ register size_t i;
  register double sum = 0.0;
	do{
		for( i = 0 ; i < n ; i++ ){
			sum += *xa++;
		}
		xa = xb, n = n2;
		xb = NULL;
	} while(xa);
	return sum;
}

double sse3_sum( double *xa, int n )
{ __m128d vsum;
  register int i, N_8 = n-8+1;
  register double sum = 0;
	for( i = 0 ; i < N_8 ; i+=8, xa+=8 ){
//		vsum = _mm_add_pd( vsum, _mm_hadd_pd( _mm_hadd_pd( _mm_set_pd(xa[3],xa[2]), _mm_set_pd(xa[1], xa[0]) ), z0 ) );
//		vsum = _mm_add_pd( vsum, _mm_hadd_pd( _mm_hadd_pd( *((__m128d*)&xa[2]), *((__m128d*)xa) ), z0 ) );
		vsum = _mm_hadd_pd( _mm_hadd_pd( *((__m128d*)&xa[2]), *((__m128d*)xa) ),
					    _mm_hadd_pd( *((__m128d*)&xa[6]), *((__m128d*)&xa[4]) ) );
		sum += *((double*)&vsum) + ((double*)&vsum)[1];
	}
	if( n-i > 4 ){
	  __m128d z0 = _mm_set1_pd(0);
		vsum = _mm_hadd_pd( _mm_hadd_pd( *((__m128d*)&xa[2]), *((__m128d*)xa) ), z0 );
		sum += *((double*)&vsum);
		xa += 4, i += 4;
  	}
	for( ; i < n ; i++ ){
		sum += *xa++;
	}
	return sum;
}

#ifdef __GNUC__
// #	ifdef __AVX__
// 	double avx_sumb( double *xa, int n )
// 	{ __m256d vsum;
// 	  register int i, N_8 = n-8+1;
// 	  register double sum = 0;
// 		for( i = 0 ; i < N_8 ; i+=8, xa+=8 ){
// 			vsum = *((__m256d*)&xa[4]) + *((__m256d*)xa);
// 			sum += *((double*)&vsum) + ((double*)&vsum)[1] + ((double*)&vsum)[2] + ((double*)&vsum)[3];
// 		}
// 		for( ; i < n ; i++ ){
// 			sum += *xa++;
// 		}
// 		return sum;
// 	}
// #	endif
	double sse3_sumb( double *xa, int n )
	{ __m128d vsum;
	  register int i, N_4 = n-4+1;
	  register double sum = 0;
		for( i = 0 ; i < N_4 ; i+=4, xa+=4 ){
			vsum = *((__m128d*)&xa[2]) + *((__m128d*)xa);
			sum += *((double*)&vsum) + ((double*)&vsum)[1];
		}
		for( ; i < n ; i++ ){
			sum += *xa++;
		}
		return sum;
	}
#else
// #	ifdef __AVX__
// 	double avx_sumb( double *xa, int n )
// 	{ __m256d vsum;
// 	  register int i, N_8 = n-8+1;
// 	  register double sum = 0;
// 		for( i = 0 ; i < N_8 ; i+=8, xa+=8 ){
// 			vsum = _mm256_add_pd( *((__m256d*)&xa[4]), *((__m256d*)xa) );
// 			sum += *((double*)&vsum) + ((double*)&vsum)[1] + ((double*)&vsum)[2] + ((double*)&vsum)[3];
// 		}
// 		for( ; i < n ; i++ ){
// 			sum += *xa++;
// 		}
// 		return sum;
// 	}
// #	endif
	double sse3_sumb( double *xa, int n )
	{ __m128d vsum;
	  register int i, N_4 = n-4+1;
	  register double sum = 0;
		for( i = 0 ; i < N_4 ; i+=4, xa+=4 ){
			vsum = _mm_add_pd( *((__m128d*)&xa[2]), *((__m128d*)xa) );
			sum += *((double*)&vsum) + ((double*)&vsum)[1];
		}
		for( ; i < n ; i++ ){
			sum += *xa++;
		}
		return sum;
	}
#endif
#	ifdef __AVX__
	// sum all elements using a single AVX vector operation (add_pd) followed by a compiler-optimised
	// solution for 3 scalar sums
	double avx_sumb( double *xa, int n )
	{ register int i, N_8 = n-8+1;
	  register double sum = 0;
		for( i = 0 ; i < N_8 ; i+=8, xa+=8 ){
			__m256d vsum = _mm256_add_pd( *((__m256d*)&xa[4]), *((__m256d*)xa) );
			sum += *((double*)&vsum) + ((double*)&vsum)[1] + ((double*)&vsum)[2] + ((double*)&vsum)[3];
		}
		for( ; i < n ; i++ ){
			sum += *xa++;
		}
		return sum;
	}

	// sum all elements using two horizontal AVX vector operations (hadd_pd) followed by a compiler-optimised
	// solution for 1 scalar sum. Contrary to what might be expected, this is slightly but consistently slower
	// (about 3% on my 2.7Ghz Core i7).
	double avx_sumc( double *xa, int n )
	{ register int i, N_8 = n-8+1;
	  register double sum = 0;
		for( i = 0 ; i < N_8 ; i+=8, xa+=8 ){
			__m256d vsum1 = _mm256_hadd_pd( *((__m256d*)xa), *((__m256d*)&xa[4]) );
			__m256d vsum = _mm256_hadd_pd( vsum1, vsum1 );
			sum += *((double*)&vsum) + ((double*)&vsum)[2];
		}
		for( ; i < n ; i++ ){
			sum += *xa++;
		}
		return sum;
	}
#	endif

double sse3_sum2( double *xa, size_t n, double *xb, size_t n2 )
{ __m128d vsum;
  register size_t i;
  register double sum = 0;
	do{
		if( n >= 8 ){
		  register size_t N_8 = n-8+1;
			for( i = 0 ; i < N_8 ; i+=8, xa+=8 ){
		//		vsum = _mm_add_pd( vsum, _mm_hadd_pd( _mm_hadd_pd( _mm_set_pd(xa[3],xa[2]), _mm_set_pd(xa[1], xa[0]) ), z0 ) );
		//		vsum = _mm_add_pd( vsum, _mm_hadd_pd( _mm_hadd_pd( *((__m128d*)&xa[2]), *((__m128d*)xa) ), z0 ) );
				vsum = _mm_hadd_pd( _mm_hadd_pd( *((__m128d*)&xa[2]), *((__m128d*)xa) ),
							    _mm_hadd_pd( *((__m128d*)&xa[6]), *((__m128d*)&xa[4]) ) );
				sum += *((double*)&vsum) + ((double*)&vsum)[1];
			}
		}
		if( n-i > 4 ){
		  __m128d z0 = _mm_set1_pd(0);
			vsum = _mm_hadd_pd( _mm_hadd_pd( *((__m128d*)&xa[2]), *((__m128d*)xa) ), z0 );
			sum += *((double*)&vsum);
			xa += 4, i += 4;
		}
		for( ; i < n ; i++ ){
			sum += *xa++;
		}
		xa = xb, n = n2;
		xb = NULL;
	} while(xa);
	return sum;
}

double va_sum( double *xa, int n )
{
	if( n < 2 ){
		return *xa;
	}
#ifdef __APPLE__
	else{
	  stdext::refarray<double> vxa(xa,n);
		return vxa.sum();
	}
#else
	else{
		if( ((size_t)xa) % 16 == 0 ){
	  stdext::refarray<double> vxa(xa,n);
		return vxa.sum();
	}
		else{
		  stdext::valarray<double> vxa(xa,n);
			return vxa.sum();
		}
	}
#endif
}

double ssumsq( double *xa, int n )
{ register int i;
  register double sumsq = 0.0;
	for( i = 0 ; i < n ; i++, xa++ ){
		sumsq += *xa * *xa;
	}
	return sumsq;
}

#if defined(__SSE4__) || defined(__SSE4_1__) || defined(__SSE4_2__)

#define __SSE4__

double sse4_sumsq( double *xa, int n )
{ __m128d z0 = _mm_set1_pd(0);
  __m128d vsumsq;
  int i, N_4 = n-4;
  double sumsq = 0;
	for( i = 0 ; i < N_4 ; i+=4, xa+=4 ){
			// dpa=_mm_dp_pd(va,va,0x31) calculates va[0]*va[0] + va[1]*va[1] and stores the result in dpa[0]
			// dpb=_mm_dp_pd(vb,vb,0x32) calculates vb[0]*vb[0] + vb[1]*vb[1] and stores the result in dpb[1]
			// _mm_blend_pd(dpa,dpb,0x2) returns dpa[0],dpb[1] = (va[0]*va[0] + va[1]*va[1]),(vb[0]*vb[0] + vb[1]*vb[1])
		vsumsq = _mm_hadd_pd( _mm_blend_pd(
							   _mm_dp_pd( *((__m128d*)xa), *((__m128d*)xa), 0x31 ),
							   _mm_dp_pd( *((__m128d*)&xa[2]), *((__m128d*)&xa[2]), 0x32 ),
							   0x2 ),
						   z0 );
		sumsq += *((double*)&vsumsq);
	}
	for( ; i < n ; i++, xa++ ){
		sumsq += *xa * *xa;
	}
	return sumsq;
}
#endif // SSE4

#ifdef __GNUC__
double sse3_sumsqb( double *xa, int n )
{ __m128d vsumsq;
  register int i, N_4 = n-4+1;
  register double sumsq = 0;
	for( i = 0 ; i < N_4 ; i+=4, xa+=4 ){
		vsumsq = *((__m128d*)&xa[2]) * *((__m128d*)&xa[2]) + *((__m128d*)xa) * *((__m128d*)xa);
		sumsq += *((double*)&vsumsq) + ((double*)&vsumsq)[1];
	}
	for( ; i < n ; i++, xa++ ){
		sumsq += *xa * *xa;
	}
	return sumsq;
}
#else
double sse3_sumsqb( double *xa, int n )
{ __m128d vsumsq;
  register int i, N_4 = n-4+1;
  register double sumsq = 0;
	for( i = 0 ; i < N_4 ; i+=4, xa+=4 ){
		vsumsq = _mm_add_pd( _mm_mul_pd( *((__m128d*)&xa[2]), *((__m128d*)&xa[2]) ),
					   _mm_mul_pd( *((__m128d*)xa), *((__m128d*)xa) ) );
		sumsq += *((double*)&vsumsq) + ((double*)&vsumsq)[1];
	}
	for( ; i < n ; i++, xa++ ){
		sumsq += *xa * *xa;
	}
	return sumsq;
}
#endif

#if defined(__SSE4__) || defined(__SSE4_1__) || defined(__SSE4_2__)
// ever so slightly slower:
double sse4_sumsq_take2( double *xa, int n )
{ __m128d z0 = _mm_set1_pd(0);
  __m128d vsumsq;
  register int i, N_8 = n-8+1;
  register double sumsq = 0;
	for( i = 0 ; i < N_8 ; i+=8, xa+=8 ){
			// dpa=_mm_dp_pd(va,va,0x31) calculates va[0]*va[0] + va[1]*va[1] and stores the result in dpa[0]
			// dpb=_mm_dp_pd(vb,vb,0x32) calculates vb[0]*vb[0] + vb[1]*vb[1] and stores the result in dpb[1]
			// _mm_blend_pd(dpa,dpb,0x2) returns dpa[0],dpb[1] = (va[0]*va[0] + va[1]*va[1]),(vb[0]*vb[0] + vb[1]*vb[1])
		vsumsq = _mm_hadd_pd( _mm_blend_pd(
								_mm_dp_pd( *((__m128d*)xa), *((__m128d*)xa), 0x31 ),
								_mm_dp_pd( *((__m128d*)&xa[2]), *((__m128d*)&xa[2]),
								0x32 ),
							0x2 ),
						 _mm_blend_pd(
							    _mm_dp_pd( *((__m128d*)&xa[4]), *((__m128d*)&xa[4]), 0x31 ),
							    _mm_dp_pd( *((__m128d*)&xa[6]), *((__m128d*)&xa[6]), 0x32 ),
						    0x2 ) );
		sumsq += *((double*)&vsumsq) + ((double*)&vsumsq)[1];
	}
	if( n-i > 4 ){
	  __m128d z0 = _mm_set1_pd(0);
		vsumsq = _mm_hadd_pd( _mm_blend_pd(
								_mm_dp_pd( *((__m128d*)xa), *((__m128d*)xa), 0x31 ),
								_mm_dp_pd( *((__m128d*)&xa[2]), *((__m128d*)&xa[2]), 0x32 ),
								0x2 ),
							z0 );
		sumsq += *((double*)&vsumsq);
		xa += 4, i += 4;
  	}
	for( ; i < n ; i++, xa++ ){
		sumsq += *xa + *xa;
	}
	return sumsq;
}
#endif //SSE4


double va_sumsq( double *xa, int n )
{ stdext::refarray<double> vxa(xa,n);
	return (vxa * vxa).sum();
}

double ssumsq( double *xa, int n, double &sumSQ )
{ register int i;
  register double sum = 0.0, sumsq = 0.0;
	for( i = 0 ; i < n ; i++, xa++ ){
		sum += *xa;
		sumsq += *xa * *xa;
	}
	sumSQ = sumsq;
	return sum;
}

#if defined(__SSE4__) || defined(__SSE4_1__) || defined(__SSE4_2__)
// calculation of sum AND sumsq is faster using stride 8
double sse4_sumsq( double *xa, int n, double &sumSQ )
{ __m128d vsum;
  int i, N_8 = n-8+1;
  double sum = 0, sumsq = 0;
	for( i = 0 ; i < N_8 ; i+=8, xa+=8 ){
		vsum = _mm_hadd_pd( _mm_hadd_pd( *((__m128d*)&xa[2]), *((__m128d*)xa) ),
					    _mm_hadd_pd( *((__m128d*)&xa[6]), *((__m128d*)&xa[4]) ) );
		sum += *((double*)&vsum) + ((double*)&vsum)[1];
			// dpa=_mm_dp_pd(va,va,0x31) calculates va[0]*va[0] + va[1]*va[1] and stores the result in dpa[0]
			// dpb=_mm_dp_pd(vb,vb,0x32) calculates vb[0]*vb[0] + vb[1]*vb[1] and stores the result in dpb[1]
			// _mm_blend_pd(dpa,dpb,0x2) returns dpa[0],dpb[1] = (va[0]*va[0] + va[1]*va[1]),(vb[0]*vb[0] + vb[1]*vb[1])
		vsum = _mm_hadd_pd( _mm_blend_pd(
								_mm_dp_pd( *((__m128d*)xa), *((__m128d*)xa), 0x31 ),
								_mm_dp_pd( *((__m128d*)&xa[2]), *((__m128d*)&xa[2]),
								0x32 ),
							0x2 ),
						 _mm_blend_pd(
							    _mm_dp_pd( *((__m128d*)&xa[4]), *((__m128d*)&xa[4]), 0x31 ),
							    _mm_dp_pd( *((__m128d*)&xa[6]), *((__m128d*)&xa[6]), 0x32 ),
						    0x2 ) );
		sumsq += *((double*)&vsum) + ((double*)&vsum)[1];
	}
	if( n-i > 4 ){
	  __m128d z0 = _mm_set1_pd(0);
		vsum = _mm_hadd_pd( _mm_hadd_pd( *((__m128d*)&xa[2]), *((__m128d*)xa) ), z0 );
		sum += *((double*)&vsum);
		vsum = _mm_hadd_pd( _mm_blend_pd(
								_mm_dp_pd( *((__m128d*)xa), *((__m128d*)xa), 0x31 ),
								_mm_dp_pd( *((__m128d*)&xa[2]), *((__m128d*)&xa[2]), 0x32 ),
								0x2 ),
							z0 );
		sumsq += *((double*)&vsum);
		xa += 4, i += 4;
  	}
	for( ; i < n ; i++, xa++ ){
		sum += *xa;
		sumsq += *xa * *xa;
	}
	sumSQ = sumsq;
	return sum;
}
#endif //SSE4

#ifdef __GNUC__
double sse3_sumsqb( double *xa, int n, double &sumSQ )
{ __m128d vsum, vsumsq;
  register int i, N_4 = n-4+1;
  register double sum = 0.0, sumsq = 0;
	for( i = 0 ; i < N_4 ; i+=4, xa+=4 ){
		vsum = *((__m128d*)&xa[2]) + *((__m128d*)xa);
		vsumsq = *((__m128d*)&xa[2]) * *((__m128d*)&xa[2]) + *((__m128d*)xa) * *((__m128d*)xa);
		sum += *((double*)&vsum) + ((double*)&vsum)[1];
		sumsq += *((double*)&vsumsq) + ((double*)&vsumsq)[1];
	}
	for( ; i < n ; i++, xa++ ){
		sum += *xa;
		sumsq += *xa * *xa;
	}
	sumSQ = sumsq;
	return sum;
}
#else
double sse3_sumsqb( double *xa, int n, double &sumSQ )
{ __m128d vsum, vsumsq;
  register int i, N_4 = n-4+1;
  register double sum = 0.0, sumsq = 0;
	for( i = 0 ; i < N_4 ; i+=4, xa+=4 ){
		vsum = _mm_add_pd( *((__m128d*)&xa[2]), *((__m128d*)xa) );
		vsumsq = _mm_add_pd( _mm_mul_pd( *((__m128d*)&xa[2]), *((__m128d*)&xa[2]) ),
					   _mm_mul_pd( *((__m128d*)xa), *((__m128d*)xa) ) );
		sum += *((double*)&vsum) + ((double*)&vsum)[1];
		sumsq += *((double*)&vsumsq) + ((double*)&vsumsq)[1];
	}
	for( ; i < n ; i++, xa++ ){
		sum += *xa;
		sumsq += *xa * *xa;
	}
	return sumsq;
}
#endif

double va_sumsq( double *xa, int n, double &sumSQ )
{ stdext::refarray<double> vxa(xa,n);
	sumSQ = (vxa * vxa).sum();
	return vxa.sum();
}

double saddarrayscalar( double *xa, double b, double *sums, int n )
{ register int i;
  double sum = 0;
	for( i = 0 ; i < n ; i++ ){
		sum += (*sums++ = *xa++ + b);
	}
	return sum;
}

double va_addarrayscalar( double *xa, double b, double *sums, int n )
{ stdext::refarray<double> vxa(xa,n), vsums(sums,n);
	return (vsums = vxa + b).sum();
}

double saddarrays( double *xa, double *xb, double *sums, int n )
{ register int i;
  double sum = 0;
	for( i = 0 ; i < n ; i++ ){
		sum += (*sums++ = *xa++ + *xb++);
	}
	return sum;
}

double va_addarrays( double *xa, double *xb, double *sums, int n )
{ stdext::refarray<double> vxa(xa,n), vxb(xb,n), vsums(sums,n);
	return (vsums = vxa + vxb).sum();
}

double smularrays( double *xa, double *xb, double *prods, int n )
{ register int i;
  double sum = 0;
	for( i = 0 ; i < n ; i++ ){
		sum += (*prods++ = *xa++ * *xb++);
	}
	return sum;
}

double va_mularrays( double *xa, double *xb, double *prods, int n )
{ stdext::refarray<double> vxa(xa,n), vxb(xb,n), vprods(prods,n);
	return (vprods = vxa * vxb).sum();
}

// macstl only does left shifts, but is about 4x faster than valarray on my system.
double stdext_shiftav( stdext::refarray<double> &vbuf, double curVal )
{
	vbuf = vbuf.shift(1);
	size_t n = vbuf.size();
	vbuf[n-1] = curVal;
	return vbuf.sum()/n;
}

double std_shiftav( std::valarray<double> &vbuf, double curVal )
{
	vbuf = vbuf.shift(-1);
	vbuf[0] = curVal;
	return vbuf.sum()/vbuf.size();
}

//typedef boost::circular_buffer<double, macstl::mach_allocator<double> > ShiftAvCBuf;
typedef boost::circular_buffer<double> ShiftAvCBuf;

double boost_shiftav( ShiftAvCBuf *cbuf, double curVal )
{
	cbuf->push_front(curVal);
	boost::circular_buffer<double>::array_range a1 = cbuf->array_one(), a2 = cbuf->array_two();
	if( cbuf->size() > 3 && !(((size_t)a1.first) % 16) && !(((size_t)a2.first) % 16) ){
		return ( sse3_sumb( a1.first, a1.second ) + sse3_sumb( a2.first, a2.second ) ) / (a1.second + a2.second);
//		return sse3_sum2( a1.first, a1.second, a2.first, a2.second ) / (a1.second + a2.second);
	}
	else{
//		return std::accumulate(cbuf->begin(), cbuf->end(), 0);
		return ( ssum( a1.first, a1.second ) + ssum( a2.first, a2.second ) ) / (a1.second + a2.second);
//		return ssum2( a1.first, a1.second, a2.first, a2.second ) / (a1.second + a2.second);
	}
}

double rateConvertedByWeightedAverage( double prevRateConvertedValue, double currentValue, double rateFraction )
{ double weightPrev = rateFraction - 1 - sqrt(rateFraction);
  double weightCur  = rateFraction - weightPrev;
	return (prevRateConvertedValue * weightPrev + currentValue * weightCur) / rateFraction;

}

static __m128d mmOne = {1,1};

#ifdef __GNUC__
__m128d rateConvertedByWeightedAverage( __m128d prevRateConvertedValue, __m128d currentValue, __m128d rateFraction )
{ __m128d weightPrev = rateFraction - mmOne - _mm_sqrt_pd(rateFraction);
	return (prevRateConvertedValue * weightPrev + currentValue * (rateFraction - weightPrev)) / rateFraction;

}
#else
__m128d rateConvertedByWeightedAverage( __m128d prevRateConvertedValue, __m128d currentValue, __m128d rateFraction )
{ __m128d weightPrev = _mm_sub_pd( _mm_sub_pd( rateFraction, mmOne ), _mm_sqrt_pd(rateFraction) );
  __m128d weightCur  = _mm_sub_pd( rateFraction, weightPrev );
	return _mm_div_pd( _mm_add_pd (_mm_mul_pd( prevRateConvertedValue, weightPrev ), _mm_mul_pd( currentValue, weightCur ) ),
				   rateFraction );

}
#endif

#ifndef _SSE_MATHFUN_H
	static inline double ssceil(double a)
	{ v2df va = _mm_ceil_pd( _MM_SETR_PD(a,0) );
		return *((double*)&va);
	}

	static inline double ssfloor(double a)
	{ v2df va = _mm_floor_pd( _MM_SETR_PD(a,0) );
		return *((double*)&va);
	}
#endif

static inline v2df *mm_round_pd( v2df *val, v2df a )
{
	// using ssceil/ssfloor (above) instead of the standard functions makes mm_round_pd ROUGHLY twice as slow
	// as _mm_round_pd ... instead of the ROUGHLY 4 times it is slower otherwise. In other words, even for
	// single scalar operations, it pays to use the SSE4 intrinsics!
	((double*)val)[0] = (((double*)&a)[0] >= 0)? floor( ((double*)&a)[0] + 0.5 ) : ceil( ((double*)&a)[0] - 0.5 );
	((double*)val)[1] = (((double*)&a)[1] >= 0)? floor( ((double*)&a)[1] + 0.5 ) : ceil( ((double*)&a)[1] - 0.5 );
// not faster, and round() doesn't seem to exist on MSWin
//	((double*)val)[0] = round(((double*)&a)[0]);
//	((double*)val)[1] = round(((double*)&a)[1]);
	return val;
}

//static inline v2df _mm_abs_pd2( v2df a )
//{ _PD_CONST_TYPE(abs_mask, long long, ~0x8000000000000000LL);
//	return _mm_and_pd(a, *(v2df*)_pd_abs_mask);
//}
//
static inline v2df _mm_abs_pd2( v2df a )
{
 	return _mm_max_pd( a, _mm_mul_pd(a, _MM_SET1_PD(-1.0)) );
}

int main(int argc, char *argv[] )
{ ALIGN16_BEG double *data, *data2, *results, tdata[] ALIGN16_END = {1,2,3,4,5,6,7,8,9,10,11,12}, toc, sum, sumsq;
  int i, Nt, klo, khi, j, stride, k;
  size_t r;
  typedef StreamEx<std::ostream> OStreamEx;
  OStreamEx CErr(std::cerr);

	init_HRTime();

	{ using namespace macstl;
	  vec<double,2> v = vec<double,2>::set(1.0, 2.5);
		fprintf( stderr, "std::cerr=%p, CErr=%p\n", &(std::cerr), &(CErr) );
		CErr << "<double,2> : shuffled<0,1>(" << v << ") == " << mmx::shuffled<0,1>( v, v ) << CErr.asprintf( " bla%s", "\n");
		std::cerr << "add( v, shuffled<0,1>(v,v) ) == " << mmx::add( v, mmx::shuffled<0,1>( v, v ) ) << "\n";
		std::cerr << "v.sum() == " << v.sum() << "\n";
		vec<float,4> ff = vec<float,4>::set(1.0, 2.5, 3.5, -2.0);
		{ const vec <float, 4> fresult = mmx::add (ff, mmx::shuffles <0, 3, 2, 1> (ff, ff));
		  vec<float, 4> vv;
			std::cerr << "<float,4> : shuffles<0,3,2,1>(1,2.5,3.5,-2) == " << mmx::shuffles<0, 3, 2, 1>(ff, ff) << "\n";
			std::cerr << "add((1,2.5,3.5,-2), shuffles<0,3,2,1>(1,2.5,3.5,-2)) == " << fresult << "\n";
			std::cerr << "hadd((" << fresult << "),(" << fresult << ")) == " << mmx::hadd(fresult,fresult) << "\n";
			vv = mmx::add(fresult, mmx::shuffles <1, 0, 3, 2> (fresult, fresult));
			std::cerr << "add(" << fresult << ", shuffles<1,0,3,2>(1,2.5,3.5,-2)) == "
				<< vv << "\n";
			CErr << "(" << vv << ").sum() == " << vv.sum(); CErr.flush();
			CErr.asprintf( " (==%g", (double) vv.sum() ) << ") formatted length==";
			CErr << CErr.lastFormattedLength() << std::endl;
		}
#ifdef __AVX__
		{	vec<double,4> vv = vec<double,4>::set(1.0, 2.5, 3.5, -2.0);
			const vec <double, 4> result = mmx::add (vv, mmx::shuffledd <0, 3, 2, 1> (vv, vv));
			std::cerr << "<double,4> : shuffledd<0,3,2,1>(1,2.5,3.5,-2) == " << mmx::shuffledd<0, 3, 2, 1>(vv, vv) << "\n";
			std::cerr << "add((1,2.5,3.5,-2), shuffledd<0,3,2,1>(1,2.5,3.5,-2)) == " << result << "\n";
			std::cerr << "add(" << result << ", shuffledd<1,0,3,2>(1,2.5,3.5,-2)) == "
				<< mmx::add(result, mmx::shuffledd <1, 0, 3, 2> (result, result)) << "\n";
			std::cerr << "hadd((1,2.5,3.5,-2),(1,2.5,3.5,-2)) == " << mmx::hadd(vv,vv) << "\n";
			std::cerr << "(1,2.5,3.5,-2).sum() == " << vv.sum() << "\n";
		}
		{	vec<float,8> vv = vec<float,8>::set(1.0, 2.5, 3.5, -2.0, 4.0, -5.5, 0.0, 100.2);
			std::cerr << "hadd((1,2.5,3.5,-2,4,-5.5,0,100.2),(1,2.5,3.5,-2,4,-5.5,0,100.2)) == " << mmx::hadd(vv,vv) << "\n";
			CErr << "(1,2.5,3.5,-2,4,-5.5,0,100.2).sum() == " << vv.sum(); CErr.flush();
			CErr.asprintf( " (==%g", vv.sum() ) << ") formatted length==" << CErr.lastFormattedLength() << std::endl;
			vv = vec<float,8>::set(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8);
			__m128 *vec4 = vv.half_data();
			__m128 result0 = _mm_max_ps( vec4[0], _mm_shuffle_ps(vec4[0], vec4[0], SHUFFLE4MASK(0,3,2,1)) );
			result0 = _mm_max_ps( result0, _mm_shuffle_ps(result0, result0, SHUFFLE4MASK(1, 0, 3, 2)) );
			__m128 result1 = _mm_max_ps( vec4[1], _mm_shuffle_ps(vec4[1], vec4[1], SHUFFLE4MASK(0,3,2,1)) );
			result1 = _mm_max_ps( result1, _mm_shuffle_ps(result1, result1, SHUFFLE4MASK(1, 0, 3, 2)) );
			vec<float,4> r0 = result0, r1 = result1;
			CErr << "max(1.1,2.2,3.3,4.4) == " << r0 << " max(5.5,6.6,7.7,8.8) == " << r1 << " max == " <<
				stdext::__mvectorelem<float>( _mm_max_ps( result0, result1 ), 0 ) << "\n";
		}
		{ vec<float,8> xx = vec<float,8>::set( 0, 0.8976, 1.0472, 1.2566, 1.5708, 2.0944, 3.1415, 6.28319 );
			CErr << "Checking sin & cos on vec<float,4>(" << ((vec<float,4>*)&xx)[0] << "),("  << ((vec<float,4>*)&xx)[1] << ") :\n";
			CErr << "\ts=(" << sin(((vec<float,4>*)&xx)[0]) << "),("  << sin(((vec<float,4>*)&xx)[1]) << "); c=";
			CErr << "(" << cos(((vec<float,4>*)&xx)[0]) << "),("  << cos(((vec<float,4>*)&xx)[1]) << ")\n";
			CErr << "Checking sin & cos on vec<float,8>(" << xx << ") :\n";
			CErr << "\ts=(" << sin(xx) << "); c=";
			CErr << "(" << cos(xx) << ")\n";
		}
		{ vec<double,4> xx[2] = { vec<double, 4>::set( 0, 0.8976, 1.0472, 1.2566 ), vec<double,4>::set( 1.5708, 2.0944, 3.1415, 6.28319 ) };
			CErr << "Checking sin & cos on vec<double,2>(" << ((vec<double,2>*)&xx)[0] << "),("  << ((vec<double,2>*)&xx)[1] << "),(";
			CErr << ((vec<double,2>*)&xx)[2] << "),("  << ((vec<double,2>*)&xx)[3] << ") :\n";
			CErr << "\ts=(" << sin(((vec<double,2>*)&xx)[0]) << "),("  << sin(((vec<double,2>*)&xx)[1]) << "),(";
			CErr << sin(((vec<double,2>*)&xx)[2]) << "),("  << sin(((vec<double,2>*)&xx)[3]) << ")";
			CErr << " c=(" << cos(((vec<double,2>*)&xx)[0]) << "),("  << cos(((vec<double,2>*)&xx)[1]) << "),(";
			CErr << cos(((vec<double,2>*)&xx)[2]) << "),("  << cos(((vec<double,2>*)&xx)[3]) << ") :\n";
			CErr << "Checking sin & cos on vec<double,4>(" << xx[0] << "),("  << xx[1] << ") :\n";
			CErr << "\ts=(" << sin(xx[0]) << "),(" << sin(xx[1]) << "); c=";
			CErr << "(" << cos(xx[0]) << "),(" << cos(xx[1]) << ")\n";
		}

		exit(-1);
#endif
	}
	fprintf( stderr, "va_sum({1,2,3,4,5,6,7,8,9,10}) = %g\n", va_sum(tdata, 10) );
	if( (data = (double*) _mm_malloc(N*sizeof(double), 16))
	   &&  (data2 = (double*) _mm_malloc(N*sizeof(double), 16))
	   &&  (results = (double*) _mm_malloc(N*sizeof(double), 16))
	){
		for( i = 0 ; i < N ; i++ ){
			data2[i] = data[i] = i+1;
			if( i % 2 ){
				data[i] *= -1;
				data2[i] *= -1;
			}
		}
		static stdext::valarray<double> vxa(tdata,sizeof(tdata)/sizeof(tdata[0]));
		static stdext::refarray<double> rxa = vxa;
		std::cerr << "vxa=" << vxa <<" ; rxa=" << rxa << "\n";

		{ v2df a = _mm_abs_pd( *((v2df*)&data[2]) ), b;
			mm_abs_pd( &b, ((v2df*)&data2[2]) );
			fprintf( stderr, "_mm_abs_pd({%g,%g}) -> {%g,%g}\n", data[2], data[3], ((double*)&a)[0], ((double*)&a)[1] );
			fprintf( stderr, "mm_abs_pd(&b,&{%g,%g}) -> {%g,%g}\n", data2[2], data2[3], ((double*)&b)[0], ((double*)&b)[1] );
			b = _mm_abs_pd2( *((v2df*)&data2[2]) );
			fprintf( stderr, "_mm_abs_pd2({%g,%g}) -> {%g,%g}\n", data2[2], data2[3], ((double*)&b)[0], ((double*)&b)[1] );
			Nt = 50 + 1;
			HRTime_tic();
			for( i = 1, r = 0 ; i < Nt ; i++ ){
				for( j = 0 ; j < N && *((double*)&b) ; j += 2 ){
//					mm_abs_pd(&b, ((v2df*)&data[j]));
//					b = _mm_load_pd(&data[j]);
					((double*)&b)[0] = data[j], ((double*)&b)[1] = data[j+1];
					r += 1;
				}
			}
			toc = HRTime_toc(); fprintf( stderr, "%lux mm_abs_pd(&data) in %gs -> %gHz\n", r, toc, r/(toc) );
			HRTime_tic();
			for( i = 1, r = 0 ; i < Nt ; i++ ){
				for( j = 0 ; j < N && *((double*)&a); j += 2 ){
					a = _mm_abs_pd(*((v2df*)&data[j]));
					r += 1;
				}
			}
			toc = HRTime_toc(); fprintf( stderr, "%lux _mm_abs_pd(data) in %gs -> %gHz\n", r, toc, r/(toc) );
			HRTime_tic();
			for( i = 1, r = 0 ; i < Nt ; i++ ){
				for( j = 0 ; j < N && *((double*)&a); j += 2 ){
					a = _mm_abs_pd2(*((v2df*)&data[j]));
					r += 1;
				}
			}
			toc = HRTime_toc(); fprintf( stderr, "%lux _mm_abs_pd2(data) in %gs -> %gHz\n", r, toc, r/(toc) );

#if defined(_MM_FROUND_TO_NEAREST_INT) && defined(__SSE4__)
			a = _mm_round_pd( _MM_SETR_PD(127.5, -315.125), _MM_FROUND_TO_NEAREST_INT|_MM_FROUND_NO_EXC );
			fprintf( stderr, "_mm_round_pd({127.5,-315.125}) -> {%g,%g}\n", ((double*)&a)[0], ((double*)&a)[1] );
			mm_round_pd( &b, _MM_SETR_PD(127.5, -315.125) );
			fprintf( stderr, "mm_round_pd(&b,{127.5,-315.125}) -> {%g,%g}\n", ((double*)&b)[0], ((double*)&b)[1] );
#endif
			HRTime_tic();
			for( i = 1, r = 0 ; i < Nt ; i++ ){
				for( j = 2 ; j < N && *((double*)&a); j += 2 ){
					a = _mm_div_pd( *((v2df*)&data[j]), _MM_SET1_PD(2.0) );
					r += 1;
				}
			}
			double bias = HRTime_toc();
#if defined(_MM_FROUND_TO_NEAREST_INT) && defined(__SSE4__)
			HRTime_tic();
			for( i = 1, r = 0 ; i < Nt ; i++ ){
				for( j = 2 ; j < N && *((double*)&a); j += 2 ){
					a = _mm_round_pd( _mm_div_pd( *((v2df*)&data[j]), _MM_SET1_PD(2.0) ), _MM_FROUND_TO_NEAREST_INT|_MM_FROUND_NO_EXC );
					r += 1;
				}
			}
			toc = HRTime_toc() - bias;
			fprintf( stderr, "%lux pure _mm_round_pd(data/2) in %gs -> %gHz\n", r, toc, r/(toc) );
#endif
			HRTime_tic();
			for( i = 1, r = 0 ; i < Nt ; i++ ){
				for( j = 2 ; j < N && *((double*)&b) ; j += 2 ){
					mm_round_pd( &b, _mm_div_pd( *((v2df*)&data2[j]), _MM_SET1_PD(2.0) ) );
					r += 1;
				}
			}
			toc = HRTime_toc() - bias;
			fprintf( stderr, "%lux pure mm_round_pd(&data/2) in %gs -> %gHz\n", r, toc, r/(toc) );
		}

		if( SHIFTN == 5 ){
		  double convVal = 10, *cV2;
		  __m128d convVal2 = {10,10}, mmZero = {0,0}, mmRateFraction = {SHIFTN,SHIFTN};
			convVal = rateConvertedByWeightedAverage( convVal, 10, SHIFTN );
			fprintf( stderr, " runAv = %g\n", convVal );
			convVal = rateConvertedByWeightedAverage( convVal, 20, SHIFTN );
			fprintf( stderr, " runAv = %g\n", convVal );
			Nt = 50 * (N/SHIFTN) + 1;
			HRTime_tic();
			for( i = 1, r = 0 ; i < Nt && convVal ; i++ ){
				convVal = rateConvertedByWeightedAverage( convVal, i, SHIFTN );
				r += 1;
			}
			toc = HRTime_toc();
			fprintf( stderr, "%lux rateConvertedByWeightedAverage( convVal, i, SHIFTN )) in %gs -> %gHz ; av=%le\n",
				   r, toc, r/toc,
				   convVal );
			cV2 = (double*) &convVal2;
			convVal2 = rateConvertedByWeightedAverage( convVal2, _MM_SET1_PD(10), mmRateFraction );
			fprintf( stderr, " runAv = %g,%g\n", cV2[0], cV2[1] );
			convVal2 = rateConvertedByWeightedAverage( convVal2, _MM_SET1_PD(20), mmRateFraction );
			fprintf( stderr, " runAv = %g,%g\n", cV2[0], cV2[1] );
			Nt = 50 * (N/SHIFTN) + 1;
			HRTime_tic();
			for( i = 1, r = 0 ; i < Nt && *cV2 ; i++ ){
				convVal2 = rateConvertedByWeightedAverage( convVal2, _MM_SET1_PD(i), mmRateFraction );
				r += 1;
			}
			toc = HRTime_toc();
			fprintf( stderr, "%lux rateConvertedByWeightedAverage( convVal, _mm_set1_pd(i), {SHIFTN,SHIFTN} )) in %gs -> %gHz ; av=%le,%le\n",
				   r, toc, r/toc,
				   cV2[0], cV2[1] );
		}
#ifndef __AVX__
		{ ShiftAvCBuf *cbuf = new ShiftAvCBuf(SHIFTN, 0.0);
		  double v;
			fprintf( stderr, "boost_shiftav(cbuf{%d},10) = %g", SHIFTN, boost_shiftav( cbuf, 10 ) );
			if( cbuf->linearize() ){
				fprintf( stderr, " cbuf[0] = %g, cbuf->sum=%g\n", (*cbuf)[0], va_sum( cbuf->linearize(), cbuf->size()) );
			}
			else{
				fprintf( stderr, " cbuf->linearize()==NULL !\n" );
			}
			fprintf( stderr, "boost_shiftav(cbuf{%d},20) = %g", SHIFTN, boost_shiftav( cbuf, 20 ) );
			if( cbuf->linearize() ){
				fprintf( stderr, " cbuf[0,1] = %g,%g, cbuf->sum=%g\n", (*cbuf)[0], (*cbuf)[1], va_sum( cbuf->linearize(), cbuf->size()) );
			}
			else{
				fprintf( stderr, " cbuf->linearize()==NULL !\n" );
			}
			Nt = 50 * (N/SHIFTN) + 1;
			HRTime_tic();
			for( i = 1, r = 0 ; i < Nt && (v = boost_shiftav( cbuf, i )) ; i++ ){
				r += 1;
			}
			toc = HRTime_toc();
			fprintf( stderr, "%lux boost_shiftav(cbuf,i) in %gs -> %gHz ; [%ld,%ld] S=%le av=%le\n",
				   r, toc, r/toc,
				   (long) (*cbuf)[0], (long) (*cbuf)[1], va_sum( cbuf->linearize(), cbuf->size()), v );
			delete cbuf;
		}
#endif
		{ stdext::refarray<double> vbuf(data,SHIFTN);
		  double v;
			fprintf( stderr, "stdext_shiftav(data,%d,10) = %g", SHIFTN, stdext_shiftav( vbuf, 10 ) );
			fprintf( stderr, " vbuf[SHIFTN-1] = %g, vbuf.sum=%g\n", vbuf[N-1], vbuf.sum() );
			fprintf( stderr, "stdext_shiftav(data,%d,20) = %g", SHIFTN, stdext_shiftav( vbuf, 20 ) );
			fprintf( stderr, " vbuf[SHIFTN-1,SHIFTN-2] = %g,%g, vbuf.sum=%g\n", vbuf[SHIFTN-1], vbuf[SHIFTN-2], vbuf.sum() );
			fprintf( stderr, " data[SHIFTN-1,SHIFTN-2] = %g,%g, data.sum=%g\n", data[SHIFTN-1], data[SHIFTN-2], va_sum(data,SHIFTN) );
			Nt = 50 * (N/SHIFTN) + 1;
			HRTime_tic();
			for( i = 1, r = 0 ; i < Nt && (v = stdext_shiftav( vbuf, i )) ; i++ ){
				r += 1;
			}
			toc = HRTime_toc();
			fprintf( stderr, "%lux stdext_shiftav(vbuf,i) in %gs -> %gHz ; [%ld,%ld] S=%le av=%le\n",
				   r, toc, r/toc,
				   (long) vbuf[SHIFTN-1], (long) vbuf[SHIFTN-2], vbuf.sum(), v );
			fprintf( stderr, "data[SHIFTN-1,SHIFTN-2] = %ld,%ld, data.sum=%le\n",
				   (long) data[SHIFTN-1], (long) data[SHIFTN-2], va_sum(data,SHIFTN) );
		}
#if 0
		memset( data2, 0, sizeof(double) * N );
		{ std::valarray<double> vbuf(data2,SHIFTN);
		  double v;
			fprintf( stderr, "std_shiftav(data2,%d,10) = %g", SHIFTN, std_shiftav( vbuf, 10 ) );
			fprintf( stderr, " vbuf[0] = %g, vbuf.sum=%g\n", vbuf[0], vbuf.sum() );
			fprintf( stderr, "std_shiftav(data2,%d,20) = %g", SHIFTN, std_shiftav( vbuf, 20 ) );
			fprintf( stderr, " vbuf[0,1] = %g,%g, vbuf.sum=%g\n", vbuf[0], vbuf[1], vbuf.sum() );
			Nt = 50 * (N/SHIFTN) + 1;
			HRTime_tic();
			for( i = 1, r = 0 ; i < Nt && (v = std_shiftav( vbuf, i )) ; i++ ){
				r += 1;
			}
			toc = HRTime_toc();
			fprintf( stderr, "%lux std_shiftav(vbuf,i) in %gs -> %gHz ; [%ld,%ld] S=%le av=%le\n",
				   r, toc, r/toc,
				   (long) vbuf[0], (long) vbuf[1], vbuf.sum(), v );
		}
#endif

		for( i = 0 ; i < N ; i++ ){
			data2[i] = data[i] = i+1;
		}

		fprintf( stderr, "ssum({1,2,3,4,5,6,7,8,9,10,11,12}) = %g\n", ssum(tdata, 12) );
		fprintf( stderr, "va_sum({1,2,3,4,5,6,7,8,9,10,11,12}) = %g\n", va_sum(tdata, 12) );
		fprintf( stderr, "sse3_sum({1,2,3,4,5,6,7,8,9,10,11,12}) = %g\n", sse3_sum(tdata, 12) );
		fprintf( stderr, "sse3_sumb({1,2,3,4,5,6,7,8,9,10,11,12}) = %g\n", sse3_sumb(tdata, 12) );
#ifdef __AVX__
		fprintf( stderr, "avx_sumb({1,2,3,4,5,6,7,8,9,10,11,12}) = %g\n", avx_sumb(tdata, 12) );
		fprintf( stderr, "avx_sumc({1,2,3,4,5,6,7,8,9,10,11,12}) = %g\n", avx_sumc(tdata, 12) );
#endif
		fprintf( stderr, "ssumsq({1,2,3,4,5,6,7,8,9,10,11,12}) = %g\n", ssumsq(tdata, 12) );
		fprintf( stderr, "va_sumsq({1,2,3,4,5,6,7,8,9,10,11,12}) = %g\n", va_sumsq(tdata, 12) );
#if defined(__SSE4__) || defined(__SSE4_1__) || defined(__SSE4_2__)
		fprintf( stderr, "sse4_sumsq({1,2,3,4,5,6,7,8,9,10,11,12}) = %g\n", sse4_sumsq(tdata, 12) );
#endif
		fprintf( stderr, "sse3_sumsqb({1,2,3,4,5,6,7,8,9,10,11,12}) = %g\n", sse3_sumsqb(tdata, 12) );
		sum = ssumsq(tdata, 12, sumsq);
		fprintf( stderr, "ssumsq({1,2,3,4,5,6,7,8,9,10,11,12}, sumsq) = %g,%g\n", sum, sumsq );
		sum = va_sumsq(tdata, 12, sumsq);
		fprintf( stderr, "va_sumsq({1,2,3,4,5,6,7,8,9,10,11,12}, sumsq) = %g,%g\n", sum, sumsq );
#if defined(__SSE4__) || defined(__SSE4_1__) || defined(__SSE4_2__)
		sum = sse4_sumsq(tdata, 12, sumsq);
		fprintf( stderr, "sse4_sumsq({1,2,3,4,5,6,7,8,9,10,11,12}, sumsq) = %g,%g\n", sum, sumsq );
#endif
		sum = sse3_sumsqb(tdata, 12, sumsq);
		fprintf( stderr, "sse3_sumsqb({1,2,3,4,5,6,7,8,9,10,11,12}, sumsq) = %g,%g\n", sum, sumsq );
		memset( results, 0, N*sizeof(double) );
		sum = saddarrays( tdata, data2, results, 12 );
		fprintf( stderr, "saddarrays({1,2,3,4,5,6,7,8,9,10,11,12},data2,results,12) = %g results[11]=%g\n", sum, results[11] );
		memset( results, 0, N*sizeof(double) );
		sum = va_addarrays( tdata, data2, results, 10 );
		fprintf( stderr, "va_addarrays({1,2,3,4,5,6,7,8,9,10},data2,results,10) = %g results[9]=%g\n", sum, results[9] );
		sum = va_addarrays( tdata, data2, results, 12 );
		fprintf( stderr, "va_addarrays({1,2,3,4,5,6,7,8,9,10,11,12},data2,results,12) = %g results[11]=%g\n", sum, results[11] );

		Nt = 100 + 1;
		HRTime_tic();
		for( i = 1, r = 0 ; i < Nt && ssum( data, N ) ; i++ ){
			r += 1;
		}
		toc = HRTime_toc();
		fprintf( stderr, "%lux ssum(data) in %gs -> %gHz\n", r, toc, r/toc );
		HRTime_tic();
		for( i = 1, r = 0 ; i < Nt && va_sum( data, N ) ; i++ ){
			r += 1;
		}
		toc = HRTime_toc();
		fprintf( stderr, "%lux va_sum(data) in %gs -> %gHz\n", r, toc, r/toc );
		HRTime_tic();
		for( i = 1, r = 0 ; i < Nt && sse3_sum( data, N ) ; i++ ){
			r += 1;
		}
		toc = HRTime_toc();
		fprintf( stderr, "%lux sse3_sum(data) in %gs -> %gHz\n", r, toc, r/toc );
		HRTime_tic();
		for( i = 1, r = 0 ; i < Nt && sse3_sumb( data, N ) ; i++ ){
			r += 1;
		}
		toc = HRTime_toc();
		fprintf( stderr, "%lux sse3_sumb(data) in %gs -> %gHz\n", r, toc, r/toc );
#ifdef __AVX__
		for( j = 0 ; j < 4 ; ++j ){
			HRTime_tic();
			for( i = 1, r = 0 ; i < Nt && avx_sumb( data, N ) ; ++i ){
				r += 1;
			}
			toc = HRTime_toc();
			fprintf( stderr, "%lux avx_sumb(data) in %gs -> %gHz\n", r, toc, r/toc );
			HRTime_tic();
			for( i = 1, r = 0 ; i < Nt && avx_sumc( data, N ) ; ++i ){
				r += 1;
			}
			toc = HRTime_toc();
			fprintf( stderr, "%lux avx_sumc(data) in %gs -> %gHz\n", r, toc, r/toc );
		}
#endif
		Nt = 100 + 1;
		HRTime_tic();
		for( i = 1, r = 0 ; i < Nt && ssumsq( data, N ) ; i++ ){
			r += 1;
		}
		toc = HRTime_toc();
		fprintf( stderr, "%lux ssumsq(data) in %gs -> %gHz\n", r, toc, r/toc );
		HRTime_tic();
		for( i = 1, r = 0 ; i < Nt && va_sumsq( data, N ) ; i++ ){
			r += 1;
		}
		toc = HRTime_toc();
		fprintf( stderr, "%lux va_sumsq(data) in %gs -> %gHz\n", r, toc, r/toc );
#if defined(__SSE4__) || defined(__SSE4_1__) || defined(__SSE4_2__)
		HRTime_tic();
		for( i = 1, r = 0 ; i < Nt && sse4_sumsq( data, N ) ; i++ ){
			r += 1;
		}
		toc = HRTime_toc();
		fprintf( stderr, "%lux sse4_sumsq(data) in %gs -> %gHz\n", r, toc, r/toc );
#endif
		HRTime_tic();
		for( i = 1, r = 0 ; i < Nt && sse3_sumsqb( data, N ) ; i++ ){
			r += 1;
		}
		toc = HRTime_toc();
		fprintf( stderr, "%lux sse3_sumsqb(data) in %gs -> %gHz\n", r, toc, r/toc );

		Nt = 100 + 1;
		HRTime_tic();
		for( i = 1, r = 0 ; i < Nt && ssumsq( data, N, sumsq ) ; i++ ){
			r += 1;
		}
		toc = HRTime_toc();
		fprintf( stderr, "%lux ssumsq(data,&sumsq) in %gs -> %gHz\n", r, toc, r/toc );
		HRTime_tic();
		for( i = 1, r = 0 ; i < Nt && va_sumsq( data, N, sumsq ) ; i++ ){
			r += 1;
		}
		toc = HRTime_toc();
		fprintf( stderr, "%lux va_sumsq(data, sumsq) in %gs -> %gHz\n", r, toc, r/toc );
#if defined(__SSE4__) || defined(__SSE4_1__) || defined(__SSE4_2__)
		HRTime_tic();
		for( i = 1, r = 0 ; i < Nt && sse4_sumsq( data, N, sumsq ) ; i++ ){
			r += 1;
		}
		toc = HRTime_toc();
		fprintf( stderr, "%lux sse4_sumsq(data, sumsq) in %gs -> %gHz\n", r, toc, r/toc );
#endif
		HRTime_tic();
		for( i = 1, r = 0 ; i < Nt && sse3_sumsqb( data, N, sumsq ) ; i++ ){
			r += 1;
		}
		toc = HRTime_toc();
		fprintf( stderr, "%lux sse3_sumsqb(data, sumsq) in %gs -> %gHz\n", r, toc, r/toc );

		Nt = 50 + 1;
		HRTime_tic();
		for( i = 1, r = 0 ; i < Nt && saddarrayscalar( data, 10, results, N ) ; i++ ){
			r += 1;
		}
		toc = HRTime_toc();
		fprintf( stderr, "%lux saddarrayscalar(data,10,results,N) in %gs -> %gHz\n", r, toc, r/toc );
		HRTime_tic();
		for( i = 1, r = 0 ; i < Nt && va_addarrayscalar( data, 10, results, N ) ; i++ ){
			r += 1;
		}
		toc = HRTime_toc();
		fprintf( stderr, "%lux va_addarrayscalar(data,10,results,N) in %gs -> %gHz\n", r, toc, r/toc );
		HRTime_tic();
		for( i = 1, r = 0 ; i < Nt && saddarrays( data, data2, results, N ) ; i++ ){
			r += 1;
		}
		toc = HRTime_toc();
		fprintf( stderr, "%lux saddarrays(data,data2,results,N) in %gs -> %gHz\n", r, toc, r/toc );
		HRTime_tic();
		for( i = 1, r = 0 ; i < Nt && va_addarrays( data, data2, results, N ) ; i++ ){
			r += 1;
		}
		toc = HRTime_toc();
		fprintf( stderr, "%lux va_addarrays(data,data2,results,N) in %gs -> %gHz\n", r, toc, r/toc );
		HRTime_tic();
		for( i = 1, r = 0 ; i < Nt && smularrays( data, data2, results, N ) ; i++ ){
			r += 1;
		}
		toc = HRTime_toc();
		fprintf( stderr, "%lux smularrays(data,data2,results,N) in %gs -> %gHz\n", r, toc, r/toc );
		HRTime_tic();
		for( i = 1, r = 0 ; i < Nt && va_mularrays( data, data2, results, N ) ; i++ ){
			r += 1;
		}
		toc = HRTime_toc();
		fprintf( stderr, "%lux va_mularrays(data,data2,results,N) in %gs -> %gHz\n", r, toc, r/toc );

		r = bisect_find( data, N, 10, klo, khi );
		fprintf( stderr, "bisect_find(.., 10,..)=%d -> bracketing values data[%d]=%g data[%d]=%g\n",
			   r, klo, data[klo], khi, data[khi]
		);
		r = bisect_find( data, N, 12.5, klo, khi );
		fprintf( stderr, "bisect_find(.., 12.5,..)=%d -> bracketing values data[%d]=%g data[%d]=%g\n",
			   r, klo, data[klo], khi, data[khi]
		);
		r = bisect_find( data, N, 0, klo, khi );
		fprintf( stderr, "bisect_find(.., 0,..)=%d -> bracketing values data[%d]=%g data[%d]=%g\n",
			   r, klo, data[klo], khi, data[khi]
		);
		HRTime_tic();
		r = va_find( data, N, 10.0, klo );
		toc = HRTime_toc();
		fprintf( stderr, "va_find(.., 10, ..)=%d: data[%d]=%g (%gs)\n", r, klo, data[klo], toc );
		HRTime_tic();
		r = va_find( data, N, 12.5, klo );
		toc = HRTime_toc();
		fprintf( stderr, "va_find(.., 12.5, ..)=%d: data[%d]=%g (%gs)\n", r, klo, data[klo], toc );
		HRTime_tic();
		r = va_find( data, N, 1000, klo );
		toc = HRTime_toc();
		fprintf( stderr, "va_find(.., 1000, ..)=%d: data[%d]=%g (%gs)\n", r, klo, data[klo], toc );
		HRTime_tic();
		r = va_find( data, N, 100000, klo );
		toc = HRTime_toc();
		fprintf( stderr, "va_find(.., 100000, ..)=%d: data[%d]=%g (%gs)\n", r, klo, data[klo], toc );
		HRTime_tic();
		r = va_find( data, N, 10000000, klo );
		toc = HRTime_toc();
		fprintf( stderr, "va_find(.., 10000000, ..)=%d: data[%d]=%g (%gs)\n", r, klo, data[klo], toc );

		Nt = N/1 + 1;
		for( k = 0 ; k < 10 ; k++ ){
		  int p;
		  double bias;
			switch( k ){
				case 0:
					stride = 1;
					break;
				case 1:
					stride = 10;
					break;
				default:
					stride += 10;
					break;
			}
			HRTime_tic();
			for( j = 0, r = 0, p = 0 ; j < stride ; j++ ){
				for( i = 1 ; i < Nt && bisect_find_nop( data, N, i, klo, khi ) ; i+=stride, p++ ){
					r += 1;
				}
			}
			bias = HRTime_toc();
			HRTime_tic();
			for( j = 0, r = 0, p = 0 ; j < stride ; j++ ){
				for( i = 1 ; i < Nt && bisect_find( data, N, i, klo, khi ) ; i+=stride, p++ ){
					r += 1;
				}
			}
			toc = HRTime_toc() - bias;
			fprintf( stderr, "%d:%lux pure bisect_find(..,i,..), with stride=%d in %gs -> %gHz (bias=%gs)\n",
				   p, r, stride, toc, r/toc, bias );
		}
		Nt = Nt/500 + 1;
		HRTime_tic();
		for( i = 1, r = 0 ; i < Nt && va_find( data, N, i, klo ) ; i++ ){
			r += 1;
		}
		toc = HRTime_toc();
		fprintf( stderr, "%lux va_find(..,i,..) in %gs -> %gHz\n", r, toc, r/toc );

		_mm_free(data);
		_mm_free(data2);
		_mm_free(results);
	}
	exit(0);
}
