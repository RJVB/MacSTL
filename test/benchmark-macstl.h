/*
 *  common.h
 *  macstl
 *
 *  Created by Glen Low on Oct 28 2004.
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

#include <cmath>
#include <iostream>
#include <iomanip>

#include <string.h>

#include <macstl/boolean.h>
#include <macstl/complex.h>

const unsigned int max_difference = 10000000;

// difference

template <typename T> unsigned int difference (const T& left, const T& right)
	{
		return left == right ? 0 : max_difference;
	}

template <typename T> unsigned int difference (const macstl::boolean <T>& left, bool right)
	{
		return left == right ? 0 : max_difference;
	}

unsigned int difference (float left, float right)
	{
		union un
			{
				float f;
				unsigned int i;
			};

		un uleft = {left};
		un uright = {right};

		bool leftnanorinf = (uleft.i & 0x7F800000U) == 0x7F800000;		// exponent all ones => nan or inf
		bool rightnanorinf = (uright.i & 0x7F800000U) == 0x7F800000;
		bool leftnan = uleft.i & 0x7FFFFFU;		// any mantissa bits => nan
		bool rightnan = uright.i & 0x7FFFFFU;

		if (leftnanorinf && rightnanorinf && leftnan && rightnan)	// both are nan
			return 0;
		else if (!((uleft.i ^ uright.i) & 0x80000000U))	// both signs the same
			{
				if (leftnanorinf && rightnanorinf && !leftnan && !rightnan)	// both are inf (of the same sign)
					return 0;
				else
					{
						// both are finite and non-nan, just take the absolute difference of exponent & mantissa as one integer
						unsigned int diff = std::abs (((int) (uleft.i & 0x7FFFFFFFU)) - ((int) (uright.i & 0x7FFFFFFF)));
						if (diff < max_difference)
							return diff;
					}
			}
		return max_difference;
	}

unsigned int difference (double left, double right)
	{
		union un
			{
				double d;
				unsigned long long i;
			};

		un uleft = {left};
		un uright = {right};

		bool leftnanorinf = (uleft.i & 0x7FF0000000000000ULL) == 0x7FF0000000000000ULL;	/// exponent al ones => nan or inf
		bool rightnanorinf = (uright.i & 0x7FF0000000000000ULL) == 0x7FF0000000000000ULL;
		bool leftnan =  uleft.i & 0xFFFFFFFFFFFFFULL;	// any mantissa bits => nan
		bool rightnan = uright.i & 0xFFFFFFFFFFFFFULL;

		if (leftnanorinf && rightnanorinf && leftnan && rightnan)	// both are nan
			return 0;
		else if (!((uleft.i ^ uright.i) & 0x8000000000000000ULL))	// both signs the same
			{
				if (leftnanorinf && rightnanorinf && !leftnan && !rightnan)	// both are inf (of the same sign)
					return 0;
				else
					{
						// both are finite and non-nan, just take the absolute difference of exponent & mantissa as one integer
						unsigned int diff = std::abs ((int) (((long long) (uleft.i & 0x7FFFFFFFFFFFFFFFULL)) -
							((long long) (uright.i & 0x7FFFFFFFFFFFFFFFULL))));
						if (diff < max_difference)
							return diff;
					}
			}

		return max_difference;
	}

unsigned int difference (const stdext::complex <float>& left, const stdext::complex <float>& right)
	{
		return std::max (difference (left.real (), right.real ()), difference (left.imag (), right.imag ()));
	}

unsigned int difference (const stdext::complex <double>& left, const stdext::complex <double>& right)
	{
		return std::max (difference (left.real (), right.real ()), difference (left.imag (), right.imag ()));
	}

// randomize

static unsigned int random_bytes = 2;

unsigned char randch ()
	{
		// random () only returns 2^31 - 1, so we only use the lower 3 bytes
		static unsigned int source = 0;

		#ifdef _MSC_VER
		return rand () & 0xFFU;
		#else

		if (random_bytes == 2)
			{
				random_bytes = 0;
				source = random ();
			}
		else
			{
				++random_bytes;
				source >>= 8;
			}

		return source & 0xFFU;

		#endif
	}

void seed ()
	{
		#ifdef _MSC_VER
		srand (1);
		#else
		srandom (1);
		random_bytes = 2;
		#endif
	}

// validate -- pass through most arguments unmolested

template <template <typename> class Op, typename T> struct validate_lhs
	{
		T operator() (const T& lhs) const
			{
				return lhs;
			}
	};

template <template <typename> class Op, typename T> struct validate_rhs
	{
		T operator() (const T& rhs) const
			{
				return rhs;
			}
	};

template <typename T> struct validate_rhs <std::divides, T>
	{
		T operator() (const T& rhs) const
			{
				return rhs == T () ? T (1) : rhs;	// non-zero second argument, avoid divide by zero
			}
	};

#if !defined(_MSC_VER) && (__GNUC__ < 4)
template <typename T> struct validate_rhs <stdext::shift_left, T>
	{
		T operator() (const T& rhs) const
			{
				return rhs % (sizeof (T) * 8);		// for <<, rhs must be positive and less than width of operand, otherwise undefined
			}
	};

template <typename T> struct validate_rhs <stdext::shift_right, T>
	{
		T operator() (const T& rhs) const
			{
				return rhs % (sizeof (T) * 8);		// for <<, rhs must be positive and less than width of operand, otherwise undefined
			}
	};

template <typename T> struct validate_rhs <stdext::shift_left, macstl::boolean <T> >
	{
		macstl::boolean <T> operator() (const macstl::boolean <T>& rhs) const
			{
				return rhs;
			}
	};

template <typename T> struct validate_rhs <stdext::shift_right, macstl::boolean <T> >
	{
		macstl::boolean <T> operator() (const macstl::boolean <T>& rhs) const
			{
				return rhs;
			}
	};
#endif

float denan (float x)
	{
		if (x == x)
			return x;
		else
			{
				union un
					{
						float f;
						unsigned int i;
					};

				un u = {x};
				u.i &= 0x7F800000U;	// change the NAN into a denormal
				return u.f;
			}
	}


// reduce arguments for trig functions

float reduce (float x)
	{
		using namespace std;
		return (float) fmod ((double) x, pow (2.0, 20.0));
	}

template <> struct validate_lhs <stdext::sine, float>
	{
		float operator () (float lhs) const
			{
				return reduce (lhs);
			}
	};

template <> struct validate_lhs <stdext::cosine, float>
	{
		float operator () (float lhs) const
			{
				return reduce (lhs);
			}
	};

template <> struct validate_lhs <stdext::tangent, float>
	{
		float operator () (float lhs) const
			{
				return reduce (lhs);
			}
	};


template <typename T> struct randomize
	{
		template <typename V> void operator() (V& array, std::size_t n) const
			{
				for (std::size_t i = 0; i != n; ++i)
					{
						T result;
						for (std::size_t j = 0; j < sizeof (T); ++j)
							{
								unsigned char ch = randch ();
								memcpy (((char*) &result) + j, &ch, 1);	// ouch!
							}

						array [i] = result;
					}
			}
	};

template <typename T> struct randomize <macstl::boolean <T> >
	{
		template <typename V> void operator() (V& array, std::size_t n) const
			{
			//	array = V::set (randch () & 1, randch () & 1);
				for (std::size_t i = 0; i != n; ++i)
					array [i] = (bool) (randch () & 1);
			}
	};

// test

template <template <typename> class UOp, typename T> inline void test
	(const char* op, unsigned int& threshold, typename UOp <T>::argument_type* = NULL)
	{
		T lhs;

		randomize <typename T::value_type> () (lhs, T::length);

		for (std::size_t i = 0; i != T::length; ++i)
			lhs [i] = validate_lhs <UOp, typename T::value_type> () (lhs [i]);

		typedef UOp <T> vector_operation;
		typename vector_operation::result_type result = vector_operation () (lhs);

		#if defined(__MMX__) || defined(__SSE__) || defined(__SSE2__)
		macstl::mmx::empty ();	// empty out MMX state after possible use of MMX
		#endif

		for (std::size_t j = 0; j != T::length; ++j)
			{
				typedef UOp <typename T::value_type> scalar_operation;
				typename scalar_operation::result_type r = scalar_operation () (lhs [j]);
				unsigned int diff = difference ((typename vector_operation::result_type::value_type) result [j], r);
				if (diff > threshold)
					{
						std::cout << std::setprecision (30) << "\t\t" << diff << ": " <<
							(typename vector_operation::result_type::value_type) result [j] << " != " << r << " == " << op << " (" <<
							(typename T::value_type) lhs [j] << ").\n";
						threshold = diff;
					}
			}
	}


template <template <typename> class BOp, typename T> inline void test
	(const char* op, unsigned int& threshold, typename BOp <T>::first_argument_type* = NULL)
	{
		T lhs, rhs;

		randomize <typename T::value_type> () (lhs, T::length);
		randomize <typename T::value_type> () (rhs, T::length);
		for (std::size_t i = 0; i != T::length; ++i)
			lhs [i] = validate_lhs <BOp, typename T::value_type> () (lhs [i]);
		for (std::size_t j = 0; j != T::length; ++j)
			rhs [j] = validate_rhs <BOp, typename T::value_type> () (rhs [j]);

		typedef BOp <T> vector_operation;
		typename vector_operation::result_type result = vector_operation () (lhs, rhs);

		#if defined(__MMX__) || defined(__SSE__) || defined(__SSE2__)
		macstl::mmx::empty ();	// empty out MMX state after possible use of MMX
		#endif

		for (std::size_t k = 0; k != T::length; ++k)
			{
				typedef BOp <typename T::value_type> scalar_operation;
				typename scalar_operation::result_type r = scalar_operation () (lhs [k], rhs [k]);
				unsigned int diff = difference ((typename vector_operation::result_type::value_type) result [k], r);
				if (diff > threshold)
					{
						std::cout << std::setprecision (30) << "\t\t" << diff << ": " <<
							(typename vector_operation::result_type::value_type) result [k] << " != " << r << " == " << op << " (" <<
							(typename T::value_type) lhs [k] << ", " <<
							(typename T::value_type) rhs [k] << ").\n";
						threshold = diff;
					}
			}
	}

template <template <typename> class BOp, typename T> inline void test_acc
	(const char* op, unsigned int& threshold)
	{
		T lhs;

		randomize <typename T::value_type> () (lhs, T::length);

		typename T::value_type result = stdext::accumulator <BOp <T> > () (lhs);

		#if defined(__MMX__) || defined(__SSE__) || defined(__SSE2__)
		macstl::mmx::empty ();	// empty out MMX state after possible use of MMX
		#endif

		typename T::value_type accum = lhs [0];
		typedef BOp <typename T::value_type> scalar_operation;
		for (std::size_t i = 1; i != T::length; ++i)
			accum = scalar_operation () (accum, lhs [i]);

		unsigned int diff = difference (accum, result);
		if (diff > threshold)
			{
				std::cout << std::setprecision (30) << "\t\t" << diff << ": " <<
					result << " != " << accum << " == " << op << " (" <<
					lhs << ").\n";
				threshold = diff;
			}
	}
