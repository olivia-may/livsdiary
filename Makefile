# (C) 2022 Olivia May GPLv3+
#
# Usage:
# make				Compile LIVSDiary.
# make run			Compile and execute LIVSDiary.
# make remove-user-files	Remove livsdiary files in home directory.
# make install			Install to /usr/local/bin. Use from command line.
# make uninstall		Remove from /usr/local/bin.

PROGRAM_VERSION = "v1.1.1"

CC = g++
.PHONY = compile run clean remove-user-files install uninstall

compile:
	@echo "Compiling src/main.cpp..."
	@rm -f src/version.h
	@printf '/* (C) 2022 Olivia May GPLv3+ */\n\n#define PROGRAM_VERSION ${PROGRAM_VERSION}\n' >> src/version.h
	@${CC} src/main.cpp -o livsdiary
	@stat livsdiary

run: compile
	@./livsdiary

clean:
	@echo "Cleaning up..."
	@rm -f livsdiary

remove-user-files:
	@echo "Removing ~/.livsdiary"
	@rm -rf ~/.livsdiary

# Must be root user for the following
install: compile
	@echo "Installing to /usr/local/bin..."
	@cp livsdiary /usr/local/bin

uninstall:
	@echo "Uninstalling from /usr/local/bin..."
	@rm -f /usr/local/bin/livsdiary
