# 开发框架头文件路径。
PUBINCL = -I/home/wydxry/demo/public

# 开发框架cpp文件名，这里直接包含进来，没有采用链接库，是为了方便调试。
PUBCPP = /home/wydxry/demo/public/_public.cpp

# mysql头文件存放路径
MYSQLINCL = -I/wydxry/mysql5.7/include  -I/home/wydxry/demo/public/db/mysql

# mysql库文件保存路径
MYSQLLIB = -L/wydxry/mysql5.7/lib

# mysql链接库
MYSQLLIBS = -lmysqlclient

# 开发框架mysql的cpp文件名，这里直接包含进来，没有采用链接库，是为了方便调试。
MYSQLCPP = /home/wydxry/demo/public/db/mysql/_mysql.cpp

# 编译参数。
CFLAGS = -g 

all: procctl gzipfiles

procctl: procctl.cpp
	g++ -o procctl procctl.cpp
	cp procctl ../bin/.

gzipfiles: gzipfiles.cpp
	g++ $(CFLAGS) -o gzipfiles gzipfiles.cpp $(PUBINCL) $(PUBCPP) -lm -lc
	cp gzipfiles ../bin/.

clean:
	rm -f procctl gzipfiles