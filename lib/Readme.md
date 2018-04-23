# Zlib

## NMake

### Seting up for building release

By default, Zlib will be compiled on `debug` mode, usually you will want to compile it on `release` mode so you don't get some warnings every time you use it later on. To do so, edit the `min32/Makefile.msc` file by replacing the `-debug` flat with `-release` and remove al the `-Zi` flags. Once you hace done this you will be ready for building.

### Building

In order to compile NMake we need to execute the `Makefile.msc` under the `win32` directory.

```bash
nmake /f win32/Makefile.msc
```

This will generate the `zlib.lib` file. It will be compatible with x86 or x64 depending on the Microsoft native compiler you used. 

## MingGW

MinGW does not need extra setup, just execute the `Makefile.gcc` under the `win32` directory.

```bash
mingw32-make.exe -fwin32/Makefile.gcc
```

This will generate the `libz.a` file.

# Curl

## NMake

In addition to running the commands in the correspoinding x86 or x64 version of the Microsoft native compiler, you have to setup the target machine.

```bash
# For x86
nmake /f makefile.vc ENABLE_WINSSL=yes mode=static MACHINE=x86 VC=17
```

```bash
# For x64
nmake /f makefile.vc ENABLE_WINSSL=yes mode=static MACHINE=x64 VC=17
```

This will generate the `libcurl_a.lib` file.

## MinGW

```bash
mingw32-make mingw32
```

This will generate the `libcurl.a` file. Curl will depend on the following libraries: `libcrypto`, `libeay` and `libssl`. They should be part of the MinGW default lib directory. In case they are not present, you can grab them from the `MinGW/` directory.
