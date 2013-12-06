/*
 *  comtest.cpp
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
#include <macstl/com.h>

using namespace macstl;

// Some COM interface
struct IOne: public IUnknown
	{
		virtual void Say () = 0;		
	};
	
// Some other COM interface
struct ITwo: public IUnknown
	{
		virtual void Talk () = 0;
	};
	
// Yet another COM interface
struct IThree: public ITwo
	{
		virtual void Speak () = 0;
	};
	
// Define the UUIDs for the interfaces...
template <> const REFIID uuid_of <IOne>::value = {0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0xC0U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x47U};
template <> const REFIID uuid_of <ITwo>::value = {0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0xC0U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x48U};
template <> const REFIID uuid_of <IThree>::value = {0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0xC0U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x49U};

// COM type that implements above interfaces -- note no IUnknown handling visible here!
struct COneTwoThree: public com_type <typelist <IOne, ITwo, IThree> >
	{
		virtual ~COneTwoThree ()	{ std::cout << "bye.\n"; }
		virtual void Say ()			{ std::cout << "say.\n"; }
		virtual void Talk ()		{ std::cout << "talk.\n"; }
		virtual void Speak ()		{ std::cout << "speak.\n"; }
	};

int main ()
	{
		// let's do the COM pointer management manually
		{
			IUnknown* c123;
			(new COneTwoThree ())->QueryInterface (uuid_of <IUnknown>::value, (void**) &c123);
			
			IOne* one;
			c123->QueryInterface (uuid_of <IOne>::value, (void**) &one);
			one->Say ();
			
			ITwo* two;
			c123->QueryInterface (uuid_of <ITwo>::value, (void**) &two);
			two->Talk ();
			
			IThree* three;
			c123->QueryInterface (uuid_of <IThree>::value, (void**) &three);
			three->Talk ();
			three->Speak ();
			
			one->Release ();	// balances the QI for IOne
			two->Release ();	// balances the QI for ITwo
			three->Release ();	// balances the QI for IThree

			c123->Release ();	// balances the QI for IUnknown
			c123->Release ();	// balances the new -- destructor called here
		}
		
		// let's do the COM pointer management automatically, see how easy it is!
		{
			com_ptr <COneTwoThree> c123 (new COneTwoThree ());
			c123->Release ();	// only need to do this to balance the new, rest now on autopilot...
		
			com_ptr <IOne> one = c123;
			one->Say ();
			
			com_ptr <ITwo> two = c123;
			two->Talk ();
			
			com_ptr <IThree> three = c123;
			three->Talk ();
			three->Speak ();
			
			// destructor called here, automatically!
		}
	
		return 0;
	}

