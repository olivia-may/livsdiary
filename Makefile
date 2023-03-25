#
# LIVSDiary - (LI)ghtweight (V)irtual (S)imple Diary
# Copyright (C) 2022 Olivia May - olmay@tuta.io
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program. If not, see <https://www.gnu.org/licenses/>.
#
# Usage:
# make				Compile 'livsdiary.o'.
# make run			Make objects if none were compiled. Link object files into 'livsdiary.o'.
# 				Then run 'livsdiary.o'.
# make livsdiary		Link object files into 'livsdiary.o'
# make SOURCE CODE FILE		Make the object for that source code file. Ex: 'make main'.
# make clean			Remove all binary files
# make remove-user-files	Remove livsdiary files in home directory.
# make install			Install to /usr/local/bin.
# make uninstall		Remove from /usr/local/bin.

CC=gcc
CPP=g++
LINKERFLAGS=

PROGRAM_NAME=livsdiary
PROGRAM_VERSION=v1.3.0
PROGRAM_DIR=/.livsdiary/

SRCS_DIR=src/
OBJS_DIR=obj/

SRCS_C=converters \
       filesystem \
       time

SRCS_CPP=main \
	 page

OBJS=converters.o \
     filesystem.o \
     main.o \
     page.o \
     time.o

.PHONY=all run clean remove-user-files install uninstall
.ONESHELL:

all: ${SRCS_C} ${SRCS_CPP} $(PROGRAM_NAME)

program.h:
	@echo -en "\n/* This file was generated by ../Makefile */\n\n#define PROGRAM_NAME \"$(PROGRAM_NAME)\"\n#define PROGRAM_VERSION \"$(PROGRAM_VERSION)\"\n#define PROGRAM_DIR \"$(PROGRAM_DIR)\"\n" > $(SRCS_DIR)program.h

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

${SRCS_C}: $(OBJS_DIR) program.h
	$(CC) -c $(SRCS_DIR)$@.c -o $(OBJS_DIR)$@.o

${SRCS_CPP}: $(OBJS_DIR) program.h
	$(CPP) -c $(SRCS_DIR)$@.cpp -o $(OBJS_DIR)$@.o

$(PROGRAM_NAME): program.h
	cd $(OBJS_DIR)
	$(CPP) $(LINKERFLAGS) $(OBJS) -o ../$(PROGRAM_NAME).o 
	cd ..
	du -b $(PROGRAM_NAME).o

run: all 
	./$(PROGRAM_NAME).o

clean:
	rm -f ./{*.out,*.o} $(SRCS_DIR){*.out,*.o}
	rm -rf $(OBJS_DIR)

remove-user-files:
	rm -rf ~/.livsdiary

# Must be root user for both
install: $(PROGRAM_NAME)
	install -D $(PROGRAM_NAME).o /usr/local/bin/$(PROGRAM_NAME)

uninstall:
	rm -f /usr/local/bin/$(PROGRAM_NAME)
