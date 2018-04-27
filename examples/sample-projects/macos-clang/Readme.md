This project contains the minimal setup required to add the mod.io functionality to your game using the Clang compiler on Mac OS. The `Makefile` in this directory shows how to include the mod.io headers and link the `libmodio.dylib` library. The `libmodio.dylib` is not present by default, we recomend you to grab it from our [releases page](https://github.com/DBolical/modioSDK/releases) and adjust the `MODIO_LIB_DIR` on the `Makefile` but you can also build it yourself by [following our guide](https://github.com/DBolical/modioSDK/wiki/Building).

# Setting up your compiler

Before you start, please update to the latest Mac OS version and install XCode from the App Store.

# Compile and run your project

Open a terminal, go to this project directory and run the `Makefile` by using the `make` command:

```bash
$ make
```

The `MyProject` binary should be generated, you can execute it by typing:

```bash
$ ./MyProject
```

You can find a detailed explanation on how to setup mod.io in the [Getting Started](https://github.com/DBolical/modioSDK/wiki/Getting-Started) guide. Once you finished setting up mod.io on your project you can complete your integration by following our [documentation](https://github.com/DBolical/modioSDK/wiki).
