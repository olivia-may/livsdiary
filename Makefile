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

PROGRAM_NAME=livsdiary
PROGRAM_VERSION=v1.3.0
# where the diary is stored in the home directory '~/.livsdiary/'
PROGRAM_DIR=/.livsdiary/

MAIN_DIR=$(shell pwd)/
SRCS_DIR=$(MAIN_DIR)src/
OBJS_DIR=$(MAIN_DIR)obj/

VIM_MAIN_DIR=$(SRCS_DIR)neovim/
VIM_MAKEFILE_DIR=$(VIM_MAIN_DIR)
VIM_OBJS_DIR=$(VIM_MAIN_DIR)build/src/nvim/CMakeFiles/nvim.dir/

CC=gcc
CPP=g++
LINKERFLAGS1=-DNVIM_TS_HAS_SET_MATCH_LIMIT -DNVIM_TS_HAS_SET_ALLOCATOR -g  -Wl,--no-undefined -Wl,--export-dynamic -rdynamic
LINKERFLAGS2=-fstack-protector-strong $(VIM_MAIN_DIR).deps/usr/lib/libluv.a $(VIM_MAIN_DIR).deps/usr/lib/libuv_a.a -ldl -lnsl -lrt $(VIM_MAIN_DIR).deps/usr/lib/libmsgpackc.a $(VIM_MAIN_DIR).deps/usr/lib/libvterm.a $(VIM_MAIN_DIR).deps/usr/lib/libtermkey.a $(VIM_MAIN_DIR).deps/usr/lib/libunibilium.a $(VIM_MAIN_DIR).deps/usr/lib/libtree-sitter.a -lm -lutil $(VIM_MAIN_DIR).deps/usr/lib/libluajit-5.1.a

SRCS_C=\
	converters.c \
	filesystem.c \
	time.c

SRCS_CPP=\
	main.cpp \
	page.cpp

