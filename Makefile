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
# make SOURCE CODE FILE		Make the object for that source code file. Ex: 'make main.cpp'.
# make clean			Remove all object files
# make remove-user-files	Remove livsdiary files in home directory.
# make install			Install to /usr/local/bin.
# make uninstall		Remove from /usr/local/bin.

CC=gcc
CPP=g++
LINKERFLAGS1=-L/usr/local/lib -Wl,--as-needed
LINKERFLAGS2=-lgtk-x11-2.0 -lgdk-x11-2.0 -lpangocairo-1.0 -latk-1.0 -lcairo -lgdk_pixbuf-2.0 -lgio-2.0 -lpangoft2-1.0 -lpango-1.0 -lgobject-2.0 -lglib-2.0 -lharfbuzz -lfontconfig -lfreetype  -lSM -lICE -lXpm -lXt -lX11 -lXdmcp -lSM -lICE  -lm -ltinfo -lelf  -lsodium  -lacl -lattr -lgpm

PROGRAM_NAME=livsdiary
PROGRAM_VERSION=v1.3.0
# where the diary is stored in the home directory '~/.livsdiary/'
PROGRAM_DIR=/.livsdiary/

MAIN_DIR=$(shell pwd)/
SRCS_DIR=$(MAIN_DIR)src/
OBJS_DIR=$(MAIN_DIR)obj/

VIM_MAIN_DIR=$(SRCS_DIR)vim/
VIM_MAKEFILE_DIR=$(VIM_MAIN_DIR)src/
VIM_OBJS_DIR=$(VIM_MAIN_DIR)src/objects/

SRCS_C=\
	converters.c \
	filesystem.c \
	time.c

SRCS_CPP=\
	main.cpp \
	page.cpp

