# open62541-nodeset-exporter-insource-demo

## General

A C++ 20 and CMake demo project showing how to build using the open2541 and nodesetexporter libraries as statically
linked
git
submodules.

## Dependencies

OS: Linux (Debian, Ubuntu, ...)

To build you will need installed in your system:

- python3
- pip
- conan
- git 
- make
- cmake
- GCC (C++20 features are available since GCC 8, but development was carried out on GCC 12)
  https://gcc.gnu.org/projects/cxx-status.html

## How to build

In the shell you need to run the following commands::

```
git clone git@github.com:xydan83/open62541-nodeset-exporter-insource-demo.git
cd open62541-nodeset-exporter-insource-demo/
mkdir build
cd 3rdparty/
git submodule update --init --recursive
cd ../build
cmake ..
make -j
```

After this, an executable file will be created in `build/bin`. You can execute the demo to
export OPC UA nodeset from any starting node.
You can try using the OPC UA demo server: `opc.tcp://opcua.demo-this.com:51210/UA/SampleServer` and "start
node" `ns=4;i=1240`.
Link to the server from here: https://kb.opclabs.com/OPC_UA_Demo_Servers.

To run the executable,
do: `./bin/nodesetexporter-insource-demo opc.tcp://opcua.demo-this.com:51210/UA/SampleServer "ns=4;i=1240"`.
The first parameter is the address of the OPC UA server, the second is the starting node.
After browsing and exporting you will see a file `demo_export.xml` with a nodeset.

## More info

For the open62541 OPC UA library, see here: https://github.com/open62541

For the nodesetexporter library, see here: https://github.com/xydan83/open62541-nodeset-exporter

## License

MPL2.0: https://github.com/xydan83/open62541-nodeset-exporter-insource-demo/blob/main/LICENSE