# ex-int-tcl-min
A minimum example for embedding Tcl scripting engine.

Build in Linux:

```shell
$ mkdir build-debug
$ cd build-debug
$ cmake .. -DCMAKE_BUILD_TYPE=Debug
$ cmake --build .
$ ./tclmin "3 * 2"
6
```

Build in Windows:

```shell
$ mkdir build
$ cd build
$ cmake ..
$ cmake --build . --config Debug
$ cd Debug
$ tclmin "3 * 2"
6
```
