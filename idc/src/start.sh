####################################################################
# 启动数据中心后台服务程序的脚本。
####################################################################

# 【示例】检查服务程序是否超时，配置在/etc/rc.local中由root用户执行
#/project/tools1/bin/procctl 30 /project/tools1/bin/checkproc

# 压缩数据中心后台服务程序的备份日志。
/home/wydxry/demo/tools/bin/procctl 300 /home/wydxry/demo/tools/bin/gzipfiles /home/wydxry/demo/idc/log "*.log.20*" 0.04

# 生成用于测试的全国气象站点观测的分钟数据。
/home/wydxry/demo/tools/bin/procctl  60 /home/wydxry/demo/idc/bin/crtsurfdata /home/wydxry/demo/idc/ini/stcode.ini /home/wydxry/demo/idc/tmp/surfdata /home/wydxry/demo/idc/log/crtsurfdata.log xml,json,csv

# 清理原始的全国气象站点观测的分钟数据目录/tmp/idc/surfdata中的历史数据文件。
/home/wydxry/demo/tools/bin/procctl 300 /home/wydxry/demo/tools/bin/deletefiles /home/wydxry/demo/idc/tmp/surfdata "*" 0.04

# 下载全国气象站点观测的分钟数据的xml文件
/home/wydxry/demo/tools/bin/procctl 30 /home/wydxry/demo/tools/bin/ftpgetfiles /home/wydxry/demo/idc/log/ftpgetfiles.log "<host>127.0.0.1:21</host><mode>1</mode><username>wydxry</username><password>1</password><remotepath>/home/wydxry/demo/idc/tmp/surfdata</remotepath><localpath>/home/wydxry/demo/idc/tmp/client</localpath><matchname>SURF_ZH*.XML</matchname><ptype>1</ptype><remotepathbak>/home/wydxry/demo/idc/tmp/backup</remotepathbak><okfilename>/home/wydxry/demo/idc/tmp/data/ftpgetfiles_surfdata.xml</okfilename><listfilename>/home/wydxry/demo/idc/tmp/ftplist/ftpgetfiles_surfdata.list</listfilename><checkmtime>true</checkmtime><timeout>80</timeout><pname>ftpgetfiles_surfdata</pname>"

# 上传全国气象站点观测的分钟数据的xml文件
/home/wydxry/demo/tools/bin/procctl 30 /home/wydxry/demo/tools/bin/ftpputfiles /home/wydxry/demo/idc/log/ftpputfiles.log "<host>127.0.0.1:21</host><mode>1</mode><username>wydxry</username><password>1</password><remotepath>/home/wydxry/demo/idc/tmp/server</remotepath><localpath>/home/wydxry/demo/idc/tmp/client</localpath><matchname>*</matchname><ptype>1</ptype><localpathbak>/home/wydxry/demo/idc/tmp/backup</localpathbak><okfilename>/home/wydxry/demo/idc/tmp/data/ftpputfiles_surfdata.xml</okfilename><timeout>80</timeout><pname>ftppufiles_surfdata</pname>"

# 清理采集的全国气象站点观测的分钟数据目录idc/tmp/client中的历史数据文件
/home/wydxry/demo/tools/bin/procctl 300 /home/wydxry/demo/tools/bin/deletefiles /home/wydxry/demo/idc/tmp/client "*" 0.02

# 清理采集的全国气象站点观测的分钟数据目录idc/tmp/server中的历史数据文件
/home/wydxry/demo/tools/bin/procctl 300 /home/wydxry/demo/tools/bin/deletefiles /home/wydxry/demo/idc/tmp/server "*" 0.02

# 文件传输的服务端程序
/home/wydxry/demo/tools/bin/procctl 10 /home/wydxry/demo/tools/bin/fileserver 5005 /home/wydxry/demo/idc/log/fileserver.log

# 把目录xxx中的文件上传到xxx目录中
/home/wydxry/demo/tools/bin/procctl 20 /home/wydxry/demo/tools/bin/tcpputfiles /home/wydxry/demo/idc/log/tcpputfiles_surfdata.log "<ip>127.0.0.1</ip><port>5005</port><ptype>1</ptype><clientpath>/home/wydxry/demo/idc/tmp/client</clientpath><andchild>true</andchild><matchname>*.XML,*.CSV,*.JSON</matchname><srvpath>/home/wydxry/demo/idc/tmp/server</srvpath><timetvl>10</timetvl><timeout>50</timeout><pname>tcpputfiles_surfdata</pname>"

# 把目录xxx中的文件下载到xxx目录中
/home/wydxry/demo/tools/bin/procctl 20 /home/wydxry/demo/tools/bin/tcpgetfiles /home/wydxry/demo/idc/log/tcpgetfiles_surfdata.log "<ip>127.0.0.1</ip><port>5005</port><ptype>1</ptype><srvpath>/home/wydxry/demo/idc/tmp/server</srvpath><andchild>true</andchild><matchname>*.XML,*.CSV,*.JSON</matchname><clientpath>/home/wydxry/demo/idc/tmp/client</clientpath><timetvl>10</timetvl><timeout>50</timeout><pname>tcpgetfiles_surfdata</pname>"