OBJS=\
	$(OBJS_DIR)converters.o \
	$(OBJS_DIR)filesystem.o \
	$(OBJS_DIR)main.o \
	$(OBJS_DIR)page.o \
	$(OBJS_DIR)time.o \
	$(VIM_OBJS_DIR)alloc.o \
	$(VIM_OBJS_DIR)arabic.o \
	$(VIM_OBJS_DIR)arglist.o \
	$(VIM_OBJS_DIR)autocmd.o \
	$(VIM_OBJS_DIR)beval.o \
	$(VIM_OBJS_DIR)blob.o \
	$(VIM_OBJS_DIR)blowfish.o \
	$(VIM_OBJS_DIR)buffer.o \
	$(VIM_OBJS_DIR)change.o \
	$(VIM_OBJS_DIR)channel.o \
	$(VIM_OBJS_DIR)charset.o \
	$(VIM_OBJS_DIR)cindent.o \
	$(VIM_OBJS_DIR)clientserver.o \
	$(VIM_OBJS_DIR)clipboard.o \
	$(VIM_OBJS_DIR)cmdexpand.o \
	$(VIM_OBJS_DIR)cmdhist.o \
	$(VIM_OBJS_DIR)crypt.o \
	$(VIM_OBJS_DIR)crypt_zip.o \
	$(VIM_OBJS_DIR)debugger.o \
	$(VIM_OBJS_DIR)dict.o \
	$(VIM_OBJS_DIR)diff.o \
	$(VIM_OBJS_DIR)digraph.o \
	$(VIM_OBJS_DIR)drawline.o \
	$(VIM_OBJS_DIR)drawscreen.o \
	$(VIM_OBJS_DIR)edit.o \
	$(VIM_OBJS_DIR)eval.o \
	$(VIM_OBJS_DIR)evalbuffer.o \
	$(VIM_OBJS_DIR)evalfunc.o \
	$(VIM_OBJS_DIR)evalvars.o \
	$(VIM_OBJS_DIR)evalwindow.o \
	$(VIM_OBJS_DIR)ex_cmds.o \
	$(VIM_OBJS_DIR)ex_cmds2.o \
	$(VIM_OBJS_DIR)ex_docmd.o \
	$(VIM_OBJS_DIR)ex_eval.o \
	$(VIM_OBJS_DIR)ex_getln.o \
	$(VIM_OBJS_DIR)fileio.o \
	$(VIM_OBJS_DIR)filepath.o \
	$(VIM_OBJS_DIR)findfile.o \
	$(VIM_OBJS_DIR)float.o \
	$(VIM_OBJS_DIR)fold.o \
	$(VIM_OBJS_DIR)getchar.o \
	$(VIM_OBJS_DIR)gui.o \
	$(VIM_OBJS_DIR)gui_beval.o \
	$(VIM_OBJS_DIR)gui_gtk.o \
	$(VIM_OBJS_DIR)gui_gtk_f.o \
	$(VIM_OBJS_DIR)gui_gtk_gresources.o \
	$(VIM_OBJS_DIR)gui_gtk_x11.o \
	$(VIM_OBJS_DIR)gui_xim.o \
	$(VIM_OBJS_DIR)hardcopy.o \
	$(VIM_OBJS_DIR)hashtab.o \
	$(VIM_OBJS_DIR)help.o \
	$(VIM_OBJS_DIR)highlight.o \
	$(VIM_OBJS_DIR)if_cscope.o \
	$(VIM_OBJS_DIR)if_xcmdsrv.o \
	$(VIM_OBJS_DIR)indent.o \
	$(VIM_OBJS_DIR)insexpand.o \
	$(VIM_OBJS_DIR)job.o \
	$(VIM_OBJS_DIR)json.o \
	$(VIM_OBJS_DIR)list.o \
	$(VIM_OBJS_DIR)locale.o \
	$(VIM_OBJS_DIR)logfile.o \
	$(VIM_OBJS_DIR)main.o \
	$(VIM_OBJS_DIR)map.o \
	$(VIM_OBJS_DIR)mark.o \
	$(VIM_OBJS_DIR)match.o \
	$(VIM_OBJS_DIR)mbyte.o \
	$(VIM_OBJS_DIR)memfile.o \
	$(VIM_OBJS_DIR)memline.o \
	$(VIM_OBJS_DIR)menu.o \
	$(VIM_OBJS_DIR)message.o \
	$(VIM_OBJS_DIR)misc1.o \
	$(VIM_OBJS_DIR)misc2.o \
	$(VIM_OBJS_DIR)mouse.o \
	$(VIM_OBJS_DIR)move.o \
	$(VIM_OBJS_DIR)netbeans.o \
	$(VIM_OBJS_DIR)normal.o \
	$(VIM_OBJS_DIR)ops.o \
	$(VIM_OBJS_DIR)option.o \
	$(VIM_OBJS_DIR)optionstr.o \
	$(VIM_OBJS_DIR)os_unix.o \
	$(VIM_OBJS_DIR)pathdef.o \
	$(VIM_OBJS_DIR)popupmenu.o \
	$(VIM_OBJS_DIR)popupwin.o \
	$(VIM_OBJS_DIR)profiler.o \
	$(VIM_OBJS_DIR)pty.o \
	$(VIM_OBJS_DIR)quickfix.o \
	$(VIM_OBJS_DIR)regexp.o \
	$(VIM_OBJS_DIR)register.o \
	$(VIM_OBJS_DIR)screen.o \
	$(VIM_OBJS_DIR)scriptfile.o \
	$(VIM_OBJS_DIR)search.o \
	$(VIM_OBJS_DIR)session.o \
	$(VIM_OBJS_DIR)sha256.o \
	$(VIM_OBJS_DIR)sign.o \
	$(VIM_OBJS_DIR)sound.o \
	$(VIM_OBJS_DIR)spell.o \
	$(VIM_OBJS_DIR)spellfile.o \
	$(VIM_OBJS_DIR)spellsuggest.o \
	$(VIM_OBJS_DIR)strings.o \
	$(VIM_OBJS_DIR)syntax.o \
	$(VIM_OBJS_DIR)tag.o \
	$(VIM_OBJS_DIR)term.o \
	$(VIM_OBJS_DIR)terminal.o \
	$(VIM_OBJS_DIR)testing.o \
	$(VIM_OBJS_DIR)textformat.o \
	$(VIM_OBJS_DIR)textobject.o \
	$(VIM_OBJS_DIR)textprop.o \
	$(VIM_OBJS_DIR)time.o \
	$(VIM_OBJS_DIR)typval.o \
	$(VIM_OBJS_DIR)ui.o \
	$(VIM_OBJS_DIR)undo.o \
	$(VIM_OBJS_DIR)usercmd.o \
	$(VIM_OBJS_DIR)userfunc.o \
	$(VIM_OBJS_DIR)version.o \
	$(VIM_OBJS_DIR)vim9class.o \
	$(VIM_OBJS_DIR)vim9cmds.o \
	$(VIM_OBJS_DIR)vim9compile.o \
	$(VIM_OBJS_DIR)vim9execute.o \
	$(VIM_OBJS_DIR)vim9expr.o \
	$(VIM_OBJS_DIR)vim9instr.o \
	$(VIM_OBJS_DIR)vim9script.o \
	$(VIM_OBJS_DIR)vim9type.o \
	$(VIM_OBJS_DIR)viminfo.o \
	$(VIM_OBJS_DIR)window.o \
	$(VIM_OBJS_DIR)bufwrite.o \
	$(VIM_OBJS_DIR)vterm_encoding.o \
	$(VIM_OBJS_DIR)vterm_keyboard.o \
	$(VIM_OBJS_DIR)vterm_mouse.o \
	$(VIM_OBJS_DIR)vterm_parser.o \
	$(VIM_OBJS_DIR)vterm_pen.o \
	$(VIM_OBJS_DIR)vterm_screen.o \
	$(VIM_OBJS_DIR)vterm_state.o \
	$(VIM_OBJS_DIR)vterm_unicode.o \
	$(VIM_OBJS_DIR)vterm_vterm.o \
	$(VIM_OBJS_DIR)xdiffi.o \
	$(VIM_OBJS_DIR)xemit.o \
	$(VIM_OBJS_DIR)xhistogram.o \
	$(VIM_OBJS_DIR)xpatience.o \
	$(VIM_OBJS_DIR)xprepare.o \
	$(VIM_OBJS_DIR)xutils.o

