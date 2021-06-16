#!/bin/sh
# one step compilation for Android ARMv7
# GMP is required

export ZOS=/home/CIOS/Development/ZOS
export ARX=ARMv7
export TKX=/home/Builds/androidsys
export ACC=arm-linux-androideabi

tar xvf $ZOS/Requires/MPFR/mpfr-3.1.2.tar.xz

cd mpfr-3.1.2

export CC="$TKX/bin/arm-linux-androideabi-gcc"
export CXX="$TKX/bin/arm-linux-androideabi-g++"
export CPP="$TKX/bin/arm-linux-androideabi-cpp"
export AR="$TKX/bin/arm-linux-androideabi-ar"
export RANLIB="$TKX/bin/arm-linux-androideabi-ranlib"
export LD="$TKX/bin/arm-linux-androideabi-ld"
export NM="$TKX/bin/arm-linux-androideabi-nm"
export STRIP="$TKX/bin/arm-linux-androideabi-strip"
export SYSROOT="$TKX/sysroot"
export PATH="$TKX/bin":$PATH

./configure \
--with-gmp=/home/Builds/androidsys/sysroot/usr \
--disable-shared \
--enable-static \
--host=$ACC \
--prefix=/home/Builds/MPFR

cd ..
patch -p0 < $ZOS/Requires/MPFR/mpfr-3.1.2-android.patch
cd mpfr-3.1.2

make
make install

cd src
cp -f *.h $ZOS/include/Android/$ARX/mpfr
cp -f libmpfr.la $ZOS/lib/Android/$ARX
cd .libs
cp -f libmpfr.a $ZOS/lib/Android/$ARX
cp -f libmpfr.lai $ZOS/lib/Android/$ARX
