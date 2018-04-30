linuxのユーザのパスワードらしい
/etc/shadowで調べると良い

john the ripperという有名なツールがあるらしい

Linuxで
`apt-get install john`で手に入る
辞書を用いてやる場合は以下。
`john --wordlist=myDictionaryFile myPassswordFile`

USER99にURLが仕込まれているので（httpの後に:を入れる必要あり）
そのファイルを辞書として,
問題文をパスワードファイルとして与えれば良い
