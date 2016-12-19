# encoding utf8
#"""该脚本用于查找大的文件"""
import os,sys,time


def checkIsLargeFile(file_path):
    #"""断判文件否是大于Bigjudge，大于打印文件大小"""
    Bigjudge = 10 * 1024 * 1024
    filesize = os.path.getsize(file_path)
    if os.path.isfile(file_path) == False:
        raise os.error("File not found")
    if(filesize > Bigjudge):
        print file_path, filesize
    else:
        pass
        

def getAlltree(dir_path):
    #"""查找该录目下全部文件大于Bigjudge的文件，并打印。"""
    for name in os.listdir(dir_path):
        full_path = os.path.join(dir_path, name)
        if os.path.isfile(full_path):
            checkIsLargeFile(full_path)                             
        elif os.path.isdir(full_path):
            getAlltree(full_path)

    
def main():
    #dir_path = "c:" 
    dir_path = "/home/young" 
    getAlltree(dir_path)
    


if __name__ == '__main__': main()  
