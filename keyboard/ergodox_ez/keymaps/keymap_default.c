#include "ergodox_ez.h"
#include "debug.h"
#include "action_layer.h"

#define BASE 0 // default layer
#define SYML 1 // symbols left
#define SYMR 2 // symbols right
#define DIGI 3 // digital pad & mouse
#define MOUS 4 // mouse
#define AROW 5 // arrow keys on HJKL
#define HPPE 6 // Home/PgDn/PgUp/End keys on HJKL

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*  BASE
 * ┌─────┬───┬───┬───┬───┬───┬───┐                   ┌───┬───┬───┬───┬───┬───┬─────┐
 * │  `  │ 1 │ 2 │ 3 │ 4 │ 5 │Ins│                   │Del│ 6 │ 7 │ 8 │ 9 │ 0 │Bak  │
 * ├─────┼───┼───┼───┼───┼───┼───┤                   ├───┼───┼───┼───┼───┼───┼─────┤
 * │Tab  │ Q │ W │ E │ R │ T │Hom│                   │PUp│ Y │ U │ I │ O │ P │  \  │
 * ├─────┼───┼───┼───┼───┼───┤   │                   │   ├───┼───┼───┼───┼───┼─────┤
 * │Ctrl │ A │ S │ D │ F │ G ├───┤                   ├───┤ H │ J │ K │ L │ ; │'Ctrl│
 * ├─────┼───┼───┼───┼───┼───┤End│                   │PDn├───┼───┼───┼───┼───┼─────┤
 * │Shift│ Z │ X │ C │ V │ B │   │┌───┬───┐ ┌───┬───┐│   │ N │ M │ , │ . │ / │Shift│
 * └─┬───┼───┼───┼───┼───┼───┴───┘│Pri│ScLk Vol-│Vol+└───┴───┼───┼───┼───┼───┼───┬─┘
 *   │Alt│ ← │ ↓ │ ↑ │ → │    ┌───┼───┼───┤ ├───┼───┼───┐    │ - │ = │ [ │ ] │Alt│
 *   └───┴───┴───┴───┴───┘    │Sp │Bak│Pause│L0 │Esc│Ent│    └───┴───┴───┴───┴───┘
 *                            │   │   ├───┤ ├───┤   │   │
 *                            │   │   │Win│ │Win│   │   │
 *                            └───┴───┴───┘ └───┴───┴───┘
 *  SYML / SYMR                                                         Hold J or F
 * ┌─────┬───┬───┬───┬───┬───┬───┐                   ┌───┬───┬───┬───┬───┬───┬─────┐
 * │     │F1 │F2 │F3 │F4 │F5 │   │                   │   │F6 │F7 │F8 │F9 │F10│ F11 │
 * ├─────┼───┼───┼───┼───┼───┼───┤                   ├───┼───┼───┼───┼───┼───┼─────┤
 * │     │   │ \ │ = │   │ ~ │   │                   │   │   │   │ _ │ # │ + │ F12 │
 * ├─────┼───┼───┼───┼───┼───┤   │                   │   ├───┼───┼───┼───┼───┼─────┤
 * │     │ & │ * │ $ │ _ │ ` ├───┤                   ├───┤ ^ │ ( │ ) │ { │ } │     │
 * ├─────┼───┼───┼───┼───┼───┤   │                   │   ├───┼───┼───┼───┼───┼─────┤
 * │     │   │ ! │ % │ | │   │   │┌───┬───┐ ┌───┬───┐│   │   │ - │   │ @ │   │     │
 * └─┬───┼───┼───┼───┼───┼───┴───┘│   │   │ │   │   │└───┴───┼───┼───┼───┼───┼───┬─┘
 *   │   │   │   │   │   │    ┌───┼───┼───┤ ├───┼───┼───┐    │   │   │   │   │   │
 *   └───┴───┴───┴───┴───┘    │   │   │   │ │   │   │   │    └───┴───┴───┴───┴───┘
 *                            │   │   ├───┤ ├───┤   │   │
 *                            │   │   │   │ │   │   │   │
 *                            └───┴───┴───┘ └───┴───┴───┘
 *  MOUS / DIGI                                                         Hold M or D
 * ┌─────┬───┬───┬───┬───┬───┬───┐                   ┌───┬───┬───┬───┬───┬───┬─────┐
 * │     │   │   │   │   │   │   │                   │   │   │NLk│ / │ * │ - │     │
 * ├─────┼───┼───┼───┼───┼───┼───┤                   ├───┼───┼───┼───┼───┼───┼─────┤
 * │     │   │   │m↑ │   │   │   │                   │   │   │ 7 │ 8 │ 9 │ + │     │
 * ├─────┼───┼───┼───┼───┼───┤   │                   │   ├───┼───┼───┼───┼───┼─────┤
 * │     │   │m← │m↓ │m→ │   ├───┤                   ├───┤   │ 4 │ 5 │ 6 │ + │     │
 * ├─────┼───┼───┼───┼───┼───┤   │                   │   ├───┼───┼───┼───┼───┼─────┤
 * │     │   │   │   │   │   │   │┌───┬───┐ ┌───┬───┐│   │   │ 1 │ 2 │ 3 │Ent│     │
 * └─┬───┼───┼───┼───┼───┼───┴───┘│   │   │ │   │   │└───┴───┼───┼───┼───┼───┼───┬─┘
 *   │   │   │   │LMB│RMB│    ┌───┼───┼───┤ ├───┼───┼───┐    │ 0 │ 0 │ . │Ent│   │
 *   └───┴───┴───┴───┴───┘    │   │   │   │ │   │   │   │    └───┴───┴───┴───┴───┘
 *                            │   │   ├───┤ ├───┤   │   │
 *                            │   │   │   │ │   │   │   │
 *                            └───┴───┴───┘ └───┴───┴───┘
 *  AROW                                                                     Hold A
 * ┌─────┬───┬───┬───┬───┬───┬───┐                   ┌───┬───┬───┬───┬───┬───┬─────┐
 * │     │   │   │   │   │   │   │                   │   │   │   │   │   │   │     │
 * ├─────┼───┼───┼───┼───┼───┼───┤                   ├───┼───┼───┼───┼───┼───┼─────┤
 * │     │   │   │   │   │   │   │                   │   │   │   │   │   │   │     │
 * ├─────┼───┼───┼───┼───┼───┤   │                   │   ├───┼───┼───┼───┼───┼─────┤
 * │     │   │   │   │   │   ├───┤                   ├───┤ ← │ ↓ │ ↑ │ → │   │     │
 * ├─────┼───┼───┼───┼───┼───┤   │                   │   ├───┼───┼───┼───┼───┼─────┤
 * │     │   │   │   │   │   │   │┌───┬───┐ ┌───┬───┐│   │   │   │   │   │   │     │
 * └─┬───┼───┼───┼───┼───┼───┴───┘│   │   │ │   │   │└───┴───┼───┼───┼───┼───┼───┬─┘
 *   │   │   │   │   │   │    ┌───┼───┼───┤ ├───┼───┼───┐    │   │   │   │   │   │
 *   └───┴───┴───┴───┴───┘    │   │   │   │ │   │   │   │    └───┴───┴───┴───┴───┘
 *                            │   │   ├───┤ ├───┤   │   │
 *                            │   │   │   │ │   │   │   │
 *                            └───┴───┴───┘ └───┴───┴───┘
 *  HPPE                                                                     Hold Z
 * ┌─────┬───┬───┬───┬───┬───┬───┐                   ┌───┬───┬───┬───┬───┬───┬─────┐
 * │     │   │   │   │   │   │   │                   │   │   │   │   │   │   │     │
 * ├─────┼───┼───┼───┼───┼───┼───┤                   ├───┼───┼───┼───┼───┼───┼─────┤
 * │     │   │   │   │   │   │   │                   │   │   │   │   │   │   │     │
 * ├─────┼───┼───┼───┼───┼───┤   │                   │   ├───┼───┼───┼───┼───┼─────┤
 * │     │   │   │   │   │   ├───┤                   ├───┤Hom│PDn│PUp│End│   │     │
 * ├─────┼───┼───┼───┼───┼───┤   │                   │   ├───┼───┼───┼───┼───┼─────┤
 * │     │   │   │   │   │   │   │┌───┬───┐ ┌───┬───┐│   │   │   │   │   │   │     │
 * └─┬───┼───┼───┼───┼───┼───┴───┘│   │   │ │   │   │└───┴───┼───┼───┼───┼───┼───┬─┘
 *   │   │   │   │   │   │    ┌───┼───┼───┤ ├───┼───┼───┐    │   │   │   │   │   │
 *   └───┴───┴───┴───┴───┘    │   │   │   │ │   │   │   │    └───┴───┴───┴───┴───┘
 *                            │   │   ├───┤ ├───┤   │   │
 *                            │   │   │   │ │   │   │   │
 *                            └───┴───┴───┘ └───┴───┴───┘
 */
