This project contains the minimal setup required to add the mod.io functionality to your game using the Visual C++ compiler. This folder contains a `modio.sln` project that includes the mod.io headers and links to `modio.lib` library. `modio.lib` and `modio.dll` are not included by default, we recomend you to grab it from our [releases page](https://github.com/modio/SDK/releases) and adjust the project's settings but you can also build it yourself by [following our guide](https://github.com/modio/SDK/wiki/Getting-Started).

# Dependencies

1. Visual Studio 15 2017 (also works on Visual Studio 16 2019)
2. x64 Native Tools Command Prompt for VS 2017
3. CMake

# Compile and run

1. Retrieve `YOUR_GAME_ID` and `"YOUR_API_KEY"` from the mod.io web and replace them on `main.cpp`
2. Copy and paste `modio.dll` into this `x64/Release`
3. Open `modio.sln` select `Release` mode and build

# Next steps

You can find a detailed explanation on how to setup mod.io in the [Getting Started](https://github.com/modio/SDK/wiki/Getting-Started) guide. Once you finished setting up mod.io on your project you can complete your integration by following our [documentation](https://github.com/modio/SDK/wiki).