OBJS=\
	$(OBJS_DIR)converters.c.o \
	$(OBJS_DIR)filesystem.c.o \
	$(OBJS_DIR)main.cpp.o \
	$(OBJS_DIR)page.cpp.o \
	$(OBJS_DIR)time.c.o \
	$(VIM_OBJS_DIR)__/__/cmake.config/auto/pathdef.c.o \
	$(VIM_OBJS_DIR)__/cjson/fpconv.c.o \
	$(VIM_OBJS_DIR)__/cjson/lua_cjson.c.o \
	$(VIM_OBJS_DIR)__/cjson/strbuf.c.o \
	$(VIM_OBJS_DIR)__/mpack/conv.c.o \
	$(VIM_OBJS_DIR)__/mpack/lmpack.c.o \
	$(VIM_OBJS_DIR)__/mpack/mpack_core.c.o \
	$(VIM_OBJS_DIR)__/mpack/object.c.o \
	$(VIM_OBJS_DIR)__/mpack/rpc.c.o \
	$(VIM_OBJS_DIR)__/xdiff/xdiffi.c.o \
	$(VIM_OBJS_DIR)__/xdiff/xemit.c.o \
	$(VIM_OBJS_DIR)__/xdiff/xhistogram.c.o \
	$(VIM_OBJS_DIR)__/xdiff/xpatience.c.o \
	$(VIM_OBJS_DIR)__/xdiff/xprepare.c.o \
	$(VIM_OBJS_DIR)__/xdiff/xutils.c.o \
	$(VIM_OBJS_DIR)api/autocmd.c.o \
	$(VIM_OBJS_DIR)api/buffer.c.o \
	$(VIM_OBJS_DIR)api/command.c.o \
	$(VIM_OBJS_DIR)api/deprecated.c.o \
	$(VIM_OBJS_DIR)api/extmark.c.o \
	$(VIM_OBJS_DIR)api/options.c.o \
	$(VIM_OBJS_DIR)api/private/converter.c.o \
	$(VIM_OBJS_DIR)api/private/dispatch.c.o \
	$(VIM_OBJS_DIR)api/private/helpers.c.o \
	$(VIM_OBJS_DIR)api/tabpage.c.o \
	$(VIM_OBJS_DIR)api/ui.c.o \
	$(VIM_OBJS_DIR)api/vim.c.o \
	$(VIM_OBJS_DIR)api/vimscript.c.o \
	$(VIM_OBJS_DIR)api/win_config.c.o \
	$(VIM_OBJS_DIR)api/window.c.o \
	$(VIM_OBJS_DIR)arabic.c.o \
	$(VIM_OBJS_DIR)arglist.c.o\
	$(VIM_OBJS_DIR)auto/lua_api_c_bindings.generated.c.o \
	$(VIM_OBJS_DIR)autocmd.c.o \
	$(VIM_OBJS_DIR)buffer.c.o \
	$(VIM_OBJS_DIR)buffer_updates.c.o \
	$(VIM_OBJS_DIR)change.c.o \
	$(VIM_OBJS_DIR)channel.c.o \
	$(VIM_OBJS_DIR)charset.c.o \
	$(VIM_OBJS_DIR)cmdexpand.c.o \
	$(VIM_OBJS_DIR)cmdhist.c.o \
	$(VIM_OBJS_DIR)context.c.o \
	$(VIM_OBJS_DIR)cursor.c.o \
	$(VIM_OBJS_DIR)cursor_shape.c.o \
	$(VIM_OBJS_DIR)debugger.c.o \
	$(VIM_OBJS_DIR)decoration.c.o \
	$(VIM_OBJS_DIR)decoration_provider.c.o \
	$(VIM_OBJS_DIR)diff.c.o \
	$(VIM_OBJS_DIR)digraph.c.o \
	$(VIM_OBJS_DIR)drawline.c.o \
	$(VIM_OBJS_DIR)drawscreen.c.o \
	$(VIM_OBJS_DIR)edit.c.o\
	$(VIM_OBJS_DIR)eval/decode.c.o \
	$(VIM_OBJS_DIR)eval/encode.c.o \
	$(VIM_OBJS_DIR)eval/executor.c.o \
	$(VIM_OBJS_DIR)eval/funcs.c.o \
	$(VIM_OBJS_DIR)eval/gc.c.o \
	$(VIM_OBJS_DIR)eval/typval.c.o \
	$(VIM_OBJS_DIR)eval/userfunc.c.o \
	$(VIM_OBJS_DIR)eval/vars.c.o \
	$(VIM_OBJS_DIR)eval.c.o \
	$(VIM_OBJS_DIR)event/libuv_process.c.o \
	$(VIM_OBJS_DIR)event/loop.c.o \
	$(VIM_OBJS_DIR)event/multiqueue.c.o \
	$(VIM_OBJS_DIR)event/process.c.o \
	$(VIM_OBJS_DIR)event/rstream.c.o \
	$(VIM_OBJS_DIR)event/signal.c.o \
	$(VIM_OBJS_DIR)event/socket.c.o \
	$(VIM_OBJS_DIR)event/stream.c.o \
	$(VIM_OBJS_DIR)event/time.c.o \
	$(VIM_OBJS_DIR)event/wstream.c.o \
	$(VIM_OBJS_DIR)ex_cmds.c.o \
	$(VIM_OBJS_DIR)ex_cmds2.c.o \
	$(VIM_OBJS_DIR)ex_docmd.c.o \
	$(VIM_OBJS_DIR)ex_eval.c.o \
	$(VIM_OBJS_DIR)ex_getln.c.o \
	$(VIM_OBJS_DIR)ex_session.c.o \
	$(VIM_OBJS_DIR)extmark.c.o \
	$(VIM_OBJS_DIR)file_search.c.o \
	$(VIM_OBJS_DIR)fileio.c.o \
	$(VIM_OBJS_DIR)fold.c.o \
	$(VIM_OBJS_DIR)garray.c.o \
	$(VIM_OBJS_DIR)getchar.c.o \
	$(VIM_OBJS_DIR)grid.c.o \
	$(VIM_OBJS_DIR)hardcopy.c.o \
	$(VIM_OBJS_DIR)hashtab.c.o \
	$(VIM_OBJS_DIR)help.c.o \
	$(VIM_OBJS_DIR)highlight.c.o \
	$(VIM_OBJS_DIR)highlight_group.c.o \
	$(VIM_OBJS_DIR)if_cscope.c.o \
	$(VIM_OBJS_DIR)indent.c.o \
	$(VIM_OBJS_DIR)indent_c.c.o \
	$(VIM_OBJS_DIR)input.c.o \
	$(VIM_OBJS_DIR)insexpand.c.o \
	$(VIM_OBJS_DIR)keycodes.c.o \
	$(VIM_OBJS_DIR)locale.c.o \
	$(VIM_OBJS_DIR)log.c.o \
	$(VIM_OBJS_DIR)lua/converter.c.o \
	$(VIM_OBJS_DIR)lua/executor.c.o\
	$(VIM_OBJS_DIR)lua/spell.c.o \
	$(VIM_OBJS_DIR)lua/stdlib.c.o \
	$(VIM_OBJS_DIR)lua/treesitter.c.o \
	$(VIM_OBJS_DIR)lua/xdiff.c.o \
	$(VIM_OBJS_DIR)main.c.o \
	$(VIM_OBJS_DIR)map.c.o \
	$(VIM_OBJS_DIR)mapping.c.o \
	$(VIM_OBJS_DIR)mark.c.o \
	$(VIM_OBJS_DIR)marktree.c.o \
	$(VIM_OBJS_DIR)match.c.o \
	$(VIM_OBJS_DIR)math.c.o \
	$(VIM_OBJS_DIR)mbyte.c.o \
	$(VIM_OBJS_DIR)memfile.c.o \
	$(VIM_OBJS_DIR)memline.c.o \
	$(VIM_OBJS_DIR)memory.c.o \
	$(VIM_OBJS_DIR)menu.c.o \
	$(VIM_OBJS_DIR)message.c.o \
	$(VIM_OBJS_DIR)mouse.c.o \
	$(VIM_OBJS_DIR)move.c.o \
	$(VIM_OBJS_DIR)msgpack_rpc/channel.c.o \
	$(VIM_OBJS_DIR)msgpack_rpc/helpers.c.o \
	$(VIM_OBJS_DIR)msgpack_rpc/server.c.o \
	$(VIM_OBJS_DIR)msgpack_rpc/unpacker.c.o \
	$(VIM_OBJS_DIR)normal.c.o \
	$(VIM_OBJS_DIR)ops.c.o \
	$(VIM_OBJS_DIR)option.c.o \
	$(VIM_OBJS_DIR)optionstr.c.o \
	$(VIM_OBJS_DIR)os/dl.c.o \
	$(VIM_OBJS_DIR)os/env.c.o \
	$(VIM_OBJS_DIR)os/fileio.c.o \
	$(VIM_OBJS_DIR)os/fs.c.o \
	$(VIM_OBJS_DIR)os/input.c.o \
	$(VIM_OBJS_DIR)os/lang.c.o \
	$(VIM_OBJS_DIR)os/mem.c.o \
	$(VIM_OBJS_DIR)os/process.c.o \
	$(VIM_OBJS_DIR)os/pty_process_unix.c.o \
	$(VIM_OBJS_DIR)os/shell.c.o \
	$(VIM_OBJS_DIR)os/signal.c.o \
	$(VIM_OBJS_DIR)os/stdpaths.c.o \
	$(VIM_OBJS_DIR)os/time.c.o \
	$(VIM_OBJS_DIR)os/tty.c.o \
	$(VIM_OBJS_DIR)os/users.c.o \
	$(VIM_OBJS_DIR)os_unix.c.o \
	$(VIM_OBJS_DIR)path.c.o \
	$(VIM_OBJS_DIR)plines.c.o \
	$(VIM_OBJS_DIR)popupmenu.c.o \
	$(VIM_OBJS_DIR)profile.c.o \
	$(VIM_OBJS_DIR)quickfix.c.o \
	$(VIM_OBJS_DIR)rbuffer.c.o \
	$(VIM_OBJS_DIR)regexp.c.o \
	$(VIM_OBJS_DIR)runtime.c.o \
	$(VIM_OBJS_DIR)screen.c.o \
	$(VIM_OBJS_DIR)search.c.o \
	$(VIM_OBJS_DIR)sha256.c.o \
	$(VIM_OBJS_DIR)shada.c.o \
	$(VIM_OBJS_DIR)sign.c.o \
	$(VIM_OBJS_DIR)spell.c.o \
	$(VIM_OBJS_DIR)spellfile.c.o \
	$(VIM_OBJS_DIR)spellsuggest.c.o \
	$(VIM_OBJS_DIR)state.c.o \
	$(VIM_OBJS_DIR)statusline.c.o \
	$(VIM_OBJS_DIR)strings.c.o \
	$(VIM_OBJS_DIR)syntax.c.o \
	$(VIM_OBJS_DIR)tag.c.o \
	$(VIM_OBJS_DIR)terminal.c.o \
	$(VIM_OBJS_DIR)testing.c.o \
	$(VIM_OBJS_DIR)textformat.c.o \
	$(VIM_OBJS_DIR)textobject.c.o \
	$(VIM_OBJS_DIR)tui/input.c.o \
	$(VIM_OBJS_DIR)tui/terminfo.c.o \
	$(VIM_OBJS_DIR)tui/tui.c.o \
	$(VIM_OBJS_DIR)ugrid.c.o \
	$(VIM_OBJS_DIR)ui.c.o \
	$(VIM_OBJS_DIR)ui_bridge.c.o \
	$(VIM_OBJS_DIR)ui_client.c.o \
	$(VIM_OBJS_DIR)ui_compositor.c.o \
	$(VIM_OBJS_DIR)undo.c.o \
	$(VIM_OBJS_DIR)usercmd.c.o \
	$(VIM_OBJS_DIR)version.c.o \
	$(VIM_OBJS_DIR)viml/parser/expressions.c.o \
	$(VIM_OBJS_DIR)viml/parser/parser.c.o \
	$(VIM_OBJS_DIR)window.c.o

