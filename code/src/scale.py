#!/usr/bin/python3

import os
import sys

from PIL import Image

GEN_DIR = 'gifs/'
GIF_EXT = '.gif'

def split(im):
    ims = []

    while True:
        try:
            ims.append(im.copy())
            im.seek(im.tell() + 1)
        except EOFError:
            break

    return ims

def scale(im, f):
    w, h = im.size
    return im.resize((w * f, h * f))

if __name__ == '__main__':

    if len(sys.argv) != 3:
        print('Usage: ./scale.py sprite.gif FACTOR')
        exit(1)

    _, path, factor = sys.argv

    name = os.path.basename(path)
    assert name.endswith(GIF_EXT)
    assert all([c.isdigit() for c in factor])
    factor = int(factor)
    assert factor > 1
    name = name[:len(GIF_EXT)]
    name += '_x%d' % factor

    gif = Image.open(path)
    ims = [scale(frame, factor) for frame in split(gif)]

    ims[0].save(GEN_DIR + name + GIF_EXT, save_all=True, append_images=ims[1:])
