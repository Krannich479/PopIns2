#!/usr/bin/env bash

set -xe

BIN_FOLDER=$(mktemp -d)
PATH=$BIN_FOLDER:$PATH
NPROC=$(nproc)
ARCH=$(echo $(uname -m) | tr '_' '-')

# Bifrost
git clone https://github.com/pmelsted/bifrost.git
pushd bifrost
# reset to commit prior to new color format
git checkout 9e6f948ce2c27de32bc687502e777aebc9eab53d
mkdir build && cd build
cmake .. -DMAX_KMER_SIZE=64
sed -i 's/MAX_KMER_SIZE \"32\" CACHE/MAX_KMER_SIZE \"64\" CACHE/g' ../CMakeLists.txt
make -j$NPROC
sudo make install
file /usr/local/bin/Bifrost | grep $ARCH
popd

# Bwa
git clone --recursive https://github.com/lh3/bwa.git
pushd bwa
make -j$NPROC
cp bwa $BIN_FOLDER/
file $BIN_FOLDER/bwa | grep $ARCH
popd

# Samtools
## Htslib
git clone --recursive https://github.com/samtools/htslib.git
pushd htslib
autoreconf -i
./configure
make -j$NPROC
popd

## Samtools
git clone --recursive https://github.com/samtools/samtools.git
pushd samtools
make -j$NPROC
cp samtools $BIN_FOLDER/
file $BIN_FOLDER/samtools | grep $ARCH
popd

# Sickle
git clone --recursive https://github.com/najoshi/sickle.git
pushd sickle
make -j$NPROC
cp sickle $BIN_FOLDER/
file $BIN_FOLDER/sickle | grep $ARCH
popd

# PopIns2
git config --global --add safe.directory .
mkdir -p build
make -j$NPROC
file popins2 | grep $ARCH
