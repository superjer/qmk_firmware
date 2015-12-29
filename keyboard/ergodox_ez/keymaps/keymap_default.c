#include "ergodox_ez.h"
#include "debug.h"
#include "action_layer.h"

#define BASE 0 // default layer
#define EASY 1 // enter, tab, bksp, etc
#define SYMB 2 // symbols
#define DIGI 3 // digital pad
#define MOVE 4 // arrow keys on HJKL

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*  BASE
 * ┌─────┬───┬───┬───┬───┬───┬───┐                   ┌───┬───┬───┬───┬───┬───┬─────┐
 * │  `  │ 1 │ 2 │ 3 │ 4 │ 5 │Ins│                   │Del│ 6 │ 7 │ 8 │ 9 │ 0 │Bsp  │
 * ├─────┼───┼───┼───┼───┼───┼───┤                   ├───┼───┼───┼───┼───┼───┼─────┤
 * │Tab  │ Q │ W │ E │ R │ T │Hom│                   │PUp│ Y │ U │ I │ O │ P │  \  │
 * ├─────┼───┼───┼───┼───┼───┤   │                   │   ├───┼───┼───┼───┼───┼─────┤
 *Esc/Ctl│ A │ S │ D │ F │ G ├───┤                   ├───┤ H │ J │ K │ L │+; │'/Ctl│--;=EASY
 * ├─────┼───┼───┼───┼───┼───┤End│                   │PDn├───┼───┼───┼───┼───┼─────┤
 * │Shift│+Z │ X │ C │ V │ B │   │┌───┬───┐ ┌───┬───┐│   │ N │ M │ , │ . │+/ │Shift│--/=SYMB
 * └─┬───┼───┼───┼───┼───┼───┴───┘│Pri│ScLk Vol-│Vol+└───┴───┼───┼───┼───┼───┼───┬─┘
 *   Alt MOVE│DIGI ( │ ) │    ┌───┼───┼───┤ ├───┼───┼───┐    │ - │ = │ [ │ ] │Alt│
 *   └───┴───┴───┴───┴───┘    │Sp │Esc│Pause│Mut│Ent│Sp │    └───┴───┴───┴───┴───┘
 *         |                  │   │   ├───┤ ├───┤   │   │
 *         Z=SYMB             │   │   │Win│ │Win│   │   │
 *                            └───┴───┴───┘ └───┴───┴───┘
 *  EASY                                                                     Hold ;
 * ┌─────┬───┬───┬───┬───┬───┬───┐                   ┌───┬───┬───┬───┬───┬───┬─────┐
 * │     │   │   │   │   │   │   │                   │   │   │   │   │   │   │     │
 * ├─────┼───┼───┼───┼───┼───┼───┤                   ├───┼───┼───┼───┼───┼───┼─────┤
 * │     │   │   │   │   │   │   │                   │   │   │   │   │   │   │     │
 * ├─────┼───┼───┼───┼───┼───┤   │                   │   ├───┼───┼───┼───┼───┼─────┤
 * │     │Tab│Sp │Del│Bsp│   ├───┤                   ├───┤   │Ent│   │Esc│XXX│     │
 * ├─────┼───┼───┼───┼───┼───┤   │                   │   ├───┼───┼───┼───┼───┼─────┤
 * │     │   │   │   │   │   │   │┌───┬───┐ ┌───┬───┐│   │   │   │   │   │   │     │
 * └─┬───┼───┼───┼───┼───┼───┴───┘│   │   │ │   │   │└───┴───┼───┼───┼───┼───┼───┬─┘
 *   │   │   │   │   │   │    ┌───┼───┼───┤ ├───┼───┼───┐    │   │   │   │   │   │
 *   └───┴───┴───┴───┴───┘    │   │   │   │ │   │   │   │    └───┴───┴───┴───┴───┘
 *                            │   │   ├───┤ ├───┤   │   │
 *                            │   │   │   │ │   │   │   │
 *                            └───┴───┴───┘ └───┴───┴───┘
 *  SYMB                                                                Hold Z or /
 * ┌─────┬───┬───┬───┬───┬───┬───┐                   ┌───┬───┬───┬───┬───┬───┬─────┐
 * │     │F1 │F2 │F3 │F4 │F5 │   │                   │   │F6 │F7 │F8 │F9 │F10│ F11 │
 * ├─────┼───┼───┼───┼───┼───┼───┤                   ├───┼───┼───┼───┼───┼───┼─────┤
 * │     │ " │ \ │ = │ % │ ~ │   │                   │   │   │ _ │ ' │ # │ + │ F12 │
 * ├─────┼───┼───┼───┼───┼───┤   │                   │   ├───┼───┼───┼───┼───┼─────┤
 * │     │ @ │ * │ $ │ _ │ ` ├───┤                   ├───┤ # │ ( │ ) │ [ │ ] │     │
 * ├─────┼───┼───┼───┼───┼───┤   │                   │   ├───┼───┼───┼───┼───┼─────┤
 * │     │XXX│ ! │ ^ │ | │ \ │   │┌───┬───┐ ┌───┬───┐│   │ & │ - │ { │ } │XXX│     │
 * └─┬───┼───┼───┼───┼───┼───┴───┘│   │   │ │   │   │└───┴───┼───┼───┼───┼───┼───┬─┘
 *   │   │   │   │   │   │    ┌───┼───┼───┤ ├───┼───┼───┐    │   │   │   │   │   │
 *   └───┴───┴───┴───┴───┘    │   │   │   │ │   │   │   │    └───┴───┴───┴───┴───┘
 *                            │   │   ├───┤ ├───┤   │   │
 *                            │   │   │   │ │   │   │   │
 *                            └───┴───┴───┘ └───┴───┴───┘
 *  DIGI                                                                  Hold DIGI
 * ┌─────┬───┬───┬───┬───┬───┬───┐                   ┌───┬───┬───┬───┬───┬───┬─────┐
 * │     │   │   │   │   │   │   │                   │   │   │NLk│ / │ * │ - │     │
 * ├─────┼───┼───┼───┼───┼───┼───┤                   ├───┼───┼───┼───┼───┼───┼─────┤
 * │     │   │   │   │   │   │   │                   │   │   │ 7 │ 8 │ 9 │ + │     │
 * ├─────┼───┼───┼───┼───┼───┤   │                   │   ├───┼───┼───┼───┼───┼─────┤
 * │     │   │   │   │   │   ├───┤                   ├───┤   │ 4 │ 5 │ 6 │ + │     │
 * ├─────┼───┼───┼───┼───┼───┤   │                   │   ├───┼───┼───┼───┼───┼─────┤
 * │     │   │   │   │   │   │   │┌───┬───┐ ┌───┬───┐│   │   │ 1 │ 2 │ 3 │Ent│     │
 * └─┬───┼───┼───┼───┼───┼───┴───┘│   │   │ │   │   │└───┴───┼───┼───┼───┼───┼───┬─┘
 *   │   │   │XXX│   │   │    ┌───┼───┼───┤ ├───┼───┼───┐    │ 0 │ 0 │ . │Ent│   │
 *   └───┴───┴───┴───┴───┘    │   │   │   │ │   │   │   │    └───┴───┴───┴───┴───┘
 *                            │   │   ├───┤ ├───┤   │   │
 *                            │   │   │   │ │   │   │   │
 *                            └───┴───┴───┘ └───┴───┴───┘
 *  MOVE                                                                  Hold MOVE
 * ┌─────┬───┬───┬───┬───┬───┬───┐                   ┌───┬───┬───┬───┬───┬───┬─────┐
 * │     │   │   │   │   │   │   │                   │   │   │   │   │   │   │     │
 * ├─────┼───┼───┼───┼───┼───┼───┤                   ├───┼───┼───┼───┼───┼───┼─────┤
 * │     │   │   │   │   │   │   │                   │   │   │Hom│PUp│   │   │     │
 * ├─────┼───┼───┼───┼───┼───┤   │                   │   ├───┼───┼───┼───┼───┼─────┤
 * │     │   │   │   │   │   ├───┤                   ├───┤ ← │ ↓ │ ↑ │ → │   │     │
 * ├─────┼───┼───┼───┼───┼───┤   │                   │   ├───┼───┼───┼───┼───┼─────┤
 * │     │   │LMB│m↑ │RMB│   │   │┌───┬───┐ ┌───┬───┐│   │   │End│PDn│   │   │     │
 * └─┬───┼───┼───┼───┼───┼───┴───┘│   │   │ │   │   │└───┴───┼───┼───┼───┼───┼───┬─┘
 *   │   │XXX│m← │m↓ │m→ │    ┌───┼───┼───┤ ├───┼───┼───┐    │   │   │   │   │   │
 *   └───┴───┴───┴───┴───┘    │   │   │   │ │   │   │   │    └───┴───┴───┴───┴───┘
 *                            │   │   ├───┤ ├───┤   │   │
 *                            │   │   │   │ │   │   │   │
 *                            └───┴───┴───┘ └───┴───┴───┘
 */
