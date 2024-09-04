import os
import sys
TMP='''PASS x\r\nNICK nick{0}\r\nUSER user{0} 0 * abc \r\n'''


for clinet in range(int(sys.argv[1])):
    cmd = TMP.format(clinet)
    filename = "files/infile{0}".format(clinet)
    with open(filename, "w") as fp:
        fp.write(cmd)
    os.system("sleep 0.05")
    os.system("nc -c localhost  8080 < '" + filename + "'")