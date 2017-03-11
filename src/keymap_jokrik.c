#include "keymap_common.h"
#include "command.h"
#include "bootloader.h"

// Default
#ifdef KEYMAP_SECTION_ENABLE
const uint8_t keymaps[KEYMAPS_COUNT][MATRIX_ROWS][MATRIX_COLS] __attribute__ ((section (".keymap.keymaps"))) = {
#else
const uint8_t keymaps[][MATRIX_ROWS][MATRIX_COLS] PROGMEM = {
#endif
    /* Keymap 4: Mini/68 - OEM 1.25-1.25-1.25-6.25-1-1-1
     * ,-----------------------------------------------------------------------.
     * | F1| F2|Esc|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backsp |Prt|
     * |---+---+-----------------------------------------------------------+---|
     * | F3| F4|Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|    \|PgU|
     * |---+---+-----------------------------------------------------------+---|
     * | F5| F6|Caps  |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return  |PgD|
     * |---+---+-----------------------------------------------------------+---|
     * | F7| F8|Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift | Up|Del|
     * |---+---+-----------------------------------------------------------+---|
     * | F9|F10|Ctrl|FN0 |Alt |       Space            |Alt|    Ctr|Lef|Dow|Rig|
     * `-----------------------------------------------------------------------'
     */
    KEYMAP(
        F1,  F2,  ESC,   1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, BSPC,PSCR, \
        F3,  F4,  TAB,   Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,BSLS,PGUP, \
        F5,  F6,  CAPS,  A,   S,   D,   F,   G,   H,   J,   K,   L,   SCLN,QUOT,ENT,      PGDN, \
        F7,  F8,  LSFT,  Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, SLSH,    RSFT,   UP,DEL,  \
        F9,  F10, LCTL, FN0,LALT,               SPC,                      RALT,LEFT, DOWN,RGHT),
    /* Keymap 6: Fn Layer
     * ,-----------------------------------------------------------------------.
     * |   |   |  `| F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|Delete |   |
     * |---+---+-----------------------------------------------------------+---|
     * |   |   |     |   |Up |Fn5|Fn6|Fn7|Cal|   |Ins|   |Psc|Slk|Pau|     |   |
     * |---+---+-----------------------------------------------------------|---|
     * |   |   |      |Lef|Dow|Rig|Fn8|Fn9|   |   |   |   |Hom|PgU|        |   |
     * |---+---+-----------------------------------------------------------|---|
     * |   |   |        |   |App|Fn1|Fn2|Fn3|VoD|VoU|Mut|End|PgD|      |   |   |
     * |---+---+-----------------------------------------------------------+---|
     * |   |   |    |    |    |                        |    |    |     |   |   |
     * `-----------------------------------------------------------------------'
     */
    KEYMAP(
        TRNS,TRNS,GRV, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, DEL, TRNS, \
        TRNS,TRNS,TRNS,TRNS,UP,  TRNS, TRNS, TRNS, CALC,TRNS,INS, TRNS,PSCR,SLCK,PAUS,TRNS,TRNS, \
        TRNS,TRNS,TRNS,LEFT,DOWN,RGHT,FN8, FN9, TRNS,TRNS,TRNS,TRNS,HOME,PGUP,TRNS,     TRNS, \
        TRNS,TRNS,TRNS,TRNS,APP, FN1, FN2, FN3, VOLD,VOLU,MUTE,END, PGDN,     TRNS,TRNS,TRNS, \
        TRNS,TRNS,TRNS,TRNS,TRNS,               TRNS,                    TRNS,TRNS,TRNS,TRNS),
};


/*
 * Fn action definition
 */
#ifdef KEYMAP_SECTION_ENABLE
const uint16_t fn_actions[FN_ACTIONS_COUNT] __attribute__ ((section (".keymap.fn_actions"))) = {
#else
const uint16_t fn_actions[] PROGMEM = {
#endif
    [0] = ACTION_LAYER_MOMENTARY(1),
    [1] = ACTION_BACKLIGHT_DECREASE(),
    [2] = ACTION_BACKLIGHT_TOGGLE(),
    [3] = ACTION_BACKLIGHT_INCREASE(),
};

#ifdef KEYMAP_IN_EEPROM_ENABLE
uint16_t keys_count(void) {
    return sizeof(keymaps) / sizeof(keymaps[0]) * MATRIX_ROWS * MATRIX_COLS;
}

uint16_t fn_actions_count(void) {
    return sizeof(fn_actions) / sizeof(fn_actions[0]);
}
#endif

/*
 * Action macro definition
 */
enum macro_id {
    KEYPAD_00 = 0,
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    switch (id) {
        case KEYPAD_00:
            return (record->event.pressed ?
                    MACRO( T(P0), T(P0), END ) :
                    MACRO_NONE );
    }
    return MACRO_NONE;
}

bool command_extra(uint8_t code)
{
    switch (code) {
        case KC_F1:
            clear_keyboard();
            print("\n\nJump to bootloader... ");
            _delay_ms(1000);
            bootloader_jump(); // not return
            print("not supported.\n");
            break;
    }
    return false;
}