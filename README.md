# c1_2024

## これは何
京都大学理学部宇宙物理学系の授業「物理科学課題演習C1」の進捗置き場。

## フォルダ構成
<dl>
  <dt>fortran/</dt>
  <dd>たまにFortranで遊びます</dd>
  <dt>qiita/zz</dt>
  <dd>佐々木先生の授業資料の課題をやるところ</dd>
</dl> 

## やりたいこととそのおおざっぱな目標
- [ ] 佐々木先生の授業資料 (-04/20)
- [ ] 輻射電磁流体シミュレーションの基礎
- [ ] [Oscillations in star formation and contents of a molecular cloud complex](https://ui.adsabs.harvard.edu/abs/1985A%26A...142..297B/abstract)
  - レポートの案。

## 実際にやったこととそのメモ
| **日付**   | **内容** | **日記** |
|------------|----------|----------|
| 2024/04/11 | [京大理学部 物理科学課題演習 C1 （その１）](https://qiita.com/sasakitakanori/items/53510d320819ef0dcfab)   | ずっとサボっていたポインタをやった, (たぶん慣れていないだけだが) やはり理解があいまいなのと, いまいち嬉しさが分かっていないので自発的に使うことはなさそう… |
| 2024/04/12 | [京大理学部 物理科学課題演習 C1 （その２）](https://qiita.com/sasakitakanori/items/619760ce65460a3ed57e)   | 典型的な場合分けのプログラムだが, これまでちゃんと精度まで考えてやったことがなかったので意識していきたい  |
| 2024/04/12 | [京大理学部 物理科学課題演習 C1 （その３）](https://qiita.com/sasakitakanori/items/f4e85fc417cc377f61de)   | 情報落ちを全く考えたことがなかったのと, ポインタの扱い？メモリの動的確保？でめちゃくちゃつまづいた, 慣れます  |
| 2024/04/12 | ポインタ | ポインタについて知っておかないといろいろ困りそうだったのでしっかり勉強して割と使えるようになりました  |
| 2024/04/12 | [京大理学部 物理科学課題演習 C1 （その４）](https://qiita.com/sasakitakanori/items/a755414cfb221033bc9d)   | ピボット選択も含め (Pythonで) 実装したことがあったので, ポインタの扱いが分かった今は簡単だった  |
| 2024/04/12 | [京大理学部 物理科学課題演習 C1 （その５）](https://qiita.com/sasakitakanori/items/b1a0c54b6a566166d80e)   | 同上。PythonはLU分解一発でできるから, Cはたいへん。  |
| 2024/04/13 | [京大理学部 物理科学課題演習 C1 （その６）](https://qiita.com/sasakitakanori/items/732e31edf599e054caac)   | 謎バグに延々と悩まされていた, 教訓: ポインタ変数のインクリメントの挙動について理解する  |
| 2024/04/13 | [京大理学部 物理科学課題演習 C1 （その７）](https://qiita.com/sasakitakanori/items/ff85a44a473b0a88758e)   | [これ](https://qiita.com/nyan99/items/0ebb446028b069a1e9e4) に悩まされてた。もう大丈夫  |
| 2024/04/14 | [京大理学部 物理科学課題演習 C1 （その８）](https://qiita.com/sasakitakanori/items/ebaf980a1cd52cf0f634)   | Pythonで連立微分方程式をRK4で書くのめんどくさかったけど, ポインタとか使えるcだと割と簡単に実装できてすごい偉い, ありがたい  |
| 2024/04/15 | [京大理学部 物理科学課題演習 C1 （その９）](https://qiita.com/sasakitakanori/items/bc924f5ab5fa29105d59)   | 二体問題とか。RK4でエネルギーがかなりの精度で保存されていることが確認できたのがよかった  |
| 2024/04/15 | [京大理学部 物理科学課題演習 C1 （その１０）](https://qiita.com/sasakitakanori/items/a1831f65043d20190c93)   | 「台形公式は周期関数で強い, シンプソンは非周期関数で強い」みたいな結果を期待したが$\int_0^1 e^xdx$で刻み幅を結構細かくしないとすごい微妙な結果になった。この範囲では割といい精度で計算してくれると思ったが… 逆に$\sin x$の積分ではどちらとも良い精度で計算してくれたが, これは割と想定通りなので安心した。  |
| 2024/04/15 | [京大理学部 物理科学課題演習 C1 （その１１）](https://qiita.com/sasakitakanori/items/adecf543657de8a6fdfc)   | explicit methodだけやった, が, 明らかに変なので困っている。  |
| 2024/04/16 | [京大理学部 物理科学課題演習 C1 （その１１）](https://qiita.com/sasakitakanori/items/adecf543657de8a6fdfc)   | TAさんに見ていただいたところ, しょうもないミスだったので直した。ここまでずっと悩んでいたのは久しぶりだ…… 拡散数の条件で, dxの精度がさほどでも, dtの精度をかなり上げないといけないので, 特にGaussianとかはいっぱい時間回さないとなかなか緩和してくれなくて大変。  |
| 2024/04/17 | [京大理学部 物理科学課題演習 C1 （その１１）](https://qiita.com/sasakitakanori/items/adecf543657de8a6fdfc)   | 今日はimplicit。連立方程式を解くのにLU分解を実装したらバグってそれがとれないのでまた明日…  |
| 2024/04/18 | [京大理学部 物理科学課題演習 C1 （その１１）](https://qiita.com/sasakitakanori/items/adecf543657de8a6fdfc)   | 終わり！！！！！！！きれいに緩和してくれました。計算量, 使用メモリ量の改善の余地はかなりあると思う, 例えば今回Gauss消去で連立方程式を解いたが, たぶん最初にAをLU分解しておいたらまとめて1回で済むので早そう  |
| 2024/04/19 | [京大理学部 物理科学課題演習 C1 （例題集）](https://qiita.com/sasakitakanori/items/1264d5955f0a5e9b341d)   | これの二分法をやった, そんなに困ったこともなく終わった。ほかにもはさみうち法とかいろいろあるっぽいので余裕があるときに調べたい, が1回で2倍の精度なのでしばらくはそれほど困ることはなさそう, 初期値の設定がめんどくさいのは懸念？  |
| 2024/04/21 | [京大理学部 物理科学課題演習 C1 （例題集）](https://qiita.com/sasakitakanori/items/1264d5955f0a5e9b341d)   | 宇宙の晴れ上がり。これはやることは実質的にはplotだけだったが, 延々にバグが取れなくて困っていた。最終的には二分法の初期値を引くほど小さくしたらうまくいった。一応見積もってはいたが少し甘かったのかもしれない。伏線回収した。  |
| 2024/04/22 | [京大理学部 物理科学課題演習 C1 （例題集）](https://qiita.com/sasakitakanori/items/1264d5955f0a5e9b341d)   | 多項式のfitting。ライブラリを使うだけで楽にできた。行列のポインタの扱いにも慣れてきたと思ってる。  |
| 2024/04/26 | [京大理学部 物理科学課題演習 C1 （例題集）](https://qiita.com/sasakitakanori/items/1264d5955f0a5e9b341d)   | ここ数日はBondi Flowをやっていた, ちょっと気になったので[Bondi (1952)](https://ui.adsabs.harvard.edu/abs/1952MNRAS.112..195B/abstract)も読んでいた  |
| 2024/04/30 | [京大理学部 物理科学課題演習 C1 （例題集）](https://qiita.com/sasakitakanori/items/1264d5955f0a5e9b341d)   | 銀河ポテンシャル。前のケプラー問題のコードそのまま使った。  |
| 2024/04/30 | [Fortran](https://www7b.biglobe.ne.jp/~fortran/education/fortran90/sec0.html)   | 時代はFortranなので, Fortranで遊びました。  |