
# move co.py to desired directory and run
# results will be saved to final.txt

import os
finalfile = open("final.txt", 'w')
donotread = ['co.py', 'final.txt', 'final.md']

files = []
for root,dir,file in os.walk('.'):
    for filename in file:
        files.append(filename)
        

files.sort()
for filename in files:
    if filename in donotread:
            continue
    finalfile.write("\n\n\n")
    finalfile.write("---------------\n")
    finalfile.write(filename)
    finalfile.write("\n---------------")
    finalfile.write("\n\n\n")
    with open(filename, 'r') as sourcefile:
        for line in sourcefile.readlines():
            finalfile.write(line)

finalfile.close()
