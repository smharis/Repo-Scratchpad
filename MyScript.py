import os

# To open a file for read
f = open("README.txt","r")
data = f.read()
print(data)
f.close()

# To run a bash command and redirect the output to some file
# For example here I'm using linux ls(list) command
cmd = "ls > out_file.txt"
os.system(cmd)