[BASE] = KEYMAP(  // layer 0 : default
        // left hand
        KC_GRV, KC_1,         KC_2,   KC_3,         KC_4,         KC_5,KC_INS,
        KC_TAB, KC_Q,         KC_W,   KC_E,         KC_R,         KC_T,KC_HOME,
        KC_LCTL,LT(AROW,KC_A),KC_S,   LT(DIGI,KC_D),LT(SYMR,KC_F),KC_G,
        KC_LSFT,LT(HPPE,KC_Z),KC_X,   KC_C,         KC_V,         KC_B,KC_END,
        KC_LALT,KC_LEFT,      KC_DOWN,KC_UP,        KC_RGHT,
                                                         KC_PSCR, KC_SLCK,
                                                                  KC_PAUS,
                                                 KC_SPC, KC_BSPC, KC_LGUI,
        // right hand
        KC_DELETE, KC_6,  KC_7,         KC_8,    KC_9,    KC_0,    KC_BSPC,
        KC_PGUP,   KC_Y,  KC_U,         KC_I,    KC_O,    KC_P,    KC_BSLS,
                   KC_H,  LT(SYML,KC_J),KC_K,    KC_L,    KC_SCLN, CTL_T(KC_QUOT),
        KC_PGDN,   KC_N,  LT(MOUS,KC_M),KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
                          KC_UP,        KC_DOWN, KC_LBRC, KC_RBRC, KC_FN1,
             KC_VOLD,         KC_VOLU,
             0,
             KC_RGUI, KC_ESC, KC_ENT
    ),
