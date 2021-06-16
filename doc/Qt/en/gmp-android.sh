#!/bin/sh

tar xvf /home/CIOS/Development/ZOS/Requires/GMP/gmp-5.1.3.tar.bz2

cd gmp-5.1.3

export TKX=/home/Builds/androidsys
export ACC=arm-linux-androideabi

export CC="$TKX/bin/arm-linux-androideabi-gcc --sysroot=$TKX/sysroot"
export CXX="$TKX/bin/arm-linux-androideabi-g++ --sysroot=$TKX/sysroot"
export AR="$TKX/bin/arm-linux-androideabi-ar"
export RANLIB="$TKX/bin/arm-linux-androideabi-ranlib"
export SYSROOT="$TKX/sysroot"
export PATH="$TKX/bin":$PATH

./configure \
--host=$ACC \
--disable-shared \
--enable-static \
--prefix=/home/Builds/GMP

make
make install

cp -f libgmp.la /home/CIOS/Development/ZOS/lib/Android/ARMv7
cd .libs
cp -f libgmp.a /home/CIOS/Development/ZOS/lib/Android/ARMv7
cp -f libgmp.lai /home/CIOS/Development/ZOS/lib/Android/ARMv7
