#!/usr/bin/python3

import json
import math

from PIL import Image


MAX_OUT_WIDTH = 80
BLACK = (0, 0, 0, 255,)

def print_img(im, out):
    w, h = im.size
    for y in range(h):
        print("        //", end="", file=out)
        for x in range(w):
            p = im.getpixel((x, y))
            print(" ■" if p == BLACK else " □", end="", file=out)
        print(file=out)
        if y % 8 == 7:
            print(file=out)

def img_to_roc(im):
    w, h = im.size
    n_rows = math.ceil(h / 8)
    rows = []
    for _ in range(n_rows):
        rows.append([0 for _ in range(w)])

    for y in range(h):
        r = y // 8
        o = y - r*8
        for x in range(w):
            if im.getpixel((x, y)) == BLACK:
                rows[r][x] |= 1 << o
    return rows


def roc_to_hex(roc):
    o = "{"
    for row in roc:
        for col in row:
            o += " 0x%02x," % col
    o += " }"

    return o


def sprite_to_rocs(sprite):
    rocs = []
    for index in sorted(sprite['frames'].keys()):
        pos = sprite['frames'][index]
        im = sheet.crop((
            pos['x'],
            pos['y'],
            pos['x'] + sprite['w'],
            pos['y'] + sprite['h'],
        ))
        rocs.append(img_to_roc(im))
    return rocs

def print_sprite_imgs(sprite, out):
    rocs = []
    for index in sorted(sprite['frames'].keys()):
        print("\n        // frame %d" % index, file=out)
        pos = sprite['frames'][index]
        im = sheet.crop((
            pos['x'],
            pos['y'],
            pos['x'] + sprite['w'],
            pos['y'] + sprite['h'],
        ))
        print_img(im, out)
    return rocs

def sprite_to_header(varname, sprite, out):
    w = sprite['w']
    h = sprite['h']
    frames = len(sprite['frames'])
    print("#define %s_len %d" % (varname, frames), file=out)
    print("#define %s_w %d" % (varname, w), file=out)
    print("#define %s_h %d" % (varname, h), file=out)

    print("extern const char pgm_%s[%d][%d] PROGMEM;" % (
        varname,
        frames,
        w*math.ceil(h/8),
    ), file=out)
    print("void s_%s(char frame, char x, char y);" % varname, file=out)
    print(file=out)

def sprite_to_pgm(varname, sprite, out):
    rocs = sprite_to_rocs(sprite)
    roc = rocs[0]
    rows = len(roc)
    cols = len(roc[0])
    size = rows * cols
    frames = len(rocs)

    print("const char pgm_%s[%d][%d] PROGMEM = {""" % (
        varname,
        frames,
        size,
    ), file=out)

    for roc in rocs:
        print("        " + roc_to_hex(roc) +  ", ", file=out)
    print("    };", file=out)



def sprite_to_fun(varname, sprite, out):
    rocs = sprite_to_rocs(sprite)
    roc = rocs[0]
    rows = len(roc)
    cols = len(roc[0])
    size = rows * cols
    frames = len(rocs)
    print("#define %s_len %d" % (varname, frames), file=out)
    print("void s_%s(char frame, char x, char y) {" % varname, file=out)

    print("""
    char h = %d, r = %d, c = %d;
    """  % (sprite['h'], rows, cols), file=out)
    print_sprite_imgs(sprite, out);
    print("""
    blit_cols(pgm_%s[frame], h, r, c, x, y);
""" % varname, file=out)

    print("};", file=out)


with open("atlas.json") as f:
    data = json.load(f)

sheet = Image.open("atlas.png")

sprites = {}

for fname, fdata in data['frames'].items():
    spritename, index = fname.split(' ')
    index = int(index.split('.ase')[0])

    sprite = sprites.get(spritename, {
        'frames': {},
        'h': fdata['frame']['h'],
        'w': fdata['frame']['w'],
    })

    sprite['frames'][index] = {
        'x': fdata['frame']['x'],
        'y': fdata['frame']['y'],
    }

    sprites[spritename] = sprite

with open("../src/atlas_gen.h", "w") as f:
    print ("""/// generado por atlas_codegen.py
#ifndef _ATLAS_GEN_H
#define _ATLAS_GEN_H

#include <avr/pgmspace.h>

void blit_cols(const char *p, char h, char r, char c, char x, char y);
""", file=f)

    for name in sorted(sprites.keys()):
        sprite_to_header(name, sprites[name], f)

    print("""

#endif""", file=f)

with open("../src/atlas_gen.cpp", "w") as f:
    print("""/// generado por atlas_codegen.py
#include "atlas_gen.h"
#include "LCD_Functions.h"

void blit_cols(const char *p, char h, char r, char c, char x, char y) {
    // optimizar, cachos de columna en vez de pixel a pixel
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

    for name in sorted(sprites.keys()):
        sprite_to_pgm(name, sprites[name], f)
        sprite_to_fun(name, sprites[name], f)
