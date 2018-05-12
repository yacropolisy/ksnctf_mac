実行すると、ゲームが始まる。  
ボタンを押すと十字型にライトが反転する。  
難しい。が、このゲーム自体はそこまで重要ではないらしい。  
ILSpyというのを使うと、C#で作られたバイナリはでコンパイルできるらしい。  
デコンパイルしたソースファイルを見てみると、checkという関数が怪しい。  

```
private void check()
{
  if (Array.IndexOf<bool>(this.state, true) < 0)
  {
    MessageBox.Show("Congratulations!");
    int[] array = new int[]
    {
      1,
      7,
      16,
      11,
      14,
      19,
      20,
      18
    };
    bool flag = true;
    for (int i = 0; i < 8; i++)
    {
      if (this.hist[i] != array[i])
      {
        flag = false;
      }
    }
    if (flag)
    {
      int[] array2 = new int[]
      {
        85,
        111,
        117,
        43,
        104,
        127,
        117,
        117,
        33,
        110,
        99,
        43,
        72,
        95,
        85,
        85,
        94,
        66,
        120,
        98,
        79,
        117,
        68,
        83,
        64,
        94,
        39,
        65,
        73,
        32,
        65,
        72,
        51
      };
      string text = "";
      for (int j = 0; j < array2.Length; j++)
      {
        text += (char)(array2[j] ^ array[j % array.Length]);
      }
      MessageBox.Show(text);
    }
  }
}
```
`if (Array.IndexOf<bool>(this.state, true) < 0)`というのがゲームのクリア条件であろう。  
実際にゲームをクリアすると、Congratulations!という表示が出る。

そのあとで、`array`を定義して、`hist`と`array`が一致した場合、`flag`をtrueにして、次の処理に移っている。  

次の処理では、`flag`がtrueな場合、ちょっと処理をした`text`を表示しているので、これがflagだろう。

よって、flagをtrueにしてゲームをクリアするか、textを解読すれば良い。  

前者のやり方としては、`hist`は `botton_click`関数で扱われているようで、
その名の通りどのボタンを押したかの履歴を格納しているようだ。  
つまり、`flag`をtrueにするためには、`array`の中身{1,7,16,11,14,19,20,18}の順にボタンを押してクリアする必要がある。  

```
private void button_Click(object sender, EventArgs e)
{
  int num = 0;
  for (int i = 0; i < 25; i++)
  {
    if (sender == this.button[i])
    {
      num = i;
    }
  }
  this.push(num);
  for (int j = 0; j < 7; j++)
  {
    this.hist[j] = this.hist[j + 1];
  }
  this.hist[7] = num;
  this.update();
  this.check();
}
```

`array`の順番でクリアをするには、クリアした状態から`array`の中身を押して行き、その後もう一度`array`の順番で押していけば良い。

他の部分を解析すると分かるが、ボタンの番号は以下のようになっている。
ゲームのクリア方法は　[ここ](http://www1.kiy.jp/~yoka/gameland/TentouPuzzle1_FLASH/TentouPuzzle1_FLASH.cgi)で調べることができる。

```
0  1  2  3  4
5  6  7  8  9
10 11 12 13 14
15 16 17 18 19
20 21 22 23 24
```

`text`を解読する手法の方が楽で、計算する部分をそのまま実行すれば良い。
pythonに書き直すと以下のような感じ

```
array = [1,7,16,11,14,19,20,18]
array2 = [85,111,117,43,104,127,117,117,33,110,99,43,72,95,85,85,94,66,120,98,79,117,68,83,64,94,39,65,73,32,65,72,51]
for i, j in enumerate(array2):
	print(chr(j^array[i%8]), end="")
print()

```
