#!/bin/sh

tar xvf /Users/Foxman/CIOS/Development/ZOS/Requires/GMP/gmp-5.1.3.tar.bz2

cd gmp-5.1.3

export IOS=/Developer/Platforms/iPhoneOS.platform/Developer
#export IROOT=/Developer/Platforms/iPhoneOS.platform/Developer/SDKs/iPhoneOS5.0.sdk
export IROOT=/Applications/Xcode.app/Contents/Developer/Platforms/iPhoneOS.platform/Developer/SDKs/iPhoneOS7.0.sdk

./configure \
CC="$IOS/usr/llvm-gcc-4.2/bin/llvm-gcc-4.2" \
CXX="$IOS/usr/llvm-gcc-4.2/bin/llvm-g++-4.2" \
CPP="$IOS/usr/llvm-gcc-4.2/bin/llvm-gcc-4.2 -E" \
LD="$IOS/usr/bin/ld" \
CPPFLAGS="-arch armv7 -isysroot $IROOT -miphoneos-version-min=4.2" \
AR="$IOS/usr/bin/ar" \
NM="$IOS/usr/bin/nm" \
NMEDIT="$IOS/usr/bin/nmedit" \
LIBTOOL="$IOS/usr/bin/libtool" \
LIPO="$IOS/usr/bin/lipo" \
OTOOL="$IOS/usr/bin/otool" \
RANLIB="$IOS/usr/bin/ranlib" \
STRIP="$IOS/usr/bin/strip" \
--disable-shared \
--enable-static \
--prefix=$IOS/usr/local \
--host=none-apple-darwin10

make

cp -f libgmp.la ~/CIOS/Development/ZOS/lib/iPhone/ARMv7
cd .libs
cp -f libgmp.a ~/CIOS/Development/ZOS/lib/iPhone/ARMv7
cp -f libgmp.lai ~/CIOS/Development/ZOS/lib/iPhone/ARMv7
