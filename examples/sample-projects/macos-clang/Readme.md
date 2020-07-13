This project contains the minimal setup required to add the mod.io functionality to your game using the Clang compiler on Mac OS. The `Makefile` in this directory shows how to include the mod.io headers and link the `libmodio.dylib` library. The `libmodio.dylib` is not included by default, we recomend you to grab it from our [releases page](https://github.com/modio/SDK/releases) and adjust the `MODIO_LIB_DIR` on the `Makefile` but you can also build it yourself by [following our guide](https://github.com/modio/SDK/wiki/Building).

# Dependencies

* XCode build tools
* CMake (optional)

# Compile and run

1. Copy and paste the `libmodio.dylib` into this directory
2. Retrieve `YOUR_GAME_ID` and `"YOUR_API_KEY"` from the mod.io web and replace them on `main.cpp`
3. `make`
4. `./MyProject`

# Next steps
```

You can find a detailed explanation on how to setup mod.io in the [Getting Started](https://github.com/modio/SDK/wiki/Getting-Started) guide. Once you finished setting up mod.io on your project you can complete your integration by following our [documentation](https://github.com/modio/SDK/wiki).
