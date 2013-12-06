#!/usr/bin/perl
#
# Created by Glen Low on Jun 22 2004.
#
# Copyright (c) 2005 Pixelglow Software, all rights reserved.
# http://www.pixelglow.com/macstl/
# macstl@pixelglow.com
#
# Unless explicitly acquired and licensed from Licensor under the Pixelglow
# Software License ("PSL") Version 2.0 or greater, the contents of this file
# are subject to the Reciprocal Public License ("RPL") Version 1.1, or
# subsequent versions as allowed by the RPL, and You may not copy or use this
# file in either source code or executable form, except in compliance with the
# terms and conditions of the RPL.
#
# While it is an open-source license, the RPL prohibits you from keeping your
# derivations of this file proprietary even if you only deploy them in-house.
# You may obtain a copy of both the PSL and the RPL ("the Licenses") from
# Pixelglow Software ("the Licensor") at http://www.pixelglow.com/.
#
# Software distributed under the Licenses is distributed on an "AS IS" basis,
# WITHOUT WARRANTY OF ANY KIND, either express or implied. See the Licenses
# for the specific language governing rights and limitations under the
# Licenses. Notwithstanding anything else in the Licenses, if any clause of
# the Licenses which purports to disclaim or limit the Licensor's liability
# for breach of any condition or warranty (whether express or implied by law)
# would otherwise be void, that clause is deemed to be subject to the
# reservation of liability of the Licensor to supply the software again or to
# repair the software or to pay the cost of having the software supplied again
# or repaired, at the Licensor's option. 
#

# use C line seperator instead of newline
$/ = ';';

$comment = '//.*\n|/\*(?:.|\n)*\*/';
$ws = '(?:\s|' . $comment . ')';
$ws0 = $ws . '*';
$ws1 = $ws . '+';
$vector = '(?:__){0,1}vector';
$bool = '(?:__){0,1}bool';
$pixel = '(?:__){0,1}pixel';
$signed = 'signed';
$unsigned = 'unsigned';
$nest = qr/[\(\{](?:(?>[^\(\)\{\}]+)|(??{ $nest }))*[\)\}]/;	# parses nested brackets

# raw vector types
$vectorFloat = $vector . $ws1 . 'float';
$vectorSignedInt = $vector . $ws1 . $signed . $ws1 . 'int';
$vectorUnsignedInt = $vector . $ws1 . $unsigned . $ws1 . 'int';
$vectorBoolInt = $vector . $ws1 . $bool . $ws1 . 'int';
$vectorSignedShort = $vector . $ws1 . $signed . $ws1 . 'short';
$vectorUnsignedShort = $vector . $ws1 . $unsigned . $ws1 . 'short';
$vectorBoolShort = $vector . $ws1 . $bool . $ws1 . 'short';
$vectorPixel = $vector . $ws1 . $pixel;
$vectorSignedChar = $vector . $ws1 . $signed . $ws1 . 'char';
$vectorUnsignedChar = $vector . $ws1 . $unsigned . $ws1 . 'char';
$vectorBoolChar = $vector . $ws1 . $bool . $ws1 . 'char';

# obj vector types
$vecFloat = 'vec <float, 4>';
$vecInt = 'vec <int, 4>';
$vecUnsignedInt = 'vec <unsigned int, 4>';
$vecBooleanInt = 'vec <boolean <int>, 4>';
$vecShort = 'vec <short, 8>';
$vecUnsignedShort = 'vec <unsigned short, 8>';
$vecBooleanShort = 'vec <boolean <short>, 8>';
$vecPixel = 'vec <pixel, 8>';
$vecSignedChar = 'vec <signed char, 16>';
$vecUnsignedChar = 'vec <unsigned char, 16>';
$vecBooleanChar = 'vec <boolean <char>, 16>';

# if you want to use typedefs instead of the templated types, define the right ones here

# $vecFloatTypeDef = "vFloat";
# $vecIntTypeDef = "vSInt32";
# $vecUnsignedIntTypeDef = "vUInt32";
# $vecBooleanIntTypeDef = "vBool32";
# $vecShortTypeDef = "vSInt16";
# $vecUnsignedShortTypeDef = "vUInt16";
# $vecBooleanShortTypeDef = "";
# $vecPixelTypeDef = "";
# $vecSignedCharTypeDef = "vSInt8";
# $vecUnsignedCharTypeDef = "vUInt8";
# $vecBooleanCharTypeDef = "";

sub replaceVectorDataCast
	{
		my $raw = $_ [0];
		my $obj = $_ [1];
		
		# (vector float) func (...) => data_cast <vec <float, 4> > (func (...))
		# (vector float) x => data_cast <vec <float, 4> > (x)
		while (s/\($ws0$raw$ws0\)$ws0(\w+(?:$ws0$nest){0,1})/data_cast <$obj > ($1)/g)
			{
			}
	}

sub replaceVectorType
	{
		my $raw = $_ [0];
		my $obj = $_ [1];
		
		# vector float => vec <float, 4>
		s/\b$raw\b/$obj/g;
	}
	
