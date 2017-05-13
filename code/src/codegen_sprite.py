#!/usr/bin/python3

import os
import sys
import math

from PIL import Image

GEN_DIR = 'gifs/'
BLACK = 1


class Sprite:
    def __init__(self, name, im, scale=1):
        self.name = name
        self.uppername = name.upper()


        frames = []

        while True:

            frame = Frame(im.copy(), scale)

            frame.sprite = self
            frames.append(frame)

            try:
                im.seek(im.tell() + 1)
            except EOFError:
                break

        self.frames = frames


        self.len = len(frames)

        f0 = frames[0]
        self.w = f0.w
        self.h = f0.h

        self.n_rows = math.ceil(self.h / 8)
        self.frame_bytecount = self.w * self.n_rows



class Frame:
    def __init__(self, im, scale):
        self.comment_lines = []
        self.roc = []
        self.hex = ''

        if scale > 1:
            w, h = im.size
            im = im.resize((w * scale, h * scale))

        self.w, self.h = im.size

        self.n_rows = math.ceil(self.h / 8)

        for _ in range(self.n_rows):
            self.roc.append([0 for _ in range(self.w)])

        for y in range(self.h):
            line = ''
            r = y // 8
            o = y - r * 8

            for x in range(self.w):
                p = im.getpixel((x, y))
                if p == BLACK:
                    self.roc[r][x] |= 1 << o

                line += (' ■' if p == BLACK else ' □')

            self.comment_lines.append(line)

        self.hex = '{'
        for row in self.roc:
            for col in row:
                self.hex += ' 0x%02x,' % col
        self.hex += ' }'


def codegen(sprite):
    with open(GEN_DIR + '%s.h' % sprite.name, 'w', encoding='utf-8') as f:
        f.write('''
#ifndef _GEN_SPRITE_{uppername}_H
#define _GEN_SPRITE_{uppername}_H

#include <avr/pgmspace.h>

#define {name}_len {len}
#define {name}_w {w}
#define {name}_h {h}

extern const unsigned char pgm_{name}[{len}][{frame_bytecount}] PROGMEM;
void s_{name}(unsigned char frame, char x, char y);

#endif
'''.format(**sprite.__dict__))


    with open(GEN_DIR + '%s.cpp' % sprite.name, 'w', encoding='utf-8') as f:
        f.write('''
#include "%s.h"
#include "../blit_cols.h"
#include <avr/pgmspace.h>
''' % sprite.name)

        write_sprite_pgm(sprite, f)
        write_sprite_fun(sprite, f)


def write_sprite_pgm(sprite, f):

    f.write('''const unsigned char pgm_%s[%d][%d] PROGMEM = {
''' % (
        sprite.name,
        sprite.len,
        sprite.frame_bytecount,
    ))

    for frame in sprite.frames:
        f.write('     ' + frame.hex +  ', \n')
    f.write('};\n')


def write_sprite_fun(sprite, f):

    f.write('void s_%s(unsigned char frame, char x, char y) {\n' % sprite.name)

    f.write('''
    char h = %d, r = %d, c = %d;
    '''  % (sprite.h, sprite.n_rows, sprite.w))

    for index, frame in enumerate(sprite.frames):
        f.write('\n    // frame %d\n' % index)
        for y, line in enumerate(frame.comment_lines):
            f.write('    //' + line + '\n')
            if y % 8 == 7:
                f.write('\n')

    f.write('''
    blit_cols(pgm_%s[frame], h, r, c, x, y);
''' % sprite.name)

    f.write('};\n')



if __name__ == '__main__':

    if len(sys.argv) < 2:
        print('Usage: ./codegen_sprite.py sprite.gif [FACTOR]')
        exit(1)

    path = sys.argv[1]

    name = os.path.basename(path)
    assert name.endswith('.gif')
    name = name[:-4]

    factor = 1
    if len(sys.argv) > 2:
        factor = int(sys.argv[2])
        name += '_x%d' % factor

    sp = Sprite(name, Image.open(path), scale=factor)

    codegen(sp)
