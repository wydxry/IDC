drop table if exists T_ZHOBTCODE;
create table T_ZHOBTCODE
(
	obtid varchar(10) not null comment '站点代码',
    cityname varchar(30) not null comment '城市名称',
    provname varchar(30) not null comment '省名称',
    lat int not null comment '纬度',
    lon int not null comment '经度',
    height int comment '海拔高度',
    upttime timestamp not null comment '更新时间',
    keyid int not null auto_increment comment ' 记录编号，自动增长列',
    primary key (obtid),
    unique key ZHOBTCODE_KEYID (keyid)
);