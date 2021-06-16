#!/bin/sh
# one step compilation for linux 64

export ZOS=/home/CIOS/Development/ZOS
export ARX=x64

tar xvf $ZOS/Requires/GMP/gmp-5.1.3.tar.bz2

cd gmp-5.1.3

./configure \
--disable-shared \
--enable-static

make

cp -f config.h $ZOS/include/Linux/$ARX/gmp
cp -f gmp.h $ZOS/include/Linux/$ARX/gmp
cp -f gmp-impl.h $ZOS/include/Linux/$ARX/gmp
cp -f gmp-mparam.h $ZOS/include/Linux/$ARX/gmp
cp -f gmpxx.h $ZOS/include/Linux/$ARX/gmp
cp -f longlong.h $ZOS/include/Linux/$ARX/gmp
cp -f libgmp.la $ZOS/lib/Linux/$ARX/shared
cd .libs
cp -f libgmp.a $ZOS/lib/Linux/$ARX/shared
cp -f libgmp.lai $ZOS/lib/Linux/$ARX/shared
