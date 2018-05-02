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