.PHONY=all run clean remove-user-files install uninstall

all: ${SRCS_C} ${SRCS_CPP} vim $(PROGRAM_NAME)

program.h:
	@echo -en "\n/* This file was generated by ../Makefile */\n\n#define PROGRAM_NAME \"$(PROGRAM_NAME)\"\n#define PROGRAM_VERSION \"$(PROGRAM_VERSION)\"\n#define PROGRAM_DIR \"$(PROGRAM_DIR)\"\n" > $(SRCS_DIR)program.h

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR) 

${SRCS_C}: $(OBJS_DIR) program.h
	$(CC) -c $(SRCS_DIR)$@ -o $(OBJS_DIR)$@.o

${SRCS_CPP}: $(OBJS_DIR) program.h
	$(CPP) -c $(SRCS_DIR)$@ -o $(OBJS_DIR)$@.o

vim:
	make -j$(nproc) --directory=$(VIM_MAKEFILE_DIR)

$(PROGRAM_NAME): program.h
	$(CPP) $(LINKERFLAGS1) $(OBJS) $(LINKERFLAGS2) -o $(MAIN_DIR)$(PROGRAM_NAME).o
	du -b $(PROGRAM_NAME).o

run: all 
	./$(PROGRAM_NAME).o

clean:
	rm -f ./{*.out,*.o} $(SRCS_DIR){*.out,*.o}
	rm -rf $(OBJS_DIR)
	make --directory=$(VIM_MAKEFILE_DIR) clean

remove-user-files:
	rm -rf ~/.livsdiary

# Must be root user for both
install: $(PROGRAM_NAME)
	install -D $(PROGRAM_NAME).o /usr/local/bin/$(PROGRAM_NAME)

uninstall:
	rm -f /usr/local/bin/$(PROGRAM_NAME)
