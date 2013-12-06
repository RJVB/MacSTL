// some typedefs that depend on the architecture address size

#ifndef _64TYPEDEFS_H

#if defined(_LP64) || defined(x86_64)
	typedef int int32;
	typedef unsigned int uint32;
	typedef unsigned long uint64;
	typedef short int16;
	typedef unsigned short uint16;
	typedef unsigned char uint8;
#else
	typedef long int32;
	typedef unsigned long uint32;
	typedef unsigned long long uint64;
	typedef short int16;
	typedef unsigned short uint16;
	typedef unsigned char uint8;
#endif

#define _64TYPEDEFS_H
#endif
