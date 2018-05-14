#2

##問題

```
EBG KVVV vf n fvzcyr yrggre fhofgvghgvba pvcure gung ercynprf n yrggre jvgu gur yrggre KVVV yrggref nsgre vg va gur nycunorg. EBG KVVV vf na rknzcyr bs gur Pnrfne pvcure, qrirybcrq va napvrag Ebzr. Synt vf SYNTFjmtkOWFNZdjkkNH. Vafreg na haqrefpber vzzrqvngryl nsgre SYNT.
```

##解法

アルファベットしか使われていない上、文構造が伺えるので、換字式暗号を疑う。  
となると、一文字のnはaだろうなとか、2文字のvfとかbsとかnaとかのどれかがisなんだろうな、とか考える。  
一つずつ当てはめて推測しても良いが、換字式暗号ではシーザー暗号が有名なので、とりあえず試してみる。  

拾い物のシーザー暗号のpythonスクリプトに、暗号文を埋め込む。

```caesor.py
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
```

このスクリプトに、0~25の引数を与えるシェルスクリプトを書いて、実行

```q2.sh
#!/bin/sh
for((i=0;i<26;i++))
do
	echo "$i"
	./caesar.py $i
done
```

```
0
EBG KVVV vf n fvzcyr yrggre fhofgvghgvba pvcure gung ercynprf n yrggre jvgu gur yrggre KVVV yrggref nsgre vg va gur nycunorg. EBG KVVV vf na rknzcyr bs gur Pnrfne pvcure, qrirybcrq va napvrag Ebzr. Synt vf SYNTFjmtkOWFNZdjkkNH. Vafreg na haqrefpber vzzrqvngryl nsgre SYNT.
1
FCH LWWW wg o gwadzs zshhsf gipghwhihwcb qwdvsf hvoh fsdzoqsg o zshhsf kwhv hvs zshhsf LWWW zshhsfg othsf wh wb hvs ozdvopsh. FCH LWWW wg ob sloadzs ct hvs Qosgof qwdvsf, rsjszcdsr wb obqwsbh Fcas. Tzou wg TZOUGknulPXGOAekllOI. Wbgsfh ob ibrsfgqcfs waasrwohszm othsf TZOU.
2
GDI MXXX xh p hxbeat atiitg hjqhixijixdc rxewtg iwpi gteaprth p atiitg lxiw iwt atiitg MXXX atiitgh puitg xi xc iwt paewpqti. GDI MXXX xh pc tmpbeat du iwt Rpthpg rxewtg, stktadets xc pcrxtci Gdbt. Uapv xh UAPVHlovmQYHPBflmmPJ. Xchtgi pc jcstghrdgt xbbtsxpitan puitg UAPV.
3
HEJ NYYY yi q iycfbu bujjuh ikrijyjkjyed syfxuh jxqj hufbqsui q bujjuh myjx jxu bujjuh NYYY bujjuhi qvjuh yj yd jxu qbfxqruj. HEJ NYYY yi qd unqcfbu ev jxu Squiqh syfxuh, tulubefut yd qdsyudj Hecu. Vbqw yi VBQWImpwnRZIQCgmnnQK. Ydiuhj qd kdtuhisehu yccutyqjubo qvjuh VBQW.

.
.
.
(以下略)

```

13文字ずらすシーザー暗号の時に、意味の通じる文章になったので、Flagゲット。
