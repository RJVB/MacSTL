/*!
 *  @file vectest.cpp
 *  macstl
 *
 *  Created by Glen Low on Nov 03 2004.
 *
 *  Copyright (c) 2004-2005 Pixelglow Software, all rights reserved.
 *  http://www.pixelglow.com/macstl/
 *  macstl@pixelglow.com
 */
 /*  Unless explicitly acquired and licensed from Licensor under the Pixelglow
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

#ifdef _MSC_VER
#pragma warning(disable:4146)	// overly pendantic -- I *know* unary minus of unsigned is still unsigned
#pragma warning(disable:4799)	// trust me, I know what I'm doing with EMMS
#endif

#include <iostream>
#include <iomanip>

#include "macstl/vec.h"
#ifdef __AVX__
#	include "macstl/impl/vec_avx.h"
#endif

#include "common.h"

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>
#include "timing.h"
#include "timing.c"

const unsigned int tries = 1000, repeats = 1000;
const unsigned int minthreshold = 5;

template <template <typename> class F, typename T, typename Enable = void> struct test_func
	{
		static void call (const char* name)
			{
				std::cout << "\t" << name << " undefined.\n";
			}
	};

template <template <typename> class F, typename T> struct test_func <F, T,
	typename stdext::impl::enable_if <stdext::impl::exists <typename F <T>::result_type>::value>::type>
	{
		static void call (const char* name)
			{
				std::cout << "\t" << name << " defined:\n";
				unsigned int threshold = minthreshold;
				HRTime_tic();
				for( unsigned int rep = 0 ; rep != repeats ; ++rep )
					for (unsigned int trial = 0; trial != tries; ++trial)
						test <F, T> (name, threshold);
				double toc = HRTime_toc();
				if (threshold == minthreshold)
					std::cout << "\t\t" << name << " OK; ";
				std::cout << tries*repeats << " samples in " << toc << "s == " << tries*repeats/toc << "Hz\n";
			}
	};

template <template <typename, typename> class F, typename T, typename Enable = void> struct test_func2
	{
		static void call (const char* name)
			{
				std::cout << "\t" << name << " undefined.\n";
			}
	};

template <template <typename, typename> class F, typename T> struct test_func2 <F, T,
	typename stdext::impl::enable_if <stdext::impl::exists <typename F <T, T>::result_type>::value>::type>
	{
		static void call (const char* name)
			{
				std::cout << "\t" << name << " defined:\n";
				unsigned int threshold = minthreshold;
				HRTime_tic();
				for( unsigned int rep = 0 ; rep != repeats ; ++rep )
					for (unsigned int trial = 0; trial != tries; ++trial)
						test2 <F, T> (name, threshold);
				double toc = HRTime_toc();
				if (threshold == minthreshold)
					std::cout << "\t\t" << name << " OK; ";
				std::cout << tries*repeats << " samples in " << toc << "s == " << tries*repeats/toc << "Hz\n";
			}
	};

template <template <typename, typename> class F, typename T, typename Enable = void> struct test_accum
	{
		static void call (const char* name)
			{
				std::cout << "\t" << name << " undefined.\n";
			}
	};

template <template <typename, typename> class F, typename T> struct test_accum <F, T,
	typename stdext::impl::enable_if <stdext::impl::exists <typename stdext::accumulator <F <T, T> >::result_type>::value>::type>
	{
		static void call (const char* name)
			{
				std::cout << "\t" << name << " defined:\n";
				unsigned int threshold = minthreshold;
				HRTime_tic();
				for( unsigned int rep = 0 ; rep != repeats ; ++rep )
					for (unsigned int trial = 0; trial != tries; ++trial)
						test_acc <F, T> (name, threshold);
				double toc = HRTime_toc();
				if (threshold == minthreshold)
					std::cout << "\t\t" << name << " OK; ";
				std::cout << tries*repeats << " samples in " << toc << "s == " << tries*repeats/toc << "Hz\n";
			}
	};

template <typename T, typename Enable = void> struct test_type
	{
		static void call (const char* name)
			{
				std::cout << name << " undefined.\n";
			}
	};

template <typename T> struct test_type <T, typename stdext::impl::enable_if <stdext::impl::exists <typename T::value_type>::value>::type>
	{
		static void call (const char* name)
			{
				std::cout << name << " defined:\n";

				test_accum <stdext::plus, T>::call ("sum");
				test_accum <stdext::maximum, T>::call ("max");
				test_accum <stdext::minimum, T>::call ("min");

				test_func <stdext::negate, T>::call ("operator-");
				test_func <stdext::logical_not, T>::call ("operator!");
				test_func2 <stdext::multiplies, T>::call ("operator*");
				test_func2 <stdext::divides, T>::call ("operator/");
				test_func2 <stdext::modulus, T>::call ("operator%");
				test_func2 <stdext::plus, T>::call ("operator+");
				test_func2 <stdext::minus, T>::call ("operator-");
				test_func2 <stdext::equal_to, T>::call ("operator==");
				test_func2 <stdext::not_equal_to, T>::call ("operator!=");
				test_func2 <stdext::less, T>::call ("operator<");
				test_func2 <stdext::greater, T>::call ("operator>");
				test_func2 <stdext::less_equal, T>::call ("operator<=");
				test_func2 <stdext::greater_equal, T>::call ("operator>=");
				test_func2 <stdext::logical_and, T>::call ("operator&&");
				test_func2 <stdext::logical_or, T>::call ("operator||");

				test_func2 <stdext::bitwise_and, T>::call ("operator&");
				test_func <stdext::bitwise_not, T>::call ("operator~");
				test_func2 <stdext::bitwise_or, T>::call ("operator|");
				test_func2 <stdext::bitwise_xor, T>::call ("operator^");
				test_func2 <stdext::shift_left, T>::call ("operator<<");
				test_func2 <stdext::shift_right, T>::call ("operator>>");

				test_func <stdext::absolute, T>::call ("abs");
				test_func <stdext::round, T>::call ("round");
				test_func <stdext::arc_cosine, T>::call ("acos");
				test_func <stdext::arc_sine, T>::call ("asin");
				test_func <stdext::arc_tangent, T>::call ("atan");
				test_func2 <stdext::arc_tangent2, T>::call ("atan2");
				test_func <stdext::cosine, T>::call ("cos");
				test_func <stdext::exponent, T>::call ("exp");
				test_func <stdext::hyperbolic_cosine, T>::call ("cosh");
				test_func <stdext::hyperbolic_sine, T>::call ("sinh");
				test_func <stdext::hyperbolic_tangent, T>::call ("tanh");
				test_func <stdext::logarithm, T>::call ("log");
				test_func2 <stdext::maximum, T>::call ("max");
				test_func2 <stdext::minimum, T>::call ("min");
				test_func2 <stdext::multiplies_high, T>::call ("mulhi");
			//	test_func <stdext::multiplies_plus, T>::call ("fma");
				test_func2 <stdext::power, T>::call ("pow");
				test_func <stdext::sine, T>::call ("sin");
				test_func <stdext::square_root, T>::call ("sqrt");
				test_func <stdext::tangent, T>::call ("tan");

			}
	};

int main (int, char *argv[])
	{
		using namespace macstl;

		init_HRTime();

		#ifdef __VEC__
		altivec::mtvscr (vec <unsigned char, 16>::fill <0> ());	// in Altivec, use more accurate Java mode for testing
		#endif

		test_type <vec <unsigned char, 32> >::call ("vec <unsigned char, 32>");
		test_type <vec <unsigned char, 16> >::call ("vec <unsigned char, 16>");
		test_type <vec <unsigned char, 8> >::call ("vec <unsigned char, 8>");
		test_type <vec <unsigned char, 4> >::call ("vec <unsigned char, 4>");
		test_type <vec <unsigned char, 2> >::call ("vec <unsigned char, 2>");

		std::cout << "---\n";
		test_type <vec <signed char, 32> >::call ("vec <signed char, 32>");
		test_type <vec <signed char, 16> >::call ("vec <signed char, 16>");
		test_type <vec <signed char, 8> >::call ("vec <signed char, 8>");
		test_type <vec <signed char, 4> >::call ("vec <signed char, 4>");
		test_type <vec <signed char, 2> >::call ("vec <signed char, 2>");

		std::cout << "---\n";
		test_type <vec <boolean <char>, 32> >::call ("vec <boolean <char>, 32>");
		test_type <vec <boolean <char>, 16> >::call ("vec <boolean <char>, 16>");
		test_type <vec <boolean <char>, 8> >::call ("vec <boolean <char>, 8>");
		test_type <vec <boolean <char>, 4> >::call ("vec <boolean <char>, 4>");
		test_type <vec <boolean <char>, 2> >::call ("vec <boolean <char>, 2>");

		std::cout << "---\n";
		test_type <vec <unsigned short, 32> >::call ("vec <unsigned short, 32>");
		test_type <vec <unsigned short, 16> >::call ("vec <unsigned short, 16>");
		test_type <vec <unsigned short, 8> >::call ("vec <unsigned short, 8>");
		test_type <vec <unsigned short, 4> >::call ("vec <unsigned short, 4>");
		test_type <vec <unsigned short, 2> >::call ("vec <unsigned short, 2>");

		std::cout << "---\n";
		test_type <vec <short, 32> >::call ("vec <short, 32>");
		test_type <vec <short, 16> >::call ("vec <short, 16>");
		test_type <vec <short, 8> >::call ("vec <short, 8>");
		test_type <vec <short, 4> >::call ("vec <short, 4>");
		test_type <vec <short, 2> >::call ("vec <short, 2>");

		std::cout << "---\n";
		test_type <vec <boolean <short>, 32> >::call ("vec <boolean <short>, 32>");
		test_type <vec <boolean <short>, 16> >::call ("vec <boolean <short>, 16>");
		test_type <vec <boolean <short>, 8> >::call ("vec <boolean <short>, 8>");
		test_type <vec <boolean <short>, 4> >::call ("vec <boolean <short>, 4>");
		test_type <vec <boolean <short>, 2> >::call ("vec <boolean <short>, 2>");

		std::cout << "---\n";
		test_type <vec <unsigned int, 32> >::call ("vec <unsigned int, 32>");
		test_type <vec <unsigned int, 16> >::call ("vec <unsigned int, 16>");
		test_type <vec <unsigned int, 8> >::call ("vec <unsigned int, 8>");
		test_type <vec <unsigned int, 4> >::call ("vec <unsigned int, 4>");
		test_type <vec <unsigned int, 2> >::call ("vec <unsigned int, 2>");

		std::cout << "---\n";
		test_type <vec <int, 32> >::call ("vec <int, 32>");
		test_type <vec <int, 16> >::call ("vec <int, 16>");
		test_type <vec <int, 8> >::call ("vec <int, 8>");
		test_type <vec <int, 4> >::call ("vec <int, 4>");
		test_type <vec <int, 2> >::call ("vec <int, 2>");

		std::cout << "---\n";
		test_type <vec <boolean <int>, 32> >::call ("vec <boolean <int>, 32>");
		test_type <vec <boolean <int>, 16> >::call ("vec <boolean <int>, 16>");
		test_type <vec <boolean <int>, 8> >::call ("vec <boolean <int>, 8>");
		test_type <vec <boolean <int>, 4> >::call ("vec <boolean <int>, 4>");
		test_type <vec <boolean <int>, 2> >::call ("vec <boolean <int>, 2>");

		std::cout << "---\n";
		test_type <vec <unsigned long long, 32> >::call ("vec <unsigned long long, 32>");
		test_type <vec <unsigned long long, 16> >::call ("vec <unsigned long long, 16>");
		test_type <vec <unsigned long long, 8> >::call ("vec <unsigned long long, 8>");
		test_type <vec <unsigned long long, 4> >::call ("vec <unsigned long long, 4>");
		test_type <vec <unsigned long long, 2> >::call ("vec <unsigned long long, 2>");

		std::cout << "---\n";
		test_type <vec <long long, 32> >::call ("vec <long long, 32>");
		test_type <vec <long long, 16> >::call ("vec <long long, 16>");
		test_type <vec <long long, 8> >::call ("vec <long long, 8>");
		test_type <vec <long long, 4> >::call ("vec <long long, 4>");
		test_type <vec <long long, 2> >::call ("vec <long long, 2>");

		std::cout << "---\n";
		test_type <vec <boolean <long long>, 32> >::call ("vec <boolean <long long>, 32>");
		test_type <vec <boolean <long long>, 16> >::call ("vec <boolean <long long>, 16>");
		test_type <vec <boolean <long long>, 8> >::call ("vec <boolean <long long>, 8>");
		test_type <vec <boolean <long long>, 4> >::call ("vec <boolean <long long>, 4>");
		test_type <vec <boolean <long long>, 2> >::call ("vec <boolean <long long>, 2>");

		std::cout << "---\n";
		test_type <vec <float, 32> >::call ("vec <float, 32>");
		test_type <vec <float, 16> >::call ("vec <float, 16>");
		test_type <vec <float, 8> >::call ("vec <float, 8>");
		test_type <vec <float, 4> >::call ("vec <float, 4>");
		test_type <vec <float, 2> >::call ("vec <float, 2>");


		#ifdef HAS_C99_COMPLEX
		std::cout << "---\n";
		test_type <vec <stdext::complex <float>, 32> >::call ("vec <stdext::complex <float>, 32>");
		test_type <vec <stdext::complex <float>, 16> >::call ("vec <stdext::complex <float>, 16>");
		test_type <vec <stdext::complex <float>, 8> >::call ("vec <stdext::complex <float>, 8>");
		test_type <vec <stdext::complex <float>, 4> >::call ("vec <stdext::complex <float>, 4>");
		test_type <vec <stdext::complex <float>, 2> >::call ("vec <stdext::complex <float>, 2>");
		#endif

		std::cout << "---\n";
		test_type <vec <boolean <float>, 32> >::call ("vec <boolean <float>, 32>");
		test_type <vec <boolean <float>, 16> >::call ("vec <boolean <float>, 16>");
		test_type <vec <boolean <float>, 8> >::call ("vec <boolean <float>, 8>");
		test_type <vec <boolean <float>, 4> >::call ("vec <boolean <float>, 4>");
		test_type <vec <boolean <float>, 2> >::call ("vec <boolean <float>, 2>");

		std::cout << "---\n";
		test_type <vec <double, 32> >::call ("vec <double, 32>");
		test_type <vec <double, 16> >::call ("vec <double, 16>");
		test_type <vec <double, 8> >::call ("vec <double, 8>");
		test_type <vec <double, 4> >::call ("vec <double, 4>");
		test_type <vec <double, 2> >::call ("vec <double, 2>");

		#ifdef HAS_C99_COMPLEX
		std::cout << "---\n";
		test_type <vec <stdext::complex <double>, 32> >::call ("vec <stdext::complex <double>, 32>");
		test_type <vec <stdext::complex <double>, 16> >::call ("vec <stdext::complex <double>, 16>");
		test_type <vec <stdext::complex <double>, 8> >::call ("vec <stdext::complex <double>, 8>");
		test_type <vec <stdext::complex <double>, 4> >::call ("vec <stdext::complex <double>, 4>");
		test_type <vec <stdext::complex <double>, 2> >::call ("vec <stdext::complex <double>, 2>");
		#endif

		std::cout << "---\n";
		test_type <vec <boolean <double>, 32> >::call ("vec <boolean <double>, 32>");
		test_type <vec <boolean <double>, 16> >::call ("vec <boolean <double>, 16>");
		test_type <vec <boolean <double>, 8> >::call ("vec <boolean <double>, 8>");
		test_type <vec <boolean <double>, 4> >::call ("vec <boolean <double>, 4>");
		test_type <vec <boolean <double>, 2> >::call ("vec <boolean <double>, 2>");
	}
