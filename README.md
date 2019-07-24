# ComDevelopmentTools

__BETA版__
4.22/windowsで動作確認

+ Statの数値を値で取得したい。的なニーズ  
+ あと、オートメーションのだとDECLARE_CYCLE_STAT_EXTERN系しか取れないのでそれ以外も取れるように  

## 使えるノード  
![2019-07-24_23h44_03](https://user-images.githubusercontent.com/11537958/61805255-742a2500-ae70-11e9-9b47-d1ea919cd20b.png)

## 使い方
![2019-07-25_00h00_47](https://user-images.githubusercontent.com/11537958/61805318-8f953000-ae70-11e9-82b5-c5f8a0db486f.png)
1. コンソールコマンド or SetEnableStatGroupノードでstatを有効化します
2. GetStat＊系で値を取得します
+ Stat Nameのリストは下記  
    + Automation Test - Stat系の全リスト  
http://com04.sakura.ne.jp/unreal/wiki/index.php?Automation%20Test#u38b70aa  
    + どのパラメーターにどのGet関数(GetStatCallCount / GetStatDuration* / GetStatValue*)使えるかは実際試してみて下さい  
合わないパラメーターだと変な値が返ってきます  
