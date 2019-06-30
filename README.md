# FileWatcher
A tool for monitoring file changes

# Getting Started

1. 安装cmake，Macos:`brew install cmake` centos: `sudo yum install cmake`
2. 安装编译器，Macos自带了clang++，linux：`sudo yum -y install gcc gcc-c++`


# Build and Test(目前只支持unix)

1. `git clone git@github.com:tiyee/FileWatcher.git`
2. `cd angemon`
3. `mkdir build && cd build`
4. `cmake ..`
5. `make`
6. `cd ..`
7. ```./bin/FileWatcher -f `pwd`/logs/test.log -f `pwd`/logs/test2.log```


> 因为是测试，所以log日志也会在控制台输出，实际应该讲log写入文件，控制台只输出文件变化，供bash捕捉

# Feature

1.linux支持(正在进行)
