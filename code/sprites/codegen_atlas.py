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
    print("void s_%s(char frame, char x, char y);" % varname, file=out)
    print(file=out)

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

    char rocbufs[%d][%d] = {"""  % (sprite['h'], rows, cols, frames, size), file=out)
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

with open("../src/atlas_gen.h", "w") as f:
    print ("""/// generado por atlas_codegen.py

void blit_cols(char *p, char h, char r, char c, char x, char y) {
    // optimizar, cachos de columna en vez de pixel a pixel
    char i, j, t;
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

void _clear(char x, char y, char w, char h) {
    // TODO
};
""", file=f)

    for name in sorted(sprites.keys()):
        sprite_to_header(name, sprites[name], f)
        sprite_to_fun(name, sprites[name], f)
