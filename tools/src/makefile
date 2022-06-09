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

all: procctl gzipfiles deletefiles ftpgetfiles1 ftpgetfiles2 ftpgetfiles3 ftpgetfiles4 ftpgetfiles5 ftpgetfiles ftpputfiles \
	tcpputfiles fileserver tcpgetfiles

procctl: procctl.cpp
	g++ -o procctl procctl.cpp
	cp procctl ../bin/.

gzipfiles: gzipfiles.cpp
	g++ $(CFLAGS) -o gzipfiles gzipfiles.cpp $(PUBINCL) $(PUBCPP) -lm -lc
	cp gzipfiles ../bin/.

deletefiles: deletefiles.cpp
	g++ $(CFLAGS) -o deletefiles deletefiles.cpp $(PUBINCL) $(PUBCPP) -lm -lc
	cp deletefiles ../bin/.

ftpgetfiles1: ftpgetfiles1.cpp
	g++ $(CFLAGS) -o ftpgetfiles1 ftpgetfiles1.cpp $(PUBINCL) $(PUBCPP) /home/wydxry/demo/public/libftp.a /home/wydxry/demo/public/_ftp.cpp -lm -lc
	cp ftpgetfiles1 ../bin/.

ftpgetfiles2: ftpgetfiles2.cpp
	g++ $(CFLAGS) -o ftpgetfiles2 ftpgetfiles2.cpp $(PUBINCL) $(PUBCPP) /home/wydxry/demo/public/libftp.a /home/wydxry/demo/public/_ftp.cpp -lm -lc
	cp ftpgetfiles2 ../bin/.

ftpgetfiles3: ftpgetfiles3.cpp
	g++ $(CFLAGS) -o ftpgetfiles3 ftpgetfiles3.cpp $(PUBINCL) $(PUBCPP) /home/wydxry/demo/public/libftp.a /home/wydxry/demo/public/_ftp.cpp -lm -lc
	cp ftpgetfiles3 ../bin/.

ftpgetfiles4: ftpgetfiles4.cpp
	g++ $(CFLAGS) -o ftpgetfiles4 ftpgetfiles4.cpp $(PUBINCL) $(PUBCPP) /home/wydxry/demo/public/libftp.a /home/wydxry/demo/public/_ftp.cpp -lm -lc
	cp ftpgetfiles4 ../bin/.

ftpgetfiles5: ftpgetfiles5.cpp
	g++ $(CFLAGS) -o ftpgetfiles5 ftpgetfiles5.cpp $(PUBINCL) $(PUBCPP) /home/wydxry/demo/public/libftp.a /home/wydxry/demo/public/_ftp.cpp -lm -lc
	cp ftpgetfiles5 ../bin/.

ftpgetfiles: ftpgetfiles.cpp
	g++ $(CFLAGS) -o ftpgetfiles ftpgetfiles.cpp $(PUBINCL) $(PUBCPP) /home/wydxry/demo/public/libftp.a /home/wydxry/demo/public/_ftp.cpp -lm -lc
	cp ftpgetfiles ../bin/.

ftpputfiles: ftpputfiles.cpp
	g++ $(CFLAGS) -o ftpputfiles ftpputfiles.cpp $(PUBINCL) $(PUBCPP) /home/wydxry/demo/public/libftp.a /home/wydxry/demo/public/_ftp.cpp -lm -lc
	cp ftpputfiles ../bin/.

tcpputfiles: tcpputfiles.cpp
	g++ $(CFLAGS) -o tcpputfiles tcpputfiles.cpp $(PUBINCL) $(PUBCPP) -lm -lc
	cp tcpputfiles ../bin/.

fileserver: fileserver.cpp
	g++ $(CFLAGS) -o fileserver fileserver.cpp $(PUBINCL) $(PUBCPP) -lm -lc
	cp fileserver ../bin/.

tcpgetfiles: tcpgetfiles.cpp
	g++ $(CFLAGS) -o tcpgetfiles tcpgetfiles.cpp $(PUBINCL) $(PUBCPP) -lm -lc
	cp tcpgetfiles ../bin/.

clean:
	rm -f procctl gzipfiles deletefiles ftpgetfiles1 ftpgetfiles2 ftpgetfiles3 ftpgetfiles4 ftpgetfiles5 ftpgetfiles ftpputfiles
	rm -f tcpputfiles fileserver tcpgetfiles