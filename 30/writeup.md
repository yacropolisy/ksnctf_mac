phpのstrcasecmpの使い方に脆弱性があるらしい。
ここでリクエストがpassword[]と配列にするとFalseになるというもの。

なのでフォームを送信するときのリクエストを
`password = '打ち込んだパスワード'`から
`password[] = '打ち込んだパスワード'`に書き換えればよい

リクエストを書き換える方法を死ぬほど調べた。
Fiddlerを使うと、filterタブで break request on POSTにチェックをいれ、
その状態でパスワードを送信し、BreakしたところでInspectorsタブのtextviewの中身を書き換えて
`Run to completion`をクリックすると書き換えたリクエストが送信される。

ChromeのDeveloper toolでもできる。
Elementsタブの状態でソースコードをダブルクリックすると編集できるので、
name="password"となっているところをname="password[]"と書き換えればよい。
こんな簡単に書き換えられるとか怖すぎ。
