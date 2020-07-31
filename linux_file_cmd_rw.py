# 1. Utility script for reading from a file.
# 2. Utility script to run a linux command from script and capture
#    its output to a file.

import os

# To open a file for reading
f = open("README.txt","r")
data = f.read()
print(data) # print the content
f.close()

# To run a bash command and redirect the output to some file.
# For example here I'm using linux ls(list) command and
# redirecting it to out_file.txt
cmd = "ls > out_file.txt"
os.system(cmd)



