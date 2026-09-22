# -*- coding: utf-8 -*-
# Split65 NICOLA keymap quick-reference sheet generator (v5)
INK = "#17191C"; SUB = "#8A6F52"; FN = "#B0872F"; LAT = "#2E6FA8"
EISU = "#4FA3E3"; NICO = "#4FBF7A"

def key(u, lat="", kna="", l="", r="", fn="", cls="", href=""):
    a = f' href="{href}"' if href else ""
    combo = ""
    if l or r:
        lv = l if l else "―"; rv = r if r else "―"
        combo = f'<div class="cmb"><span>左{lv}</span><span>右{rv}</span></div>'
    fnh = ''  # function-layer legend removed (NICOLA-only sheet)
    lath = ''  # english-mode legend removed (NICOLA-only sheet)
    knah = f'<div class="kna">{kna}</div>' if kna else ""
    return f'<a class="kcap {cls}" style="--u:{u}"{a}>{fnh}{lath}{knah}{combo}</a>'

def gap(u=0.5):
    return f'<div class="kgap" style="--u:{u}"></div>'

# row5 thumb state cards
def thumb(idle_label, states, accent):
    st = "".join(f'<div class="st"><b>{s[0]}</b>{s[1]}</div>' for s in states)
    return f'<div class="thumb" style="flex-grow:{0}; --ac:{accent}"><div class="tidle">{idle_label}</div>{st}</div>'

rows = []
# ---- row 1 : ESC 1-5 | 6-0 - = BSPC MUTE ----
r1L = [
 key(1,"","ESC","","","","mod"),
 key(1,"","1","?","?"), key(1,"","2","/","/"), key(1,"","3","〜","〜"),
 key(1,"","4","「","「"), key(1,"","5","」","」"),
]
r1R = [
 key(1,"","6","」","」"), key(1,"","7","}","}"), key(1,"","8","(","("),
 key(1,"","9",")",")"), key(1,"","0",")",")"),
 key(1,"","-","｜","｜"), key(1,"","=","+","+"),
 key(1.25,"","⌫","","","","mod"),
 key(1,"","MUTE","","","","mod"),
]
# ---- row 2 ----
r2L = [key(1.5,"TAB","","","","","mod"),
 key(1,"Q",".","xa","",""), key(1,"W","か","e","ga"), key(1,"E","た","ri","da"),
 key(1,"R","こ","xya","go"), key(1,"T","さ","re","za")]
r2R = [
 key(1,"Y","ら","pa","yo"), key(1,"U","ち","di","ni"), key(1,"I","く","gu","ru"),
 key(1,"O","つ","du","ma"), key(1,"P","、","pi","xe"),
 key(1,"[","、","]","["), key(1,"]",";","〕","]"), key(1,"\\","\\","\\","\\"),
 key(1,"DEL","DEL","","","Insert","mod"),
]
# ---- row 3 ----
r3L = [key(1.75,"CapsLock","","","","英字/機能層","caps mod"),
 key(1,"A","う","wo","vu"), key(1,"S","し","a","zi"), key(1,"D","て","na","de"),
 key(1,"F","け","xyu","ge"), key(1,"G","せ","mo","ze")]
r3R = [
 key(1,"H","は","ba","mi"), key(1,"J","と","do","o"), key(1,"K","き","gi","no"),
 key(1,"L","い","po","xyo"),
 key(1,";","ん","―","っ"), key(1,"'","⌫","⌫","'"),
 key(1.25,"ENT","ENT","","","","mod"), key(1,"PGUP","PGUP","","","Home","mod"),
]
# ---- row 4 ----
r4L = [key(2.25,"左SHIFT","","","","濁音半濁音表","mod"),
 key(1,"Z",".","xu","―"), key(1,"X","ひ","-","bi|ぴ"), key(1,"C","す","ro","zu"),
 key(1,"V","ふ","ya","bu|ぷ"), key(1,"B","へ","xi","be|ぺ")]
r4R = [
 key(1,"N","め","pu","nu"), key(1,"M","そ","zo","yu"),
 key(1,",","ね","pe","mu"), key(1,".","ほ","po","wa"), key(1,"/","/","?","xo"),
 key(1.75,"右SHIFT","","","","大文字/ぴぷぺ","mod"),
 key(1,"↑","↑","","","RGB明+","mod"), key(1,"PGDN","PGDN","","","End","mod"),
]
# ---- row 5 ----
r5L = [key(1.25,"Ctrl","","","","","mod"), key(1.25,"Win","","","","","mod"), key(1.25,"Alt","","","","","mod")]
r5R = [
 key(2.25,"L-SP","","","","","thumb-l mod"),
 key(2.25,"R-SP","","","","","thumb-r mod"),
 key(1,"DEL","DEL","","","","mod"), key(1,"FL","","","","","mod"),
 key(1.25,"RCTL","","","","Home","mod"),
 key(1,"←","←","","","RGB速−","mod"), key(1,"↓","↓","","","RGB明−","mod"), key(1,"→","→","","","RGB速+","mod"),
]
rows = [(r1L,r1R),(r2L,r2R),(r3L,r3R),(r4L,r4R),(r5L,r5R)]

