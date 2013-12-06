/*
 *  benchmark.cpp
 *  macstl
 *
 *  Created by Glen Low on Oct 29 2004.
 *
 *  Copyright (c) 2004-2005 Pixelglow Software, all rights reserved.
 *  http://www.pixelglow.com/macstl/
 *  macstl@pixelglow.com
 *
 *  Unless explicitly acquired and licensed from Licensor under the Pixelglow
 *  Software License ("PSL") Version 2.0 or greater, the contents of this file
 *  are subject to the Reciprocal Public License ("RPL") Version 1.1, or
 *  subsequent versions as allowed by the RPL, and You may not copy or use this
 *  file in either source code or executable form, except in compliance with the
 *  terms and conditions of the RPL.
 *
 *  While it is an open-source license, the RPL prohibits you from keeping your
 *  derivations of this file proprietary even if you only deploy them in-house.
 *  You may obtain a copy of both the PSL and the RPL ("the Licenses") from
 *  Pixelglow Software ("the Licensor") at http://www.pixelglow.com/.
 *
 *  Software distributed under the Licenses is distributed on an "AS IS" basis,
 *  WITHOUT WARRANTY OF ANY KIND, either express or implied. See the Licenses
 *  for the specific language governing rights and limitations under the
 *  Licenses. Notwithstanding anything else in the Licenses, if any clause of
 *  the Licenses which purports to disclaim or limit the Licensor's liability
 *  for breach of any condition or warranty (whether express or implied by law)
 *  would otherwise be void, that clause is deemed to be subject to the
 *  reservation of liability of the Licensor to supply the software again or to
 *  repair the software or to pay the cost of having the software supplied again
 *  or repaired, at the Licensor's option.
 */

/*
	On a Mac G4:
	g++-3.3 -x c++ -pipe -Wno-trigraphs -fasm-blocks -faltivec -O3 -mcpu=G4 -mtune=G4 -Wno-unknown-pragmas -fmessage-length=0 -mdynamic-no-pic -I/usr/local/include -falign-loops=16 -falign-jumps=16 -falign-functions=16 -fstrict-aliasing -funroll-loops benchmark.cpp -o benchmark -Wl,-no_arch_warnings -Wl,-dead_strip -mfused-madd -mmultiple -misel=yes -fomit-frame-pointer

	On a Mac G5:
	g++-3.3 -x c++ -pipe -Wno-trigraphs -fasm-blocks -faltivec -O3 -mcpu=G5 -mtune=G5 -mpowerpc64 -Wno-unknown-pragmas -fmessage-length=0 -mdynamic-no-pic -I/usr/local/include -falign-loops=32 -falign-jumps=32 -falign-functions=32 -fstrict-aliasing -funroll-loops benchmark-macstl.cpp -o benchmark-macstl -Wl,-no_arch_warnings -Wl,-dead_strip -mfused-madd -mmultiple -misel=yes -fomit-frame-pointer

 */

#undef DO_CHAR
#undef DO_SHORT
#define DO_LONG
#undef DO_LONGLONG
#define DO_FLOAT
#define DO_DOUBLE

#ifdef ONLY_LONGLONG
#	undef DO_CHAR
#	undef DO_SHORT
#	undef DO_LONG
#	undef DO_FLOAT
#	undef DO_DOUBLE
#endif

#ifdef __GCCOPT__
#	include <local/Macros.h>
IDENTIFY( "MacSTL benchmark" );
#endif

/*
 * Performs several benchmark speed tests of the stdext::valarray implementation.
 *
 * In each test, we use arrays of size 1000 and ensure they are cache-bound. The # of iterations per second,
 * the factor speedup over the library's std::valarray and over an equivalent C arrays and loop are measured.
 *
 * mul-add:			v1 * v2 + v3						basic arithmetic, fma optimization, vector intrinsics
 * inner product:	(v1 * v2).sum ()					fma optimization, scalarization
 * polynomial:		3.0 * v1 * v1 + 2.0 * v1 + 1.0		fma optimization, constant loading, vector intrinsics
 * hypotenuse:		sqrt (v1 * v1 + v2 * v2)			sqrt optimization, vector inline transcendentals
 * complex mul-add:	v1 * v2 + v3						complex arithmetic, fma optimization
 * predicate:		(v1 == v2).max ()					predication intrinsics
 * slicing:			v1 [slice (0, size, 4)]				basic arithmetic, slicing
 *				  + v2 [slice (0, size, 5)]
 *				  + v3 [slice (0, size, 6)]
 * power:			exp (ln (v1) * v2)					inline transcendentals
 * trigonometric:	sin (v1) * cos (v2) +				inline transcendentals, fma optimization, register spills
 *				  + sin (v2) * cos (v1)
 *
 */


