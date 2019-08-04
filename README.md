# ComDevelopmentTools
<img src="https://user-images.githubusercontent.com/11537958/61805255-742a2500-ae70-11e9-9b47-d1ea919cd20b.png" width="200px"><img src="https://user-images.githubusercontent.com/11537958/62422455-07bfe900-b6ee-11e9-8547-fe32049d82ec.png" width="400px">

4.22/windowsで動作確認

+ 開発用のツール郡  
  + [Stats](#stats): Statの数値を値で取得したい。DECLARE_CYCLE_STAT_EXTERN系以外も取れるように  
  + [ScreenInfo](#screen-info): インプレイ中にActor/Componentの情報を表示したい。Tick/Collision等の情報確認  


## Stats
Statの数値を値で取得できるようになります。
### 使えるノード  
![2019-07-24_23h44_03](https://user-images.githubusercontent.com/11537958/61805255-742a2500-ae70-11e9-9b47-d1ea919cd20b.png)

### 使い方
![2019-07-25_00h00_47](https://user-images.githubusercontent.com/11537958/61805318-8f953000-ae70-11e9-82b5-c5f8a0db486f.png)
1. コンソールコマンド or SetEnableStatGroupノードでstatを有効化します
2. GetStat＊系で値を取得します
+ Stat Nameのリストは下記  
  + Automation Test - Stat系の全リスト  
http://com04.sakura.ne.jp/unreal/wiki/index.php?Automation%20Test#u38b70aa  
  + どのパラメーターにどのGet関数(GetStatCallCount / GetStatDuration* / GetStatValue*)使えるかは実際試してみて下さい  
合わないパラメーターだと変な値が返ってきます  
  + SetEnableStatGroupの後、少し待たないとGetStat系で正常な値が返ってこない事があります  

## Screen Info
![2019-08-04_19h28_16](https://user-images.githubusercontent.com/11537958/62422455-07bfe900-b6ee-11e9-8547-fe32049d82ec.png)
Actor/Componentの情報を収集してスクリーンに表示します  
Tick、Collision等無駄な設定がされていないかをチェックできます  

### 使い方
Plugin内のContentに下記Actorが入っています。  
それらをSpawn、SetEnableで有効化すると反映されます  
![2019-08-04_19h22_18](https://user-images.githubusercontent.com/11537958/62422404-3b4e4380-b6ed-11e9-9c96-bfcc4c203155.png)
+ __BP_CDTScreenInfoCollision__ : コリジョンが有効なComponentの数を表示  
+ __BP_CDTScreenInfoCollisionSimple__ : Simple（簡単な）コリジョンが有効なComponentの数を表示  
+ __BP_CDTScreenInfoCollisionComplex__ : Complex（複雑な）コリジョンが有効なComponentの数を表示  
+ __BP_CDTScreenInfoDynamicShadow__ : Dynamic Shadowが有効なComponentの数を表示  
+ __BP_CDTScreenInfoLODMax__ : LODの最大値を表示  
+ __BP_CDTScreenInfoOverlapEvents__ : Generate Overlap Eventsが有効なComponentの数を表示  
+ __BP_CDTScreenInfoTick__ : Tickが有効なActor/Componentの数を表示  

## サンプルについて
![2019-08-04_19h31_42](https://user-images.githubusercontent.com/11537958/62422491-874db800-b6ee-11e9-91ba-ddd70faad038.png)
+ BP_CDTPlayerControllerに使用するサンプルを実装しています  
+ 「Q」キーでStatのサンプルでDrawCall表示  
+ 「1~7」キーでScreenInfoの各チェックを表示  

