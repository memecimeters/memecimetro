#!/usr/bin/python3
from PIL import Image

WIDTH = 84
HEIGHT = 48
ROWS = 6
ROW_SIZE = 8
MAX_OUT_WIDTH = 80
VAR_NAME = "frame"

VAR_DEC_MEMEDUINO = "static const char %s[%d][%d] PROGMEM = {"
VAR_DEC_SIMAVR = "const uint8_t %s[%d][%d] PROGMEM = {"

import sys

frames = []
for filename in sys.argv[1:]:

    im = Image.open(filename)
    assert im.size == (WIDTH, HEIGHT)


    colors = set()
    for x in range(WIDTH):
        for y in range(HEIGHT):
            p = im.getpixel((x, y))
            colors.add(p)

    assert len(colors) in (1, 2)
    colors = sorted(colors, key=lambda p: sum(p))
    fg, bg = colors

    for y in range(HEIGHT):
        for x in range(WIDTH):
            p = im.getpixel((x, y))
    #        print(" " if p == bg else "o", end="")
    #    print()

    data = []
    for r in range(ROWS):
        row = []
        for x in range(WIDTH):
            col = 0
            for y in range(ROW_SIZE):
                p = im.getpixel((x, y + r*ROW_SIZE))
                if p == fg:
                    col |= (1 << y)

            row.append(col)
        data.append(row)
    frames.append(data)

t = len(frames)

print(VAR_DEC_SIMAVR % (VAR_NAME, t, WIDTH*ROWS))
for data in frames:
    w = 0
    print("{")
    for r in data:
        for c in r:
            o = "0x%02x, " % c
            l = len(o)
            print(o, end="")
            w += l

            if w + l > MAX_OUT_WIDTH:
                w = 0
                print("")
    print("}, ")
print("};")
