# BirdCatch

### About This Game

This is a 2d casual game which you should use your mouse to draw circle for catching birds.

When you enter the game, hold your mouse and try to circle the flying bird, and you get it.

That's all.


### How To Build

0. Make sure you installed **DirectX 9.0 sdk** first.

1. Go to Project **Properties**

2. **General** -> **Project Defaults** -> **Character Set** 

   change "**Use Muti-Byte Character Set**" -> "**Use Unicode Character Set**"

3. **VC++ Directories** -> **Include Directories**

   add "**$(DXSDK_DIR)include**"

4. **VC++ Directories** -> **Library Directories**

   add "**$(DXSDK_DIR)lib\x86**"   (or "$(DXSDK_DIR)lib\x64" if you what to build it on 64-bit)

5. **Linker** -> **Input** -> **Additional Dependencies**

   add "**Winmm.lib**"
           "**d3d9.lib**"
           "**d3dx9d.lib**"
           "**dinput8.lib**"
           "**dxguid.lib**"
           "**xinput.lib**"
   
6. Run
   
-----

### ビルド手順

0. DirectX 9.0がインストールされてことを確認する

1. プロジェクトのプロパティを開く

2. 全般　文字セット　

   ”マルチバイト文字セットを使用する”　を　”Unicode文字セットを使用する”

3. VC++ ディレクトリ　　

   インクルードディレクトリ　に　"$(DXSDK_DIR)include"　を追加する
   ライブラリディレクトリ　に　"$(DXSDK_DIR)lib\x86"　を追加する　
   （64位でビルドしたい場合は"$(DXSDK_DIR)lib\x64"）

   もしくは自分でDirectXのインクルードファイルとライブラリファイルのパスを設定する

4. リンカー　入力　

   追加の依存ファイル　に　"Winmm.lib d3d9.lib d3dx9d.lib dinput8.lib dxguid.lib xinput.lib"を追加する

5. ビルド

-----

### Site credits

This game's resources are mainly come from free resource sites: 

https://opengameart.org/

https://dova-s.jp/
