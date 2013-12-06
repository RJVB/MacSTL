/*
 *  machtest.cpp
 *  macstl
 *
 *  Created by Glen Low on Jan 24 2005.
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


#include <time.h>
#include <cstdlib>
#include <iostream>
#include <macstl/mach.h>

static const int tries = 1000;
static const int factor = 1000000;

template <typename V1, typename V2> bool check (const V1& v1, const V2& v2)
	{
		if (v1.size () == v2.size () && std::equal (v1.begin (), v1.end (), v2.begin ()))
			{
				std::cout << "OK.\n";
				return true;
			}
		else
			{
				if (v1.size () != v2.size ())
					std::cout << "sizes differ: " << v1.size () << " != " << v2.size () << ".\n";
				else
					{
						std::pair <typename V1::const_iterator, typename V2::const_iterator> where =
							std::mismatch (v1.begin (), v1.end (), v2.begin ());
							
						std::cout << "elements differ: [" << (where.first - v1.begin ()) << "] == " << *where.first <<
							" != [" << (where.second - v2.begin ()) << "] == " << *where.second << ".\n";
					}
				return false;
			}
	}
	
int main ()
	{
		std::cout << "Constructing -- ";
		
		{
		std::vector <int> v1;
		std::vector <int, macstl::mach_allocator <int> > v2;
		
		for (int i = 0; check (v1, v2) && i != tries; ++i)
			{
			
				switch (random () % 8)
					{
						case 0:
							{
							int insert_size = random () % factor;
							int* insertion = (int*) std::malloc (sizeof (int) * insert_size);
							for (int i = 0; i != insert_size; ++i)
								insertion [i] = random ();
							
						//	int insert_pos = random () % (v1.size () + 1);
							int insert_pos = v1.size ();
							
							std::cout << "Inserting range of " << insert_size << " values at position " << insert_pos << " -- "; std::cout.flush ();
							
							v1.insert (v1.begin () + insert_pos, insertion, insertion + insert_size);
							v2.insert (v2.begin () + insert_pos, insertion, insertion + insert_size);
							
							std::free (insertion);
							}
							break;
						
						case 1:
							{
							int fill_size = random () % factor;
							int filler = random ();
							
							int fill_pos = random () % (v1.size () + 1);
							
							std::cout << "Inserting fill of " << fill_size << " values at position " << fill_pos << " -- ";
							
							v1.insert (v1.begin () + fill_pos, fill_size, filler);
							v2.insert (v2.begin () + fill_pos, fill_size, filler);
							}
							break;

						case 2:
							{
							int one = random ();
							
							int one_pos = random () % (v1.size () + 1);
							
							
							
							std::cout << "Inserting one at position " << one_pos << " -- "; std::cout.flush ();
							
							std::vector <int>::iterator it1 = v1.insert (v1.begin () + one_pos, one);
							std::vector <int, macstl::mach_allocator <int> >::iterator it2 = v2.insert (v2.begin () + one_pos, one);
							if (it1 - v1.begin () != it2 - v2.begin ()) std::cout << "Iterators differ.\n";
							}
							break;
							
						case 3:
							{
							int push = random ();
							
							std::cout << "Pushing back -- "; std::cout.flush ();
							
							v1.push_back (push);
							v2.push_back (push);
							}
							break;
							
						case 4:
							{
							int erase1 = random () % (v1.size () + 1);
							int erase2 = random () % (v1.size () + 1);
							
							int erase_first = std::min (erase1, erase2);
							int erase_last = std::max (erase1, erase2);
							
							std::cout << "Erasing from " << erase_first << " to " << erase_last << " -- "; std::cout.flush ();
							
							int pos1 = v1.erase (v1.begin () + erase_first, v1.begin () + erase_last) - v1.begin ();
							int pos2 = v2.erase (v2.begin () + erase_first, v2.begin () + erase_last) - v2.begin ();
							if (pos1 != pos2) std::cout << "Iterators differ.\n";
							}
							break;
							
						case 5:
							if (v1.size () > 0)
								{
									int erase = random () % v1.size ();
									
									std::cout << "Erasing " << erase << " -- "; std::cout.flush ();
									
									int pos1 = v1.erase (v1.begin () + erase) - v1.begin ();
									int pos2 = v2.erase (v2.begin () + erase) - v2.begin ();
									if (pos1 != pos2) std::cout << "Iterators differ.\n";
								}
							else
								std::cout << "Skip Erasing -- ";
							
							break;

						case 6:
							{
							std::cout << "Clearing -- "; std::cout.flush ();
							
							v1.clear ();
							v2.clear ();
							}
							break;

						case 7:
							if (v1.size () > 0)
								{
									std::cout << "Popping back -- "; std::cout.flush ();
											
									v1.pop_back ();
									v2.pop_back ();
									
								}
							else
								std::cout << "Skip Popping Back -- ";
								
							break;
					
					}
			
			}
		}
		
		std::cout << "---\n";
		{
			int x = random ();
			std::vector <int> v1 (factor, x);
			std::vector <int, macstl::mach_allocator <int> > v2 (factor, x);

			clock_t a = clock ();
			for (int i = 0; i != tries; ++i)
				{
					std::vector <int> v1a = v1;
				}
			clock_t b = clock ();
			for (int i = 0; i != tries; ++i)
				{
					std::vector <int, macstl::mach_allocator <int> > v2a = v2;
				}
			clock_t c = clock ();
			
			std::cout << "Regular vector copy took " << (b - a) << " ticks.\n";
			std::cout << "Mach vector copy took " << (c- b) << " ticks.\n";
		
		
		}
		
		std::cout << "---\n";

		{
			int x = random ();
			std::vector <int> v1;
			std::vector <int, macstl::mach_allocator <int> > v2;

			clock_t a = clock ();
			for (int i = 0; i != tries * 10; ++i)
				{
					v1.insert (v1.end (), factor / tries, x);
				}
			clock_t b = clock ();
			for (int i = 0; i != tries * 10; ++i)
				{
					v2.insert (v2.end (), factor / tries, x);
				}
			clock_t c = clock ();
			
			std::cout << "Regular vector insert took " << (b - a) << " ticks.\n";
			std::cout << "Mach vector insert took " << (c- b) << " ticks.\n";
		
		
		}


	}