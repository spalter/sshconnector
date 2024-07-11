# Makefile
# This file is part of sshconnector, distributed under the GNU GPL v2
# For full terms see the included COPYING file.

CPP = g++
CPPFLAGS = -g -Wall -std=c++11
LDFLAGS = -lm
FRAMEWORKS = -lncurses -lmenu -lform
FILE = *.cpp
BUILDDIR = build
SOURCEDIR = .

all: clean format *.cpp
	echo "Start baking SSHConector"
	mkdir -p $(BUILDDIR)
	$(CPP) $(CPPFLAGS) -o $(BUILDDIR)/sshconnector $(FILE) $(LDFLAGS) $(FRAMEWORKS)

clean:
	rm -rf $(BUILDDIR)/sshconnector

run: all
	echo "Run SSHConector"
	./$(BUILDDIR)/sshconnector ~/.config/sshc/hosts.conf

format:
	echo "Format Source Files"
	clang-format -i $(SOURCEDIR)/*.cpp
	clang-format -i $(SOURCEDIR)/*.h