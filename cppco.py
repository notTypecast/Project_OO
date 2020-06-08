
# move co.py to desired directory and run
# results will be saved to final.txt

import os
finalfile = open("final.txt", 'w')
donotread = ['co.py', 'final.txt', 'final.md']

files = []
for root,dir,file in os.walk('.'):
    for filename in file:
        if not filename in donotread:
            files.append(filename)
        

namesonly = []
for filename in files:
    fname = filename.split('.')[0]
    if not( fname in namesonly):
        namesonly.append(fname)

namesonly.sort()
print(namesonly)
files.sort()
for filename in namesonly:
    try: 
        with open(filename + ".h", 'r') as sourcefile:
            finalfile.write("\n\n\n")
            finalfile.write("---------------\n")
            finalfile.write(filename + ".h")
            finalfile.write("\n---------------")
            finalfile.write("\n\n\n")
            for line in sourcefile.readlines():
                finalfile.write(line)
    except FileNotFoundError as ex:
        pass
    try: 
        with open(filename + ".cpp", 'r') as sourcefile:
            finalfile.write("\n\n\n")
            finalfile.write("---------------\n")
            finalfile.write(filename + ".cpp")
            finalfile.write("\n---------------")
            finalfile.write("\n\n\n")
            for line in sourcefile.readlines():
                finalfile.write(line)
    except FileNotFoundError as ex:
        pass
finalfile.close()
