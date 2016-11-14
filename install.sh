#########################################################################
# File Name: install.sh
# Author: yeephycho
# mail: huyixuanhyx@gmail.com
# Created Time: Monday, November 14, 2016 PM02:46:37 HKT
#########################################################################
#!/bin/bash

mkdir ./build
cd ./build
echo "ENTER DIRECTORY BUILD"

cmake ..
echo "BUILD FINISHED!"

cd src
echo "ENTER DIRECTORY SRC"

make
echo "START MAKE"

echo "TRY EXECUTE"
./fastSpatialConvolution
