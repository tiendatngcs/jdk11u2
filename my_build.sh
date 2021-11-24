#!/bin/bash

if [ $# == 0 ];
then
    echo 'Usage my_build.sh 1|fastdebug|2|release jdk|images|all clean|null' 
    #echo 'make clean CONF=linux-x86_64-normal-server-fastdebug'
    #make clean CONF=linux-x86_64-normal-server-fastdebug

    #echo 'make images CONF=linux-x86_64-normal-server-fastdebug'
    #make images CONF=linux-x86_64-normal-server-fastdebug

    #echo 'make clean CONF=linux-x86_64-normal-server-release'
    #make clean CONF=linux-x86_64-normal-server-release

    #echo 'make images CONF=linux-x86_64-normal-server-release'
    #make  CONF=linux-x86_64-normal-server-release
else
    if [[ -z $2 ]];
    then
	echo 'empty $2 - setting to "images" as default'
	set -- "$1" "images"
    fi
    
    if [ $1 == "1" ] || [ $1 == "fastdebug" ];
    then
	if [[ -n $3 ]] && [ $3 == "clean" ];
	then   
	    echo 'make clean CONF=linux-x86_64-normal-server-fastdebug'
	    make clean CONF=linux-x86_64-normal-server-fastdebug
	fi     
	echo 'make '$2' CONF=linux-x86_64-normal-server-fastdebug'
	time make $2 CONF=linux-x86_64-normal-server-fastdebug
    else
	if [ $1 == "2" ] || [ $1 == "release" ];
	then
	    if [[ -n $3 ]] && [ $3 == "clean" ];
            then
		echo 'make clean CONF=linux-x86_64-normal-server-release'
		make clean CONF=linux-x86_64-normal-server-release
	    fi	
	    echo 'make '$2' CONF=linux-x86_64-normal-server-release'
	    time make $2 CONF=linux-x86_64-normal-server-release
	else
	    #if [ $1 == "3" ] || [ $1 == "slowdebug" ];
	    #then
	    echo 'Not configured for anything else'
		#echo 'make clean CONF=linux-x86_64-normal-server-slowdebug'
		#make clean CONF=linux-x86_64-normal-server-slowdebug

		#echo 'make all CONF=linux-x86_64-normal-server-slowdebug'
		#make all CONF=linux-x86_64-normal-server-slowdebug
	    #fi

	fi

    fi
fi

#./make_class_info_server.sh

#echo 'make all CONF=linux-x86_64-normal-server-fastdebug'
#make all CONF=linux-x86_64-normal-server-fastdebug

#echo 'make all CONF=linux-x86_64-normal-server-release'
#make all CONF=linux-x86_64-normal-server-release
