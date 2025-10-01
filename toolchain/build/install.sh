#!/bin/sh

set -e

if [ "$(id -u)" -ne 0 ]; then
    echo "Error: you must be root!"
    exit 1
fi

BINUTILS_TAR_FILENAME=binutils-2.40
GCC_TAR_FILENAME=gcc-13.2.0

TARGET=i386-elf
PREFIX=/opt/i386-elf

# binutils
#curl -O https://ftp.gnu.org/gnu/binutils/binutils-2.34.tar.gz
tar xf "$BINUTILS_TAR_FILENAME.tar.gz"
mkdir "$BINUTILS_TAR_FILENAME-build"
cd "$BINUTILS_TAR_FILENAME-build"
../$BINUTILS_TAR_FILENAME/configure --target=$TARGET --prefix=$PREFIX --enable-interwork --enable-multilib --disable-nls --disable-werror
make -j 4 all
make install
cd ..

# gcc
#curl -O https://ftp.gnu.org/gnu/gcc/gcc-9.2.0/gcc-9.2.0.tar.gz
tar xf "$GCC_TAR_FILENAME.tar.gz"
cd "$GCC_TAR_FILENAME"
./contrib/download_prerequisites
cd ..
mkdir "$GCC_TAR_FILENAME-build"
cd "$GCC_TAR_FILENAME-build"
../$GCC_TAR_FILENAME/configure --target=$TARGET --prefix=$PREFIX --disable-nls --enable-languages=c --enable-interword --enable-multilib
make -j 4 all-gcc
make -j 4 all-target-libgcc
make install-gcc
make install-target-libgcc

echo "export PATH=\$PATH:$PREFIX/bin" >> ~/.bashrc

echo "Success!"