#include <iostream>
#include <stdexcept>
#include <complex>
#include <valarray>
#include <time.h>
#include <signal.h>

#include "macstl/valarray.h"

#include "benchmark-macstl.h"

 #ifdef __i386__

#ifndef __MMX__
#	warning "__MMX__ undefined"
#endif
#ifndef __SSE__
#	warning "__SSE__ undefined"
#endif
#ifndef __SSE2__
#	warning "__SSE2__ undefined"
#endif

 #endif

const std::size_t prime_caches = 100;
const std::size_t size = 1000;
const std::size_t tries = 100000;
std::size_t tried= 0;

const int step1 = 5;
const int step2 = 6;
const int step3 = 7;

/* 20050417 RJVB
 \ bench() uses clock(), which is not the most fine-grained timer in existence. In addition, some
 \ of the benchmarks execute in a fraction of a second or less -- and not just the stdext:: ones.
 \ That makes the results overly sensitive to micropeaks of other activity on the system.
 \ Therefore, do some simple adaptive scaling, requiring a minimum execution time (of 0.75 seconds);
 \ the default number of samples (tries) is multiplied by 5 until this time is exceeded. The additional
 \ wait that this causes can be neglected. A smaller factor (2?) could be used if the sometimes rather
 \ high resulting execution times (5*0.7499999 = 3.749999s) are undesirable.
 */

template <typename Fn> inline clock_t bench ()
{
		Fn fn;
		double duration;
		clock_t start, finish;
#define	ADAPT
#define	MIN_DURATION	0.75
#define	ADAPT_FACTOR	5

		for (unsigned int i = 0; i != prime_caches; ++i)
			fn ();
#ifdef ADAPT
		tried= tries;
		do
#endif
		{
			start = clock ();
			for (unsigned int j = 0; j != tried; ++j)
				fn ();
			finish = clock ();
			duration= (finish - start) / ((double) CLOCKS_PER_SEC);
#ifdef ADAPT
			if( duration< MIN_DURATION ){
/* 				fprintf( stderr, "dt=%g: %d -> %d\n", duration, tried, tried*ADAPT_FACTOR );	*/
				tried*= ADAPT_FACTOR;
			}
#endif
		}
#ifdef ADAPT
		while( duration< MIN_DURATION );
#endif
		return finish - start;
}

/* 20050829 RJVB
 \ global benchmarking:
 */
double stdext_tTime=0, stdext_tN= 0;
double std_tTime=0, std_tN= 0;
double raw_tTime=0, raw_tN= 0;

void reset_global_bench()
{
	stdext_tTime=0, stdext_tN= 0;
	std_tTime=0, std_tN= 0;
	raw_tTime=0, raw_tN= 0;
}

/* 20050417 RJVB
 \ The actual benchmark/comparison function. I modified this to print results as they come in: this gives the user
 \ something more appropriate to contemplate, and provides feedback on where time is being spent, and at what.
 \ Since the number of samples varies, it is printed, along with the actual execution times. For the stdext:: results,
 \ we print the score in Hz (calls/s). For the comparison benchmarks, we only print the # of samples, the total time,
 \ and the gain (or loss) of the stdext: implementation with respect to the reference. This gain is calculated in terms
 \ of the achieved score in Hz: total time can no longer be compared since the # of samples may vary.
 */
template <template <typename> class M, typename V1, typename V2, typename V3> inline void benchmark (const char* title)
	{
		clock_t stdext_run = bench <M <V2> > ();
		unsigned long long stdext_hz, std_hz, raw_hz;
		double time;

		std::cout /* << "Benching " */ << tried << "x " << title << ":  "
			<< "(" << (time= stdext_run/((double) CLOCKS_PER_SEC)) << "s) "
			<< (stdext_hz= (((unsigned long long) tried) * CLOCKS_PER_SEC) / stdext_run) << "/sec  " ;
		fflush(stdout);
		stdext_tTime+= time;
		stdext_tN+= tried;

		clock_t std_run = bench <M <V1> > ();
		std_hz= (((unsigned long long) tried) * CLOCKS_PER_SEC) / std_run;
		std::cout << "(" << tried << "x=" << (time= std_run/((double) CLOCKS_PER_SEC)) << "s) " << ((double) stdext_hz) / ((double) std_hz) << "*std::  " ;
		fflush(stdout);
		std_tTime+= time;
		std_tN+= tried;

		clock_t raw_run = bench <M <V3> > ();
		raw_hz= (((unsigned long long) tried) * CLOCKS_PER_SEC) / raw_run;
		std::cout << "(" << tried << "x=" << (time= raw_run/((double) CLOCKS_PER_SEC)) << "s) " << ((double) stdext_hz) / ((double) raw_hz) << "*\"standard C++\".\n";
		fflush(stdout);
		raw_tTime+= time;
		raw_tN+= tried;
	}

