#!/bin/sh
# one step compilation for linux 32

export ZOS=/home/CIOS/Development/ZOS
export ARX=x86

tar xvf $ZOS/Requires/MPFR/mpfr-3.1.2.tar.xz

cd mpfr-3.1.2

./configure \
--disable-shared \
--enable-static

make

cd src
cp -f *.h $ZOS/include/Linux/$ARX/mpfr
cp -f libmpfr.la $ZOS/lib/Linux/$ARX/shared
cd .libs
cp -f libmpfr.a $ZOS/lib/Linux/$ARX/shared
cp -f libmpfr.lai $ZOS/lib/Linux/$ARX/shared
