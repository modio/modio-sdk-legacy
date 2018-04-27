This project contains the minimal setup required to add the mod.io functionality to your game using the MinGW compiler on Windows. The `Makefile` in this directory shows how to include the mod.io headers and link the `libmodio.dll.a` library. The `libmodio.dll.a` is not present by default, we recomend you to grab it from our [releases page](https://github.com/DBolical/modioSDK/releases) and adjust the `MODIO_LIB_DIR` on the `Makefile` but you can also build it yourself by [following our guide](https://github.com/DBolical/modioSDK/wiki/Building).

# Setting up your compiler

Before you start, please do the following to setup the MinGW compiler on your system:

1. Install the MinGW compiler provided by the [MinGW Installer](https://sourceforge.net/projects/mingw/files/)
2. Download the ´mingw32-gcc-c++´ package
3. Add your MinGW binary folder to the path environment variable. By default it's `C:\MinGW\bin`.

# Compile and run your project

Open a terminal, go to this project directory and run the `Makefile` by using the `mingw32-make` command:

```bash
> mingw32-make
```

The `MyProject.exe` binary should be generated, now add the `libmodio.dll` next to it and execute by typing:

```bash
> MyProject.exe
```

You can find a detailed explanation on how to setup mod.io in the [Getting Started](https://github.com/DBolical/modioSDK/wiki/Getting-Started) guide. Once you finished setting up mod.io on your project you can complete your integration by following our [documentation](https://github.com/DBolical/modioSDK/wiki).