template <typename V> class polynomial
	{
		public:
			polynomial (): v1 (size), vr (size)
				{
					seed ();
					randomize <typename V::value_type> () (v1, size);
				}

			void operator() ()
				{
// 					vr = 3.0f * v1 * v1 + 2.0f * v1 + 1.0f;
// 					vr = ((V)3) * v1 * v1 + ((V)2) * v1 + ((V)1);
				  typedef typename V::value_type value_type;
 					vr = ((value_type) 3) * v1 * v1 + ((value_type) 2) * v1 + ((value_type) 1);
				}

		private:
			V v1;
			V vr;
	};

template <typename T> class polynomial <stdext::statarray <T, size> >
	{
		public:
			polynomial (): v1 (), vr ()
				{
					seed ();
					randomize <T> () (v1, size);
				}

			void operator() ()
				{
// 					vr = 3.0f * v1 * v1 + 2.0f * v1 + 1.0f;
 					vr = ((T)3) * v1 * v1 + ((T)2) * v1 + ((T)1);
// 				  typedef typename T::value_type value_type;
//  					vr = ((value_type) 3) * v1 * v1 + ((value_type) 2) * v1 + ((value_type) 1);
				}

		private:
			stdext::statarray <T, size> v1;
			stdext::statarray <T, size> vr;
	};

template <typename T> class polynomial <T*>
	{
		public:
			polynomial (): v1 (new T [size]), vr (new T [size])
				{
					seed ();
					randomize <T> () (v1, size);
				}

			~polynomial ()
				{
					delete [] v1;
					delete [] vr;
				}

			void operator() ()
				{
					for (std::size_t i = 0; i != size; ++i)
// 						vr [i] = 3.0f * v1 [i] * v1 [i] + 2.0f * v1 [i] + 1.0f;
 						vr [i] = ((T)3) * v1 [i] * v1 [i] + ((T)2) * v1 [i] + ((T)1);
				}

		private:
			T* v1;
			T* vr;
	};


template <typename V> class multiply_add
	{
		public:
			multiply_add (): v1 (size), v2 (size), v3 (size), vr (size)
				{
					seed ();
					randomize <typename V::value_type> () (v1, size);
					randomize <typename V::value_type> () (v2, size);
					randomize <typename V::value_type> () (v3, size);
				}

			void operator() ()
				{
					vr = v1 * v2 + v3;
				}

		private:
			V v1;
			V v2;
			V v3;
			V vr;
	};

template <typename T> class multiply_add <stdext::statarray <T, size> >
	{
		public:
			multiply_add (): v1 (), v2 (), v3 (), vr ()
				{
					seed ();
					randomize <T> () (v1, size);
					randomize <T> () (v2, size);
					randomize <T> () (v3, size);
				}

			void operator() ()
				{
					vr = v1 * v2 + v3;
				}

		private:
			stdext::statarray <T, size> v1;
			stdext::statarray <T, size> v2;
			stdext::statarray <T, size> v3;
			stdext::statarray <T, size> vr;
	};

template <typename T> class multiply_add <T*>
	{
		public:
			multiply_add (): v1 (new T [size]), v2 (new T [size]), v3 (new T [size]), vr (new T [size])
				{
					seed ();
					randomize <T> () (v1, size);
					randomize <T> () (v2, size);
					randomize <T> () (v3, size);
				}

			~multiply_add ()
				{
					delete [] v1;
					delete [] v2;
					delete [] v3;
					delete [] vr;
				}

			void operator() ()
				{
					for (std::size_t i = 0; i != size; ++i)
						vr [i] = v1 [i] * v2 [i] + v3 [i];
				}

		private:
			T* v1;
			T* v2;
			T* v3;
			T* vr;
	};

template <typename V> class division
	{
		public:
			division (): v1 (size), v2 (size), vr (size)
				{
					seed ();
					randomize <typename V::value_type> () (v1, size);
					randomize <typename V::value_type> () (v2, size);
				}

			void operator() ()
				{
					vr = v1 / v2;
				}

		private:
			V v1;
			V v2;
			V vr;
	};

template <typename T> class division <T*>
	{
		public:
			division (): v1 (new T [size]), v2 (new T [size]), vr (new T [size])
				{
					seed ();
					randomize <T> () (v1, size);
					randomize <T> () (v2, size);
				}

			~division ()
				{
					delete [] v1;
					delete [] v2;
					delete [] vr;
				}

			void operator() ()
				{
					for (std::size_t i = 0; i != size; ++i)
						vr [i] = v1 [i] / v2 [i];
				}

		private:
			T* v1;
			T* v2;
			T* vr;
	};

