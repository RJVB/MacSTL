/*!
 *  @file vec_avx.h
 *  macstl
 *
 *  Created by René J.V. Bertin on 20131202
 *  from vec_mmx.h, Created by Glen Low on Oct 29 2004.
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

#ifndef MACSTL_IMPL_VEC_AVX_H
#define MACSTL_IMPL_VEC_AVX_H

#ifdef __MMX__
#include <mmintrin.h>
#endif

#ifdef __SSE__
#include <xmmintrin.h>
#endif

#ifdef __SSE2__
#include <emmintrin.h>
#endif

#ifdef __SSE3__
#include <pmmintrin.h>
#endif

#ifdef __SSSE3__
#include <tmmintrin.h>
#endif

#if defined(__SSE4__) || defined(__SSE4_1__)
#include <smmintrin.h>
#endif

#ifdef __SSE4_2__
#include <nmmintrin.h>
#endif

#if defined(__AVX__) || defined(__AVX2__)
#	include <immintrin.h>
#	warning "vec_avx.h"
#else
#	error "including vec_avx.h without __AVX__ or __AVX2__!"
#endif

namespace stdext
	{
		// accumulator <maximum>

		#if defined(__MMX__) && defined(__SSE__)

		template <> struct accumulator <maximum <macstl::vec <macstl::boolean <char>, 8>, macstl::vec <macstl::boolean <char>, 8> > >
			{
				typedef macstl::vec <macstl::boolean <char>, 8> argument_type;
				typedef macstl::boolean <char> result_type;

				const result_type operator() (const argument_type& lhs) const;
			};

		template <> struct accumulator <maximum <macstl::vec <unsigned short, 4>, macstl::vec <unsigned short, 4> > >
			{
				typedef macstl::vec <unsigned short, 4> argument_type;
				typedef unsigned short result_type;

				result_type operator() (const argument_type& lhs) const;
			};

		template <> struct accumulator <maximum <macstl::vec <short, 4>, macstl::vec <short, 4> > >
			{
				typedef macstl::vec <short, 4> argument_type;
				typedef short result_type;

				result_type operator() (const argument_type& lhs) const;
			};

		#endif

		template <> struct accumulator <maximum <macstl::vec <float, 4>, macstl::vec <float, 4> > >
			{
				typedef macstl::vec <float, 4> argument_type;
				typedef float result_type;

				result_type operator() (const argument_type& lhs) const;
			};

		template <> struct accumulator <maximum <macstl::vec <macstl::boolean <float>, 4>, macstl::vec <macstl::boolean <float>, 4> > >
			{
				typedef macstl::vec <macstl::boolean <float>, 4> argument_type;
				typedef macstl::boolean <float> result_type;

				const result_type operator() (const argument_type& lhs) const;
			};

		template <> struct accumulator <maximum <macstl::vec <float, 8>, macstl::vec <float, 8> > >
			{
				typedef macstl::vec <float, 8> argument_type;
				typedef float result_type;

				result_type operator() (const argument_type& lhs) const;
			};

		template <> struct accumulator <maximum <macstl::vec <macstl::boolean <float>, 8>, macstl::vec <macstl::boolean <float>, 8> > >
			{
				typedef macstl::vec <macstl::boolean <float>, 8> argument_type;
				typedef macstl::boolean <float> result_type;

				const result_type operator() (const argument_type& lhs) const;
			};

		template <> struct accumulator <maximum <macstl::vec <double, 2>, macstl::vec <double, 2> > >
			{
				typedef macstl::vec <double, 2> argument_type;
				typedef double result_type;

				result_type operator() (const argument_type& lhs) const;
			};

		template <> struct accumulator <maximum <macstl::vec <macstl::boolean <double>, 2>, macstl::vec <macstl::boolean <double>, 2> > >
			{
				typedef macstl::vec <macstl::boolean <double>, 2> argument_type;
				typedef macstl::boolean <double> result_type;

				const result_type operator() (const argument_type& lhs) const;
			};

		template <> struct accumulator <maximum <macstl::vec <double, 4>, macstl::vec <double, 4> > >
			{
				typedef macstl::vec <double, 4> argument_type;
				typedef double result_type;

				result_type operator() (const argument_type& lhs) const;
			};

		template <> struct accumulator <maximum <macstl::vec <macstl::boolean <double>, 4>, macstl::vec <macstl::boolean <double>, 4> > >
			{
				typedef macstl::vec <macstl::boolean <double>, 4> argument_type;
				typedef macstl::boolean <double> result_type;

				const result_type operator() (const argument_type& lhs) const;
			};

		template <> struct accumulator <maximum <macstl::vec <macstl::boolean <char>, 16>, macstl::vec <macstl::boolean <char>, 16> > >
			{
				typedef macstl::vec <macstl::boolean <char>, 16> argument_type;
				typedef macstl::boolean <char> result_type;

				const result_type operator() (const argument_type& lhs) const;
			};

		// accumulator <minimum>

		#if defined(__MMX__) && defined(__SSE__)

		template <> struct accumulator <minimum <macstl::vec <macstl::boolean <char>, 8>, macstl::vec <macstl::boolean <char>, 8> > >
			{
				typedef macstl::vec <macstl::boolean <char>, 8> argument_type;
				typedef macstl::boolean <char> result_type;

				const result_type operator() (const argument_type& lhs) const;
			};

		template <> struct accumulator <minimum <macstl::vec <unsigned short, 4>, macstl::vec <unsigned short, 4> > >
			{
				typedef macstl::vec <unsigned short, 4> argument_type;
				typedef unsigned short result_type;

				result_type operator() (const argument_type& lhs) const;
			};

		template <> struct accumulator <minimum <macstl::vec <short, 4>, macstl::vec <short, 4> > >
			{
				typedef macstl::vec <short, 4> argument_type;
				typedef short result_type;

				result_type operator() (const argument_type& lhs) const;
			};

		#endif

		template <> struct accumulator <minimum <macstl::vec <float, 4>, macstl::vec <float, 4> > >
			{
				typedef macstl::vec <float, 4> argument_type;
				typedef float result_type;

				result_type operator() (const argument_type& lhs) const;
			};

		template <> struct accumulator <minimum <macstl::vec <macstl::boolean <float>, 4>, macstl::vec <macstl::boolean <float>, 4> > >
			{
				typedef macstl::vec <macstl::boolean <float>, 4> argument_type;
				typedef macstl::boolean <float> result_type;

				const result_type operator() (const argument_type& lhs) const;
			};

		template <> struct accumulator <minimum <macstl::vec <float, 8>, macstl::vec <float, 8> > >
			{
				typedef macstl::vec <float, 8> argument_type;
				typedef float result_type;

				result_type operator() (const argument_type& lhs) const;
			};

		template <> struct accumulator <minimum <macstl::vec <macstl::boolean <float>, 8>, macstl::vec <macstl::boolean <float>, 8> > >
			{
				typedef macstl::vec <macstl::boolean <float>, 8> argument_type;
				typedef macstl::boolean <float> result_type;

				const result_type operator() (const argument_type& lhs) const;
			};

		template <> struct accumulator <minimum <macstl::vec <double, 2>, macstl::vec <double, 2> > >
			{
				typedef macstl::vec <double, 2> argument_type;
				typedef double result_type;

				result_type operator() (const argument_type& lhs) const;
			};

		template <> struct accumulator <minimum <macstl::vec <macstl::boolean <double>, 2>, macstl::vec <macstl::boolean <double>, 2> > >
			{
				typedef macstl::vec <macstl::boolean <double>, 2> argument_type;
				typedef macstl::boolean <double> result_type;

				const result_type operator() (const argument_type& lhs) const;
			};

		template <> struct accumulator <minimum <macstl::vec <double, 4>, macstl::vec <double, 4> > >
			{
				typedef macstl::vec <double, 4> argument_type;
				typedef double result_type;

				result_type operator() (const argument_type& lhs) const;
			};

		template <> struct accumulator <minimum <macstl::vec <macstl::boolean <double>, 4>, macstl::vec <macstl::boolean <double>, 4> > >
			{
				typedef macstl::vec <macstl::boolean <double>, 4> argument_type;
				typedef macstl::boolean <double> result_type;

				const result_type operator() (const argument_type& lhs) const;
			};

		template <> struct accumulator <minimum <macstl::vec <macstl::boolean <char>, 16>, macstl::vec <macstl::boolean <char>, 16> > >
			{
				typedef macstl::vec <macstl::boolean <char>, 16> argument_type;
				typedef macstl::boolean <char> result_type;

				const result_type operator() (const argument_type& lhs) const;
			};

		// accumulator <plus>

		#if defined(__MMX__) && defined(__SSE__)

		template <> struct accumulator <plus <macstl::vec <unsigned short, 4>, macstl::vec <unsigned short, 4> > >
			{
				typedef macstl::vec <unsigned short, 4> argument_type;
				typedef unsigned short result_type;

				result_type operator() (const argument_type& lhs) const;
			};

		template <> struct accumulator <plus <macstl::vec <short, 4>, macstl::vec <short, 4> > >
			{
				typedef macstl::vec <short, 4> argument_type;
				typedef short result_type;

				result_type operator() (const argument_type& lhs) const;
			};

		#endif

		template <> struct accumulator <plus <macstl::vec <float, 4>, macstl::vec <float, 4> > >
			{
				typedef macstl::vec <float, 4> argument_type;
				typedef float result_type;

				result_type operator() (const argument_type& lhs) const;
			};

		template <> struct accumulator <plus <macstl::vec <float, 8>, macstl::vec <float, 8> > >
			{
				typedef macstl::vec <float, 8> argument_type;
				typedef float result_type;

				result_type operator() (const argument_type& lhs) const;
			};

		template <> struct accumulator <plus <macstl::vec <double, 2>, macstl::vec <double, 2> > >
			{
				typedef macstl::vec <double, 2> argument_type;
				typedef double result_type;

				result_type operator() (const argument_type& lhs) const;
			};

		template <> struct accumulator <plus <macstl::vec <double, 4>, macstl::vec <double, 4> > >
			{
				typedef macstl::vec <double, 4> argument_type;
				typedef double result_type;

				result_type operator() (const argument_type& lhs) const;
			};

		template <> struct accumulator <plus <macstl::vec <unsigned int, 4>, macstl::vec <unsigned int, 4> > >
			{
				typedef macstl::vec <unsigned int, 4> argument_type;
				typedef unsigned int result_type;

				result_type operator() (const argument_type& lhs) const;
			};

		template <> struct accumulator <plus <macstl::vec <int, 4>, macstl::vec <int, 4> > >
			{
				typedef macstl::vec <int, 4> argument_type;
				typedef int result_type;

				result_type operator() (const argument_type& lhs) const;
			};

		template <> struct accumulator <plus <macstl::vec <int, 8>, macstl::vec <int, 8> > >
			{
				typedef macstl::vec <int, 8> argument_type;
				typedef int result_type;

				result_type operator() (const argument_type& lhs) const;
			};
	}

namespace macstl
	{
		namespace impl
			{
				#ifdef __MMX__

				template <> struct data_vec <__m64>		{ typedef vec <int, 2> type; };

				template <unsigned int v0, unsigned int v1> struct generator_m64
					{
						static INLINE __m64 call ()
							{
								union union_type
									{
										unsigned int val [2];
										__m64 vec;
									};

								static const union_type un = {v0, v1};
								return un.vec;
							}
					};

				template <> struct generator_m64 <0, 0>
					{
						static INLINE __m64 call ()
							{
								return _mm_setzero_si64 ();
							}
					};

				#endif

				template <> struct data_vec <__m128>	{ typedef vec <float, 4> type; };
				template <> struct data_vec <__m256>	{ typedef vec <float, 8> type; };

				template <unsigned int v0, unsigned int v1, unsigned int v2, unsigned int v3> struct generator_m128
					{
						static INLINE __m128 call ()
							{
								union union_type
									{
										unsigned int val [4];
										__m128 vec;
									};

								static const union_type un = {v0, v1, v2, v3};
								return un.vec;
							}
					};

				template <> struct generator_m128 <0, 0, 0, 0>
					{
						static INLINE __m128 call ()
							{
								return _mm_setzero_ps ();
							}
					};

				template <unsigned int v0, unsigned int v1, unsigned int v2, unsigned int v3,
					unsigned int v4, unsigned int v5, unsigned int v6, unsigned int v7> struct generator_m256
					{
						static INLINE __m256 call ()
							{
								union union_type
									{
										unsigned int val [8];
										__m256 vec;
									};

								static const union_type un = {v0, v1, v2, v3, v4, v5, v6, v7};
								return un.vec;
							}
					};

				template <> struct generator_m256 <0, 0, 0, 0, 0, 0, 0, 0>
					{
						static INLINE __m256 call ()
							{
								return _mm256_setzero_ps ();
							}
					};

				template <> struct data_vec <__m128d>	{ typedef vec <double, 2> type; };
				template <> struct data_vec <__m256d>	{ typedef vec <double, 4> type; };
				template <> struct data_vec <__m128i>	{ typedef vec <int, 4> type; };
				template <> struct data_vec <__m256i>	{ typedef vec <int, 8> type; };

				template <unsigned int v0, unsigned int v1, unsigned int v2, unsigned int v3> struct generator_m128d
					{
						static INLINE __m128d call ()
							{
								union union_type
									{
										unsigned int val [4];
										__m128d vec;
									};

								static const union_type un = {v0, v1, v2, v3};
								return un.vec;
							}
					};

				template <> struct generator_m128d <0, 0, 0, 0>
					{
						static INLINE __m128d call ()
							{
								return _mm_setzero_pd ();
							}
					};

				template <unsigned int v0, unsigned int v1, unsigned int v2, unsigned int v3,
					unsigned int v4, unsigned int v5, unsigned int v6, unsigned int v7> struct generator_m256d
					{
						static INLINE __m256d call ()
							{
								union union_type
									{
										unsigned int val [8];
										__m256d vec;
									};

								static const union_type un = {v0, v1, v2, v3, v4, v5, v6, v7};
								return un.vec;
							}
					};

				template <> struct generator_m256d <0, 0, 0, 0, 0, 0, 0, 0>
					{
						static INLINE __m256d call ()
							{
								return _mm256_setzero_pd ();
							}
					};

				template <unsigned int v0, unsigned int v1, unsigned int v2, unsigned int v3> struct generator_m128i
					{
						static INLINE __m128i call ()
							{
								union union_type
									{
										unsigned int val [4];
										__m128i vec;
									};

								static const union_type un = {v0, v1, v2, v3};
								return un.vec;
							}
					};

				template <> struct generator_m128i <0, 0, 0, 0>
					{
						static INLINE __m128i call ()
							{
								return _mm_setzero_si128 ();
							}
					};

				template <unsigned int v0, unsigned int v1, unsigned int v2, unsigned int v3,
					unsigned int v4, unsigned int v5, unsigned int v6, unsigned int v7> struct generator_m256i
					{
						static INLINE __m256i call ()
							{
								union union_type
									{
										unsigned int val [8];
										__m256i vec;
									};

								static const union_type un = {v0, v1, v2, v3, v4, v5, v6, v7};
								return un.vec;
							}
					};

				template <> struct generator_m256i <0, 0, 0, 0, 0, 0, 0, 0>
					{
						static INLINE __m256i call ()
							{
								return _mm256_setzero_si256 ();
							}
					};


			}

		#ifndef DOXYGEN

		#ifdef __MMX__

		template <> class vec <unsigned char, 8>
			{
				DEFINE_VEC_CLASS_GUTS(__m64,unsigned char,boolean <char>)

				public:
					typedef unsigned char init_type;

					union union_type
						{
							unsigned char val [8];
							data_type vec;
						};

					static INLINE const vec set (
						value_type v0, value_type v1, value_type v2, value_type v3,
						value_type v4, value_type v5, value_type v6, value_type v7)
						{
							return _mm_setr_pi8 (v0, v1, v2, v3, v4, v5, v6, v7);
						}

					static INLINE const vec fill (
						value_type v0)
						{
							return _mm_set1_pi8 (v0);
						}

					template <
						init_type v0, init_type v1, init_type v2, init_type v3,
						init_type v4, init_type v5, init_type v6, init_type v7>
						static INLINE const vec <unsigned char, 8> set ()
						{
							return impl::generator_m64 <
								(v3 << 24) | (v2 << 16) | (v1 << 8) | v0,
								(v7 << 24) | (v6 << 16) | (v5 << 8) | v4>::call ();
						}

					template <init_type v0>
						static INLINE const vec <unsigned char, 8> fill ()
						{
							return set <v0, v0, v0, v0, v0, v0, v0, v0> ();
						}

					INLINE vec (): data_ (impl::generator_m64 <0, 0>::call ())
						{
						}
			};

		template <> class vec <signed char, 8>
			{
				DEFINE_VEC_CLASS_GUTS(__m64,signed char,boolean <char>)

				public:
					typedef signed char init_type;

					union union_type
						{
							signed char val [8];
							data_type vec;
						};

					static INLINE const vec set (
						value_type v0, value_type v1, value_type v2, value_type v3,
						value_type v4, value_type v5, value_type v6, value_type v7)
						{
							return _mm_setr_pi8 (v0, v1, v2, v3, v4, v5, v6, v7);
						}

					static INLINE const vec fill (
						value_type v0)
						{
							return _mm_set1_pi8 (v0);
						}

					template <
						init_type v0, init_type v1, init_type v2, init_type v3,
						init_type v4, init_type v5, init_type v6, init_type v7>
						static INLINE const vec <signed char, 8> set ()
						{
							return impl::generator_m64 <
								(((unsigned char) v3) << 24) | (((unsigned char) v2) << 16) | (((unsigned char) v1) << 8) | ((unsigned char) v0),
								(((unsigned char) v7) << 24) | (((unsigned char) v6) << 16) | (((unsigned char) v5) << 8) | ((unsigned char) v4)>::call ();
						}

					template <init_type v0>
						static INLINE const vec <signed char, 8> fill ()
						{
							return set <v0, v0, v0, v0, v0, v0, v0, v0> ();
						}

					INLINE vec (): data_ (impl::generator_m64 <0, 0>::call ())
						{
						}
			};

		template <> class vec <boolean <char>, 8>
			{
				DEFINE_VEC_CLASS_GUTS(__m64,boolean <char>,boolean <char>)

				public:
					typedef bool init_type;

					union union_type
						{
							unsigned char val [8];
							data_type vec;
						};

					static INLINE const vec set (
						value_type v0, value_type v1, value_type v2, value_type v3,
						value_type v4, value_type v5, value_type v6, value_type v7)
						{
							return _mm_setr_pi8 (
								v0.data (), v1.data (), v2.data (), v3.data (),
								v4.data (), v5.data (), v6.data (), v7.data ());
						}

					static INLINE const vec fill (
						value_type v0)
						{
							return _mm_set1_pi8 (v0.data ());
						}

					template <
						init_type v0, init_type v1, init_type v2, init_type v3,
						init_type v4, init_type v5, init_type v6, init_type v7>
						static INLINE const vec <boolean <char>, 8> set ()
						{
							return impl::generator_m64 <
								(v3 ? 0xFF000000U : 0) | (v2 ? 0x00FF0000U : 0) | (v1 ? 0x0000FF00U : 0) | (v0 ? 0x000000FFU : 0),
								(v7 ? 0xFF000000U : 0) | (v6 ? 0x00FF0000U : 0) | (v5 ? 0x0000FF00U : 0) | (v4 ? 0x000000FFU : 0)>::call ();
						}

					template <init_type v0>
						static INLINE const vec <boolean <char>, 8> fill ()
						{
							return set <v0, v0, v0, v0, v0, v0, v0, v0> ();
						}

					INLINE vec (): data_ (impl::generator_m64 <0, 0>::call ())
						{
						}

					#ifdef __SSE__
					INLINE const value_type min () const	{ return stdext::accumulator <stdext::minimum <vec> > () (*this); }
					INLINE const value_type max () const	{ return stdext::accumulator <stdext::maximum <vec> > () (*this); }
					#endif
			};

		template <> class vec <unsigned short, 4>
			{
				DEFINE_VEC_CLASS_GUTS(__m64,unsigned short,boolean <short>)

				public:
					typedef unsigned short init_type;

					union union_type
						{
							unsigned short val [4];
							data_type vec;
						};

					static INLINE const vec set (
						value_type v0, value_type v1, value_type v2, value_type v3)
						{
							return _mm_setr_pi16 (v0, v1, v2, v3);
						}

					static INLINE const vec fill (
						value_type v0)
						{
							return _mm_set1_pi16 (v0);
						}

					template <
						init_type v0, init_type v1, init_type v2, init_type v3>
						static INLINE const vec <unsigned short, 4> set ()
						{
							return impl::generator_m64 <
								(v1 << 16) | v0, (v3 << 16) | v2>::call ();
						}

					template <init_type v0>
						static INLINE const vec <unsigned short, 4> fill ()
						{
							return set <v0, v0, v0, v0> ();
						}

					INLINE vec (): data_ (impl::generator_m64 <0, 0>::call ())
						{
						}

					#ifdef __SSE__
					INLINE const value_type max () const	{ return stdext::accumulator <stdext::maximum <vec> > () (*this); }
					INLINE const value_type min () const	{ return stdext::accumulator <stdext::minimum <vec> > () (*this); }
					INLINE const value_type sum () const	{ return stdext::accumulator <stdext::plus <vec> > () (*this); }
					#endif
			};

		template <> class vec <short, 4>
			{
				DEFINE_VEC_CLASS_GUTS(__m64,short,boolean <short>)

				public:
					typedef short init_type;

					union union_type
						{
							short val [4];
							data_type vec;
						};

					static INLINE const vec set (
						value_type v0, value_type v1, value_type v2, value_type v3)
						{
							return _mm_setr_pi16 (v0, v1, v2, v3);
						}

					static INLINE const vec fill (
						value_type v0)
						{
							return _mm_set1_pi16 (v0);
						}

					template <
						init_type v0, init_type v1, init_type v2, init_type v3>
						static INLINE const vec <short, 4> set ()
						{
							return impl::generator_m64 <
								(((unsigned short) v1) << 16) | ((unsigned short) v0), (((unsigned short) v3) << 16) | ((unsigned short) v2)>::call ();
						}

					template <init_type v0>
						static INLINE const vec <short, 4> fill ()
						{
							return set <v0, v0, v0, v0> ();
						}

					INLINE vec (): data_ (impl::generator_m64 <0, 0>::call ())
						{
						}

					#ifdef __SSE__
					INLINE const value_type max () const	{ return stdext::accumulator <stdext::maximum <vec> > () (*this); }
					INLINE const value_type min () const	{ return stdext::accumulator <stdext::minimum <vec> > () (*this); }
					INLINE const value_type sum () const	{ return stdext::accumulator <stdext::plus <vec> > () (*this); }
					#endif
			};

		template <> class vec <boolean <short>, 4>
			{
				DEFINE_VEC_CLASS_GUTS(__m64,boolean <short>,boolean <short>)

				public:
					typedef bool init_type;

					union union_type
						{
							unsigned short val [4];
							data_type vec;
						};

					static INLINE const vec set (
						value_type v0, value_type v1, value_type v2, value_type v3)
						{
							return _mm_setr_pi16 (
								v0.data (), v1.data (), v2.data (), v3.data ());
						}

					static INLINE const vec fill (
						value_type v0)
						{
							return _mm_set1_pi16 (v0.data ());
						}

					template <
						init_type v0, init_type v1, init_type v2, init_type v3>
						static INLINE const vec <boolean <short>, 4> set ()
						{
							return impl::generator_m64 <
								(v1 ? 0xFFFF0000U : 0) | (v0 ? 0x0000FFFFU : 0), (v3 ? 0xFFFF0000U : 0) | (v2 ? 0x0000FFFFU : 0)>::call ();
						}

					template <init_type v0>
						static INLINE const vec <boolean <short>, 4> fill ()
						{
							return set <v0, v0, v0, v0> ();
						}

					INLINE vec (): data_ (impl::generator_m64 <0, 0>::call ())
						{
						}
			};

		template <> class vec <unsigned int, 2>
			{
				DEFINE_VEC_CLASS_GUTS(__m64,unsigned int,boolean <int>)

				public:
					typedef unsigned int init_type;

					union union_type
						{
							unsigned int val [2];
							data_type vec;
						};

					static INLINE const vec set (
						value_type v0, value_type v1)
						{
							return _mm_setr_pi32 (v0, v1);
						}

					static INLINE const vec fill (
						value_type v0)
						{
							return _mm_set1_pi32 (v0);
						}

					template <
						init_type v0, init_type v1>
						static INLINE const vec <unsigned int, 2> set ()
						{
							return impl::generator_m64 <v0, v1>::call ();
						}

					template <init_type v0>
						static INLINE const vec <unsigned int, 2> fill ()
						{
							return set <v0, v0> ();
						}

					INLINE vec (): data_ (impl::generator_m64 <0, 0>::call ())
						{
						}
			};

		template <> class vec <int, 2>
			{
				DEFINE_VEC_CLASS_GUTS(__m64,int,boolean <int>)

				public:
					typedef int init_type;

					union union_type
						{
							int val [2];
							data_type vec;
						};

					static INLINE const vec set (
						value_type v0, value_type v1)
						{
							return _mm_setr_pi32 (v0, v1);
						}

					static INLINE const vec fill (
						value_type v0)
						{
							return _mm_set1_pi32 (v0);
						}

					template <
						init_type v0, init_type v1>
						static INLINE const vec <int, 2> set ()
						{
							return impl::generator_m64 <(int) v0, (int) v1>::call ();
						}

					template <init_type v0>
						static INLINE const vec <int, 2> fill ()
						{
							return set <v0, v0> ();
						}

					INLINE vec (): data_ (impl::generator_m64 <0, 0>::call ())
						{
						}
			};

		template <> class vec <boolean <int>, 2>
			{
				DEFINE_VEC_CLASS_GUTS(__m64,boolean <int>,boolean <int>)

				public:
					typedef bool init_type;

					union union_type
						{
							int val [2];
							data_type vec;
						};

					static INLINE const vec set (
						value_type v0, value_type v1)
						{
							return _mm_setr_pi32 (
								v0.data (), v1.data ());
						}

					static INLINE const vec fill (
						value_type v0)
						{
							return _mm_set1_pi32 (v0.data ());
						}

					template <
						init_type v0, init_type v1>
						static INLINE const vec <boolean <int>, 2> set ()
						{
							return impl::generator_m64 <v0 ? 0xFFFFFFFFU : 0, v1 ? 0xFFFFFFFFU : 0>::call ();
						}

					template <init_type v0>
						static INLINE const vec <boolean <int>, 2> fill ()
						{
							return set <v0, v0> ();
						}

					INLINE vec (): data_ (impl::generator_m64 <0, 0>::call ())
						{
						}
			};

		#endif // MMX

		template <> class vec <float, 4>
			{
				DEFINE_VEC_CLASS_GUTS(__m128,float,boolean <float>)

				public:
					typedef unsigned int init_type;

					union union_type
						{
							float val [4];
							data_type vec;
						};

					static INLINE const vec set (
						value_type v0, value_type v1, value_type v2, value_type v3)
						{
							return _mm_setr_ps (v0, v1, v2, v3);
						}

					static INLINE const vec fill (
						value_type v0)
						{
							return _mm_set1_ps (v0);
						}

					template <
						init_type v0, init_type v1, init_type v2, init_type v3>
						static INLINE const vec <float, 4> set ()
						{
							return impl::generator_m128 <v0, v1, v2, v3>::call ();
						}

					template <init_type v0>
						static INLINE const vec <float, 4> fill ()
						{
							return set <v0, v0, v0, v0> ();
						}

					static INLINE const vec <float, 4> load (const value_data* address, std::ptrdiff_t offset)
						{
							return _mm_load_ps (address + offset * length);
						}

					INLINE void store (value_data* address, std::ptrdiff_t offset) const
						{
							_mm_store_ps (address + offset * length, data_);
						}

					INLINE vec (): data_ (impl::generator_m128 <0, 0, 0, 0>::call ())
						{
						}

					INLINE const value_type max () const	{ return stdext::accumulator <stdext::maximum <vec> > () (*this); }
					INLINE const value_type min () const	{ return stdext::accumulator <stdext::minimum <vec> > () (*this); }
					INLINE const value_type sum () const	{ return stdext::accumulator <stdext::plus <vec> > () (*this); }
			};

		template <> class vec <boolean <float>, 4>
			{
				DEFINE_VEC_CLASS_GUTS(__m128,boolean <float>,boolean <float>)

				public:
					typedef bool init_type;

					union union_type
						{
							float val [4];
							data_type vec;
						};

					static INLINE const vec set (
						value_type v0, value_type v1, value_type v2, value_type v3)
						{
							return _mm_setr_ps (
								v0.data (), v1.data (), v2.data (), v3.data ());
						}

					static INLINE const vec fill (
						value_type v0)
						{
							return _mm_set1_ps (v0.data ());
						}

					template <
						init_type v0, init_type v1, init_type v2, init_type v3>
						static INLINE const vec <boolean <float>, 4> set ()
						{
							return impl::generator_m128 <v0 ? 0xFFFFFFFFU : 0, v1 ? 0xFFFFFFFFU : 0, v2 ? 0xFFFFFFFFU : 0, v3 ? 0xFFFFFFFFU : 0>::call ();
						}

					template <init_type v0>
						static INLINE const vec <boolean <float>, 4> fill ()
						{
							return set <v0, v0, v0, v0> ();
						}

					static INLINE const vec <boolean <float>, 4> load (const value_data* address, std::ptrdiff_t offset)
						{
							return _mm_load_ps (reinterpret_cast <const float*> (address) + offset * length);
						}

					INLINE void store (value_data* address, std::ptrdiff_t offset) const
						{
							_mm_store_ps (reinterpret_cast <float*> (address) + offset * length, data_);
						}

					INLINE vec (): data_ (impl::generator_m128 <0, 0, 0, 0>::call ())
						{
						}

					INLINE const value_type max () const	{ return stdext::accumulator <stdext::maximum <vec> > () (*this); }
					INLINE const value_type min () const	{ return stdext::accumulator <stdext::minimum <vec> > () (*this); }
			};

		template <> class vec <float, 8>
			{
				DEFINE_DWVEC_CLASS_GUTS(__m256,__m128,float,boolean <float>)

				public:
					typedef unsigned int init_type;

					union union_type
						{
							float val [8];
							data_type vec;
							__m128 vec4;
						};

					static INLINE const vec set (
						value_type v0, value_type v1, value_type v2, value_type v3,
						value_type v4, value_type v5, value_type v6, value_type v7)
						{
							return _mm256_setr_ps (v0, v1, v2, v3, v4, v5, v6, v7);
						}

					static INLINE const vec fill (
						value_type v0)
						{
							return _mm256_set1_ps (v0);
						}

					template <
						init_type v0, init_type v1, init_type v2, init_type v3,
						init_type v4, init_type v5, init_type v6, init_type v7>
						static INLINE const vec <float, 8> set ()
						{
							return impl::generator_m256 <v0, v1, v2, v3, v4, v5, v6, v7>::call ();
						}

					template <init_type v0>
						static INLINE const vec <float, 8> fill ()
						{
							return set <v0, v0, v0, v0, v0, v0, v0, v0> ();
						}

					static INLINE const vec <float, 8> load (const value_data* address, std::ptrdiff_t offset)
						{
							return _mm256_load_ps (address + offset * length);
						}

					INLINE void store (value_data* address, std::ptrdiff_t offset) const
						{
							_mm256_store_ps (address + offset * length, data_);
						}

					INLINE vec (): data_ (impl::generator_m256 <0, 0, 0, 0, 0, 0, 0, 0>::call ())
						{
						}

					INLINE const value_type max () const	{ return stdext::accumulator <stdext::maximum <vec> > () (*this); }
					INLINE const value_type min () const	{ return stdext::accumulator <stdext::minimum <vec> > () (*this); }
					INLINE const value_type sum () const	{ return stdext::accumulator <stdext::plus <vec> > () (*this); }
			};

		template <> class vec <double, 2>
			{
				DEFINE_VEC_CLASS_GUTS(__m128d,double,boolean <double>)

				public:
					typedef unsigned long long init_type;

					union union_type
						{
							double val [2];
							data_type vec;
						};

					static INLINE const vec set (
						value_type v0, value_type v1)
						{
							return _mm_setr_pd (v0, v1);
						}

					static INLINE const vec fill (
						value_type v0)
						{
							return _mm_set1_pd (v0);
						}

					template <
						init_type v0, init_type v1>
						static INLINE const vec <double, 2> set ()
						{
							return impl::generator_m128d <
								(v0 & 0x00000000FFFFFFFFULL), ((v0 & 0xFFFFFFFF00000000ULL) >> 32),
								(v1 & 0x00000000FFFFFFFFULL), ((v1 & 0xFFFFFFFF00000000ULL) >> 32) >::call ();
						}

					template <init_type v0>
						static INLINE const vec <double, 2> fill ()
						{
							return set <v0, v0> ();
						}

					static INLINE const vec <double, 2> load (const value_data* address, std::ptrdiff_t offset)
						{
							return _mm_load_pd (address + offset * length);
						}

					INLINE void store (value_data* address, std::ptrdiff_t offset) const
						{
							_mm_store_pd (address + offset * length, data_);
						}

					INLINE vec (): data_ (impl::generator_m128d <0, 0, 0, 0>::call ())
						{
						}

					INLINE const value_type max () const	{ return stdext::accumulator <stdext::maximum <vec> > () (*this); }
					INLINE const value_type min () const	{ return stdext::accumulator <stdext::minimum <vec> > () (*this); }
					INLINE const value_type sum () const	{ return stdext::accumulator <stdext::plus <vec> > () (*this); }
			};

		template <> class vec <boolean <double>, 2>
			{
				DEFINE_VEC_CLASS_GUTS(__m128d,boolean <double>,boolean <double>)

				public:
					typedef bool init_type;

					union union_type
						{
							double val [2];
							data_type vec;
						};

					static INLINE const vec set (
						value_type v0, value_type v1)
						{
							return _mm_setr_pd (
								v0.data (), v1.data ());
						}

					static INLINE const vec fill (
						value_type v0)
						{
							return _mm_set1_pd (v0.data ());
						}

					template <
						init_type v0, init_type v1>
						static INLINE const vec <boolean <double>, 2> set ()
						{
							return impl::generator_m128d <
								v0 ? 0xFFFFFFFFU : 0x00000000U, v0 ? 0xFFFFFFFFU : 0x00000000U,
								v1 ? 0xFFFFFFFFU : 0x00000000U, v1 ? 0xFFFFFFFFU : 0x00000000U>::call ();
						}

					template <init_type v0>
						static INLINE const vec <boolean <double>, 2> fill ()
						{
							return set <v0, v0> ();
						}

					static INLINE const vec <boolean <double>, 2> load (const value_data* address, std::ptrdiff_t offset)
						{
							return _mm_load_pd (reinterpret_cast <const double *> (address) + offset * length);
						}

					INLINE void store (value_data* address, std::ptrdiff_t offset) const
						{
							_mm_store_pd (reinterpret_cast <double*> (address) + offset * length, data_);
						}

					INLINE vec (): data_ (impl::generator_m128d <0, 0, 0, 0>::call ())
						{
						}

					INLINE const value_type max () const	{ return stdext::accumulator <stdext::maximum <vec> > () (*this); }
					INLINE const value_type min () const	{ return stdext::accumulator <stdext::minimum <vec> > () (*this); }
			};

		template <> class vec <boolean <float>, 8>
			{
				DEFINE_DWVEC_CLASS_GUTS(__m256,__m128,boolean<float>,boolean <float>)

				public:
					typedef bool init_type;

					union union_type
						{
							float val [8];
							data_type vec;
						};

					static INLINE const vec set (
						value_type v0, value_type v1, value_type v2, value_type v3,
						value_type v4, value_type v5, value_type v6, value_type v7)
						{
							return _mm256_setr_ps (v0.data(), v1.data(), v2.data(), v3.data(),
											   v4.data(), v5.data(), v6.data(), v7.data());
						}

					static INLINE const vec fill (
						value_type v0)
						{
							return _mm256_set1_ps (v0.data ());
						}

					template <
						init_type v0, init_type v1, init_type v2, init_type v3,
						init_type v4, init_type v5, init_type v6, init_type v7>
						static INLINE const vec <boolean <float>, 8> set ()
						{
							return impl::generator_m256 <v0 ? 0xFFFFFFFFU : 0, v1 ? 0xFFFFFFFFU : 0, v2 ? 0xFFFFFFFFU : 0, v3 ? 0xFFFFFFFFU : 0,
									v4 ? 0xFFFFFFFFU : 0, v5 ? 0xFFFFFFFFU : 0, v6 ? 0xFFFFFFFFU : 0, v7 ? 0xFFFFFFFFU : 0>::call ();
						}

					template <init_type v0>
						static INLINE const vec <boolean <float>, 8> fill ()
						{
							return set <v0, v0, v0, v0, v0, v0, v0, v0> ();
						}

					static INLINE const vec <boolean <float>, 8> load (const value_data* address, std::ptrdiff_t offset)
						{
							return _mm256_load_ps (reinterpret_cast <const float*> (address) + offset * length);
						}

					INLINE void store (value_data* address, std::ptrdiff_t offset) const
						{
							_mm256_store_ps (reinterpret_cast <float*> (address) + offset * length, data_);
						}

					INLINE vec (): data_ (impl::generator_m256 <0, 0, 0, 0, 0, 0, 0, 0>::call ())
						{
						}

					INLINE const value_type max () const	{ return stdext::accumulator <stdext::maximum <vec> > () (*this); }
					INLINE const value_type min () const	{ return stdext::accumulator <stdext::minimum <vec> > () (*this); }
			};

		#if defined(__AVX__) || defined(__AVX2__)

		template <> class vec <double, 4>
			{
				DEFINE_DWVEC_CLASS_GUTS(__m256d,__m128d,double,boolean <double>)

				public:
					typedef unsigned long long init_type;

					union union_type
						{
							double val [4];
							data_type vec;
							__m128d vec2;
						};

					static INLINE const vec set (
						value_type v0, value_type v1, value_type v2, value_type v3)
						{
							return _mm256_setr_pd (v0, v1, v2, v3);
						}

					static INLINE const vec fill (
						value_type v0)
						{
							return _mm256_set1_pd (v0);
						}

					template <
						init_type v0, init_type v1, init_type v2, init_type v3>
						static INLINE const vec <double, 4> set ()
						{
							return impl::generator_m256d <
								(v0 & 0x00000000FFFFFFFFULL), ((v0 & 0xFFFFFFFF00000000ULL) >> 32),
								(v1 & 0x00000000FFFFFFFFULL), ((v1 & 0xFFFFFFFF00000000ULL) >> 32),
								(v2 & 0x00000000FFFFFFFFULL), ((v2 & 0xFFFFFFFF00000000ULL) >> 32),
								(v3 & 0x00000000FFFFFFFFULL), ((v3 & 0xFFFFFFFF00000000ULL) >> 32) 								 >::call ();
						}

					template <init_type v0>
						static INLINE const vec <double, 4> fill ()
						{
							return set <v0, v0, v0, v0> ();
						}

					static INLINE const vec <double, 4> load (const value_data* address, std::ptrdiff_t offset)
						{
							return _mm256_load_pd (address + offset * length);
						}

					INLINE void store (value_data* address, std::ptrdiff_t offset) const
						{
							_mm256_store_pd (address + offset * length, data_);
						}

					INLINE vec (): data_ (impl::generator_m256d <0, 0, 0, 0, 0, 0, 0, 0>::call ())
						{
						}

					INLINE const value_type max () const	{ return stdext::accumulator <stdext::maximum <vec> > () (*this); }
					INLINE const value_type min () const	{ return stdext::accumulator <stdext::minimum <vec> > () (*this); }
					INLINE const value_type sum () const	{ return stdext::accumulator <stdext::plus <vec> > () (*this); }
			};

		template <> class vec <boolean <double>, 4>
			{
				DEFINE_DWVEC_CLASS_GUTS(__m256d,__m128d,boolean<double>,boolean <double>)

				public:
					typedef bool init_type;

					union union_type
						{
							double val [4];
							data_type vec;
						};

					static INLINE const vec set (
						value_type v0, value_type v1, value_type v2, value_type v3)
						{
							return _mm256_setr_pd (
								v0.data(), v1.data(), v2.data(), v3.data() );
						}

					static INLINE const vec fill (
						value_type v0)
						{
							return _mm256_set1_pd (v0.data());
						}

					template <
						init_type v0, init_type v1, init_type v2, init_type v3>
						static INLINE const vec <boolean <double>, 4> set ()
						{
							return impl::generator_m256d <
								v0 ? 0xFFFFFFFFU : 0x00000000U, v0 ? 0xFFFFFFFFU : 0x00000000U,
								v1 ? 0xFFFFFFFFU : 0x00000000U, v1 ? 0xFFFFFFFFU : 0x00000000U,
								v2 ? 0xFFFFFFFFU : 0x00000000U, v2 ? 0xFFFFFFFFU : 0x00000000U,
								v3 ? 0xFFFFFFFFU : 0x00000000U, v3 ? 0xFFFFFFFFU : 0x00000000U>::call ();
						}

					template <init_type v0>
						static INLINE const vec <boolean <double>, 4> fill ()
						{
							return set <v0, v0, v0, v0> ();
						}

					static INLINE const vec <boolean <double>, 4> load (const value_data* address, std::ptrdiff_t offset)
						{
							return _mm256_load_pd (reinterpret_cast <const double *> (address) + offset * length);
						}

					INLINE void store (value_data* address, std::ptrdiff_t offset) const
						{
							_mm256_store_pd (reinterpret_cast <double*> (address) + offset * length, data_);
						}

					INLINE vec (): data_ (impl::generator_m256d <0, 0, 0, 0, 0, 0, 0, 0>::call ())
						{
						}

					INLINE const value_type max () const	{ return stdext::accumulator <stdext::maximum <vec> > () (*this); }
					INLINE const value_type min () const	{ return stdext::accumulator <stdext::minimum <vec> > () (*this); }
			};

		template <> class vec <unsigned char, 16>
			{
				DEFINE_VEC_CLASS_GUTS(__m128i,unsigned char,boolean <char>)

				public:
					typedef unsigned char init_type;

					union union_type
						{
							unsigned char val [16];
							data_type vec;
						};

					static INLINE const vec set (
						value_type v0, value_type v1, value_type v2, value_type v3,
						value_type v4, value_type v5, value_type v6, value_type v7,
						value_type v8, value_type v9, value_type v10, value_type v11,
						value_type v12, value_type v13, value_type v14, value_type v15)
						{
							return _mm_setr_epi8 (v0, v1, v2, v3, v4, v5, v6, v7,
								v8, v9, v10, v11, v12, v13, v14, v15);
						}

					static INLINE const vec fill (
						value_type v0)
						{
							return _mm_set1_epi8 (v0);
						}

					template <
						init_type v0, init_type v1, init_type v2, init_type v3,
						init_type v4, init_type v5, init_type v6, init_type v7,
						init_type v8, init_type v9, init_type v10, init_type v11,
						init_type v12, init_type v13, init_type v14, init_type v15>
						static INLINE const vec <unsigned char, 16> set ()
						{
							return impl::generator_m128i <
								(v3 << 24) | (v2 << 16) | (v1 << 8) | v0,
								(v7 << 24) | (v6 << 16) | (v5 << 8) | v4,
								(v11 << 24) | (v10 << 16) | (v9 << 8) | v8,
								(v15 << 24) | (v14 << 16) | (v13 << 8) | v12>::call ();
						}

					template <init_type v0>
						static INLINE const vec <unsigned char, 16> fill ()
						{
							return set <v0, v0, v0, v0, v0, v0, v0, v0, v0, v0, v0, v0, v0, v0, v0, v0> ();
						}

					static INLINE const vec <unsigned char, 16> load (const value_data* address, std::ptrdiff_t offset)
						{
							return _mm_load_si128 (reinterpret_cast <const __m128i*> (address) + offset);
						}

					INLINE void store (value_data* address, std::ptrdiff_t offset) const
						{
							_mm_store_si128 (reinterpret_cast <__m128i*> (address) + offset, data_);
						}

					INLINE vec (): data_ (impl::generator_m128i <0, 0, 0, 0>::call ())
						{
						}
			};

		template <> class vec <signed char, 16>
			{
				DEFINE_VEC_CLASS_GUTS(__m128i,signed char,boolean <char>)

				public:
					typedef signed char init_type;

					union union_type
						{
							signed char val [16];
							data_type vec;
						};

					static INLINE const vec set (
						value_type v0, value_type v1, value_type v2, value_type v3,
						value_type v4, value_type v5, value_type v6, value_type v7,
						value_type v8, value_type v9, value_type v10, value_type v11,
						value_type v12, value_type v13, value_type v14, value_type v15)
						{
							return _mm_setr_epi8 (v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15);
						}

					static INLINE const vec fill (
						value_type v0)
						{
							return _mm_set1_epi8 (v0);
						}

					template <
						init_type v0, init_type v1, init_type v2, init_type v3,
						init_type v4, init_type v5, init_type v6, init_type v7,
						init_type v8, init_type v9, init_type v10, init_type v11,
						init_type v12, init_type v13, init_type v14, init_type v15>
						static INLINE const vec <signed char, 16> set ()
						{
							return impl::generator_m128i <
								(((unsigned char) v3) << 24) | (((unsigned char) v2) << 16) | (((unsigned char) v1) << 8) | ((unsigned char) v0),
								(((unsigned char) v7) << 24) | (((unsigned char) v6) << 16) | (((unsigned char) v5) << 8) | ((unsigned char) v4),
								(((unsigned char) v11) << 24) | (((unsigned char) v10) << 16) | (((unsigned char) v9) << 8) | ((unsigned char) v8),
								(((unsigned char) v15) << 24) | (((unsigned char) v14)<< 16) | (((unsigned char) v13) << 8) | ((unsigned char) v12)>::call ();
						}

					template <init_type v0>
						static INLINE const vec <signed char, 16> fill ()
						{
							return set <v0, v0, v0, v0, v0, v0, v0, v0, v0, v0, v0, v0, v0, v0, v0, v0> ();
						}

					static INLINE const vec <signed char, 16> load (const value_data* address, std::ptrdiff_t offset)
						{
							return _mm_load_si128 (reinterpret_cast <const __m128i*> (address) + offset);
						}

					INLINE void store (value_data* address, std::ptrdiff_t offset) const
						{
							_mm_store_si128 (reinterpret_cast <__m128i*> (address) + offset, data_);
						}

					INLINE vec (): data_ (impl::generator_m128i <0, 0, 0, 0>::call ())
						{
						}
			};

		template <> class vec <boolean <char>, 16>
			{
				DEFINE_VEC_CLASS_GUTS(__m128i,boolean <char>,boolean <char>)

				public:
					typedef bool init_type;

					union union_type
						{
							unsigned char val [16];
							data_type vec;
						};

					static INLINE const vec set (
						value_type v0, value_type v1, value_type v2, value_type v3,
						value_type v4, value_type v5, value_type v6, value_type v7,
						value_type v8, value_type v9, value_type v10, value_type v11,
						value_type v12, value_type v13, value_type v14, value_type v15)
						{
							return _mm_setr_epi8 (
								v0.data (), v1.data (), v2.data (), v3.data (),
								v4.data (), v5.data (), v6.data (), v7.data (),
								v8.data (), v9.data (), v10.data (), v11.data (),
								v12.data (), v13.data (), v14.data (), v15.data ());
						}

					static INLINE const vec fill (
						value_type v0)
						{
							return _mm_set1_epi8 (v0.data ());
						}

					template <
						init_type v0, init_type v1, init_type v2, init_type v3,
						init_type v4, init_type v5, init_type v6, init_type v7,
						init_type v8, init_type v9, init_type v10, init_type v11,
						init_type v12, init_type v13, init_type v14, init_type v15>
						static INLINE const vec <boolean <char>, 16> set ()
						{
							return impl::generator_m128i <
								(v3 ? 0xFF000000U : 0) | (v2 ? 0x00FF0000U : 0) | (v1 ? 0x0000FF00U : 0) | (v0 ? 0x000000FFU : 0),
								(v7 ? 0xFF000000U : 0) | (v6 ? 0x00FF0000U : 0) | (v5 ? 0x0000FF00U : 0) | (v4 ? 0x000000FFU : 0),
								(v11 ? 0xFF000000U : 0) | (v10 ? 0x00FF0000U : 0) | (v9 ? 0x0000FF00U : 0) | (v8 ? 0x000000FFU : 0),
								(v15 ? 0xFF000000U : 0) | (v14 ? 0x00FF0000U : 0) | (v13 ? 0x0000FF00U : 0) | (v12 ? 0x000000FFU : 0)>::call ();
						}

					template <init_type v0>
						static INLINE const vec <boolean <char>, 16> fill ()
						{
							return set <v0, v0, v0, v0, v0, v0, v0, v0, v0, v0, v0, v0, v0, v0, v0, v0> ();
						}

					static INLINE const vec <boolean <char>, 16> load (const value_data* address, std::ptrdiff_t offset)
						{
							return _mm_load_si128 (reinterpret_cast <const __m128i*> (address) + offset);
						}

					INLINE void store (value_data* address, std::ptrdiff_t offset) const
						{
							_mm_store_si128 (reinterpret_cast <__m128i*> (address) + offset, data_);
						}

					INLINE vec (): data_ (impl::generator_m128i <0, 0, 0, 0>::call ())
						{
						}

					INLINE const value_type max () const	{ return stdext::accumulator <stdext::maximum <vec> > () (*this); }
					INLINE const value_type min () const	{ return stdext::accumulator <stdext::minimum <vec> > () (*this); }
			};

		template <> class vec <unsigned short, 8>
			{
				DEFINE_VEC_CLASS_GUTS(__m128i,unsigned short,boolean <short>)

				public:
					typedef unsigned short init_type;

					union union_type
						{
							unsigned short val [8];
							data_type vec;
						};

					static INLINE const vec set (
						value_type v0, value_type v1, value_type v2, value_type v3,
						value_type v4, value_type v5, value_type v6, value_type v7)
						{
							return _mm_setr_epi16 (v0, v1, v2, v3, v4, v5, v6, v7);
						}

					static INLINE const vec fill (
						value_type v0)
						{
							return _mm_set1_epi16 (v0);
						}

					template <
						init_type v0, init_type v1, init_type v2, init_type v3,
						init_type v4, init_type v5, init_type v6, init_type v7>
						static INLINE const vec <unsigned short, 8> set ()
						{
							return impl::generator_m128i <
								(v1 << 16) | v0, (v3 << 16) | v2,
								(v5 << 16) | v4, (v7 << 16) | v6>::call ();
						}

					template <init_type v0>
						static INLINE const vec <unsigned short, 8> fill ()
						{
							return set <v0, v0, v0, v0, v0, v0, v0, v0> ();
						}

					static INLINE const vec <unsigned short, 8> load (const value_data* address, std::ptrdiff_t offset)
						{
							return _mm_load_si128 (reinterpret_cast <const __m128i*> (address) + offset);
						}

					INLINE void store (value_data* address, std::ptrdiff_t offset) const
						{
							_mm_store_si128 (reinterpret_cast <__m128i*> (address) + offset, data_);
						}

					INLINE vec (): data_ (impl::generator_m128i <0, 0, 0, 0>::call ())
						{
						}
			};

		template <> class vec <short, 8>
			{
				DEFINE_VEC_CLASS_GUTS(__m128i,short,boolean <short>)

				public:
					typedef short init_type;

					union union_type
						{
							short val [8];
							data_type vec;
						};

					static INLINE const vec set (
						value_type v0, value_type v1, value_type v2, value_type v3,
						value_type v4, value_type v5, value_type v6, value_type v7)
						{
							return _mm_setr_epi16 (v0, v1, v2, v3, v4, v5, v6, v7);
						}

					static INLINE const vec fill (
						value_type v0)
						{
							return _mm_set1_epi16 (v0);
						}

					template <
						init_type v0, init_type v1, init_type v2, init_type v3,
						init_type v4, init_type v5, init_type v6, init_type v7>
						static INLINE const vec <short, 8> set ()
						{
							return impl::generator_m128i <
								(((unsigned short) v1) << 16) | ((unsigned short) v0), (((unsigned short) v3) << 16) | ((unsigned short) v2),
								(((unsigned short) v5) << 16) | ((unsigned short) v4), (((unsigned short) v7) << 16) | ((unsigned short) v6)>::call ();
						}

					template <init_type v0>
						static INLINE const vec <short, 8> fill ()
						{
							return set <v0, v0, v0, v0, v0, v0, v0, v0> ();
						}

					static INLINE const vec <short, 8> load (const value_data* address, std::ptrdiff_t offset)
						{
							return _mm_load_si128 (reinterpret_cast <const __m128i*> (address) + offset);
						}

					INLINE void store (value_data* address, std::ptrdiff_t offset) const
						{
							_mm_store_si128 (reinterpret_cast <__m128i*> (address) + offset, data_);
						}

					INLINE vec (): data_ (impl::generator_m128i <0, 0, 0, 0>::call ())
						{
						}
			};

		template <> class vec <boolean <short>, 8>
			{
				DEFINE_VEC_CLASS_GUTS(__m128i,boolean <short>,boolean <short>)

				public:
					typedef bool init_type;

					union union_type
						{
							unsigned short val [8];
							data_type vec;
						};

					static INLINE const vec set (
						value_type v0, value_type v1, value_type v2, value_type v3,
						value_type v4, value_type v5, value_type v6, value_type v7)
						{
							return _mm_setr_epi16 (
								v0.data (), v1.data (), v2.data (), v3.data (),
								v4.data (), v5.data (), v6.data (), v7.data ());
						}

					static INLINE const vec fill (
						value_type v0)
						{
							return _mm_set1_epi16 (v0.data ());
						}

					template <
						init_type v0, init_type v1, init_type v2, init_type v3,
						init_type v4, init_type v5, init_type v6, init_type v7>
						static INLINE const vec <boolean <short>, 8> set ()
						{
							return impl::generator_m128i <
								(v1 ? 0xFFFF0000U : 0) | (v0 ? 0x0000FFFFU : 0), (v3 ? 0xFFFF0000U : 0) | (v2 ? 0x0000FFFFU : 0),
								(v5 ? 0xFFFF0000U : 0) | (v4 ? 0x0000FFFFU : 0), (v7 ? 0xFFFF0000U : 0) | (v6 ? 0x0000FFFFU : 0)>::call ();
						}

					template <init_type v0>
						static INLINE const vec <boolean <short>, 8> fill ()
						{
							return set <v0, v0, v0, v0, v0, v0, v0, v0> ();
						}

					static INLINE const vec <boolean <short>, 8> load (const value_data* address, std::ptrdiff_t offset)
						{
							return _mm_load_si128 (reinterpret_cast <const __m128i*> (address) + offset);
						}

					INLINE void store (value_data* address, std::ptrdiff_t offset) const
						{
							_mm_store_si128 (reinterpret_cast <__m128i*> (address) + offset, data_);
						}

					INLINE vec (): data_ (impl::generator_m128i <0, 0, 0, 0>::call ())
						{
						}
			};

		template <> class vec <unsigned int, 4>
			{
				DEFINE_VEC_CLASS_GUTS(__m128i,unsigned int,boolean <int>)

				public:
					typedef unsigned int init_type;

					union union_type
						{
							unsigned int val [4];
							data_type vec;
						};

					static INLINE const vec set (
						value_type v0, value_type v1, value_type v2, value_type v3)
						{
							return _mm_setr_epi32 (v0, v1, v2, v3);
						}

					static INLINE const vec fill (
						value_type v0)
						{
							return _mm_set1_epi32 (v0);
						}

					template <
						init_type v0, init_type v1, init_type v2, init_type v3>
						static INLINE const vec <unsigned int, 4> set ()
						{
							return impl::generator_m128i <v0, v1, v2, v3>::call ();
						}

					template <init_type v0>
						static INLINE const vec <unsigned int, 4> fill ()
						{
							return set <v0, v0, v0, v0> ();
						}

					static INLINE const vec <unsigned int, 4> load (const value_data* address, std::ptrdiff_t offset)
						{
							return _mm_load_si128 (reinterpret_cast <const __m128i*> (address) + offset);
						}

					INLINE void store (value_data* address, std::ptrdiff_t offset) const
						{
							_mm_store_si128 (reinterpret_cast <__m128i*> (address) + offset, data_);
						}

					INLINE vec (): data_ (impl::generator_m128i <0, 0, 0, 0>::call ())
						{
						}

					INLINE const value_type sum () const	{ return stdext::accumulator <stdext::plus <vec> > () (*this); }
			};

		template <> class vec <int, 4>
			{
				DEFINE_VEC_CLASS_GUTS(__m128i,int,boolean <int>)

				public:
					typedef int init_type;

					union union_type
						{
							int val [4];
							data_type vec;
						};

					static INLINE const vec set (
						value_type v0, value_type v1, value_type v2, value_type v3)
						{
							return _mm_setr_epi32 (v0, v1, v2, v3);
						}

					static INLINE const vec fill (
						value_type v0)
						{
							return _mm_set1_epi32 (v0);
						}

					template <
						init_type v0, init_type v1, init_type v2, init_type v3>
						static INLINE const vec <int, 4> set ()
						{
							return impl::generator_m128i <(unsigned int) v0, (unsigned int) v1, (unsigned int) v2, (unsigned int) v3>::call ();
						}

					template <init_type v0>
						static INLINE const vec <int, 4> fill ()
						{
							return set <v0, v0, v0, v0> ();
						}

					static INLINE const vec <int, 4> load (const value_data* address, std::ptrdiff_t offset)
						{
							return _mm_load_si128 (reinterpret_cast <const __m128i*> (address) + offset);
						}

					INLINE void store (value_data* address, std::ptrdiff_t offset) const
						{
							_mm_store_si128 (reinterpret_cast <__m128i*> (address) + offset, data_);
						}

					INLINE vec (): data_ (impl::generator_m128i <0, 0, 0, 0>::call ())
						{
						}

					INLINE const value_type sum () const	{ return stdext::accumulator <stdext::plus <vec> > () (*this); }
			};

		template <> class vec <boolean <int>, 4>
			{
				DEFINE_VEC_CLASS_GUTS(__m128i,boolean <int>,boolean <int>)

				public:
					typedef bool init_type;

					union union_type
						{
							unsigned int val [4];
							data_type vec;
						};

					static INLINE const vec set (
						value_type v0, value_type v1, value_type v2, value_type v3)
						{
							return _mm_setr_epi32 (
								v0.data (), v1.data (), v2.data (), v3.data ());
						}

					static INLINE const vec fill (
						value_type v0)
						{
							return _mm_set1_epi32 (v0.data ());
						}

					template <
						init_type v0, init_type v1, init_type v2, init_type v3>
						static INLINE const vec <boolean <int>, 4> set ()
						{
							return impl::generator_m128i <v0 ? 0xFFFFFFFFU : 0, v1 ? 0xFFFFFFFFU : 0, v2 ? 0xFFFFFFFFU : 0, v3 ? 0xFFFFFFFFU : 0>::call ();
						}

					template <init_type v0>
						static INLINE const vec <boolean <int>, 4> fill ()
						{
							return set <v0, v0, v0, v0> ();
						}

					static INLINE const vec <boolean <int>, 4> load (const value_data* address, std::ptrdiff_t offset)
						{
							return _mm_load_si128 (reinterpret_cast <const __m128i*> (address) + offset);
						}

					INLINE void store (value_data* address, std::ptrdiff_t offset) const
						{
							_mm_store_si128 (reinterpret_cast <__m128i*> (address) + offset, data_);
						}

					INLINE vec (): data_ (impl::generator_m128i <0, 0, 0, 0>::call ())
						{
						}
			};

		template <> class vec <int, 8>
			{
				DEFINE_DWVEC_CLASS_GUTS(__m256i,__m128i,int,boolean <int>)

				public:
					typedef int init_type;

					union union_type
						{
							int val [8];
							data_type vec;
							half_data_type vec4;
						};

					static INLINE const vec set (
						value_type v0, value_type v1, value_type v2, value_type v3,
						value_type v4, value_type v5, value_type v6, value_type v7)
						{
							return _mm256_setr_epi32 (v0, v1, v2, v3, v4, v5, v6, v7);
						}

					static INLINE const vec fill (
						value_type v0)
						{
							return _mm256_set1_epi32 (v0);
						}

					template <
						init_type v0, init_type v1, init_type v2, init_type v3,
						init_type v4, init_type v5, init_type v6, init_type v7>
						static INLINE const vec <int, 8> set ()
						{
							return impl::generator_m256i <(unsigned int) v0, (unsigned int) v1, (unsigned int) v2, (unsigned int) v3,
								(unsigned int) v4, (unsigned int) v5, (unsigned int) v6, (unsigned int) v7
								>::call ();
						}

					template <init_type v0>
						static INLINE const vec <int, 8> fill ()
						{
							return set <v0, v0, v0, v0, v0, v0, v0, v0> ();
						}

					static INLINE const vec <int, 8> load (const value_data* address, std::ptrdiff_t offset)
						{
							return _mm256_load_si256 (reinterpret_cast <const __m256i*> (address) + offset);
						}

					INLINE void store (value_data* address, std::ptrdiff_t offset) const
						{
							_mm256_store_si256 (reinterpret_cast <__m256i*> (address) + offset, data_);
						}

					INLINE vec (): data_ (impl::generator_m256i <0, 0, 0, 0, 0, 0, 0, 0>::call ())
						{
						}

					INLINE const value_type sum () const	{ return stdext::accumulator <stdext::plus <vec> > () (*this); }
			};

		template <> class vec <boolean <int>, 8>
			{
				DEFINE_DWVEC_CLASS_GUTS(__m256i,__m128i,boolean<int>,boolean <int>)

				public:
					typedef bool init_type;

					union union_type
						{
							unsigned int val [8];
							data_type vec;
						};

					static INLINE const vec set (
						value_type v0, value_type v1, value_type v2, value_type v3,
						value_type v4, value_type v5, value_type v6, value_type v7)
						{
							return _mm256_setr_epi32 (
								v0.data (), v1.data (), v2.data (), v3.data (),
								v4.data(), v5.data(), v6.data(), v7.data() );
						}

					static INLINE const vec fill (
						value_type v0)
						{
							return _mm256_set1_epi32 (v0.data ());
						}

					template <
						init_type v0, init_type v1, init_type v2, init_type v3,
						init_type v4, init_type v5, init_type v6, init_type v7>
						static INLINE const vec <boolean <int>, 8> set ()
						{
							return impl::generator_m256i <v0 ? 0xFFFFFFFFU : 0, v1 ? 0xFFFFFFFFU : 0, v2 ? 0xFFFFFFFFU : 0, v3 ? 0xFFFFFFFFU : 0,
								v4 ? 0xFFFFFFFFU : 0, v5 ? 0xFFFFFFFFU : 0, v6 ? 0xFFFFFFFFU : 0, v7 ? 0xFFFFFFFFU : 0
								>::call ();
						}

					template <init_type v0>
						static INLINE const vec <boolean <int>, 8> fill ()
						{
							return set <v0, v0, v0, v0, v0, v0, v0, v0> ();
						}

					static INLINE const vec <boolean <int>, 8> load (const value_data* address, std::ptrdiff_t offset)
						{
							return _mm256_load_si256 (reinterpret_cast <const __m256i*> (address) + offset);
						}

					INLINE void store (value_data* address, std::ptrdiff_t offset) const
						{
							_mm256_store_si256 (reinterpret_cast <__m256i*> (address) + offset, data_);
						}

					INLINE vec (): data_ (impl::generator_m256i <0, 0, 0, 0, 0, 0, 0, 0>::call ())
						{
						}
			};

		template <> class vec <unsigned long long, 2>
			{
				DEFINE_VEC_CLASS_GUTS(__m128i,unsigned long long,boolean <long long>)

				public:
					typedef unsigned long long init_type;

					union union_type
						{
							unsigned long long val [2];
							data_type vec;
						};

					static INLINE const vec set (
						value_type v0, value_type v1)
						{
							union_type un = {v0, v1};
							return un.vec;
						}

					static INLINE const vec fill (
						value_type v0)
						{
							return set (v0, v0);
						}

					template <
						init_type v0, init_type v1>
						static INLINE const vec <unsigned long long, 2> set ()
						{
							return impl::generator_m128i <
								(v0 & 0x00000000FFFFFFFFULL), ((v0 & 0xFFFFFFFF00000000ULL) >> 32),
								(v1 & 0x00000000FFFFFFFFULL), ((v1 & 0xFFFFFFFF00000000ULL) >> 32) >::call ();
						}

					template <init_type v0>
						static INLINE const vec <unsigned long long, 2> fill ()
						{
							return set <v0, v0> ();
						}

					static INLINE const vec <unsigned long long, 2> load (const value_data* address, std::ptrdiff_t offset)
						{
							return _mm_load_si128 (reinterpret_cast <const __m128i*> (address) + offset);
						}

					INLINE void store (value_data* address, std::ptrdiff_t offset) const
						{
							_mm_store_si128 (reinterpret_cast <__m128i*> (address) + offset, data_);
						}

					INLINE vec (): data_ (impl::generator_m128i <0, 0, 0, 0>::call ())
						{
						}
			};

		template <> class vec <long long, 2>
			{
				DEFINE_VEC_CLASS_GUTS(__m128i,long long,boolean <long long>)

				public:
					typedef long long init_type;

					union union_type
						{
							long long val [2];
							data_type vec;
						};

					static INLINE const vec set (
						value_type v0, value_type v1)
						{
							union_type un = {v0, v1};
							return un.vec;
						}

					static INLINE const vec fill (
						value_type v0)
						{
							return set (v0, v0);
						}

					template <
						init_type v0, init_type v1>
						static INLINE const vec <long long, 2> set ()
						{
							return impl::generator_m128i <
								(((unsigned long long) v0) & 0x00000000FFFFFFFFULL), ((((unsigned long long) v0) & 0xFFFFFFFF00000000ULL) >> 32),
								(((unsigned long long) v1) & 0x00000000FFFFFFFFULL), ((((unsigned long long) v1) & 0xFFFFFFFF00000000ULL) >> 32) >::call ();
						}

					template <init_type v0>
						static INLINE const vec <long long, 2> fill ()
						{
							return set <v0, v0> ();
						}

					static INLINE const vec <long long, 2> load (const value_data* address, std::ptrdiff_t offset)
						{
							return _mm_load_si128 (reinterpret_cast <const __m128i*> (address) + offset);
						}

					INLINE void store (value_data* address, std::ptrdiff_t offset) const
						{
							_mm_store_si128 (reinterpret_cast <__m128i*> (address) + offset, data_);
						}

					INLINE vec (): data_ (impl::generator_m128i <0, 0, 0, 0>::call ())
						{
						}
			};

		template <> class vec <boolean <long long>, 2>
			{
				DEFINE_VEC_CLASS_GUTS(__m128i,boolean <long long>,boolean <long long>)

				public:
					typedef bool init_type;

					union union_type
						{
							unsigned long long val [2];
							data_type vec;
						};

					static INLINE const vec set (
						value_type v0, value_type v1)
						{
							union_type un = {v0.data (), v1.data ()};
							return un.vec;
						}

					static INLINE const vec fill (
						value_type v0)
						{
							return set (v0, v0);
						}

					template <
						init_type v0, init_type v1>
						static INLINE const vec <boolean <long long>, 2> set ()
						{
							return impl::generator_m128i <
								v0 ? 0xFFFFFFFFU : 0x00000000U, v0 ? 0xFFFFFFFFU : 0x00000000U,
								v1 ? 0xFFFFFFFFU : 0x00000000U, v1 ? 0xFFFFFFFFU : 0x00000000U>::call ();
						}

					template <init_type v0>
						static INLINE const vec <boolean <long long>, 2> fill ()
						{
							return set <v0, v0> ();
						}

					static INLINE const vec <boolean <long long>, 2> load (const value_data* address, std::ptrdiff_t offset)
						{
							return _mm_load_si128 (reinterpret_cast <const __m128i*> (address) + offset);
						}

					INLINE void store (value_data* address, std::ptrdiff_t offset) const
						{
							_mm_store_si128 (reinterpret_cast <__m128i*> (address) + offset, data_);
						}

					INLINE vec (): data_ (impl::generator_m128i <0, 0, 0, 0>::call ())
						{
						}
			};

		template <> class vec <unsigned long long, 4>
			{
				DEFINE_DWVEC_CLASS_GUTS(__m256i,__m128i,unsigned long long,boolean <long long>)

				public:
					typedef unsigned long long init_type;

					union union_type
						{
							unsigned long long val [4];
							data_type vec;
							half_data_type vec2;
						};

					static INLINE const vec set (
						value_type v0, value_type v1, value_type v2, value_type v3)
						{
							union_type un = {v0, v1, v2, v3};
							return un.vec;
						}

					static INLINE const vec fill (
						value_type v0)
						{
							return set (v0, v0, v0, v0);
						}

					template <
						init_type v0, init_type v1, init_type v2, init_type v3>
						static INLINE const vec <unsigned long long, 4> set ()
						{
							return impl::generator_m256i <
								(v0 & 0x00000000FFFFFFFFULL), ((v0 & 0xFFFFFFFF00000000ULL) >> 32),
								(v1 & 0x00000000FFFFFFFFULL), ((v1 & 0xFFFFFFFF00000000ULL) >> 32),
								(v2 & 0x00000000FFFFFFFFULL), ((v2 & 0xFFFFFFFF00000000ULL) >> 32),
								(v3 & 0x00000000FFFFFFFFULL), ((v3 & 0xFFFFFFFF00000000ULL) >> 32)
								>::call ();
						}

					template <init_type v0>
						static INLINE const vec <unsigned long long, 4> fill ()
						{
							return set <v0, v0, v0, v0> ();
						}

					static INLINE const vec <unsigned long long, 4> load (const value_data* address, std::ptrdiff_t offset)
						{
							return _mm256_load_si256 (reinterpret_cast <const __m256i*> (address) + offset);
						}

					INLINE void store (value_data* address, std::ptrdiff_t offset) const
						{
							_mm256_store_si256 (reinterpret_cast <__m256i*> (address) + offset, data_);
						}

					INLINE vec (): data_ (impl::generator_m256i <0, 0, 0, 0, 0, 0, 0, 0>::call ())
						{
						}
			};

		template <> class vec <long long, 4>
			{
				DEFINE_DWVEC_CLASS_GUTS(__m256i,__m128i,long long,boolean <long long>)

				public:
					typedef long long init_type;

					union union_type
						{
							long long val [4];
							data_type vec;
							half_data_type vec2;
						};

					static INLINE const vec set (
						value_type v0, value_type v1, value_type v2, value_type v3)
						{
							union_type un = {v0, v1, v2, v3};
							return un.vec;
						}

					static INLINE const vec fill (
						value_type v0)
						{
							return set (v0, v0, v0, v0);
						}

					template <
						init_type v0, init_type v1, init_type v2, init_type v3>
						static INLINE const vec <long long, 4> set ()
						{
							return impl::generator_m256i <
								(((unsigned long long) v0) & 0x00000000FFFFFFFFULL), ((((unsigned long long) v0) & 0xFFFFFFFF00000000ULL) >> 32),
								(((unsigned long long) v1) & 0x00000000FFFFFFFFULL), ((((unsigned long long) v1) & 0xFFFFFFFF00000000ULL) >> 32),
								(((unsigned long long) v2) & 0x00000000FFFFFFFFULL), ((((unsigned long long) v2) & 0xFFFFFFFF00000000ULL) >> 32),
								(((unsigned long long) v3) & 0x00000000FFFFFFFFULL), ((((unsigned long long) v3) & 0xFFFFFFFF00000000ULL) >> 32)
								>::call ();
						}

					template <init_type v0>
						static INLINE const vec <long long, 4> fill ()
						{
							return set <v0, v0, v0, v0> ();
						}

					static INLINE const vec <long long, 4> load (const value_data* address, std::ptrdiff_t offset)
						{
							return _mm256_load_si256 (reinterpret_cast <const __m256i*> (address) + offset);
						}

					INLINE void store (value_data* address, std::ptrdiff_t offset) const
						{
							_mm256_store_si256 (reinterpret_cast <__m256i*> (address) + offset, data_);
						}

					INLINE vec (): data_ (impl::generator_m256i <0, 0, 0, 0, 0, 0, 0, 0>::call ())
						{
						}
			};

		template <> class vec <boolean <long long>, 4>
			{
				DEFINE_DWVEC_CLASS_GUTS(__m256i,__m128i,boolean<long long>,boolean <long long>)

				public:
					typedef bool init_type;

					union union_type
						{
							unsigned long long val [4];
							data_type vec;
						};

					static INLINE const vec set (
						value_type v0, value_type v1, value_type v2, value_type v3)
						{
							union_type un = {v0.data (), v1.data (), v2.data(), v3.data() };
							return un.vec;
						}

					static INLINE const vec fill (
						value_type v0)
						{
							return set (v0, v0, v0, v0);
						}

					template <
						init_type v0, init_type v1, init_type v2, init_type v3>
						static INLINE const vec <boolean <long long>, 4> set ()
						{
							return impl::generator_m256i <
								v0 ? 0xFFFFFFFFU : 0x00000000U, v0 ? 0xFFFFFFFFU : 0x00000000U,
								v1 ? 0xFFFFFFFFU : 0x00000000U, v1 ? 0xFFFFFFFFU : 0x00000000U,
								v2 ? 0xFFFFFFFFU : 0x00000000U, v2 ? 0xFFFFFFFFU : 0x00000000U,
								v3 ? 0xFFFFFFFFU : 0x00000000U, v3 ? 0xFFFFFFFFU : 0x00000000U
								>::call ();
						}

					template <init_type v0>
						static INLINE const vec <boolean <long long>, 4> fill ()
						{
							return set <v0, v0, v0, v0> ();
						}

					static INLINE const vec <boolean <long long>, 4> load (const value_data* address, std::ptrdiff_t offset)
						{
							return _mm256_load_si256 (reinterpret_cast <const __m256i*> (address) + offset);
						}

					INLINE void store (value_data* address, std::ptrdiff_t offset) const
						{
							_mm256_store_si256 (reinterpret_cast <__m256i*> (address) + offset, data_);
						}

					INLINE vec (): data_ (impl::generator_m256i <0, 0, 0, 0, 0, 0, 0, 0>::call ())
						{
						}
			};

		#endif

		#endif

#define DEFINE_MMX_UNARY_CONVERSION(FN,INTR,ARG,RESULT)								\
template <> struct FN##_function <RESULT, ARG >										\
	{																				\
		typedef ARG argument_type;													\
		typedef RESULT result_type;													\
																					\
		INLINE const result_type operator() (const argument_type& lhs) const						\
			{																		\
				return INTR (lhs.data ());											\
			}																		\
	};

#define SHUFFLE4MASK(i,j,k,l)	((i << 6) | (j << 4) | (k << 2) | l)

#define DEFINE_MMX_UNARY_SHUFFLE4(FN,INTR,ARG,RESULT)								\
template <unsigned int i, unsigned int j, unsigned int k, unsigned int l> struct FN##_function <i, j, k, l, ARG >										\
	{																				\
		typedef ARG argument_type;													\
		typedef RESULT result_type;													\
																					\
		INLINE const result_type operator() (const argument_type& lhs) const						\
			{																		\
				return INTR (lhs.data (), (i << 6) | (j << 4) | (k << 2) | l);		\
			}																		\
	};

#define DEFINE_MMX_BINARY_SHUFFLE4(FN,INTR,ARG1,ARG2,RESULT)								\
template <unsigned int i, unsigned int j, unsigned int k, unsigned int l> struct FN##_function <i, j, k, l, ARG1, ARG2 >										\
	{																				\
		typedef ARG1 first_argument_type;													\
		typedef ARG2 second_argument_type;													\
		typedef RESULT result_type;													\
																					\
		INLINE const result_type operator()														\
			(const first_argument_type& lhs, const second_argument_type& rhs) const	\
			{																		\
				return INTR (lhs.data (), rhs.data (), (i << 6) | (j << 4) | (k << 2) | l);		\
			}																		\
	};

#define SHUFFLE2MASK(i,j)	((i << 1) | j)

#define DEFINE_MMX_BINARY_SHUFFLE2(FN,INTR,ARG1,ARG2,RESULT)						\
template <unsigned int i, unsigned int j> struct FN##_function <i, j, ARG1, ARG2 >	\
	{																				\
		typedef ARG1 first_argument_type;											\
		typedef ARG2 second_argument_type;											\
		typedef RESULT result_type;													\
																					\
		INLINE const result_type operator()														\
			(const first_argument_type& lhs, const second_argument_type& rhs) const	\
			{																		\
				return INTR (lhs.data (), rhs.data (), (i << 1) | j);				\
			}																		\
	};


#define DEFINE_MMX_UNARY_FUNCTION(FN,INTR,ARG,RESULT)								\
template <> struct FN##_function <ARG >												\
	{																				\
		typedef ARG argument_type;													\
		typedef RESULT result_type;													\
																					\
		INLINE const result_type operator() (const argument_type& lhs) const						\
			{																		\
				return INTR (data_of (lhs));										\
			}																		\
	};

#define DEFINE_MMX_UNARY_FUNCTION_WITH_LITERAL(FN,INTR,ARG,RESULT)					\
template <unsigned int i> struct FN##_function <i, ARG >							\
	{																				\
		typedef ARG argument_type;													\
		typedef RESULT result_type;													\
																					\
		INLINE const result_type operator() (const argument_type& lhs) const						\
			{																		\
				return INTR (lhs.data (), i);										\
			}																		\
	};

#define DEFINE_MMX_UNARY_FUNCTION_WITH_CONSTINT(FN,INTR,ARG,RESULT)			\
template <const int i> struct FN##_function <i, ARG >						\
	{																				\
		typedef ARG argument_type;											\
		typedef RESULT result_type;													\
																					\
		INLINE const result_type operator()														\
			(const argument_type& lhs) const	\
			{																		\
				return INTR (lhs.data (), i);						\
			}																		\
	};

#define DEFINE_MMX_BINARY_CONVERSION(FN,INTR,ARG1,ARG2,RESULT)						\
template <> struct FN##_function <ARG1, ARG2, RESULT >								\
	{																				\
		typedef ARG1 first_argument_type;											\
		typedef ARG2 second_argument_type;											\
		typedef RESULT result_type;													\
																					\
		INLINE const result_type operator()														\
			(const first_argument_type& lhs, const second_argument_type& rhs) const	\
			{																		\
				return INTR (lhs.data (), rhs.data ());								\
			}																		\
	};

#define DEFINE_MMX_BINARY_FUNCTION(FN,INTR,ARG1,ARG2,RESULT)						\
template <> struct FN##_function <ARG1, ARG2 >										\
	{																				\
		typedef ARG1 first_argument_type;											\
		typedef ARG2 second_argument_type;											\
		typedef RESULT result_type;													\
																					\
		INLINE const result_type operator()														\
			(const first_argument_type& lhs, const second_argument_type& rhs) const	\
			{																		\
				return INTR (data_of (lhs), data_of (rhs));							\
			}																		\
	};

#define DEFINE_MMX_BINARY_FUNCTION_WITH_LITERAL(FN,INTR,ARG1,ARG2,RESULT)			\
template <unsigned int i> struct FN##_function <i, ARG1, ARG2 >						\
	{																				\
		typedef ARG1 first_argument_type;											\
		typedef ARG2 second_argument_type;											\
		typedef RESULT result_type;													\
																					\
		INLINE const result_type operator()														\
			(const first_argument_type& lhs, const second_argument_type& rhs) const	\
			{																		\
				return INTR (lhs.data (), data_of (rhs), i);						\
			}																		\
	};

#define DEFINE_MMX_BINARY_FUNCTION_WITH_CONSTINT(FN,INTR,ARG1,ARG2,RESULT)			\
template <const int i> struct FN##_function <i, ARG1, ARG2 >						\
	{																				\
		typedef ARG1 first_argument_type;											\
		typedef ARG2 second_argument_type;											\
		typedef RESULT result_type;													\
																					\
		INLINE const result_type operator()														\
			(const first_argument_type& lhs, const second_argument_type& rhs) const	\
			{																		\
				return INTR (lhs.data (), data_of (rhs), i);						\
			}																		\
	};

// AVX doesn't define all existing SSE/SSE2 functions to operate on double-width vectors, e.g.
// it has _mm256_add_ps and _mm256_add_pd, but not _mm256_add_epi32. This can be emulated with a sequence
// of SSE calls, approaching the arguments as 2-element single-width (__m128) vectors, and storing the
// result in a local 2-element __m128 to be returned as a single __m256.
#define DEFINE_AVX_BINARY_FUNCTION_FROM_MMX(FN,INTR,ARG1,ARG2,RESULT,ARG1m,ARG2m,RESULTm)						\
template <> struct FN##_function <ARG1, ARG2 >										\
	{																				\
		typedef ARG1 first_argument_type;											\
		typedef ARG2 second_argument_type;											\
		typedef RESULT result_type;													\
		typedef ARG1m first_arg_type_mmx;											\
		typedef ARG2m second_arg_type_mmx;											\
		typedef RESULTm result_type_mmx;													\
																					\
		INLINE const result_type operator()														\
			(const first_argument_type& lhs, const second_argument_type& rhs) const	\
			{ const first_arg_type_mmx *a = (const first_arg_type_mmx*) &lhs;						\
			  const second_arg_type_mmx *b = (const second_arg_type_mmx*) &rhs;					\
			  result_type r;														\
				((result_type_mmx*) &r)[0] = INTR (data_of (a[0]), data_of (b[0]));							\
				((result_type_mmx*) &r)[1] = INTR (data_of (a[1]), data_of (b[1]));							\
				return r;										\
			}																		\
	};

// slightly slower??
// //! AVX doesn't define all existing SSE/SSE2 functions to operate on double-width vectors, e.g.
// //! it has _mm256_add_ps and _mm256_add_pd, but not _mm256_add_epi32. This can be emulated with a sequence
// //! of SSE calls, approaching the arguments as 2-element single-width (__m128) vectors, and storing the
// //! result in a local __m256 addressed as a 2-element __m128.
// //! @n
// //! NB: ARG1m::data_type should be equal to ARG1::half_data_type; the extra arguments ARG1m, ARG2m and RESULTm
// //! are redundant (their types are available through __m256 ARG1, ARG2 and RESULT) but help catch
// //! type mismatches.
// #define DEFINE_AVX_BINARY_FUNCTION_FROM_MMX(FN,INTR,ARG1,ARG2,RESULT,ARG1m,ARG2m,RESULTm)						\
// template <> struct FN##_function <ARG1, ARG2 >										\
// 	{																				\
// 		typedef ARG1 first_argument_type;											\
// 		typedef ARG2 second_argument_type;											\
// 		typedef RESULT result_type;													\
// 		typedef ARG1m::data_type first_hdata_type;	\
// 		typedef ARG2m::data_type second_hdata_type;	\
// 		typedef RESULT::data_type result_data_type;		\
// 		typedef RESULTm::data_type result_hdata_type;		\
// 																					\
// 		INLINE const result_type operator()														\
// 			(const first_argument_type& lhs, const second_argument_type& rhs) const	\
// 			{ const first_hdata_type *a = lhs.half_data();						\
// 			  const second_hdata_type *b = rhs.half_data();					\
// 			  result_data_type r; result_hdata_type *rr = (result_hdata_type*) &r;					\
// 				rr[0] = INTR (a[0], b[0]);							\
// 				rr[1] = INTR (a[1], b[1]);							\
// 				return r;										\
// 			}																		\
// 	};

#define DEFINE_MMX_LOAD(FN,INTR,ARG,ARGA,RESULT)									\
template <> struct FN##_function <const ARG*>										\
	{																				\
		typedef const ARG* argument_type;											\
		typedef RESULT result_type;													\
																					\
		INLINE const result_type operator() (argument_type lhs) const							\
			{																		\
				return INTR (reinterpret_cast <const ARGA*> (lhs));					\
			}																		\
	};																				\
																					\
template <> struct FN##_function <ARG*>												\
	{																				\
		typedef ARG* argument_type;													\
		typedef RESULT result_type;													\
																					\
		INLINE const result_type operator() (argument_type lhs) const							\
			{																		\
				return INTR (reinterpret_cast <ARGA*> (lhs));						\
			}																		\
	};

#define DEFINE_MMX_STORE(FN,INTR,ARG1,ARG1A,ARG2)												\
template <> struct FN##_function <ARG1*, ARG2 >													\
	{																							\
		typedef ARG1* first_argument_type;														\
		typedef ARG2 second_argument_type;														\
		typedef void result_type;																\
																								\
		INLINE void operator() (first_argument_type lhs, const second_argument_type& rhs) const	\
			{																					\
				INTR (reinterpret_cast <ARG1A*> (lhs), data_of (rhs));							\
			}																					\
	};

		/// MMX/SSE/SSE2/SSE3/AVX intrinsics.

		/// Sequesters the MMX/SSE/SSE2/SSE3/AVX intrinsics from similarly named common or platform SIMD functions.
		/// Each MMX intrinsic of the form _mm_xxx_yyy is wrapped in a function xxx as well as a functor xxx_function.
		/// Any literal parameters are expressed as template non-type parameters, e.g. slli <0> (x) wraps _mm_slli_yyy (x, 0).
		///
		/// @note	You can use either the raw vector type or macstl::vec for any of the type parameters, except that the raw
		///			types convert to the object type with a 32-bit element size e.g. __m128i converts to macstl::vec <unsigned int, 4>.

		namespace mmx
			{
				/// @name Arithmetic

				//@{
				DEFINE_VEC_PLATFORM_BINARY_FUNCTION (add,add)
				DEFINE_VEC_PLATFORM_BINARY_FUNCTION (adds,add saturated)
				DEFINE_VEC_PLATFORM_BINARY_FUNCTION (addsub,add odd and subtract even)
				DEFINE_VEC_PLATFORM_BINARY_FUNCTION (avg,rounded average)
				DEFINE_VEC_PLATFORM_BINARY_FUNCTION (div,divide)
				DEFINE_VEC_PLATFORM_BINARY_FUNCTION (hadd,add adjacent)
				DEFINE_VEC_PLATFORM_BINARY_FUNCTION (hsub,subtract adjacent)
				DEFINE_VEC_PLATFORM_BINARY_FUNCTION (madd,multiply and add adjacent)
				DEFINE_VEC_PLATFORM_BINARY_FUNCTION (max,maximum)
				DEFINE_VEC_PLATFORM_BINARY_FUNCTION (min,minimum)
				DEFINE_VEC_PLATFORM_BINARY_FUNCTION (mul,multiply)
				DEFINE_VEC_PLATFORM_BINARY_FUNCTION (mulhi,multiply high)
				DEFINE_VEC_PLATFORM_BINARY_FUNCTION (mullo,multiply low)
				DEFINE_VEC_PLATFORM_UNARY_FUNCTION (rcp,reciprocal)
				DEFINE_VEC_PLATFORM_UNARY_FUNCTION (rsqrt,reciprocal square root)
				DEFINE_VEC_PLATFORM_BINARY_FUNCTION (sad,sum of absolute differences)
				DEFINE_VEC_PLATFORM_UNARY_FUNCTION (sqrt,square root)
				DEFINE_VEC_PLATFORM_BINARY_FUNCTION (sub,subtract)
				DEFINE_VEC_PLATFORM_BINARY_FUNCTION (subs,subtract saturated)
				DEFINE_VEC_PLATFORM_UNARY_FUNCTION_WITH_CONSTINT (round,round to nearest)
				//@}

				/// @name Logic

				//@{
				DEFINE_VEC_PLATFORM_BINARY_FUNCTION (vand,bitwise AND)
				DEFINE_VEC_PLATFORM_BINARY_FUNCTION (andnot,bitwise AND-NOT)
				DEFINE_VEC_PLATFORM_BINARY_FUNCTION (vor,bitwise OR)
				DEFINE_VEC_PLATFORM_BINARY_FUNCTION (vxor,bitwise XOR)
				//@}

				/// @name Shifters

				//@{
				DEFINE_VEC_PLATFORM_BINARY_FUNCTION (sll,shift left logical)
				DEFINE_VEC_PLATFORM_UNARY_FUNCTION_WITH_LITERAL (slli,shift left logical immediate)
				DEFINE_VEC_PLATFORM_BINARY_FUNCTION (sra,shift right algebraic)
				DEFINE_VEC_PLATFORM_UNARY_FUNCTION_WITH_LITERAL (srai, shift right algebraic immediate)
				DEFINE_VEC_PLATFORM_BINARY_FUNCTION (srl,shift right logical)
				DEFINE_VEC_PLATFORM_UNARY_FUNCTION_WITH_LITERAL (srli,shift right logical immediate)
				//@}

				/// @name Conversions

				//@{
				DEFINE_VEC_PLATFORM_UNARY_FUNCTION_WITH_RETURN_TYPE (cvt,convert)
				DEFINE_VEC_PLATFORM_UNARY_FUNCTION_WITH_RETURN_TYPE (cvtt,convert truncate)
				DEFINE_VEC_PLATFORM_BINARY_FUNCTION_WITH_RETURN_TYPE (cvt2,convert)
				//@}

				/// @name Compares

				//@{
				DEFINE_VEC_PLATFORM_BINARY_FUNCTION (cmpeq,compare equal-to)
				DEFINE_VEC_PLATFORM_BINARY_FUNCTION (cmpge,compare greater-than-orequal-to)
				DEFINE_VEC_PLATFORM_BINARY_FUNCTION (cmpgt,compare greater-than)
				DEFINE_VEC_PLATFORM_BINARY_FUNCTION (cmple,compare less-than-or-equal-to)
				DEFINE_VEC_PLATFORM_BINARY_FUNCTION (cmplt,compare less-than)
				DEFINE_VEC_PLATFORM_BINARY_FUNCTION (cmpneq,compare not equal-to)
				DEFINE_VEC_PLATFORM_BINARY_FUNCTION (cmpnge,compare not greater-than-or-equal-to)
				DEFINE_VEC_PLATFORM_BINARY_FUNCTION (cmpngt,compare not greater-than)
				DEFINE_VEC_PLATFORM_BINARY_FUNCTION (cmpnle,compare not less-than-or-equal-to)
				DEFINE_VEC_PLATFORM_BINARY_FUNCTION (cmpnlt,compare not less-than)
				DEFINE_VEC_PLATFORM_BINARY_FUNCTION (cmpord,compare ordered)
				DEFINE_VEC_PLATFORM_BINARY_FUNCTION (cmpunord,compare unordered)
				//@}

				/// @name Memory

				//@{
				DEFINE_VEC_PLATFORM_UNARY_FUNCTION (load,load aligned)
				DEFINE_VEC_PLATFORM_UNARY_FUNCTION (loadu,load unaligned)
				DEFINE_VEC_PLATFORM_UNARY_FUNCTION (loadd,load aligned)
				DEFINE_VEC_PLATFORM_UNARY_FUNCTION (loaddu,load unaligned)
				DEFINE_VEC_PLATFORM_UNARY_FUNCTION (loadr,load reverse)
				DEFINE_VEC_PLATFORM_BINARY_FUNCTION (store,store aligned)
				DEFINE_VEC_PLATFORM_BINARY_FUNCTION (storeu,store unaligned)
				DEFINE_VEC_PLATFORM_BINARY_FUNCTION (storer,store reverse)
				//@}

				/// @name Miscellaneous

				//@{
				DEFINE_VEC_PLATFORM_UNARY_FUNCTION_WITH_LITERAL (extract,extract element)
				DEFINE_VEC_PLATFORM_BINARY_FUNCTION_WITH_LITERAL (insert,insert element)
				DEFINE_VEC_PLATFORM_UNARY_FUNCTION (movedup,duplicate low to high)
				DEFINE_VEC_PLATFORM_UNARY_FUNCTION (movehdup,duplicate odd to even)
				DEFINE_VEC_PLATFORM_BINARY_FUNCTION (movehl,move high to low)
				DEFINE_VEC_PLATFORM_UNARY_FUNCTION (moveldup,duplicate even to odd)
				DEFINE_VEC_PLATFORM_BINARY_FUNCTION (movelh,move low to high)
				DEFINE_VEC_PLATFORM_UNARY_FUNCTION (movemask,mask creation)
				DEFINE_VEC_PLATFORM_BINARY_FUNCTION (packs,pack signed saturated)
				DEFINE_VEC_PLATFORM_BINARY_FUNCTION (packus,pack unsigned saturated)
				DEFINE_VEC_PLATFORM_BINARY_FUNCTION_WITH_LITERAL4 (shuffles,shuffle 4 float)
				DEFINE_VEC_PLATFORM_BINARY_FUNCTION_WITH_LITERAL4 (shuffledd,shuffle 4 double)
				DEFINE_VEC_PLATFORM_BINARY_FUNCTION_WITH_LITERAL2 (shuffled,shuffle 2 double)
				DEFINE_VEC_PLATFORM_UNARY_FUNCTION_WITH_LITERAL4 (shuffle,shuffle 4)
				DEFINE_VEC_PLATFORM_UNARY_FUNCTION_WITH_LITERAL4 (shufflehi,shuffle 4 high)
				DEFINE_VEC_PLATFORM_UNARY_FUNCTION_WITH_LITERAL4 (shufflelo,shuffle 4 low)
				DEFINE_VEC_PLATFORM_BINARY_FUNCTION (unpackhi,unpack high)
				DEFINE_VEC_PLATFORM_BINARY_FUNCTION (unpacklo,unpack low)
				DEFINE_VEC_PLATFORM_BINARY_FUNCTION_WITH_CONSTINT (blend,blends packed floating point values)
				DEFINE_VEC_PLATFORM_BINARY_FUNCTION_WITH_CONSTINT (dprod,dot product of floating point values)
				//@}

				#define M64_U8 vec <unsigned char, 8>
				#define M64_I8 vec <signed char, 8>
				#define M64_B8 vec <boolean <char>, 8>
				#define M64_U16 vec <unsigned short, 4>
				#define M64_I16 vec <short, 4>
				#define M64_B16 vec <boolean <short>, 4>
				#define M64_U32 vec <unsigned int, 2>
				#define M64_I32 vec <int, 2>
				#define M64_B32 vec <boolean <int>, 2>
				#define M128_F32 vec <float, 4>
				#define M128_B32 vec <boolean <float>, 4>
				#define M128D_F64 vec <double, 2>
				#define M128D_B64 vec <boolean <double>, 2>
				#define M128I_U8 vec <unsigned char, 16>
				#define M128I_I8 vec <signed char, 16>
				#define M128I_B8 vec <boolean <char>, 16>
				#define M128I_U16 vec <unsigned short, 8>
				#define M128I_I16 vec <short, 8>
				#define M128I_B16 vec <boolean <short>, 8>
				#define M128I_U32 vec <unsigned int, 4>
				#define M128I_I32 vec <int, 4>
				#define M128I_B32 vec <boolean <int>, 4>
				#define M128I_U64 vec <unsigned long long, 2>
				#define M128I_I64 vec <long long, 2>
				#define M128I_B64 vec <boolean <long long>, 2>

				#define M256I_U32 vec <unsigned int, 8>
				#define M256I_I32 vec <int, 8>
				#define M256I_B32 vec <boolean <int>, 8>
				#define M256I_U64 vec <unsigned long long, 4>
				#define M256I_I64 vec <long long, 4>
				#define M256I_B64 vec <boolean <long long>, 4>
				#define M256_F32 vec <float, 8>
				#define M256_B32 vec <boolean <float>, 8>
				#define M256D_F64 vec <double, 4>
				#define M256D_B64 vec <boolean <double>, 4>

				// MMX General Support Intrinsics

				#ifdef __MMX__

				INLINE void empty ()	{ _mm_empty (); }

				DEFINE_MMX_BINARY_FUNCTION (packs, _mm_packs_pi16, M64_I16, M64_I16, M64_I8)
				DEFINE_MMX_BINARY_FUNCTION (packs, _mm_packs_pi32, M64_I32, M64_I32, M64_I16)
				DEFINE_MMX_BINARY_FUNCTION (packs, _mm_packs_pu16, M64_U16, M64_U16, M64_U8)

				DEFINE_MMX_BINARY_FUNCTION (unpackhi, _mm_unpackhi_pi8, M64_I8, M64_I8, M64_I8)
				DEFINE_MMX_BINARY_FUNCTION (unpackhi, _mm_unpackhi_pi8, M64_U8, M64_U8, M64_U8)
				DEFINE_MMX_BINARY_FUNCTION (unpackhi, _mm_unpackhi_pi8, M64_B8, M64_B8, M64_B8)
				DEFINE_MMX_BINARY_FUNCTION (unpackhi, _mm_unpackhi_pi16, M64_I16, M64_I16, M64_I16)
				DEFINE_MMX_BINARY_FUNCTION (unpackhi, _mm_unpackhi_pi16, M64_U16, M64_U16, M64_U16)
				DEFINE_MMX_BINARY_FUNCTION (unpackhi, _mm_unpackhi_pi16, M64_B16, M64_B16, M64_B16)
				DEFINE_MMX_BINARY_FUNCTION (unpackhi, _mm_unpackhi_pi32, M64_I32, M64_I32, M64_I32)
				DEFINE_MMX_BINARY_FUNCTION (unpackhi, _mm_unpackhi_pi32, M64_U32, M64_U32, M64_U32)
				DEFINE_MMX_BINARY_FUNCTION (unpackhi, _mm_unpackhi_pi32, M64_B32, M64_B32, M64_B32)

				DEFINE_MMX_BINARY_FUNCTION (unpacklo, _mm_unpacklo_pi8, M64_I8, M64_I8, M64_I8)
				DEFINE_MMX_BINARY_FUNCTION (unpacklo, _mm_unpacklo_pi8, M64_U8, M64_U8, M64_U8)
				DEFINE_MMX_BINARY_FUNCTION (unpacklo, _mm_unpacklo_pi8, M64_B8, M64_B8, M64_B8)
				DEFINE_MMX_BINARY_FUNCTION (unpacklo, _mm_unpacklo_pi16, M64_I16, M64_I16, M64_I16)
				DEFINE_MMX_BINARY_FUNCTION (unpacklo, _mm_unpacklo_pi16, M64_U16, M64_U16, M64_U16)
				DEFINE_MMX_BINARY_FUNCTION (unpacklo, _mm_unpacklo_pi16, M64_B16, M64_B16, M64_B16)
				DEFINE_MMX_BINARY_FUNCTION (unpacklo, _mm_unpacklo_pi32, M64_I32, M64_I32, M64_I32)
				DEFINE_MMX_BINARY_FUNCTION (unpacklo, _mm_unpacklo_pi32, M64_U32, M64_U32, M64_U32)
				DEFINE_MMX_BINARY_FUNCTION (unpacklo, _mm_unpacklo_pi32, M64_B32, M64_B32, M64_B32)

				// MMX Arithmetic Intrinsics

				DEFINE_MMX_BINARY_FUNCTION (add, _mm_add_pi8, M64_I8, M64_I8, M64_I8)
				DEFINE_MMX_BINARY_FUNCTION (add, _mm_add_pi8, M64_U8, M64_U8, M64_U8)
				DEFINE_MMX_BINARY_FUNCTION (add, _mm_add_pi16, M64_I16, M64_I16, M64_I16)
				DEFINE_MMX_BINARY_FUNCTION (add, _mm_add_pi16, M64_U16, M64_U16, M64_U16)
				DEFINE_MMX_BINARY_FUNCTION (add, _mm_add_pi32, M64_I32, M64_I32, M64_I32)
				DEFINE_MMX_BINARY_FUNCTION (add, _mm_add_pi32, M64_U32, M64_U32, M64_U32)

				DEFINE_MMX_BINARY_FUNCTION (adds, _mm_adds_pi8, M64_I8, M64_I8, M64_I8)
				DEFINE_MMX_BINARY_FUNCTION (adds, _mm_adds_pi16, M64_I16, M64_I16, M64_I16)
				DEFINE_MMX_BINARY_FUNCTION (adds, _mm_adds_pu8, M64_U8, M64_U8, M64_U8)
				DEFINE_MMX_BINARY_FUNCTION (adds, _mm_adds_pu16, M64_U16, M64_U16, M64_U16)

				DEFINE_MMX_BINARY_FUNCTION (madd, _mm_madd_pi16, M64_I16, M64_I16, M64_I32)
				DEFINE_MMX_BINARY_FUNCTION (madd, _mm_madd_pi16, M64_U16, M64_U16, M64_U32)

				DEFINE_MMX_BINARY_FUNCTION (mulhi, _mm_mulhi_pi16, M64_I16, M64_I16, M64_I16)

				DEFINE_MMX_BINARY_FUNCTION (mullo, _mm_mullo_pi16, M64_I16, M64_I16, M64_I16)
				DEFINE_MMX_BINARY_FUNCTION (mullo, _mm_mullo_pi16, M64_U16, M64_U16, M64_U16)

				DEFINE_MMX_BINARY_FUNCTION (sub, _mm_sub_pi8, M64_I8, M64_I8, M64_I8)
				DEFINE_MMX_BINARY_FUNCTION (sub, _mm_sub_pi8, M64_U8, M64_U8, M64_U8)
				DEFINE_MMX_BINARY_FUNCTION (sub, _mm_sub_pi16, M64_I16, M64_I16, M64_I16)
				DEFINE_MMX_BINARY_FUNCTION (sub, _mm_sub_pi16, M64_U16, M64_U16, M64_U16)
				DEFINE_MMX_BINARY_FUNCTION (sub, _mm_sub_pi32, M64_I32, M64_I32, M64_I32)
				DEFINE_MMX_BINARY_FUNCTION (sub, _mm_sub_pi32, M64_U32, M64_U32, M64_U32)

				DEFINE_MMX_BINARY_FUNCTION (subs, _mm_subs_pi8, M64_I8, M64_I8, M64_I8)
				DEFINE_MMX_BINARY_FUNCTION (subs, _mm_subs_pi16, M64_I16, M64_I16, M64_I16)
				DEFINE_MMX_BINARY_FUNCTION (subs, _mm_subs_pu8, M64_U8, M64_U8, M64_U8)
				DEFINE_MMX_BINARY_FUNCTION (subs, _mm_subs_pu16, M64_U16, M64_U16, M64_U16)

				// MMX Shift Intrinsics

				DEFINE_MMX_BINARY_FUNCTION (sll, _mm_sll_pi16, M64_I16, M64_U16, M64_I16)
				DEFINE_MMX_BINARY_FUNCTION (sll, _mm_sll_pi16, M64_U16, M64_U16, M64_U16)

				DEFINE_MMX_BINARY_FUNCTION (sll, _mm_slli_pi16, M64_I16, int, M64_I16)
				DEFINE_MMX_BINARY_FUNCTION (sll, _mm_slli_pi16, M64_U16, int, M64_U16)

				DEFINE_MMX_BINARY_FUNCTION (sll, _mm_sll_pi32, M64_I32, M64_U32, M64_I32)
				DEFINE_MMX_BINARY_FUNCTION (sll, _mm_sll_pi32, M64_U32, M64_U32, M64_U32)

				DEFINE_MMX_BINARY_FUNCTION (sll, _mm_slli_pi32, M64_I32, int, M64_I32)
				DEFINE_MMX_BINARY_FUNCTION (sll, _mm_slli_pi32, M64_U32, int, M64_U32)

				DEFINE_MMX_UNARY_FUNCTION_WITH_LITERAL (slli, _mm_slli_pi16, M64_I16, M64_I16)
				DEFINE_MMX_UNARY_FUNCTION_WITH_LITERAL (slli, _mm_slli_pi16, M64_U16, M64_U16)

				DEFINE_MMX_UNARY_FUNCTION_WITH_LITERAL (slli, _mm_slli_pi32, M64_I32, M64_I32)
				DEFINE_MMX_UNARY_FUNCTION_WITH_LITERAL (slli, _mm_slli_pi32, M64_U32, M64_U32)

				DEFINE_MMX_BINARY_FUNCTION (sra, _mm_sra_pi16, M64_I16, M64_U16, M64_I16)
				DEFINE_MMX_BINARY_FUNCTION (sra, _mm_sra_pi32, M64_I32, M64_U32, M64_I32)

				DEFINE_MMX_BINARY_FUNCTION (sra, _mm_srai_pi16, M64_I16, int, M64_I16)
				DEFINE_MMX_BINARY_FUNCTION (sra, _mm_srai_pi32, M64_I32, int, M64_I32)

				DEFINE_MMX_UNARY_FUNCTION_WITH_LITERAL (srai, _mm_srai_pi16, M64_I16, M64_I16)
				DEFINE_MMX_UNARY_FUNCTION_WITH_LITERAL (srai, _mm_srai_pi32, M64_I32, M64_I32)

				DEFINE_MMX_BINARY_FUNCTION (srl, _mm_srl_pi16, M64_I16, M64_U16, M64_I16)
				DEFINE_MMX_BINARY_FUNCTION (srl, _mm_srl_pi16, M64_U16, M64_U16, M64_U16)

				DEFINE_MMX_BINARY_FUNCTION (srl, _mm_srli_pi16, M64_I16, int, M64_I16)
				DEFINE_MMX_BINARY_FUNCTION (srl, _mm_srli_pi16, M64_U16, int, M64_U16)

				DEFINE_MMX_BINARY_FUNCTION (srl, _mm_srl_pi32, M64_I32, M64_U32, M64_I32)
				DEFINE_MMX_BINARY_FUNCTION (srl, _mm_srl_pi32, M64_U32, M64_U32, M64_U32)

				DEFINE_MMX_BINARY_FUNCTION (srl, _mm_srli_pi32, M64_I32, int, M64_I32)
				DEFINE_MMX_BINARY_FUNCTION (srl, _mm_srli_pi32, M64_U32, int, M64_U32)

				DEFINE_MMX_UNARY_FUNCTION_WITH_LITERAL (srli, _mm_srli_pi16, M64_I16, M64_I16)
				DEFINE_MMX_UNARY_FUNCTION_WITH_LITERAL (srli, _mm_srli_pi16, M64_U16, M64_U16)

				DEFINE_MMX_UNARY_FUNCTION_WITH_LITERAL (srli, _mm_srli_pi32, M64_I32, M64_I32)
				DEFINE_MMX_UNARY_FUNCTION_WITH_LITERAL (srli, _mm_srli_pi32, M64_U32, M64_U32)

				// MMX Logical Intrinsics

				DEFINE_MMX_BINARY_FUNCTION (vand, _mm_and_si64, M64_I8, M64_I8, M64_I8)
				DEFINE_MMX_BINARY_FUNCTION (vand, _mm_and_si64, M64_B8, M64_I8, M64_I8)
				DEFINE_MMX_BINARY_FUNCTION (vand, _mm_and_si64, M64_I8, M64_B8, M64_I8)
				DEFINE_MMX_BINARY_FUNCTION (vand, _mm_and_si64, M64_U8, M64_U8, M64_U8)
				DEFINE_MMX_BINARY_FUNCTION (vand, _mm_and_si64, M64_B8, M64_U8, M64_U8)
				DEFINE_MMX_BINARY_FUNCTION (vand, _mm_and_si64, M64_U8, M64_B8, M64_U8)
				DEFINE_MMX_BINARY_FUNCTION (vand, _mm_and_si64, M64_B8, M64_B8, M64_B8)

				DEFINE_MMX_BINARY_FUNCTION (vand, _mm_and_si64, M64_I16, M64_I16, M64_I16)
				DEFINE_MMX_BINARY_FUNCTION (vand, _mm_and_si64, M64_B16, M64_I16, M64_I16)
				DEFINE_MMX_BINARY_FUNCTION (vand, _mm_and_si64, M64_I16, M64_B16, M64_I16)
				DEFINE_MMX_BINARY_FUNCTION (vand, _mm_and_si64, M64_U16, M64_U16, M64_U16)
				DEFINE_MMX_BINARY_FUNCTION (vand, _mm_and_si64, M64_B16, M64_U16, M64_U16)
				DEFINE_MMX_BINARY_FUNCTION (vand, _mm_and_si64, M64_U16, M64_B16, M64_U16)
				DEFINE_MMX_BINARY_FUNCTION (vand, _mm_and_si64, M64_B16, M64_B16, M64_B16)

				DEFINE_MMX_BINARY_FUNCTION (vand, _mm_and_si64, M64_I32, M64_I32, M64_I32)
				DEFINE_MMX_BINARY_FUNCTION (vand, _mm_and_si64, M64_B32, M64_I32, M64_I32)
				DEFINE_MMX_BINARY_FUNCTION (vand, _mm_and_si64, M64_I32, M64_B32, M64_I32)
				DEFINE_MMX_BINARY_FUNCTION (vand, _mm_and_si64, M64_U32, M64_U32, M64_U32)
				DEFINE_MMX_BINARY_FUNCTION (vand, _mm_and_si64, M64_B32, M64_U32, M64_U32)
				DEFINE_MMX_BINARY_FUNCTION (vand, _mm_and_si64, M64_U32, M64_B32, M64_U32)
				DEFINE_MMX_BINARY_FUNCTION (vand, _mm_and_si64, M64_B32, M64_B32, M64_B32)

				DEFINE_MMX_BINARY_FUNCTION (andnot, _mm_andnot_si64, M64_I8, M64_I8, M64_I8)
				DEFINE_MMX_BINARY_FUNCTION (andnot, _mm_andnot_si64, M64_B8, M64_I8, M64_I8)
				DEFINE_MMX_BINARY_FUNCTION (andnot, _mm_andnot_si64, M64_I8, M64_B8, M64_I8)
				DEFINE_MMX_BINARY_FUNCTION (andnot, _mm_andnot_si64, M64_U8, M64_U8, M64_U8)
				DEFINE_MMX_BINARY_FUNCTION (andnot, _mm_andnot_si64, M64_B8, M64_U8, M64_U8)
				DEFINE_MMX_BINARY_FUNCTION (andnot, _mm_andnot_si64, M64_U8, M64_B8, M64_U8)
				DEFINE_MMX_BINARY_FUNCTION (andnot, _mm_andnot_si64, M64_B8, M64_B8, M64_B8)

				DEFINE_MMX_BINARY_FUNCTION (andnot, _mm_andnot_si64, M64_I16, M64_I16, M64_I16)
				DEFINE_MMX_BINARY_FUNCTION (andnot, _mm_andnot_si64, M64_B16, M64_I16, M64_I16)
				DEFINE_MMX_BINARY_FUNCTION (andnot, _mm_andnot_si64, M64_I16, M64_B16, M64_I16)
				DEFINE_MMX_BINARY_FUNCTION (andnot, _mm_andnot_si64, M64_U16, M64_U16, M64_U16)
				DEFINE_MMX_BINARY_FUNCTION (andnot, _mm_andnot_si64, M64_B16, M64_U16, M64_U16)
				DEFINE_MMX_BINARY_FUNCTION (andnot, _mm_andnot_si64, M64_U16, M64_B16, M64_U16)
				DEFINE_MMX_BINARY_FUNCTION (andnot, _mm_andnot_si64, M64_B16, M64_B16, M64_B16)

				DEFINE_MMX_BINARY_FUNCTION (andnot, _mm_andnot_si64, M64_I32, M64_I32, M64_I32)
				DEFINE_MMX_BINARY_FUNCTION (andnot, _mm_andnot_si64, M64_B32, M64_I32, M64_I32)
				DEFINE_MMX_BINARY_FUNCTION (andnot, _mm_andnot_si64, M64_I32, M64_B32, M64_I32)
				DEFINE_MMX_BINARY_FUNCTION (andnot, _mm_andnot_si64, M64_U32, M64_U32, M64_U32)
				DEFINE_MMX_BINARY_FUNCTION (andnot, _mm_andnot_si64, M64_B32, M64_U32, M64_U32)
				DEFINE_MMX_BINARY_FUNCTION (andnot, _mm_andnot_si64, M64_U32, M64_B32, M64_U32)
				DEFINE_MMX_BINARY_FUNCTION (andnot, _mm_andnot_si64, M64_B32, M64_B32, M64_B32)

				DEFINE_MMX_BINARY_FUNCTION (vor, _mm_or_si64, M64_I8, M64_I8, M64_I8)
				DEFINE_MMX_BINARY_FUNCTION (vor, _mm_or_si64, M64_B8, M64_I8, M64_I8)
				DEFINE_MMX_BINARY_FUNCTION (vor, _mm_or_si64, M64_I8, M64_B8, M64_I8)
				DEFINE_MMX_BINARY_FUNCTION (vor, _mm_or_si64, M64_U8, M64_U8, M64_U8)
				DEFINE_MMX_BINARY_FUNCTION (vor, _mm_or_si64, M64_B8, M64_U8, M64_U8)
				DEFINE_MMX_BINARY_FUNCTION (vor, _mm_or_si64, M64_U8, M64_B8, M64_U8)
				DEFINE_MMX_BINARY_FUNCTION (vor, _mm_or_si64, M64_B8, M64_B8, M64_B8)

				DEFINE_MMX_BINARY_FUNCTION (vor, _mm_or_si64, M64_I16, M64_I16, M64_I16)
				DEFINE_MMX_BINARY_FUNCTION (vor, _mm_or_si64, M64_B16, M64_I16, M64_I16)
				DEFINE_MMX_BINARY_FUNCTION (vor, _mm_or_si64, M64_I16, M64_B16, M64_I16)
				DEFINE_MMX_BINARY_FUNCTION (vor, _mm_or_si64, M64_U16, M64_U16, M64_U16)
				DEFINE_MMX_BINARY_FUNCTION (vor, _mm_or_si64, M64_B16, M64_U16, M64_U16)
				DEFINE_MMX_BINARY_FUNCTION (vor, _mm_or_si64, M64_U16, M64_B16, M64_U16)
				DEFINE_MMX_BINARY_FUNCTION (vor, _mm_or_si64, M64_B16, M64_B16, M64_B16)

				DEFINE_MMX_BINARY_FUNCTION (vor, _mm_or_si64, M64_I32, M64_I32, M64_I32)
				DEFINE_MMX_BINARY_FUNCTION (vor, _mm_or_si64, M64_B32, M64_I32, M64_I32)
				DEFINE_MMX_BINARY_FUNCTION (vor, _mm_or_si64, M64_I32, M64_B32, M64_I32)
				DEFINE_MMX_BINARY_FUNCTION (vor, _mm_or_si64, M64_U32, M64_U32, M64_U32)
				DEFINE_MMX_BINARY_FUNCTION (vor, _mm_or_si64, M64_B32, M64_U32, M64_U32)
				DEFINE_MMX_BINARY_FUNCTION (vor, _mm_or_si64, M64_U32, M64_B32, M64_U32)
				DEFINE_MMX_BINARY_FUNCTION (vor, _mm_or_si64, M64_B32, M64_B32, M64_B32)

				DEFINE_MMX_BINARY_FUNCTION (vxor, _mm_xor_si64, M64_I8, M64_I8, M64_I8)
				DEFINE_MMX_BINARY_FUNCTION (vxor, _mm_xor_si64, M64_B8, M64_I8, M64_I8)
				DEFINE_MMX_BINARY_FUNCTION (vxor, _mm_xor_si64, M64_I8, M64_B8, M64_I8)
				DEFINE_MMX_BINARY_FUNCTION (vxor, _mm_xor_si64, M64_U8, M64_U8, M64_U8)
				DEFINE_MMX_BINARY_FUNCTION (vxor, _mm_xor_si64, M64_B8, M64_U8, M64_U8)
				DEFINE_MMX_BINARY_FUNCTION (vxor, _mm_xor_si64, M64_U8, M64_B8, M64_U8)
				DEFINE_MMX_BINARY_FUNCTION (vxor, _mm_xor_si64, M64_B8, M64_B8, M64_B8)

				DEFINE_MMX_BINARY_FUNCTION (vxor, _mm_xor_si64, M64_I16, M64_I16, M64_I16)
				DEFINE_MMX_BINARY_FUNCTION (vxor, _mm_xor_si64, M64_B16, M64_I16, M64_I16)
				DEFINE_MMX_BINARY_FUNCTION (vxor, _mm_xor_si64, M64_I16, M64_B16, M64_I16)
				DEFINE_MMX_BINARY_FUNCTION (vxor, _mm_xor_si64, M64_U16, M64_U16, M64_U16)
				DEFINE_MMX_BINARY_FUNCTION (vxor, _mm_xor_si64, M64_B16, M64_U16, M64_U16)
				DEFINE_MMX_BINARY_FUNCTION (vxor, _mm_xor_si64, M64_U16, M64_B16, M64_U16)
				DEFINE_MMX_BINARY_FUNCTION (vxor, _mm_xor_si64, M64_B16, M64_B16, M64_B16)

				DEFINE_MMX_BINARY_FUNCTION (vxor, _mm_xor_si64, M64_I32, M64_I32, M64_I32)
				DEFINE_MMX_BINARY_FUNCTION (vxor, _mm_xor_si64, M64_B32, M64_I32, M64_I32)
				DEFINE_MMX_BINARY_FUNCTION (vxor, _mm_xor_si64, M64_I32, M64_B32, M64_I32)
				DEFINE_MMX_BINARY_FUNCTION (vxor, _mm_xor_si64, M64_U32, M64_U32, M64_U32)
				DEFINE_MMX_BINARY_FUNCTION (vxor, _mm_xor_si64, M64_B32, M64_U32, M64_U32)
				DEFINE_MMX_BINARY_FUNCTION (vxor, _mm_xor_si64, M64_U32, M64_B32, M64_U32)
				DEFINE_MMX_BINARY_FUNCTION (vxor, _mm_xor_si64, M64_B32, M64_B32, M64_B32)

				// MMX Compare Intrinsics

				DEFINE_MMX_BINARY_FUNCTION (cmpeq, _mm_cmpeq_pi8, M64_I8, M64_I8, M64_B8)
				DEFINE_MMX_BINARY_FUNCTION (cmpeq, _mm_cmpeq_pi8, M64_U8, M64_U8, M64_B8)
				DEFINE_MMX_BINARY_FUNCTION (cmpeq, _mm_cmpeq_pi8, M64_B8, M64_B8, M64_B8)
				DEFINE_MMX_BINARY_FUNCTION (cmpeq, _mm_cmpeq_pi16, M64_I16, M64_I16, M64_B16)
				DEFINE_MMX_BINARY_FUNCTION (cmpeq, _mm_cmpeq_pi16, M64_U16, M64_U16, M64_B16)
				DEFINE_MMX_BINARY_FUNCTION (cmpeq, _mm_cmpeq_pi16, M64_B16, M64_B16, M64_B16)
				DEFINE_MMX_BINARY_FUNCTION (cmpeq, _mm_cmpeq_pi32, M64_I32, M64_I32, M64_B32)
				DEFINE_MMX_BINARY_FUNCTION (cmpeq, _mm_cmpeq_pi32, M64_U32, M64_U32, M64_B32)
				DEFINE_MMX_BINARY_FUNCTION (cmpeq, _mm_cmpeq_pi32, M64_B32, M64_B32, M64_B32)

				DEFINE_MMX_BINARY_FUNCTION (cmpgt, _mm_cmpgt_pi8, M64_I8, M64_I8, M64_B8)
				DEFINE_MMX_BINARY_FUNCTION (cmpgt, _mm_cmpgt_pi16, M64_I16, M64_I16, M64_B16)
				DEFINE_MMX_BINARY_FUNCTION (cmpgt, _mm_cmpgt_pi32, M64_I32, M64_I32, M64_B32)

				#endif

				#if defined(__AVX__) || defined(__AVX2__)

				// AVX Floating-Point Arithmetic Intrinsics

				DEFINE_MMX_BINARY_FUNCTION (add, _mm_add_ps, M128_F32, M128_F32, M128_F32)
				DEFINE_MMX_BINARY_FUNCTION (div, _mm_div_ps, M128_F32, M128_F32, M128_F32)
				DEFINE_MMX_BINARY_FUNCTION (max, _mm_max_ps, M128_F32, M128_F32, M128_F32)
				DEFINE_MMX_BINARY_FUNCTION (min, _mm_min_ps, M128_F32, M128_F32, M128_F32)
				DEFINE_MMX_BINARY_FUNCTION (mul, _mm_mul_ps, M128_F32, M128_F32, M128_F32)
				DEFINE_MMX_UNARY_FUNCTION (rcp, _mm_rcp_ps, M128_F32, M128_F32)
				DEFINE_MMX_UNARY_FUNCTION (rsqrt, _mm_rsqrt_ps, M128_F32, M128_F32)
				DEFINE_MMX_UNARY_FUNCTION (sqrt, _mm_sqrt_ps, M128_F32, M128_F32)
				DEFINE_MMX_BINARY_FUNCTION (sub, _mm_sub_ps, M128_F32, M128_F32, M128_F32)

				DEFINE_MMX_BINARY_FUNCTION (add, _mm256_add_ps, M256_F32, M256_F32, M256_F32)
				DEFINE_MMX_BINARY_FUNCTION (div, _mm256_div_ps, M256_F32, M256_F32, M256_F32)
				DEFINE_MMX_BINARY_FUNCTION (max, _mm256_max_ps, M256_F32, M256_F32, M256_F32)
				DEFINE_MMX_BINARY_FUNCTION (min, _mm256_min_ps, M256_F32, M256_F32, M256_F32)
				DEFINE_MMX_BINARY_FUNCTION (mul, _mm256_mul_ps, M256_F32, M256_F32, M256_F32)
				DEFINE_MMX_UNARY_FUNCTION (rcp, _mm256_rcp_ps, M256_F32, M256_F32)
				DEFINE_MMX_UNARY_FUNCTION (rsqrt, _mm256_rsqrt_ps, M256_F32, M256_F32)
				DEFINE_MMX_UNARY_FUNCTION (sqrt, _mm256_sqrt_ps, M256_F32, M256_F32)
				DEFINE_MMX_BINARY_FUNCTION (sub, _mm256_sub_ps, M256_F32, M256_F32, M256_F32)

				// AVX Logical Intrinsics

				DEFINE_MMX_BINARY_FUNCTION (vand, _mm_and_ps, M128_F32, M128_F32, M128_F32)
				DEFINE_MMX_BINARY_FUNCTION (vand, _mm_and_ps, M128_F32, M128_B32, M128_F32)
				DEFINE_MMX_BINARY_FUNCTION (vand, _mm_and_ps, M128_B32, M128_F32, M128_F32)
				DEFINE_MMX_BINARY_FUNCTION (vand, _mm_and_ps, M128_B32, M128_B32, M128_B32)

				DEFINE_MMX_BINARY_FUNCTION (andnot, _mm_andnot_ps, M128_F32, M128_F32, M128_F32)
				DEFINE_MMX_BINARY_FUNCTION (andnot, _mm_andnot_ps, M128_F32, M128_B32, M128_F32)
				DEFINE_MMX_BINARY_FUNCTION (andnot, _mm_andnot_ps, M128_B32, M128_F32, M128_F32)
				DEFINE_MMX_BINARY_FUNCTION (andnot, _mm_andnot_ps, M128_B32, M128_B32, M128_B32)

				DEFINE_MMX_BINARY_FUNCTION (vor, _mm_or_ps, M128_F32, M128_F32, M128_F32)
				DEFINE_MMX_BINARY_FUNCTION (vor, _mm_or_ps, M128_F32, M128_B32, M128_F32)
				DEFINE_MMX_BINARY_FUNCTION (vor, _mm_or_ps, M128_B32, M128_F32, M128_F32)
				DEFINE_MMX_BINARY_FUNCTION (vor, _mm_or_ps, M128_B32, M128_B32, M128_B32)

				DEFINE_MMX_BINARY_FUNCTION (vxor, _mm_xor_ps, M128_F32, M128_F32, M128_F32)
				DEFINE_MMX_BINARY_FUNCTION (vxor, _mm_xor_ps, M128_F32, M128_B32, M128_F32)
				DEFINE_MMX_BINARY_FUNCTION (vxor, _mm_xor_ps, M128_B32, M128_F32, M128_F32)
				DEFINE_MMX_BINARY_FUNCTION (vxor, _mm_xor_ps, M128_B32, M128_B32, M128_B32)

				DEFINE_MMX_BINARY_FUNCTION (vand, _mm256_and_ps, M256_F32, M256_F32, M256_F32)
				DEFINE_MMX_BINARY_FUNCTION (vand, _mm256_and_ps, M256_F32, M256_B32, M256_F32)
				DEFINE_MMX_BINARY_FUNCTION (vand, _mm256_and_ps, M256_B32, M256_F32, M256_F32)
				DEFINE_MMX_BINARY_FUNCTION (vand, _mm256_and_ps, M256_B32, M256_B32, M256_B32)

				DEFINE_MMX_BINARY_FUNCTION (andnot, _mm256_andnot_ps, M256_F32, M256_F32, M256_F32)
				DEFINE_MMX_BINARY_FUNCTION (andnot, _mm256_andnot_ps, M256_F32, M256_B32, M256_F32)
				DEFINE_MMX_BINARY_FUNCTION (andnot, _mm256_andnot_ps, M256_B32, M256_F32, M256_F32)
				DEFINE_MMX_BINARY_FUNCTION (andnot, _mm256_andnot_ps, M256_B32, M256_B32, M256_B32)

				DEFINE_MMX_BINARY_FUNCTION (vor, _mm256_or_ps, M256_F32, M256_F32, M256_F32)
				DEFINE_MMX_BINARY_FUNCTION (vor, _mm256_or_ps, M256_F32, M256_B32, M256_F32)
				DEFINE_MMX_BINARY_FUNCTION (vor, _mm256_or_ps, M256_B32, M256_F32, M256_F32)
				DEFINE_MMX_BINARY_FUNCTION (vor, _mm256_or_ps, M256_B32, M256_B32, M256_B32)

				DEFINE_MMX_BINARY_FUNCTION (vxor, _mm256_xor_ps, M256_F32, M256_F32, M256_F32)
				DEFINE_MMX_BINARY_FUNCTION (vxor, _mm256_xor_ps, M256_F32, M256_B32, M256_F32)
				DEFINE_MMX_BINARY_FUNCTION (vxor, _mm256_xor_ps, M256_B32, M256_F32, M256_F32)
				DEFINE_MMX_BINARY_FUNCTION (vxor, _mm256_xor_ps, M256_B32, M256_B32, M256_B32)

				// SSE Comparison Intrinsics

				DEFINE_MMX_BINARY_FUNCTION (cmpeq, _mm_cmpeq_ps, M128_F32, M128_F32, M128_B32)
				DEFINE_MMX_BINARY_FUNCTION (cmplt, _mm_cmplt_ps, M128_F32, M128_F32, M128_B32)
				DEFINE_MMX_BINARY_FUNCTION (cmple, _mm_cmple_ps, M128_F32, M128_F32, M128_B32)
				DEFINE_MMX_BINARY_FUNCTION (cmpgt, _mm_cmpgt_ps, M128_F32, M128_F32, M128_B32)
				DEFINE_MMX_BINARY_FUNCTION (cmpge, _mm_cmpge_ps, M128_F32, M128_F32, M128_B32)
				DEFINE_MMX_BINARY_FUNCTION (cmpneq, _mm_cmpneq_ps, M128_F32, M128_F32, M128_B32)
				DEFINE_MMX_BINARY_FUNCTION (cmpnlt, _mm_cmpnlt_ps, M128_F32, M128_F32, M128_B32)
				DEFINE_MMX_BINARY_FUNCTION (cmpnle, _mm_cmpnle_ps, M128_F32, M128_F32, M128_B32)
				DEFINE_MMX_BINARY_FUNCTION (cmpngt, _mm_cmpngt_ps, M128_F32, M128_F32, M128_B32)
				DEFINE_MMX_BINARY_FUNCTION (cmpnge, _mm_cmpnge_ps, M128_F32, M128_F32, M128_B32)
				DEFINE_MMX_BINARY_FUNCTION (cmpord, _mm_cmpord_ps, M128_F32, M128_F32, M128_B32)
				DEFINE_MMX_BINARY_FUNCTION (cmpunord, _mm_cmpunord_ps, M128_F32, M128_F32, M128_B32)

				DEFINE_MMX_BINARY_FUNCTION (cmpeq, _mm_cmpeq_ps, M128_B32, M128_B32, M128_B32)

//! AVX has only a single _cmp_pX function, taking an opcode that determines its exact behaviour
#define DEFINE_AVX_CMP_FUNCTION(FN,INTR,OPCODE,ARG1,ARG2,RESULT)						\
template <> struct FN##_function <ARG1, ARG2 >									\
	{																	\
		typedef ARG1 first_argument_type;										\
		typedef ARG2 second_argument_type;										\
		typedef RESULT result_type;											\
																		\
		INLINE const result_type operator()									\
			(const first_argument_type& lhs, const second_argument_type& rhs) const	\
			{															\
				return INTR (lhs.data (), data_of (rhs), OPCODE);					\
			}															\
	};

				DEFINE_AVX_CMP_FUNCTION(cmpeq, _mm256_cmp_ps,_CMP_EQ_OQ, M256_B32, M256_B32, M256_B32)
				DEFINE_AVX_CMP_FUNCTION(cmpeq, _mm256_cmp_ps,_CMP_EQ_OQ, M256_F32, M256_F32, M256_B32)
				DEFINE_AVX_CMP_FUNCTION(cmpneq, _mm256_cmp_ps,_CMP_NEQ_OQ, M256_F32, M256_F32, M256_B32)
				DEFINE_AVX_CMP_FUNCTION(cmpgt, _mm256_cmp_ps,_CMP_GT_OQ, M256_F32, M256_F32, M256_B32)
				DEFINE_AVX_CMP_FUNCTION(cmpge, _mm256_cmp_ps,_CMP_GE_OQ, M256_F32, M256_F32, M256_B32)
				DEFINE_AVX_CMP_FUNCTION(cmpngt, _mm256_cmp_ps,_CMP_NGT_UQ, M256_F32, M256_F32, M256_B32)
				DEFINE_AVX_CMP_FUNCTION(cmpnge, _mm256_cmp_ps,_CMP_NGE_UQ, M256_F32, M256_F32, M256_B32)
				DEFINE_AVX_CMP_FUNCTION(cmplt, _mm256_cmp_ps,_CMP_LT_OQ, M256_F32, M256_F32, M256_B32)
				DEFINE_AVX_CMP_FUNCTION(cmple, _mm256_cmp_ps,_CMP_LT_OQ, M256_F32, M256_F32, M256_B32)
				DEFINE_AVX_CMP_FUNCTION(cmpnlt, _mm256_cmp_ps,_CMP_NLT_UQ, M256_F32, M256_F32, M256_B32)
				DEFINE_AVX_CMP_FUNCTION(cmpnle, _mm256_cmp_ps,_CMP_NLT_UQ, M256_F32, M256_F32, M256_B32)
				DEFINE_AVX_CMP_FUNCTION(cmpord, _mm256_cmp_ps,_CMP_ORD_Q, M256_F32, M256_F32, M256_B32)
				DEFINE_AVX_CMP_FUNCTION(cmpunord, _mm256_cmp_ps,_CMP_UNORD_Q, M256_F32, M256_F32, M256_B32)

				// SSE Conversion Intrinsics

				DEFINE_MMX_UNARY_CONVERSION (cvt, _mm_cvtps_pi32, M128_F32, M64_I32)
				DEFINE_MMX_UNARY_CONVERSION (cvtt, _mm_cvttps_pi32, M128_F32, M64_I32)
				DEFINE_MMX_BINARY_CONVERSION (cvt2, _mm_cvtpi32_ps, M128_F32, M64_I32, M128_F32)
				DEFINE_MMX_UNARY_CONVERSION (cvt, _mm_cvtpi16_ps, M64_I16, M128_F32)
				DEFINE_MMX_UNARY_CONVERSION (cvt, _mm_cvtpu16_ps, M64_U16, M128_F32)
				DEFINE_MMX_UNARY_CONVERSION (cvt, _mm_cvtpi8_ps, M64_I8, M128_F32)
				DEFINE_MMX_UNARY_CONVERSION (cvt, _mm_cvtpu8_ps, M64_U8, M128_F32)
				DEFINE_MMX_BINARY_CONVERSION (cvt2, _mm_cvtpi32x2_ps, M64_I32, M64_I32, M128_F32)
				DEFINE_MMX_UNARY_CONVERSION (cvt, _mm_cvtps_pi16, M128_F32, M64_I16)
				DEFINE_MMX_UNARY_CONVERSION (cvt, _mm_cvtps_pi8, M128_F32, M64_I8)

				// AVX Memory Intrinsics

				DEFINE_MMX_LOAD (load, _mm_load_ps, float, float, M128_F32)
				DEFINE_MMX_LOAD (loadu, _mm_loadu_ps, float, float, M128_F32)
				DEFINE_MMX_LOAD (loadd, _mm256_load_ps, float, float, M256_F32)
				DEFINE_MMX_LOAD (loaddu, _mm256_loadu_ps, float, float, M256_F32)
				DEFINE_MMX_LOAD (loadr, _mm_loadr_ps, float, float, M128_F32)

				DEFINE_MMX_STORE (store, _mm_store_ps, float, float, M128_F32)
				DEFINE_MMX_STORE (storeu, _mm_storeu_ps, float, float, M128_F32)
				DEFINE_MMX_STORE (store, _mm256_store_ps, float, float, M256_F32)
				DEFINE_MMX_STORE (storeu, _mm256_storeu_ps, float, float, M256_F32)
				DEFINE_MMX_STORE (storer, _mm_storer_ps, float, float, M128_F32)

				// SSE2/AVX Miscellaneous Intrinsics

				DEFINE_MMX_BINARY_FUNCTION (movehl, _mm_movehl_ps, M128_F32, M128_F32, M128_F32)
				DEFINE_MMX_BINARY_FUNCTION (movehl, _mm_movehl_ps, M128_B32, M128_B32, M128_B32)

				DEFINE_MMX_BINARY_FUNCTION (movelh, _mm_movelh_ps, M128_F32, M128_F32, M128_F32)
				DEFINE_MMX_BINARY_FUNCTION (movelh, _mm_movelh_ps, M128_B32, M128_B32, M128_B32)

				DEFINE_MMX_UNARY_FUNCTION (movemask, _mm_movemask_ps, M128_F32, int)
				DEFINE_MMX_UNARY_FUNCTION (movemask, _mm_movemask_ps, M128_B32, int)

				DEFINE_MMX_BINARY_SHUFFLE4 (shuffles, _mm_shuffle_ps, M128_F32, M128_F32, M128_F32)
				DEFINE_MMX_BINARY_SHUFFLE4 (shuffles, _mm_shuffle_ps, M128_B32, M128_B32, M128_B32)

				DEFINE_MMX_BINARY_FUNCTION (unpackhi, _mm_unpackhi_ps, M128_F32, M128_F32, M128_F32)
				DEFINE_MMX_BINARY_FUNCTION (unpackhi, _mm_unpackhi_ps, M128_B32, M128_B32, M128_B32)

				DEFINE_MMX_BINARY_FUNCTION (unpacklo, _mm_unpacklo_ps, M128_F32, M128_F32, M128_F32)
				DEFINE_MMX_BINARY_FUNCTION (unpacklo, _mm_unpacklo_ps, M128_B32, M128_B32, M128_B32)

				DEFINE_MMX_UNARY_FUNCTION (movemask, _mm256_movemask_ps, M256_F32, int)
				DEFINE_MMX_UNARY_FUNCTION (movemask, _mm256_movemask_ps, M256_B32, int)

				DEFINE_MMX_BINARY_SHUFFLE4 (shuffles, _mm256_shuffle_ps, M256_F32, M256_F32, M256_F32)
				DEFINE_MMX_BINARY_SHUFFLE4 (shuffles, _mm256_shuffle_ps, M256_B32, M256_B32, M256_B32)

				DEFINE_MMX_BINARY_FUNCTION (unpackhi, _mm256_unpackhi_ps, M256_F32, M256_F32, M256_F32)
				DEFINE_MMX_BINARY_FUNCTION (unpackhi, _mm256_unpackhi_ps, M256_B32, M256_B32, M256_B32)

				DEFINE_MMX_BINARY_FUNCTION (unpacklo, _mm256_unpacklo_ps, M256_F32, M256_F32, M256_F32)
				DEFINE_MMX_BINARY_FUNCTION (unpacklo, _mm256_unpacklo_ps, M256_B32, M256_B32, M256_B32)

				// SSE Integer Intrinsics

				DEFINE_MMX_UNARY_FUNCTION_WITH_LITERAL (extract, _mm_extract_pi16, M64_I16, short)
				DEFINE_MMX_UNARY_FUNCTION_WITH_LITERAL (extract, _mm_extract_pi16, M64_U16, unsigned short)
				DEFINE_MMX_UNARY_FUNCTION_WITH_LITERAL (extract, _mm_extract_pi16, M64_B16, boolean <short>)

				DEFINE_MMX_BINARY_FUNCTION_WITH_LITERAL (insert, _mm_insert_pi16, M64_I16, short, M64_I16)
				DEFINE_MMX_BINARY_FUNCTION_WITH_LITERAL (insert, _mm_insert_pi16, M64_U16, unsigned short, M64_U16)
				DEFINE_MMX_BINARY_FUNCTION_WITH_LITERAL (insert, _mm_insert_pi16, M64_B16, boolean <short>, M64_B16)

				DEFINE_MMX_BINARY_FUNCTION (max, _mm_max_pi16, M64_I16, M64_I16, M64_I16)
				DEFINE_MMX_BINARY_FUNCTION (max, _mm_max_pu8, M64_U8, M64_U8, M64_U8)

				DEFINE_MMX_BINARY_FUNCTION (min, _mm_min_pi16, M64_I16, M64_I16, M64_I16)
				DEFINE_MMX_BINARY_FUNCTION (min, _mm_min_pu8, M64_U8, M64_U8, M64_U8)

				DEFINE_MMX_BINARY_FUNCTION (mulhi, _mm_mulhi_pu16, M64_U16, M64_U16, M64_U16)

				DEFINE_MMX_UNARY_FUNCTION (movemask, _mm_movemask_pi8, M64_I8, unsigned int)
				DEFINE_MMX_UNARY_FUNCTION (movemask, _mm_movemask_pi8, M64_U8, unsigned int)
				DEFINE_MMX_UNARY_FUNCTION (movemask, _mm_movemask_pi8, M64_B8, unsigned int)

				DEFINE_MMX_BINARY_FUNCTION (avg, _mm_avg_pu8, M64_U8, M64_U8, M64_U8)
				DEFINE_MMX_BINARY_FUNCTION (avg, _mm_avg_pu16, M64_U16, M64_U16, M64_U16)

				DEFINE_MMX_BINARY_FUNCTION (sad, _mm_sad_pu8, M64_U8, M64_U8, M64_U16)

				DEFINE_MMX_UNARY_SHUFFLE4 (shuffle, _mm_shuffle_pi16, M64_I16, M64_I16)
				DEFINE_MMX_UNARY_SHUFFLE4 (shuffle, _mm_shuffle_pi16, M64_U16, M64_U16)
				DEFINE_MMX_UNARY_SHUFFLE4 (shuffle, _mm_shuffle_pi16, M64_B16, M64_B16)

				#endif

				#if defined(__SSE2__) || defined(__AVX__) || defined(__AVX2__)

				// AVX Floating-Point Arithmetic Intrinsics

				DEFINE_MMX_BINARY_FUNCTION (add, _mm_add_pd, M128D_F64, M128D_F64, M128D_F64)
				DEFINE_MMX_BINARY_FUNCTION (div, _mm_div_pd, M128D_F64, M128D_F64, M128D_F64)
				DEFINE_MMX_BINARY_FUNCTION (max, _mm_max_pd, M128D_F64, M128D_F64, M128D_F64)
				DEFINE_MMX_BINARY_FUNCTION (min, _mm_min_pd, M128D_F64, M128D_F64, M128D_F64)
				DEFINE_MMX_BINARY_FUNCTION (mul, _mm_mul_pd, M128D_F64, M128D_F64, M128D_F64)
				DEFINE_MMX_UNARY_FUNCTION (sqrt, _mm_sqrt_pd, M128D_F64, M128D_F64)
				DEFINE_MMX_BINARY_FUNCTION (sub, _mm_sub_pd, M128D_F64, M128D_F64, M128D_F64)

				DEFINE_MMX_BINARY_FUNCTION (add, _mm256_add_pd, M256D_F64, M256D_F64, M256D_F64)
				DEFINE_MMX_BINARY_FUNCTION (div, _mm256_div_pd, M256D_F64, M256D_F64, M256D_F64)
				DEFINE_MMX_BINARY_FUNCTION (max, _mm256_max_pd, M256D_F64, M256D_F64, M256D_F64)
				DEFINE_MMX_BINARY_FUNCTION (min, _mm256_min_pd, M256D_F64, M256D_F64, M256D_F64)
				DEFINE_MMX_BINARY_FUNCTION (mul, _mm256_mul_pd, M256D_F64, M256D_F64, M256D_F64)
				DEFINE_MMX_UNARY_FUNCTION (sqrt, _mm256_sqrt_pd, M256D_F64, M256D_F64)
				DEFINE_MMX_BINARY_FUNCTION (sub, _mm256_sub_pd, M256D_F64, M256D_F64, M256D_F64)

				// AVX Floating-Point Logical Intrinsics

				DEFINE_MMX_BINARY_FUNCTION (vand, _mm_and_pd, M128D_F64, M128D_F64, M128D_F64)
				DEFINE_MMX_BINARY_FUNCTION (vand, _mm_and_pd, M128D_F64, M128D_B64, M128D_F64)
				DEFINE_MMX_BINARY_FUNCTION (vand, _mm_and_pd, M128D_B64, M128D_F64, M128D_F64)
				DEFINE_MMX_BINARY_FUNCTION (vand, _mm_and_pd, M128D_B64, M128D_B64, M128D_B64)

				DEFINE_MMX_BINARY_FUNCTION (andnot, _mm_andnot_pd, M128D_F64, M128D_F64, M128D_F64)
				DEFINE_MMX_BINARY_FUNCTION (andnot, _mm_andnot_pd, M128D_F64, M128D_B64, M128D_F64)
				DEFINE_MMX_BINARY_FUNCTION (andnot, _mm_andnot_pd, M128D_B64, M128D_F64, M128D_F64)
				DEFINE_MMX_BINARY_FUNCTION (andnot, _mm_andnot_pd, M128D_B64, M128D_B64, M128D_B64)

				DEFINE_MMX_BINARY_FUNCTION (vor, _mm_or_pd, M128D_F64, M128D_F64, M128D_F64)
				DEFINE_MMX_BINARY_FUNCTION (vor, _mm_or_pd, M128D_F64, M128D_B64, M128D_F64)
				DEFINE_MMX_BINARY_FUNCTION (vor, _mm_or_pd, M128D_B64, M128D_F64, M128D_F64)
				DEFINE_MMX_BINARY_FUNCTION (vor, _mm_or_pd, M128D_B64, M128D_B64, M128D_B64)

				DEFINE_MMX_BINARY_FUNCTION (vxor, _mm_xor_pd, M128D_F64, M128D_F64, M128D_F64)
				DEFINE_MMX_BINARY_FUNCTION (vxor, _mm_xor_pd, M128D_F64, M128D_B64, M128D_F64)
				DEFINE_MMX_BINARY_FUNCTION (vxor, _mm_xor_pd, M128D_B64, M128D_F64, M128D_F64)
				DEFINE_MMX_BINARY_FUNCTION (vxor, _mm_xor_pd, M128D_B64, M128D_B64, M128D_B64)

				DEFINE_MMX_BINARY_FUNCTION (vand, _mm256_and_pd, M256D_F64, M256D_F64, M256D_F64)
				DEFINE_MMX_BINARY_FUNCTION (vand, _mm256_and_pd, M256D_F64, M256D_B64, M256D_F64)
				DEFINE_MMX_BINARY_FUNCTION (vand, _mm256_and_pd, M256D_B64, M256D_F64, M256D_F64)
				DEFINE_MMX_BINARY_FUNCTION (vand, _mm256_and_pd, M256D_B64, M256D_B64, M256D_B64)

				DEFINE_MMX_BINARY_FUNCTION (andnot, _mm256_andnot_pd, M256D_F64, M256D_F64, M256D_F64)
				DEFINE_MMX_BINARY_FUNCTION (andnot, _mm256_andnot_pd, M256D_F64, M256D_B64, M256D_F64)
				DEFINE_MMX_BINARY_FUNCTION (andnot, _mm256_andnot_pd, M256D_B64, M256D_F64, M256D_F64)
				DEFINE_MMX_BINARY_FUNCTION (andnot, _mm256_andnot_pd, M256D_B64, M256D_B64, M256D_B64)

				DEFINE_MMX_BINARY_FUNCTION (vor, _mm256_or_pd, M256D_F64, M256D_F64, M256D_F64)
				DEFINE_MMX_BINARY_FUNCTION (vor, _mm256_or_pd, M256D_F64, M256D_B64, M256D_F64)
				DEFINE_MMX_BINARY_FUNCTION (vor, _mm256_or_pd, M256D_B64, M256D_F64, M256D_F64)
				DEFINE_MMX_BINARY_FUNCTION (vor, _mm256_or_pd, M256D_B64, M256D_B64, M256D_B64)

				DEFINE_MMX_BINARY_FUNCTION (vxor, _mm256_xor_pd, M256D_F64, M256D_F64, M256D_F64)
				DEFINE_MMX_BINARY_FUNCTION (vxor, _mm256_xor_pd, M256D_F64, M256D_B64, M256D_F64)
				DEFINE_MMX_BINARY_FUNCTION (vxor, _mm256_xor_pd, M256D_B64, M256D_F64, M256D_F64)
				DEFINE_MMX_BINARY_FUNCTION (vxor, _mm256_xor_pd, M256D_B64, M256D_B64, M256D_B64)

				// SSE2 Floating-Point Comparison Intrinsics

				DEFINE_MMX_BINARY_FUNCTION (cmpeq, _mm_cmpeq_pd, M128D_F64, M128D_F64, M128D_B64)
				DEFINE_MMX_BINARY_FUNCTION (cmplt, _mm_cmplt_pd, M128D_F64, M128D_F64, M128D_B64)
				DEFINE_MMX_BINARY_FUNCTION (cmple, _mm_cmple_pd, M128D_F64, M128D_F64, M128D_B64)
				DEFINE_MMX_BINARY_FUNCTION (cmpgt, _mm_cmpgt_pd, M128D_F64, M128D_F64, M128D_B64)
				DEFINE_MMX_BINARY_FUNCTION (cmpge, _mm_cmpge_pd, M128D_F64, M128D_F64, M128D_B64)
				DEFINE_MMX_BINARY_FUNCTION (cmpneq, _mm_cmpneq_pd, M128D_F64, M128D_F64, M128D_B64)
				DEFINE_MMX_BINARY_FUNCTION (cmpnlt, _mm_cmpnlt_pd, M128D_F64, M128D_F64, M128D_B64)
				DEFINE_MMX_BINARY_FUNCTION (cmpnle, _mm_cmpnle_pd, M128D_F64, M128D_F64, M128D_B64)
				DEFINE_MMX_BINARY_FUNCTION (cmpngt, _mm_cmpngt_pd, M128D_F64, M128D_F64, M128D_B64)
				DEFINE_MMX_BINARY_FUNCTION (cmpnge, _mm_cmpnge_pd, M128D_F64, M128D_F64, M128D_B64)
				DEFINE_MMX_BINARY_FUNCTION (cmpord, _mm_cmpord_pd, M128D_F64, M128D_F64, M128D_B64)
				DEFINE_MMX_BINARY_FUNCTION (cmpunord, _mm_cmpunord_pd, M128D_F64, M128D_F64, M128D_B64)

				DEFINE_MMX_BINARY_FUNCTION (cmpeq, _mm_cmpeq_pd, M128D_B64, M128D_B64, M128D_B64)

				DEFINE_AVX_CMP_FUNCTION(cmpeq, _mm256_cmp_pd,_CMP_EQ_OQ, M256D_B64, M256D_B64, M256D_B64)
				DEFINE_AVX_CMP_FUNCTION(cmpeq, _mm256_cmp_pd,_CMP_EQ_OQ, M256D_F64, M256D_F64, M256D_B64)
				DEFINE_AVX_CMP_FUNCTION(cmpneq, _mm256_cmp_pd,_CMP_NEQ_OQ, M256D_F64, M256D_F64, M256D_B64)
				DEFINE_AVX_CMP_FUNCTION(cmpgt, _mm256_cmp_pd,_CMP_GT_OQ, M256D_F64, M256D_F64, M256D_B64)
				DEFINE_AVX_CMP_FUNCTION(cmpge, _mm256_cmp_pd,_CMP_GE_OQ, M256D_F64, M256D_F64, M256D_B64)
				DEFINE_AVX_CMP_FUNCTION(cmpngt, _mm256_cmp_pd,_CMP_NGT_UQ, M256D_F64, M256D_F64, M256D_B64)
				DEFINE_AVX_CMP_FUNCTION(cmpnge, _mm256_cmp_pd,_CMP_NGE_UQ, M256D_F64, M256D_F64, M256D_B64)
				DEFINE_AVX_CMP_FUNCTION(cmplt, _mm256_cmp_pd,_CMP_LT_OQ, M256D_F64, M256D_F64, M256D_B64)
				DEFINE_AVX_CMP_FUNCTION(cmple, _mm256_cmp_pd,_CMP_LT_OQ, M256D_F64, M256D_F64, M256D_B64)
				DEFINE_AVX_CMP_FUNCTION(cmpnlt, _mm256_cmp_pd,_CMP_NLT_UQ, M256D_F64, M256D_F64, M256D_B64)
				DEFINE_AVX_CMP_FUNCTION(cmpnle, _mm256_cmp_pd,_CMP_NLT_UQ, M256D_F64, M256D_F64, M256D_B64)
				DEFINE_AVX_CMP_FUNCTION(cmpord, _mm256_cmp_pd,_CMP_ORD_Q, M256D_F64, M256D_F64, M256D_B64)
				DEFINE_AVX_CMP_FUNCTION(cmpunord, _mm256_cmp_pd,_CMP_UNORD_Q, M256D_F64, M256D_F64, M256D_B64)


				// AVX Floating-Point Conversion

				DEFINE_MMX_UNARY_CONVERSION (cvt, _mm_cvtpd_ps, M128D_F64, M128_F32)
				DEFINE_MMX_UNARY_CONVERSION (cvt, _mm_cvtps_pd, M128_F32, M128D_F64)
				DEFINE_MMX_UNARY_CONVERSION (cvt, _mm_cvtepi32_pd, M128I_I32, M128D_F64)
				DEFINE_MMX_UNARY_CONVERSION (cvt, _mm_cvtpd_epi32, M128D_F64, M128I_I32)
				DEFINE_MMX_UNARY_CONVERSION (cvtt, _mm_cvttpd_epi32, M128D_F64, M128I_I32)
				DEFINE_MMX_UNARY_CONVERSION (cvtt, _mm_cvtepi32_pd, M128I_I32, M128D_F64)
				DEFINE_MMX_UNARY_CONVERSION (cvt, _mm_cvtepi32_ps, M128I_I32, M128_F32)
				DEFINE_MMX_UNARY_CONVERSION (cvt, _mm_cvtps_epi32, M128_F32, M128I_I32)
				DEFINE_MMX_UNARY_CONVERSION (cvtt, _mm_cvttps_epi32, M128_F32, M128I_I32)
				DEFINE_MMX_UNARY_CONVERSION (cvt, _mm_cvtpd_pi32, M128D_F64, M64_I32)
				DEFINE_MMX_UNARY_CONVERSION (cvtt, _mm_cvttpd_pi32, M128D_F64, M64_I32)
				DEFINE_MMX_UNARY_CONVERSION (cvt, _mm_cvtpi32_pd, M64_I32, M128D_F64)

				DEFINE_MMX_UNARY_CONVERSION (cvt, _mm256_cvtepi32_pd, M128I_I32, M256D_F64)
				DEFINE_MMX_UNARY_CONVERSION (cvt, _mm256_cvtepi32_ps, M256I_I32, M256_F32)
				DEFINE_MMX_UNARY_CONVERSION (cvt, _mm256_cvtps_pd, M128_F32, M256D_F64)	//!!
				DEFINE_MMX_UNARY_CONVERSION (cvt, _mm256_cvtpd_ps, M256D_F64, M128_F32)
				DEFINE_MMX_UNARY_CONVERSION (cvt, _mm256_cvtps_epi32, M256_F32, M256I_I32)
				DEFINE_MMX_UNARY_CONVERSION (cvt, _mm256_cvtpd_epi32, M256D_F64, M128I_I32)
				DEFINE_MMX_UNARY_CONVERSION (cvtt, _mm256_cvttpd_epi32, M256D_F64, M128I_I32)
				DEFINE_MMX_UNARY_CONVERSION (cvtt, _mm256_cvttps_epi32, M256_F32, M256I_I32)

				// AVX Floating-Point Memory Intrinsics

				DEFINE_MMX_LOAD (load, _mm_load_pd, double, double, M128D_F64)
				DEFINE_MMX_LOAD (loadu, _mm_loadu_pd, double, double, M128D_F64)
				DEFINE_MMX_LOAD (loadr, _mm_loadr_pd, double, double, M128D_F64)

				DEFINE_MMX_STORE (store, _mm_store_pd, double, double, M128D_F64)
				DEFINE_MMX_STORE (storeu, _mm_storeu_pd, double, double, M128D_F64)
				DEFINE_MMX_STORE (storer, _mm_storer_pd, double, double, M128D_F64)

				DEFINE_MMX_LOAD (loadd, _mm256_load_pd, double, double, M256D_F64)
				DEFINE_MMX_LOAD (loaddu, _mm256_loadu_pd, double, double, M256D_F64)

				DEFINE_MMX_STORE (store, _mm256_store_pd, double, double, M256D_F64)
				DEFINE_MMX_STORE (storeu, _mm256_storeu_pd, double, double, M256D_F64)

				// AVX Floating-Point Miscellaneous Intrinsics

				DEFINE_MMX_BINARY_FUNCTION (unpackhi, _mm_unpackhi_pd, M128D_F64, M128D_F64, M128D_F64)
				DEFINE_MMX_BINARY_FUNCTION (unpackhi, _mm_unpackhi_pd, M128D_B64, M128D_B64, M128D_B64)
				DEFINE_MMX_BINARY_FUNCTION (unpacklo, _mm_unpacklo_pd, M128D_F64, M128D_F64, M128D_F64)
				DEFINE_MMX_BINARY_FUNCTION (unpacklo, _mm_unpacklo_pd, M128D_B64, M128D_B64, M128D_B64)
				DEFINE_MMX_UNARY_FUNCTION (movemask, _mm_movemask_pd, M128D_F64, unsigned int)
				DEFINE_MMX_UNARY_FUNCTION (movemask, _mm_movemask_pd, M128D_B64, unsigned int)
				DEFINE_MMX_BINARY_SHUFFLE2 (shuffled, _mm_shuffle_pd, M128D_F64, M128D_F64, M128D_F64)
				DEFINE_MMX_BINARY_SHUFFLE2 (shuffled, _mm_shuffle_pd, M128D_B64, M128D_B64, M128D_B64)

				DEFINE_MMX_BINARY_FUNCTION (unpackhi, _mm256_unpackhi_pd, M256D_F64, M256D_F64, M256D_F64)
				DEFINE_MMX_BINARY_FUNCTION (unpackhi, _mm256_unpackhi_pd, M256D_B64, M256D_B64, M256D_B64)
				DEFINE_MMX_BINARY_FUNCTION (unpacklo, _mm256_unpacklo_pd, M256D_F64, M256D_F64, M256D_F64)
				DEFINE_MMX_BINARY_FUNCTION (unpacklo, _mm256_unpacklo_pd, M256D_B64, M256D_B64, M256D_B64)
				DEFINE_MMX_UNARY_FUNCTION (movemask, _mm256_movemask_pd, M256D_F64, unsigned int)
				DEFINE_MMX_UNARY_FUNCTION (movemask, _mm256_movemask_pd, M256D_B64, unsigned int)
				DEFINE_MMX_BINARY_SHUFFLE4 (shuffledd, _mm256_shuffle_pd, M256D_F64, M256D_F64, M256D_F64)
				DEFINE_MMX_BINARY_SHUFFLE4 (shuffledd, _mm256_shuffle_pd, M256D_B64, M256D_B64, M256D_B64)

				// SSE2 Integer Arithmetic

				DEFINE_MMX_BINARY_FUNCTION (add, _mm_add_epi8, M128I_I8, M128I_I8, M128I_I8)
				DEFINE_MMX_BINARY_FUNCTION (add, _mm_add_epi8, M128I_U8, M128I_U8, M128I_U8)
				DEFINE_MMX_BINARY_FUNCTION (add, _mm_add_epi16, M128I_I16, M128I_I16, M128I_I16)
				DEFINE_MMX_BINARY_FUNCTION (add, _mm_add_epi16, M128I_U16, M128I_U16, M128I_U16)
				DEFINE_MMX_BINARY_FUNCTION (add, _mm_add_epi32, M128I_I32, M128I_I32, M128I_I32)
				DEFINE_MMX_BINARY_FUNCTION (add, _mm_add_epi32, M128I_U32, M128I_U32, M128I_U32)
				DEFINE_MMX_BINARY_FUNCTION (add, _mm_add_epi64, M128I_I64, M128I_I64, M128I_I64)
				DEFINE_MMX_BINARY_FUNCTION (add, _mm_add_epi64, M128I_U64, M128I_U64, M128I_U64)
				DEFINE_AVX_BINARY_FUNCTION_FROM_MMX(add, _mm_add_epi32, M256I_I32, M256I_I32, M256I_I32,
											 M128I_I32, M128I_I32, M128I_I32)
// 				DEFINE_AVX_BINARY_FUNCTION_FROM_MMX(add, _mm_add_epi32, M256I_U32, M256I_U32, M256I_U32,
// 											 M128I_U32, M128I_U32, M128I_U32)
				DEFINE_AVX_BINARY_FUNCTION_FROM_MMX(add, _mm_add_epi64, M256I_I64, M256I_I64, M256I_I64,
											 M128I_I64, M128I_I64, M128I_I64)
				DEFINE_AVX_BINARY_FUNCTION_FROM_MMX(add, _mm_add_epi64, M256I_U64, M256I_U64, M256I_U64,
											 M128I_U64, M128I_U64, M128I_U64)

				DEFINE_MMX_BINARY_FUNCTION (adds, _mm_adds_epi8, M128I_I8, M128I_I8, M128I_I8)
				DEFINE_MMX_BINARY_FUNCTION (adds, _mm_adds_epi16, M128I_I16, M128I_I16, M128I_I16)
				DEFINE_MMX_BINARY_FUNCTION (adds, _mm_adds_epu8, M128I_U8, M128I_U8, M128I_U8)
				DEFINE_MMX_BINARY_FUNCTION (adds, _mm_adds_epu16, M128I_U16, M128I_U16, M128I_U16)

				DEFINE_MMX_BINARY_FUNCTION (avg, _mm_avg_epu8, M128I_U8, M128I_U8, M128I_U8)
				DEFINE_MMX_BINARY_FUNCTION (avg, _mm_avg_epu16, M128I_U16, M128I_U16, M128I_U16)

				DEFINE_MMX_BINARY_FUNCTION (madd, _mm_madd_epi16, M128I_I16, M128I_I16, M128I_I32)
				DEFINE_MMX_BINARY_FUNCTION (madd, _mm_madd_epi16, M128I_U16, M128I_U16, M128I_U32)

				DEFINE_MMX_BINARY_FUNCTION (max, _mm_max_epi16, M128I_I16, M128I_I16, M128I_I16)
				DEFINE_MMX_BINARY_FUNCTION (max, _mm_max_epu8, M128I_U8, M128I_U8, M128I_U8)

				DEFINE_MMX_BINARY_FUNCTION (min, _mm_min_epi16, M128I_I16, M128I_I16, M128I_I16)
				DEFINE_MMX_BINARY_FUNCTION (min, _mm_min_epu8, M128I_U8, M128I_U8, M128I_U8)

				DEFINE_MMX_BINARY_FUNCTION (mulhi, _mm_mulhi_epi16, M128I_I16, M128I_I16, M128I_I16)
				DEFINE_MMX_BINARY_FUNCTION (mulhi, _mm_mulhi_epu16, M128I_U16, M128I_U16, M128I_U16)

				DEFINE_MMX_BINARY_FUNCTION (mullo, _mm_mullo_epi16, M128I_I16, M128I_I16, M128I_I16)
				DEFINE_MMX_BINARY_FUNCTION (mullo, _mm_mullo_epi16, M128I_U16, M128I_U16, M128I_U16)

				DEFINE_MMX_BINARY_FUNCTION (mul, _mm_mul_epu32, M128I_I32, M128I_I32, M128I_I64)
				DEFINE_MMX_BINARY_FUNCTION (mul, _mm_mul_epu32, M128I_U32, M128I_U32, M128I_U64)
				DEFINE_AVX_BINARY_FUNCTION_FROM_MMX(mul, _mm_mul_epu32, M256I_I32, M256I_I32, M256I_I64,
											 M128I_I32, M128I_I32, M128I_I64)

				DEFINE_MMX_BINARY_FUNCTION (sad, _mm_sad_epu8, M128I_U8, M128I_U8, M128I_U16)

				DEFINE_MMX_BINARY_FUNCTION (sub, _mm_sub_epi8, M128I_I8, M128I_I8, M128I_I8)
				DEFINE_MMX_BINARY_FUNCTION (sub, _mm_sub_epi8, M128I_U8, M128I_U8, M128I_U8)
				DEFINE_MMX_BINARY_FUNCTION (sub, _mm_sub_epi16, M128I_I16, M128I_I16, M128I_I16)
				DEFINE_MMX_BINARY_FUNCTION (sub, _mm_sub_epi16, M128I_U16, M128I_U16, M128I_U16)
				DEFINE_MMX_BINARY_FUNCTION (sub, _mm_sub_epi32, M128I_I32, M128I_I32, M128I_I32)
				DEFINE_MMX_BINARY_FUNCTION (sub, _mm_sub_epi32, M128I_U32, M128I_U32, M128I_U32)
				DEFINE_AVX_BINARY_FUNCTION_FROM_MMX(sub, _mm_sub_epi32, M256I_I32, M256I_I32, M256I_I32,
											 M128I_I32, M128I_I32, M128I_I32)
				DEFINE_MMX_BINARY_FUNCTION (sub, _mm_sub_epi64, M128I_I64, M128I_I64, M128I_I64)
				DEFINE_MMX_BINARY_FUNCTION (sub, _mm_sub_epi64, M128I_U64, M128I_U64, M128I_U64)
				DEFINE_AVX_BINARY_FUNCTION_FROM_MMX(sub, _mm_sub_epi64, M256I_I64, M256I_I64, M256I_I64,
											 M128I_I64, M128I_I64, M128I_I64)
				DEFINE_AVX_BINARY_FUNCTION_FROM_MMX(sub, _mm_sub_epi64, M256I_U64, M256I_U64, M256I_U64,
											 M128I_U64, M128I_U64, M128I_U64)

				DEFINE_MMX_BINARY_FUNCTION (subs, _mm_subs_epi8, M128I_I8, M128I_I8, M128I_I8)
				DEFINE_MMX_BINARY_FUNCTION (subs, _mm_subs_epi16, M128I_I16, M128I_I16, M128I_I16)
				DEFINE_MMX_BINARY_FUNCTION (subs, _mm_subs_epu8, M128I_U8, M128I_U8, M128I_U8)
				DEFINE_MMX_BINARY_FUNCTION (subs, _mm_subs_epu16, M128I_U16, M128I_U16, M128I_U16)

				// SSE2 Integer Logical Intrinsics

				DEFINE_MMX_BINARY_FUNCTION (vand, _mm_and_si128, M128I_I8, M128I_I8, M128I_I8)
				DEFINE_MMX_BINARY_FUNCTION (vand, _mm_and_si128, M128I_B8, M128I_I8, M128I_I8)
				DEFINE_MMX_BINARY_FUNCTION (vand, _mm_and_si128, M128I_I8, M128I_B8, M128I_I8)
				DEFINE_MMX_BINARY_FUNCTION (vand, _mm_and_si128, M128I_U8, M128I_U8, M128I_U8)
				DEFINE_MMX_BINARY_FUNCTION (vand, _mm_and_si128, M128I_B8, M128I_U8, M128I_U8)
				DEFINE_MMX_BINARY_FUNCTION (vand, _mm_and_si128, M128I_U8, M128I_B8, M128I_U8)
				DEFINE_MMX_BINARY_FUNCTION (vand, _mm_and_si128, M128I_B8, M128I_B8, M128I_B8)

				DEFINE_MMX_BINARY_FUNCTION (vand, _mm_and_si128, M128I_I16, M128I_I16, M128I_I16)
				DEFINE_MMX_BINARY_FUNCTION (vand, _mm_and_si128, M128I_B16, M128I_I16, M128I_I16)
				DEFINE_MMX_BINARY_FUNCTION (vand, _mm_and_si128, M128I_I16, M128I_B16, M128I_I16)
				DEFINE_MMX_BINARY_FUNCTION (vand, _mm_and_si128, M128I_U16, M128I_U16, M128I_U16)
				DEFINE_MMX_BINARY_FUNCTION (vand, _mm_and_si128, M128I_B16, M128I_U16, M128I_U16)
				DEFINE_MMX_BINARY_FUNCTION (vand, _mm_and_si128, M128I_U16, M128I_B16, M128I_U16)
				DEFINE_MMX_BINARY_FUNCTION (vand, _mm_and_si128, M128I_B16, M128I_B16, M128I_B16)

				DEFINE_MMX_BINARY_FUNCTION (vand, _mm_and_si128, M128I_I32, M128I_I32, M128I_I32)
				DEFINE_MMX_BINARY_FUNCTION (vand, _mm_and_si128, M128I_B32, M128I_I32, M128I_I32)
				DEFINE_MMX_BINARY_FUNCTION (vand, _mm_and_si128, M128I_I32, M128I_B32, M128I_I32)
				DEFINE_MMX_BINARY_FUNCTION (vand, _mm_and_si128, M128I_U32, M128I_U32, M128I_U32)
				DEFINE_MMX_BINARY_FUNCTION (vand, _mm_and_si128, M128I_B32, M128I_U32, M128I_U32)
				DEFINE_MMX_BINARY_FUNCTION (vand, _mm_and_si128, M128I_U32, M128I_B32, M128I_U32)
				DEFINE_MMX_BINARY_FUNCTION (vand, _mm_and_si128, M128I_B32, M128I_B32, M128I_B32)
				DEFINE_AVX_BINARY_FUNCTION_FROM_MMX(vand, _mm_and_si128, M256I_I32, M256I_I32, M256I_I32,
											 M128I_I32, M128I_I32, M128I_I32)
				DEFINE_AVX_BINARY_FUNCTION_FROM_MMX(vand, _mm_and_si128, M256I_B32, M256I_I32, M256I_I32,
											 M128I_B32, M128I_I32, M128I_I32)
				DEFINE_AVX_BINARY_FUNCTION_FROM_MMX(vand, _mm_and_si128, M256I_I32, M256I_B32, M256I_I32,
											 M128I_I32, M128I_B32, M128I_I32)
				DEFINE_AVX_BINARY_FUNCTION_FROM_MMX(vand, _mm_and_si128, M256I_B32, M256I_B32, M256I_B32,
											 M128I_B32, M128I_B32, M128I_B32)

				DEFINE_MMX_BINARY_FUNCTION (vand, _mm_and_si128, M128I_I64, M128I_I64, M128I_I64)
				DEFINE_MMX_BINARY_FUNCTION (vand, _mm_and_si128, M128I_B64, M128I_I64, M128I_I64)
				DEFINE_MMX_BINARY_FUNCTION (vand, _mm_and_si128, M128I_I64, M128I_B64, M128I_I64)
				DEFINE_MMX_BINARY_FUNCTION (vand, _mm_and_si128, M128I_U64, M128I_U64, M128I_U64)
				DEFINE_MMX_BINARY_FUNCTION (vand, _mm_and_si128, M128I_B64, M128I_U64, M128I_U64)
				DEFINE_MMX_BINARY_FUNCTION (vand, _mm_and_si128, M128I_U64, M128I_B64, M128I_U64)
				DEFINE_MMX_BINARY_FUNCTION (vand, _mm_and_si128, M128I_B64, M128I_B64, M128I_B64)
				DEFINE_AVX_BINARY_FUNCTION_FROM_MMX(vand, _mm_and_si128, M256I_I64, M256I_I64, M256I_I64,
											 M128I_I64, M128I_I64, M128I_I64)
				DEFINE_AVX_BINARY_FUNCTION_FROM_MMX(vand, _mm_and_si128, M256I_B64, M256I_I64, M256I_I64,
											 M128I_B64, M128I_I64, M128I_I64)
				DEFINE_AVX_BINARY_FUNCTION_FROM_MMX(vand, _mm_and_si128, M256I_I64, M256I_B64, M256I_I64,
											 M128I_I64, M128I_B64, M128I_I64)
				DEFINE_AVX_BINARY_FUNCTION_FROM_MMX(vand, _mm_and_si128, M256I_U64, M256I_U64, M256I_U64,
											 M128I_U64, M128I_U64, M128I_U64)
				DEFINE_AVX_BINARY_FUNCTION_FROM_MMX(vand, _mm_and_si128, M256I_B64, M256I_U64, M256I_U64,
											 M128I_B64, M128I_U64, M128I_U64)
				DEFINE_AVX_BINARY_FUNCTION_FROM_MMX(vand, _mm_and_si128, M256I_U64, M256I_B64, M256I_U64,
											 M128I_U64, M128I_B64, M128I_U64)
				DEFINE_AVX_BINARY_FUNCTION_FROM_MMX(vand, _mm_and_si128, M256I_B64, M256I_B64, M256I_B64,
											 M128I_B64, M128I_B64, M128I_B64)

				DEFINE_MMX_BINARY_FUNCTION (andnot, _mm_andnot_si128, M128I_I8, M128I_I8, M128I_I8)
				DEFINE_MMX_BINARY_FUNCTION (andnot, _mm_andnot_si128, M128I_B8, M128I_I8, M128I_I8)
				DEFINE_MMX_BINARY_FUNCTION (andnot, _mm_andnot_si128, M128I_I8, M128I_B8, M128I_I8)
				DEFINE_MMX_BINARY_FUNCTION (andnot, _mm_andnot_si128, M128I_U8, M128I_U8, M128I_U8)
				DEFINE_MMX_BINARY_FUNCTION (andnot, _mm_andnot_si128, M128I_B8, M128I_U8, M128I_U8)
				DEFINE_MMX_BINARY_FUNCTION (andnot, _mm_andnot_si128, M128I_U8, M128I_B8, M128I_U8)
				DEFINE_MMX_BINARY_FUNCTION (andnot, _mm_andnot_si128, M128I_B8, M128I_B8, M128I_B8)

				DEFINE_MMX_BINARY_FUNCTION (andnot, _mm_andnot_si128, M128I_I16, M128I_I16, M128I_I16)
				DEFINE_MMX_BINARY_FUNCTION (andnot, _mm_andnot_si128, M128I_B16, M128I_I16, M128I_I16)
				DEFINE_MMX_BINARY_FUNCTION (andnot, _mm_andnot_si128, M128I_I16, M128I_B16, M128I_I16)
				DEFINE_MMX_BINARY_FUNCTION (andnot, _mm_andnot_si128, M128I_U16, M128I_U16, M128I_U16)
				DEFINE_MMX_BINARY_FUNCTION (andnot, _mm_andnot_si128, M128I_B16, M128I_U16, M128I_U16)
				DEFINE_MMX_BINARY_FUNCTION (andnot, _mm_andnot_si128, M128I_U16, M128I_B16, M128I_U16)
				DEFINE_MMX_BINARY_FUNCTION (andnot, _mm_andnot_si128, M128I_B16, M128I_B16, M128I_B16)

				DEFINE_MMX_BINARY_FUNCTION (andnot, _mm_andnot_si128, M128I_I32, M128I_I32, M128I_I32)
				DEFINE_MMX_BINARY_FUNCTION (andnot, _mm_andnot_si128, M128I_B32, M128I_I32, M128I_I32)
				DEFINE_MMX_BINARY_FUNCTION (andnot, _mm_andnot_si128, M128I_I32, M128I_B32, M128I_I32)
				DEFINE_MMX_BINARY_FUNCTION (andnot, _mm_andnot_si128, M128I_U32, M128I_U32, M128I_U32)
				DEFINE_MMX_BINARY_FUNCTION (andnot, _mm_andnot_si128, M128I_B32, M128I_U32, M128I_U32)
				DEFINE_MMX_BINARY_FUNCTION (andnot, _mm_andnot_si128, M128I_U32, M128I_B32, M128I_U32)
				DEFINE_MMX_BINARY_FUNCTION (andnot, _mm_andnot_si128, M128I_B32, M128I_B32, M128I_B32)
				DEFINE_AVX_BINARY_FUNCTION_FROM_MMX(andnot, _mm_andnot_si128, M256I_I32, M256I_I32, M256I_I32,
											 M128I_I32, M128I_I32, M128I_I32)
				DEFINE_AVX_BINARY_FUNCTION_FROM_MMX(andnot, _mm_andnot_si128, M256I_B32, M256I_I32, M256I_I32,
											 M128I_B32, M128I_I32, M128I_I32)
				DEFINE_AVX_BINARY_FUNCTION_FROM_MMX(andnot, _mm_andnot_si128, M256I_I32, M256I_B32, M256I_I32,
											 M128I_I32, M128I_B32, M128I_I32)
				DEFINE_AVX_BINARY_FUNCTION_FROM_MMX(andnot, _mm_andnot_si128, M256I_B32, M256I_B32, M256I_B32,
											 M128I_B32, M128I_B32, M128I_B32)

				DEFINE_MMX_BINARY_FUNCTION (andnot, _mm_andnot_si128, M128I_I64, M128I_I64, M128I_I64)
				DEFINE_MMX_BINARY_FUNCTION (andnot, _mm_andnot_si128, M128I_B64, M128I_I64, M128I_I64)
				DEFINE_MMX_BINARY_FUNCTION (andnot, _mm_andnot_si128, M128I_I64, M128I_B64, M128I_I64)
				DEFINE_MMX_BINARY_FUNCTION (andnot, _mm_andnot_si128, M128I_U64, M128I_U64, M128I_U64)
				DEFINE_MMX_BINARY_FUNCTION (andnot, _mm_andnot_si128, M128I_B64, M128I_U64, M128I_U64)
				DEFINE_MMX_BINARY_FUNCTION (andnot, _mm_andnot_si128, M128I_U64, M128I_B64, M128I_U64)
				DEFINE_MMX_BINARY_FUNCTION (andnot, _mm_andnot_si128, M128I_B64, M128I_B64, M128I_B64)
				DEFINE_AVX_BINARY_FUNCTION_FROM_MMX(andnot, _mm_andnot_si128, M256I_I64, M256I_I64, M256I_I64,
											 M128I_I64, M128I_I64, M128I_I64)
				DEFINE_AVX_BINARY_FUNCTION_FROM_MMX(andnot, _mm_andnot_si128, M256I_B64, M256I_I64, M256I_I64,
											 M128I_B64, M128I_I64, M128I_I64)
				DEFINE_AVX_BINARY_FUNCTION_FROM_MMX(andnot, _mm_andnot_si128, M256I_I64, M256I_B64, M256I_I64,
											 M128I_I64, M128I_B64, M128I_I64)
				DEFINE_AVX_BINARY_FUNCTION_FROM_MMX(andnot, _mm_andnot_si128, M256I_U64, M256I_U64, M256I_U64,
											 M128I_U64, M128I_U64, M128I_U64)
				DEFINE_AVX_BINARY_FUNCTION_FROM_MMX(andnot, _mm_andnot_si128, M256I_B64, M256I_U64, M256I_U64,
											 M128I_B64, M128I_U64, M128I_U64)
				DEFINE_AVX_BINARY_FUNCTION_FROM_MMX(andnot, _mm_andnot_si128, M256I_U64, M256I_B64, M256I_U64,
											 M128I_U64, M128I_B64, M128I_U64)
				DEFINE_AVX_BINARY_FUNCTION_FROM_MMX(andnot, _mm_andnot_si128, M256I_B64, M256I_B64, M256I_B64,
											 M128I_B64, M128I_B64, M128I_B64)

				DEFINE_MMX_BINARY_FUNCTION (vor, _mm_or_si128, M128I_I8, M128I_I8, M128I_I8)
				DEFINE_MMX_BINARY_FUNCTION (vor, _mm_or_si128, M128I_B8, M128I_I8, M128I_I8)
				DEFINE_MMX_BINARY_FUNCTION (vor, _mm_or_si128, M128I_I8, M128I_B8, M128I_I8)
				DEFINE_MMX_BINARY_FUNCTION (vor, _mm_or_si128, M128I_U8, M128I_U8, M128I_U8)
				DEFINE_MMX_BINARY_FUNCTION (vor, _mm_or_si128, M128I_B8, M128I_U8, M128I_U8)
				DEFINE_MMX_BINARY_FUNCTION (vor, _mm_or_si128, M128I_U8, M128I_B8, M128I_U8)
				DEFINE_MMX_BINARY_FUNCTION (vor, _mm_or_si128, M128I_B8, M128I_B8, M128I_B8)

				DEFINE_MMX_BINARY_FUNCTION (vor, _mm_or_si128, M128I_I16, M128I_I16, M128I_I16)
				DEFINE_MMX_BINARY_FUNCTION (vor, _mm_or_si128, M128I_B16, M128I_I16, M128I_I16)
				DEFINE_MMX_BINARY_FUNCTION (vor, _mm_or_si128, M128I_I16, M128I_B16, M128I_I16)
				DEFINE_MMX_BINARY_FUNCTION (vor, _mm_or_si128, M128I_U16, M128I_U16, M128I_U16)
				DEFINE_MMX_BINARY_FUNCTION (vor, _mm_or_si128, M128I_B16, M128I_U16, M128I_U16)
				DEFINE_MMX_BINARY_FUNCTION (vor, _mm_or_si128, M128I_U16, M128I_B16, M128I_U16)
				DEFINE_MMX_BINARY_FUNCTION (vor, _mm_or_si128, M128I_B16, M128I_B16, M128I_B16)

				DEFINE_MMX_BINARY_FUNCTION (vor, _mm_or_si128, M128I_I32, M128I_I32, M128I_I32)
				DEFINE_MMX_BINARY_FUNCTION (vor, _mm_or_si128, M128I_B32, M128I_I32, M128I_I32)
				DEFINE_MMX_BINARY_FUNCTION (vor, _mm_or_si128, M128I_I32, M128I_B32, M128I_I32)
				DEFINE_MMX_BINARY_FUNCTION (vor, _mm_or_si128, M128I_U32, M128I_U32, M128I_U32)
				DEFINE_MMX_BINARY_FUNCTION (vor, _mm_or_si128, M128I_B32, M128I_U32, M128I_U32)
				DEFINE_MMX_BINARY_FUNCTION (vor, _mm_or_si128, M128I_U32, M128I_B32, M128I_U32)
				DEFINE_MMX_BINARY_FUNCTION (vor, _mm_or_si128, M128I_B32, M128I_B32, M128I_B32)
				DEFINE_AVX_BINARY_FUNCTION_FROM_MMX(vor, _mm_or_si128, M256I_I32, M256I_I32, M256I_I32,
											 M128I_I32, M128I_I32, M128I_I32)
				DEFINE_AVX_BINARY_FUNCTION_FROM_MMX(vor, _mm_or_si128, M256I_B32, M256I_I32, M256I_I32,
											 M128I_B32, M128I_I32, M128I_I32)
				DEFINE_AVX_BINARY_FUNCTION_FROM_MMX(vor, _mm_or_si128, M256I_I32, M256I_B32, M256I_I32,
											 M128I_I32, M128I_B32, M128I_I32)
				DEFINE_AVX_BINARY_FUNCTION_FROM_MMX(vor, _mm_or_si128, M256I_B32, M256I_B32, M256I_B32,
											 M128I_B32, M128I_B32, M128I_B32)

				DEFINE_MMX_BINARY_FUNCTION (vor, _mm_or_si128, M128I_I64, M128I_I64, M128I_I64)
				DEFINE_MMX_BINARY_FUNCTION (vor, _mm_or_si128, M128I_B64, M128I_I64, M128I_I64)
				DEFINE_MMX_BINARY_FUNCTION (vor, _mm_or_si128, M128I_I64, M128I_B64, M128I_I64)
				DEFINE_MMX_BINARY_FUNCTION (vor, _mm_or_si128, M128I_U64, M128I_U64, M128I_U64)
				DEFINE_MMX_BINARY_FUNCTION (vor, _mm_or_si128, M128I_B64, M128I_U64, M128I_U64)
				DEFINE_MMX_BINARY_FUNCTION (vor, _mm_or_si128, M128I_U64, M128I_B64, M128I_U64)
				DEFINE_MMX_BINARY_FUNCTION (vor, _mm_or_si128, M128I_B64, M128I_B64, M128I_B64)
				DEFINE_AVX_BINARY_FUNCTION_FROM_MMX(vor, _mm_or_si128, M256I_I64, M256I_I64, M256I_I64,
											 M128I_I64, M128I_I64, M128I_I64)
				DEFINE_AVX_BINARY_FUNCTION_FROM_MMX(vor, _mm_or_si128, M256I_B64, M256I_I64, M256I_I64,
											 M128I_B64, M128I_I64, M128I_I64)
				DEFINE_AVX_BINARY_FUNCTION_FROM_MMX(vor, _mm_or_si128, M256I_I64, M256I_B64, M256I_I64,
											 M128I_I64, M128I_B64, M128I_I64)
				DEFINE_AVX_BINARY_FUNCTION_FROM_MMX(vor, _mm_or_si128, M256I_U64, M256I_U64, M256I_U64,
											 M128I_U64, M128I_U64, M128I_U64)
				DEFINE_AVX_BINARY_FUNCTION_FROM_MMX(vor, _mm_or_si128, M256I_B64, M256I_U64, M256I_U64,
											 M128I_B64, M128I_U64, M128I_U64)
				DEFINE_AVX_BINARY_FUNCTION_FROM_MMX(vor, _mm_or_si128, M256I_U64, M256I_B64, M256I_U64,
											 M128I_U64, M128I_B64, M128I_U64)
				DEFINE_AVX_BINARY_FUNCTION_FROM_MMX(vor, _mm_or_si128, M256I_B64, M256I_B64, M256I_B64,
											 M128I_B64, M128I_B64, M128I_B64)

				DEFINE_MMX_BINARY_FUNCTION (vxor, _mm_xor_si128, M128I_I8, M128I_I8, M128I_I8)
				DEFINE_MMX_BINARY_FUNCTION (vxor, _mm_xor_si128, M128I_B8, M128I_I8, M128I_I8)
				DEFINE_MMX_BINARY_FUNCTION (vxor, _mm_xor_si128, M128I_I8, M128I_B8, M128I_I8)
				DEFINE_MMX_BINARY_FUNCTION (vxor, _mm_xor_si128, M128I_U8, M128I_U8, M128I_U8)
				DEFINE_MMX_BINARY_FUNCTION (vxor, _mm_xor_si128, M128I_B8, M128I_U8, M128I_U8)
				DEFINE_MMX_BINARY_FUNCTION (vxor, _mm_xor_si128, M128I_U8, M128I_B8, M128I_U8)
				DEFINE_MMX_BINARY_FUNCTION (vxor, _mm_xor_si128, M128I_B8, M128I_B8, M128I_B8)

				DEFINE_MMX_BINARY_FUNCTION (vxor, _mm_xor_si128, M128I_I16, M128I_I16, M128I_I16)
				DEFINE_MMX_BINARY_FUNCTION (vxor, _mm_xor_si128, M128I_B16, M128I_I16, M128I_I16)
				DEFINE_MMX_BINARY_FUNCTION (vxor, _mm_xor_si128, M128I_I16, M128I_B16, M128I_I16)
				DEFINE_MMX_BINARY_FUNCTION (vxor, _mm_xor_si128, M128I_U16, M128I_U16, M128I_U16)
				DEFINE_MMX_BINARY_FUNCTION (vxor, _mm_xor_si128, M128I_B16, M128I_U16, M128I_U16)
				DEFINE_MMX_BINARY_FUNCTION (vxor, _mm_xor_si128, M128I_U16, M128I_B16, M128I_U16)
				DEFINE_MMX_BINARY_FUNCTION (vxor, _mm_xor_si128, M128I_B16, M128I_B16, M128I_B16)

				DEFINE_MMX_BINARY_FUNCTION (vxor, _mm_xor_si128, M128I_I32, M128I_I32, M128I_I32)
				DEFINE_MMX_BINARY_FUNCTION (vxor, _mm_xor_si128, M128I_B32, M128I_I32, M128I_I32)
				DEFINE_MMX_BINARY_FUNCTION (vxor, _mm_xor_si128, M128I_I32, M128I_B32, M128I_I32)
				DEFINE_MMX_BINARY_FUNCTION (vxor, _mm_xor_si128, M128I_U32, M128I_U32, M128I_U32)
				DEFINE_MMX_BINARY_FUNCTION (vxor, _mm_xor_si128, M128I_B32, M128I_U32, M128I_U32)
				DEFINE_MMX_BINARY_FUNCTION (vxor, _mm_xor_si128, M128I_U32, M128I_B32, M128I_U32)
				DEFINE_MMX_BINARY_FUNCTION (vxor, _mm_xor_si128, M128I_B32, M128I_B32, M128I_B32)
				DEFINE_AVX_BINARY_FUNCTION_FROM_MMX(vxor, _mm_xor_si128, M256I_I32, M256I_I32, M256I_I32,
											 M128I_I32, M128I_I32, M128I_I32)
				DEFINE_AVX_BINARY_FUNCTION_FROM_MMX(vxor, _mm_xor_si128, M256I_B32, M256I_I32, M256I_I32,
											 M128I_B32, M128I_I32, M128I_I32)
				DEFINE_AVX_BINARY_FUNCTION_FROM_MMX(vxor, _mm_xor_si128, M256I_I32, M256I_B32, M256I_I32,
											 M128I_I32, M128I_B32, M128I_I32)
				DEFINE_AVX_BINARY_FUNCTION_FROM_MMX(vxor, _mm_xor_si128, M256I_B32, M256I_B32, M256I_B32,
											 M128I_B32, M128I_B32, M128I_B32)

				DEFINE_MMX_BINARY_FUNCTION (vxor, _mm_xor_si128, M128I_I64, M128I_I64, M128I_I64)
				DEFINE_MMX_BINARY_FUNCTION (vxor, _mm_xor_si128, M128I_B64, M128I_I64, M128I_I64)
				DEFINE_MMX_BINARY_FUNCTION (vxor, _mm_xor_si128, M128I_I64, M128I_B64, M128I_I64)
				DEFINE_MMX_BINARY_FUNCTION (vxor, _mm_xor_si128, M128I_U64, M128I_U64, M128I_U64)
				DEFINE_MMX_BINARY_FUNCTION (vxor, _mm_xor_si128, M128I_B64, M128I_U64, M128I_U64)
				DEFINE_MMX_BINARY_FUNCTION (vxor, _mm_xor_si128, M128I_U64, M128I_B64, M128I_U64)
				DEFINE_MMX_BINARY_FUNCTION (vxor, _mm_xor_si128, M128I_B64, M128I_B64, M128I_B64)
				DEFINE_AVX_BINARY_FUNCTION_FROM_MMX(vxor, _mm_xor_si128, M256I_I64, M256I_I64, M256I_I64,
											 M128I_I64, M128I_I64, M128I_I64)
				DEFINE_AVX_BINARY_FUNCTION_FROM_MMX(vxor, _mm_xor_si128, M256I_B64, M256I_I64, M256I_I64,
											 M128I_B64, M128I_I64, M128I_I64)
				DEFINE_AVX_BINARY_FUNCTION_FROM_MMX(vxor, _mm_xor_si128, M256I_I64, M256I_B64, M256I_I64,
											 M128I_I64, M128I_B64, M128I_I64)
				DEFINE_AVX_BINARY_FUNCTION_FROM_MMX(vxor, _mm_xor_si128, M256I_U64, M256I_U64, M256I_U64,
											 M128I_U64, M128I_U64, M128I_U64)
				DEFINE_AVX_BINARY_FUNCTION_FROM_MMX(vxor, _mm_xor_si128, M256I_B64, M256I_U64, M256I_U64,
											 M128I_B64, M128I_U64, M128I_U64)
				DEFINE_AVX_BINARY_FUNCTION_FROM_MMX(vxor, _mm_xor_si128, M256I_U64, M256I_B64, M256I_U64,
											 M128I_U64, M128I_B64, M128I_U64)
				DEFINE_AVX_BINARY_FUNCTION_FROM_MMX(vxor, _mm_xor_si128, M256I_B64, M256I_B64, M256I_B64,
											 M128I_B64, M128I_B64, M128I_B64)

				// SSE2 Integer Compare Intrinsics

				DEFINE_MMX_BINARY_FUNCTION (cmpeq, _mm_cmpeq_epi8, M128I_I8, M128I_I8, M128I_B8)
				DEFINE_MMX_BINARY_FUNCTION (cmpeq, _mm_cmpeq_epi8, M128I_U8, M128I_U8, M128I_B8)
				DEFINE_MMX_BINARY_FUNCTION (cmpeq, _mm_cmpeq_epi8, M128I_B8, M128I_B8, M128I_B8)
				DEFINE_MMX_BINARY_FUNCTION (cmpeq, _mm_cmpeq_epi16, M128I_I16, M128I_I16, M128I_B16)
				DEFINE_MMX_BINARY_FUNCTION (cmpeq, _mm_cmpeq_epi16, M128I_U16, M128I_U16, M128I_B16)
				DEFINE_MMX_BINARY_FUNCTION (cmpeq, _mm_cmpeq_epi16, M128I_B16, M128I_B16, M128I_B16)
				DEFINE_MMX_BINARY_FUNCTION (cmpeq, _mm_cmpeq_epi32, M128I_I32, M128I_I32, M128I_B32)
				DEFINE_MMX_BINARY_FUNCTION (cmpeq, _mm_cmpeq_epi32, M128I_U32, M128I_U32, M128I_B32)
				DEFINE_MMX_BINARY_FUNCTION (cmpeq, _mm_cmpeq_epi32, M128I_B32, M128I_B32, M128I_B32)
				DEFINE_AVX_BINARY_FUNCTION_FROM_MMX(cmpeq, _mm_cmpeq_epi32, M256I_I32, M256I_I32, M256I_B32,
											 M128I_I32, M128I_I32, M128I_B32)
				DEFINE_AVX_BINARY_FUNCTION_FROM_MMX(cmpeq, _mm_cmpeq_epi32, M256I_B32, M256I_B32, M256I_B32,
											 M128I_B32, M128I_B32, M128I_B32)
				// kludge! We'll do the equality testing not on vec<long long,4> but on 2-element vec<long,2>
				DEFINE_AVX_BINARY_FUNCTION_FROM_MMX(cmpeq, _mm_cmpeq_epi32, M256I_I64, M256I_I64, M256I_I64,
											 M128I_I32, M128I_I32, M128I_I32)
				DEFINE_AVX_BINARY_FUNCTION_FROM_MMX(cmpeq, _mm_cmpeq_epi32, M256I_B64, M256I_I64, M256I_I64,
											 M128I_B32, M128I_I32, M128I_I32)
				DEFINE_AVX_BINARY_FUNCTION_FROM_MMX(cmpeq, _mm_cmpeq_epi32, M256I_I64, M256I_B64, M256I_I64,
											 M128I_I32, M128I_B32, M128I_I32)
				DEFINE_AVX_BINARY_FUNCTION_FROM_MMX(cmpeq, _mm_cmpeq_epi32, M256I_U64, M256I_U64, M256I_U64,
											 M128I_U32, M128I_U32, M128I_U32)
				DEFINE_AVX_BINARY_FUNCTION_FROM_MMX(cmpeq, _mm_cmpeq_epi32, M256I_B64, M256I_U64, M256I_U64,
											 M128I_B32, M128I_U32, M128I_U32)
				DEFINE_AVX_BINARY_FUNCTION_FROM_MMX(cmpeq, _mm_cmpeq_epi32, M256I_U64, M256I_B64, M256I_U64,
											 M128I_U32, M128I_B32, M128I_U32)
				DEFINE_AVX_BINARY_FUNCTION_FROM_MMX(cmpeq, _mm_cmpeq_epi32, M256I_B64, M256I_B64, M256I_B64,
											 M128I_B32, M128I_B32, M128I_B32)

				DEFINE_MMX_BINARY_FUNCTION (cmpgt, _mm_cmpgt_epi8, M128I_I8, M128I_I8, M128I_B8)
				DEFINE_MMX_BINARY_FUNCTION (cmpgt, _mm_cmpgt_epi16, M128I_I16, M128I_I16, M128I_B16)
				DEFINE_MMX_BINARY_FUNCTION (cmpgt, _mm_cmpgt_epi32, M128I_I32, M128I_I32, M128I_B32)
				DEFINE_AVX_BINARY_FUNCTION_FROM_MMX(cmpgt, _mm_cmpgt_epi32, M256I_I32, M256I_I32, M256I_B32,
											 M128I_I32, M128I_I32, M128I_B32)

				DEFINE_MMX_BINARY_FUNCTION (cmplt, _mm_cmplt_epi8, M128I_I8, M128I_I8, M128I_B8)
				DEFINE_MMX_BINARY_FUNCTION (cmplt, _mm_cmplt_epi16, M128I_I16, M128I_I16, M128I_B16)
				DEFINE_MMX_BINARY_FUNCTION (cmplt, _mm_cmplt_epi32, M128I_I32, M128I_I32, M128I_B32)
				DEFINE_AVX_BINARY_FUNCTION_FROM_MMX(cmplt, _mm_cmplt_epi32, M256I_I32, M256I_I32, M256I_B32,
											 M128I_I32, M128I_I32, M128I_B32)

				// SSE2 Integer Shift Intrinsics

				DEFINE_MMX_BINARY_FUNCTION (sll, _mm_sll_epi16, M128I_I16, M128I_U16, M128I_I16)
				DEFINE_MMX_BINARY_FUNCTION (sll, _mm_sll_epi16, M128I_U16, M128I_U16, M128I_U16)

				DEFINE_MMX_BINARY_FUNCTION (sll, _mm_slli_epi16, M128I_I16, int, M128I_I16)
				DEFINE_MMX_BINARY_FUNCTION (sll, _mm_slli_epi16, M128I_U16, int, M128I_U16)

				DEFINE_MMX_BINARY_FUNCTION (sll, _mm_sll_epi32, M128I_I32, M128I_U32, M128I_I32)
				DEFINE_MMX_BINARY_FUNCTION (sll, _mm_sll_epi32, M128I_U32, M128I_U32, M128I_U32)

				DEFINE_MMX_BINARY_FUNCTION (sll, _mm_slli_epi32, M128I_I32, int, M128I_I32)
				DEFINE_MMX_BINARY_FUNCTION (sll, _mm_slli_epi32, M128I_U32, int, M128I_U32)

				DEFINE_MMX_BINARY_FUNCTION (sll, _mm_sll_epi64, M128I_I64, M128I_U64, M128I_I64)
				DEFINE_MMX_BINARY_FUNCTION (sll, _mm_sll_epi64, M128I_U64, M128I_U64, M128I_U64)

				DEFINE_MMX_BINARY_FUNCTION (sll, _mm_slli_epi64, M128I_I64, int, M128I_I64)
				DEFINE_MMX_BINARY_FUNCTION (sll, _mm_slli_epi64, M128I_U64, int, M128I_U64)

				DEFINE_MMX_UNARY_FUNCTION_WITH_LITERAL (slli, _mm_slli_epi16, M128I_I16, M128I_I16)
				DEFINE_MMX_UNARY_FUNCTION_WITH_LITERAL (slli, _mm_slli_epi16, M128I_U16, M128I_U16)

				DEFINE_MMX_UNARY_FUNCTION_WITH_LITERAL (slli, _mm_slli_epi32, M128I_I32, M128I_I32)
				DEFINE_MMX_UNARY_FUNCTION_WITH_LITERAL (slli, _mm_slli_epi32, M128I_U32, M128I_U32)

				DEFINE_MMX_UNARY_FUNCTION_WITH_LITERAL (slli, _mm_slli_epi64, M128I_I64, M128I_I64)
				DEFINE_MMX_UNARY_FUNCTION_WITH_LITERAL (slli, _mm_slli_epi64, M128I_U64, M128I_U64)

				DEFINE_MMX_BINARY_FUNCTION (sra, _mm_sra_epi16, M128I_I16, M128I_U16, M128I_I16)
				DEFINE_MMX_BINARY_FUNCTION (sra, _mm_sra_epi32, M128I_I32, M128I_U32, M128I_I32)

				DEFINE_MMX_BINARY_FUNCTION (sra, _mm_srai_epi16, M128I_I16, int, M128I_I16)
				DEFINE_MMX_BINARY_FUNCTION (sra, _mm_srai_epi32, M128I_I32, int, M128I_I32)

				DEFINE_MMX_UNARY_FUNCTION_WITH_LITERAL (srai, _mm_srai_epi16, M128I_I16, M128I_I16)
				DEFINE_MMX_UNARY_FUNCTION_WITH_LITERAL (srai, _mm_srai_epi32, M128I_I32, M128I_I32)
// _mm_srai_epi64 doesn't exist!
//				DEFINE_MMX_UNARY_FUNCTION_WITH_LITERAL (srai, _mm_srai_epi64, M128I_I64, M128I_I64)

				DEFINE_MMX_BINARY_FUNCTION (srl, _mm_srl_epi16, M128I_I16, M128I_U16, M128I_I16)
				DEFINE_MMX_BINARY_FUNCTION (srl, _mm_srl_epi16, M128I_U16, M128I_U16, M128I_U16)

				DEFINE_MMX_BINARY_FUNCTION (srl, _mm_srli_epi16, M128I_I16, int, M128I_I16)
				DEFINE_MMX_BINARY_FUNCTION (srl, _mm_srli_epi16, M128I_U16, int, M128I_U16)

				DEFINE_MMX_BINARY_FUNCTION (srl, _mm_srl_epi32, M128I_I32, M128I_U32, M128I_I32)
				DEFINE_MMX_BINARY_FUNCTION (srl, _mm_srl_epi32, M128I_U32, M128I_U32, M128I_U32)

				DEFINE_MMX_BINARY_FUNCTION (srl, _mm_srli_epi32, M128I_I32, int, M128I_I32)
				DEFINE_MMX_BINARY_FUNCTION (srl, _mm_srli_epi32, M128I_U32, int, M128I_U32)

				DEFINE_MMX_BINARY_FUNCTION (srl, _mm_srl_epi64, M128I_I64, M128I_U64, M128I_I64)
				DEFINE_MMX_BINARY_FUNCTION (srl, _mm_srl_epi64, M128I_U64, M128I_U64, M128I_U64)

				DEFINE_MMX_BINARY_FUNCTION (srl, _mm_srli_epi64, M128I_I64, int, M128I_I64)
				DEFINE_MMX_BINARY_FUNCTION (srl, _mm_srli_epi64, M128I_U64, int, M128I_U64)

				DEFINE_MMX_UNARY_FUNCTION_WITH_LITERAL (srli, _mm_srli_epi16, M128I_I16, M128I_I16)
				DEFINE_MMX_UNARY_FUNCTION_WITH_LITERAL (srli, _mm_srli_epi16, M128I_U16, M128I_U16)

				DEFINE_MMX_UNARY_FUNCTION_WITH_LITERAL (srli, _mm_srli_epi32, M128I_I32, M128I_I32)
				DEFINE_MMX_UNARY_FUNCTION_WITH_LITERAL (srli, _mm_srli_epi32, M128I_U32, M128I_U32)

				DEFINE_MMX_UNARY_FUNCTION_WITH_LITERAL (srli, _mm_srli_epi64, M128I_I64, M128I_I64)
				DEFINE_MMX_UNARY_FUNCTION_WITH_LITERAL (srli, _mm_srli_epi64, M128I_U64, M128I_U64)

				// AVX Integer Memory Intrinsics

				DEFINE_MMX_LOAD (load, _mm_load_si128, signed char, __m128i, M128I_I8)
				DEFINE_MMX_LOAD (load, _mm_load_si128, unsigned char, __m128i, M128I_U8)
				DEFINE_MMX_LOAD (load, _mm_load_si128, boolean <char>, __m128i, M128I_B8)
				DEFINE_MMX_LOAD (load, _mm_load_si128, short, __m128i, M128I_I16)
				DEFINE_MMX_LOAD (load, _mm_load_si128, unsigned short, __m128i, M128I_U16)
				DEFINE_MMX_LOAD (load, _mm_load_si128, boolean <short>*, __m128i, M128I_B16)
				DEFINE_MMX_LOAD (load, _mm_load_si128, int, __m128i, M128I_I32)
				DEFINE_MMX_LOAD (load, _mm_load_si128, unsigned int, __m128i, M128I_U32)
				DEFINE_MMX_LOAD (load, _mm_load_si128, boolean <int>, __m128i, M128I_B32)
// 				DEFINE_MMX_LOAD (load, _mm_load_si128, long long, __m128i, M128I_I64)
// 				DEFINE_MMX_LOAD (load, _mm_load_si128, unsigned long long, __m128i, M128I_U64)
// 				DEFINE_MMX_LOAD (load, _mm_load_si128, boolean <long long>, __m128i, M128I_B64)
				DEFINE_MMX_LOAD (load, _mm256_load_si256, long long, __m256i, M256I_I64)
				DEFINE_MMX_LOAD (load, _mm256_load_si256, unsigned long long, __m256i, M256I_U64)
				DEFINE_MMX_LOAD (load, _mm256_load_si256, boolean <long long>, __m256i, M256I_B64)

				DEFINE_MMX_LOAD (loadu, _mm_loadu_si128, signed char, __m128i, M128I_I8)
				DEFINE_MMX_LOAD (loadu, _mm_loadu_si128, unsigned char, __m128i, M128I_U8)
				DEFINE_MMX_LOAD (loadu, _mm_loadu_si128, boolean <char>, __m128i, M128I_B8)
				DEFINE_MMX_LOAD (loadu, _mm_loadu_si128, short, __m128i, M128I_I16)
				DEFINE_MMX_LOAD (loadu, _mm_loadu_si128, unsigned short, __m128i, M128I_U16)
				DEFINE_MMX_LOAD (loadu, _mm_loadu_si128, boolean <short>, __m128i, M128I_B16)
				DEFINE_MMX_LOAD (loadu, _mm_loadu_si128, int, __m128i, M128I_I32)
				DEFINE_MMX_LOAD (loadu, _mm_loadu_si128, unsigned int, __m128i, M128I_U32)
				DEFINE_MMX_LOAD (loadu, _mm_loadu_si128, boolean <int>, __m128i, M128I_B32)
// 				DEFINE_MMX_LOAD (loadu, _mm_loadu_si128, long long, __m128i, M128I_I64)
// 				DEFINE_MMX_LOAD (loadu, _mm_loadu_si128, unsigned long long, __m128i, M128I_U64)
// 				DEFINE_MMX_LOAD (loadu, _mm_loadu_si128, boolean <long long>, __m128i, M128I_B64)
				DEFINE_MMX_LOAD (loadu, _mm256_loadu_si256, long long, __m256i, M256I_I64)
				DEFINE_MMX_LOAD (loadu, _mm256_loadu_si256, unsigned long long, __m256i, M256I_U64)
				DEFINE_MMX_LOAD (loadu, _mm256_loadu_si256, boolean <long long>, __m256i, M256I_B64)

				DEFINE_MMX_STORE (store, _mm_store_si128, signed char, __m128i, M128I_I8)
				DEFINE_MMX_STORE (store, _mm_store_si128, unsigned char, __m128i, M128I_U8)
				DEFINE_MMX_STORE (store, _mm_store_si128, boolean <char>, __m128i, M128I_B8)
				DEFINE_MMX_STORE (store, _mm_store_si128, short, __m128i, M128I_I16)
				DEFINE_MMX_STORE (store, _mm_store_si128, unsigned short, __m128i, M128I_U16)
				DEFINE_MMX_STORE (store, _mm_store_si128, boolean <short>, __m128i, M128I_B16)
				DEFINE_MMX_STORE (store, _mm_store_si128, int, __m128i, M128I_I32)
				DEFINE_MMX_STORE (store, _mm_store_si128, unsigned int, __m128i, M128I_U32)
				DEFINE_MMX_STORE (store, _mm_store_si128, boolean <int>, __m128i, M128I_B32)
				DEFINE_MMX_STORE (store, _mm_store_si128, long long, __m128i, M128I_I64)
				DEFINE_MMX_STORE (store, _mm_store_si128, unsigned long long, __m128i, M128I_U64)
				DEFINE_MMX_STORE (store, _mm_store_si128, boolean <long long>, __m128i, M128I_B64)
				DEFINE_MMX_STORE (store, _mm256_store_si256, long long, __m256i, M256I_I64)
				DEFINE_MMX_STORE (store, _mm256_store_si256, unsigned long long, __m256i, M256I_U64)
				DEFINE_MMX_STORE (store, _mm256_store_si256, boolean <long long>, __m256i, M256I_B64)

				DEFINE_MMX_STORE (storeu, _mm_storeu_si128, signed char, __m128i, M128I_I8)
				DEFINE_MMX_STORE (storeu, _mm_storeu_si128, unsigned char, __m128i, M128I_U8)
				DEFINE_MMX_STORE (storeu, _mm_storeu_si128, boolean <char>, __m128i, M128I_B8)
				DEFINE_MMX_STORE (storeu, _mm_storeu_si128, short, __m128i, M128I_I16)
				DEFINE_MMX_STORE (storeu, _mm_storeu_si128, unsigned short, __m128i, M128I_U16)
				DEFINE_MMX_STORE (storeu, _mm_storeu_si128, boolean <short>, __m128i, M128I_B16)
				DEFINE_MMX_STORE (storeu, _mm_storeu_si128, int, __m128i, M128I_I32)
				DEFINE_MMX_STORE (storeu, _mm_storeu_si128, unsigned int, __m128i, M128I_U32)
				DEFINE_MMX_STORE (storeu, _mm_storeu_si128, boolean <int>, __m128i, M128I_B32)
				DEFINE_MMX_STORE (storeu, _mm_storeu_si128, long long, __m128i, M128I_I64)
				DEFINE_MMX_STORE (storeu, _mm_storeu_si128, unsigned long long, __m128i, M128I_U64)
				DEFINE_MMX_STORE (storeu, _mm_storeu_si128, boolean <long long>, __m128i, M128I_B64)
				DEFINE_MMX_STORE (storeu, _mm256_storeu_si256, long long, __m256i, M256I_I64)
				DEFINE_MMX_STORE (storeu, _mm256_storeu_si256, unsigned long long, __m256i, M256I_U64)
				DEFINE_MMX_STORE (storeu, _mm256_storeu_si256, boolean <long long>, __m256i, M256I_B64)

				// SSE2 Integer Miscellaneous Intrinsics

				DEFINE_MMX_UNARY_FUNCTION_WITH_LITERAL (extract, _mm_extract_epi16, M128I_I16, short)
				DEFINE_MMX_UNARY_FUNCTION_WITH_LITERAL (extract, _mm_extract_epi16, M128I_U16, unsigned short)
				DEFINE_MMX_UNARY_FUNCTION_WITH_LITERAL (extract, _mm_extract_epi16, M128I_B16, boolean <short>)

				DEFINE_MMX_BINARY_FUNCTION_WITH_LITERAL (insert, _mm_insert_epi16, M128I_I16, short, M128I_I16)
				DEFINE_MMX_BINARY_FUNCTION_WITH_LITERAL (insert, _mm_insert_epi16, M128I_U16, unsigned short, M128I_U16)
				DEFINE_MMX_BINARY_FUNCTION_WITH_LITERAL (insert, _mm_insert_epi16, M128I_B16, boolean <short>, M128I_B16)

				DEFINE_MMX_UNARY_FUNCTION (movemask, _mm_movemask_epi8, M128I_I8, unsigned int)
				DEFINE_MMX_UNARY_FUNCTION (movemask, _mm_movemask_epi8, M128I_U8, unsigned int)
				DEFINE_MMX_UNARY_FUNCTION (movemask, _mm_movemask_epi8, M128I_B8, unsigned int)

				DEFINE_MMX_BINARY_FUNCTION (packs, _mm_packs_epi16, M128I_I16, M128I_I16, M128I_I8)
				DEFINE_MMX_BINARY_FUNCTION (packs, _mm_packs_epi32, M128I_I32, M128I_I32, M128I_I16)

				DEFINE_MMX_BINARY_FUNCTION (packus, _mm_packus_epi16, M128I_I16, M128I_I16, M128I_U8)

				DEFINE_MMX_UNARY_SHUFFLE4 (shuffle, _mm_shuffle_epi32, M128I_I32, M128I_I32)
				DEFINE_MMX_UNARY_SHUFFLE4 (shuffle, _mm_shuffle_epi32, M128I_U32, M128I_U32)
				DEFINE_MMX_UNARY_SHUFFLE4 (shuffle, _mm_shuffle_epi32, M128I_B32, M128I_B32)

				DEFINE_MMX_UNARY_SHUFFLE4 (shufflehi, _mm_shufflehi_epi16, M128I_I16, M128I_I16)
				DEFINE_MMX_UNARY_SHUFFLE4 (shufflehi, _mm_shufflehi_epi16, M128I_U16, M128I_U16)
				DEFINE_MMX_UNARY_SHUFFLE4 (shufflehi, _mm_shufflehi_epi16, M128I_B16, M128I_B16)

				DEFINE_MMX_UNARY_SHUFFLE4 (shufflelo, _mm_shufflelo_epi16, M128I_I16, M128I_I16)
				DEFINE_MMX_UNARY_SHUFFLE4 (shufflelo, _mm_shufflelo_epi16, M128I_U16, M128I_U16)
				DEFINE_MMX_UNARY_SHUFFLE4 (shufflelo, _mm_shufflelo_epi16, M128I_B16, M128I_B16)

				DEFINE_MMX_BINARY_FUNCTION (unpackhi, _mm_unpackhi_epi8, M128I_I8, M128I_I8, M128I_I8)
				DEFINE_MMX_BINARY_FUNCTION (unpackhi, _mm_unpackhi_epi8, M128I_U8, M128I_U8, M128I_U8)
				DEFINE_MMX_BINARY_FUNCTION (unpackhi, _mm_unpackhi_epi8, M128I_B8, M128I_B8, M128I_B8)
				DEFINE_MMX_BINARY_FUNCTION (unpackhi, _mm_unpackhi_epi16, M128I_I16, M128I_I16, M128I_I16)
				DEFINE_MMX_BINARY_FUNCTION (unpackhi, _mm_unpackhi_epi16, M128I_U16, M128I_U16, M128I_U16)
				DEFINE_MMX_BINARY_FUNCTION (unpackhi, _mm_unpackhi_epi16, M128I_B16, M128I_B16, M128I_B16)
				DEFINE_MMX_BINARY_FUNCTION (unpackhi, _mm_unpackhi_epi32, M128I_I32, M128I_I32, M128I_I32)
				DEFINE_MMX_BINARY_FUNCTION (unpackhi, _mm_unpackhi_epi32, M128I_U32, M128I_U32, M128I_U32)
				DEFINE_MMX_BINARY_FUNCTION (unpackhi, _mm_unpackhi_epi32, M128I_B32, M128I_B32, M128I_B32)
				DEFINE_MMX_BINARY_FUNCTION (unpackhi, _mm_unpackhi_epi64, M128I_I64, M128I_I64, M128I_I64)
				DEFINE_MMX_BINARY_FUNCTION (unpackhi, _mm_unpackhi_epi64, M128I_U64, M128I_U64, M128I_U64)
				DEFINE_MMX_BINARY_FUNCTION (unpackhi, _mm_unpackhi_epi64, M128I_B64, M128I_B64, M128I_B64)

				DEFINE_MMX_BINARY_FUNCTION (unpacklo, _mm_unpacklo_epi8, M128I_I8, M128I_I8, M128I_I8)
				DEFINE_MMX_BINARY_FUNCTION (unpacklo, _mm_unpacklo_epi8, M128I_U8, M128I_U8, M128I_U8)
				DEFINE_MMX_BINARY_FUNCTION (unpacklo, _mm_unpacklo_epi8, M128I_B8, M128I_B8, M128I_B8)
				DEFINE_MMX_BINARY_FUNCTION (unpacklo, _mm_unpacklo_epi16, M128I_I16, M128I_I16, M128I_I16)
				DEFINE_MMX_BINARY_FUNCTION (unpacklo, _mm_unpacklo_epi16, M128I_U16, M128I_U16, M128I_U16)
				DEFINE_MMX_BINARY_FUNCTION (unpacklo, _mm_unpacklo_epi16, M128I_B16, M128I_B16, M128I_B16)
				DEFINE_MMX_BINARY_FUNCTION (unpacklo, _mm_unpacklo_epi32, M128I_I32, M128I_I32, M128I_I32)
				DEFINE_MMX_BINARY_FUNCTION (unpacklo, _mm_unpacklo_epi32, M128I_U32, M128I_U32, M128I_U32)
				DEFINE_MMX_BINARY_FUNCTION (unpacklo, _mm_unpacklo_epi32, M128I_B32, M128I_B32, M128I_B32)
				DEFINE_MMX_BINARY_FUNCTION (unpacklo, _mm_unpacklo_epi64, M128I_I64, M128I_I64, M128I_I64)
				DEFINE_MMX_BINARY_FUNCTION (unpacklo, _mm_unpacklo_epi64, M128I_U64, M128I_U64, M128I_U64)
				DEFINE_MMX_BINARY_FUNCTION (unpacklo, _mm_unpacklo_epi64, M128I_B64, M128I_B64, M128I_B64)

				#endif

				#if defined(__SSE3__) || defined(__AVX__) || defined(__AVX2__)

				DEFINE_MMX_BINARY_FUNCTION (addsub, _mm_addsub_ps, M128_F32, M128_F32, M128_F32)
				DEFINE_MMX_BINARY_FUNCTION (hadd, _mm_hadd_ps, M128_F32, M128_F32, M128_F32)
				DEFINE_MMX_BINARY_FUNCTION (hsub, _mm_hsub_ps, M128_F32, M128_F32, M128_F32)
				DEFINE_MMX_UNARY_FUNCTION (movehdup, _mm_movehdup_ps, M128_F32, M128_F32)
				DEFINE_MMX_UNARY_FUNCTION (moveldup, _mm_moveldup_ps, M128_F32, M128_F32)

				DEFINE_MMX_BINARY_FUNCTION (addsub, _mm_addsub_pd, M128D_F64, M128D_F64, M128D_F64)
				DEFINE_MMX_BINARY_FUNCTION (hadd, _mm_hadd_pd, M128D_F64, M128D_F64, M128D_F64)
				DEFINE_MMX_BINARY_FUNCTION (hsub, _mm_hsub_pd, M128D_F64, M128D_F64, M128D_F64)
				DEFINE_MMX_UNARY_FUNCTION (movedup, _mm_movedup_pd, M128D_F64, M128D_F64)

				DEFINE_MMX_BINARY_FUNCTION (addsub, _mm256_addsub_ps, M256_F32, M256_F32, M256_F32)
				DEFINE_MMX_BINARY_FUNCTION (hadd, _mm256_hadd_ps, M256_F32, M256_F32, M256_F32)
				DEFINE_MMX_BINARY_FUNCTION (hsub, _mm256_hsub_ps, M256_F32, M256_F32, M256_F32)
				DEFINE_MMX_UNARY_FUNCTION (movehdup, _mm256_movehdup_ps, M256_F32, M256_F32)
				DEFINE_MMX_UNARY_FUNCTION (moveldup, _mm256_moveldup_ps, M256_F32, M256_F32)

				DEFINE_MMX_BINARY_FUNCTION (addsub, _mm256_addsub_pd, M256D_F64, M256D_F64, M256D_F64)
				DEFINE_MMX_BINARY_FUNCTION (hadd, _mm256_hadd_pd, M256D_F64, M256D_F64, M256D_F64)
				DEFINE_MMX_BINARY_FUNCTION (hsub, _mm256_hsub_pd, M256D_F64, M256D_F64, M256D_F64)
				DEFINE_MMX_UNARY_FUNCTION (movedup, _mm256_movedup_pd, M256D_F64, M256D_F64)

				#endif

				#if defined(__SSE4__) || defined(__SSE4_1__) || defined(__SSE4_2__) || defined(__AVX__) || defined(__AVX2__)
				DEFINE_MMX_BINARY_FUNCTION_WITH_CONSTINT(blend, _mm_blend_ps, M128_F32, M128_F32, M128_F32)
				DEFINE_MMX_BINARY_FUNCTION_WITH_CONSTINT(dprod, _mm_dp_ps, M128_F32, M128_F32, M128_F32)
				DEFINE_MMX_UNARY_FUNCTION_WITH_CONSTINT(round, _mm_round_ps, M128_F32, M128_F32)

				DEFINE_MMX_BINARY_FUNCTION_WITH_CONSTINT(blend, _mm_blend_pd, M128D_F64, M128D_F64, M128D_F64)
				DEFINE_MMX_BINARY_FUNCTION_WITH_CONSTINT(dprod, _mm_dp_pd, M128D_F64, M128D_F64, M128D_F64)
				DEFINE_MMX_UNARY_FUNCTION_WITH_CONSTINT(round, _mm_round_pd, M128D_F64, M128D_F64)

				DEFINE_MMX_BINARY_FUNCTION_WITH_CONSTINT(blend, _mm256_blend_ps, M256_F32, M256_F32, M256_F32)
				DEFINE_MMX_BINARY_FUNCTION_WITH_CONSTINT(blend, _mm256_blend_pd, M256D_F64, M256D_F64, M256D_F64)
				DEFINE_MMX_BINARY_FUNCTION_WITH_CONSTINT(dprod, _mm256_dp_ps, M256_F32, M256_F32, M256_F32)
				DEFINE_MMX_UNARY_FUNCTION_WITH_CONSTINT(round, _mm256_round_ps, M256_F32, M256_F32)
				DEFINE_MMX_UNARY_FUNCTION_WITH_CONSTINT(round, _mm256_round_pd, M256D_F64, M256D_F64)
				#endif

				/// MMX/SSE/SSE2/SSE3/AVX intrinsics implementation.
				namespace impl
					{
						// sin (x) -- where x is in [-Pi/2, Pi/2]
						INLINE const vec <float, 4> sine_reduced (const vec <float, 4>& x)
							{
								// minimax polynomial of degree 9, odd powers only on [0, Pi/2] -- because p(x) == -p(-x) this works also for [-Pi/2,0]
								// NOTE: we got a minimax polynomial of degree 4 on sin(sqrt(x))/sqrt(x) on [0, (Pi^2)/4], then expanded it out
								const vec <float, 4> xx = mmx::mul (x, x);
								return
									mmx::mul (
										mmx::add (mmx::mul (
											mmx::add (mmx::mul (
												mmx::add (mmx::mul (
													mmx::add (mmx::mul (
														xx, vec <float, 4>::fill <0x362E9C5BU> ()),	// 2.60190306765133772461701600763e-6 x^9
														vec <float, 4>::fill <0xB94FB223U> ()),		// -0.000198074187274269112790200299439 x^7
													xx), vec <float, 4>::fill <0x3C08873EU> ()),		// 0.00833302513896936648486927563199 x^5
												xx), vec <float, 4>::fill <0xBE2AAAA4U> ()),			// -0.166666566840071513511254831176 x^3
											xx), vec <float, 4>::fill <0x3F800000U> ()),				// 0.999999994686007336962522087826 x
										x);
							}
						INLINE const vec <double, 2> sine_reduced (const vec <double, 2>& x)
							{
								// minimax polynomial of degree 9, odd powers only on [0, Pi/2] -- because p(x) == -p(-x) this works also for [-Pi/2,0]
								// NOTE: we got a minimax polynomial of degree 4 on sin(sqrt(x))/sqrt(x) on [0, (Pi^2)/4], then expanded it out
								const vec <double, 2> xx = mmx::mul (x, x);
								return
									mmx::mul (
										mmx::add (mmx::mul (
											mmx::add (mmx::mul (
												mmx::add (mmx::mul (
													mmx::add (mmx::mul (
														xx, vec <double, 2>::fill <0x362E9C5BU> ()),	// 2.60190306765133772461701600763e-6 x^9
														vec <double, 2>::fill <0xB94FB223U> ()),		// -0.000198074187274269112790200299439 x^7
													xx), vec <double, 2>::fill <0x3C08873EU> ()),		// 0.00833302513896936648486927563199 x^5
												xx), vec <double, 2>::fill <0xBE2AAAA4U> ()),			// -0.166666566840071513511254831176 x^3
											xx), vec <double, 2>::fill <0x3F800000U> ()),				// 0.999999994686007336962522087826 x
										x);
							}
						INLINE const vec <float, 8> sine_reduced (const vec <float, 8>& x)
							{
								// minimax polynomial of degree 9, odd powers only on [0, Pi/2] -- because p(x) == -p(-x) this works also for [-Pi/2,0]
								// NOTE: we got a minimax polynomial of degree 4 on sin(sqrt(x))/sqrt(x) on [0, (Pi^2)/4], then expanded it out
								const vec <float, 8> xx = mmx::mul (x, x);
								return
									mmx::mul (
										mmx::add (mmx::mul (
											mmx::add (mmx::mul (
												mmx::add (mmx::mul (
													mmx::add (mmx::mul (
														xx, vec <float, 8>::fill <0x362E9C5BU> ()),	// 2.60190306765133772461701600763e-6 x^9
														vec <float, 8>::fill <0xB94FB223U> ()),		// -0.000198074187274269112790200299439 x^7
													xx), vec <float, 8>::fill <0x3C08873EU> ()),		// 0.00833302513896936648486927563199 x^5
												xx), vec <float, 8>::fill <0xBE2AAAA4U> ()),			// -0.166666566840071513511254831176 x^3
											xx), vec <float, 8>::fill <0x3F800000U> ()),				// 0.999999994686007336962522087826 x
										x);
							}
						INLINE const vec <double, 4> sine_reduced (const vec <double, 4>& x)
							{
								// minimax polynomial of degree 9, odd powers only on [0, Pi/2] -- because p(x) == -p(-x) this works also for [-Pi/2,0]
								// NOTE: we got a minimax polynomial of degree 4 on sin(sqrt(x))/sqrt(x) on [0, (Pi^2)/4], then expanded it out
								const vec <double, 4> xx = mmx::mul (x, x);
								return
									mmx::mul (
										mmx::add (mmx::mul (
											mmx::add (mmx::mul (
												mmx::add (mmx::mul (
													mmx::add (mmx::mul (
														xx, vec <double, 4>::fill <0x362E9C5BU> ()),	// 2.60190306765133772461701600763e-6 x^9
														vec <double, 4>::fill <0xB94FB223U> ()),		// -0.000198074187274269112790200299439 x^7
													xx), vec <double, 4>::fill <0x3C08873EU> ()),		// 0.00833302513896936648486927563199 x^5
												xx), vec <double, 4>::fill <0xBE2AAAA4U> ()),			// -0.166666566840071513511254831176 x^3
											xx), vec <double, 4>::fill <0x3F800000U> ()),				// 0.999999994686007336962522087826 x
										x);
							}
					}
			}
	}

namespace stdext
	{

		template <typename T, typename V> INLINE T __mvectorelem(V v, int i)
		{
			return ((T*)&v)[i];
		}

		// absolute

		template <typename T, std::size_t n> struct absolute <macstl::vec <macstl::boolean <T>, n> >
			{
				typedef macstl::vec <macstl::boolean <T>, n> argument_type;
				typedef macstl::vec <macstl::boolean <T>, n> result_type;

				INLINE const result_type operator() (const argument_type& lhs) const
					{
						return lhs;
					}
			};

		template <> struct absolute <macstl::vec <float, 4> >
			{
				typedef macstl::vec <float, 4> argument_type;
				typedef macstl::vec <float, 4> result_type;

				INLINE const result_type operator() (const argument_type& lhs) const
					{
						using namespace macstl;

						return mmx::vand (argument_type::fill <0x7FFFFFFFU> (), lhs);
					}
			};

		template <> struct absolute <macstl::vec <float, 8> >
			{
				typedef macstl::vec <float, 8> argument_type;
				typedef macstl::vec <float, 8> result_type;

				INLINE const result_type operator() (const argument_type& lhs) const
					{
						using namespace macstl;

						return mmx::vand (argument_type::fill <0x7FFFFFFFU> (), lhs);
					}
			};

		template <> struct absolute <macstl::vec <double, 2> >
			{
				typedef macstl::vec <double, 2> argument_type;
				typedef macstl::vec <double, 2> result_type;

				INLINE const result_type operator() (const argument_type& lhs) const
					{
						using namespace macstl;

						return mmx::andnot (argument_type::fill <0x7FFFFFFFFFFFFFFFULL> (), lhs);
					}
			};

		template <> struct absolute <macstl::vec <double, 4> >
			{
				typedef macstl::vec <double, 4> argument_type;
				typedef macstl::vec <double, 4> result_type;

				INLINE const result_type operator() (const argument_type& lhs) const
					{
						using namespace macstl;

						return mmx::andnot (argument_type::fill <0x7FFFFFFFFFFFFFFFULL> (), lhs);
					}
			};


		// bitwise_and

		template <typename T, std::size_t n> struct bitwise_and <macstl::vec <T, n>, macstl::vec <T, n> >:
			public macstl::mmx::vand_function <macstl::vec <T, n>, macstl::vec <T, n> >
			{
			};

		template <std::size_t n> struct bitwise_and <macstl::vec <float, n>, macstl::vec <float, n> >;
		template <std::size_t n> struct bitwise_and <macstl::vec <double, n>, macstl::vec <double, n> >;

		// bitwise_not

		template <typename T, std::size_t n> struct bitwise_not <macstl::vec <T, n> >
			{
				typedef macstl::vec <T, n> argument_type;
				typedef macstl::vec <T, n> result_type;

				INLINE const result_type operator() (const argument_type& lhs) const
					{
						using namespace macstl;

						return mmx::vxor (lhs, argument_type::template fill <-1> ());
					}
			};

		template <typename T, std::size_t n> struct bitwise_not <macstl::vec <macstl::boolean <T>, n> >
			{
				typedef macstl::vec <macstl::boolean <T>, n> argument_type;
				typedef macstl::vec <macstl::boolean <T>, n> result_type;

				INLINE const result_type operator() (const argument_type&) const
					{
						return argument_type::template fill <true> ();
					}
			};

		template <std::size_t n> struct bitwise_not <macstl::vec <float, n> >;
		template <std::size_t n> struct bitwise_not <macstl::vec <double, n> >;

		// bitwise_or

		template <typename T, std::size_t n> struct bitwise_or <macstl::vec <T, n>, macstl::vec <T, n> >:
			public macstl::mmx::vor_function <macstl::vec <T, n>, macstl::vec <T, n> >
			{
			};

		template <std::size_t n> struct bitwise_or <macstl::vec <float, n>, macstl::vec <float, n> >;
		template <std::size_t n> struct bitwise_or <macstl::vec <double, n>, macstl::vec <double, n> >;

		// bitwise_xor

		template <typename T, std::size_t n> struct bitwise_xor <macstl::vec <T, n>, macstl::vec <T, n> >:
			public macstl::mmx::vxor_function <macstl::vec <T, n>, macstl::vec <T, n> >
			{
			};

		template <std::size_t n> struct bitwise_xor <macstl::vec <float, n>, macstl::vec <float, n> >;
		template <std::size_t n> struct bitwise_xor <macstl::vec <double, n>, macstl::vec <double, n> >;

		// cosine

		#if defined(__SSE__) && defined(__SSE2__)

		// RJVB
		struct sinecosine
			{
				typedef macstl::vec <double, 2> argument_type;
				typedef macstl::vec <double, 2> result_type;
				typedef macstl::vec <double, 4> argument4_type;
				typedef macstl::vec <double, 4> result4_type;
				typedef macstl::vec <float, 8> argument8_type;
				typedef macstl::vec <float, 8> result8_type;
				typedef __m256d v4df;
				typedef __m128d v2df;
				typedef __m256 v8sf;
				typedef __m128 v4sf;
				typedef __m128i v4si;
				typedef __m256i v8si;

				/*!
				 calculates the sine and cosine of lhs, returning them in an AVX vec<double,4>
				 structure.
				 */
// 				INLINE const macstl::vec<double, 4> operator() (const argument_type &lhs) const
// 					{
// 						using namespace macstl;
// 						result_type cs[2];
// 						v2df x = lhs.data();
//
// 						static const v2df _pd_sign_mask = _mm_set1_pd(0x8000000000000000LL);
// 						static const v2df _pd_inv_sign_mask = _mm_set1_pd(~0x8000000000000000LL);
// 						static const v2df _pd_1 = _mm_set1_pd(1.0);
// 						static const v2df _pd_0p5 = _mm_set1_pd(0.5);
// 						static const v2df _pd_cephes_FOPI = _mm_set1_pd(1.27323954473516);
// 						static const v2df _pd_minus_cephes_DP1 = _mm_set1_pd(-0.78515625);
// 						static const v2df _pd_minus_cephes_DP2 = _mm_set1_pd(-2.4187564849853515625e-4);
// 						static const v2df _pd_minus_cephes_DP3 = _mm_set1_pd(-3.77489497744594108e-8);
// 						static const v2df _pd_sincof_p0 = _mm_set1_pd(-1.9515295891E-4);
// 						static const v2df _pd_sincof_p1 = _mm_set1_pd( 8.3321608736E-3);
// 						static const v2df _pd_sincof_p2 = _mm_set1_pd(-1.6666654611E-1);
// 						static const v2df _pd_coscof_p0 = _mm_set1_pd( 2.443315711809948E-005);
// 						static const v2df _pd_coscof_p1 = _mm_set1_pd(-1.388731625493765E-003);
// 						static const v2df _pd_coscof_p2 = _mm_set1_pd( 4.166664568298827E-002);
// 						static const v4si _pi32_1 = _mm_set1_epi32(1);
// 						static const v4si _pi32_inv1 = _mm_set1_epi32(~1);
// 						static const v4si _pi32_2 = _mm_set1_epi32(2);
// 						static const v4si _pi32_4 = _mm_set1_epi32(4);
//
// 						v2df xmm1, xmm2, sign_bit_sin, y, y2, z, swap_sign_bit_sin, poly_mask;
// 						v2df sign_bit_cos;
// 						v4si emm2;
// 						sign_bit_sin = x;
// 						/* take the absolute value */
// 						x = _mm_and_pd(x, _pd_inv_sign_mask);
// 						/* extract the sign bit (upper one) */
// 						sign_bit_sin = _mm_and_pd(sign_bit_sin, _pd_sign_mask);
//
// 						/* scale by 4/Pi */
// 						y = _mm_mul_pd(x, _pd_cephes_FOPI);
//
// 						/* store the integer part of y in emm2 */
// 						emm2 = _mm_cvttpd_epi32(y);
//
// 						/* j=(j+1) & (~1) (see the cephes sources) */
// 						emm2 = _mm_and_si128( _mm_add_epi64( _mm_cvttpd_epi32(y), _pi32_1 ), _pi32_inv1 );
// 						y = _mm_cvtepi32_pd(emm2);
//
// 						/* get the swap sign flag for the sine */
// 						{ v4sf sss = _mm_castsi128_ps( _mm_slli_epi32( _mm_and_si128(emm2, _pi32_4), 29) );
// 							float *fsss = ((float*)&sss);
// 							swap_sign_bit_sin = _mm_setr_pd( fsss[0], fsss[1] );
// 						}
//
// 						/* get the polynom selection mask for the sine*/
// 						{ v4sf pm = _mm_castsi128_ps( _mm_cmpeq_epi32( _mm_and_si128(emm2, _pi32_2), _mm_setzero_si128()) );
// 							float *fpm = ((float*)&pm);
// 							poly_mask = _mm_setr_pd( fpm[0], fpm[1] );
// 						}
//
// 						/* The magic pass: "Extended precision modular arithmetic"
// 						 x = ((x - y * DP1) - y * DP2) - y * DP3; */
// #ifdef __GNUC__
// 						x += y * ( _pd_minus_cephes_DP1 + _pd_minus_cephes_DP2 + _pd_minus_cephes_DP3 );
// #else
// 						x = _mm_add_pd( x, _mm_mul_pd( y, _mm_add_pd( _mm_add_pd(_pd_minus_cephes_DP1, _pd_minus_cephes_DP2),
// 															_pd_minus_cephes_DP3 ) ) );
// #endif
//
// 						{ v4sf sbc = _mm_castsi128_ps( _mm_slli_epi32( _mm_andnot_si128( _mm_sub_epi32(emm2, _pi32_2), _pi32_4), 29) );
// 							float *fsbc = ((float*)&sbc);
// 							sign_bit_cos = _mm_setr_pd( fsbc[0], fsbc[1] );
// 						}
//
// 						sign_bit_sin = _mm_xor_pd(sign_bit_sin, swap_sign_bit_sin);
//
//
// 						/* Evaluate the first polynom  (0 <= x <= Pi/4) */
// #ifdef __GNUC__
// 						z = x * x;
// 						y = ( ( ( (_pd_coscof_p0) * z + _pd_coscof_p1 ) * z + _pd_coscof_p2 ) * z
// 							- _pd_0p5 ) * z + _pd_1;
// #else
// 						z = _mm_mul_pd(x,x);
// 						y = _mm_add_pd(
// 									_mm_mul_pd(
// 											 _mm_sub_pd(
// 													  _mm_mul_pd(
// 															   _mm_add_pd(
// 																	    _mm_mul_pd(
// 																				_mm_add_pd(
// 																						 _mm_mul_pd(_pd_coscof_p0, z),
// 																						 _pd_coscof_p1 ),
// 																				z ),
// 																	    _pd_coscof_p2 ),
// 															   z ),
// 													  _pd_0p5 ),
// 											 z ),
// 									_pd_1 );
// #endif
//
// 						/* Evaluate the second polynom  (Pi/4 <= x <= 0) */
//
// #ifdef __GNUC__
// 						y2 = ( ( ( ( ((_pd_sincof_p0) * z ) + _pd_sincof_p1 ) * z ) + _pd_sincof_p2 ) * z
// 							 + _pd_1 ) * x;
// #else
// 						y2 = _mm_mul_pd(
// 									 _mm_add_pd(
// 											  _mm_mul_pd(
// 													   _mm_add_pd(
// 															    _mm_mul_pd(
// 																		_mm_add_pd(
// 																				 _mm_mul_pd(_pd_sincof_p0, z ),
// 																				 _pd_sincof_p1 ),
// 																		z ),
// 															    _pd_sincof_p2 ),
// 													   z ),
// 											  _pd_1 ),
// 									 x );
// #endif
//
// 						/* select the correct result from the two polynoms */
// 						{
// 							xmm1 = _mm_add_pd( _mm_andnot_pd( poly_mask, y), _mm_and_pd(poly_mask, y2) );
// 							xmm2 = _mm_sub_pd( _mm_add_pd( y, y2 ), xmm1 );
// 							/* update the sign */
// 							cs[0] = _mm_xor_pd(xmm1, sign_bit_sin);
// 							cs[1] = _mm_xor_pd(xmm2, sign_bit_cos);
// 						}
//
// 						return *((vec<double,4>*)&cs[0]);
// 					}

#ifndef VECSSE_SINCOS_DOUBLE2_VIA_FLOAT4
				/*!
				 evaluation of 2 sines at onces, using SSE2 intrinsics.
				 From Julien Pommier's sse_mathfun.h, adapted by RJVB
				 @n
				 The code is the exact rewriting of the cephes sinf function.
				 Precision is excellent as long as x < 8192 (I did not bother to
				 take into account the special handling they have for greater values
				 -- it does not return garbage for arguments over 8192, though, but
				 the extra precision is missing).
				 @n
				 Note that it is such that sinf((float)M_PI) = 8.74e-8, which is the
				 surprising but correct result.
				 @n
				 Performance is also surprisingly good, at least 1.33 times faster than the
				 macos vsinf SSE2 function, and 1.5 times faster than the
				 __vrs4_sinf of amd's ACML (which is only available in 64 bits). Not
				 too bad for the SSE1+MMX version of this function (with no special tuning) !
				 However the latter libraries probably have a much better handling of NaN,
				 Inf, denormalized and other special arguments..
				 @n
				 On my core 1 duo, the execution of this function takes approximately 95 cycles.
				 @n
				 From what I have observed on the experiments with Intel AMath lib, switching to an
				 SSE2 version would improve the perf by only 10%.
				 @n
				 If VECSSE_SINCOS_DOUBLE2_VIA_FLOAT4 is defined before including macstl headers,
				 the sine and cosine calculations of vec<double,2> use macstl's own vec<float,4>
				 sine and cosine functions, via conversion steps. This ensures identical results on
				 the operand value range where doubles map exactly to floats. It's not clear which
				 method is preferrable, except when optimal compatibility with vec<double,4> results is
				 required.
				 */

				INLINE const result_type sin(const argument_type &lhs) const
					{
						using namespace macstl;
						result_type sn;
						v2df x = lhs.data();

						static const v2df _pd_sign_mask = _mm_set1_pd(0x8000000000000000LL);
						static const v2df _pd_inv_sign_mask = _mm_set1_pd(~0x8000000000000000LL);
						static const v2df _pd_1 = _mm_set1_pd(1.0);
						static const v2df _pd_0p5 = _mm_set1_pd(0.5);
						static const v2df _pd_cephes_FOPI = _mm_set1_pd(1.27323954473516);
						static const v2df _pd_minus_cephes_DP1 = _mm_set1_pd(-0.78515625);
						static const v2df _pd_minus_cephes_DP2 = _mm_set1_pd(-2.4187564849853515625e-4);
						static const v2df _pd_minus_cephes_DP3 = _mm_set1_pd(-3.77489497744594108e-8);
						static const v2df _pd_sincof_p0 = _mm_set1_pd(-1.9515295891E-4);
						static const v2df _pd_sincof_p1 = _mm_set1_pd( 8.3321608736E-3);
						static const v2df _pd_sincof_p2 = _mm_set1_pd(-1.6666654611E-1);
						static const v2df _pd_coscof_p0 = _mm_set1_pd( 2.443315711809948E-005);
						static const v2df _pd_coscof_p1 = _mm_set1_pd(-1.388731625493765E-003);
						static const v2df _pd_coscof_p2 = _mm_set1_pd( 4.166664568298827E-002);
						static const v4si _pi32_1 = _mm_set1_epi32(1);
						static const v4si _pi32_inv1 = _mm_set1_epi32(~1);
						static const v4si _pi32_2 = _mm_set1_epi32(2);
						static const v4si _pi32_4 = _mm_set1_epi32(4);
						v2df sign_bit, y, y2, z;

						v2df swap_sign_bit, poly_mask;
						v4si emm0, emm2;
						sign_bit = x;
						/* take the absolute value */
						x = _mm_and_pd(x, _pd_inv_sign_mask);
						/* extract the sign bit (upper one) */
						sign_bit = _mm_and_pd(sign_bit, _pd_sign_mask);

						/* scale by 4/Pi */
						y = _mm_mul_pd(x, _pd_cephes_FOPI);

						/* store the integer part of y in mm0 */
						/* j=(j+1) & (~1) (see the cephes sources) */
						emm2 = _mm_and_si128(_mm_add_epi32(_mm_cvttpd_epi32(y), _pi32_1), _pi32_inv1);
						y = _mm_cvtepi32_pd(emm2);
						/* get the swap sign flag */
						emm0 = _mm_slli_epi32(_mm_and_si128(emm2, _pi32_4), 29);
						/* get the polynom selection mask
						 there is one polynom for 0 <= x <= Pi/4
						 and another one for Pi/4<x<=Pi/2

						 Both branches will be computed.
						 */
						emm2 = _mm_cmpeq_epi32(_mm_and_si128(emm2, _pi32_2), _mm_setzero_si128());

						swap_sign_bit = _mm_castsi128_pd(emm0);
						poly_mask = _mm_castsi128_pd(emm2);
						sign_bit = _mm_xor_pd(sign_bit, swap_sign_bit);

						/* The magic pass: "Extended precision modular arithmetic"
						 x = ((x - y * DP1) - y * DP2) - y * DP3; */
						x = _mm_add_pd( _mm_add_pd( _mm_add_pd(x, _mm_mul_pd(y, _pd_minus_cephes_DP1)), _mm_mul_pd(y, _pd_minus_cephes_DP2)), _mm_mul_pd(y, _pd_minus_cephes_DP3));

						/* Evaluate the first polynom  (0 <= x <= Pi/4) */
						y = _pd_coscof_p0;
						z = _mm_mul_pd(x,x);

						y = _mm_add_pd( _mm_sub_pd( _mm_mul_pd( _mm_mul_pd( _mm_add_pd( _mm_mul_pd( _mm_add_pd( _mm_mul_pd(y, z), _pd_coscof_p1), z), _pd_coscof_p2), z), z), _mm_mul_pd(z, _pd_0p5) ), _pd_1);

						/* Evaluate the second polynom  (Pi/4 <= x <= 0) */

						y2 = _mm_add_pd( _mm_mul_pd( _mm_mul_pd( _mm_add_pd( _mm_mul_pd( _mm_add_pd( _mm_mul_pd(_pd_sincof_p0, z), _pd_sincof_p1), z), _pd_sincof_p2), z), x), x);

						/* select the correct result from the two polynoms */
						/* update the sign */
						y2 = _mm_and_pd(poly_mask, y2); //, xmm3);
						y = _mm_xor_pd( _mm_add_pd( _mm_andnot_pd(poly_mask, y),y2), sign_bit);

						sn = y;
						return sn;
					}

				/*!
				 almost the same as the sin function
				 */
				INLINE const result_type cos(const argument_type &lhs) const
					{
						using namespace macstl;
						result_type cs;
						v2df x = lhs.data();

						static const v2df _pd_inv_sign_mask = _mm_set1_pd(~0x8000000000000000LL);
						static const v2df _pd_1 = _mm_set1_pd(1.0);
						static const v2df _pd_0p5 = _mm_set1_pd(0.5);
						static const v2df _pd_cephes_FOPI = _mm_set1_pd(1.27323954473516);
						static const v2df _pd_minus_cephes_DP1 = _mm_set1_pd(-0.78515625);
						static const v2df _pd_minus_cephes_DP2 = _mm_set1_pd(-2.4187564849853515625e-4);
						static const v2df _pd_minus_cephes_DP3 = _mm_set1_pd(-3.77489497744594108e-8);
						static const v2df _pd_sincof_p0 = _mm_set1_pd(-1.9515295891E-4);
						static const v2df _pd_sincof_p1 = _mm_set1_pd( 8.3321608736E-3);
						static const v2df _pd_sincof_p2 = _mm_set1_pd(-1.6666654611E-1);
						static const v2df _pd_coscof_p0 = _mm_set1_pd( 2.443315711809948E-005);
						static const v2df _pd_coscof_p1 = _mm_set1_pd(-1.388731625493765E-003);
						static const v2df _pd_coscof_p2 = _mm_set1_pd( 4.166664568298827E-002);
						static const v4si _pi32_1 = _mm_set1_epi32(1);
						static const v4si _pi32_inv1 = _mm_set1_epi32(~1);
						static const v4si _pi32_2 = _mm_set1_epi32(2);
						static const v4si _pi32_4 = _mm_set1_epi32(4);
						v2df y, y2, z, sign_bit, poly_mask;
						v4si emm0, emm2;

						/* take the absolute value */
						x = _mm_and_pd(x, _pd_inv_sign_mask);

						/* scale by 4/Pi */
						y = _mm_mul_pd(x, _pd_cephes_FOPI);

						/* store the integer part of y in mm0 */
						/* j=(j+1) & (~1) (see the cephes sources) */
						emm2 = _mm_and_si128( _mm_add_epi32( _mm_cvttpd_epi32(y), _pi32_1), _pi32_inv1);
						y = _mm_cvtepi32_pd(emm2);

						emm2 = _mm_sub_epi32(emm2, _pi32_2);

						/* get the swap sign flag */
						emm0 = _mm_slli_epi32( _mm_andnot_si128(emm2, _pi32_4), 29);
						/* get the polynom selection mask */
						emm2 = _mm_cmpeq_epi32( _mm_and_si128(emm2, _pi32_2), _mm_setzero_si128());

						sign_bit = _mm_castsi128_pd(emm0);
						poly_mask = _mm_castsi128_pd(emm2);

						/* The magic pass: "Extended precision modular arithmetic"
						 x = ((x - y * DP1) - y * DP2) - y * DP3; */
						x = _mm_add_pd( _mm_add_pd( _mm_add_pd(x, _mm_mul_pd(y, _pd_minus_cephes_DP1)), _mm_mul_pd(y, _pd_minus_cephes_DP2)), _mm_mul_pd(y, _pd_minus_cephes_DP3));

						/* Evaluate the first polynom  (0 <= x <= Pi/4) */
						y = _pd_coscof_p0;
						z = _mm_mul_pd(x,x);

						y = _mm_add_pd( _mm_sub_pd( _mm_mul_pd( _mm_mul_pd( _mm_add_pd( _mm_mul_pd( _mm_add_pd( _mm_mul_pd(y, z), _pd_coscof_p1), z), _pd_coscof_p2), z), z), _mm_mul_pd(z, _pd_0p5) ), _pd_1);

						/* Evaluate the second polynom  (Pi/4 <= x <= 0) */

						y2 = _mm_add_pd( _mm_mul_pd( _mm_mul_pd( _mm_add_pd( _mm_mul_pd( _mm_add_pd( _mm_mul_pd( _pd_sincof_p0, z), _pd_sincof_p1), z), _pd_sincof_p2), z), x), x);

						/* select the correct result from the two polynoms */
						y2 = _mm_and_pd(poly_mask, y2); //, xmm3);
						/* update the sign */
						y = _mm_xor_pd( _mm_add_pd( _mm_andnot_pd(poly_mask, y),y2), sign_bit);

						cs = y;
						return cs;
					}
#endif	// !VECSSE_SINCOS_DOUBLE2_VIA_FLOAT4

				//! AVX __m256d sin function
				INLINE const result4_type sin(const argument4_type &lhs) const
					{
						using namespace macstl;
						result4_type sn;
						v4df x = lhs.data();

						static const v4df _pd_sign_mask = _mm256_set1_pd(0x8000000000000000LL);
						static const v4df _pd_inv_sign_mask = _mm256_set1_pd(~0x8000000000000000LL);
						static const v4df _pd_1 = _mm256_set1_pd(1.0);
						static const v4df _pd_0p5 = _mm256_set1_pd(0.5);
						static const v4df _pd_cephes_FOPI = _mm256_set1_pd(1.27323954473516);
						static const v4df _pd_minus_cephes_DP1 = _mm256_set1_pd(-0.78515625);
						static const v4df _pd_minus_cephes_DP2 = _mm256_set1_pd(-2.4187564849853515625e-4);
						static const v4df _pd_minus_cephes_DP3 = _mm256_set1_pd(-3.77489497744594108e-8);
						static const v4df _pd_sincof_p0 = _mm256_set1_pd(-1.9515295891E-4);
						static const v4df _pd_sincof_p1 = _mm256_set1_pd( 8.3321608736E-3);
						static const v4df _pd_sincof_p2 = _mm256_set1_pd(-1.6666654611E-1);
						static const v4df _pd_coscof_p0 = _mm256_set1_pd( 2.443315711809948E-005);
						static const v4df _pd_coscof_p1 = _mm256_set1_pd(-1.388731625493765E-003);
						static const v4df _pd_coscof_p2 = _mm256_set1_pd( 4.166664568298827E-002);
						static const v4si _pi32_1 = _mm_set1_epi32(1);
						static const v4si _pi32_inv1 = _mm_set1_epi32(~1);
						static const v4si _pi32_2 = _mm_set1_epi32(2);
						static const v4si _pi32_4 = _mm_set1_epi32(4);
						v4df sign_bit, y, y2, z;

						v4df swap_sign_bit, poly_mask;
						v4si emm0, emm2;
						sign_bit = x;
						/* take the absolute value */
						x = _mm256_and_pd(x, _pd_inv_sign_mask);
						/* extract the sign bit (upper one) */
						sign_bit = _mm256_and_pd(sign_bit, _pd_sign_mask);

						/* scale by 4/Pi */
						y = _mm256_mul_pd(x, _pd_cephes_FOPI);

						/* store the integer part of y in mm0 */
						/* j=(j+1) & (~1) (see the cephes sources) */
						emm2 = _mm_and_si128(_mm_add_epi32(_mm256_cvttpd_epi32(y), _pi32_1), _pi32_inv1);
						y = _mm256_cvtepi32_pd(emm2);
						/* get the swap sign flag */
						emm0 = _mm_slli_epi32(_mm_and_si128(emm2, _pi32_4), 29);
						/* get the polynom selection mask
						 there is one polynom for 0 <= x <= Pi/4
						 and another one for Pi/4<x<=Pi/2

						 Both branches will be computed.
						 */
						emm2 = _mm_cmpeq_epi32(_mm_and_si128(emm2, _pi32_2), _mm_setzero_si128());

						((v2df*)&swap_sign_bit)[1] = ((v2df*)&swap_sign_bit)[0] = _mm_castsi128_pd(emm0);
						((v2df*)&poly_mask)[1] = ((v2df*)&poly_mask)[0] = _mm_castsi128_pd(emm2);
						sign_bit = _mm256_xor_pd(sign_bit, swap_sign_bit);

						/* The magic pass: "Extended precision modular arithmetic"
						 x = ((x - y * DP1) - y * DP2) - y * DP3; */
						x = _mm256_add_pd( _mm256_add_pd( _mm256_add_pd(x, _mm256_mul_pd(y, _pd_minus_cephes_DP1)), _mm256_mul_pd(y, _pd_minus_cephes_DP2)), _mm256_mul_pd(y, _pd_minus_cephes_DP3));

						/* Evaluate the first polynom  (0 <= x <= Pi/4) */
						y = _pd_coscof_p0;
						z = _mm256_mul_pd(x,x);

						y = _mm256_add_pd( _mm256_sub_pd( _mm256_mul_pd( _mm256_mul_pd( _mm256_add_pd( _mm256_mul_pd( _mm256_add_pd( _mm256_mul_pd(y, z), _pd_coscof_p1), z), _pd_coscof_p2), z), z), _mm256_mul_pd(z, _pd_0p5) ), _pd_1);

						/* Evaluate the second polynom  (Pi/4 <= x <= 0) */

						y2 = _mm256_add_pd( _mm256_mul_pd( _mm256_mul_pd( _mm256_add_pd( _mm256_mul_pd( _mm256_add_pd( _mm256_mul_pd(_pd_sincof_p0, z), _pd_sincof_p1), z), _pd_sincof_p2), z), x), x);

						/* select the correct result from the two polynoms */
						/* update the sign */
						y2 = _mm256_and_pd(poly_mask, y2); //, xmm3);
						y = _mm256_xor_pd( _mm256_add_pd( _mm256_andnot_pd(poly_mask, y),y2), sign_bit);

						sn = y;
						return sn;
					}

				//! AVX __m256d cos function
				INLINE const result4_type cos(const argument4_type &lhs) const
					{
						using namespace macstl;
						result4_type cs;
						v4df x = lhs.data();

						static const v4df _pd_inv_sign_mask = _mm256_set1_pd(~0x8000000000000000LL);
						static const v4df _pd_1 = _mm256_set1_pd(1.0);
						static const v4df _pd_0p5 = _mm256_set1_pd(0.5);
						static const v4df _pd_cephes_FOPI = _mm256_set1_pd(1.27323954473516);
						static const v4df _pd_minus_cephes_DP1 = _mm256_set1_pd(-0.78515625);
						static const v4df _pd_minus_cephes_DP2 = _mm256_set1_pd(-2.4187564849853515625e-4);
						static const v4df _pd_minus_cephes_DP3 = _mm256_set1_pd(-3.77489497744594108e-8);
						static const v4df _pd_sincof_p0 = _mm256_set1_pd(-1.9515295891E-4);
						static const v4df _pd_sincof_p1 = _mm256_set1_pd( 8.3321608736E-3);
						static const v4df _pd_sincof_p2 = _mm256_set1_pd(-1.6666654611E-1);
						static const v4df _pd_coscof_p0 = _mm256_set1_pd( 2.443315711809948E-005);
						static const v4df _pd_coscof_p1 = _mm256_set1_pd(-1.388731625493765E-003);
						static const v4df _pd_coscof_p2 = _mm256_set1_pd( 4.166664568298827E-002);
						static const v4si _pi32_1 = _mm_set1_epi32(1);
						static const v4si _pi32_inv1 = _mm_set1_epi32(~1);
						static const v4si _pi32_2 = _mm_set1_epi32(2);
						static const v4si _pi32_4 = _mm_set1_epi32(4);
						v4df y, y2, z, sign_bit, poly_mask;
						v4si emm0, emm2;

						/* take the absolute value */
						x = _mm256_and_pd(x, _pd_inv_sign_mask);

						/* scale by 4/Pi */
						y = _mm256_mul_pd(x, _pd_cephes_FOPI);

						/* store the integer part of y in mm0 */
						/* j=(j+1) & (~1) (see the cephes sources) */
						emm2 = _mm_and_si128( _mm_add_epi32( _mm256_cvttpd_epi32(y), _pi32_1), _pi32_inv1);
						y = _mm256_cvtepi32_pd(emm2);

						emm2 = _mm_sub_epi32(emm2, _pi32_2);

						/* get the swap sign flag */
						emm0 = _mm_slli_epi32( _mm_andnot_si128(emm2, _pi32_4), 29);
						/* get the polynom selection mask */
						emm2 = _mm_cmpeq_epi32( _mm_and_si128(emm2, _pi32_2), _mm_setzero_si128());

						((v2df*)&sign_bit)[1] = ((v2df*)&sign_bit)[0] = _mm_castsi128_pd(emm0);
						((v2df*)&poly_mask)[1] = ((v2df*)&poly_mask)[0] = _mm_castsi128_pd(emm2);

						/* The magic pass: "Extended precision modular arithmetic"
						 x = ((x - y * DP1) - y * DP2) - y * DP3; */
						x = _mm256_add_pd( _mm256_add_pd( _mm256_add_pd(x, _mm256_mul_pd(y, _pd_minus_cephes_DP1)), _mm256_mul_pd(y, _pd_minus_cephes_DP2)), _mm256_mul_pd(y, _pd_minus_cephes_DP3));

						/* Evaluate the first polynom  (0 <= x <= Pi/4) */
						y = _pd_coscof_p0;
						z = _mm256_mul_pd(x,x);

						y = _mm256_add_pd( _mm256_sub_pd( _mm256_mul_pd( _mm256_mul_pd( _mm256_add_pd( _mm256_mul_pd( _mm256_add_pd( _mm256_mul_pd(y, z), _pd_coscof_p1), z), _pd_coscof_p2), z), z), _mm256_mul_pd(z, _pd_0p5) ), _pd_1);

						/* Evaluate the second polynom  (Pi/4 <= x <= 0) */

						y2 = _mm256_add_pd( _mm256_mul_pd( _mm256_mul_pd( _mm256_add_pd( _mm256_mul_pd( _mm256_add_pd( _mm256_mul_pd( _pd_sincof_p0, z), _pd_sincof_p1), z), _pd_sincof_p2), z), x), x);

						/* select the correct result from the two polynoms */
						y2 = _mm256_and_pd(poly_mask, y2); //, xmm3);
						/* update the sign */
						y = _mm256_xor_pd( _mm256_add_pd( _mm256_andnot_pd(poly_mask, y),y2), sign_bit);

						cs = y;
						return cs;
					}

#ifdef VECAVX_SINCOS_FLOAT8_NOT_VIA_FLOAT4
				//! AVX __m256d sin function
				INLINE const result8_type sin(const argument8_type &lhs) const
					{
						using namespace macstl;
						result8_type sn;
						v8sf x = lhs.data();

						static const v8sf _ps_sign_mask = _mm256_set1_ps(0x8000000000000000LL);
						static const v8sf _ps_inv_sign_mask = _mm256_set1_ps(~0x8000000000000000LL);
						static const v8sf _ps_1 = _mm256_set1_ps(1.0);
						static const v8sf _ps_0p5 = _mm256_set1_ps(0.5);
						static const v8sf _ps_cephes_FOPI = _mm256_set1_ps(1.27323954473516);
						static const v8sf _ps_minus_cephes_DP1 = _mm256_set1_ps(-0.78515625);
						static const v8sf _ps_minus_cephes_DP2 = _mm256_set1_ps(-2.4187564849853515625e-4);
						static const v8sf _ps_minus_cephes_DP3 = _mm256_set1_ps(-3.77489497744594108e-8);
						static const v8sf _ps_sincof_p0 = _mm256_set1_ps(-1.9515295891E-4);
						static const v8sf _ps_sincof_p1 = _mm256_set1_ps( 8.3321608736E-3);
						static const v8sf _ps_sincof_p2 = _mm256_set1_ps(-1.6666654611E-1);
						static const v8sf _ps_coscof_p0 = _mm256_set1_ps( 2.443315711809948E-005);
						static const v8sf _ps_coscof_p1 = _mm256_set1_ps(-1.388731625493765E-003);
						static const v8sf _ps_coscof_p2 = _mm256_set1_ps( 4.166664568298827E-002);
						static const v4si _pi32_1 = _mm_set1_epi32(1);
						static const v4si _pi32_inv1 = _mm_set1_epi32(~1);
						static const v4si _pi32_2 = _mm_set1_epi32(2);
						static const v4si _pi32_4 = _mm_set1_epi32(4);

						v8sf sign_bit, y, y2, z, tmp;

						v8sf swap_sign_bit, poly_mask;
						v8si emmm0, emmm2;
						v4si *emm0 = (v4si*) &emmm0, *emm2 = (v4si*) &emmm2;

						sign_bit = x;
						/* take the absolute value */
						x = _mm256_and_ps(x, _ps_inv_sign_mask);
						/* extract the sign bit (upper one) */
						sign_bit = _mm256_and_ps(sign_bit, _ps_sign_mask);

						/* scale by 4/Pi */
						y = _mm256_mul_ps(x, _ps_cephes_FOPI);

						// for the following part we have to do as if we have 2 v4sf entries
						/* store the integer part of y in mm0 */
						emm2[0] = _mm_cvttps_epi32( ((v4sf*)&y)[0] );
						emm2[1] = _mm_cvttps_epi32( ((v4sf*)&y)[1] );
						/* j=(j+1) & (~1) (see the cephes sources) */
						emm2[0] = _mm_and_si128(_mm_add_epi32(emm2[0], _pi32_1), _pi32_inv1);
						emm2[1] = _mm_and_si128(_mm_add_epi32(emm2[1], _pi32_1), _pi32_inv1);
						((v4sf*)&y)[0] = _mm_cvtepi32_ps(emm2[0]);
						((v4sf*)&y)[1] = _mm_cvtepi32_ps(emm2[1]);
						/* get the swap sign flag */
						emm0[0] = _mm_slli_epi32(_mm_and_si128(emm2[0], _pi32_4), 29);
						emm0[1] = _mm_slli_epi32(_mm_and_si128(emm2[1], _pi32_4), 29);
						/* get the polynom selection mask
						 there is one polynom for 0 <= x <= Pi/4
						 and another one for Pi/4<x<=Pi/2

						 Both branches will be computed.
						 */
						emm2[0] = _mm_cmpeq_epi32(_mm_and_si128(emm2[0], _pi32_2), _mm_setzero_si128());
						emm2[1] = _mm_cmpeq_epi32(_mm_and_si128(emm2[1], _pi32_2), _mm_setzero_si128());

						// the fact we need to cast 8 integers makes this routine about 16x SLOWER
						// than the vec<double,4> version, regardless of whether we use 2 calls to _mm256_castsi256_ps
						// or 4 calls to _mm_castsi128_ps ??!
						swap_sign_bit = _mm256_castsi256_ps(emmm0);
						poly_mask = _mm256_castsi256_ps(emmm2);

						sign_bit = _mm256_xor_ps(sign_bit, swap_sign_bit);

						/* The magic pass: "Extended precision modular arithmetic"
						 x = ((x - y * DP1) - y * DP2) - y * DP3; */
						x = _mm256_add_ps(_mm256_add_ps(_mm256_add_ps(x, _mm256_mul_ps(y, _ps_minus_cephes_DP1)), _mm256_mul_ps(y, _ps_minus_cephes_DP2)), _mm256_mul_ps(y, _ps_minus_cephes_DP3));

						/* Evaluate the first polynom  (0 <= x <= Pi/4) */
						y = _ps_coscof_p0;
						z = _mm256_mul_ps(x,x);
						tmp = _mm256_mul_ps(z, _ps_0p5);
						y = _mm256_add_ps( _mm256_sub_ps( _mm256_mul_ps( _mm256_mul_ps( _mm256_add_ps( _mm256_mul_ps( _mm256_add_ps(_mm256_mul_ps(y, z), _ps_coscof_p1), z), _ps_coscof_p2), z), z), tmp), _ps_1);

						/* Evaluate the second polynom  (Pi/4 <= x <= 0) */

						y2 = _ps_sincof_p0;
						y2 = _mm256_add_ps( _mm256_mul_ps( _mm256_mul_ps( _mm256_add_ps( _mm256_mul_ps( _mm256_add_ps( _mm256_mul_ps(y2, z), _ps_sincof_p1), z), _ps_sincof_p2), z), x), x);

						/* select the correct result from the two polynoms */
						y2 = _mm256_and_ps(poly_mask, y2);
						/* update the sign */
						sn = y = _mm256_xor_ps( _mm256_add_ps( _mm256_andnot_ps(poly_mask, y),y2), sign_bit);

						return sn;
					}

				//! AVX __m256d cos function
				INLINE const result8_type cos(const argument8_type &lhs) const
					{
						using namespace macstl;
						result8_type cs;
						v8sf x = lhs.data();

// 						static const v8sf _ps_sign_mask = _mm256_set1_ps(0x8000000000000000LL);
						static const v8sf _ps_inv_sign_mask = _mm256_set1_ps(~0x8000000000000000LL);
						static const v8sf _ps_1 = _mm256_set1_ps(1.0);
						static const v8sf _ps_0p5 = _mm256_set1_ps(0.5);
						static const v8sf _ps_cephes_FOPI = _mm256_set1_ps(1.27323954473516);
						static const v8sf _ps_minus_cephes_DP1 = _mm256_set1_ps(-0.78515625);
						static const v8sf _ps_minus_cephes_DP2 = _mm256_set1_ps(-2.4187564849853515625e-4);
						static const v8sf _ps_minus_cephes_DP3 = _mm256_set1_ps(-3.77489497744594108e-8);
						static const v8sf _ps_sincof_p0 = _mm256_set1_ps(-1.9515295891E-4);
						static const v8sf _ps_sincof_p1 = _mm256_set1_ps( 8.3321608736E-3);
						static const v8sf _ps_sincof_p2 = _mm256_set1_ps(-1.6666654611E-1);
						static const v8sf _ps_coscof_p0 = _mm256_set1_ps( 2.443315711809948E-005);
						static const v8sf _ps_coscof_p1 = _mm256_set1_ps(-1.388731625493765E-003);
						static const v8sf _ps_coscof_p2 = _mm256_set1_ps( 4.166664568298827E-002);
						static const v4si _pi32_1 = _mm_set1_epi32(1);
						static const v4si _pi32_inv1 = _mm_set1_epi32(~1);
						static const v4si _pi32_2 = _mm_set1_epi32(2);
						static const v4si _pi32_4 = _mm_set1_epi32(4);

						v8sf y, y2, z, sign_bit, poly_mask, tmp;
						v8si emmm0, emmm2;
						v4si *emm0 = (v4si*) &emmm0, *emm2 = (v4si*) &emmm2;

						/* take the absolute value */
						x = _mm256_and_ps(x, _ps_inv_sign_mask);

						/* scale by 4/Pi */
						y = _mm256_mul_ps(x, _ps_cephes_FOPI);

						// for the following part we have to do as if we have 2 v4sf entries
						/* store the integer part of y in mm0 */
						emm2[0] = _mm_cvttps_epi32( ((v4sf*)&y)[0] );
						emm2[1] = _mm_cvttps_epi32( ((v4sf*)&y)[1] );
						/* j=(j+1) & (~1) (see the cephes sources) */
						emm2[0] = _mm_and_si128(_mm_add_epi32(emm2[0], _pi32_1), _pi32_inv1);
						emm2[1] = _mm_and_si128(_mm_add_epi32(emm2[1], _pi32_1), _pi32_inv1);
						((v4sf*)&y)[0] = _mm_cvtepi32_ps(emm2[0]);
						((v4sf*)&y)[1] = _mm_cvtepi32_ps(emm2[1]);
						emm2[0] = _mm_sub_epi32(emm2[0], _pi32_2);
						emm2[1] = _mm_sub_epi32(emm2[1], _pi32_2);

						/* get the swap sign flag */
						emm0[0] = _mm_slli_epi32(_mm_andnot_si128(emm2[0], _pi32_4), 29);
						emm0[1] = _mm_slli_epi32(_mm_andnot_si128(emm2[1], _pi32_4), 29);
						/* get the polynom selection mask */
						emm2[0] = _mm_cmpeq_epi32(_mm_and_si128(emm2[0], _pi32_2), _mm_setzero_si128());
						emm2[1] = _mm_cmpeq_epi32(_mm_and_si128(emm2[1], _pi32_2), _mm_setzero_si128());

						// the fact we need to cast 8 integers makes this routine about 16x SLOWER
						// than the vec<double,4> version, regardless of whether we use 2 calls to _mm256_castsi256_ps
						// or 4 calls to _mm_castsi128_ps ??!
						sign_bit = _mm256_castsi256_ps(emmm0);
						poly_mask = _mm256_castsi256_ps(emmm2);

						/* The magic pass: "Extended precision modular arithmetic"
						 x = ((x - y * DP1) - y * DP2) - y * DP3; */
						x = _mm256_add_ps( _mm256_add_ps( _mm256_add_ps(x, _mm256_mul_ps(y, _ps_minus_cephes_DP1)), _mm256_mul_ps(y, _ps_minus_cephes_DP2)), _mm256_mul_ps(y, _ps_minus_cephes_DP3));

						/* Evaluate the first polynom  (0 <= x <= Pi/4) */
						y = _ps_coscof_p0;
						z = _mm256_mul_ps(x,x);
						tmp = _mm256_mul_ps(z, _ps_0p5);

						y = _mm256_add_ps( _mm256_sub_ps( _mm256_mul_ps( _mm256_mul_ps( _mm256_add_ps( _mm256_mul_ps( _mm256_add_ps( _mm256_mul_ps(y, z), _ps_coscof_p1), z), _ps_coscof_p2), z), z), tmp), _ps_1);

						/* Evaluate the second polynom  (Pi/4 <= x <= 0) */

						y2 = _ps_sincof_p0;
						y2 = _mm256_add_ps( _mm256_mul_ps( _mm256_mul_ps( _mm256_add_ps( _mm256_mul_ps( _mm256_add_ps( _mm256_mul_ps(y2, z), _ps_sincof_p1), z), _ps_sincof_p2), z), x), x);

						/* select the correct result from the two polynoms */
						y2 = _mm256_and_ps(poly_mask, y2);
						/* update the sign */
						y = _mm256_xor_ps( _mm256_add_ps( _mm256_andnot_ps(poly_mask, y), y2), sign_bit);
						return cs;
					}
#endif // !VECAVX_SINCOS_FLOAT8_NOT_VIA_FLOAT4

			};

		template <> struct cosine <macstl::vec <float, 4> >
			{
				typedef macstl::vec <float, 4> argument_type;
				typedef macstl::vec <float, 4> result_type;

				INLINE const result_type operator() (const argument_type& lhs) const
					{
						using namespace macstl;

						const vec <double, 2> pi = vec <double, 2>::fill <0x400921FB54442D18ULL> ();	// pi
						const vec <double, 2> half_pi = vec <double, 2>::fill <0x3FF921FB54442D18ULL> ();	// pi/2

						const vec <int, 4> lhs_n = mmx::cvt <vec <int, 4> > (
							mmx::mul (lhs, vec <float, 4>::fill <0x3EA2F983U> ()));	// 1/pi
						const vec <float, 4> lhs_reduced =
							mmx::movelh (
								// low two floats
								mmx::cvt <vec <float, 4> > (
									mmx::sub (mmx::sub (mmx::cvt <vec <double, 2> > (lhs), half_pi),
									mmx::mul (mmx::cvt <vec <double, 2> > (lhs_n), pi))),
								// high two floats
								mmx::cvt <vec <float, 4> > (
									mmx::sub (mmx::sub (mmx::cvt <vec <double, 2> > (mmx::movehl (lhs, lhs)), half_pi),
									mmx::mul (mmx::cvt <vec <double, 2> > (mmx::shuffle <1, 0, 3, 2> (lhs_n)), pi))));

						const __m128i neg = mmx::cmpeq (
							mmx::vand (lhs_n, vec <int, 4>::fill <1> ()),
							vec <int, 4>::fill <0> ()).data ();

						return
							mmx::vxor (
								mmx::impl::sine_reduced (lhs_reduced),
								mmx::vand (
									vec <float, 4>::fill <0x80000000U> (),	// -0.0
									reinterpret_cast <const __m128&> (neg)));
					}
			};

#ifndef VECAVX_SINCOS_FLOAT8_NOT_VIA_FLOAT4
		template <> struct cosine <macstl::vec <float, 8> >
			{
				typedef macstl::vec <float, 8> argument_type;
				typedef macstl::vec <float, 8> result_type;

				INLINE const result_type operator() (const argument_type& lhs) const
					{
						using namespace macstl;
						result_type r;
						vec<float,4> *rr = (vec<float,4>*) &r, *xx = (vec<float,4>*) &lhs;
						rr[0] = cos(xx[0]), rr[1] = cos(xx[1]);
						return r;
					}
			};
#else
		template <> struct cosine <macstl::vec <float, 8> >
			{
				typedef macstl::vec <float, 8> argument_type;
				typedef macstl::vec <float, 8> result_type;

				INLINE const result_type operator() (const argument_type& lhs) const
					{
						using namespace macstl;
						return sinecosine().cos(lhs);
					}
			};
#endif // VECAVX_SINCOS_FLOAT8_NOT_VIA_FLOAT4

#ifdef VECSSE_SINCOS_DOUBLE2_VIA_FLOAT4
		/*!
		 If VECSSE_SINCOS_DOUBLE2_VIA_FLOAT4 is defined before including macstl headers,
		 the sine and cosine calculations of vec<double,2> use macstl's own vec<float,4>
		 sine and cosine functions, via conversion steps. This ensures identical results on
		 the operand value range where doubles map exactly to floats. It's not clear which
		 method is preferrable, except when optimal compatibility with vec<double,4> results is
		 required.
		 */
		template <> struct cosine <macstl::vec <double, 2> >
			{
				typedef macstl::vec <double, 2> argument_type;
				typedef macstl::vec <double, 2> result_type;

				INLINE const result_type operator() (const argument_type& lhs) const
					{
						using namespace macstl;
// 						vec<float,4> slhs = mmx::cvt< vec<float,4> >(lhs);
						return mmx::cvt< vec<double,2> >( cos(mmx::cvt< vec<float,4> >(lhs)) );
					}
			};
#else
		template <> struct cosine <macstl::vec <double, 2> >
			{
				typedef macstl::vec <double, 2> argument_type;
				typedef macstl::vec <double, 2> result_type;

				INLINE const result_type operator() (const argument_type& lhs) const
					{
						using namespace macstl;
// 						vec<double,4> sincos = sinecosine()(lhs);
// 						result_type *sc = (result_type*) &sincos;
// 						return sc[1];
						return sinecosine().cos(lhs);
					}
			};
#endif // VECSSE_SINCOS_DOUBLE2_VIA_FLOAT4

		template <> struct cosine <macstl::vec <double, 4> >
			{
				typedef macstl::vec <double, 4> argument_type;
				typedef macstl::vec <double, 4> result_type;

				INLINE const result_type operator() (const argument_type& lhs) const
					{
						using namespace macstl;
						return sinecosine().cos(lhs);
					}
			};

		#endif

		// divides

		template <> struct divides <macstl::vec <float, 4>, macstl::vec <float, 4> >:
			public macstl::mmx::div_function <macstl::vec <float, 4>, macstl::vec <float, 4> >
			{
			};

		template <> struct divides <macstl::vec <float, 8>, macstl::vec <float, 8> >:
			public macstl::mmx::div_function <macstl::vec <float, 8>, macstl::vec <float, 8> >
			{
			};

		template <> struct divides <macstl::vec <double, 2>, macstl::vec <double, 2> >:
			public macstl::mmx::div_function <macstl::vec <double, 2>, macstl::vec <double, 2> >
			{
			};

		template <> struct divides <macstl::vec <double, 4>, macstl::vec <double, 4> >:
			public macstl::mmx::div_function <macstl::vec <double, 4>, macstl::vec <double, 4> >
			{
			};

		// equal_to

		template <typename T, std::size_t n> struct equal_to <macstl::vec <T, n>, macstl::vec <T, n> >:
			public macstl::mmx::cmpeq_function <macstl::vec <T, n>, macstl::vec <T, n> >
			{
			};

		template <> struct equal_to <macstl::vec <macstl::boolean <float>, 4>, macstl::vec <macstl::boolean <float>, 4> >
			{
				typedef macstl::vec <macstl::boolean <float>, 4> first_argument_type;
				typedef macstl::vec <macstl::boolean <float>, 4> second_argument_type;
				typedef macstl::vec <macstl::boolean <float>, 4> result_type;

				INLINE const result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;

						return mmx::vxor (mmx::vxor (lhs, rhs), result_type::fill <true> ());
					}
			};
		template <> struct equal_to <macstl::vec <macstl::boolean <float>, 8>, macstl::vec <macstl::boolean <float>, 8> >
			{
				typedef macstl::vec <macstl::boolean <float>, 8> first_argument_type;
				typedef macstl::vec <macstl::boolean <float>, 8> second_argument_type;
				typedef macstl::vec <macstl::boolean <float>, 8> result_type;

				INLINE const result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;

						return mmx::vxor (mmx::vxor (lhs, rhs), result_type::fill <true> ());
					}
			};

		template <> struct equal_to <macstl::vec <macstl::boolean <double>, 2>, macstl::vec <macstl::boolean <double>, 2> >
			{
				typedef macstl::vec <macstl::boolean <double>, 2> first_argument_type;
				typedef macstl::vec <macstl::boolean <double>, 2> second_argument_type;
				typedef macstl::vec <macstl::boolean <double>, 2> result_type;

				INLINE const result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;

						return mmx::vxor (mmx::vxor (lhs, rhs), result_type::fill <true> ());
					}
			};

		template <> struct equal_to <macstl::vec <macstl::boolean <double>, 4>, macstl::vec <macstl::boolean <double>, 4> >
			{
				typedef macstl::vec <macstl::boolean <double>, 4> first_argument_type;
				typedef macstl::vec <macstl::boolean <double>, 4> second_argument_type;
				typedef macstl::vec <macstl::boolean <double>, 4> result_type;

				INLINE const result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;

						return mmx::vxor (mmx::vxor (lhs, rhs), result_type::fill <true> ());
					}
			};

		template <> struct equal_to <macstl::vec <long long, 2>, macstl::vec <long long, 2> >
			{
				typedef macstl::vec <long long, 2> first_argument_type;
				typedef macstl::vec <long long, 2> second_argument_type;
				typedef macstl::vec <macstl::boolean <long long>, 2> result_type;

				INLINE const result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;

						vec <boolean <int>, 4> eq = mmx::cmpeq (data_cast <vec <int, 4> > (lhs), data_cast <vec <int, 4> > (rhs));
						return data_cast <result_type> (mmx::vand (mmx::shuffle <2, 3, 0, 1> (eq), eq));
					}
			};

		template <> struct equal_to <macstl::vec <unsigned long long, 2>, macstl::vec <unsigned long long, 2> >
			{
				typedef macstl::vec <unsigned long long, 2> first_argument_type;
				typedef macstl::vec <unsigned long long, 2> second_argument_type;
				typedef macstl::vec <macstl::boolean <long long>, 2> result_type;

				INLINE const result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;

						vec <boolean <int>, 4> eq = mmx::cmpeq (data_cast <vec <unsigned int, 4> > (lhs), data_cast <vec <unsigned int, 4> > (rhs));
						return data_cast <result_type> (mmx::vand (mmx::shuffle <2, 3, 0, 1> (eq), eq));
					}
			};

		template <> struct equal_to <macstl::vec <macstl::boolean <long long>, 2>, macstl::vec <macstl::boolean <long long>, 2> >
			{
				typedef macstl::vec <macstl::boolean <long long>, 2> first_argument_type;
				typedef macstl::vec <macstl::boolean <long long>, 2> second_argument_type;
				typedef macstl::vec <macstl::boolean <long long>, 2> result_type;

				INLINE const result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;

						vec <boolean <int>, 4> eq = mmx::cmpeq (data_cast <vec <boolean <int>, 4> > (lhs), data_cast <vec <boolean <int>, 4> > (rhs));
						return data_cast <result_type> (mmx::vand (mmx::shuffle <2, 3, 0, 1> (eq), eq));
					}
			};

		template <> struct equal_to <macstl::vec <long long, 4>, macstl::vec <long long, 4> >
			{
				typedef macstl::vec <long long, 4> first_argument_type;
				typedef macstl::vec <long long, 4> second_argument_type;
				typedef macstl::vec <macstl::boolean <long long>, 4> result_type;
				typedef macstl::vec <long long, 2> a_type;
				typedef macstl::vec <long long, 2> b_type;
				typedef macstl::vec <macstl::boolean <long long>, 2> r_type;

				INLINE const result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;
						a_type *a = (a_type*) &lhs;
						b_type *b = (b_type*) &rhs;
						result_type r;
						r_type *rr = (r_type*) &r;
						stdext::equal_to<a_type,b_type> F;

						rr[0] = F(a[0], b[0]);
						rr[1] = F(a[1], b[1]);
						return r;
					}
			};

		template <> struct equal_to <macstl::vec <unsigned long long, 4>, macstl::vec <unsigned long long, 4> >
			{
				typedef macstl::vec <unsigned long long, 4> first_argument_type;
				typedef macstl::vec <unsigned long long, 4> second_argument_type;
				typedef macstl::vec <macstl::boolean <long long>, 4> result_type;
				typedef macstl::vec <long long, 2> a_type;
				typedef macstl::vec <long long, 2> b_type;
				typedef macstl::vec <macstl::boolean <long long>, 2> r_type;

				INLINE const result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;
						a_type *a = (a_type*) &lhs;
						b_type *b = (b_type*) &rhs;
						result_type r;
						r_type *rr = (r_type*) &r;
						stdext::equal_to<a_type,b_type> F;

						rr[0] = F(a[0], b[0]);
						rr[1] = F(a[1], b[1]);
						return r;
					}
			};

		template <> struct equal_to <macstl::vec <macstl::boolean <long long>, 4>, macstl::vec <macstl::boolean <long long>, 4> >
			{
				typedef macstl::vec <macstl::boolean <long long>, 4> first_argument_type;
				typedef macstl::vec <macstl::boolean <long long>, 4> second_argument_type;
				typedef macstl::vec <macstl::boolean <long long>, 4> result_type;
				typedef macstl::vec <long long, 2> a_type;
				typedef macstl::vec <long long, 2> b_type;
				typedef macstl::vec <macstl::boolean <long long>, 2> r_type;

				INLINE const result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;
						a_type *a = (a_type*) &lhs;
						b_type *b = (b_type*) &rhs;
						result_type r;
						r_type *rr = (r_type*) &r;
						stdext::equal_to<a_type,b_type> F;

						rr[0] = F(a[0], b[0]);
						rr[1] = F(a[1], b[1]);
						return r;
					}
			};

		// greater

		template <typename T, std::size_t n> struct greater <macstl::vec <macstl::boolean <T>, n>, macstl::vec <macstl::boolean <T>, n> >
			{
				typedef macstl::vec <macstl::boolean <T>, n> first_argument_type;
				typedef macstl::vec <macstl::boolean <T>, n> second_argument_type;
				typedef macstl::vec <macstl::boolean <T>, n> result_type;

				INLINE const result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;

						return mmx::andnot (rhs, lhs);
					}
			};

#ifdef __MMX__
		template <> struct greater <macstl::vec <unsigned char, 8>, macstl::vec <unsigned char, 8> >
			{
				typedef macstl::vec <unsigned char, 8> first_argument_type;
				typedef macstl::vec <unsigned char, 8> second_argument_type;
				typedef macstl::vec <macstl::boolean <char>, 8> result_type;

				INLINE const result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;

						vec <unsigned char, 8> offset = vec <unsigned char, 8>::fill <0x80U> ();
						return mmx::cmpgt (
							data_cast <vec <signed char, 8> > (mmx::sub (lhs, offset)),
							data_cast <vec <signed char, 8> > (mmx::sub (rhs, offset)));
					}
			};

		template <> struct greater <macstl::vec <signed char, 8>, macstl::vec <signed char, 8> >:
			public macstl::mmx::cmpgt_function <macstl::vec <signed char, 8>, macstl::vec <signed char, 8> >
			{
			};

		template <> struct greater <macstl::vec <unsigned short, 4>, macstl::vec <unsigned short, 4> >
			{
				typedef macstl::vec <unsigned short, 4> first_argument_type;
				typedef macstl::vec <unsigned short, 4> second_argument_type;
				typedef macstl::vec <macstl::boolean <short>, 4> result_type;

				INLINE const result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;

						vec <unsigned short, 4> offset = vec <unsigned short, 4>::fill <0x8000U> ();
						return mmx::cmpgt (
							data_cast <vec <short, 4> > (mmx::sub (lhs, offset)),
							data_cast <vec <short, 4> > (mmx::sub (rhs, offset)));
					}
			};

		template <> struct greater <macstl::vec <short, 4>, macstl::vec <short, 4> >:
			public macstl::mmx::cmpgt_function <macstl::vec <short, 4>, macstl::vec <short, 4> >
			{
			};

		template <> struct greater <macstl::vec <unsigned int, 2>, macstl::vec <unsigned int, 2> >
			{
				typedef macstl::vec <unsigned int, 2> first_argument_type;
				typedef macstl::vec <unsigned int, 2> second_argument_type;
				typedef macstl::vec <macstl::boolean <int>, 2> result_type;

				INLINE const result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;

						vec <unsigned int, 2> offset = vec <unsigned int, 2>::fill <0x80000000U> ();
						return mmx::cmpgt (
							data_cast <vec <int, 2> > (mmx::sub (lhs, offset)),
							data_cast <vec <int, 2> > (mmx::sub (rhs, offset)));
					}
			};

		template <> struct greater <macstl::vec <int, 2>, macstl::vec <int, 2> >:
			public macstl::mmx::cmpgt_function <macstl::vec <int, 2>, macstl::vec <int, 2> >
			{
			};

#endif

		template <> struct greater <macstl::vec <float, 4>, macstl::vec <float, 4> >:
			public macstl::mmx::cmpgt_function <macstl::vec <float, 4>, macstl::vec <float, 4> >
			{
			};
		template <> struct greater <macstl::vec <float, 8>, macstl::vec <float, 8> >:
			public macstl::mmx::cmpgt_function <macstl::vec <float, 8>, macstl::vec <float, 8> >
			{
			};

	#ifdef __SSE2__

		template <> struct greater <macstl::vec <double, 2>, macstl::vec <double, 2> >:
			public macstl::mmx::cmpgt_function <macstl::vec <double, 2>, macstl::vec <double, 2> >
			{
			};

		template <> struct greater <macstl::vec <double, 4>, macstl::vec <double, 4> >:
			public macstl::mmx::cmpgt_function <macstl::vec <double, 4>, macstl::vec <double, 4> >
			{
			};

		template <> struct greater <macstl::vec <unsigned char, 16>, macstl::vec <unsigned char, 16> >
			{
				typedef macstl::vec <unsigned char, 16> first_argument_type;
				typedef macstl::vec <unsigned char, 16> second_argument_type;
				typedef macstl::vec <macstl::boolean <char>, 16> result_type;

				INLINE const result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;

						vec <unsigned char, 16> offset = vec <unsigned char, 16>::fill <0x80U> ();
						return mmx::cmpgt (
							data_cast <vec <signed char, 16> > (mmx::sub (lhs, offset)),
							data_cast <vec <signed char, 16> > (mmx::sub (rhs, offset)));
					}
			};

		template <> struct greater <macstl::vec <signed char, 16>, macstl::vec <signed char, 16> >:
			public macstl::mmx::cmpgt_function <macstl::vec <signed char, 16>, macstl::vec <signed char, 16> >
			{
			};

		template <> struct greater <macstl::vec <unsigned short, 8>, macstl::vec <unsigned short, 8> >
			{
				typedef macstl::vec <unsigned short, 8> first_argument_type;
				typedef macstl::vec <unsigned short, 8> second_argument_type;
				typedef macstl::vec <macstl::boolean <short>, 8> result_type;

				INLINE const result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;

						vec <unsigned short, 8> offset = vec <unsigned short, 8>::fill <0x8000U> ();
						return mmx::cmpgt (
							data_cast <vec <short, 8> > (mmx::sub (lhs, offset)),
							data_cast <vec <short, 8> > (mmx::sub (rhs, offset)));
					}
			};

		template <> struct greater <macstl::vec <short, 8>, macstl::vec <short, 8> >:
			public macstl::mmx::cmpgt_function <macstl::vec <short, 8>, macstl::vec <short, 8> >
			{
			};

		template <> struct greater <macstl::vec <unsigned int, 4>, macstl::vec <unsigned int, 4> >
			{
				typedef macstl::vec <unsigned int, 4> first_argument_type;
				typedef macstl::vec <unsigned int, 4> second_argument_type;
				typedef macstl::vec <macstl::boolean <int>, 4> result_type;

				INLINE const result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;

						vec <unsigned int, 4> offset = vec <unsigned int, 4>::fill <0x80000000U> ();
						return mmx::cmpgt (
							data_cast <vec <int, 4> > (mmx::sub (lhs, offset)),
							data_cast <vec <int, 4> > (mmx::sub (rhs, offset)));
					}
			};

		template <> struct greater <macstl::vec <int, 4>, macstl::vec <int, 4> >:
			public macstl::mmx::cmpgt_function <macstl::vec <int, 4>, macstl::vec <int, 4> >
			{
			};
		template <> struct greater <macstl::vec <int, 8>, macstl::vec <int, 8> >:
			public macstl::mmx::cmpgt_function <macstl::vec <int, 8>, macstl::vec <int, 8> >
			{
			};


#endif
		// greater_equal

		template <typename T, std::size_t n> struct greater_equal <macstl::vec <T, n>, macstl::vec <T, n> >
			{
				typedef macstl::vec <T, n> first_argument_type;
				typedef macstl::vec <T, n> second_argument_type;
				typedef typename macstl::vec <T, n>::vec_boolean result_type;

				INLINE const result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						return !(rhs > lhs);
					}
			};

	#ifdef __SSE__

		template <> struct greater_equal <macstl::vec <float, 4>, macstl::vec <float, 4> >:
			public macstl::mmx::cmpge_function <macstl::vec <float, 4>, macstl::vec <float, 4> >
			{
			};

	#endif

	#ifdef __SSE2__

		template <> struct greater_equal <macstl::vec <double, 2>, macstl::vec <double, 2> >:
			public macstl::mmx::cmpge_function <macstl::vec <double, 2>, macstl::vec <double, 2> >
			{
			};

		template <> struct greater_equal <macstl::vec <unsigned long long, 2>, macstl::vec <unsigned long long, 2> >;
		template <> struct greater_equal <macstl::vec <long long, 2>, macstl::vec <long long, 2> >;
		template <> struct greater_equal <macstl::vec <unsigned long long, 4>, macstl::vec <unsigned long long, 4> >;
		template <> struct greater_equal <macstl::vec <long long, 4>, macstl::vec <long long, 4> >;

	#endif


		// less

		template <typename T, std::size_t n> struct less <macstl::vec <T, n>, macstl::vec <T, n> >
			{
				typedef macstl::vec <T, n> first_argument_type;
				typedef macstl::vec <T, n> second_argument_type;
				typedef typename macstl::vec <T, n>::vec_boolean result_type;

				INLINE const result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						return rhs > lhs;
					}
			};

#ifdef __SSE2__

		template <> struct less <macstl::vec <unsigned long long, 2>, macstl::vec <unsigned long long, 2> >;
		template <> struct less <macstl::vec <long long, 2>, macstl::vec <long long, 2> >;
		template <> struct less <macstl::vec <unsigned long long, 4>, macstl::vec <unsigned long long, 4> >;
		template <> struct less <macstl::vec <long long, 4>, macstl::vec <long long, 4> >;

#endif

		// less_equal

		template <typename T, std::size_t n> struct less_equal <macstl::vec <T, n>, macstl::vec <T, n> >
			{
				typedef macstl::vec <T, n> first_argument_type;
				typedef macstl::vec <T, n> second_argument_type;
				typedef typename macstl::vec <T, n>::vec_boolean result_type;

				INLINE const result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						return !(lhs > rhs);
					}
			};

	#ifdef __SSE__

		template <> struct less_equal <macstl::vec <float, 4>, macstl::vec <float, 4> >:
			public macstl::mmx::cmple_function <macstl::vec <float, 4>, macstl::vec <float, 4> >
			{
			};

	#endif

	#ifdef __SSE2__

		template <> struct less_equal <macstl::vec <double, 2>, macstl::vec <double, 2> >:
			public macstl::mmx::cmple_function <macstl::vec <double, 2>, macstl::vec <double, 2> >
			{
			};

		template <> struct less_equal <macstl::vec <unsigned long long, 2>, macstl::vec <unsigned long long, 2> >;
		template <> struct less_equal <macstl::vec <long long, 2>, macstl::vec <long long, 2> >;
		template <> struct less_equal <macstl::vec <unsigned long long, 4>, macstl::vec <unsigned long long, 4> >;
		template <> struct less_equal <macstl::vec <long long, 4>, macstl::vec <long long, 4> >;

	#endif

			// logical_and

		template <typename T, std::size_t n> struct logical_and <macstl::vec <T, n>, macstl::vec <T, n> >
			{
				typedef macstl::vec <T, n> first_argument_type;
				typedef macstl::vec <T, n> second_argument_type;
				typedef typename macstl::vec <T, n>::vec_boolean result_type;

				INLINE const result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;

						return mmx::andnot (
							mmx::cmpeq (lhs, first_argument_type::template fill <0> ()),
							mmx::vxor (mmx::cmpeq (rhs, second_argument_type::template fill <0> ()), result_type::template fill <true> ()));
					}
			};

		template <typename T, std::size_t n> struct logical_and <macstl::vec <macstl::boolean <T>, n>, macstl::vec <macstl::boolean <T>, n> >:
			public macstl::mmx::vand_function <macstl::vec <macstl::boolean <T>, n>, macstl::vec <macstl::boolean <T>, n> >
			{
			};

		template <> struct logical_and <macstl::vec <float, 4>, macstl::vec <float, 4> >
			{
				typedef macstl::vec <float, 4> first_argument_type;
				typedef macstl::vec <float, 4> second_argument_type;
				typedef macstl::vec <macstl::boolean <float>, 4> result_type;

				INLINE const result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
						{
							using namespace macstl;

							vec <float, 4> zero = vec <float, 4>::fill <0> ();
							return mmx::vand (
								mmx::cmpneq (lhs, zero),
								mmx::cmpneq (rhs, zero));
						}
			};


		template <> struct logical_and <macstl::vec <double, 2>, macstl::vec <double, 2> >
			{
				typedef macstl::vec <double, 2> first_argument_type;
				typedef macstl::vec <double, 2> second_argument_type;
				typedef macstl::vec <macstl::boolean <double>, 2> result_type;

				INLINE const result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
						{
							using namespace macstl;

							vec <double, 2> zero = vec <double, 2>::fill <0> ();
							return mmx::vand (
								mmx::cmpneq (lhs, zero),
								mmx::cmpneq (rhs, zero));
						}
			};

		template <> struct logical_and <macstl::vec <unsigned long long, 2>, macstl::vec <unsigned long long, 2> >;
		template <> struct logical_and <macstl::vec <long long, 2>, macstl::vec <long long, 2> >;
		template <> struct logical_and <macstl::vec <unsigned long long, 4>, macstl::vec <unsigned long long, 4> >;
		template <> struct logical_and <macstl::vec <long long, 4>, macstl::vec <long long, 4> >;

		// logical_not

		template <typename T, std::size_t n> struct logical_not <macstl::vec <T, n> >
			{
				typedef macstl::vec <T, n> argument_type;
				typedef typename macstl::vec <T, n>::vec_boolean result_type;

				INLINE const result_type operator() (const argument_type& lhs) const
					{
						using namespace macstl;

						return lhs == argument_type::template fill <0> ();
					}
			};

		template <typename T, std::size_t n> struct logical_not <macstl::vec <macstl::boolean <T>, n> >
			{
				typedef macstl::vec <macstl::boolean <T>, n> argument_type;
				typedef macstl::vec <macstl::boolean <T>, n> result_type;

				INLINE const result_type operator() (const argument_type& lhs) const
					{
						using namespace macstl;

						return mmx::vxor (lhs, argument_type::template fill <true> ());
					}
			};

		// logical_or

		template <typename T, std::size_t n> struct logical_or <macstl::vec <T, n>, macstl::vec <T, n> >
			{
				typedef macstl::vec <T, n> first_argument_type;
				typedef macstl::vec <T, n> second_argument_type;
				typedef typename macstl::vec <T, n>::vec_boolean result_type;

				INLINE const result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;

						return mmx::vxor (mmx::vand (
							mmx::cmpeq (lhs, first_argument_type::template fill <0> ()),
							mmx::cmpeq (rhs, second_argument_type::template fill <0> ())),
							result_type::template fill <true> ());
					}
			};

		template <typename T, std::size_t n> struct logical_or <macstl::vec <macstl::boolean <T>, n>, macstl::vec <macstl::boolean <T>, n> >:
			public macstl::mmx::vor_function <macstl::vec <macstl::boolean <T>, n>, macstl::vec <macstl::boolean <T>, n> >
			{
			};

		template <> struct logical_or <macstl::vec <float, 4>, macstl::vec <float, 4> >
			{
				typedef macstl::vec <float, 4> first_argument_type;
				typedef macstl::vec <float, 4> second_argument_type;
				typedef macstl::vec <macstl::boolean <float>, 4> result_type;

				INLINE const result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
						{
							using namespace macstl;

							vec <float, 4> zero = vec <float, 4>::fill <0> ();
							return mmx::vor (
								mmx::cmpneq (lhs, zero),
								mmx::cmpneq (rhs, zero));
						}
			};

		template <> struct logical_or <macstl::vec <double, 2>, macstl::vec <double, 2> >
			{
				typedef macstl::vec <double, 2> first_argument_type;
				typedef macstl::vec <double, 2> second_argument_type;
				typedef macstl::vec <macstl::boolean <double>, 2> result_type;

				INLINE const result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
						{
							using namespace macstl;

							vec <double, 2> zero = vec <double, 2>::fill <0> ();
							return mmx::vor (
								mmx::cmpneq (lhs, zero),
								mmx::cmpneq (rhs, zero));
						}
			};

		template <> struct logical_or <macstl::vec <unsigned long long, 2>, macstl::vec <unsigned long long, 2> >;
		template <> struct logical_or <macstl::vec <long long, 2>, macstl::vec <long long, 2> >;
		template <> struct logical_or <macstl::vec <unsigned long long, 4>, macstl::vec <unsigned long long, 4> >;
		template <> struct logical_or <macstl::vec <long long, 4>, macstl::vec <long long, 4> >;

		// maximum

		template <typename T, std::size_t n> struct maximum <macstl::vec <macstl::boolean <T>, n>, macstl::vec <macstl::boolean <T>, n> >
			{
				typedef macstl::vec <macstl::boolean <T>, n> first_argument_type;
				typedef macstl::vec <macstl::boolean <T>, n> second_argument_type;
				typedef macstl::vec <macstl::boolean <T>, n> result_type;

				INLINE const result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;

						return mmx::vor (lhs, rhs);
					}
			};

	#if defined(__MMX__) && defined(__SSE__)

		template <> struct maximum <macstl::vec <unsigned short, 4>, macstl::vec <unsigned short, 4> >
			{
				typedef macstl::vec <unsigned short, 4> first_argument_type;
				typedef macstl::vec <unsigned short, 4> second_argument_type;
				typedef macstl::vec <unsigned short, 4> result_type;

				INLINE const result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;

						vec <short, 4> offset = vec <short, 4>::fill <-0x8000> ();
						return data_cast <vec <unsigned short, 4> > (mmx::add (mmx::max (
							mmx::sub (data_cast <vec <short, 4> > (lhs), offset),
							mmx::sub (data_cast <vec <short, 4> > (rhs), offset)),
							offset));
					}
			};

		template <> struct maximum <macstl::vec <short, 4>, macstl::vec <short, 4> >:
			public macstl::mmx::max_function <macstl::vec <short, 4>, macstl::vec <short, 4> >
			{
			};

		template <> struct maximum <macstl::vec <unsigned char, 8>, macstl::vec <unsigned char, 8> >:
			public macstl::mmx::max_function <macstl::vec <unsigned char, 8>, macstl::vec <unsigned char, 8> >
			{
			};


	#endif

		template <> struct maximum <macstl::vec <float, 4>, macstl::vec <float, 4> >:
			public macstl::mmx::max_function <macstl::vec <float, 4>, macstl::vec <float, 4> >
			{
			};

		template <> struct maximum <macstl::vec <float, 8>, macstl::vec <float, 8> >:
			public macstl::mmx::max_function <macstl::vec <float, 8>, macstl::vec <float, 8> >
			{
			};

		template <> struct maximum <macstl::vec <double, 2>, macstl::vec <double, 2> >:
			public macstl::mmx::max_function <macstl::vec <double, 2>, macstl::vec <double, 2> >
			{
			};

		template <> struct maximum <macstl::vec <double, 4>, macstl::vec <double, 4> >:
			public macstl::mmx::max_function <macstl::vec <double, 4>, macstl::vec <double, 4> >
			{
			};

		template <> struct maximum <macstl::vec <unsigned short, 8>, macstl::vec <unsigned short, 8> >
			{
				typedef macstl::vec <unsigned short, 8> first_argument_type;
				typedef macstl::vec <unsigned short, 8> second_argument_type;
				typedef macstl::vec <unsigned short, 8> result_type;

				INLINE const result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;

						vec <short, 8> offset = vec <short, 8>::fill <-0x8000> ();
						return data_cast <vec <unsigned short, 8> > (mmx::add (mmx::max (
							mmx::sub (data_cast <vec <short, 8> > (lhs), offset),
							mmx::sub (data_cast <vec <short, 8> > (rhs), offset)),
							offset));
					}
			};

		template <> struct maximum <macstl::vec <short, 8>, macstl::vec <short, 8> >:
			public macstl::mmx::max_function <macstl::vec <short, 8>, macstl::vec <short, 8> >
			{
			};

		template <> struct maximum <macstl::vec <unsigned char, 16>, macstl::vec <unsigned char, 16> >:
			public macstl::mmx::max_function <macstl::vec <unsigned char, 16>, macstl::vec <unsigned char, 16> >
			{
			};


		// minimum

		template <typename T, std::size_t n> struct minimum <macstl::vec <macstl::boolean <T>, n>, macstl::vec <macstl::boolean <T>, n> >
			{
				typedef macstl::vec <macstl::boolean <T>, n> first_argument_type;
				typedef macstl::vec <macstl::boolean <T>, n> second_argument_type;
				typedef macstl::vec <macstl::boolean <T>, n> result_type;

				INLINE const result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;

						return mmx::vand (lhs, rhs);
					}
			};

	#if defined(__MMX__) && defined(__SSE__)

		template <> struct minimum <macstl::vec <unsigned short, 4>, macstl::vec <unsigned short, 4> >
			{
				typedef macstl::vec <unsigned short, 4> first_argument_type;
				typedef macstl::vec <unsigned short, 4> second_argument_type;
				typedef macstl::vec <unsigned short, 4> result_type;

				INLINE const result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;

						vec <short, 4> offset = vec <short, 4>::fill <0x8000> ();
						return data_cast <vec <unsigned short, 4> > (mmx::add (mmx::min (
							mmx::sub (data_cast <vec <short, 4> > (lhs), offset),
							mmx::sub (data_cast <vec <short, 4> > (rhs), offset)),
							offset));
					}
			};

		template <> struct minimum <macstl::vec <short, 4>, macstl::vec <short, 4> >:
			public macstl::mmx::min_function <macstl::vec <short, 4>, macstl::vec <short, 4> >
			{
			};

		template <> struct minimum <macstl::vec <unsigned char, 8>, macstl::vec <unsigned char, 8> >:
			public macstl::mmx::min_function <macstl::vec <unsigned char, 8>, macstl::vec <unsigned char, 8> >
			{
			};
#endif

		template <> struct minimum <macstl::vec <float, 4>, macstl::vec <float, 4> >:
			public macstl::mmx::min_function <macstl::vec <float, 4>, macstl::vec <float, 4> >
			{
			};

		template <> struct minimum <macstl::vec <float, 8>, macstl::vec <float, 8> >:
			public macstl::mmx::min_function <macstl::vec <float, 8>, macstl::vec <float, 8> >
			{
			};

		template <> struct minimum <macstl::vec <double, 2>, macstl::vec <double, 2> >:
			public macstl::mmx::min_function <macstl::vec <double, 2>, macstl::vec <double, 2> >
			{
			};

		template <> struct minimum <macstl::vec <double, 4>, macstl::vec <double, 4> >:
			public macstl::mmx::min_function <macstl::vec <double, 4>, macstl::vec <double, 4> >
			{
			};

		template <> struct minimum <macstl::vec <unsigned short, 8>, macstl::vec <unsigned short, 8> >
			{
				typedef macstl::vec <unsigned short, 8> first_argument_type;
				typedef macstl::vec <unsigned short, 8> second_argument_type;
				typedef macstl::vec <unsigned short, 8> result_type;

				INLINE const result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;

						vec <short, 8> offset = vec <short, 8>::fill <0x8000> ();
						return data_cast <vec <unsigned short, 8> > (mmx::add (mmx::min (
							mmx::sub (data_cast <vec <short, 8> > (lhs), offset),
							mmx::sub (data_cast <vec <short, 8> > (rhs), offset)),
							offset));
					}
			};

		template <> struct minimum <macstl::vec <short, 8>, macstl::vec <short, 8> >:
			public macstl::mmx::min_function <macstl::vec <short, 8>, macstl::vec <short, 8> >
			{
			};

		template <> struct minimum <macstl::vec <unsigned char, 16>, macstl::vec <unsigned char, 16> >:
			public macstl::mmx::min_function <macstl::vec <unsigned char, 16>, macstl::vec <unsigned char, 16> >
			{
			};

		// minus

		template <typename T, std::size_t n> struct minus <macstl::vec <T, n>, macstl::vec <T, n> >:
			public macstl::mmx::sub_function <macstl::vec <T, n>, macstl::vec <T, n> >
			{
			};

		template <typename T, std::size_t n> struct minus <macstl::vec <macstl::boolean <T>, n>, macstl::vec <macstl::boolean <T>, n> >
			{
				typedef macstl::vec <macstl::boolean <T>, n> first_argument_type;
				typedef macstl::vec <macstl::boolean <T>, n> second_argument_type;
				typedef macstl::vec <macstl::boolean <T>, n> result_type;

				INLINE const result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;

						return mmx::vxor (lhs, rhs);
					}
			};


		// multiplies

		template <typename T, std::size_t n> struct multiplies <macstl::vec <macstl::boolean <T>, n>, macstl::vec <macstl::boolean <T>, n> >
			{
				typedef macstl::vec <macstl::boolean <T>, n> first_argument_type;
				typedef macstl::vec <macstl::boolean <T>, n> second_argument_type;
				typedef macstl::vec <macstl::boolean <T>, n> result_type;

				INLINE const result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;

						return mmx::vand (lhs, rhs);
					}
			};

		#ifdef __MMX__

		template <> struct multiplies <macstl::vec <unsigned short, 4>, macstl::vec <unsigned short, 4> >:
			public macstl::mmx::mullo_function <macstl::vec <unsigned short, 4>, macstl::vec <unsigned short, 4> >
			{
			};

		template <> struct multiplies <macstl::vec <short, 4>, macstl::vec <short, 4> >:
			public macstl::mmx::mullo_function <macstl::vec <short, 4>, macstl::vec <short, 4> >
			{
			};

		#endif

		template <> struct multiplies <macstl::vec <float, 4>, macstl::vec <float, 4> >:
			public macstl::mmx::mul_function <macstl::vec <float, 4>, macstl::vec <float, 4> >
			{
			};

		template <> struct multiplies <macstl::vec <float, 8>, macstl::vec <float, 8> >:
			public macstl::mmx::mul_function <macstl::vec <float, 8>, macstl::vec <float, 8> >
			{
			};

		template <> struct multiplies <macstl::vec <double, 2>, macstl::vec <double, 2> >:
			public macstl::mmx::mul_function <macstl::vec <double, 2>, macstl::vec <double, 2> >
			{
			};

		template <> struct multiplies <macstl::vec <double, 4>, macstl::vec <double, 4> >:
			public macstl::mmx::mul_function <macstl::vec <double, 4>, macstl::vec <double, 4> >
			{
			};

		template <> struct multiplies <macstl::vec <unsigned short, 8>, macstl::vec <unsigned short, 8> >:
			public macstl::mmx::mullo_function <macstl::vec <unsigned short, 8>, macstl::vec <unsigned short, 8> >
			{
			};

		template <> struct multiplies <macstl::vec <short, 8>, macstl::vec <short, 8> >:
			public macstl::mmx::mullo_function <macstl::vec <short, 8>, macstl::vec <short, 8> >
			{
			};


		// multiplies_high

		template <typename T, std::size_t n> struct multiplies_high <macstl::vec <macstl::boolean <T>, n>, macstl::vec <macstl::boolean <T>, n> >
			{
				typedef macstl::vec <macstl::boolean <T>, n> first_argument_type;
				typedef macstl::vec <macstl::boolean <T>, n> second_argument_type;
				typedef macstl::vec <macstl::boolean <T>, n> result_type;

				INLINE const result_type operator() (const first_argument_type&, const second_argument_type&) const
					{
						return result_type::template fill <false> ();
					}
			};

		#ifdef __MMX__

		template <> struct multiplies_high <macstl::vec <short, 4>, macstl::vec <short, 4> >:
			public macstl::mmx::mulhi_function <macstl::vec <short, 4>, macstl::vec <short, 4> >
			{
			};

		#endif

		#ifdef __SSE2__

		template <> struct multiplies_high <macstl::vec <unsigned short, 8>, macstl::vec <unsigned short, 8> >:
			public macstl::mmx::mulhi_function <macstl::vec <unsigned short, 8>, macstl::vec <unsigned short, 8> >
			{
			};

		template <> struct multiplies_high <macstl::vec <short, 8>, macstl::vec <short, 8> >:
			public macstl::mmx::mulhi_function <macstl::vec <short, 8>, macstl::vec <short, 8> >
			{
			};

		#endif

		// negate

		template <typename T, std::size_t n> struct negate <macstl::vec <T, n> >
			{
				typedef macstl::vec <T, n> argument_type;
				typedef macstl::vec <T, n> result_type;

				INLINE const result_type operator() (const argument_type& lhs) const
					{
						using namespace macstl;

						return mmx::sub (argument_type::template fill <0> (), lhs);
					}
			};

		template <typename T, std::size_t n> struct negate <macstl::vec <macstl::boolean <T>, n> >
			{
				typedef macstl::vec <macstl::boolean <T>, n> argument_type;
				typedef macstl::vec <macstl::boolean <T>, n> result_type;

				INLINE const result_type operator() (const argument_type& lhs) const
					{
						return lhs;
					}
			};

		// not_equal_to

		template <typename T, std::size_t n> struct not_equal_to <macstl::vec <T, n>, macstl::vec <T, n> >
			{
				typedef macstl::vec <T, n> first_argument_type;
				typedef macstl::vec <T, n> second_argument_type;
				typedef typename macstl::vec <T, n>::vec_boolean result_type;

				INLINE const result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;

						return mmx::vxor (mmx::cmpeq (lhs, rhs), result_type::template fill <true> ());
					}
			};

#ifdef __SSE__

		template <> struct not_equal_to <macstl::vec <float, 4>, macstl::vec <float, 4> >:
			public macstl::mmx::cmpneq_function <macstl::vec <float, 4>, macstl::vec <float, 4> >
			{
			};

		template <> struct not_equal_to <macstl::vec <float, 8>, macstl::vec <float, 8> >:
			public macstl::mmx::cmpneq_function <macstl::vec <float, 8>, macstl::vec <float, 8> >
			{
			};

		template <> struct not_equal_to <macstl::vec <macstl::boolean <float>, 4>, macstl::vec <macstl::boolean <float>, 4> >
			{
				typedef macstl::vec <macstl::boolean <float>, 4> first_argument_type;
				typedef macstl::vec <macstl::boolean <float>, 4> second_argument_type;
				typedef macstl::vec <macstl::boolean <float>, 4> result_type;

				INLINE const result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;

						return mmx::vxor (lhs, rhs);
					}
			};

		template <> struct not_equal_to <macstl::vec <macstl::boolean <float>, 8>, macstl::vec <macstl::boolean <float>, 8> >
			{
				typedef macstl::vec <macstl::boolean <float>, 8> first_argument_type;
				typedef macstl::vec <macstl::boolean <float>, 8> second_argument_type;
				typedef macstl::vec <macstl::boolean <float>, 8> result_type;

				INLINE const result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;

						return mmx::vxor (lhs, rhs);
					}
			};
#endif

#ifdef __SSE2__

		template <> struct not_equal_to <macstl::vec <double, 2>, macstl::vec <double, 2> >:
			public macstl::mmx::cmpneq_function <macstl::vec <double, 2>, macstl::vec <double, 2> >
			{
			};

		template <> struct not_equal_to <macstl::vec <double, 4>, macstl::vec <double, 4> >:
			public macstl::mmx::cmpneq_function <macstl::vec <double, 4>, macstl::vec <double, 4> >
			{
			};

		template <> struct not_equal_to <macstl::vec <macstl::boolean <double>, 2>, macstl::vec <macstl::boolean <double>, 2> >
			{
				typedef macstl::vec <macstl::boolean <double>, 2> first_argument_type;
				typedef macstl::vec <macstl::boolean <double>, 2> second_argument_type;
				typedef macstl::vec <macstl::boolean <double>, 2> result_type;

				INLINE const result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;

						return mmx::vxor (lhs, rhs);
					}
			};

		template <> struct not_equal_to <macstl::vec <macstl::boolean <double>, 4>, macstl::vec <macstl::boolean <double>, 4> >
			{
				typedef macstl::vec <macstl::boolean <double>, 4> first_argument_type;
				typedef macstl::vec <macstl::boolean <double>, 4> second_argument_type;
				typedef macstl::vec <macstl::boolean <double>, 4> result_type;

				INLINE const result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;

						return mmx::vxor (lhs, rhs);
					}
			};

		template <> struct not_equal_to <macstl::vec <long long, 2>, macstl::vec <long long, 2> >
			{
				typedef macstl::vec <long long, 2> first_argument_type;
				typedef macstl::vec <long long, 2> second_argument_type;
				typedef macstl::vec <macstl::boolean <long long>, 2> result_type;

				INLINE const result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;

						vec <boolean <int>, 4> neq = mmx::vxor (
							mmx::cmpeq (data_cast <vec <int, 4> > (lhs), data_cast <vec <int, 4> > (rhs)),
							vec <boolean <int>, 4>::fill <true> ());
						return data_cast <result_type> (mmx::vor (mmx::shuffle <2, 3, 0, 1> (neq), neq));
					}
			};

		template <> struct not_equal_to <macstl::vec <unsigned long long, 2>, macstl::vec <unsigned long long, 2> >
			{
				typedef macstl::vec <unsigned long long, 2> first_argument_type;
				typedef macstl::vec <unsigned long long, 2> second_argument_type;
				typedef macstl::vec <macstl::boolean <long long>, 2> result_type;

				INLINE const result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;

						vec <boolean <int>, 4> neq = mmx::vxor (
							mmx::cmpeq (data_cast <vec <unsigned int, 4> > (lhs), data_cast <vec <unsigned int, 4> > (rhs)),
							vec <boolean <int>, 4>::fill <true> ());
						return data_cast <result_type> (mmx::vor (mmx::shuffle <2, 3, 0, 1> (neq), neq));
					}
			};

		template <> struct not_equal_to <macstl::vec <macstl::boolean <long long>, 2>, macstl::vec <macstl::boolean <long long>, 2> >
			{
				typedef macstl::vec <macstl::boolean <long long>, 2> first_argument_type;
				typedef macstl::vec <macstl::boolean <long long>, 2> second_argument_type;
				typedef macstl::vec <macstl::boolean <long long>, 2> result_type;

				INLINE const result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;

						vec <boolean <int>, 4> neq = mmx::vxor (
							mmx::cmpeq (data_cast <vec <boolean <int>, 4> > (lhs), data_cast <vec <boolean <int>, 4> > (rhs)),
							vec <boolean <int>, 4>::fill <true> ());
						return data_cast <result_type> (mmx::vor (mmx::shuffle <2, 3, 0, 1> (neq), neq));
					}
			};

		template <> struct not_equal_to <macstl::vec <long long, 4>, macstl::vec <long long, 4> >
			{
				typedef macstl::vec <long long, 4> first_argument_type;
				typedef macstl::vec <long long, 4> second_argument_type;
				typedef macstl::vec <macstl::boolean <long long>, 4> result_type;
				typedef macstl::vec <long long, 2> a_type;
				typedef macstl::vec <long long, 2> b_type;
				typedef macstl::vec <macstl::boolean <long long>, 2> r_type;

				INLINE const result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;
						a_type *a = (a_type*) &lhs;
						b_type *b = (b_type*) &rhs;
						result_type r;
						r_type *rr = (r_type*) &r;
						stdext::not_equal_to<a_type,b_type> F;

						rr[0] = F(a[0], b[0]);
						rr[1] = F(a[1], b[1]);
						return r;
					}
			};

		template <> struct not_equal_to <macstl::vec <unsigned long long, 4>, macstl::vec <unsigned long long, 4> >
			{
				typedef macstl::vec <unsigned long long, 4> first_argument_type;
				typedef macstl::vec <unsigned long long, 4> second_argument_type;
				typedef macstl::vec <macstl::boolean <long long>, 4> result_type;
				typedef macstl::vec <long long, 2> a_type;
				typedef macstl::vec <long long, 2> b_type;
				typedef macstl::vec <macstl::boolean <long long>, 2> r_type;

				INLINE const result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;
						a_type *a = (a_type*) &lhs;
						b_type *b = (b_type*) &rhs;
						result_type r;
						r_type *rr = (r_type*) &r;
						stdext::not_equal_to<a_type,b_type> F;

						rr[0] = F(a[0], b[0]);
						rr[1] = F(a[1], b[1]);
						return r;
					}
			};

		template <> struct not_equal_to <macstl::vec <macstl::boolean <long long>, 4>, macstl::vec <macstl::boolean <long long>, 4> >
			{
				typedef macstl::vec <macstl::boolean <long long>, 4> first_argument_type;
				typedef macstl::vec <macstl::boolean <long long>, 4> second_argument_type;
				typedef macstl::vec <macstl::boolean <long long>, 4> result_type;
				typedef macstl::vec <long long, 2> a_type;
				typedef macstl::vec <long long, 2> b_type;
				typedef macstl::vec <macstl::boolean <long long>, 2> r_type;

				INLINE const result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;
						a_type *a = (a_type*) &lhs;
						b_type *b = (b_type*) &rhs;
						result_type r;
						r_type *rr = (r_type*) &r;
						stdext::not_equal_to<a_type,b_type> F;

						rr[0] = F(a[0], b[0]);
						rr[1] = F(a[1], b[1]);
						return r;
					}
			};

#endif

		// plus

		template <typename T, std::size_t n> struct plus <macstl::vec <T, n>, macstl::vec <T, n> >:
			public macstl::mmx::add_function <macstl::vec <T, n>, macstl::vec <T, n> >
			{
			};

		template <typename T, std::size_t n> struct plus <macstl::vec <macstl::boolean <T>, n>, macstl::vec <macstl::boolean <T>, n> >
			{
				typedef macstl::vec <macstl::boolean <T>, n> first_argument_type;
				typedef macstl::vec <macstl::boolean <T>, n> second_argument_type;
				typedef macstl::vec <macstl::boolean <T>, n> result_type;

				INLINE const result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
					{
						using namespace macstl;

						return mmx::vor (lhs, rhs);
					}
			};

		// reciprocal_square_root

		template <> struct reciprocal_square_root <macstl::vec <float, 4> >:
			public macstl::mmx::rsqrt_function <macstl::vec <float, 4> >
			{
			};

		template <> struct reciprocal_square_root <macstl::vec <float, 8> >:
			public macstl::mmx::rsqrt_function <macstl::vec <float, 8> >
			{
			};

		// selection

		template <typename T, std::size_t n> struct selection <macstl::vec <typename macstl::vec <T, n>::boolean_type, n>, macstl::vec <T, n>, macstl::vec <T, n> >
			{
				typedef typename macstl::vec <T, n>::vec_boolean first_argument_type;
				typedef macstl::vec <T, n> second_argument_type;
				typedef macstl::vec <T, n> third_argument_type;
				typedef macstl::vec <T, n> result_type;

				INLINE const result_type operator() (const first_argument_type& lhs, const second_argument_type& mhs, const third_argument_type& rhs) const
					{
						using namespace macstl;

						return mmx::vor (mmx::vand (lhs, rhs), mmx::andnot (lhs, rhs));
					}
			};

		// sine

		#if defined(__SSE__) && defined(__SSE2__)

		template <> struct sine <macstl::vec <float, 4> >
			{
				typedef macstl::vec <float, 4> argument_type;
				typedef macstl::vec <float, 4> result_type;

				INLINE const result_type operator() (const argument_type& lhs) const
					{
						using namespace macstl;

						const vec <double, 2> pi = vec <double, 2>::fill <0x400921FB54442D18ULL> ();	// pi

						// force lhs to [-pi/2, pi/2]
						const vec <int, 4> lhs_n = mmx::cvt <vec <int, 4> > (
							mmx::mul (lhs, vec <float, 4>::fill <0x3EA2F983U> ()));
						const vec <float, 4> lhs_reduced =
							mmx::movelh (
								// low two floats
								mmx::cvt <vec <float, 4> > (
									mmx::sub (mmx::cvt <vec <double, 2> > (lhs),
									mmx::mul (mmx::cvt <vec <double, 2> > (lhs_n), pi))),
								// high two floats
								mmx::cvt <vec <float, 4> > (
									mmx::sub (mmx::cvt <vec <double, 2> > (mmx::movehl (lhs, lhs)),
									mmx::mul (mmx::cvt <vec <double, 2> > (mmx::shuffle <1, 0, 3, 2> (lhs_n)), pi))));

						const __m128i neg = mmx::andnot (
							mmx::cmpeq (reinterpret_cast <const vec <int, 4>&> (lhs), vec <int, 4>::fill <-0x7FFFFFFF - 1> ()),
							mmx::cmpeq (mmx::vand (lhs_n, vec <int, 4>::fill <1> ()), vec <int, 4>::fill <0> ())).data ();

						return
							mmx::vxor (
								mmx::impl::sine_reduced (lhs_reduced),
								mmx::andnot (
									// if lhs == -0.0 or lhs_n is odd, need to invert sign of result
									reinterpret_cast <const __m128&> (neg),
									vec <float, 4>::fill <0x80000000U> ()));

					}

			};

// 		template <> struct sine <macstl::vec <float, 8> >
// 			{
// 				typedef macstl::vec <float, 8> argument_type;
// 				typedef macstl::vec <float, 8> result_type;
//
// 				INLINE const result_type operator() (const argument_type& lhs) const
// 					{
// 						using namespace macstl;
//
// 						const vec <double, 4> pi = vec <double, 4>::fill <0x400921FB54442D18ULL> ();	// pi
//
// 						// force lhs to [-pi/2, pi/2]
// 						const vec <int, 8> lhs_n = mmx::cvt <vec <int, 8> > (
// 							mmx::mul (lhs, vec <float, 8>::fill <0x3EA2F983U> ()));
// 						const vec <float, 8> lhs_reduced =
// 							mmx::movelh (
// 								// low two floats
// 								mmx::cvt <vec <float, 8> > (
// 									mmx::sub (mmx::cvt <vec <double, 4> > (lhs),
// 									mmx::mul (mmx::cvt <vec <double, 4> > (lhs_n), pi))),
// 								// high two floats
// 								mmx::cvt <vec <float, 8> > (
// 									mmx::sub (mmx::cvt <vec <double, 4> > (mmx::movehl (lhs, lhs)),
// 									mmx::mul (mmx::cvt <vec <double, 4> > (mmx::shuffle <1, 0, 3, 2> (lhs_n)), pi))));
//
// 						const __m256i neg = mmx::andnot (
// 							mmx::cmpeq (reinterpret_cast <const vec <int, 8>&> (lhs), vec <int, 8>::fill <-0x7FFFFFFF - 1> ()),
// 							mmx::cmpeq (mmx::vand (lhs_n, vec <int, 8>::fill <1> ()), vec <int, 8>::fill <0> ())).data ();
//
// 						return
// 							mmx::vxor (
// 								mmx::impl::sine_reduced (lhs_reduced),
// 								mmx::andnot (
// 									// if lhs == -0.0 or lhs_n is odd, need to invert sign of result
// 									reinterpret_cast <const __m256&> (neg),
// 									vec <float, 8>::fill <0x80000000U> ()));
//
// 					}
//
// 			};
//
#ifdef VECAVX_SINCOS_FLOAT8_NOT_VIA_FLOAT4
		template <> struct sine <macstl::vec <float, 8> >
			{
				typedef macstl::vec <float, 8> argument_type;
				typedef macstl::vec <float, 8> result_type;

				INLINE const result_type operator() (const argument_type& lhs) const
					{
						using namespace macstl;
						return sinecosine().sin(lhs);
					}
			};
#else
		template <> struct sine <macstl::vec <float, 8> >
		{
			typedef macstl::vec <float, 8> argument_type;
			typedef macstl::vec <float, 8> result_type;

			INLINE const result_type operator() (const argument_type& lhs) const
			{
				using namespace macstl;
				result_type r;
				vec<float,4> *rr = (vec<float,4>*) &r, *xx = (vec<float,4>*) &lhs;
				rr[0] = sin(xx[0]), rr[1] = sin(xx[1]);
				return r;
			}
		};
#endif // VECAVX_SINCOS_FLOAT8_NOT_VIA_FLOAT4

#ifdef VECSSE_SINCOS_DOUBLE2_VIA_FLOAT4
		/*!
		 If VECSSE_SINCOS_DOUBLE2_VIA_FLOAT4 is defined before including macstl headers,
		 the sine and cosine calculations of vec<double,2> use macstl's own vec<float,4>
		 sine and cosine functions, via conversion steps. This ensures identical results on
		 the operand value range where doubles map exactly to floats. It's not clear which
		 method is preferrable, except when optimal compatibility with vec<double,4> results is
		 required.
		 */
		template <> struct sine <macstl::vec <double, 2> >
			{
				typedef macstl::vec <double, 2> argument_type;
				typedef macstl::vec <double, 2> result_type;

				INLINE const result_type operator() (const argument_type& lhs) const
					{
						using namespace macstl;
// 						vec<float,4> slhs = mmx::cvt< vec<float,4> >(lhs);
						return mmx::cvt< vec<double,2> >( sin(mmx::cvt< vec<float,4> >(lhs)) );
					}
			};
#else
		template <> struct sine <macstl::vec <double, 2> >
			{
				typedef macstl::vec <double, 2> argument_type;
				typedef macstl::vec <double, 2> result_type;

				INLINE const result_type operator() (const argument_type& lhs) const
					{
						using namespace macstl;
// 						vec<double,4> sincos = sinecosine()(lhs);
// 						result_type *sc = (result_type*) &sincos;
// 						return sc[0];
						return sinecosine().sin(lhs);
					}
			};
#endif // VECSSE_SINCOS_DOUBLE2_VIA_FLOAT4

		template <> struct sine <macstl::vec <double, 4> >
			{
				typedef macstl::vec <double, 4> argument_type;
				typedef macstl::vec <double, 4> result_type;

				INLINE const result_type operator() (const argument_type& lhs) const
					{
						using namespace macstl;
						return sinecosine().sin(lhs);
					}
			};

		#endif

		// square_root

		template <> struct square_root <macstl::vec <float, 4> >:
			public macstl::mmx::sqrt_function <macstl::vec <float, 4> >
			{
			};

		template <> struct square_root <macstl::vec <float, 8> >:
			public macstl::mmx::sqrt_function <macstl::vec <float, 8> >
			{
			};

		template <> struct square_root <macstl::vec <double, 2> >:
			public macstl::mmx::sqrt_function <macstl::vec <double, 2> >
			{
			};

		template <> struct square_root <macstl::vec <double, 4> >:
			public macstl::mmx::sqrt_function <macstl::vec <double, 4> >
			{
			};

		template <> struct round <macstl::vec <float, 8> >:
			public macstl::mmx::round_function < (_MM_FROUND_TO_NEAREST_INT|_MM_FROUND_NO_EXC),
										macstl::vec <float, 8> >
			{
			};

		template <> struct round <macstl::vec <float, 4> >:
			public macstl::mmx::round_function < (_MM_FROUND_TO_NEAREST_INT|_MM_FROUND_NO_EXC),
										macstl::vec <float, 4> >
			{
			};

		template <> struct round <macstl::vec <double, 2> >:
			public macstl::mmx::round_function < (_MM_FROUND_TO_NEAREST_INT|_MM_FROUND_NO_EXC),
										macstl::vec <double, 2> >
			{
			};

		template <> struct round <macstl::vec <double, 4> >:
			public macstl::mmx::round_function < (_MM_FROUND_TO_NEAREST_INT|_MM_FROUND_NO_EXC),
										macstl::vec <double, 4> >
			{
			};

		// accumulator <maximum>

		#if defined(__MMX__) && defined(__SSE__)

		INLINE const macstl::boolean <char> accumulator <maximum <macstl::vec <macstl::boolean <char>, 8>, macstl::vec <macstl::boolean <char>, 8> > >::operator() (const macstl::vec <macstl::boolean <char>, 8>& lhs) const
			{
				using namespace macstl;

				return mmx::movemask (lhs) != 0;
			}

		INLINE unsigned short accumulator <maximum <macstl::vec <unsigned short, 4>, macstl::vec <unsigned short, 4> > >::operator() (const macstl::vec <unsigned short, 4>& lhs) const
			{
				using namespace macstl;

				const vec <short, 4> offset = vec <short, 4>::fill <0x8000> ();
				const vec <short, 4> lhs_offset = mmx::sub (data_cast <vec <short, 4> > (lhs), offset);

				const vec <short, 4> result = mmx::max (lhs_offset, mmx::shuffle <0, 3, 2, 1> (lhs_offset));
				return mmx::extract <0> (
					mmx::add (mmx::max (result, mmx::shuffle <1, 0, 3, 2> (result)), offset));
			}


		INLINE short accumulator <maximum <macstl::vec <short, 4>, macstl::vec <short, 4> > >::operator() (const macstl::vec <short, 4>& lhs) const
			{
				using namespace macstl;

				const vec <short, 4> result = mmx::max (lhs, mmx::shuffle <0, 3, 2, 1> (lhs));
				return mmx::extract <0> (mmx::max (result, mmx::shuffle <1, 0, 3, 2> (result)));
			}

		#endif

		INLINE float accumulator <maximum <macstl::vec <float, 4>, macstl::vec <float, 4> > >::operator() (const macstl::vec <float, 4>& lhs) const
			{
				using namespace macstl;

				const vec <float, 4> result = mmx::max (lhs, mmx::shuffles <0, 3, 2, 1> (lhs, lhs));
				return mmx::max (result, mmx::shuffles <1, 0, 3, 2> (result, result)) [0];
			}

		INLINE const macstl::boolean <float> accumulator <maximum <macstl::vec <macstl::boolean <float>, 4>, macstl::vec <macstl::boolean <float>, 4> > >::operator() (const macstl::vec <macstl::boolean <float>, 4>& lhs) const
			{
				using namespace macstl;

				return mmx::movemask (lhs) != 0;
			}

		INLINE float accumulator <maximum <macstl::vec <float, 8>, macstl::vec <float, 8> > >::operator() (const macstl::vec <float, 8>& lhs) const
			{
				using namespace macstl;

// 				const vec<float,4> *vals = (vec<float,4>*) &lhs;
// 				float a = vals[0].max(), b = vals[1].max();
// 				return (a > b)? a : b;
				typedef vec<float,8>::half_data_type hdata_type;
				const hdata_type *vec4 = lhs.half_data();
				static const int m0321 = SHUFFLE4MASK(0,3,2,1), m1032 = SHUFFLE4MASK(1, 0, 3, 2);
				hdata_type result0 = _mm_max_ps( vec4[0], _mm_shuffle_ps(vec4[0], vec4[0], m0321) );
				result0 = _mm_max_ps( result0, _mm_shuffle_ps(result0, result0, m1032) );
				hdata_type result1 = _mm_max_ps( vec4[1], _mm_shuffle_ps(vec4[1], vec4[1], m0321) );
				result1 = _mm_max_ps( result1, _mm_shuffle_ps(result1, result1, m1032) );
				return __mvectorelem<float>( _mm_max_ps( result0, result1 ), 0 );
			}
		INLINE const macstl::boolean <float> accumulator <maximum <macstl::vec <macstl::boolean <float>, 8>, macstl::vec <macstl::boolean <float>, 8> > >::operator() (const macstl::vec <macstl::boolean <float>, 8>& lhs) const
			{
				using namespace macstl;
				return mmx::movemask (lhs) != 0;
			}

		INLINE double accumulator <maximum <macstl::vec <double, 2>, macstl::vec <double, 2> > >::operator() (const macstl::vec <double, 2>& lhs) const
			{
				using namespace macstl;

				return mmx::max (lhs, mmx::shuffled <0, 1> (lhs, lhs)) [0];
			}

		INLINE const macstl::boolean <double> accumulator <maximum <macstl::vec <macstl::boolean <double>, 2>, macstl::vec <macstl::boolean <double>, 2> > >::operator() (const macstl::vec <macstl::boolean <double>, 2>& lhs) const
			{
				using namespace macstl;

				return mmx::movemask (lhs) != 0;
			}

		INLINE double accumulator <maximum <macstl::vec <double, 4>, macstl::vec <double, 4> > >::operator() (const macstl::vec <double, 4>& lhs) const
			{
				using namespace macstl;

// 				const vec<double,2> *vals = (vec<double,2>*) &lhs;
// 				double a = vals[0].max(), b = vals[1].max();
// 				return (a > b)? a : b;
				typedef vec<double,4>::half_data_type hdata_type;
				const hdata_type *vec2 = lhs.half_data();
				hdata_type result0 = _mm_max_pd( vec2[0], _mm_shuffle_pd(vec2[0], vec2[0], SHUFFLE2MASK(0,1)) );
				hdata_type result1 = _mm_max_pd( vec2[1], _mm_shuffle_pd(vec2[1], vec2[1], SHUFFLE2MASK(0,1)) );
				return __mvectorelem<double>( _mm_max_pd( result0, result1 ), 0 );
			}

		INLINE const macstl::boolean <double> accumulator <maximum <macstl::vec <macstl::boolean <double>, 4>, macstl::vec <macstl::boolean <double>, 4> > >::operator() (const macstl::vec <macstl::boolean <double>, 4>& lhs) const
			{
				using namespace macstl;

				return mmx::movemask (lhs) != 0;
			}

		INLINE const macstl::boolean <char> accumulator <maximum <macstl::vec <macstl::boolean <char>, 16>, macstl::vec <macstl::boolean <char>, 16> > >::operator() (const macstl::vec <macstl::boolean <char>, 16>& lhs) const
			{
				using namespace macstl;

				return mmx::movemask (lhs) != 0;
			}

		// accumulator <minimum>

		#if defined(__MMX__) && defined(__SSE__)

		INLINE const macstl::boolean <char> accumulator <minimum <macstl::vec <macstl::boolean <char>, 8>, macstl::vec <macstl::boolean <char>, 8> > >::operator() (const macstl::vec <macstl::boolean <char>, 8>& lhs) const
			{
				using namespace macstl;

				return mmx::movemask (lhs) == 255;
			}

		INLINE unsigned short accumulator <minimum <macstl::vec <unsigned short, 4>, macstl::vec <unsigned short, 4> > >::operator() (const macstl::vec <unsigned short, 4>& lhs) const
			{
				using namespace macstl;

				const vec <short, 4> offset = vec <short, 4>::fill <0x8000> ();
				const vec <short, 4> lhs_offset = mmx::sub (data_cast <vec <short, 4> > (lhs), offset);

				const vec <short, 4> result = mmx::min (lhs_offset, mmx::shuffle <0, 3, 2, 1> (lhs_offset));
				return mmx::extract <0> (
					mmx::add (mmx::min (result, mmx::shuffle <1, 0, 3, 2> (result)), offset));
			}

		INLINE short accumulator <minimum <macstl::vec <short, 4>, macstl::vec <short, 4> > >::operator() (const macstl::vec <short, 4>& lhs) const
			{
				using namespace macstl;

				const vec <short, 4> result = mmx::min (lhs, mmx::shuffle <0, 3, 2, 1> (lhs));
				return mmx::extract <0> (mmx::min (result, mmx::shuffle <1, 0, 3, 2> (result)));
			}

		#endif

		INLINE float accumulator <minimum <macstl::vec <float, 4>, macstl::vec <float, 4> > >::operator() (const macstl::vec <float, 4>& lhs) const
			{
				using namespace macstl;

				const vec <float, 4> result = mmx::min (lhs, mmx::shuffles <0, 3, 2, 1> (lhs, lhs));
				return mmx::min (result, mmx::shuffles <1, 0, 3, 2> (result, result)) [0];
			}

		INLINE const macstl::boolean <float> accumulator <minimum <macstl::vec <macstl::boolean <float>, 4>, macstl::vec <macstl::boolean <float>, 4> > >::operator() (const macstl::vec <macstl::boolean <float>, 4>& lhs) const
			{
				using namespace macstl;

				return mmx::movemask (lhs) == 15;
			}

		INLINE float accumulator <minimum <macstl::vec <float, 8>, macstl::vec <float, 8> > >::operator() (const macstl::vec <float, 8>& lhs) const
			{
				using namespace macstl;

// 				const vec<float,4> *vals = (vec<float,4>*) &lhs;
// 				float a = vals[0].min(), b = vals[1].min();
// 				return (a < b)? a : b;
				typedef vec<float,8>::half_data_type hdata_type;
				const hdata_type *vec4 = lhs.half_data();
				hdata_type result0 = _mm_min_ps( vec4[0], _mm_shuffle_ps(vec4[0], vec4[0], SHUFFLE4MASK(0,3,2,1)) );
				result0 = _mm_min_ps( result0, _mm_shuffle_ps(result0, result0, SHUFFLE4MASK(1, 0, 3, 2)) );
				hdata_type result1 = _mm_min_ps( vec4[1], _mm_shuffle_ps(vec4[1], vec4[1], SHUFFLE4MASK(0,3,2,1)) );
				result1 = _mm_min_ps( result1, _mm_shuffle_ps(result1, result1, SHUFFLE4MASK(1, 0, 3, 2)) );
				return __mvectorelem<float>( _mm_min_ps( result0, result1 ), 0 );
			}
		INLINE const macstl::boolean <float> accumulator <minimum <macstl::vec <macstl::boolean <float>, 8>, macstl::vec <macstl::boolean <float>, 8> > >::operator() (const macstl::vec <macstl::boolean <float>, 8>& lhs) const
			{
				using namespace macstl;

				return mmx::movemask (lhs) == 0xff;
			}

		INLINE double accumulator <minimum <macstl::vec <double, 2>, macstl::vec <double, 2> > >::operator() (const macstl::vec <double, 2>& lhs) const
			{
				using namespace macstl;

				return mmx::min (lhs, mmx::shuffled <0, 1> (lhs, lhs)) [0];
			}

		INLINE double accumulator <minimum <macstl::vec <double, 4>, macstl::vec <double, 4> > >::operator() (const macstl::vec <double, 4>& lhs) const
			{
				using namespace macstl;

				// _mm256_shuffle_pd doesn't work exactly the same as _mm_shuffle_ps, so we cannot simply
				// base the <double,4> case on the <float,4> case. In any case, most native AVX operations on <double,4>
				// take about twice the time as SSE2/3 <double,2> operations, so there is little penalty for emulating
				// a <double,4> operation with 2 <double,2> operations.
// 				const vec<double,2> *vals = (vec<double,2>*) &lhs;
// 				double a = vals[0].min(), b = vals[1].min();
// 				return (a < b)? a : b;
				typedef vec<double,4>::half_data_type hdata_type;
				const hdata_type *vec2 = lhs.half_data();
				hdata_type result0 = _mm_max_pd( vec2[0], _mm_shuffle_pd(vec2[0], vec2[0], SHUFFLE2MASK(0,1)) );
				hdata_type result1 = _mm_max_pd( vec2[1], _mm_shuffle_pd(vec2[1], vec2[1], SHUFFLE2MASK(0,1)) );
				return __mvectorelem<double>( _mm_max_pd( result0, result1 ), 0 );
			}

		INLINE const macstl::boolean <double> accumulator <minimum <macstl::vec <macstl::boolean <double>, 2>, macstl::vec <macstl::boolean <double>, 2> > >::operator() (const macstl::vec <macstl::boolean <double>, 2>& lhs) const
			{
				using namespace macstl;

				return mmx::movemask (lhs) == 3;
			}

		INLINE const macstl::boolean <double> accumulator <minimum <macstl::vec <macstl::boolean <double>, 4>, macstl::vec <macstl::boolean <double>, 4> > >::operator() (const macstl::vec <macstl::boolean <double>, 4>& lhs) const
			{
				using namespace macstl;

				return mmx::movemask (lhs) == 0xf;
			}

		INLINE const macstl::boolean <char> accumulator <minimum <macstl::vec <macstl::boolean <char>, 16>, macstl::vec <macstl::boolean <char>, 16> > >::operator() (const macstl::vec <macstl::boolean <char>, 16>& lhs) const
			{
				using namespace macstl;

				return mmx::movemask (lhs) == 65535;
			}

		// accumulator <plus>

		#if defined(__MMX__) && defined(__SSE__)

		INLINE unsigned short accumulator <plus <macstl::vec <unsigned short, 4>, macstl::vec <unsigned short, 4> > >::operator() (const macstl::vec <unsigned short, 4>& lhs) const
			{
				using namespace macstl;

				const vec <unsigned short, 4> result = mmx::add (lhs, mmx::shuffle <0, 3, 2, 1> (lhs));
				return mmx::extract <0> (mmx::add (result, mmx::shuffle <1, 0, 3, 2> (result)));
			}

		INLINE short accumulator <plus <macstl::vec <short, 4>, macstl::vec <short, 4> > >::operator() (const macstl::vec <short, 4>& lhs) const
			{
				using namespace macstl;

				const vec <short, 4> result = mmx::add (lhs, mmx::shuffle <0, 3, 2, 1> (lhs));
				return mmx::extract <0> (mmx::add (result, mmx::shuffle <1, 0, 3, 2> (result)));
			}

		#endif

		INLINE float accumulator <plus <macstl::vec <float, 4>, macstl::vec <float, 4> > >::operator() (const macstl::vec <float, 4>& lhs) const
			{
				using namespace macstl;

				const vec <float, 4> result = mmx::add (lhs, mmx::shuffles <0, 3, 2, 1> (lhs, lhs));
				return mmx::add (result, mmx::shuffles <1, 0, 3, 2> (result, result)) [0];
			}

 		INLINE float accumulator <plus <macstl::vec <float, 8>, macstl::vec <float, 8> > >::operator() (const macstl::vec <float, 8>& lhs) const
 			{
 				using namespace macstl;

// 				const vec<float,4> *vals = (vec<float,4>*) &lhs;
// 				return vals[0].sum() + vals[1].sum();
				const vec<float,8> s = mmx::hadd(lhs,lhs);
				return s[2] + s[3] + s[4] + s[5];
 			}

		INLINE double accumulator <plus <macstl::vec <double, 2>, macstl::vec <double, 2> > >::operator() (const macstl::vec <double, 2>& lhs) const
			{
				using namespace macstl;

				return mmx::add (lhs, mmx::shuffled <0, 1> (lhs, lhs)) [0];
			}

 		INLINE double accumulator <plus <macstl::vec <double, 4>, macstl::vec <double, 4> > >::operator() (const macstl::vec <double, 4>& lhs) const
 			{
 				using namespace macstl;

// 				const vec<double,2> *vals = (vec<double,2>*) &lhs;
// 				return vals[0].sum() + vals[1].sum();
				const vec<double,4> s = mmx::hadd(lhs,lhs);
				return s[0] + s[2];
 			}

		INLINE unsigned int accumulator <plus <macstl::vec <unsigned int, 4>, macstl::vec <unsigned int, 4> > >::operator() (const macstl::vec <unsigned int, 4>& lhs) const
			{
				using namespace macstl;

				const vec <unsigned int, 4> result = mmx::add (lhs, mmx::shuffle <0, 3, 2, 1> (lhs));
				return mmx::add (result, mmx::shuffle <1, 0, 3, 2> (result)) [0];
			}

		INLINE int accumulator <plus <macstl::vec <int, 4>, macstl::vec <int, 4> > >::operator() (const macstl::vec <int, 4>& lhs) const
			{
				using namespace macstl;

				const vec <int, 4> result = mmx::add (lhs, mmx::shuffle <0, 3, 2, 1> (lhs));
				return mmx::add (result, mmx::shuffle <1, 0, 3, 2> (result)) [0];
			}

		INLINE int accumulator <plus <macstl::vec <int, 8>, macstl::vec <int, 8> > >::operator() (const macstl::vec <int, 8>& lhs) const
			{
				using namespace macstl;

				const vec<int,4> *vals = (vec<int,4>*) &lhs;
				return vals[0].sum() + vals[1].sum();
			}


	}

#endif
