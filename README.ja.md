[English](README.md) | [Japanese](README.ja.md)
# Leverless on UIAPduino

## 概要
Leverless on UIAPduino は[UIAPduino](https://www.uiap.jp/uiapduino/pro-micro/ch32v003/v1dot4) 向けのUSB HID ゲームパッドの実装で[rv003usb](https://github.com/cnlohr/rv003usb/tree/master/demo_gamepad) をベースに作られています。

<img src="images/3d-printed-leverless.jpg" height="180px"> [![The world cheapest DIY Leverless](https://markdown-videos-api.jorgenkh.no/url?url=https%3A%2F%2Fyoutu.be%2FpFhHLlzWdBo)](https://youtu.be/pFhHLlzWdBo)

## ハードウェア
回路図の通り、UIAPduinoの GPIO とGND の間にスイッチを入れただけのものです。

<img src="images/leverless-schematic.png" height="280px">

## 3D Model
以下に3Dモデルがありますが、自分で筐体、ボタンを用意しても良いです。

[レバーレス 3Dモデル](https://www.thingiverse.com/thing:7350970)

## ビルド方法
### 事前準備
このプロジェクトは[ch32fun](https://github.com/cnlohr/ch32fun) を使うので、以下のページに従って必要なソフトウェアをあらかじめインストールしておいてください。

[ch32fun のための事前準備](https://github.com/cnlohr/ch32fun/wiki/Installation)

### Submodules
Clone 後に以下のコマンドでサブモジュールを取得します。

```
 git submodule update --init --recursive
```

### ビルド・書き込み
WCH-LinkE をPC とUIAPduino に接続し、`gamepad/` 以下で`make` するとビルドと成果物の書き込みが始まります。

```
cd gamepad
make
```

## テスト
UIAPDuino を Windows PC に接続し、joy.cpl を起動します。

<img src="images/run-joy-cpl.png" height="100px">

正しく動作していればゲームパッドが表示されます。

<img src="images/joy-cpl.png" height="200px">

プロパティウィンドウを開きます。

UIAPduino のGPIO をGND に接続すると、対応するボタン・Dpad が反応するのが分かります。

<img src="images/test-button7.png" height="200px"> <img src="images/test-dpad-left.png" height="200px">

<img src="images/pin-layout.png" height="200px">
