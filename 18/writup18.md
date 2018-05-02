クッソ手こずった。
[ここ](https://qiita.com/knqyf263/items/6ebf06e27be7c48aab2e#the-sleuth-kiat)を参考に
ubuntuで
```
sudo mkdir /mnt/test
sudo mount drive.img /mnt/test/
sudo ls /mnt/test
```
すると、３つファイルが出てくる。
macで開いても勝手にマウントされるから同じ３つのファイルが出てくる。

しかしこれらのファイルは全く関係ない。

次に`fdisk`してパーティションをマウントしようとするもうまく行かず。

```
fdisk -lu drive.img
sudo mount -o loop,offset=1936269394*512 drive.img /mnt/test
```

testdisc, photorecも試すもよくわからん。

```
sudo apt-get testdisc
```

foremost を試すともう一枚画像が出現。
```
sudo apt -y install foremost
foremost drive.img
cd output/jpg/
```

The flag is in this file, but not in this image.
と書いてある。
が、どうすればいいかわからん。

最後に
FTK ImagerというのをWindowsに入れて、その画像を調べるとFileListというのがあり、そこに3文字づつFlagが書いてあった。


追記。
The Sleuth Kitを使える。
macなら`brew install autopsy`で入る。
`fls drive.imp`で中身が見れる。
```
r/r 4-128-4:    $AttrDef
r/r 8-128-2:    $BadClus
r/r 8-128-1:    $BadClus:$Bad
r/r 6-128-4:    $Bitmap
r/r 7-128-1:    $Boot
d/d 11-144-4:   $Extend
r/r 2-128-1:    $LogFile
r/r 0-128-1:    $MFT
r/r 1-128-1:    $MFTMirr
r/r 9-128-8:    $Secure:$SDS
r/r 9-144-11:   $Secure:$SDH
r/r 9-144-5:    $Secure:$SII
r/r 10-128-1:   $UpCase

r/r 3-128-3:    $Volume
r/r 35-128-1:   Carl Larsson Brita as Iduna.jpg
r/r 37-128-1:   Mona Lisa.jpg
r/r 38-128-1:   The Great Wave off Kanagawa.jpg
-/r * 36-128-1: Liberty Leading the People.jpg
-/r * 36-128-4: Liberty Leading the People.jpg:00
-/r * 36-128-5: Liberty Leading the People.jpg:01
-/r * 36-128-6: Liberty Leading the People.jpg:02
-/r * 36-128-7: Liberty Leading the People.jpg:03
-/r * 36-128-8: Liberty Leading the People.jpg:04
-/r * 36-128-9: Liberty Leading the People.jpg:05
-/r * 36-128-10:        Liberty Leading the People.jpg:06
V/V 256:        $OrphanFiles
```

Liberty Leading the People.jpg:00 ~ Liberty Leading the People.jpg:06
あたりが怪しいので、`icat`コマンドで取り出してみる。
icat.shを実行すれば、Flagファイルゲット。
