#!/usr/bin/env python

import os

print('git clone https://git.sr.ht/~lattis/muon/')
os.system('git clone https://git.sr.ht/~lattis/muon/')
print('cd muon/')
os.chdir('muon/')
print('meson setup build')
os.system('meson setup build')
print('cd build')
os.chdir('build')
print('ninja')
os.system('ninja')
print('meson test')
os.system('meson test')
print('meson install')
os.system('meson install')
