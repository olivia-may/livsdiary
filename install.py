#!/usr/bin/env python

import os

print('muon setup build')
os.system('muon setup build')
print('cd build/')
os.chdir('build/')
print('ninja')
os.system('ninja')
print('muon install')
os.system('muon install')
print('cp ../livsdiary.desktop /usr/share/applications/')
os.system('cp ../livsdiary.desktop /usr/share/applications/')
