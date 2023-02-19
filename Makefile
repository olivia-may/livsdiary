# (C) 2022 Olivia May GPLv3+
#
# Usage:
# make				Compile LIVSDiary.
# make run			Compile and execute LIVSDiary.
# make remove-user-files	Remove livsdiary files in home directory.
# make install			Install to /usr/local/bin. Use from command line.
# make uninstall		Remove from /usr/local/bin.

CC=g++
LINKERFLAGS=

.PHONY=compile run clean remove-user-files install uninstall

compile:
	${CC} ${LINKERFLAGS} src/main.cpp -o livsdiary.o
	stat livsdiary.o

run: compile
	./livsdiary.o

clean:
	rm -f livsdiary.o

remove-user-files:
	rm -rf ~/.livsdiary

# Must be root user for the following
install: compile
	cp livsdiary.o /usr/local/bin/livsdiary

uninstall:
	rm -f /usr/local/bin/livsdiary