template <typename V> class inner_product
	{
		public:
			inner_product (): v1 (size), v2 (size)
				{
					seed ();
					randomize <typename V::value_type> () (v1, size);
					randomize <typename V::value_type> () (v2, size);
				}

			void operator() ()
				{
					r = (v1 * v2).sum ();
				}

		private:
			V v1;
			V v2;
			typename V::value_type r;
	};

template <typename T> class inner_product <stdext::statarray <T, size> >
	{
		public:
			inner_product (): v1 (), v2 ()
				{
					seed ();
					randomize <T> () (v1, size);
					randomize <T> () (v2, size);
				}

			void operator() ()
				{
					r = (v1 * v2).sum ();
				}

		private:
			stdext::statarray <T, size> v1;
			stdext::statarray <T, size> v2;
			T r;
	};

template <typename T> class inner_product <T*>
	{
		public:
			inner_product (): v1 (new T [size]), v2 (new T [size])
				{
					seed ();
					randomize <T> () (v1, size);
					randomize <T> () (v2, size);
				}

			~inner_product ()
				{
					delete [] v1;
					delete [] v2;
				}

			void operator() ()
				{
					T r2 = v1 [0] * v2 [0];
					for (std::size_t i = 1; i != size; ++i)
						r2 += v1 [i] * v2 [i];
					r = r2;
				}

		private:
			T* v1;
			T* v2;

		public:
			static T r;	// prevent optimizing this away!!
	};

template <typename T> T inner_product <T*>::r;

template <typename V> class hypotenuse
	{
		public:
			hypotenuse (): v1 (size), v2 (size), vr (size)
				{
					seed ();
					randomize <typename V::value_type> () (v1, size);
					randomize <typename V::value_type> () (v2, size);
				}

			void operator() ()
				{
					vr = sqrt (v1 * v1 + v2 * v2);
				}

		private:
			V v1;
			V v2;
			V vr;
	};

template <typename T> class hypotenuse <stdext::statarray <T, size> >
	{
		public:
			hypotenuse (): v1 (), v2 (), vr ()
				{
					seed ();
					randomize <T> () (v1, size);
					randomize <T> () (v2, size);
				}

			void operator() ()
				{
					vr = sqrt (v1 * v1 + v2 * v2);
				}

		private:
			stdext::statarray <T, size> v1;
			stdext::statarray <T, size> v2;
			stdext::statarray <T, size> vr;
	};

template <typename T> class hypotenuse <T*>
	{
		public:
			hypotenuse (): v1 (new T [size]), v2 (new T [size]), vr (new T [size])
				{
					seed ();
					randomize <T> () (v1, size);
					randomize <T> () (v2, size);
				}

			~hypotenuse ()
				{
					delete [] v1;
					delete [] v2;
					delete [] vr;
				}

			void operator() ()
				{
					for (std::size_t i = 0; i != size; ++i)
						vr [i] = std::sqrt (v1 [i] * v1 [i] + v2 [i] * v2 [i]);
				}

		private:
			T* v1;
			T* v2;
			T* vr;
	};

template <typename V> class trigonometric
	{
		public:
			trigonometric (): v1 (size), v2 (size), vr (size)
				{
					seed ();
					randomize <typename V::value_type> () (v1, size);
					randomize <typename V::value_type> () (v2, size);
				}

			void operator() ()
				{
					vr = sin (v1) * cos (v2) + sin (v2) * cos (v1);
				}

		private:
			V v1;
			V v2;
			V vr;
	};



template <typename T> class trigonometric <stdext::statarray <T, size> >
	{
		public:
			trigonometric (): v1 (), v2 (), vr ()
				{
					seed ();
					randomize <T> () (v1, size);
					randomize <T> () (v2, size);
				}

			void operator() ()
				{
					vr = sin (v1) * cos (v2) + sin (v2) * cos (v1);
				}

		private:
			stdext::statarray <T, size> v1;
			stdext::statarray <T, size> v2;
			stdext::statarray <T, size> vr;
	};

#if defined(i386) || defined(_MSC_VER)
#	if defined(_MSC_VER) || defined(__CYGWIN__)
		extern void sincos( double, double*, double* );

#define SSE_MATHFUN_WITH_CODE

#ifdef __SSE__
#		define USE_SSE2
#		include <xmmintrin.h>
#		include <emmintrin.h>
#		include "sse_mathfun.h"

		void fsincos_sse(float x, float *s, float *c )
		{ v4sf xx, ss, cc;
//  			xx = _mm_set_ps1(x);
 			((float*)&xx)[0] = (float) x;
			sincos_ps(xx, &ss, &cc);
			*s = ((float*)&ss)[0];
			*c = ((float*)&cc)[0];
		}
