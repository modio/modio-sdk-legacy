This project shows the minimal setup required to add the mod.io functionality to your project using the GNU C++ compiler. The `Makefile` in this directory shows how to include the mod.io headers and link the `libmodio.so` library. The `libmodio.so` is not present by default, we recomend you to grab it from our [releases page](https://github.com/DBolical/modioSDK/releases) and adjust the `MODIO_LIB_DIR` on the makefile but you can also build it yourself by [following our guide](https://github.com/DBolical/modioSDK/wiki/Building).

# Setting up your compiler

Before you start, please install the GNU C++ compiler.

```bash
# on Debian machines:
$ sudo apt install g++
# on Fedora machines:
$ sudo yum install gcc-c++
```


# Compile and run your project

Open a terminal, go to this project directory and run the `Makefile` by using the `make` command:

```bash
$ make
```

Once the `MyProject` binary file is generated you can execute it by typing:

```bash
$ ./example
```
