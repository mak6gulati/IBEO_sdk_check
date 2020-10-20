#!/bin/bash

baseFolder=`pwd`

# Create target folder.
targetFolder=$baseFolder'/target'
if [ ! -d "$targetFolder" ]; then
    mkdir -p $targetFolder
fi
cd $targetFolder

# tinyxml2
mkdir tinyxml2-6.2.0
cd tinyxml2-6.2.0
cmake $baseFolder'/tinyxml2-6.2.0'
make -j16
tinyxml2_DIR=$targetFolder'/tinyxml2-6.2.0'
cd ..

# logging
mkdir logging
cd logging
cmake -D tinyxml2_DIR=$tinyxml2_DIR $baseFolder'/logging/source'
make -j16
logging_DIR=$targetFolder'/logging'
cd ..

# sdk
mkdir sdk
cd sdk
cmake -D tinyxml2_DIR=$tinyxml2_DIR -D ibeo-common-logging_DIR=$logging_DIR $baseFolder'/sdk/source'
make -j16
sdk_DIR=$targetFolder'/sdk'
cd ..

# sdk_demos
mkdir sdk_demos
cd sdk_demos
cmake -D tinyxml2_DIR=$tinyxml2_DIR -D ibeo-common-logging_DIR=$logging_DIR -Dibeo-common-sdk_DIR=$sdk_DIR $baseFolder'/sdk_demos/source'
make -j16
cd ..

# sdk_tools
mkdir sdk_tools
cd sdk_tools
cmake -D tinyxml2_DIR=$tinyxml2_DIR -D ibeo-common-logging_DIR=$logging_DIR -Dibeo-common-sdk_DIR=$sdk_DIR $baseFolder'/sdk_tools/source'
make -j16
cd ..
