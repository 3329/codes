# encoding utf8
import os,sys,time


def checkIsLargeFile(file_path):
    Bigjudge = 10 * 1024 * 1024
    filesize = os.path.getsize(file_path)
    if os.path.isfile(file_path) == False:
        raise os.error("File not found")
    if(filesize > Bigjudge):
        print file_path, filesize
    else:
        pass
        

def getAlltree(dir_path):
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