kb = ""
for L,R in rows:
    kb += '<div class="krow"><div class="half">' + "".join(L) + '</div><div class="half">' + "".join(R) + '</div></div>'

# thumb state cards content (absolute overlays would complicate; use flex cards under keyboard)
thumb_cards = f'''
<div class="thumbs">
  <div class="tcard"><h4>左スペース(L-SP)</h4>
    <div class="st"><b>英字モード中</b>タップ → 日本語モードへ(緑)</div>
    <div class="st"><b>日本語モード中</b>押中=左親指シフト(同時打鍵)</div>
    <div class="st"><b>未確定タップ</b>無変送出 → ひらがな⇔カタカナ</div>
    <div class="st"><b>未確定なし</b>タップ → スペース</div></div>
  <div class="tcard"><h4>右スペース(R-SP)</h4>
    <div class="st"><b>押中</b>右親指シフト(同時打鍵)</div>
    <div class="st"><b>未確定タップ</b>変換送出 → 漢字変換・次候補</div>
    <div class="st"><b>未確定なし</b>タップ → スペース</div>
    <div class="st"><b>候補連打</b>変換維持で次々候補(Enterで確定)</div></div>
  <div class="tcard"><h4>CapsLock</h4>
    <div class="st"><b>タップ</b>英字モードへ(青)+IME OFF(Alt+`)</div>
    <div class="st"><b>ホールド</b>機能層(Fキー/RGB/カーソル)</div>
    <div class="st"><b>旧コンボ</b>Caps+L-SP=英字 / Caps+R-SP=日本語</div>
    <div class="st"><b>判定</b>300ms・PERMISSIVE_HOLD</div></div>
  <div class="tcard"><h4>右SHIFT</h4>
    <div class="st"><b>基本</b>大文字(通常のSHIFT動作)</div>
    <div class="st"><b>+X</b>ぴ(pi)</div>
    <div class="st"><b>+V</b>ぷ(pu)</div>
    <div class="st"><b>+B</b>ぺ(pe)</div></div>
</div>'''

modebar = f'''
<div class="modebar">
  <div class="mode"><span class="dot" style="background:{EISU}"></span>英字モード</div>
  <div class="flow">CapsLockタップ →</div>
  <div class="mode"><span class="dot" style="background:{NICO}"></span>日本語モード</div>
  <div class="flow">← CapsLockタップ(IME OFF: Alt+` 同時送出) / 英字中にL-SPタップ →</div>
  <div class="mode">RGBはモード連動</div>
</div>'''

# SHIFT table (right column)
shift_table = '''
<table class="tbl">
<tr><th class="kh"></th><th>左SHIFT</th><th>右SHIFT</th></tr>
<tr><td class="kh">H</td><td>ぱ(pa)</td><td>ハ(大文字)</td></tr>
<tr><td class="kh">X</td><td>ー</td><td>ぴ(pi)</td></tr>
<tr><td class="kh">V</td><td>や</td><td>ぷ(pu)</td></tr>
<tr><td class="kh">B</td><td>ぃ</td><td>ぺ(pe)</td></tr>
<tr><td class="kh">.(&gt;)</td><td>ぽ(po)</td><td>ホ(大文字)</td></tr>
<tr><td class="kh">Y/P/N/,/L</td><td>ぱぴぷぺぽ</td><td>大文字</td></tr>
<tr><td class="kh">その他</td><td>左親指表(濁音等)</td><td>大文字</td></tr>
</table>'''

