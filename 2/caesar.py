#! /usr/bin/env python

import sys

def rot_n(c, n):
    if 'a' <= c and c <= 'z':
        return chr((ord(c) - ord('a') + int(n)) % 26 + ord('a'))

    if 'A' <= c and c <= 'Z':
        return chr((ord(c) - ord('A') + int(n)) % 26 + ord('A'))

    return c

def rot(s, n):
    c = (rot_n(c, n) for c in s)
    print(''.join(c))

if __name__ == '__main__':
    param = sys.argv
    s = 'EBG KVVV vf n fvzcyr yrggre fhofgvghgvba pvcure gung ercynprf n yrggre jvgu gur yrggre KVVV yrggref nsgre vg va gur nycunorg. EBG KVVV vf na rknzcyr bs gur Pnrfne pvcure, qrirybcrq va napvrag Ebzr. Synt vf SYNTFjmtkOWFNZdjkkNH. Vafreg na haqrefpber vzzrqvngryl nsgre SYNT.'
    r = param[1]
    rot(s, r)
