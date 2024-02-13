Chess project in C++ for Programming Lab course (INP8084324), University of Padova:

Console commands:

`cd build`

`cmake ...`

`make`

In case the "cmake .." doesn't work because it doesn't find the correct generator:

`rm CMakeCache.txt`

`cmake -G "MinGW Makefiles" ...`

`make`

The log files for the PC and CC match, respectively, are in the /build directory in the form of logPC.txt and logCC.txt files.

It is important that no other .txt files are used for the replay because they are generated to contain other important information such as special moves (build/spec.txt file). 

The replay executable does not check for the validity of the moves because it expects the moves to come from an already valid match. 
When entering files as command-line arguments, it is necessary that you do not prefix "./" to indicate the current folder.
