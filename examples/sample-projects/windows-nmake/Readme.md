This project contains the minimal setup required to add the mod.io functionality to your game using the Visual Studio's NMake compiler on Windows. The `Makefile` in this directory shows how to include the mod.io headers and link the `modio.lib` library. The `modio.lib` is not present by default, we recomend you to grab it from our [releases page](https://github.com/DBolical/modioSDK/releases) and adjust the `MODIO_LIB_DIR` on the `Makefile` but you can also build it yourself by [following our guide](https://github.com/DBolical/modioSDK/wiki/Building).

# Setting up your compiler

Before you start, please do the following to setup the NMake on your system:

1. Install the [Visual Studio Installer](https://www.visualstudio.com/downloads/?utm_source=mscom&utm_campaign=msdocs).
2. Download the recommended `Desktop development with C++` packages.
3. Run the `x64 Native Tools Command Prompt for VS 2017` program from the start menu.

# Compile and run your project

Open a terminal, go to this project directory and run the `Makefile` by using the `nmake` command:

```bash
> nmake
```

The `main.exe` binary should be generated, now add the `modio.dll` next to it and execute by typing:

```bash
> main.exe
```

You can find a detailed explanation on how to setup mod.io in the [Getting Started](https://github.com/DBolical/modioSDK/wiki/Getting-Started) guide. Once you finished setting up mod.io on your project you can complete your integration by following our [documentation](https://github.com/DBolical/modioSDK/wiki).
