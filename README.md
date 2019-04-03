# Chinese SM2 crypto for RISC-V

Author: μNEST dev team, http://iotee.io

Take the following steps to cross-compile it for RISC-V platform. The cross-compiling platform is Ubuntu 16.04/18.04 x64.

## Install RISC-V GNU toolchain

Install the toolchain to ~/opt/riscv.

```
sudo apt-get install -y autoconf automake autotools-dev curl libmpc-dev libmpfr-dev \
	libgmp-dev libusb-1.0-0-dev gawk build-essential bison flex texinfo gperf libtool \
	patchutils bc zlib1g-dev device-tree-compiler pkg-config libexpat-dev
cd ~ && git clone --recursive https://github.com/riscv/riscv-tools
export RISCV=~/opt/riscv
cd ~/riscv-tools && ./build.sh

export PATH=~/opt/riscv/bin:$PATH
```

## Cross-compiling the test program for RISC-V

```
cd ~ && git clone --recursive https://github.com/NESTchain/risc-v-sm2
export CC=riscv64-unknown-elf-gcc
cd ~/risc-v-sm2
make
```

## Run the SM2 test program in RISC-V emulator

```
spike pk ~/risc-v-sm2/test/sm2_internal_test
```



## Note

This repo is based on OpenSSL 1.1.1b and we comment out some platform-dependent code to compile it for RISC-V.

Modified files:

```
	crypto/LPdir_unix.c
	crypto/uid.c
```

Makefile is generated with the following configuration command and slightly edited:

```
./Configure no-threads no-asm no-shared no-dso no-afalgeng -DOPENSSL_NO_SOCK=1 \
	-DOPENSSL_NO_DGRAM=1  -DOPENSSL_NO_UI_CONSOLE=1 -DNO_SYSLOG=1 linux-elf
```

