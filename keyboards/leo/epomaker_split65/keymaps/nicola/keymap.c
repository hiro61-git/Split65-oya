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
  KC_KANA2
};

 //�I���W�i����"LAYOUT_62_ansi_2space"���Ȃ���������"LAYOUT"�֕ύX
 //"LAYOUT"�͈���69�ɑ΂��āAansi������65�ő���Ȃ��������߁A�_�~�[��4�ǉ���������Œ���
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT( \
      KC_ESC,  KC_1,    JU_2,    KC_3,    KC_4,    KC_5,    JU_6,           JU_7,   JU_8,    JU_9,    JU_0,    JU_MINS,  JU_EQL,  KC_BSPC,   KC_MUTE, \
      KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                 KC_Y,    KC_U,   KC_I,    KC_O,    KC_P,  JU_LBRC,  JU_RBRC,  JU_BSLS,  KC_DEL, \
      LT(_FUNC, KC_EISU), KC_A,  KC_S,    KC_D,    KC_F,    KC_G,              KC_H,    KC_J,   KC_K,    KC_L,    JU_SCLN, JU_QUOT,  KC_ENT, KC_PGUP, \
      KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,           KC_N,    KC_M,   KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,  KC_UP,   KC_PGDN,  \
      KC_LCTL, KC_LCMD , KC_LALT,             KC_KANA2,      KC_SPC, KC_DEL, MO(_FL), KC_RCTL, KC_LEFT,  KC_DOWN, KC_RIGHT ), 


  // NICOLA入力レイヤー(この定義が有効)
  [_NICOLA] = LAYOUT( \
      KC_ESC,  NG_1,    NG_2,    NG_3,    NG_4,    NG_5,    NG_6,           NG_7,   NG_8,    NG_9,    NG_0,    NG_MINS,  NG_EQL,  KC_BSPC,   KC_MUTE, \
      KC_TAB,  NG_Q,    NG_W,    NG_E,    NG_R,    NG_T,                 NG_Y,    NG_U,   NG_I,    NG_O,    NG_P,  NG_LBRC,  NG_RBRC,  NG_BSLS,  KC_DEL, \
      LT(_FUNC, KC_EISU), NG_A,  NG_S,    NG_D,    NG_F,    NG_G,              NG_H,    NG_J,   NG_K,    NG_L,    NG_SCLN, NG_QUOT,  KC_ENT, KC_PGUP,  \
      KC_LSFT, NG_Z,    NG_X,    NG_C,    NG_V,    NG_B,           NG_N,    NG_M,   NG_COMM, NG_DOT,  NG_SLSH, KC_RSFT,  KC_UP,  KC_PGDN,   \
      KC_LCTL, KC_LCMD,  KC_LALT,             NG_SHFTL,     NG_SHFTR, KC_DEL, MO(_FL), KC_RCTL, KC_LEFT, KC_DOWN, KC_RIGHT ),

  // Function Layer, KC_BSLS is not confirmed
  // ファンクション層(CapsLockホールド)
  [_FUNC] = LAYOUT( \
      JU_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,          KC_F7,  KC_F8,   KC_F9,   KC_F10,  KC_F11,   KC_F12,  KC_DEL,    KC_MUTE, \
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RGB_TOG,              LCTL(KC_LEFT), KC_PGDN, KC_PGUP, LCTL(KC_RIGHT), KC_PSCR, KC_TRNS, KC_BRK, KC_TRNS,  KC_TRNS, \
      MO(_FUNC), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,        KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, KC_INS,  KC_DEL,  KC_ENT, KC_PGUP,  \
      KC_LSFT, KC_TRNS,KC_TRNS,LCTL(KC_C),LCTL(KC_V),KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_SLSH, KC_RSFT, KC_UP,  KC_PGDN,   \
      KC_TRNS, KC_TRNS,    KC_TRNS,             KC_EISU,      KC_KANA2, KC_TRNS, MO(_FL), KC_HOME, KC_LEFT, KC_DOWN, KC_RIGHT ),

  // Function layer of split65
  [_FL] = LAYOUT( \
      KC_GRV,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,              KC_F6,    KC_F7,    KC_F8,    KC_F9,     KC_F10,   KC_F11,  KC_F12,   EE_CLR,   KC_TRNS, \
      RGB_MOD,  KC_BT1,   KC_BT2,   KC_BT3,   KC_2G4,   KC_TRNS,            KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS,    KC_TRNS,  RGB_HUD, RGB_HUI,  KC_TRNS,  KC_INS,  \
      KC_TRNS,  KC_A,     KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS,    RGB_SAD,  RGB_SAI, KC_TRNS,            KC_HOME, \
      KC_TRNS,  KC_TRNS,  RGB_TOG,  KC_TRNS,  KC_TRNS,  KC_TRNS,            NK_TOGG,  KC_TRNS,  KC_TRNS, KC_TRNS,    KC_TRNS,           KC_TRNS,  RGB_VAI,  KC_END, \
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

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  // v2: explicit physical shift tracking (independent of get_mods() timing)
  static bool lshift_held = false, rshift_held = false;
  if (keycode == KC_LSFT)      { lshift_held = record->event.pressed; }
  else if (keycode == KC_RSFT) { rshift_held = record->event.pressed; }

  switch (keycode) {
    case KC_EISU:
      if (record->event.pressed) {
        // NICOLA�e�w�V�t�g
        if (nicola_state()) {
          // 日本語モードからの切替は Alt+`(半角/全角)のみ送出。
          // 無変換/英数を追加で送ると MS-IME の既定トグルが再発火して IME が戻るため送らない。
          tap_code16(LALT(KC_GRV)); // Win: Alt+` = OSレベルのIME ON/OFFトグル
        } else {
          tap_code(X_LANG2);     // Mac: 英数(既に英字モード時の保険)
        }
#ifdef RGB_MATRIX_ENABLE
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
        // NICOLA�e�w�V�t�g
//        send_string(SS_LALT(SS_TAP(KC_LSHIFT())));	// ANSI��JIS
        //send_string(SS_TAP(X_HENK));		// Win
        tap_code(X_HENK);      // Win	
        //send_string(SS_TAP(X_LANG1));		// Mac
        tap_code(X_LANG1);     // Mac
#ifdef RGB_MATRIX_ENABLE
        rgb_matrix_sethsv_noeeprom(85, 255, rgb_matrix_get_val()); // NICOLA mode = GREEN
#endif
        nicola_on();
        nicola_pending = false;
        // NICOLA�e�w�V�t�g

/* LED�֘A�͂ЂƂ܂��R�����g�A�E�g
//        RGBLIGHT_MODE_RAINBOW_MOOD(0);
//        rgblight_sethsv_at(85,255,40, RGBLED_NUM-1); // the last LED = GREEN (NICOLA on)
        for(int i=0; i<RGBLED_NUM; ++i) {
            rgblight_setrgb_at(0, 126, 0, i);	// GREEN
        }
*/

      }
      return false;
      break;
  }

  // NICOLA�e�w�V�t�g
  // NICOLA mode: physical LEFT SHIFT + seion = dakuten/handaku (left-thumb-shift table).
  // Covers both KC_* (layer auto-off while shift held) and NG_* keycodes.
  // Capitals: use RIGHT shift (this block ignores it).
  // v2: LEFT SHIFT + seion = dakuten/handaku, robust version.
  // - uses explicitly tracked physical shift state (no get_mods() timing dependency)
  // - temporarily unregisters LSFT while sending, so symbols are not shifted
  // - right shift untouched (capitals)
  if (nicola_state() && lshift_held && !rshift_held) {
    if (!record->event.pressed) { return false; } // v3: swallow release (press already sent it - no double output)
    unregister_code(KC_LSFT);
    bool matched = true;
    nicola_pending = true; // kana output follows -> pending state
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
      case KC_H: case NG_H: send_string("pa"); break;
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
    if (matched) { return false; }
  }

  // v5: RIGHT SHIFT + selected keys = handaku (pi/pu/pe). Other keys keep normal shift (capitals).
  if (nicola_state() && rshift_held && !lshift_held) {
    if (!record->event.pressed) { return false; }
    unregister_code(KC_RSFT);
    bool matched = true;
    nicola_pending = true;
    switch (keycode) {
      case KC_X: case NG_X: send_string("pi"); break;
      case KC_V: case NG_V: send_string("pu"); break;
      case KC_B: case NG_B: send_string("pe"); break;
      default: matched = false; break;
    }
    if (rshift_held) { register_code(KC_RSFT); }
    if (matched) { return false; }
  }

  bool a = true;
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

bool is_keyboard_master(void) {
    setPinInput(SPLIT_HAND_PIN);
    return readPin(SPLIT_HAND_PIN);
}

