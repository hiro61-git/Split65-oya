# Split65 NICOLA Edition (v34)

EPOMAKER Split65(無線対応分割キーボード)を、**NICOLA配列(親指シフト)+ 日本語入力最適化 + 無線活用**に仕上げたQMKファームウェアです。
[banroku/qmk_firmware](https://github.com/banroku/qmk_firmware)(commit `8e8ae400`)をベースに、実機での長期検証を重ねて改造しました。QMKのGPL-2.0-or-laterに従い公開します。

## このファームでできること

| 機能 | 概要 |
|---|---|
| NICOLA親指シフト | 両親指キー(L-SP/R-SP)+jtu(JISかな)エンジン。未確定文字の変換・濁音・半濁音対応 |
| ぱ/ば出し分け | Shift+H=ぱ / L-SP+H=ば(NICOLA-F親指同時打鍵) |
| モード切替 | Caps単押し=IMEオフ(冪等)・かな入力で復帰。英数/かなキーで切替 |
| 無線 | BT1〜3スロット(Fn+Q/W/E長押しでペア)+2.4Gドングル(Fn+R)。有線へは裏面スイッチ中央+USB挿しで即復帰(再ペア不要) |
| ソフトDFU | ピンホール短絡不要。右=直挿し+スイッチON→Fn+M / 左=Fn+M |

## ハードウェアの重要ノウハウ(このキーボード固有)

- **右Shift下のスライドスイッチ=右Type-CのUSBデータ線ON/OFF**。OFFで右に直挿しすると「コード43(USBポートのリセット要求が失敗)」になる。DFU書き込み・右=マスター運用時のみON
- **ピンホール**: 左=L-SPキー下 / 右=R-SPキー下(電源投入の瞬間にサンプル)
- **右Type-Cはbridgeと共用**(1ポートのみ)。右への直挿し中はbridgeが物理的に繋がらない=左右通信不可。**無線モードでもbridgeは必須**(無線モジュールは左のみ・右は常にスレーブ+bridge給電)
- 役割(マスター/スレーブ)は「USBが活性な方がマスター・どこにもUSBが無ければ左(モジュール側)」(v34)

## フラッシュ手順

1. [QMK Toolbox](https://qmk.fm/toolbox) を用意
2. 左半身: Fn+M → WB32 DFU が出る → hex を Flash
3. 右半身: 右Type-C直挿し+右Shift下スイッチON → Fn+M → Flash → スイッチを普段の位置へ
4. ファームは必ず**両半身同じ版**に揃える

## ビルド

```bash
git clone https://github.com/banroku/qmk_firmware   # commit 8e8ae400
# このリポジトリの差分を適用(keyboards/leo/epomaker_split65, users/nicola)
make leo/epomaker_split65:nicola -j8
```

## 詳細ドキュメント

- `docs/firmware_manual.md` — 使い方全般
- `docs/changelog.md` — v1〜v34の全変更記録(デバッグの過程も含む)
- `docs/hardware_notes.md` — ハード仕様の調査記録

## ライセンス / クレジット

GPL-2.0-or-later。元実装の皆様に感謝:
- [banroku/qmk_firmware](https://github.com/banroku/qmk_firmware) — 本ファームのベース
- [Epomaker/Split65](https://github.com/Epomaker/Split65) — ハード公式
- linker/wireless は zozonteq リポジトリ由来(Su (@isuua) 他)

## 同梱物

- `keyboards/leo/epomaker_split65/` — キーボード定義+`keymaps/nicola`(NICOLAキーマップ)
- `users/nicola/` — NICOLA/jtuエンジン
- `split65_v34_clean.hex/.bin` — 日常確定版(推奨)
- `split65_v34.hex/.bin` — 診断ログ付き版(HID Consoleでログが読める)
- `docs/` — manual / changelog(v1〜v34全記録)/ hardware_notes

ビルドは上記フォルダを banroku/qmk_firmware(commit 8e8ae400)の同パスへ上書きコピーして `make leo/epomaker_split65:nicola -j8`
