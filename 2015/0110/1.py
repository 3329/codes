import os


dirname = "ops"
DATA_TARGET_DIR  = "/home/young/test/UNICOM/TARGET_DIR"
decompress_str = ''.join(["print  ", dirname, " > ", DATA_TARGET_DIR])
print decompress_str
os.system(''.join(["print  ", dirname, " > ", DATA_TARGET_DIR]))
os.system("".join["gizp -d ", filename])

filename = "/home/young/codes/2015/0110/1.py"
file_base_name = os.path.basename(filename)
print file_base_name
print os.path.dirname(filename)
