#!/usr/bin/python3

import json
import math

from PIL import Image


MAX_OUT_WIDTH = 80
BLACK = (0, 0, 0, 255,)


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

def sprite_to_header(varname, sprite, out):
    frames = len(sprite['frames'])
    print("#define %s_len %d" % (varname, frames), file=out)
    print("void s_%s(uint8_t frame, uint8_t x, uint8_t y);" % varname, file=out)
    print(file=out)

def sprite_to_fun(varname, sprite, out):
    rocs = sprite_to_rocs(sprite)
    roc = rocs[0]
    rows = len(roc)
    cols = len(roc[0])
    size = rows * cols
    frames = len(rocs)
    print("#define %s_len %d" % (varname, frames), file=out)
    print("void s_%s(uint8_t frame, uint8_t x, uint8_t y) {" % varname, file=out)
    print("""
    uint8_t h = %d, r = %d, c = %d;

    uint8_t rocbufs[%d][%d] = {"""  % (sprite['h'], rows, cols, frames, size), file=out)
    for roc in rocs:
        print("        " + roc_to_hex(roc) +  ", ", file=out)
    print("    };", file=out)

    print("""
    blit_cols(rocbufs[frame], h, r, c, x, y);
""", file=out)

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

with open("atlas_gen.c", "w") as f:

    print ("""/// generado por atlas_codegen.py

void blit_cols(uint8_t *p, uint8_t h, uint8_t r, uint8_t c, uint8_t x, uint8_t y) {
    // optimizar, cachos de columna en vez de pixel a pixel
    uint8_t i, j, t;
    for(t=0; t<r; t++) {
        for(i=0; i<c; i++) {
            for(j=0; j<h; j++) {
                if (p[i+t*c] & (1 << j)) {
                    pcd8544_set_pixel_fb (x+i, y+j+t*8, PIXEL_STATE_ON);
                }
            }
        }
    }
};

void _clear(uint8_t x, uint8_t y, uint8_t w, uint8_t h) {
    // TODO
};
""", file=f)

    for name in sorted(sprites.keys()):
        sprite_to_fun(name, sprites[name], f)

with open("atlas_gen.h", "w") as f:
    print ("""/// generado por atlas_codegen.py
""", file=f)
    for name in sorted(sprites.keys()):
        sprite_to_header(name, sprites[name], f)