#		define fsincos(x,s,c)	fsincos_sse((x),(s),(c))
#endif

#	else

#		ifdef __SSE__

#			define USE_SSE2
#			include <xmmintrin.h>
#			include <emmintrin.h>
#			include "sse_mathfun.h"

			void fsincos_sse(float x, float *s, float *c )
			{ v4sf xx, ss, cc;
// 				xx = _mm_set_ps1(x);
				((float*)&xx)[0] = (float) x;
				sincos_ps(xx, &ss, &cc);
				*s = ((float*)&ss)[0];
				*c = ((float*)&cc)[0];
			}

#			define fsincos(x,s,c)	fsincos_sse((x),(s),(c))

#		else

			void fsincos_x86_fpu(float x, float *s, float *c )
			{
				asm( "fsincos;" : "=t" (*c), "=u" (*s) : "0" (x) : "st(7)" );
			}

#			define fsincos(x,s,c)	fsincos_x86_fpu((x),(s),(c))
#		endif

#	endif

namespace std
{
//	using ::sincos;

	inline void sincos(float __x, float* __sin, float* __cos)
	{
		fsincos(__x,__sin,__cos);
	}
}
#endif

template <typename T> class trigonometric <T*>
	{
		public:
			trigonometric (): v1 (new T [size]), v2 (new T [size]), vr (new T [size])
				{
					seed ();
					randomize <T> () (v1, size);
					randomize <T> () (v2, size);
				}

			~trigonometric ()
				{
					delete [] v1;
					delete [] v2;
					delete [] vr;
				}

			void operator() ()
				{
					for (std::size_t i = 0; i != size; ++i){
#ifdef i386
					  float v1s, v1c, v2s, v2c;
						std::sincos( v1[i], &v1s, &v1c );
						std::sincos( v2[i], &v2s, &v2c );
						vr [i] = v1s * v2c + v2s * v1c;
#else
						vr [i] = std::sin (v1 [i]) * std::cos (v2 [i]) + std::sin (v2 [i]) * std::cos (v1 [i]);
#endif
					}
				}

		private:
			T* v1;
			T* v2;
			T* vr;
	};

template <typename V> class power
	{
		public:
			power (): v1 (size), v2 (size), vr (size)
				{
					seed ();
					randomize <typename V::value_type> () (v1, size);
					randomize <typename V::value_type> () (v2, size);
				}

			void operator() ()
				{
					vr = exp (log (v1) * v2);
				}

		private:
			V v1;
			V v2;
			V vr;
	};



template <typename T> class power <stdext::statarray <T, size> >
	{
		public:
			power (): v1 (), v2 (), vr ()
				{
					seed ();
					randomize <T> () (v1, size);
					randomize <T> () (v2, size);
				}

			void operator() ()
				{
					vr = exp (log (v1) * v2);
				}

		private:
			stdext::statarray <T, size> v1;
			stdext::statarray <T, size> v2;
			stdext::statarray <T, size> vr;
	};

template <typename T> class power <T*>
	{
		public:
			power (): v1 (new T [size]), v2 (new T [size]), vr (new T [size])
				{
					seed ();
					randomize <T> () (v1, size);
					randomize <T> () (v2, size);
				}

			~power ()
				{
					delete [] v1;
					delete [] v2;
					delete [] vr;
				}

			void operator() ()
				{
					for (std::size_t i = 0; i != size; ++i)
						vr [i] = std::exp (std::log (v1 [i]) * v2 [i]);
				}

		private:
			T* v1;
			T* v2;
			T* vr;
	};

#ifdef DEBUG
static bool called;
#endif

template <typename V> class predicate
	{
		public:
			predicate (): v1 (size), v2 (size)
				{
					seed ();
					randomize <typename V::value_type> () (v1, size);
					randomize <typename V::value_type> () (v2, size);
#ifdef DEBUG
					called= False;
#endif
				}

			void operator() ()
				{
#ifdef DEBUG
					if( !called ){
						fprintf( stderr, " predicate(|v1|=%d) ", sizeof(typename V::value_type) );
						called= True;
					}
#endif
					r = (v1 == v2).max ();
				}

		private:
			V v1;
			V v2;
			bool r;
	};

template <typename T> class predicate <stdext::statarray <T, size> >
	{
		public:
			predicate (): v1 (), v2 ()
				{
					seed ();
					randomize <T> () (v1, size);
					randomize <T> () (v2, size);
#ifdef DEBUG
					called= False;
#endif
				}

			void operator() ()
				{
#ifdef DEBUG
					if( !called ){
						fprintf( stderr, " predicate(|T|=%d) ", sizeof(T) );
						called= True;
					}
#endif
					r = (v1 == v2).max ();
				}

		private:
			stdext::statarray <T, size> v1;
			stdext::statarray <T, size> v2;
			bool r;
	};

