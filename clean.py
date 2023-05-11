#!/usr/bin/env python

import shutil

print('rm -rf muon/')
shutil.rmtree('muon/', ignore_errors=True)
print('rm -rf build/')
shutil.rmtree('build/', ignore_errors=True)
