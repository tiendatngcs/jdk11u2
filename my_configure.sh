#!/bin/bash

if [ $# == 0 ];
then
    echo 'Usage my_configure.sh 1|fastdebug|2|release' 

else
    if [ $1 == "1" ] || [ $1 == "fastdebug" ];
    then
	bash configure --with-jvm-features=shenandoahgc --enable-debug --with-native-debug-symbols=internal --disable-warnings-as-errors  --enable-ccache 
    else
	if [ $1 == "2" ] || [ $1 == "release" ];
	then
	    bash configure --with-jvm-features=shenandoahgc --with-native-debug-symbols=internal --disable-warnings-as-errors  --enable-ccache 
	else
	    echo 'Not configured for anything else'

	fi

    fi
fi

