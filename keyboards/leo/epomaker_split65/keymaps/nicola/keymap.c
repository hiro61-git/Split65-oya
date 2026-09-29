// Copyright 2025 EPOMAKER (@Epomaker)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "rgb_record/rgb_record.h"

#include "nicola.h" // NICOLA�e�w�V�t�g
#include "jtu.h"    // JIS keyboard on ANSI layout hardware

// Japanese IME keys
#define KC_HENK   0x8A  // Henkan
#define KC_MHEN   0x8B  // Muhenkan
#define KC_LANG1  0x90  // Katakana/Hiragana (Japanese mode)
#define KC_LANG2  0x91  // Eisu (Alphanumeric mode)

#define RGBLED_NUM 0
#define X_MHEN   KC_MHEN
#define X_LANG2  KC_LANG2
#define X_HENK   KC_HENK
#define X_LANG1  KC_LANG1

extern void master_to_slave_boot(void);  // v22: epomaker_split65.c
extern void rgb_matrix_hs_indicator_set(uint8_t index, RGB rgb, uint32_t interval, uint8_t times);  // v23: epomaker_split65.c
bool is_keyboard_master(void);           // v22: defined at bottom of this file

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

//enum layers {
//    _BL = 0,
//    _FL,
//    _MBL,
//    _MFL,
//};

#define ______ HS_BLACK

enum keymap_layers {
  _QWERTY,
// NICOLA�e�w�V�t�g
  _NICOLA, // NICOLA�e�w�V�t�g���̓��C���[
// NICOLA�e�w�V�t�g
  _FUNC,
  _FL //FL layer of split65 original
};