[BASE] = KEYMAP(  // layer 0 : default
        // left hand
        KC_GRV,       KC_1,         KC_2,    KC_3,   KC_4,   KC_5,    KC_INS,
        KC_TAB,       KC_Q,         KC_W,    KC_E,   KC_R,   KC_T,    KC_HOME,
        CTL_T(KC_ESC),KC_A,         KC_S,    KC_D,   KC_F,   KC_G,   
        KC_LSFT,      LT(SYMB,KC_Z),KC_X,    KC_C,   KC_V,   KC_B,    KC_END,
        KC_LALT,      MO(MOVE),     MO(DIGI),KC_LPRN,KC_RPRN,
                                                               KC_PSCR, KC_SLCK,
                                                                        KC_PAUS,
                                                       KC_SPC, KC_ESC,  KC_LGUI,
        // right hand
        KC_DELETE, KC_6,  KC_7,   KC_8,   KC_9,    KC_0,             KC_BSPC,
        KC_PGUP,   KC_Y,  KC_U,   KC_I,   KC_O,    KC_P,             KC_BSLS,
                   KC_H,  KC_J,   KC_K,   KC_L,    LT(EASY,KC_SCLN), CTL_T(KC_QUOT),
        KC_PGDN,   KC_N,  KC_M,   KC_COMM,KC_DOT,  LT(SYMB,KC_SLSH), KC_RSFT,
                          KC_MINS,KC_EQL, KC_LBRC, KC_RBRC,          KC_FN1,
        KC_VOLD, KC_VOLU,
        KC_MUTE,
        KC_RGUI, KC_ENT, KC_SPACE
    ),
