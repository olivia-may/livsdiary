### LIVSDiary - (LI)ghtweight (V)irtual (S)imple Diary
A command-line program that starts up fast and makes writing a virtual diary easy.
Only tested on GNU/Linux, most likely wont compile/run on other operating systems.
#### GNU/Linux
##### Archlinux based distros:
Get from the AUR.
https://aur.archlinux.org/packages/livsdiary
##### Other distros
Compile from source. Check that you have neovim's dependencies.

`git clone https://github.com/olivia-livs/livsdiary`

`cd livsdiary`

`make nvim` The linking for this will fail. That's alright though because we're linking nvim with LIVSDiary.

`make -j$(nproc)` Make LIVSDiary files, and link everything.

`./livsdiary` Check if nothing crashed horribly. Should be on Table of Contents page.

`sudo make install` (Optional) To install LIVSDiary to /usr/local/bin to be called from your shell.

`livsdiary --help` Try it out!

### Licenses
LIVSDiary has the GPLv3 license `LICENSE`. Neovim has the Apache 2.0 license and vim license. Read `src/neovim/LICENSE.txt` for more information.
