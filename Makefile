# (C) 2022 Olivia May GPLv3+
#
# Usage:
# make			Compile LIVSDiary
# make run		Compile and execute LIVSDiary
# make install		Install to /usr/bin, type 'livsdiary' in terminal to use
# make uninstall	Remove from /usr/bin


# Variables
CC = g++
.PHONY = compile run clean install uninstall


# Targets 
compile:
	@echo "Compiling src/main.cpp..."
	@${CC} src/main.cpp -o livsdiary

run: compile
	@stat livsdiary
	@./livsdiary

clean:
	@echo "Cleaning up..."
	@rm livsdiary

# Must be root user for the following
install: compile
	@echo "Installing to /usr/bin..."
	@mv livsdiary /usr/bin

uninstall:
	@echo "Uninstalling from /usr/bin..."
	@rm /usr/bin/livsdiary
