#!/usr/bin/python3

import os
import sys

INCLUDE_DIR = 'gifs/'

if __name__ == '__main__':

    _, *files = sys.argv

    headers = []
    for f in files:
        name = os.path.basename(f)
        if not name.endswith('.h'):
            continue
        headers.append(name)

    for h in headers:
        print('#include "{dir}{file}"'.format(dir=INCLUDE_DIR, file=h))
