#!/bin/sh
# one step compilation for iPhone ARMv7
# GMP is required

export ZOS=/Users/Foxman/CIOS/Development/ZOS
export ARX=ARMv7
export IOS=/Developer/Platforms/iPhoneOS.platform/Developer
export IROOT=/Applications/Xcode.app/Contents/Developer/Platforms/iPhoneOS.platform/Developer/SDKs/iPhoneOS7.0.sdk

tar xvf $ZOS/Requires/MPFR/mpfr-3.1.2.tar.xz

cd mpfr-3.1.2

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
--with-gmp=/Users/Foxman/Temp/gmp \
--disable-shared \
--enable-static \
--prefix=$IOS/usr/local \
--host=none-apple-darwin10

make

cd src
cp -f *.h $ZOS/include/iPhone/$ARX/mpfr
cp -f libmpfr.la $ZOS/lib/iPhone/$ARX
cd .libs
cp -f libmpfr.a $ZOS/lib/iPhone/$ARX
cp -f libmpfr.lai $ZOS/lib/iPhone/$ARX
