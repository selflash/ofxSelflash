#!/bin/sh

#MacOSX固有コマンド『sips』を使って画像のリサイズをする
#http://d.hatena.ne.jp/oniloq/20121111/1352625190

#自分のスクリプトの位置にカレントディレクトリを持ってくる
current_directory=$(dirname $0)
cd $current_directory

base_path="Macintosh HD"${current_directory////:}
path="$(osascript -e '
on run argv
set base_path to item 1 of argv
choose file default location alias base_path
end run
' -- "$base_path"
)"

path=${path/"alias Macintosh HD"/}
path=${path//://}
# path=${path%/*}
echo ${path}

#画像の縦横のうち、大きい方のサイズに合わせて縦横比率はそのままで指定サイズにリサイズ
#sips -Z 712 ${path}
sips -Z 1024 ${path}

exit 0
#ENTERが押されるまで待機
read -p "Press [Enter] key to resume."