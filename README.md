# Shenandoah Variant on JDK-11u

## Turn off "Treating warnings as errors"
At line 171 in make/autoconf/flags-cflags.m4 <br/>
Change
```
CFLAGS_WARNINGS_ARE_ERRORS="-Werror"
```
To
```
CFLAGS_WARNINGS_ARE_ERRORS=""
```

## Build
```shell
sudo ./configure --with-jvm-features=shenandoahgc --enable-debug
sudo make images
```

## Verify Shenandoah is working
```shell
build/*/jdk/bin/java -XX:+UseShenandoahGC -Xlog:gc -version
```
You should get something like this
```shell
[0.025s][info][gc] Heuristics ergonomically sets -XX:+ExplicitGCInvokesConcurrent
[0.025s][info][gc] Heuristics ergonomically sets -XX:+ShenandoahImplicitGCInvokesConcurrent
[0.027s][info][gc] Using Shenandoah
openjdk version "11.0.13-internal" 2021-10-19
OpenJDK Runtime Environment (build 11.0.13-internal+0-adhoc.root.jdk11u)
OpenJDK 64-Bit Server VM (build 11.0.13-internal+0-adhoc.root.jdk11u, mixed mode)
[0.188s][info][gc] Cancelling GC: Stopping VM
```

## Install JDK-11u
```shell
sudo update-alternatives --install /usr/bin/java java /path/to/jdk11u/build/*/jdk/bin/java 11
sudo update-alternatives --install /usr/bin/javac javac /path/to/jdk11u/build/*/jdk/bin/javac 11
```

## Switch among JDK versions
```shell
sudo update-alternatives --config java
sudo update-alternatives --config javac
```
