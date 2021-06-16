#!/bin/sh
# one step compilation for mac os x clang 64

export ZOS=/Users/Foxman/CIOS/Development/ZOS
export ARX=x64

tar xvf $ZOS/Requires/MPFR/mpfr-3.1.2.tar.xz

cd mpfr-3.1.2

./configure \
--with-gmp=/usr/local \
--disable-shared \
--enable-static

make

cd src
cp -f *.h $ZOS/include/MacOSX/$ARX/mpfr
cp -f libmpfr.la $ZOS/lib/MacOSX/$ARX
cd .libs
cp -f libmpfr.a $ZOS/lib/MacOSX/$ARX
cp -f libmpfr.lai $ZOS/lib/MacOSX/$ARX