enum custom_keycodes {
  KC_EISU = JTU_SAFE_RANGE,
  KC_KANA2,
  KC_T_MHEN,   // v21: diagnostic — send 0x8B only
  KC_T_HENK,   // v21: diagnostic — send 0x8A only
  KC_T_LANG2,  // v21: diagnostic — send 0x91 only
  KC_T_LANG1,  // v21: diagnostic — send 0x90 only
  KC_T_ALTGR,
  KC_RST_R,    // v22: reset RIGHT half into bootloader (split sync cmd 0xBB)
  KC_CAPSFUNC  // v26: own Caps hold/tap (QMK LT tap keycode never fires on this board = B1)
};

 //�I���W�i����"LAYOUT_62_ansi_2space"���Ȃ���������"LAYOUT"�֕ύX
 //"LAYOUT"�͈���69�ɑ΂��āAansi������65�ő���Ȃ��������߁A�_�~�[��4�ǉ���������Œ���
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT( \
      KC_ESC,  KC_1,    JU_2,    KC_3,    KC_4,    KC_5,    JU_6,           JU_7,   JU_8,    JU_9,    JU_0,    JU_MINS,  JU_EQL,  KC_BSPC,   KC_MUTE, \
      KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                 KC_Y,    KC_U,   KC_I,    KC_O,    KC_P,  JU_LBRC,  JU_RBRC,  JU_BSLS,  KC_DEL, \
      KC_CAPSFUNC, KC_A,  KC_S,    KC_D,    KC_F,    KC_G,              KC_H,    KC_J,   KC_K,    KC_L,    JU_SCLN, JU_QUOT,  KC_ENT, KC_PGUP, \
      KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,           KC_N,    KC_M,   KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,  KC_UP,   KC_PGDN,  \
      KC_LCTL, KC_LCMD , KC_LALT,             KC_KANA2,      KC_SPC, KC_DEL, MO(_FL), KC_RCTL, KC_LEFT,  KC_DOWN, KC_RIGHT ), 


  // NICOLA入力レイヤー(この定義が有効)
  [_NICOLA] = LAYOUT( \
      KC_ESC,  NG_1,    NG_2,    NG_3,    NG_4,    NG_5,    NG_6,           NG_7,   NG_8,    NG_9,    NG_0,    NG_MINS,  NG_EQL,  KC_BSPC,   KC_MUTE, \
      KC_TAB,  NG_Q,    NG_W,    NG_E,    NG_R,    NG_T,                 NG_Y,    NG_U,   NG_I,    NG_O,    NG_P,  NG_LBRC,  NG_RBRC,  NG_BSLS,  KC_DEL, \
      KC_CAPSFUNC, NG_A,  NG_S,    NG_D,    NG_F,    NG_G,              NG_H,    NG_J,   NG_K,    NG_L,    NG_SCLN, NG_QUOT,  KC_ENT, KC_PGUP,  \
      KC_LSFT, NG_Z,    NG_X,    NG_C,    NG_V,    NG_B,           NG_N,    NG_M,   NG_COMM, NG_DOT,  NG_SLSH, KC_RSFT,  KC_UP,  KC_PGDN,   \
      KC_LCTL, KC_LCMD,  KC_LALT,             NG_SHFTL,     NG_SHFTR, KC_DEL, MO(_FL), KC_RCTL, KC_LEFT, KC_DOWN, KC_RIGHT ),

  // Function Layer, KC_BSLS is not confirmed
  // ファンクション層(CapsLockホールド)
  [_FUNC] = LAYOUT( \
      QK_BOOT /*v19: LEFT half DFU key (Caps+`)*/,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,          KC_F7,  KC_F8,   KC_F9,   KC_F10,  KC_F11,   KC_F12,  KC_RST_R /*v23: Caps+DEL = right DFU, no USB swap needed if DFU survives*/,    KC_MUTE, \
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RGB_TOG,              LCTL(KC_LEFT), KC_PGDN, KC_PGUP, LCTL(KC_RIGHT), KC_T_MHEN, KC_T_HENK, QK_BOOT, KC_T_LANG2,  KC_RST_R, \
      MO(_FUNC), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,        KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, KC_T_LANG1,  KC_DEL,  KC_ENT, KC_PGUP,  \
      KC_LSFT, KC_TRNS,KC_TRNS,LCTL(KC_C),LCTL(KC_V),KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_T_ALTGR, KC_RSFT, KC_UP,  KC_PGDN,   \
      KC_TRNS, KC_TRNS,    KC_TRNS,             KC_EISU,      KC_KANA2, KC_TRNS, MO(_FL), KC_HOME, KC_LEFT, KC_DOWN, KC_RIGHT ),

  // Function layer of split65
  [_FL] = LAYOUT( \
      KC_GRV,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,              KC_F6,    KC_F7,    KC_F8,    KC_F9,     KC_F10,   KC_F11,  KC_F12,   EE_CLR,   KC_TRNS, \
      RGB_MOD,  KC_BT1,   KC_BT2,   KC_BT3,   KC_2G4,   KC_TRNS,            KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS,    KC_TRNS,  RGB_HUD, RGB_HUI,  KC_TRNS,  KC_INS,  \
      KC_TRNS,  KC_A,     KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS,    RGB_SAD,  RGB_SAI, KC_TRNS,            KC_HOME, \
      KC_TRNS,  KC_TRNS,  RGB_TOG,  KC_TRNS,  KC_TRNS,  KC_TRNS,            NK_TOGG,  QK_BOOT,  KC_TRNS, KC_TRNS,    KC_TRNS,           KC_TRNS,  RGB_VAI,  KC_END, \
      KC_FILP,  GU_TOGG,  KC_TRNS,  KC_BATQ,                                KC_BATQ,  KC_TRNS,  KC_TRNS, KC_TRNS,                       RGB_SPD,  RGB_VAD,  RGB_SPI),

};


