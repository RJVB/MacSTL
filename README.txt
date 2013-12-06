MacSTL

Welcome to macstl, the C++ header library designed to bring the world of generic programming to the Macintosh, and deliver the surprising speed of SIMD in an intuitive cross-platform package. 

This is a spin-off of MacSTL 0.3.1 as still available on www.pixelglow.com, corrected to build on recent MSVC versions, and to have support for AVX on Intel x86.
My modifications are © 2013 René J.V. Bertin

Where is Everything?

The library files are in the directory macstl. Each header in that directory is public; each header in the subdirectory impl is private.
A comprehensive benchmark and test suite is in the directory test.
The directory macstlizer contains headers and scripts to ease converting from Altivec to SSE code.
Build files for Mac OS X are in directory mac, build files for Windows are in directory win and build files for Linux and Cygwin are in directory unix.

How to Build

Out of the box, you can build several suites in Apple Xcode 1.5-2.1, Metrowerks CodeWarrior 9.x (Mac OS X), Microsoft Visual Studio .NET 2003 (Windows) or FSF gcc 3.4/4.0 (Linux and Cygwin). These will build into the build subdirectory of mac, win, or unix, and make command-line programs suitable for that platform.
Simply open in the respective IDE and do a complete build. The Xcode project builds “Optimized for G5” by default; select the “Optimized for G4” build style to build for G4, or “Optimized for PowerPC and Intel” build style to build an Universal Binary. The Visual Studio solution builds for P4 by default; adjust the options appropriately for other Intel CPUs. The Unix makefiles build for Linux PPC/x86 or Cygwin automatically.
You can install macstl for your own programs by pointing the -I option of your compiler to the outermost macstl directory. Alternatively, you may use Xcode to build a header-only framework called macstl.framework, and in your projects use Add to Project... .

Licensing

macstl is dual licensed under the open-source Reciprocal Public License (RPL) and the proprietary Pixelglow Source License (PSL). The text of both licenses are available in the macstl directory.
The way it works is this: you either reciprocate your own code, or pay the license fee. While it is an open-source license, the RPL prohibits you from keeping your derivations proprietary even if you only deploy them in-house. On the other hand, paying the license fee also entitles you to priority support, version control access and free upgrades for differing periods.

Useful Links

Main site:	http://www.pixelglow.com/macstl/
Documentation:	http://www.pixelglow.com/macstl/reference/
Purchase:	http://www.pixelglow.com/macstl/purchase/
Mailing list:	http://www.pixelglow.com/lists/listinfo/macstl-dev/

Thank you for evaluating macstl and I do hope it boosts your development and program performance!

Cheers, Glen Low
pixelglow software | simply brilliant stuff
www.pixelglow.com
