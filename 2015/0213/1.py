#!/usr/bin/env python
# -*- encoding: utf8 -*-
#
# Description:
#   use for get remote files from ftp
#
# History: 
#   created by Young     2015/02/13

import os
import sys
import ftplib
import time

REMOTE_DIR = "/home/baidu"
LOCAL_DIR = "/home/young/temp"
FTPADDR = "192.168.99.208"
FTPUSER = "baidu"
FTPPASSWD = "12345"


class FTPSync(object):
    def __init__(self):
        self.conn = ftplib.FTP(FTPADDR, FTPUSER, FTPPASSWD)
        remote_base_dirname = os.path.basename(REMOTE_DIR)
        local_data_dirname = os.path.join(LOCAL_DIR, remote_base_dirname)
        if not os.path.isdir(local_data_dirname):
            os.makedirs(local_data_dirname)
        self.conn.cwd(REMOTE_DIR)               # 远端FTP目录
        os.chdir(local_data_dirname)            # 本地下载目录

    def get_dirs_files(self):
        u''' 得到当前目录和文件, 放入dir_res列表 '''
        dir_res = []
        self.conn.dir('.', dir_res.append)
        files = [f.split(None, 8)[-1] for f in dir_res if f.startswith('-')]
        dirs = [f.split(None, 8)[-1] for f in dir_res if f.startswith('d')]
        return (files, dirs)

    def walk(self, next_dir):
        #print 'Walking to', next_dir
        self.conn.cwd(next_dir)
        try:
            os.mkdir(next_dir)
        except OSError:
            pass
        os.chdir(next_dir)

        ftp_curr_dir = self.conn.pwd()
        local_curr_dir = os.getcwd()

        files, dirs = self.get_dirs_files()
        #print "FILES: ", files
        #print "DIRS: ", dirs
        for f in files:
            #print next_dir, ':', f
            outf = open(f, 'wb')
            try:
                self.conn.retrbinary('RETR %s' % f, outf.write)
            finally:
                outf.close()
        for d in dirs:
            os.chdir(local_curr_dir)
            self.conn.cwd(ftp_curr_dir)
            self.walk(d)

    def run(self):
        self.walk('.')

def main():
    f = FTPSync()
    print time.strftime("start:\t%Y-%m-%d %H:%M:%S", time.localtime())
    f.run()
    print time.strftime("finish:\t%Y-%m-%d %H:%M:%S", time.localtime())

if __name__ == '__main__':
    main()
