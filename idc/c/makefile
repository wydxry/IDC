# 开发框架头文件路径。
PUBINCL = -I/home/wydxry/ProjectCpp/demo/public

# 开发框架cpp文件名，这里直接包含进来，没有采用链接库，是为了方便调试。
PUBCPP = /home/wydxry/ProjectCpp/demo/public/_public.cpp

# mysql头文件存放路径
MYSQLINCL = -I/usr/local/mysql/include  -I/project/public/db/mysql

# mysql库文件保存路径
MYSQLLIB = -L/usr/local/mysql/lib

# mysql链接库
MYSQLLIBS = -lmysqlclient

# 开发框架mysql的cpp文件名，这里直接包含进来，没有采用链接库，是为了方便调试。
MYSQLCPP = /project/public/db/mysql/_mysql.cpp

# 编译参数。
CFLAGS = -g 

all: crtsurfdata1 crtsurfdata2

crtsurfdata1: crtsurfdata1.cpp
	g++ $(CFLAGS) -o crtsurfdata1 crtsurfdata1.cpp $(PUBINCL) $(PUBCPP) -lm -lc
	cp crtsurfdata1 ../bin/.

crtsurfdata2: crtsurfdata2.cpp
	g++ $(CFLAGS) -o crtsurfdata2 crtsurfdata2.cpp $(PUBINCL) $(PUBCPP) -lm -lc
	cp crtsurfdata2 ../bin/.

clean:
	rm -f crtsurfdata1 crtsurfdata2