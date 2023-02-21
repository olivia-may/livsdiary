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
	rm -f livsdiary.o src/{*.out,*.o}

remove-user-files:
	rm -rf ~/.livsdiary

# Must be root user for the following
install: compile
	cp livsdiary.o /usr/local/bin/livsdiary

uninstall:
	rm -f /usr/local/bin/livsdiary
