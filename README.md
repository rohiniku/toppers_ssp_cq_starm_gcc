# toppers_ssp_cq_starm_gcc
TOPPERS/SSP build on my Mac OS X

Mac OS X環境でTOPPERS/SSPの「DesignWave誌附属CQ_STARM基板用簡易パッケージ」をビルドできるようにする。

TOPPERS/SSPは https://www.toppers.jp/download.cgi/ssp_cq_starm_gcc-20120607.tar.gz (非依存部のバージョン1.1.1)をベースに、非依存部の1.2.1(2014-3-7)まで取り込みました。
非依存部は1.2.0 https://www.toppers.jp/download.cgi/ssp-1.2.0.tar.gz と、1.2.1 https://www.toppers.jp/download.cgi/ssp-1.2.1.tar.gz を順に取り込みました。
それぞれのバージョンで、sample1.cでのLチカが動作することを確認しました。

ボードは http://www.cqpub.co.jp/dwm/Contents/0126/dwm012600520.pdf に紹介があります。CQ出版のDesignWave誌2008年5月号の付録です。STM32F103VBT6が載ってます。
このボードを使ったときだけ、ボード上のLEDをLチカさせるよう、サンプルコード(sample/sample1.c)を修正しています。

あらかじめ、以下のインストールが完了していること。

- gcc4.9系のarm-none-eabi-gccを使う  
brew info arm-none-eabi-gcc  
arm-none-eabi-gcc: stable 20140609  
https://launchpad.net/gcc-arm-embedded  
/usr/local/Cellar/arm-none-eabi-gcc/20140609 (4636 files, 286M) *  
  Built from source  
From: https://github.com/rohiniku/homebrew-stm32/blob/master/arm-none-eabi-gcc.rb  

- プログラムをボードに書き込むためにdfu-utilを使う
brew info dfu-util  
dfu-util: stable 0.8 (bottled), HEAD  
https://gitorious.org/dfu-util/community  
/usr/local/Cellar/dfu-util/0.8 (10 files, 144K) *  
  Poured from bottle  
From: https://github.com/Homebrew/homebrew/blob/master/Library/Formula/dfu-util.rb  
==> Dependencies  
Build: pkg-config  
Required: libusb  