// clang-format off
// const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
// 
//     [_BL] = LAYOUT( /* Base */
//         KC_ESC,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,               KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC, KC_MUTE,
//         KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,               KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS, KC_DEL,   
//         KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,               KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,  KC_ENT,            KC_PGUP,
//         KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,               KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,            KC_RSFT,  KC_UP,   KC_PGDN,
//         KC_LCTL,  KC_LCMD,  KC_LALT,  KC_SPC,                                 KC_SPC,   KC_RALT,  MO(_FL),  KC_RCTL,                      KC_LEFT,  KC_DOWN, KC_RGHT),
// 
//     [_FL] = LAYOUT( /* Base */
//         KC_GRV,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,              KC_F6,    KC_F7,    KC_F8,    KC_F9,     KC_F10,   KC_F11,  KC_F12,   EE_CLR,   _______,
//         RGB_MOD,  KC_BT1,   KC_BT2,   KC_BT3,   KC_2G4,   _______,            _______,  _______,  _______, _______,    _______,  RGB_HUD, RGB_HUI,  _______,  KC_INS,  
//         _______,  KC_A,     TO(_MBL), _______,  _______,  _______,            _______,  _______,  _______, _______,    RGB_SAD,  RGB_SAI, _______,            KC_HOME, 
//         _______,  _______,  RGB_TOG,  _______,  _______,  _______,            NK_TOGG,  _______,  _______, _______,    _______,           _______,  RGB_VAI,  KC_END,
//         KC_FILP,  GU_TOGG,  _______,  KC_BATQ,                                KC_BATQ,  _______,  _______, _______,                       RGB_SPD,  RGB_VAD,  RGB_SPI),
// 
//     [_MBL] = LAYOUT( /* Base */
//         KC_ESC,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,               KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC, KC_MUTE,
//         KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,               KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS, KC_DEL,   
//         KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,               KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,  KC_ENT,            KC_PGUP,
//         KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,               KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,            KC_RSFT,  KC_UP,   KC_PGDN,
//         KC_LCTL,  KC_LALT,  KC_LGUI,  KC_SPC,                                 KC_SPC,   KC_RGUI,  MO(_MFL), KC_RCTL,                      KC_LEFT,  KC_DOWN, KC_RGHT),
//     [_MFL] = LAYOUT( /* Base */
//         KC_GRV,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,              KC_F6,    KC_F7,    KC_F8,    KC_F9,     KC_F10,   KC_F11,  KC_F12,   EE_CLR,   _______,
//         RGB_MOD,  KC_BT1,   KC_BT2,   KC_BT3,   KC_2G4,   _______,            _______,  _______,  _______, _______,    _______,  RGB_HUD, RGB_HUI,  _______,  KC_INS,  
//         _______,  TO(_BL),  KC_S,     _______,  _______,  _______,            _______,  _______,  _______, _______,    RGB_SAD,  RGB_SAI, _______,            KC_HOME, 
//         _______,  _______,  RGB_TOG,  _______,  _______,  _______,            NK_TOGG,  _______,  _______, _______,    _______,           _______,  RGB_VAI,  KC_END,
//         KC_FILP,  _______,  _______,  KC_BATQ,                                KC_BATQ,  _______,  _______, _______,                       RGB_SPD,  RGB_VAD,  RGB_SPI),
// 
// };

// ��������nicola mechanism�̈ڐA�̈�

void matrix_init_user(void) {
  // NICOLA�e�w�V�t�g
  set_nicola(_NICOLA);
  // NICOLA�e�w�V�t�g
}

// v23: translate NG_* (NICOLA layer keycodes) to plain KC_* so shortcut combos
// (Win+D, Ctrl+C...) work in kana mode - raw NG_* usages are invisible to Windows
static uint16_t ng_to_kc(uint16_t kc) {
  switch (kc) {
    case NG_1: return KC_1;   case NG_2: return KC_2;   case NG_3: return KC_3;
    case NG_4: return KC_4;   case NG_5: return KC_5;   case NG_6: return KC_6;
    case NG_7: return KC_7;   case NG_8: return KC_8;   case NG_9: return KC_9;
    case NG_0: return KC_0;   case NG_MINS: return KC_MINS; case NG_EQL: return KC_EQL;
    case NG_Q: return KC_Q;   case NG_W: return KC_W;   case NG_E: return KC_E;
    case NG_R: return KC_R;   case NG_T: return KC_T;   case NG_Y: return KC_Y;
    case NG_U: return KC_U;   case NG_I: return KC_I;   case NG_O: return KC_O;
    case NG_P: return KC_P;   case NG_LBRC: return KC_LBRC; case NG_RBRC: return KC_RBRC;
    case NG_BSLS: return KC_BSLS;
    case NG_A: return KC_A;   case NG_S: return KC_S;   case NG_D: return KC_D;
    case NG_F: return KC_F;   case NG_G: return KC_G;   case NG_H: return KC_H;
    case NG_J: return KC_J;   case NG_K: return KC_K;   case NG_L: return KC_L;
    case NG_SCLN: return KC_SCLN; case NG_QUOT: return KC_QUOT;
    case NG_Z: return KC_Z;   case NG_X: return KC_X;   case NG_C: return KC_C;
    case NG_V: return KC_V;   case NG_B: return KC_B;   case NG_N: return KC_N;
    case NG_M: return KC_M;   case NG_COMM: return KC_COMM; case NG_DOT: return KC_DOT;
    case NG_SLSH: return KC_SLSH;
    default: return KC_NO;
  }
}