.PHONY=all run clean help vim nvim neovim remove-user-files install uninstall

all: ${SRCS_C} ${SRCS_CPP} $(PROGRAM_NAME)

program.h:
	@echo -en "\n/* This file was generated by ../Makefile */\n\n#define PROGRAM_NAME \"$(PROGRAM_NAME)\"\n#define PROGRAM_VERSION \"$(PROGRAM_VERSION)\"\n#define PROGRAM_DIR \"$(PROGRAM_DIR)\"\n" > $(SRCS_DIR)program.h

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR) 

${SRCS_C}: $(OBJS_DIR) program.h
	$(CC) -c $(SRCS_DIR)$@ -o $(OBJS_DIR)$@.o

${SRCS_CPP}: $(OBJS_DIR) program.h
	$(CPP) -c $(SRCS_DIR)$@ -o $(OBJS_DIR)$@.o

vim nvim neovim:
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

help:
	@printf "LIVSDiary Makefile help\n"

remove-user-files:
	rm -rf ~$(PROGRAM_DIR)

# Must be root user for both
install: $(PROGRAM_NAME)
	install -D $(PROGRAM_NAME).o /usr/local/bin/$(PROGRAM_NAME)

uninstall:
	rm -f /usr/local/bin/$(PROGRAM_NAME)