template <typename T> class predicate <T*>
	{
		public:
			predicate (): v1 (new T [size]), v2 (new T [size])
				{
					seed ();
					randomize <T> () (v1, size);
					randomize <T> () (v2, size);
#ifdef DEBUG
					called= False;
#endif
				}

			~predicate ()
				{
					delete [] v1;
					delete [] v2;
				}

			void operator() ()
				{
#ifdef DEBUG
					if( !called ){
						fprintf( stderr, " predicate(|T|=%d) ", sizeof(T) );
						called= True;
					}
#endif
					r = false;
					for (std::size_t i = 0; i != size; ++i)
						if (v1 [i] == v2 [i])
							{
								r = true;
								return;
							}
				}

		private:
			T* v1;
			T* v2;

		public:
			static bool r;	// prevent optimizing this away!!
	};

template <typename T> bool predicate <T*>::r;


template <typename V> class slicing
	{
		public:
			slicing (): v1 (size * step1), v2 (size * step2), v3 (size * step3), vr (size)
				{
					seed ();
					randomize <typename V::value_type> () (v1, size * step1);
					randomize <typename V::value_type> () (v2, size * step2);
					randomize <typename V::value_type> () (v3, size * step3);
				}

			void operator() ()
				{
					vr = ((const V&) v1) [std::slice (0, size, step1)]
						+ ((const V&) v2) [std::slice (0, size, step2)]
						+ ((const V&) v3) [std::slice (0, size, step3)];
				}

		private:
			V v1;
			V v2;
			V v3;
			V vr;
	};

template <typename T> class slicing <stdext::valarray <T> >
	{
		public:
			slicing (): v1 (size * step1),  v2 (size * step2),  v3 (size * step3), vr (size)
				{
					seed ();
					randomize <T> () (v1, size * step1);
					randomize <T> () (v2, size * step2);
					randomize <T> () (v3, size * step3);
				}

			void operator() ()
				{
					vr = v1 [stdext::slice (0, size, step1)]
						+ v2 [stdext::slice (0, size, step2)]
					+ v3 [stdext::slice (0, size, step3)];
				}

		private:
			stdext::valarray <T> v1;
			stdext::valarray <T> v2;
			stdext::valarray <T> v3;
			stdext::valarray <T> vr;
	};

template <typename T> class slicing <stdext::statarray <T, size> >
	{
		public:
			slicing (): v1 (),  v2 (),  v3 (), vr ()
				{
					seed ();
					randomize <T> () (v1, size * step1);
					randomize <T> () (v2, size * step2);
					randomize <T> () (v3, size * step3);
				}

			void operator() ()
				{
					vr = v1 [stdext::slice (0, size, step1)]
						+ v2 [stdext::slice (0, size, step2)]
					+ v3 [stdext::slice (0, size, step3)];
				}

		private:
			stdext::statarray <T, size * step1> v1;
			stdext::statarray <T, size * step2> v2;
			stdext::statarray <T, size * step3> v3;
			stdext::statarray <T, size> vr;
	};

template <typename T> class slicing <T*>
	{
		public:
			slicing (): v1 (new T [size * step1]), v2 (new T [size * step2]), v3 (new T [size * step3]), vr (new T [size])
				{
					seed ();
					randomize <T> () (v1, size * step1);
					randomize <T> () (v2, size * step2);
					randomize <T> () (v3, size * step3);
				}

			~slicing ()
				{
					delete [] v1;
					delete [] v2;
					delete [] v3;
					delete [] vr;
				}

			void operator() ()
				{
					for (std::size_t i = 0; i != size; ++i)
						vr [i] = v1 [i * step1] + v2 [i * step2] + v3 [i * step3];

				}

		private:
			T* v1;
			T* v2;
			T* v3;
			T* vr;
	};

