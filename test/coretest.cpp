/*
 *  coretest.cpp
 *  macstl
 *
 *  Created by Glen Low on Jan 22 2005.
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

#include <iostream>
#include <macstl/core.h>
#include <macstl/refptr.h>

using namespace macstl;
using namespace std;

struct dumper
	{
		template <typename T> void operator() (const T& t)
			{
				cout << " " << t;
			}
	};

class T
	{
		public:
			T (): i_ ()
				{
					++count;
				}
				
			T (int i): i_ (i)
				{
					++count;
				}
				
			T (const T& t): i_ (t.i_)
				{
					++count;
				}
				
			~T ()
				{
					--count;
				}
				
			operator int () const
				{
					return i_;
				}
				
			static int count;
			
		private:
			int i_;
	};

int T::count = 0;
	
template <typename Cont> void dump (const Cont& c)
	{
		cout << "Forwards:";
		for_each (c.begin (), c.end (), dumper ());
		cout << ".\nBackwards:";
		for_each (c.rbegin (), c.rend (), dumper ());
		cout << ".\nSize is " << c.size ();
		cout << "\nEmpty is " << c.empty ();
		if (!c.empty ())
			{
				cout << "\nFront is " << c.front ();
				cout << "\nBack is " << c.back ();
			}
		
		cout << "\nBounds unchecked:";
		for (int i = 0; i != c.size (); ++i)
			cout << "\nElement #" << i << " is " << c [i] << ".";
		
		cout << "\nBounds checked:";
		for (int i = -5; i != c.size () + 5; ++i)
			{
				try
					{
						cout << "\nElement #" << i << " is " << c.at (i) << ".";
					}
				catch (const out_of_range& err)
					{
						cout << "out of range.";
					}
			}
		cout << "\nCFShow:\n";
		cout.flush ();
		CFShow (c.data ());
		cout << "References: " << T::count << "\n";
		cout << "---\n";
	}



int main ()
	{
		{
			int ai [] = {2, 3, 4, 5, 6, 7, 5, 9};
			
			cout << "Constructing with 8 elements.\n";
			core_array <T> ca (ai, ai + 8);		// works the same as core_array <int>, we just want to check refcounts...
			dump (ca);
			
			cout << "Changing the value at index 0.\n";
			ca [0] = 5;
			dump (ca);
			
			cout << "Inserting one value at index 1.\n";
			ca.insert (ca.begin () + 1, 10);
			dump (ca);

			cout << "Inserting 5 values at index 2.\n";
			ca.insert (ca.begin () + 2, 5, 20);
			dump (ca);

			cout << "Inserting a range of 8 values at index 3.\n";
			ca.insert (ca.begin () + 3, ai, ai + 8);
			dump (ca);

			cout << "Push back a value.\n";
			ca.push_back (30);
			dump (ca);
			
			cout << "Erase a value at index 4.\n";
			ca.erase (ca.begin () + 4);
			dump (ca);
			
			cout << "Erase a range of 5 values at index 5.\n";
			ca.erase (ca.begin () + 5, ca.begin () + 10);
			dump (ca);
			
			cout << "Pop back a value.\n";
			ca.pop_back ();
			dump (ca);
			
			cout << "Sorting the array.\n";
			sort (ca.begin (), ca.end ());
			dump (ca);

			cout << "Reverse sorting the array.\n";
			sort (ca.begin (), ca.end (), greater <int> ());
			dump (ca);
			
			cout << "Making a new reference to the array.\n";
			refptr <core_array <T> > ref (&ca);
			dump (*ref);
			cout << "Clear.\n";
			ca.clear ();
			dump (ca);
		}
		// this result should be zero, which proves that all that retaining and releasing counting worked OK...
		cout << "At the end of the day, we are at " << T::count << "!";
	}