sub replaceFloatVector
	{
		my $raw = $_ [0];
		my $obj = $_ [1];
		
		replaceVectorDataCast ($raw, $obj);
		
		# (vector pixel) (...) => vec <pixel, 4>::fill <...> ()
		# (vector pixel) (... vec_ ...) => data_cast <vec <pixel, 4> > (... vec_ ...)
		# (vector pixel) (..., ....) => vec <pixel, 4>::set <...> ()
		while (/\($ws0$raw$ws0\)$ws0($nest)/g)
			{
				my $pre = $- [0];
				my $post = $+ [0];
				my $replace = "";
				my $nested = $1;
				if ($nested =~ /vec_/)
					{
						$replace = 'data_cast <' . $obj . ' > ' . $nested . '';
					}
				elsif ($nested =~ /,/)
					{
						$replace = $obj . '::set ' . $nested;
					}
				else
					{
						$replace = $obj . '::fill ' . $nested;
					}
				substr ($_, $pre, $post - $pre) = $replace;
			}
			
		replaceVectorType ($raw, $obj);
	}

sub replaceVector
	{
		my $raw = $_ [0];
		my $obj = $_ [1];
		
		replaceVectorDataCast ($raw, $obj);
		
		# (vector float) (...) => vec <float, 4>::fill (...)
		# (vector float) (... vec_ ...) => data_cast <vec <float, 4> > (... vec_ ...)
		# (vector float) (..., ....) => vec <float, 4>::set (...)
		while (/\($ws0$raw$ws0\)$ws0($nest)/g)
			{
				my $pre = $- [0];
				my $post = $+ [0];
				my $replace = "";
				my $nested = substr ($1, 1, length ($1) - 2);
				if ($nested =~ /vec_/)
					{
						$replace = 'data_cast <' . $obj . ' > (' . $nested . ')';
					}
				elsif ($nested =~ /,/)
					{
						$replace = $obj . '::set <' . $nested . '> ()';
					}
				else
					{
						$replace = $obj . '::fill <' . $nested . '> ()';
					}
				substr ($_, $pre, $post - $pre) = $replace;
			}
			
		replaceVectorType ($raw, $obj);
	}
	
sub replaceVectorFunction
	{
		my $func = $_ [0];
		
		s/\bvec_$func\b/altivec::$func/g;
	}

sub replaceVectorReservedFunction
	{
		my $func = $_ [0];
		
		s/\bvec_$func\b/altivec::v$func/g;
	}

sub replaceVectorLiteralFunction
	{
		my $func = $_ [0];
		
		while (/\bvec_$func$ws0($nest)/g)
			{
				my $pre = $- [0];
				my $post = $+ [0];
				my $nested = substr ($1, 1, length ($1) - 2);
				if ($nested =~ /(.*),$ws0(\w+)/)
					{
						substr ($_, $pre, $post - $pre) = 'altivec::' . $func . ' <' . $2 . '> (' . $1 . ')';
					}
			}
	}
	
sub replaceVectorSplatImmediate
	{
		my $code = $_ [0];
		my $obj = $_ [1];
		
		while (/\bvec_splat_$code$ws0($nest)/g)
			{
				my $pre = $- [0];
				my $post = $+ [0];
				my $nested = substr ($1, 1, length ($1) - 2);
				substr ($_, $pre, $post - $pre) = $obj . '::fill <' . $nested . '> ()';
			}
	}
	
sub replaceVectorTypeDef
	{
		my $type = $_ [0];
		my $typedef = $_ [1];
		
		if ($typedef)
			{
				s/\b$type (?=>)/$typedef/g;
				s/\b$type/$typedef/g;
			}
	}

print "#include <macstlizer/altivec2mmx.h>\n";
print "using namespace macstl;\n\n";

