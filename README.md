# toppers_ssp_cq_starm_gcc
TOPPERS/SSP build on my Mac OS X

Mac OS X環境でTOPPERS/SSPの「DesignWave誌附属CQ_STARM基板用簡易パッケージ」をビルドできるようにする。

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
