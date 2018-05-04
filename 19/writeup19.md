zip の脆弱性を調べてみると、[既知平文攻撃](http://www.stockdog.work/entry/2017/07/09/131657)というのがあるらしい。
zipファイルの中にあるファイルの中身を一つでも知っていたらパスワードが分かってしまうらしい。怖い。
今回の問題では、`unzip`コマンドを叩くとパスワードを求められ、何も入力せずにエンターを押すと
`flag.html`と`Standard-lock-key.jpg`というファイルが中にあることがわかる。

もう`Standard-lock-key.jpg`とか絶対ネットに転がってるやつやんと思ったら案の定転がっていた。(https://ja.wikipedia.org/wiki/%E3%83%95%E3%82%A1%E3%82%A4%E3%83%AB:Standard-lock-key.jpg)
ここの画像を保存し、
`pkcrack -C flag.zip -c Standard-lock-key.jpg -p Standard-lock-key.jpg -d flag2.zip`
と叩いた。`pkcrack`は`brew install pkcrack`でmacにインストールできる。

しかし、最初は失敗した。
ファイルのサイズが間違っているのかと思い、ファイルサイズを調べてみる。
`binwalk flag.zip`とすると
`Standard-lock-key.jpg`のファイルサイズは255964。`binwalk`も`brew install binwalk`でいけるはず。
先ほどダウンロードしたファイルははるかに小さいサイズとなっていた。
先のWikiで他のサイズがあるかと探すと、元ファイルというのがあったのでそれを保存。サイズは255964でビンゴ。
もう一度`pkcrack`を叩くと成功。Flagゲット。
