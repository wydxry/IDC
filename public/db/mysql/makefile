# mysql头文件存放的目录。
MYSQLINCL = -I/wydxry/mysql5.7/include

# mysql库文件存放的目录。
MYSQLLIB = -L/wydxry/mysql5.7/lib

# 需要链接的mysql库。
MYSQLLIBS = -lmysqlclient

CFLAGS=-g -Wno-write-strings

all: createtable inserttable

createtable:createtable.cpp _mysql.h _mysql.cpp
	g++ $(CFLAGS) -o createtable createtable.cpp $(MYSQLINCL) $(MYSQLLIB) $(MYSQLLIBS) _mysql.cpp -lm -lc
	cp createtable ../bin/.

inserttable:inserttable.cpp _mysql.h _mysql.cpp
	g++ $(CFLAGS) -o inserttable inserttable.cpp $(MYSQLINCL) $(MYSQLLIB) $(MYSQLLIBS) _mysql.cpp -lm -lc
	cp inserttable ../bin/.

clean:
	rm -rf createtable inserttable