// v23: Caps tap fallback - a FUNC hold shorter than 500ms with no FUNC-layer key
// used is treated as a tap (= English mode), even when the LT tap keycode never fires
static uint32_t func_on_time = 0;
static bool func_key_used = false;

layer_state_t layer_state_set_user(layer_state_t state) {
  // v26: FUNC hold/tap is now handled in process_record_user (KC_CAPSFUNC).
  // The old 500ms fallback here would double-fire on the manual layer toggle - removed.
  return state;
}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  if (IS_LAYER_ON(_FUNC) && record->event.pressed && keycode != KC_MHEN) { func_key_used = true; }  // v23

  // v2: explicit physical shift tracking (independent of get_mods() timing)
  static bool lshift_held = false, rshift_held = false;
  if (keycode == KC_LSFT)      { lshift_held = record->event.pressed; }
  else if (keycode == KC_RSFT) { rshift_held = record->event.pressed; }

  static uint16_t last_lsp_rel = 0;  // v9: last release time of KANA2 (L-SP tap)
  static bool lsp_swallow = false;   // v9: swallow the 2nd release of a double tap
  static bool lsp_space_held = false; // v13: KANA2 is holding a real space (KC_SPC)
  static bool lshift_ate = false;    // v9: press-side swallowed this key (LSHIFT table)
  static bool rshift_ate = false;    // v9: same for RSHIFT block
  static bool combo_held = false;    // v9: Ctrl/Alt/Win held (shortcut in progress)
  if (keycode == KC_LCTL || keycode == KC_RCTL) { combo_held = record->event.pressed; }
  else if (keycode == KC_LALT || keycode == KC_RALT) { combo_held = record->event.pressed; }
  else if (keycode == KC_LCMD || keycode == KC_RCMD) { combo_held = record->event.pressed; }

  switch (keycode) {
    case KC_CAPSFUNC:  // v26: own hold/tap for Caps (replaces LT; B1 fix)
      if (record->event.pressed) {
        func_on_time = timer_read32();
        func_key_used = false;
        layer_on(_FUNC);
      } else {
        layer_off(_FUNC);
        bool quick = timer_elapsed32(func_on_time) < 500;
        func_on_time = 0;
        if (!func_key_used && quick) {
          tap_code(X_MHEN);  // 0x8B - C1-proven on this IME
#ifdef RGB_MATRIX_ENABLE
          rgb_matrix_mode_noeeprom(1);
          rgb_matrix_sethsv_noeeprom(170, 255, rgb_matrix_get_val());  // EISU mode = BLUE
#endif
          nicola_off();
          nicola_pending = false;
        }
      }
      return false;
    case KC_RST_R:  // v22: software-DFU the RIGHT half (master sends 0xBB over split sync)
      if (record->event.pressed && is_keyboard_master()) {
        master_to_slave_boot();
      }
      return false;
    // v21: diagnostic keys
    case KC_T_MHEN:  if (record->event.pressed) { rgb_matrix_hs_indicator_set(0xFF, (RGB){0xFF,0xA5,0x00}, 250, 2); tap_code(KC_MHEN); }  return false;  // v23 blink ORANGE
    case KC_T_HENK:  if (record->event.pressed) { rgb_matrix_hs_indicator_set(0xFF, (RGB){0xA0,0x00,0xFF}, 250, 2); tap_code(KC_HENK); }  return false;  // v23 blink PURPLE
    case KC_T_LANG2: if (record->event.pressed) { rgb_matrix_hs_indicator_set(0xFF, (RGB){0x00,0xC8,0xFF}, 250, 2); tap_code(KC_LANG2); } return false;  // v23 blink CYAN
    case KC_T_LANG1: if (record->event.pressed) { rgb_matrix_hs_indicator_set(0xFF, (RGB){0xFF,0x69,0xB4}, 250, 2); tap_code(KC_LANG1); } return false;  // v23 blink PINK
    case KC_T_ALTGR:
      if (record->event.pressed) {
        rgb_matrix_hs_indicator_set(0xFF, (RGB){0xFF,0xFF,0xFF}, 250, 2);  // v23 blink WHITE
        register_code(KC_LALT); tap_code(KC_GRV); unregister_code(KC_LALT);
      }
      return false;
    case KC_MHEN: // v13: CapsLock tap (LT needs an 8-bit keycode; KC_EISU cannot encode in LT)
      if (record->event.pressed) {
        // v19: LANG2 (英数) ONLY. MHEN (無変換) removed — on MS-IME default it is
        // the IME-ON (kana) key, so re-sending it re-entered kana (the "2nd Caps
        // tap falls back to Japanese" bug). LANG2 alone is idempotent and heals
        // any firmware/IME divergence (e.g. PC rebooted in kana mode).
        // v24: MHEN only - proven working on this user IME (v23 test C1)
        tap_code(X_MHEN);
#ifdef RGB_MATRIX_ENABLE
        rgb_matrix_mode_noeeprom(1); /* RGB_MATRIX_SOLID_COLOR */ // v20: leave rainbow/cycle animations so the hue is visible
        rgb_matrix_sethsv_noeeprom(170, 255, rgb_matrix_get_val()); // EISU mode = BLUE
#endif
        nicola_off();
        nicola_pending = false;
      }
      return false;
    case KC_EISU:
      if (record->event.pressed) {
        // NICOLAewVtg
        // v12: 無変換+英数に戻す(Caps+L-SP コンボ時代から実機で動作実績のある確定手法)
        // v24: MHEN only (C1-proven; LANG2 alone is a no-op on this IME)
        tap_code(X_MHEN);
#ifdef RGB_MATRIX_ENABLE
        rgb_matrix_mode_noeeprom(1); /* RGB_MATRIX_SOLID_COLOR */ // v20: leave rainbow/cycle animations so the hue is visible
        rgb_matrix_sethsv_noeeprom(170, 255, rgb_matrix_get_val()); // EISU mode = BLUE
#endif
//        send_string(SS_LALT(SS_TAP(KC_LSHIFT())));	// ANSI��JIS
        nicola_off();
        nicola_pending = false;
        // NICOLA�e�w�V�t�g

/* LED�֘A�͂ЂƂ܂��R�����g�A�E�g
//        RGBLIGHT_MODE_RAINBOW_SWIRL(0);
//        rgblight_sethsv_at(170,255,40, RGBLED_NUM-1); // the last LED = BLUE (NICOLA off)
        for(int i=0; i<RGBLED_NUM; ++i) {
            rgblight_setrgb_at(0, 0, 128, i);  // BLUE
        }
*/

      }
      return false;
      break;
    case KC_KANA2:
      if (record->event.pressed) {
        if (IS_LAYER_ON(_FUNC)) {
          // legacy combo (Caps hold + R-SP): direct switch
          // v19: LANG1 only — HENK (変換) with an empty buffer re-converts the
          // previous clause (the persistent re-conversion bug). LANG1 alone
          // switches to kana mode with no side effects.
          tap_code(X_LANG1);   // Win/Mac: かな (kana)
          nicola_on(); nicola_pending = false;
#ifdef RGB_MATRIX_ENABLE
          rgb_matrix_mode_noeeprom(1); /* RGB_MATRIX_SOLID_COLOR */ // v20: leave rainbow/cycle animations so the hue is visible
          rgb_matrix_sethsv_noeeprom(85, 255, rgb_matrix_get_val()); // NICOLA mode = GREEN
#endif
          return false;
        }
        // v13: double tap = enter NICOLA (retract tap #1's real space)
        if (last_lsp_rel != 0 && TIMER_DIFF_16(timer_read(), last_lsp_rel) <= 300) {
          last_lsp_rel = 0;
          tap_code(KC_BSPC);       // retract the real space fired by tap #1
          // v19: LANG1 only (see FUNC-path note)
          tap_code(X_LANG1);   // Win/Mac: かな (kana)
          nicola_on(); nicola_pending = false;
#ifdef RGB_MATRIX_ENABLE
          rgb_matrix_mode_noeeprom(1); /* RGB_MATRIX_SOLID_COLOR */ // v20: leave rainbow/cycle animations so the hue is visible
          rgb_matrix_sethsv_noeeprom(85, 255, rgb_matrix_get_val()); // NICOLA mode = GREEN
#endif
          lsp_swallow = true;      // swallow the 2nd release too
          return false;
        }
        // v13: press #1 = REAL space (register: hold repeats like a normal space)
        register_code(KC_SPC);
        lsp_space_held = true;
        return false;
      } else {
        if (lsp_swallow) { lsp_swallow = false; return false; }
        if (lsp_space_held) { unregister_code(KC_SPC); lsp_space_held = false; }
        last_lsp_rel = timer_read();
        return false;
      }
      break;
      break;
  }

  // NICOLA�e�w�V�t�g
  // NICOLA mode: physical LEFT SHIFT + seion = dakuten/handaku (left-thumb-shift table).
  // Covers both KC_* (layer auto-off while shift held) and NG_* keycodes.
  // Capitals: use RIGHT shift (this block ignores it).
  // v9: Ctrl/Alt/Win held = OS shortcut combo: pass key through untouched
  if (combo_held) {
    // v23: drop the NICOLA layer while a shortcut combo is held, and translate
    // NG_* to KC_* so Win+D / Ctrl+C actually reach Windows in kana mode
    if (nicola_state()) { nicola_mode(keycode, record); }
    uint16_t k2 = ng_to_kc(keycode);
    if (k2 != KC_NO) {
      if (record->event.pressed) { register_code(k2); } else { unregister_code(k2); }
      return false;
    }
    return true;
  }

  // v2: LEFT SHIFT + seion = dakuten/handaku, robust version.
  // - uses explicitly tracked physical shift state (no get_mods() timing dependency)
  // - temporarily unregisters LSFT while sending, so symbols are not shifted
  // - right shift untouched (capitals)
  if (nicola_state() && lshift_held && !rshift_held) {
    if (record->event.pressed) {
    unregister_code(KC_LSFT);
    bool matched = true;
    // v26: pending is now set ONLY when matched (the unconditional set leaked
    // into unmatched keys like Shift+Caps -> stuck pending -> spurious 0x8B/0x8A
    // on the next thumb press = the "rare mode change" the user observed)
    switch (keycode) {
      case KC_1: case NG_1: send_string("?"); break;
      case KC_2: case NG_2: send_string("/"); break;
      case KC_3: case NG_3: send_string("+"); break;
      case KC_4: case NG_4: send_string("]"); break;
      case KC_5: case NG_5: tap_code(X_NUHS); break;
      case KC_6: case NG_6: send_string(SS_LSFT("]")); break;
      case KC_7: case NG_7: send_string(SS_LSFT(SS_TAP(X_NUHS))); break;
      case KC_8: case NG_8: send_string(SS_LSFT("8")); break;
      case KC_9: case NG_9: send_string(SS_LSFT("9")); break;
      case KC_0: case NG_0: send_string("("); break;
      case KC_MINS: case NG_MINS: send_string(SS_LSFT(SS_TAP(X_INT1))); break;
      case KC_EQL: case NG_EQL: send_string(SS_LSFT(";")); break;
      case KC_Q: case NG_Q: send_string("xa"); break;
      case KC_W: case NG_W: send_string("e"); break;
      case KC_E: case NG_E: send_string("ri"); break;
      case KC_R: case NG_R: send_string("xya"); break;
      case KC_T: case NG_T: send_string("re"); break;
      case KC_Y: case NG_Y: send_string("pa"); break;
      case KC_U: case NG_U: send_string("di"); break;
      case KC_I: case NG_I: send_string("gu"); break;
      case KC_O: case NG_O: send_string("du"); break;
      case KC_P: case NG_P: send_string("pi"); break;
      case KC_LBRC: case NG_LBRC: send_string("]"); break;
      case KC_RBRC: case NG_RBRC: tap_code(X_NUHS); break;
      case KC_BSLS: case NG_BSLS: send_string("\\"); break;
      case KC_A: case NG_A: send_string("wo"); break;
      case KC_S: case NG_S: send_string("a"); break;
      case KC_D: case NG_D: send_string("na"); break;
      case KC_F: case NG_F: send_string("xyu"); break;
      case KC_G: case NG_G: send_string("mo"); break;
      case KC_H: case NG_H: send_string("pa"); break;  // v31: Shift+H=pa (user spec - restores pre-v23 differentiation: Shift+H=PA / L-SP+H=BA)
      case KC_J: case NG_J: send_string("do"); break;
      case KC_K: case NG_K: send_string("gi"); break;
      case KC_L: case NG_L: send_string("po"); break;
      case KC_SCLN: case NG_SCLN: break; break;
      case KC_QUOT: case NG_QUOT: tap_code(KC_BSPC); break;
      case KC_Z: case NG_Z: send_string("xu"); break;
      case KC_X: case NG_X: send_string("-"); break;
      case KC_C: case NG_C: send_string("ro"); break;
      case KC_V: case NG_V: send_string("ya"); break;
      case KC_B: case NG_B: send_string("xi"); break;
      case KC_N: case NG_N: send_string("pu"); break;
      case KC_M: case NG_M: send_string("zo"); break;
      case KC_COMM: case NG_COMM: send_string("pe"); break;
      case KC_DOT: case NG_DOT: send_string("po"); break;
      case KC_SLSH: case NG_SLSH: send_string("?"); break;
      default: matched = false; break;
    }
    if (lshift_held) { register_code(KC_LSFT); }
    lshift_ate = matched;
    if (matched) { nicola_pending = true; return false; }  // v26
    } else {
      if (lshift_ate) { lshift_ate = false; return false; }
    }
  }

  // v5: RIGHT SHIFT + selected keys = handaku (pi/pu/pe). Other keys keep normal shift (capitals).
  if (nicola_state() && rshift_held && !lshift_held) {
    if (record->event.pressed) {
    unregister_code(KC_RSFT);
    bool matched = true;
    // v26: pending only when matched (same fix as LSHIFT block)
    switch (keycode) {
      case KC_X: case NG_X: send_string("pi"); break;
      case KC_V: case NG_V: send_string("pu"); break;
      case KC_B: case NG_B: send_string("pe"); break;
      default: matched = false; break;
    }
    if (rshift_held) { register_code(KC_RSFT); }
    rshift_ate = matched;
    if (matched) { nicola_pending = true; return false; }  // v26
    } else {
      if (rshift_ate) { rshift_ate = false; return false; }
    }
  }

  bool a = true;
  // v15: while _FUNC is held (CapsLock), the R-SP press can leak the base layer's KC_SPC
  // into the IME before KC_KANA2 fires -> a space lands in the pending clause -> re-conversion mode.
  // Swallow KC_SPC entirely while Caps is held (its space role is not needed during the combo).
  if (IS_LAYER_ON(_FUNC) && keycode == KC_SPC) {
    if (record->event.pressed) { /* swallow press */ }
    else { /* swallow release too */ }
    return false;
  }
  // thumb keys during _FUNC belong to the mode-switch layer: never feed the nicola engine
  if (IS_LAYER_ON(_FUNC) && (keycode == NG_SHFTL || keycode == NG_SHFTR)) {
    return true;
  }
  if (nicola_state()) {
    nicola_mode(keycode, record);
    a = process_nicola(keycode, record);
  }
  if (a == false) return false;
  // NICOLA�e�w�V�t�g

  bool continue_process = process_jtu(keycode, record);
  if (continue_process == false) {
    return false;
  }

  return true;
}

// �����܂�nicola mechanism�̈ڐA�̈�

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [1] = {ENCODER_CCW_CW(_______, _______)},
    [2] = {ENCODER_CCW_CW(_______, _______)},
    [3] = {ENCODER_CCW_CW(_______, _______)},
};
#endif
// clang-format on

// v25: override removed. QMK's split_common default (SPLIT_USB_DETECT, default-on
// for ChibiOS/ARM) makes master = the half with an active USB connection.
// => USB in left  = left master  (normal use, unchanged)
// => USB in right = right master (FL+M / Caps+ESC then work on the right half!)
// HandEDNESS (key layout mirror) still comes from split.handedness.pin = B9 (keyboard.json).
// Wireless note: the wireless module is driven from the master; with USB in the right
// half, wireless commands may not reach it - irrelevant for wired-only use.
