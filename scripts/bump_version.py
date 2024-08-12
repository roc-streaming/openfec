#! /usr/bin/env python3
import fileinput
import glob
import os
import os.path
import re

os.chdir(os.path.dirname(__file__))

with open('.version') as fp:
    old_ver = fp.read().strip()

new_ver = '.'.join(old_ver.split('.')[:-1] + \
                   [str(int(old_ver.split('.')[-1])+1)])

print(f'Bumping version from {old_ver} to {new_ver}')

with open('.version', 'w') as fp:
    fp.write(f'{new_ver}\n')

for line in fileinput.input(files=['rpm/openfec.spec'], inplace=True):
    m = re.match('^(Version:\s+).*$', line)
    if m:
        line = m.group(1) + new_ver + '\n'
    print(line, end='')

print('Done.')
