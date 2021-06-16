#!/bin/sh
# one step compilation for mac os x clang 64

export ZOS=/Users/Foxman/CIOS/Development/ZOS
export ARX=x64

tar xvf $ZOS/Requires/GMP/gmp-5.1.3.tar.bz2

cd gmp-5.1.3

./configure \
--disable-shared \
--enable-static

make

cp -f config.h $ZOS/include/MacOSX/$ARX/gmp
cp -f gmp.h $ZOS/include/MacOSX/$ARX/gmp
cp -f gmp-impl.h $ZOS/include/MacOSX/$ARX/gmp
cp -f gmp-mparam.h $ZOS/include/MacOSX/$ARX/gmp
cp -f gmpxx.h $ZOS/include/MacOSX/$ARX/gmp
cp -f longlong.h $ZOS/include/MacOSX/$ARX/gmp
cp -f libgmp.la $ZOS/lib/MacOSX/$ARX
cd .libs
cp -f libgmp.a $ZOS/lib/MacOSX/$ARX
cp -f libgmp.lai $ZOS/lib/MacOSX/$ARX
