#Makefile

CPP = g++ 
CPPFLAGS = -g -Wall -std=c++11
LDFLAGS = -lm
FRAMEWORKS = -lncurses
FILE = *.cpp

all: *.cpp
	echo Start baking SSHConector
	$(CPP) $(CPPFLAGS) -o sshconnector $(FILE) $(LDFLAGS) $(FRAMEWORKS)
	#echo Run $(FILE)
	#gnome-terminal
	#echo Clean up
	#make clean

normal: *.cpp
	$(CPP) $(CPPFLAGS) -o sshconnector $(FILE) $(LDFLAGS)
	
clean:
	rm -r sshconnector
