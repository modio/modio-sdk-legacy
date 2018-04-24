This directory contains the mod.io dependencies needed to build mod.io for Windows. If you want to integrate mod.io into your game please refer to the [mod.io SDK overview](https://github.com/DBolical/modioSDK/wiki), you don't need to build mod.io in order to use it on your game you can use our [binary release](https://github.com/DBolical/modioSDK/releases) instead.

mod.io uses Curl and Zlib as external libraries. Both are present on Mac OS by default and can be downloaded from the most common repositories on [Linux](https://github.com/DBolical/modioSDK/wiki/Building#linux). We ship Windows version of both libraries under this directory so you can build mod.io right away using our [Building guide](https://github.com/DBolical/modioSDK/wiki/Building#linux). The following is a guide to build Curl and Zlib from source using both VisualC++ and MinGW compilers.

# Zlib

Before you start, please download the source at the official [Zlib website](http://zlib.net/).

## NMake

By default, Zlib will be compiled on `debug` mode, usually you will want to compile it on `release` mode so you don't get some warnings every time you use it later on. To do so, edit the `min32/Makefile.msc` file by replacing the `-debug` flag with `-release` and remove all the `-Zi` flags. Once you hace done this you will be ready for building.

In order to compile the NMake version we need to execute the `Makefile.msc` under the `win32` directory:

```bash
$ nmake /f win32/Makefile.msc
```

This will generate the `zlib.lib` file. It will be compatible with x86 or x64 depending on the Microsoft native compiler you used. 

## MingGW

MinGW does not need extra setup, just execute the `Makefile.gcc` under the `win32` directory.

```bash
$ mingw32-make.exe -fwin32/Makefile.gcc
```

This will generate the `libz.a` file ready to be statically linked.

# Curl

Before you start, please download the source at the official [Curl website](https://curl.haxx.se/download.html).

## NMake

In addition to running the commands in the correspoinding x86 or x64 version of the Microsoft native compiler, you have to explicitly setup the target machine.

```bash
# For x86
$ nmake /f makefile.vc ENABLE_WINSSL=yes mode=static MACHINE=x86 VC=17
```

```bash
# For x64
$ nmake /f makefile.vc ENABLE_WINSSL=yes mode=static MACHINE=x64 VC=17
```

This will generate the `libcurl_a.lib` file ready to be statically linked.

## MinGW

```bash
$ mingw32-make mingw32
```

This will generate the `libcurl.a` file ready to be statically linked. Curl will depend on the following libraries: `libcrypto`, `libeay` and `libssl`. They should be part of the MinGW default lib directory. In case they are not present, you can grab them from the `MinGW/` directory.

### Building MinGW dependencies

```bash
$ perl Configure mingw --prefix=/c/openssl
$ make depend
$ make
```
