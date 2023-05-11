#!/usr/bin/env python

import shutil
import glob
import os

print('rm -rf muon/')
shutil.rmtree('muon/', ignore_errors=True)
print('rm -rf build/')
shutil.rmtree('build/', ignore_errors=True)
print('rm -f *.html')
remove_list = glob.glob('*.html')
for i in range(0, len(remove_list)):
    os.remove(remove_list[i])
