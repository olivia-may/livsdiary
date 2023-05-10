#!/usr/bin/env python

import os

os.system('git clone https://git.sr.ht/~lattis/muon/')
os.chdir('muon')
os.system('meson setup build')
os.chdir('build')
os.system('ninja')
os.system('meson test')
os.system('meson install')