void global_benchmarks()
{ double stdext_Hz= 0, std_Hz= 0, raw_Hz= 0;
	if( stdext_tN> 0 ){
		fputs( "## Overall results (excluding char benchmarks):\n", stdout );
		fprintf( stdout, "%g operations in %gs = %g/s -- stdext:: (macstl)\n",
			stdext_tN, stdext_tTime, (stdext_Hz= stdext_tN/stdext_tTime)
		);
	}
	if( std_tN> 0 ){
		fprintf( stdout, "%g operations in %gs = %g/s -- std::\n",
			std_tN, std_tTime, (std_Hz= std_tN/std_tTime)
		);
	}
	if( raw_tN> 0 ){
		fprintf( stdout, "%g operations in %gs = %g/s -- \"standard C++\"\n",
			raw_tN, raw_tTime, (raw_Hz= raw_tN/raw_tTime)
		);
	}
	if( std_Hz ){
		fprintf( stdout, "stdext:: benchmarks at %gx std:: ; \"standard C++\" benchmarks at %gx std::\n",
			stdext_Hz/std_Hz, raw_Hz/std_Hz
		);
	}
	if( raw_Hz ){
		fprintf( stdout, "stdext:: benchmarks at %gx \"standard C++\" ; std:: benchmarks at %gx \"standard C++\"\n",
			stdext_Hz/raw_Hz, std_Hz/raw_Hz
		);
	}
	if( stdext_Hz ){
	  double N, Time;
		N= stdext_tN+std_tN+raw_tN, Time= stdext_tTime+std_tTime+raw_tTime;
		fprintf( stdout, "Grand totals: %g operations in %gs = %g/s\n",
			N, Time, N/Time
		);
	}
}

void sighandler(int sig)
{
	global_benchmarks();
	exit(sig);
}

