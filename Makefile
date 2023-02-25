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
# make SOURCE CODE FILE		Make the object for that source code file. Ex: 'make command_line'.
# make clean			Remove all binary files
# make remove-user-files	Remove livsdiary files in home directory.
# make install			Install to /usr/local/bin.
# make uninstall		Remove from /usr/local/bin.

CC=g++
LINKERFLAGS=

PROGRAM_NAME=livsdiary

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

all: $(SRCS_C) ${SRCS_CPP} $(PROGRAM_NAME)

$(OBJS_DIR):	
	@mkdir -p $(OBJS_DIR)

${SRCS_C}: $(OBJS_DIR) 
	$(CC) -c $(SRCS_DIR)$@.c -o $(OBJS_DIR)$@.o

$(SRCS_CPP): $(OBJS_DIR)
	$(CC) -c $(SRCS_DIR)$@.cpp -o $(OBJS_DIR)$@.o

$(PROGRAM_NAME): $(OBJS_DIR) 
	cd $(OBJS_DIR)
	$(CC) $(LINKERFLAGS) $(OBJS) -o ../$(PROGRAM_NAME).o 
	cd ..
	du -b $(PROGRAM_NAME).o

run: $(PROGRAM_NAME)
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
