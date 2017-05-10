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
#include <complex>
#include <valarray>
#include <time.h>

#include <macstl/valarray.h>

#include "common.h"

const std::size_t size = 1000;
const std::size_t tries = 100000;

const int step1 = 5;
const int step2 = 6;
const int step3 = 7;

#if defined(__GNUC__)
#define NOINLINE __attribute__((noinline))
#elif defined(_MSC_VER)
#define NOINLINE __declspec(noinline)
#else
#define NOINLINE
#endif

template <typename Fn> NOINLINE clock_t bench ()
	{
		Fn fn;

		clock_t start = clock ();
		for (std::size_t j = 0; j != tries; ++j)
			fn ();
		clock_t finish = clock ();
		return finish - start;	
	}
	
template <template <typename> class M, typename V1, typename V2, typename V3> inline void benchmark (const char* title)
	{
		clock_t std_run = bench <M <V1> > ();
		clock_t stdext_run = bench <M <V2> > ();
		clock_t raw_run = bench <M <V3> > ();
		
		std::cout << "Benching " << title << ":  "
			<< (((double) tries) * CLOCKS_PER_SEC) / ((double)stdext_run) << "/sec  "
			<< ((double) std_run) / ((double) stdext_run) << "*std  "
			<< ((double) raw_run) / ((double) stdext_run) << "*raw.\n";
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
					typedef typename V::value_type value_type;
					vr = ((value_type) 3) * v1 * v1 + ((value_type) 2) * v1 + ((value_type) 1);
				}
				
		private:
			V v1;
			V vr;
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
						vr [i] = ((T) 3) * v1 [i] * v1 [i] + ((T) 2) * v1 [i] + ((T) 1);
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

	
/*

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
	
*/

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
			static T r;
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
					for (std::size_t i = 0; i != size; ++i)
						vr [i] = std::sin (v1 [i]) * std::cos (v2 [i]) + std::sin (v2 [i]) * std::cos (v1 [i]);
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

template <typename V> class predicate
	{
		public:
			predicate (): v1 (size), v2 (size)
				{
					seed ();
					randomize <typename V::value_type> () (v1, size);
					randomize <typename V::value_type> () (v2, size);
				}
				
			void operator() ()
				{
					r = (v1 == v2).max ();
				}
				
		private:
			V v1;
			V v2;
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
				}
				
			~predicate ()
				{
					delete [] v1;
					delete [] v2;
				}
				
			void operator() ()
				{
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
			bool r;
	};

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

int main (int argc, char *argv[])
	{
		#ifdef __SSE__
		_mm_setcsr (_mm_getcsr () | 0x8040);	// on Intel, treat denormals as zero for full speed
		#endif
		
		benchmark <multiply_add,
			std::valarray <float>,
			stdext::valarray <float>,
			float*> ("multiply add");
		
		benchmark <inner_product,
			std::valarray <float>,
			stdext::valarray <float>,
			float*> ("inner product");
		
		benchmark <polynomial,
			std::valarray <float>,
			stdext::valarray <float>,
			float*> ("polynomial");
		
		
		benchmark <hypotenuse,
			std::valarray <float>,
			stdext::valarray <float>,
			float*> ("hypotenuse");
		
		
		#ifdef HAS_C99_COMPLEX
		benchmark <multiply_add,
			std::valarray <std::complex <float> >,
			stdext::valarray <stdext::complex <float> >,
			float _Complex*> ("complex multiply add");
		#endif
	
		#ifndef _MSC_VER	// Visual C++ ICE's here
		benchmark <predicate,
			std::valarray <float>,
			stdext::valarray <float>,
			float*> ("predicate");
		#endif
		
		
		benchmark <slicing,
			std::valarray <float>,
			stdext::valarray <float>,
			float*> ("slicing");

		benchmark <power,
			std::valarray <float>,
			stdext::valarray <float>,
			float*> ("power");
	
		benchmark <trigonometric,
			std::valarray <float>,
			stdext::valarray <float>,
			float*> ("trigonometric");				
	}
	

	