[SYML] = KEYMAP(
       // left hand
       KC_TRNS,KC_F1,     KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_TRNS,
       KC_TRNS,S(KC_QUOT),KC_BSLS,KC_EQL, KC_NO,  KC_TILD,KC_TRNS,
       KC_TRNS,KC_AMPR,   KC_ASTR,KC_DLR, KC_UNDS,KC_GRV,
       KC_TRNS,KC_NO,     KC_EXLM,KC_PERC,KC_PIPE,KC_NO,  KC_TRNS,

       KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
                                       KC_TRNS,KC_TRNS,
                                               KC_TRNS,
                               KC_TRNS,KC_TRNS,KC_TRNS,
       // right hand
       KC_TRNS,  KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
       KC_TRNS,  KC_NO,   KC_NO,   KC_UNDS, KC_HASH, KC_PLUS, KC_F12,
                 KC_CIRC, KC_TRNS, KC_RPRN, KC_LCBR, KC_RCBR, KC_TRNS, /* <-- TRNS! */
       KC_TRNS,  KC_NO,   KC_MINS, KC_TRNS, KC_AT,   KC_TRNS, KC_TRNS,
                          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
),
[SYMR] = KEYMAP(
       // left hand
       KC_TRNS,KC_F1,     KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_TRNS,
       KC_TRNS,S(KC_QUOT),KC_BSLS,KC_EQL, KC_NO,  KC_TILD,KC_TRNS,
       KC_TRNS,KC_AMPR,   KC_ASTR,KC_DLR, KC_TRNS,KC_GRV, /* <-- TRNS! */
       KC_TRNS,KC_NO,     KC_EXLM,KC_PERC,KC_PIPE,KC_NO,  KC_TRNS,

       KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
                                       KC_TRNS,KC_TRNS,
                                               KC_TRNS,
                               KC_TRNS,KC_TRNS,KC_TRNS,
       // right hand
       KC_TRNS,  KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
       KC_TRNS,  KC_NO,   KC_NO,   KC_UNDS, KC_HASH, KC_PLUS, KC_F12,
                 KC_CIRC, KC_LPRN, KC_RPRN, KC_LCBR, KC_RCBR, KC_TRNS,
       KC_TRNS,  KC_NO,   KC_MINS, KC_TRNS, KC_AT,   KC_TRNS, KC_TRNS,
                          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
),
[DIGI] = KEYMAP(
       // left hand
       KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_TRNS,
       KC_TRNS, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_TRNS,
       KC_TRNS, KC_NO,   KC_NO,   KC_TRNS, KC_NO,   KC_NO, /* <-- TRNS! */
       KC_TRNS, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                           KC_TRNS, KC_TRNS,
                                                    KC_TRNS,
                                  KC_TRNS, KC_TRNS, KC_TRNS,
       // right hand
       KC_TRNS, KC_NO,   KC_NLCK, KC_SLSH, KC_ASTR, KC_MINS, KC_NO,
       KC_TRNS, KC_NO,   KC_7,    KC_8,    KC_9,    KC_PLUS, KC_NO,
                KC_NO,   KC_4,    KC_5,    KC_6,    KC_PLUS, KC_RCTL,
       KC_TRNS, KC_NO,   KC_1,    KC_2,    KC_3,    KC_ENT,  KC_TRNS,
                         KC_0,    KC_0,    KC_DOT,  KC_ENT,  KC_TRNS,
                KC_TRNS, KC_TRNS,
                KC_TRNS,
                KC_TRNS, KC_TRNS, KC_TRNS
),
[MOUS] = KEYMAP(
       // left hand
       KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_TRNS,
       KC_TRNS, KC_NO,   KC_NO,   KC_MS_U, KC_NO,   KC_NO,   KC_TRNS,
       KC_TRNS, KC_NO,   KC_MS_L, KC_MS_D, KC_MS_R, KC_NO,  
       KC_TRNS, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_BTN1, KC_BTN2,
                                           KC_TRNS, KC_TRNS,
                                                    KC_TRNS,
                                  KC_TRNS, KC_TRNS, KC_TRNS,
       // right hand
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                KC_TRNS, KC_TRNS,
                KC_TRNS,
                KC_TRNS, KC_TRNS, KC_TRNS
),
[AROW] = KEYMAP(
       // left hand
       KC_NO,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                           KC_TRNS, KC_TRNS,
                                                    KC_TRNS,
                                  KC_TRNS, KC_TRNS, KC_TRNS,
       // right hand
       KC_TRNS, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
       KC_TRNS, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
                KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_NO,   KC_RCTL,
       KC_TRNS, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_TRNS,
                         KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_TRNS,
                KC_TRNS, KC_TRNS,
                KC_TRNS,
                KC_TRNS, KC_TRNS, KC_TRNS
),
[HPPE] = KEYMAP(
       // left hand
       KC_NO,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                           KC_TRNS, KC_TRNS,
                                                    KC_TRNS,
                                  KC_TRNS, KC_TRNS, KC_TRNS,
       // right hand
       KC_TRNS, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
       KC_TRNS, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
                KC_HOME, KC_PGDN, KC_PGUP, KC_END,  KC_NO,   KC_RCTL,
       KC_TRNS, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_TRNS,
                         KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_TRNS,
                KC_TRNS, KC_TRNS,
                KC_TRNS,
                KC_TRNS, KC_TRNS, KC_TRNS
),
};

const uint16_t PROGMEM fn_actions[] = {
    [SYML] = ACTION_LAYER_TAP_TOGGLE(SYML),
    [SYMR] = ACTION_LAYER_TAP_TOGGLE(SYMR),
    [MOUS] = ACTION_LAYER_TAP_TOGGLE(MOUS),
    [AROW] = ACTION_LAYER_TAP_TOGGLE(AROW),
    [HPPE] = ACTION_LAYER_TAP_TOGGLE(HPPE),
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
      switch(id) {
        case 0:
        if (record->event.pressed) {
          register_code(KC_RSFT);
        } else {
          unregister_code(KC_RSFT);
        }
        break;
      }
    return MACRO_NONE;
};

// Runs just one time when the keyboard initializes.
void * matrix_init_user(void) {
    return NULL;
};

// Runs constantly in the background, in a loop.
void * matrix_scan_user(void) {

    uint8_t layer = biton32(layer_state);

    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();

    if ((layer) % 2)
            ergodox_right_led_3_on();

    if ((layer >> 1) % 2)
            ergodox_right_led_2_on();

    if ((layer >> 2) % 2)
            ergodox_right_led_1_on();

    return NULL;
};
