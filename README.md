# Split65 NICOLA v8 - 変更済みソース

banroku/qmk_firmware (commit 8e8ae400) ベースの改造キーマップ。
確定版は v8 (2026-09-22)。

## 構成

- `split65_v8.patch` — ベースからの全変更の git パッチ(412行)
- `keyboards/leo/epomaker_split65/keymaps/nicola/` — keymap.c + config.h(変更済み実物)
- `users/nicola/` — nicola.c / nicola.h / jtu.h(変更済み実物)
- `leo_epomaker_split65_nicola.hex / .bin` — 確定版ファーム(v8)
- `split65_firmware_manual.md` — 手順書・キーマップ表・チェックリスト
- `keymap_sheet.png` / `gen_keymap_sheet.py` — 早見表と生成スクリプト

## GitHub への取り込み方(2択)

### A. フォーク+ファイル上書き(最も簡単)

1. https://github.com/banroku/qmk_firmware を自分のアカウントにフォーク
2. フォーク先で以下の4ファイルを編集し、このアーカイブの同名ファイルの中身を貼り付け:
   - keyboards/leo/epomaker_split65/keymaps/nicola/keymap.c
   - users/nicola/nicola.c
   - users/nicola/nicola.h
   - users/nicola/jtu.h
3. さらに keyboards/leo/epomaker_split65/keymaps/nicola/ に config.h を新規追加
   (内容はアーカイブの config.h をコピー)
4. コミットメッセージ例: 「NICOLA keymap v8 for Split65 (mode toggle, handaku on SHIFT, F digits, pending-conversion thumb)」

### B. パッチ適用(コマンドライン)

```
git clone https://github.com/<あなた>/qmk_firmware
cd qmk_firmware
git am split65_v8.patch   # または git apply split65_v8.patch
git push
```

## 再ビルド方法(自分のPCで)

QMK MSYS で qmk setup 後、このリポジトリで:
```
make leo/epomaker_split65:nicola
```
生成物 .build/leo_epomaker_split65_nicola.hex を QMK Toolbox で書き込み。

## 変更履歴(v1-v8)

手順書 split65_firmware_manual.md の §6 を参照。
