####################################################################
# 启动数据中心后台服务程序的脚本。
####################################################################

# 【示例】检查服务程序是否超时，配置在/etc/rc.local中由root用户执行。
#/project/tools1/bin/procctl 30 /project/tools1/bin/checkproc

# 压缩数据中心后台服务程序的备份日志。
/home/wydxry/demo/tools/bin/procctl 300 /home/wydxry/demo/tools/bin/gzipfiles /home/wydxry/demo/idc/log "*.log.20*" 0.04

# 生成用于测试的全国气象站点观测的分钟数据。
/home/wydxry/demo/tools/bin/procctl  60 /home/wydxry/demo/idc/bin/crtsurfdata /home/wydxry/demo/idc/ini/stcode.ini /home/wydxry/demo/idc/tmp/surfdata /home/wydxry/demo/idc/log/crtsurfdata.log xml,json,csv

# 清理原始的全国气象站点观测的分钟数据目录/tmp/idc/surfdata中的历史数据文件。
/home/wydxry/demo/tools/bin/procctl 300 /home/wydxry/demo/tools/bin/deletefiles /home/wydxry/demo/idc/tmp/surfdata "*" 0.04