html = f'''<!DOCTYPE html>
<html lang="ja"><head><meta charset="utf-8">
<style>
* {{ margin:0; padding:0; box-sizing:border-box; }}
body {{ width:1560px; height:1100px; background:#0F1216; color:#C9CDD3;
  font-family:"Noto Sans CJK JP","Noto Sans JP",sans-serif; padding:34px 40px; position:relative; }}
h1 {{ font-size:30px; font-weight:900; color:#F2F0EA; letter-spacing:.02em; }}
h1 small {{ font-size:14px; font-weight:500; color:#8A9099; margin-left:14px; }}
.meta {{ position:absolute; top:40px; right:44px; text-align:right; font-size:12px; color:#8A9099; line-height:1.7; }}
.kbwrap {{ margin-top:20px; }}
.krow {{ display:flex; gap:6px; margin-bottom:6px; }}
.half {{ display:flex; gap:6px; }}
.kgap {{ flex-grow:1; }}
.krow > .half:last-child {{ margin-left:18px; }}
.kcap, .kgap {{ flex-grow:var(--u); }}
.kgap {{ min-width:2px; }}
.kcap {{ position:relative; height:64px; background:linear-gradient(180deg,#F3EFE6,#E2DCCE);
  border-radius:7px; box-shadow:inset 0 -5px 0 rgba(0,0,0,.16), 0 2px 4px rgba(0,0,0,.5);
  color:{INK}; min-width:34px; }}
.kcap.mod {{ background:linear-gradient(180deg,#CBC5B7,#B7B0A0); }}
.kcap.caps {{ background:linear-gradient(180deg,#DCE9F7,#C6DAF0); }}
.kcap.thumb-l {{ background:linear-gradient(180deg,#DFF2E5,#C5E4D1); }}
.kcap.thumb-r {{ background:linear-gradient(180deg,#DFF2E5,#C5E4D1); }}
.lat {{ position:absolute; top:5px; right:7px; font-family:"DejaVu Sans Mono",monospace;
  font-size:11px; font-weight:700; color:{LAT}; }}
.fn {{ position:absolute; top:5px; left:7px; font-size:9px; font-weight:700; color:{FN}; line-height:1.2; }}
.kna {{ position:absolute; top:38%; left:0; right:0; transform:translateY(-50%);
  text-align:center; font-size:21px; font-weight:900; }}
.cmb {{ position:absolute; bottom:4px; left:0; right:0; display:flex; justify-content:center;
  gap:8px; font-size:10px; font-weight:700; color:{SUB}; }}
.thumbs {{ display:flex; gap:10px; margin-top:16px; width:1460px; margin-left:auto; margin-right:auto; }}
.tcard {{ flex:1; background:#161B21; border:1px solid #262D35; border-radius:9px; padding:12px 14px; }}
.tcard h4 {{ font-size:13px; color:#F2F0EA; margin-bottom:8px; font-weight:900; }}
.st {{ font-size:11px; line-height:1.55; color:#AEB4BC; margin-bottom:5px; }}
.st b {{ display:inline-block; min-width:74px; color:{NICO}; font-weight:700; margin-right:8px; }}
.side {{ position:absolute; right:40px; top:150px; width:328px; }}
.panel {{ background:#161B21; border:1px solid #262D35; border-radius:11px; padding:16px 18px; margin-bottom:14px; }}
.panel h3 {{ font-size:15px; color:#F2F0EA; font-weight:900; margin-bottom:10px; }}
.panel h3 span {{ font-size:11px; font-weight:500; color:#8A9099; margin-left:8px; }}
.tbl {{ width:100%; border-collapse:collapse; font-size:12px; }}
.tbl th, .tbl td {{ border-bottom:1px solid #262D35; padding:6px 4px; text-align:left; color:#C9CDD3; }}
.tbl th {{ color:#8A9099; font-weight:700; font-size:11px; }}
.kh {{ font-family:"DejaVu Sans Mono",monospace; color:{EISU}; font-weight:700; }}
.note {{ font-size:11px; line-height:1.7; color:#AEB4BC; }}
.note b {{ color:{NICO}; }}
.legendrow {{ display:flex; gap:18px; margin-top:14px; font-size:11px; color:#AEB4BC; }}
.legendrow span::before {{ content:""; display:inline-block; width:9px; height:9px; border-radius:2px;
  margin-right:6px; vertical-align:-1px; }}
.lg-lat::before {{ background:{LAT}; }} .lg-kna::before {{ background:{INK}; }}
.lg-cmb::before {{ background:{SUB}; }} .lg-fn::before {{ background:{FN}; }}
.footer {{ position:absolute; bottom:26px; left:40px; right:40px; font-size:11px; color:#6E747C; line-height:1.6; }}
.modebar {{ display:flex; align-items:center; gap:14px; margin-top:14px; background:#161B21;
  border:1px solid #262D35; border-radius:9px; padding:10px 16px; font-size:12.5px; width:fit-content; }}
.mode {{ font-weight:900; color:#F2F0EA; display:flex; align-items:center; gap:7px; }}
.dot {{ width:11px; height:11px; border-radius:50%; display:inline-block; box-shadow:0 0 8px currentColor; }}
.flow {{ color:#8A9099; }}
.kbzone {{ width:1460px; margin:0 auto; }}
</style></head><body>
<h1>Split65 日本語モード入力表<small>NICOLA親指シフト v7</small></h1>
<div class="meta"><div>LED <b style="color:#4FBF7A">緑</b>=日本語モード(この表)</div><div>英字モードへの切替は CapsLock タップ</div><div>v7 確定版 · 2026-09-22</div></div>

{modebar}

<div class="kbzone kbwrap">{kb}</div>
<div class="legendrow"><span class="lg-kna">中央:単独打鍵</span><span class="lg-cmb">下段:左親指/右親指 同時打鍵の出力(ローマ字)</span></div>

{thumb_cards}

<div class="footer">対応ファーム: leo_epomaker_split65_nicola.hex (v5) — 変更詳細は手順書 split65_firmware_manual.md 参照。NICOLA配列の同時打鍵判定は元実装のまま(タイムアウト式)。英字モードはjtuによりSJIS設定のPCでも刻印通りに入力。</div>
</body></html>'''

open('/home/user/workspace/keymap_sheet.html','w',encoding='utf-8').write(html)
print("html written", len(html))
