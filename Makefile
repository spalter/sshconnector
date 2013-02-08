#Makefile
#This file is part of sshconnector, distributed under the GNU GPL v2
#For full terms see the included COPYING file.

CPP = g++ 
CPPFLAGS = -g -Wall -std=c++11
LDFLAGS = -lm
FRAMEWORKS = -lncurses -lmenu
FILE = *.cpp

all: *.cpp
	echo Start baking SSHConector
	$(CPP) $(CPPFLAGS) -o sshconnector $(FILE) $(LDFLAGS) $(FRAMEWORKS)

normal: *.cpp
	$(CPP) $(CPPFLAGS) -o sshconnector $(FILE) $(LDFLAGS)
	
clean:
	rm -r sshconnector
