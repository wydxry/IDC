# mysql头文件存放的目录。
MYSQLINCL = -I/wydxry/mysql5.7/include

# mysql库文件存放的目录。
MYSQLLIB = -L/wydxry/mysql5.7/lib

# 需要链接的mysql库。
MYSQLLIBS = -lmysqlclient

CFLAGS=-g -Wno-write-strings

all: createtable inserttable updatetable selecttable deletetable filetoblob blobtofile 

createtable:createtable.cpp _mysql.h _mysql.cpp
	g++ $(CFLAGS) -o createtable createtable.cpp $(MYSQLINCL) $(MYSQLLIB) $(MYSQLLIBS) _mysql.cpp -lm -lc
	cp createtable ../bin/.

inserttable:inserttable.cpp _mysql.h _mysql.cpp
	g++ $(CFLAGS) -o inserttable inserttable.cpp $(MYSQLINCL) $(MYSQLLIB) $(MYSQLLIBS) _mysql.cpp -lm -lc
	cp inserttable ../bin/.

updatetable:updatetable.cpp _mysql.h _mysql.cpp
	g++ $(CFLAGS) -o updatetable updatetable.cpp $(MYSQLINCL) $(MYSQLLIB) $(MYSQLLIBS) _mysql.cpp -lm -lc
	cp updatetable ../bin/.

selecttable:selecttable.cpp _mysql.h _mysql.cpp
	g++ $(CFLAGS) -o selecttable selecttable.cpp $(MYSQLINCL) $(MYSQLLIB) $(MYSQLLIBS) _mysql.cpp -lm -lc
	cp selecttable ../bin/.

deletetable:deletetable.cpp _mysql.h _mysql.cpp
	g++ $(CFLAGS) -o deletetable deletetable.cpp $(MYSQLINCL) $(MYSQLLIB) $(MYSQLLIBS) _mysql.cpp -lm -lc
	cp deletetable ../bin/.

filetoblob:filetoblob.cpp _mysql.h _mysql.cpp
	g++ $(CFLAGS) -o filetoblob filetoblob.cpp $(MYSQLINCL) $(MYSQLLIB) $(MYSQLLIBS) _mysql.cpp -lm -lc
	cp filetoblob ../bin/.

blobtofile:blobtofile.cpp _mysql.h _mysql.cpp
	g++ $(CFLAGS) -o blobtofile blobtofile.cpp $(MYSQLINCL) $(MYSQLLIB) $(MYSQLLIBS) _mysql.cpp -lm -lc
	cp blobtofile ../bin/.

clean:
	rm -rf createtable inserttable updatetable selecttable deletetable filetoblob blobtofile
