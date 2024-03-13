# Makefile
# This file is part of sshconnector, distributed under the GNU GPL v2
# For full terms see the included COPYING file.

CPP = g++
CPPFLAGS = -g -Wall -std=c++11
LDFLAGS = -lm
FRAMEWORKS = -lncurses -lmenu -lform
FILE = *.cpp
BUILDDIR = build

all: *.cpp
	echo Start baking SSHConector
	mkdir -p $(BUILDDIR)
	$(CPP) $(CPPFLAGS) -o $(BUILDDIR)/sshconnector $(FILE) $(LDFLAGS) $(FRAMEWORKS)

normal: *.cpp
	mkdir -p $(BUILDDIR)
	$(CPP) $(CPPFLAGS) -o $(BUILDDIR)/sshconnector $(FILE) $(LDFLAGS)

clean:
	rm -rf $(BUILDDIR)/sshconnector
