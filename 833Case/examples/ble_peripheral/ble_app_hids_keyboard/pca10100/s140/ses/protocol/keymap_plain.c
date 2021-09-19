
#include "keymap_common.h"
#include "config.h"


const uint8_t keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	
       {
	{ KC_ESC,   KC_TAB, KC_EQL,   KC_BSPC}, \
	{ KC_NLCK, KC_PSLS, KC_PAST,   KC_PMNS }, \
	{ KC_P7,    KC_P8,   KC_P9,   KC_PPLS }, \
	{ KC_P4,    KC_P5,  KC_P6,  KC_NO }, \
	{ KC_P1,    KC_P2,    KC_P3,   KC_PENT}, \
	{ KC_P0,  KC_NO,    KC_PDOT,    KC_NO } }

       
         
};

const action_t fn_actions[] = {

     ACTION_LAYER_MOMENTARY(1)
};