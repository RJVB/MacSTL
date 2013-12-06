/*
 *  altivec2mmx.h
 *  macstl
 *
 *  Created by Glen Low on Jun 15 2004.
 *
 *  Copyright (c) 2005 Pixelglow Software, all rights reserved.
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

#ifndef MACSTL_ALTIVEC2MMX_H
#define MACSTL_ALTIVEC2MMX_H

#include <macstl/vec.h>

#if !defined(__VEC__) && defined(__SSE__) && defined(__SSE2__)

namespace macstl
	{
		namespace altivec
			{
				DEFINE_VEC_PLATFORM_UNARY_FUNCTION(abs,absolute value)
				DEFINE_VEC_PLATFORM_UNARY_FUNCTION(abss,absolute value saturated)
				DEFINE_VEC_PLATFORM_BINARY_FUNCTION(add,add modulo)
				DEFINE_VEC_PLATFORM_BINARY_FUNCTION(adds,add saturated)
				DEFINE_VEC_PLATFORM_BINARY_FUNCTION(all_eq,compare all equal-to)
				DEFINE_VEC_PLATFORM_BINARY_FUNCTION(all_ne,compare all not-equal-to)
				DEFINE_VEC_PLATFORM_BINARY_FUNCTION(vand,bitwise AND)
				DEFINE_VEC_PLATFORM_BINARY_FUNCTION(andc,bitwise AND-NOT)
				DEFINE_VEC_PLATFORM_BINARY_FUNCTION(any_eq,compare any equal-to)
				DEFINE_VEC_PLATFORM_BINARY_FUNCTION(any_ne,compare any not-equal-to)
				DEFINE_VEC_PLATFORM_BINARY_FUNCTION(avg,average integer)
				DEFINE_VEC_PLATFORM_BINARY_FUNCTION(cmpeq,compare equal-to)
				DEFINE_VEC_PLATFORM_BINARY_FUNCTION(cmpge,compare greater-than-or-equal-to)
				DEFINE_VEC_PLATFORM_BINARY_FUNCTION(cmpgt,compare greater-than)
				DEFINE_VEC_PLATFORM_BINARY_FUNCTION(cmple,compare less-than-or-equal-to)
				DEFINE_VEC_PLATFORM_BINARY_FUNCTION(cmplt,compare less than)
				DEFINE_VEC_PLATFORM_UNARY_FUNCTION_WITH_LITERAL(ctf,convert from fixed-point word)
				DEFINE_VEC_PLATFORM_BINARY_FUNCTION(ld,load indexed)
				DEFINE_VEC_PLATFORM_TERNARY_FUNCTION(madd,multiply-add float)
				DEFINE_VEC_PLATFORM_BINARY_FUNCTION(max,maximum)
				DEFINE_VEC_PLATFORM_BINARY_FUNCTION(mergeh,merge high)
				DEFINE_VEC_PLATFORM_BINARY_FUNCTION(mergel,merge low)			
				DEFINE_VEC_PLATFORM_BINARY_FUNCTION(min,minimum)
				DEFINE_VEC_PLATFORM_TERNARY_FUNCTION(mladd,multiply-low and add modulo)
				DEFINE_VEC_PLATFORM_TERNARY_FUNCTION(msum,multiply-sum modulo)
				DEFINE_VEC_PLATFORM_TERNARY_FUNCTION(nmsub,negative multiply-subtract)
				DEFINE_VEC_PLATFORM_BINARY_FUNCTION(nor,bitwise NOR)
				DEFINE_VEC_PLATFORM_BINARY_FUNCTION(vor,bitwise OR)
				DEFINE_VEC_PLATFORM_BINARY_FUNCTION(packs,pack saturate)
				DEFINE_VEC_PLATFORM_BINARY_FUNCTION(packsu,pack unsigned saturate)
				DEFINE_VEC_PLATFORM_UNARY_FUNCTION(re,reciprocal estimate)
				DEFINE_VEC_PLATFORM_UNARY_FUNCTION(round,round)
				DEFINE_VEC_PLATFORM_UNARY_FUNCTION(rsqrte,reciprocal square root estimate)
				DEFINE_VEC_PLATFORM_TERNARY_FUNCTION(sel,conditional select)
				DEFINE_VEC_PLATFORM_UNARY_FUNCTION_WITH_LITERAL(splat,splat)
				DEFINE_VEC_PLATFORM_TERNARY_FUNCTION(st,store indexed)
				DEFINE_VEC_PLATFORM_BINARY_FUNCTION(sub,subtract modulo)
				DEFINE_VEC_PLATFORM_BINARY_FUNCTION(subs,subtract saturate)
				DEFINE_VEC_PLATFORM_UNARY_FUNCTION(trunc,truncate)
				DEFINE_VEC_PLATFORM_UNARY_FUNCTION(unpackh,unpack high)
				DEFINE_VEC_PLATFORM_UNARY_FUNCTION(unpackl,unpack low)		
				DEFINE_VEC_PLATFORM_BINARY_FUNCTION(vxor,bitwise XOR)
				
				// vec_abs
					
				template <> struct abs_function <vec <signed char, 16> >
					{
						typedef vec <signed char, 16> argument_type;
						typedef vec <signed char, 16> result_type;
						
						result_type operator() (const argument_type& lhs)
							{
								vec <boolean <char>, 16> gt = mmx::cmpgt (argument_type::fill <0> (), lhs);
								return mmx::sub (mmx::vxor (lhs, gt), data_cast <result_type> (lhs));
							}
					};

				template <> struct abs_function <vec <short, 8> >
					{
						typedef vec <short, 8> argument_type;
						typedef vec <short, 8> result_type;
						
						result_type operator() (const argument_type& lhs)
							{
								return mmx:max (lhs, mmx::sub (argument_type::fill <0> (), lhs));
							}
					};

				template <> struct abs_function <vec <int, 4> >
					{
						typedef vec <int, 4> argument_type;
						typedef vec <int, 4> result_type;
						
						result_type operator() (const argument_type& lhs)
							{
								vec <int, 4> sr = mmx::srai <31> (lhs);
								return mmx::sub (mmx::vxor (lhs, sr), sr);
							}
					};

				template <> struct abs_function <vec <float, 4> >
					{
						typedef vec <float, 4> argument_type;
						typedef vec <float, 4> result_type;
						
						result_type operator() (const argument_type& lhs)
							{
								return mmx::vand (lhs, argument_type::fill <0x7FFFFFFFU> ());
							}
					};

				// vec_abss

				template <> struct abss_function <vec <signed char, 16> >
					{
						typedef vec <signed char, 16> argument_type;
						typedef vec <signed char, 16> result_type;
						
						result_type operator() (const argument_type& lhs)
							{
								vec <boolean <char>, 16> gt = mmx::cmpgt (argument_type::fill <0> (), lhs);
								return mmx::subs (mmx::vxor (lhs, gt), data_cast <result_type> (lhs));
							}
					};

				template <> struct abss_function <vec <short, 8> >
					{
						typedef vec <short, 8> argument_type;
						typedef vec <short, 8> result_type;
						
						result_type operator() (const argument_type& lhs)
							{
								return mmx:max (lhs, mmx::subs (argument_type::fill <0> (), lhs));
							}
					};
					
				// vec_add
					
				template <typename T, std::size_t n> struct add_function <vec <T, n>, vec <T, n> >:
					public mmx::add_function <vec <T, n>, vec <T, n> >
					{
					};
					
				// vec_adds

				template <typename T, std::size_t n> struct adds_function <vec <T, n>, vec <T, n> >:
					public mmx::adds_function <vec <T, n>, vec <T, n> >
					{
					};
					
				// vec_all_eq
						
				template <typename T, std::size_t n> struct all_eq_function <vec <T, n>, vec <T, n> >
					{
						typedef vec <T, n> first_argument_type;
						typedef vec <T, n> second_argument_type;
						typedef bool result_type;
						
						result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs)
							{
								return mmx::movemask (data_cast <vec <unsigned char, 16> > (mmx::cmpeq (lhs, rhs))) == 255;
							}
					};
					
				template <> struct all_eq_function <vec <float, 4>, vec <float, 4> >
					{
						typedef vec <float, 4> first_argument_type;
						typedef vec <float, 4> second_argument_type;
						typedef bool result_type;
						
						result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs)
							{
								return mmx::movemask (mmx::cmpeq (lhs, rhs)) == 15;
							}
					};
					
				// vec_all_ne

				template <typename T, std::size_t n> struct all_ne_function <vec <T, n>, vec <T, n> >
					{
						typedef vec <T, n> first_argument_type;
						typedef vec <T, n> second_argument_type;
						typedef bool result_type;
						
						result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs)
							{
								return mmx::movemask (data_cast <vec <unsigned char, 16> > (mmx::cmpeq (lhs, rhs))) == 0;
							}
					};
					
				template <> struct all_ne_function <vec <float, 4>, vec <float, 4> >
					{
						typedef vec <float, 4> first_argument_type;
						typedef vec <float, 4> second_argument_type;
						typedef bool result_type;
						
						result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs)
							{
								return mmx::movemask (mmx::cmpneq (lhs, rhs)) == 15;
							}
					};

				// vec_and
				
				template <typename T, std::size_t n> struct vand_function <vec <T, n>, vec <T, n> >:
					public mmx::vand_function <vec <T, n>, vec <T, n> >
					{
					};

				// vec_andc
				
				template <typename T, std::size_t n> struct andc_function <vec <T, n>, vec <T, n> >
					{
						typedef vec <T, n> first_argument_type;
						typedef vec <T, n> second_argument_type;
						typedef vec <T, n> result_type;
						
						result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs)
							{
								return mmx::andnot (rhs, lhs);
							}
					};

				// vec_any_eq
				
				template <typename T, std::size_t n> struct any_eq_function <vec <T, n>, vec <T, n> >
					{
						typedef vec <T, n> first_argument_type;
						typedef vec <T, n> second_argument_type;
						typedef bool result_type;
						
						result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs)
							{
								return mmx::movemask (data_cast <vec <unsigned char, 16> > (mmx::cmpeq (lhs, rhs))) != 0;
							}
					};

				template <> struct any_eq_function <vec <float, 4>, vec <float, 4> >
					{
						typedef vec <float, 4> first_argument_type;
						typedef vec <float, 4> second_argument_type;
						typedef bool result_type;
						
						result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs)
							{
								return mmx::movemask (mmx::cmpeq (lhs, rhs)) != 0;
							}
					};

				// vec_any_ne
				
				template <typename T, std::size_t n> struct any_ne_function <vec <T, n>, vec <T, n> >
					{
						typedef vec <T, n> first_argument_type;
						typedef vec <T, n> second_argument_type;
						typedef bool result_type;
						
						result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs)
							{
								return mmx::movemask (data_cast <vec <unsigned char, 16> > (mmx::cmpeq (lhs, rhs))) != 255;
							}
					};
					
				template <> struct any_ne_function <vec <float, 4>, vec <float, 4> >
					{
						typedef vec <float, 4> first_argument_type;
						typedef vec <float, 4> second_argument_type;
						typedef bool result_type;
						
						result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs)
							{
								return mmx::movemask (mmx::cmpneq (lhs, rhs)) != 0;
							}
					};

				// vec_avg
				
				template <typename T, std::size_t n> struct avg_function <vec <T, n>, vec <T, n> >:
					public mmx::avg_function <vec <T, n>, vec <T, n> >
					{
					};

				// vec_cmpeq
				
				template <typename T, std::size_t n> struct cmpeq_function <vec <T, n>, vec <T, n> >:
					public mmx::cmpeq_function <vec <T, n>, vec <T, n> >
					{
					};

				// vec_cmpge
				
				template <> struct cmpge_function <vec <float, 4>, vec <float, 4> >:
					public mmx::cmpge_function <vec <float, 4>, vec <float, 4> >
					{
					};

				// vec_cmpgt
				
				template <> struct cmpgt_function <macstl::vec <float, 4>, macstl::vec <float, 4> >:
					public macstl::mmx::cmpgt_function <macstl::vec <float, 4>, macstl::vec <float, 4> >
					{
					};

				template <> struct cmpgt_function <macstl::vec <double, 2>, macstl::vec <double, 2> >:
					public macstl::mmx::cmpgt_function <macstl::vec <double, 2>, macstl::vec <double, 2> >
					{
					};

				template <> struct cmpgt_function <macstl::vec <unsigned char, 16>, macstl::vec <unsigned char, 16> >
					{
						typedef macstl::vec <unsigned char, 16> first_argument_type;
						typedef macstl::vec <unsigned char, 16> second_argument_type;
						typedef macstl::vec <macstl::boolean <char>, 16> result_type;
						
						result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
							{
								using namespace macstl;

								vec <unsigned char, 16> offset = vec <unsigned char, 16>::fill <0x80U> ();
								return mmx::cmpgt (
									data_cast <vec <signed char, 16> > (mmx::sub (lhs, offset)),
									data_cast <vec <signed char, 16> > (mmx::sub (rhs, offset)));
							}
					};

				template <> struct cmpgt_function <macstl::vec <signed char, 16>, macstl::vec <signed char, 16> >:
					public macstl::mmx::cmpgt_function <macstl::vec <signed char, 16>, macstl::vec <signed char, 16> >
					{
					};

				template <> struct cmpgt_function <macstl::vec <unsigned short, 8>, macstl::vec <unsigned short, 8> >
					{
						typedef macstl::vec <unsigned short, 8> first_argument_type;
						typedef macstl::vec <unsigned short, 8> second_argument_type;
						typedef macstl::vec <macstl::boolean <short>, 8> result_type;
						
						result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
							{
								using namespace macstl;

								vec <unsigned short, 8> offset = vec <unsigned short, 8>::fill <0x8000U> ();
								return mmx::cmpgt (
									data_cast <vec <short, 8> > (mmx::sub (lhs, offset)),
									data_cast <vec <short, 8> > (mmx::sub (rhs, offset)));
							}
					};

				template <> struct cmpgt_function <macstl::vec <short, 8>, macstl::vec <short, 8> >:
					public macstl::mmx::cmpgt_function <macstl::vec <short, 8>, macstl::vec <short, 8> >
					{
					};

				template <> struct cmpgt_function <macstl::vec <unsigned int, 4>, macstl::vec <unsigned int, 4> >
					{
						typedef macstl::vec <unsigned int, 4> first_argument_type;
						typedef macstl::vec <unsigned int, 4> second_argument_type;
						typedef macstl::vec <macstl::boolean <int>, 4> result_type;
						
						result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
							{
								using namespace macstl;

								vec <unsigned int, 4> offset = vec <unsigned int, 4>::fill <0x80000000U> ();
								return mmx::cmpgt (
									data_cast <vec <int, 4> > (mmx::sub (lhs, offset)),
									data_cast <vec <int, 4> > (mmx::sub (rhs, offset)));
							}
					};

				template <> struct cmpgt_function <macstl::vec <int, 4>, macstl::vec <int, 4> >:
					public macstl::mmx::cmpgt_function <macstl::vec <int, 4>, macstl::vec <int, 4> >
					{
					};

				// vec_cmple
				
				template <> struct cmple_function <vec <float, 4>, vec <float, 4> >:
					public mmx::cmple_function <vec <float, 4>, vec <float, 4> >
					{
					};

				// vec_cmplt
				
				template <> struct cmplt_function <macstl::vec <float, 4>, macstl::vec <float, 4> >:
					public macstl::mmx::cmplt_function <macstl::vec <float, 4>, macstl::vec <float, 4> >
					{
					};

				template <> struct cmplt_function <macstl::vec <double, 2>, macstl::vec <double, 2> >:
					public macstl::mmx::cmplt_function <macstl::vec <double, 2>, macstl::vec <double, 2> >
					{
					};

				template <> struct cmplt_function <macstl::vec <unsigned char, 16>, macstl::vec <unsigned char, 16> >
					{
						typedef macstl::vec <unsigned char, 16> first_argument_type;
						typedef macstl::vec <unsigned char, 16> second_argument_type;
						typedef macstl::vec <macstl::boolean <char>, 16> result_type;
						
						result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
							{
								using namespace macstl;

								vec <unsigned char, 16> offset = vec <unsigned char, 16>::fill <0x80U> ();
								return mmx::cmplt (
									data_cast <vec <signed char, 16> > (mmx::sub (lhs, offset)),
									data_cast <vec <signed char, 16> > (mmx::sub (rhs, offset)));
							}
					};

				template <> struct cmplt_function <macstl::vec <signed char, 16>, macstl::vec <signed char, 16> >:
					public macstl::mmx::cmplt_function <macstl::vec <signed char, 16>, macstl::vec <signed char, 16> >
					{
					};

				template <> struct cmplt_function <macstl::vec <unsigned short, 8>, macstl::vec <unsigned short, 8> >
					{
						typedef macstl::vec <unsigned short, 8> first_argument_type;
						typedef macstl::vec <unsigned short, 8> second_argument_type;
						typedef macstl::vec <macstl::boolean <short>, 8> result_type;
						
						result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
							{
								using namespace macstl;

								vec <unsigned short, 8> offset = vec <unsigned short, 8>::fill <0x8000U> ();
								return mmx::cmplt (
									data_cast <vec <short, 8> > (mmx::sub (lhs, offset)),
									data_cast <vec <short, 8> > (mmx::sub (rhs, offset)));
							}
					};

				template <> struct cmplt_function <macstl::vec <short, 8>, macstl::vec <short, 8> >:
					public macstl::mmx::cmplt_function <macstl::vec <short, 8>, macstl::vec <short, 8> >
					{
					};

				template <> struct cmplt_function <macstl::vec <unsigned int, 4>, macstl::vec <unsigned int, 4> >
					{
						typedef macstl::vec <unsigned int, 4> first_argument_type;
						typedef macstl::vec <unsigned int, 4> second_argument_type;
						typedef macstl::vec <macstl::boolean <int>, 4> result_type;
						
						result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs) const
							{
								using namespace macstl;

								vec <unsigned int, 4> offset = vec <unsigned int, 4>::fill <0x80000000U> ();
								return mmx::cmplt (
									data_cast <vec <int, 4> > (mmx::sub (lhs, offset)),
									data_cast <vec <int, 4> > (mmx::sub (rhs, offset)));
							}
					};

				template <> struct cmplt_function <macstl::vec <int, 4>, macstl::vec <int, 4> >:
					public macstl::mmx::cmplt_function <macstl::vec <int, 4>, macstl::vec <int, 4> >
					{
					};
				
				// vec_ctf
				
				template <typename T, std::size_t n> struct ctf_function <0, vec <T, n> >
					{
						typedef vec <T, n> argument_type;
						typedef vec <float, n> result_type;
						
						result_type operator() (const argument_type& lhs)
							{
								return mmx::cvt <vec <float, 4> > (lhs);
							}
					};

				// vec_ld
				
				template <typename T> struct ld_function <int, const T*>
					{
						typedef int first_argument_type;
						typedef const T* second_argument_type;
						typedef vec <T, 16 / sizeof (T)> result_type;
						
						result_type operator() (first_argument_type lhs, second_argument_type rhs) const
							{
								return mmx::load (reinterpret_cast <const T*> (reinterpret_cast <const char*> (rhs) + lhs));
							}
					};

				template <typename T> struct ld_function <int, T*>
					{
						typedef int first_argument_type;
						typedef T* second_argument_type;
						typedef vec <T, 16 / sizeof (T)> result_type;
						
						result_type operator() (first_argument_type lhs, second_argument_type rhs) const
							{
								return mmx::load (reinterpret_cast <T*> (reinterpret_cast <char*> (rhs) + lhs));
							}
					};

				#ifndef MACSTLIZER_NEED_PRECISE_TRANSLATION
				
				// vec_madd
				
				template <> struct madd_function <vec <float, 4>, vec <float, 4> >
					{
						typedef vec <float, 4> first_argument_type;
						typedef vec <float, 4> second_argument_type;
						typedef vec <float, 4> third_argument_type;
						typedef vec <float, 4> result_type;
						
						result_type operator() (const first_argument_type& lhs, const second_argument_type& mhs, const third_argument_type& rhs)
							{
								return mmx::add (mmx::mul (lhs, mhs), rhs);
							}
					};
					
				#endif

				// vec_max
				
				template <typename T, std::size_t n> struct max_function <vec <T, n>, vec <T, n> >:
					public mmx::max_function <vec <T, n>, vec <T, n> >
					{
					};

				template <> struct max_function <vec <signed char, 16>, vec <signed char, 16> >
					{
						typedef vec <signed char, 16> virst_argument_type;
						typedef vec <signed char, 16> second_argument_type;
						typedef vec <signed char, 16> result_type;
						
						result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs)
							{
								const vec <boolean <char>, 16> gt = mmx::cmpgt (lhs, rhs);
								return mmx::vor (mmx::andnot (gt, rhs), mmx::vand (gt, lhs));
							}
					};

				template <> struct max_function <vec <short, 8>, vec <short, 8> >
					{
						typedef vec <short, 8> virst_argument_type;
						typedef vec <short, 8> second_argument_type;
						typedef vec <short, 8> result_type;
						
						result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs)
							{
								const vec <boolean <short>, 8> gt = mmx::cmpgt (lhs, rhs);
								return mmx::vor (mmx::andnot (gt, rhs), mmx::vand (gt, lhs));
							}
					};

				template <> struct max_function <vec <int, 4>, vec <int, 4> >
					{
						typedef vec <int, 4> virst_argument_type;
						typedef vec <int, 4> second_argument_type;
						typedef vec <int, 4> result_type;
						
						result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs)
							{
								const vec <boolean <int>, 4> gt = mmx::cmpgt (lhs, rhs);
								return mmx::vor (mmx::andnot (gt, rhs), mmx::vand (gt, lhs));
							}
					};

				// vec_mergeh
				
				template <typename T, std::size_t n> struct mergeh_function <vec <T, n>, vec <T, n> >:
					public mmx::unpacklo_function <vec <T, n>, vec <T, n> >
					{
					};
				
				// vec_mergel
				
				template <typename T, std::size_t n> struct mergel_function <vec <T, n>, vec <T, n> >:
					public mmx::unpackhi_function <vec <T, n>, vec <T, n> >
					{
					};

				// vec_min
				
				template <typename T, std::size_t n> struct min_function <vec <T, n>, vec <T, n> >:
					public mmx::min_function <vec <T, n>, vec <T, n> >
					{
					};
					
				template <> struct min_function <vec <signed char, 16>, vec <signed char, 16> >
					{
						typedef vec <signed char, 16> virst_argument_type;
						typedef vec <signed char, 16> second_argument_type;
						typedef vec <signed char, 16> result_type;
						
						result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs)
							{
								const vec <boolean <char>, 16> gt = mmx::cmpgt (lhs, rhs);
								return mmx::vor (mmx::vand (gt, rhs), mmx::andnot (gt, lhs));
							}
					};

				template <> struct min_function <vec <short, 8>, vec <short, 8> >
					{
						typedef vec <short, 8> virst_argument_type;
						typedef vec <short, 8> second_argument_type;
						typedef vec <short, 8> result_type;
						
						result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs)
							{
								const vec <boolean <short>, 8> gt = mmx::cmpgt (lhs, rhs);
								return mmx::vor (mmx::vand (gt, rhs), mmx::andnot (gt, lhs));
							}
					};

				template <> struct min_function <vec <int, 4>, vec <int, 4> >
					{
						typedef vec <int, 4> virst_argument_type;
						typedef vec <int, 4> second_argument_type;
						typedef vec <int, 4> result_type;
						
						result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs)
							{
								const vec <boolean <int>, 4> gt = mmx::cmpgt (lhs, rhs);
								return mmx::vor (mmx::vand (gt, rhs), mmx::andnot (gt, lhs));
							}
					};
				
				// vec_mladd
				
				template <typename T, std::size_t n> struct mladd_function <vec <T, n>, vec <T, n>, vec <T, n> >
					{
						typedef vec <T, n> first_argument_type;
						typedef vec <T, n> second_argument_type;
						typedef vec <T, n> third_argument_type;
						typedef vec <T, n> result_type;
						
						result_type operator() (const first_argument_type& lhs, const second_argument_type& mhs, const third_argument_type& rhs)
							{
								return mmx::add (mmx::mullo (lhs, mhs), rhs);
							}
					};

				// vec_msum
				
				template <> struct msum_function <vec <unsigned short, 8>, vec <unsigned short, 8>, vec <unsigned int, 4> >
					{
						typedef vec <unsigned short, 8> first_argument_type;
						typedef vec <unsigned short, 8> second_argument_type;
						typedef vec <unsigned int, 4> third_argument_type;
						typedef vec <unsigned int, 4> result_type;
						
						result_type operator() (const first_argument_type& lhs, const second_argument_type& mhs, const third_argument_type& rhs)
							{
								return mmx::add (mmx::madd (lhs, mhs), rhs);
							}
					};

				template <> struct msum_function <vec <short, 8>, vec <short, 8>, vec <int, 4> >
					{
						typedef vec <short, 8> first_argument_type;
						typedef vec <short, 8> second_argument_type;
						typedef vec <int, 4> third_argument_type;
						typedef vec <int, 4> result_type;
						
						result_type operator() (const first_argument_type& lhs, const second_argument_type& mhs, const third_argument_type& rhs)
							{
								return mmx::add (mmx::madd (lhs, mhs), rhs);
							}
					};

				#ifdef MACSTLIZER_NEED_PRECISE_TRANSLATION
				
				// vec_nmsub
				
				template <> struct nmsub_function <vec <float, 4>, vec <float, 4> >
					{
						typedef vec <float, 4> first_argument_type;
						typedef vec <float, 4> second_argument_type;
						typedef vec <float, 4> third_argument_type;
						typedef vec <float, 4> result_type;
						
						result_type operator() (const first_argument_type& lhs, const second_argument_type& mhs, const third_argument_type& rhs)
							{
								return mmx::sub (rhs, mmx::mul (lhs, mhs));
							}
					};
				
				#endif
				
				// vec_nor
				
				template <typename T, std::size_t n> struct nor_function <vec <T, n>, vec <T, n> >
					{
						typedef vec <T, n> first_argument_type;
						typedef vec <T, n> second_argument_type;
						typedef vec <T, n> result_type;
						
						result_type operator() (const first_argument_type& lhs, const second_argument_type& rhs)
							{
								return mmx::vxor (mmx::vor (lhs, rhs), result_type::template set <-1> ());
							}
					};

				// vec_or
				
				template <typename T, std::size_t n> struct vor_function <vec <T, n>, vec <T, n> >:
					public mmx::vor_function <vec <T, n>, vec <T, n> >
					{
					};

				// vec_packs
				
				template <typename T, std::size_t n> struct packs_function <vec <T, n>, vec <T, n> >:
					public mmx::packs_function <vec <T, n>, vec <T, n> >
					{
					};

				// vec_packsu
				
				template <typename T, std::size_t n> struct packsu_function <vec <T, n>, vec <T, n> >:
					public mmx::packus_function <vec <T, n>, vec <T, n> >
					{
					};
				
				// vec_re
				
				template <> struct re_function <vec <float, 4> >:
					public mmx::rcp_function <vec <float, 4> >
					{
					};

				#ifndef MACSTLIZER_NEED_PRECISE_TRANSLATION
				
				// vec_round
				
				template <> struct round_function <vec <float, 4> >
					{
						typedef vec <float, 4> argument_type;
						typedef vec <float, 4> result_type;
						
						result_type operator() (const argument_type& lhs)
							{
								return mmx::cvt <result_type> (mmx::cvt <vec <int, 4> > (lhs));
							}
					};

				#endif
				
				// vec_rsqrte
				
				template <> struct rsqrte_function <vec <float, 4> >:
					public mmx::rsqrt_function <vec <float, 4> >
					{
					};
				
				// vec_sel
				
				template <typename T, std::size_t n> struct sel_function <vec <T, n>, vec <T, n>, vec <typename vec <T, n>::boolean_type, n> >
					{
						typedef vec <T, n> first_argument_type;
						typedef vec <T, n> second_argument_type;
						typedef vec <typename vec <T, n>::boolean_type, n> third_argument_type;
						typedef vec <T, n> result_type;
						
						result_type operator() (const first_argument_type& lhs, const second_argument_type& mhs, const third_argument_type& rhs)
							{
								return mmx::vor (mmx::vand (rhs, mhs), mmx::andnot (rhs, lhs));
							}
					};

				// vec_splat
				
				template <unsigned int i, typename T> struct splat_function <i, vec <T, 4> >
					{
						typedef vec <T, 4> argument_type;
						typedef vec <T, 4> result_type;
						
						result_type operator() (const argument_type& lhs)
							{
								return mmx::shuffle <3 - i, 3 - i, 3 - i, 3 - i> (lhs);
							}
					};

				template <unsigned int i> struct splat_function <i, vec <float, 4> >
					{
						typedef vec <float, 4> argument_type;
						typedef vec <float, 4> result_type;
						
						result_type operator() (const argument_type& lhs)
							{
								return mmx::shuffles <3 - i, 3 - i, 3 - i, 3 - i> (lhs, lhs);
							}
					};

				// vec_st
				
				template <typename T1, std::size_t n1, typename T2> struct st_function <vec <T1, n1>, int, T2*>
					{	
						typedef vec <T1, n1> first_argument_type;	
						typedef int second_argument_type;	
						typedef T2* third_argument_type;
					
						typedef void result_type;
												
						result_type operator() (const first_argument_type& lhs,
							second_argument_type mhs, third_argument_type rhs) const
							{		
								return mmx::store (reinterpret_cast <T2*> (reinterpret_cast <char*> (rhs) + mhs),
									lhs);	
							}		
					};

				// vec_sub
				
				template <typename T, std::size_t n> struct sub_function <vec <T, n>, vec <T, n> >:
					public mmx::sub_function <vec <T, n>, vec <T, n> >
					{
					};

				// vec_subs
				
				template <typename T, std::size_t n> struct subs_function <vec <T, n>, vec <T, n> >:
					public mmx::subs_function <vec <T, n>, vec <T, n> >
					{
					};


				#ifndef MACSTLIZER_NEED_PRECISE_TRANSLATION
				
				// vec_trunc
				
				template <> struct trunc_function <vec <float, 4> >
					{
						typedef vec <float, 4> argument_type;
						typedef vec <float, 4> result_type;
						
						result_type operator() (const argument_type& lhs)
							{
								return mmx::cvt <result_type> (mmx::cvtt <vec <int, 4> > (lhs));
							}
					};

				#endif

				// vec_unpackh
				
				template <> struct unpackh_function <vec <signed char, 16> >
					{
						typedef vec <signed char, 16> argument_type;
						typedef vec <short, 8> result_type;
						
						result_type operator() (const argument_type& lhs)
							{
								return mmx::srai <8> (data_cast <result_type> (mmx::unpacklo (lhs, argument_type::fill <0> ())));
							}
					};

				// vec_unpackl
				
				template <> struct unpackl_function <vec <signed char, 16> >
					{
						typedef vec <signed char, 16> argument_type;
						typedef vec <short, 8> result_type;
						
						result_type operator() (const argument_type& lhs)
							{
								return mmx::srai <8> (data_cast <result_type> (mmx::unpackhi (lhs, argument_type::fill <0> ())));
							}
					};
				
				// vec_xor
				
				template <typename T, std::size_t n> struct vxor_function <vec <T, n>, vec <T, n> >:
					public mmx::vxor_function <vec <T, n>, vec <T, n> >
					{
					};
					
			}
	}


#endif

#endif