[EASY] = KEYMAP(
       // left hand
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TAB,  KC_SPC,  KC_DEL,  KC_BSPC, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                                    KC_TRNS, KC_TRNS,
                                                             KC_TRNS,
                                           KC_TRNS, KC_TRNS, KC_TRNS,
       // right hand
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                KC_TRNS, KC_ENT,  KC_TRNS, KC_ESC, +KC_TRNS, KC_TRNS, /* + do not change! */
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
),
[SYMB] = KEYMAP(
       // left hand
       KC_TRNS, KC_F1,      KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_TRNS,
       KC_TRNS, S(KC_QUOT), KC_BSLS, KC_EQL,  KC_PERC, KC_TILD, KC_TRNS,
       KC_TRNS, KC_AT,      KC_ASTR, KC_DLR,  KC_UNDS, KC_GRV,
       KC_TRNS,+KC_TRNS,    KC_EXLM, KC_CIRC, KC_PIPE, KC_BSLS, KC_TRNS, /* + do not change! */
       KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS,
                                                       KC_TRNS, KC_TRNS,
                                                                KC_TRNS,
                                              KC_TRNS, KC_TRNS, KC_TRNS,
       // right hand
       KC_TRNS, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
       KC_TRNS, KC_NO,   KC_UNDS, KC_QUOT, KC_HASH, KC_PLUS, KC_F12,  /* what to put on Y? */
                KC_HASH, KC_LPRN, KC_RPRN, KC_LBRC, KC_RBRC, KC_TRNS,
       KC_TRNS, KC_AMPR, KC_MINS, KC_LCBR, KC_RCBR,+KC_TRNS, KC_TRNS, /* + do not change! */
                         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
),
[DIGI] = KEYMAP(
       // left hand
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,+KC_TRNS, KC_TRNS, KC_TRNS,
                                                    KC_TRNS, KC_TRNS,
                                                             KC_TRNS,
                                           KC_TRNS, KC_TRNS, KC_TRNS,
       // right hand
       KC_TRNS, KC_NO,   KC_NLCK, KC_SLSH, KC_ASTR, KC_MINS, KC_TRNS,
       KC_TRNS, KC_NO,   KC_7,    KC_8,    KC_9,    KC_PLUS, KC_TRNS,
                KC_NO,   KC_4,    KC_5,    KC_6,    KC_PLUS, KC_TRNS,
       KC_TRNS, KC_NO,   KC_1,    KC_2,    KC_3,    KC_ENT,  KC_TRNS,
                         KC_0,    KC_0,    KC_DOT,  KC_ENT,  KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
),
[MOVE] = KEYMAP(
       // left hand
       KC_TRNS, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_TRNS,
       KC_TRNS, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_TRNS,
       KC_TRNS, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
       KC_TRNS, KC_NO,   KC_BTN1, KC_MS_U, KC_BTN2, KC_NO,   KC_TRNS,
       KC_TRNS,+KC_TRNS, KC_MS_L, KC_MS_D, KC_MS_R,
                                                    KC_TRNS, KC_TRNS,
                                                             KC_TRNS,
                                           KC_TRNS, KC_TRNS, KC_TRNS,
       // right hand
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_HOME, KC_PGUP, KC_TRNS, KC_TRNS, KC_TRNS,
                KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_END,  KC_PGDN, KC_TRNS, KC_TRNS, KC_TRNS,
                         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                KC_TRNS, KC_TRNS,
                KC_TRNS,
                KC_TRNS, KC_TRNS, KC_TRNS
),
};

const uint16_t PROGMEM fn_actions[] = {
    [EASY] = ACTION_LAYER_TAP_TOGGLE(EASY),
    [SYMB] = ACTION_LAYER_TAP_TOGGLE(SYMB),
    [DIGI] = ACTION_LAYER_TAP_TOGGLE(DIGI),
    [MOVE] = ACTION_LAYER_TAP_TOGGLE(MOVE),
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
