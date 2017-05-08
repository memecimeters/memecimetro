#!/usr/bin/python3

import math
import os
from subprocess import call

from PIL import Image

FRAMES_DIR = 'frames/'
BLACK = (0, 255,)

TO_SCALE = [
    ('font', (2, 3,)),  # font_x2, font_x3
#    ('corners', (16,)),  # corners_x16
]


class Sprite:
    def __init__(self, name, frames):
        print('constructing Sprite %s' % name)
        self.name = name
        self.frames = frames

        f0 = frames[0]
        self.w = f0.w
        self.h = f0.h
        self.n_rows = f0.n_rows
        self.frame_bytecount = f0.bytecount

        for frame in frames:
            frame.sprite = self
            assert frame.w == self.w
            assert frame.h == self.h

        self.len = len(frames)


class Frame:
    def __init__(self, im):
        self.im = im
        self.comment_lines = []
        self.roc = []
        self.hex = ""

        self.w, self.h = im.size
        self.n_rows = math.ceil(self.h / 8)
        self.bytecount = self.w * self.n_rows

        for _ in range(self.n_rows):
            self.roc.append([0 for _ in range(self.w)])

        for y in range(self.h):
            line = ""
            r = y // 8
            o = y - r * 8

            for x in range(self.w):
                p = im.getpixel((x, y))
                if p == BLACK:
                    self.roc[r][x] |= 1 << o

                line += (" ■" if p == BLACK else " □")

            self.comment_lines.append(line)

        self.hex = "{"
        for row in self.roc:
            for col in row:
                self.hex += " 0x%02x," % col
        self.hex += " }"





def find_gifs():
    spritenames = []

    # get gifs
    files = [f for f in os.listdir('.') if os.path.isfile(f)]
    for f in files:
        if not f.endswith('.gif'):
            continue
        s = f[:-4]
        spritenames.append(s)

    return spritenames

def explode(name):
    print('exploding %s' % name)

    call([
        'convert',
        '-coalesce',
        name + '.gif',
        FRAMES_DIR + name + '.%04d.png',
    ])


def scale(name, factors):
    files = [f for f in os.listdir(FRAMES_DIR) if os.path.isfile(FRAMES_DIR + f)]

    for factor in factors:
        print('scaling %s x%d' % (name, factor))
        for f in files:
            if not f.startswith(name):
                continue

            tail = f[len(name):]
            call([
                'convert',
                FRAMES_DIR + f,
                '-scale', str(factor*100) + '%',
                FRAMES_DIR + '%s_x%d' % (name, factor) + tail,
            ])


def explode_and_scale(spritenames, to_scale={}):
    # explode them into frames
    for name in spritenames:
        explode(name)

    # make scaled versions of sprites
    for name, factors in to_scale:
        if name not in spritenames:
            continue

        scale(name, factors)
        for factor in factors:
            spritenames.append('%s_x%d' % (name, factor))

    return spritenames


def read_sprites():
    sprite_frames = {}

    files = [f for f in os.listdir(FRAMES_DIR) if os.path.isfile(FRAMES_DIR + f)]
    for f in sorted(files):
        if not f.endswith('.png'):
            continue

        im = Image.open(FRAMES_DIR + f)
        name, frame, png = f.split('.')

        if name not in sprite_frames:
            sprite_frames[name] = []

        sprite_frames[name].append(Frame(im))

    sprites = []
    for name in sprite_frames.keys():
        sprites.append(Sprite(name, sprite_frames[name]))

    return sprites



def print_frame_comment(frame, out):
    for y, line in enumerate(frame.comment_lines):
        print("        //" + line, file=out)
        if y % 8 == 7:
            print(file=out)


def print_all_frames_comments(sprite, out):
    for index, frame in enumerate(sprite.frames):
        print("\n        // frame %d" % index, file=out)
        print_frame_comment(frame, out)


def print_sprite_header(sprite, out):

    print("#define %s_len %d" % (sprite.name, sprite.len), file=out)
    print("#define %s_w %d" % (sprite.name, sprite.w), file=out)
    print("#define %s_h %d" % (sprite.name, sprite.h), file=out)

    print("extern const char pgm_%s[%d][%d] PROGMEM;" % (
        sprite.name,
        sprite.len,
        sprite.frame_bytecount,
    ), file=out)
    print("void s_%s(char frame, char x, char y);" % sprite.name, file=out)
    print(file=out)


def print_sprite_pgm(sprite, out):

    print("const char pgm_%s[%d][%d] PROGMEM = {""" % (
        sprite.name,
        sprite.len,
        sprite.frame_bytecount,
    ), file=out)

    for frame in sprite.frames:
        print("        " + frame.hex +  ", ", file=out)
    print("    };", file=out)


def print_sprite_fun(sprite, out):
    print("void s_%s(char frame, char x, char y) {" % sprite.name, file=out)

    print("""
    char h = %d, r = %d, c = %d;
    """  % (sprite.h, sprite.n_rows, sprite.w), file=out)
    print_all_frames_comments(sprite, out);
    print("""
    blit_cols(pgm_%s[frame], h, r, c, x, y);
""" % sprite.name, file=out)

    print("};", file=out)



def codegen(sprites):
    print('generating sprites.h')
    with open("../src/sprites.h", "w") as f:
        print ("""/// generado por codegen_sprites.py
#ifndef _SPRITES_H
#define _SPRITES_H

#include <avr/pgmspace.h>

void blit_cols(const char *p, char h, char r, char c, char x, char y);
""", file=f)

        for sprite in sprites:
            print_sprite_header(sprite, f)

        print("""

#endif""", file=f)

    print('generating sprites.cpp')
    with open("../src/sprites.cpp", "w") as f:
        print("""/// generado por codegen_sprites.py
#include "sprites.h"
#include "LCD_Functions.h"

void blit_cols(const char *p, char h, char r, char c, char x, char y) {
    // TODO: optimizar, cachos de columna en vez de pixel a pixel
    char i, j, t, b;
    for(t=0; t<r; t++) {
        for(i=0; i<c; i++) {
            for(j=0; j<8; j++) {
                b = pgm_read_byte(p+i+t*c);
                if (b & (1 << j)) {
                    setPixel (x+i, y+j+t*8);
                }
            }
        }
    }
};""", file=f)

        for sprite in sprites:
            print_sprite_pgm(sprite, f)
            print_sprite_fun(sprite, f)


if __name__ == '__main__':
    spritenames = find_gifs()
    explode_and_scale(spritenames, TO_SCALE)
    codegen(read_sprites())
