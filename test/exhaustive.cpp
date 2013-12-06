/*
 *  exhaustive.cpp
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

#include <iostream>
#include <iomanip>
#include <macstl/vec.h>
#include "common.h"

#ifndef OPERATION
#define OPERATION stdext::reciprocal_square_root
#endif

// make 16-byte vec the default since TYPE cannot contain any commas...
namespace macstl
	{
		template <typename T, size_t n = 16 / sizeof (T)> class vec;
	}
	
#ifndef TYPE
#define TYPE macstl::vec <float>
#endif

#define NAME(X) NAMIFY(X)
#define NAMIFY(X) #X

const unsigned int checkpoint = 10000000;

int main (int, const char *)
	{
		using namespace macstl;
		
		std::cout << "Testing " << NAME(OPERATION) << " with " << NAME(TYPE) << ".\n\n";
		
		// use more accurate Java mode for testing
#ifdef USE_ALTIVEC_H
		altivec::mtvscr (vec <unsigned char, 16>::fill <0> ());
#endif

		unsigned long long count = 0;
		unsigned int threshold = 0;
		while (threshold != max_difference)
			{
				test <OPERATION, TYPE> (NAME(OPERATION), threshold);
				if (++count % checkpoint == 0)
					std::cout << "Tested " << count << ".\n";
			}
	}

