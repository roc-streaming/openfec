#! /usr/bin/env python3
import fileinput
import glob
import os
import os.path
import re

os.chdir(os.path.dirname(__file__))

with open('.version') as fp:
    old_ver = fp.read().strip()

new_ver = '.'.join(old_ver.split('.')[:-1] + [str(int(old_ver.split('.')[-1])+1)])
new_minor = new_ver.split('.')[-1]

print(f'Bumping version from {old_ver} to {new_ver}')

with open('.version', 'w') as fp:
    fp.write(f'{new_ver}\n')

spec = list(sorted(glob.glob('rpm/*.spec')))[-1]
spec_ver = re.search('\w+-([.0-9]+).spec', spec).group(1)

for line in fileinput.input(files=[spec], inplace=True):
    if '%define' in line and 'minor' in line:
        line = re.sub(r'minor\s+\d+', f'minor {new_minor}', line)
    print(line, end='')

new_spec = spec.replace(spec_ver, new_ver)

os.rename(spec, new_spec)

print('Done.')