while (<>)
	{
		replaceFloatVector ($vectorFloat, $vecFloat);
		replaceVector ($vectorSignedInt, $vecInt);
		replaceVector ($vectorUnsignedInt, $vecUnsignedInt);
		replaceVector ($vectorBoolInt, $vecBooleanInt);
		replaceVector ($vectorSignedShort, $vecShort);
		replaceVector ($vectorUnsignedShort, $vecUnsignedShort);
		replaceVector ($vectorBoolShort, $vecBooleanShort);
		replaceVector ($vectorPixel, $vecPixel);
		replaceVector ($vectorSignedChar, $vecSignedChar);
		replaceVector ($vectorUnsignedChar, $vecUnsignedChar);
		replaceVector ($vectorBoolChar, $vecBooleanChar);
		
		replaceVectorFunction ('ld');
		replaceVectorFunction ('lde');
		replaceVectorFunction ('lvsl');
		replaceVectorFunction ('lvsr');
		replaceVectorFunction ('st');
		replaceVectorFunction ('ste');
		replaceVectorFunction ('perm');
		replaceVectorFunction ('sel');
		replaceVectorFunction ('sr');
		replaceVectorFunction ('sra');
		replaceVectorFunction ('srl');
		replaceVectorFunction ('sro');
		replaceVectorFunction ('sl');
		replaceVectorFunction ('sll');
		replaceVectorFunction ('slo');
		replaceVectorFunction ('rl');
		replaceVectorFunction ('mergeh');
		replaceVectorFunction ('mergel');
		replaceVectorFunction ('mtvscr');
		replaceVectorFunction ('pack');
		replaceVectorFunction ('packpx');
		replaceVectorFunction ('packs');
		replaceVectorFunction ('packsu');
		replaceVectorFunction ('unpackh');
		replaceVectorFunction ('unpackl');
		replaceVectorFunction ('abs');
		replaceVectorFunction ('abss');
		replaceVectorFunction ('add');
		replaceVectorFunction ('addc');
		replaceVectorFunction ('adds');
		replaceVectorFunction ('sub');
		replaceVectorFunction ('subc');
		replaceVectorFunction ('subs');
		replaceVectorFunction ('mule');
		replaceVectorFunction ('mulo');
		replaceVectorFunction ('madd');
		replaceVectorFunction ('madds');
		replaceVectorFunction ('mladd');
		replaceVectorFunction ('mradds');
		replaceVectorFunction ('msum');
		replaceVectorFunction ('msums');
		replaceVectorFunction ('sum4s');
		replaceVectorFunction ('sum2s');
		replaceVectorFunction ('sums');
		replaceVectorFunction ('nmsub');
		replaceVectorFunction ('avg');
		replaceVectorFunction ('max');
		replaceVectorFunction ('min');
		replaceVectorFunction ('round');
		replaceVectorFunction ('ceil');
		replaceVectorFunction ('floor');
		replaceVectorFunction ('trunc');
		replaceVectorFunction ('re');
		replaceVectorFunction ('rsqrte');
		replaceVectorFunction ('loge');
		replaceVectorFunction ('expte');
		replaceVectorReservedFunction ('and');
		replaceVectorFunction ('andc');
		replaceVectorReservedFunction ('or');
		replaceVectorFunction ('nor');
		replaceVectorReservedFunction ('xor');
		replaceVectorFunction ('cmpeq');
		replaceVectorFunction ('cmpge');
		replaceVectorFunction ('cmpgt');
		replaceVectorFunction ('cmple');
		replaceVectorFunction ('cmplt');
		replaceVectorFunction ('cmpb');
		replaceVectorFunction ('all_eq');
		replaceVectorFunction ('all_ne');
		replaceVectorFunction ('any_eq');
		replaceVectorFunction ('any_ne');
		replaceVectorFunction ('all_ge');
		replaceVectorFunction ('all_le');
		replaceVectorFunction ('any_ge');
		replaceVectorFunction ('any_le');
		replaceVectorFunction ('all_gt');
		replaceVectorFunction ('all_lt');
		replaceVectorFunction ('any_gt');
		replaceVectorFunction ('any_lt');
		replaceVectorFunction ('all_nan');
		replaceVectorFunction ('all_numeric');
		replaceVectorFunction ('any_nan');
		replaceVectorFunction ('any_numeric');
		replaceVectorFunction ('all_nge');
		replaceVectorFunction ('all_nle');
		replaceVectorFunction ('any_nge');
		replaceVectorFunction ('any_nle');
		replaceVectorFunction ('all_ngt');
		replaceVectorFunction ('all_nlt');
		replaceVectorFunction ('any_ngt');
		replaceVectorFunction ('any_nlt');
		replaceVectorFunction ('all_in');
		replaceVectorFunction ('any_out');
		
		replaceVectorLiteralFunction ('sld');
		replaceVectorLiteralFunction ('splat');
		replaceVectorLiteralFunction ('ctf');
		replaceVectorLiteralFunction ('cts');
		replaceVectorLiteralFunction ('ctu');
		
		replaceVectorSplatImmediate ('s8', 'vec <signed char, 16>');
		replaceVectorSplatImmediate ('s16', 'vec <short, 8>');
		replaceVectorSplatImmediate ('s32', 'vec <int, 4>');
		replaceVectorSplatImmediate ('u8', 'vec <unsigned char, 16>');
		replaceVectorSplatImmediate ('u16', 'vec <unsigned short, 8>');
		replaceVectorSplatImmediate ('u32', 'vec <unsigned int, 4>');
		
		replaceVectorTypeDef ($vecFloat, $vecFloatTypeDef);
		replaceVectorTypeDef ($vecInt, $vecIntTypeDef);
		replaceVectorTypeDef ($vecUnsignedInt, $vecUnsignedIntTypeDef);
		replaceVectorTypeDef ($vecBooleanInt, $vecBooleanIntTypeDef);
		replaceVectorTypeDef ($vecShort, $vecShortTypeDef);
		replaceVectorTypeDef ($vecUnsignedShort, $vecUnsignedShortTypeDef);
		replaceVectorTypeDef ($vecBooleanShort, $vecBooleanShortTypeDef);
		replaceVectorTypeDef ($vecPixel, $vecPixelTypeDef);
		replaceVectorTypeDef ($vecSignedChar, $vecSignedCharTypeDef);
		replaceVectorTypeDef ($vecUnsignedChar, $vecUnsignedCharTypeDef);
		replaceVectorTypeDef ($vecBooleanChar, $vecBooleanCharTypeDef);

		print "$_";
	}