int main (int, char *argvp[])
{
#if defined(__GNUC__) && defined(__i386__) && ( (__GNUC__ == 2 && __GNUC_MINOR__ >= 9) || __GNUC__ > 2 )
     /* RJVB: this comes from fftw 3.0.1:
      * horrible hack to align the stack to a 16-byte boundary.
      *
      * We assume a gcc version >= 2.95 so that
      * -mpreferred-stack-boundary works.  Otherwise, all bets are
      * off.  However, -mpreferred-stack-boundary does not create a
      * stack alignment, but it only preserves it.  Unfortunately,
      * many versions of libc on linux call main() with the wrong
      * initial stack alignment, with the result that the code is now
      * pessimally aligned instead of having a 50% chance of being
      * correct.
      */
	{
		/*
		* Use alloca to allocate some memory on the stack.
		* This alerts gcc that something funny is going
		* on, so that it does not omit the frame pointer
		* etc.
		*/
		(void)__builtin_alloca(16);

		/*
		* Now align the stack pointer
		*/
		__asm__ __volatile__ ("andl $-16, %esp");

		if( getenv("XG_BAD_STACKALIGN") ){
			/* pessimally align the stack, in order to check whether the
			   stack re-alignment hacks in FFTW3 work
			*/
			__asm__ __volatile__ ("addl $-4, %esp");
		}
	}
#	ifdef __GNUC__
#		warning "16-bit stack alignment forced"
#	endif
#endif

#if defined(__APPLE_CC__) || defined(linux)
	signal( SIGHUP, sighandler );
#endif
	signal( SIGINT, sighandler );
	signal( SIGTERM, sighandler );

		std::cout << "## macstl benchmark, comparing performance of several stdext::valarray operations\n"
				<< "## with the same operations using std::valarray and using \"standard C(++)\" code.\n";

#if defined(__SSE__)
#	if defined(__GNUC__)
#		warning "on Intel, treat denormals as zero for full speed"
#	endif
		_mm_setcsr (_mm_getcsr () | 0x8040);	// on Intel, treat denormals as zero for full speed
#endif

#ifdef DO_CHAR
		// RJVB: also have a look at chars!
		benchmark <multiply_add,
			std::valarray <char>,
			stdext::valarray <char>,
			char*> ("multiply add (char)");
		benchmark <inner_product,
			std::valarray <char>,
			stdext::valarray <char>,
			char*> ("inner product (char)");
		benchmark <polynomial,
			std::valarray <char>,
			stdext::valarray <char>,
			char*> ("polynomial (char)");
#ifndef _MSC_VER	// Visual C++ ICE's here
		benchmark <predicate,
			std::valarray <char>,
			stdext::valarray <char>,
			char*> ("predicate (char)");
#endif
		benchmark <slicing,
			std::valarray <char>,
			stdext::valarray <char>,
			char*> ("slicing (char)");
		std::cout << "\n";
#endif

#ifdef DO_SHORT
		// RJVB: also have a look at shorts!
		reset_global_bench();
		benchmark <multiply_add,
			std::valarray <short>,
			stdext::valarray <short>,
			short*> ("multiply add (short)");
		benchmark <inner_product,
			std::valarray <short>,
			stdext::valarray <short>,
			short*> ("inner product (short)");
		benchmark <polynomial,
			std::valarray <short>,
			stdext::valarray <short>,
			short*> ("polynomial (short)");
#ifndef _MSC_VER	// Visual C++ ICE's here
		benchmark <predicate,
			std::valarray <short>,
			stdext::valarray <short>,
			short*> ("predicate (short)");
#endif
		benchmark <slicing,
			std::valarray <short>,
			stdext::valarray <short>,
			short*> ("slicing (short)");

		std::cout << "\n";
#endif

#ifdef DO_LONG
		// RJVB: also have a look at longs!
		benchmark <multiply_add,
			std::valarray <long>,
			stdext::valarray <long>,
			long*> ("multiply add (long)");
		benchmark <inner_product,
			std::valarray <long>,
			stdext::valarray <long>,
			long*> ("inner product (long)");
		benchmark <polynomial,
			std::valarray <long>,
			stdext::valarray <long>,
			long*> ("polynomial (long)");
#ifndef _MSC_VER	// Visual C++ ICE's here
		benchmark <predicate,
			std::valarray <long>,
			stdext::valarray <long>,
			long*> ("predicate (long)");
#endif
		benchmark <slicing,
			std::valarray <long>,
			stdext::valarray <long>,
			long*> ("slicing (long)");

		std::cout << "\n";
#endif

#ifdef DO_LONGLONG
		// RJVB: also have a look at long long!
		benchmark <multiply_add,
			std::valarray <long long>,
			stdext::valarray <long long>,
			long long*> ("multiply add (long long)");
		benchmark <inner_product,
			std::valarray <long long>,
			stdext::valarray <long long>,
			long long*> ("inner product (long long)");
		benchmark <polynomial,
			std::valarray <long long>,
			stdext::valarray <long long>,
			long long*> ("polynomial (long long)");
#ifndef _MSC_VER	// Visual C++ ICE's here
		benchmark <predicate,
			std::valarray <long long>,
			stdext::valarray <long long>,
			long long*> ("predicate (long long)");
#endif
		benchmark <slicing,
			std::valarray <long long>,
			stdext::valarray <long long>,
			long long*> ("slicing (long long)");

		std::cout << "\n";
#endif

#ifdef DO_FLOAT
		benchmark <multiply_add,
			std::valarray <float>,
			stdext::valarray <float>,
			float*> ("multiply add (float)");

		benchmark <inner_product,
			std::valarray <float>,
			stdext::valarray <float>,
			float*> ("inner product (float)");
		benchmark <polynomial,
			std::valarray <float>,
			stdext::valarray <float>,
			float*> ("polynomial (float)");
		benchmark <hypotenuse,
			std::valarray <float>,
			stdext::valarray <float>,
			float*> ("hypotenuse (float)");

#ifdef HAS_C99_COMPLEX
		benchmark <multiply_add,
			std::valarray <std::complex <float> >,
			stdext::valarray <stdext::complex <float> >,
			float _Complex*> ("complex multiply add (float)");
#endif
#ifndef _MSC_VER	// Visual C++ ICE's here
		benchmark <predicate,
			std::valarray <float>,
			stdext::valarray <float>,
			float*> ("predicate (float)");
#endif

		benchmark <slicing,
			std::valarray <float>,
			stdext::valarray <float>,
			float*> ("slicing (float)");

		benchmark <power,
			std::valarray <float>,
			stdext::valarray <float>,
			float*> ("power (float)");

		benchmark <trigonometric,
			std::valarray <float>,
			stdext::valarray <float>,
			float*> ("trigonometric (float)");

		std::cout << "\n";
#endif

#ifdef DO_DOUBLE
		// RJVB: also have a look at doubles!
		benchmark <multiply_add,
			std::valarray <double>,
			stdext::valarray <double>,
			double*> ("multiply add (double)");

		benchmark <inner_product,
			std::valarray <double>,
			stdext::valarray <double>,
			double*> ("inner product (double)");
		benchmark <polynomial,
			std::valarray <double>,
			stdext::valarray <double>,
			double*> ("polynomial (double)");
		benchmark <hypotenuse,
			std::valarray <double>,
			stdext::valarray <double>,
			double*> ("hypotenuse (double)");

#ifdef HAS_C99_COMPLEX
		benchmark <multiply_add,
			std::valarray <std::complex <double> >,
			stdext::valarray <stdext::complex <double> >,
			double _Complex*> ("complex multiply add (double)");
#endif
#ifndef _MSC_VER	// Visual C++ ICE's here
		benchmark <predicate,
			std::valarray <double>,
			stdext::valarray <double>,
			double*> ("predicate (double)");
#endif

		benchmark <slicing,
			std::valarray <double>,
			stdext::valarray <double>,
			double*> ("slicing (double)");

		benchmark <power,
			std::valarray <double>,
			stdext::valarray <double>,
			double*> ("power (double)");

		benchmark <trigonometric,
			std::valarray <double>,
			stdext::valarray <double>,
			double*> ("trigonometric (double)");

		std::cout << "\n";
#endif

	global_benchmarks();
}



