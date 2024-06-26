#include QMK_KEYBOARD_H

uint16_t copy_paste_timer;

enum layers {
    BASE = 0,
    NAV,
    NUM,
    GERMAN,
    SPANISH,
    FKEY   
};

enum custom_keycodes {
    KC_CCCV = SAFE_RANGE
};

// Fillers to make layering more clear

#define ____ KC_TRNS

typedef struct {
    bool is_press_action;
    uint8_t state;
} tap;

enum {
    SINGLE_TAP = 1,
    SINGLE_HOLD,
    DOUBLE_TAP,
    DOUBLE_HOLD,
    DOUBLE_SINGLE_TAP, // Send two single taps
    TRIPLE_TAP,
    TRIPLE_HOLD
};

// Tap dance enums
enum {
    X_CTL,
    SOME_OTHER_DANCE
};

uint8_t cur_dance(tap_dance_state_t *state);

// For the x tap dance. Put it here so it can be used in any keymap
void x_finished(tap_dance_state_t *state, void *user_data);
void x_reset(tap_dance_state_t *state, void *user_data);

enum unicode_names {
	INVEXCL,
	PARAGRAPH,
	DEGREE,
	PLUSMINUS,
	SUPER2,
	SUPER3,
	MU,
	DOT,
	INVQUES,
	AACCSH,
	ADIARSH,
	EACCSH,
	IACCSH,
	ENIESH,
	OACCSH,
	ODIARSH,
	TIMES,
	UACCSH,
	UDIARSH,
	ESZETT,
	AACC,
	ADIAR,
	EACC,
	IACC,
	ENIE,
	OACC,
	ODIAR,
	DIV,
	UACC,
	UDIAR,
	DIAMETER,
	WINKY,
	EURO
};

const uint32_t PROGMEM unicode_map[] = {
	[INVEXCL] = 0x00A1,	// ¡
	[PARAGRAPH] = 0x00A7,	// §
	[DEGREE] = 0x00B0,	// °
	[PLUSMINUS] = 0x00B1,	// ±
	[SUPER2] = 0x00B2,	// ²
	[SUPER3] = 0x00B3,	// ³
	[MU] = 0x00B5,	// µ	
	[DOT] = 0x00B7,	// ·	
	[INVQUES] = 0x00BF,	// ¿
	[AACCSH] = 0x00C1,	// Á
	[ADIARSH] = 0x00C4,	// Ä
	[EACCSH] = 0x00C9,	// É
	[IACCSH] = 0x00CD,	// Í
	[ENIESH] = 0x00D1,	// Ñ
	[OACCSH] = 0x00D3,	// Ó
	[ODIARSH] = 0x00D6,	// Ö
	[TIMES] = 0x00D7,	// ×
	[UACCSH] = 0x00DA,	// Ú
	[UDIARSH] = 0x00DC,	// Ü
	[ESZETT] = 0x00DF,  // ß
	[AACC] = 0x00E1,	// á
	[ADIAR] = 0x00E4,	// ä
	[EACC] = 0x00E9,	// é
	[IACC] = 0x00ED,	// í
	[ENIE] = 0x00F1,	// ñ
	[OACC] = 0x00F3,	// ó
	[ODIAR] = 0x00F6,	// ö
	[DIV] = 0x00F7,	// ÷
	[UACC] = 0x00FA,	// ú
	[UDIAR] = 0x00FC,	// ü
	[DIAMETER] = 0x2300,  // ⌀ 
	[WINKY] = 0x1F609,	 // 😉
	[EURO] = 0x20AC,	// €
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* 
 * Base Layer: Colemak-DH 
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * | ESC    |   Q  |   W  |  F   |   P  |   B  |                              |   J  |   L  |   U  |   Y  | ; :  |  Bspc  |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * | LCTL   |   A  |   R  |  S   |   T  |   G  |                              |   M  |   N  |   E  |   I  |   O  |  ALT   |
 * |--------+------+------+------+------+------+                              +------+------+------+------+------+--------|
 * | LSFT   |   Z  |   X  |   C  |   D  |   V  |                              |   K  |   H  | ,  < | . >  | /  ? | SUPER  |
 * `----------------------+------+------+------+  			      +------+------+------+----------------------'
 *                 | FKEYS| FKEYS|                                                          | SPC  | SPC  |
 *                 +-------------+-------------+                              +-------------+-------------+
 *                               |  DEL | Enc1 |                              | Enc2 | TAB  |
 *                               |   #  |      |                              |      |  #   |
 *                               |------+------|                              |------+------|
 *                                             +-------------+  +-------------+
 *                                             |SpcEnt| CCCV |  | Bspc |SpcEnt|
 *                                             | Nav  |      |  |      | Nav  | 
 *                                             |------+------|  |------+------|
 *                                             | ESP  |SUPER |  |SUPER | DE   |
 *                                             |      |      |  |      |      |	
 *                                             +-------------+  +-------------+
 */
// TG(STENO) disabled and changed for KC_LCMD
[BASE] = LAYOUT( 
      KC_ESC,  KC_Q,   KC_W,   KC_F,   KC_P,   KC_B,                                         KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_BSPC,
      KC_LCTL, KC_A,   KC_R,   KC_S,   KC_T,   KC_G,                                         KC_M,    KC_N,    KC_E,    KC_I,    KC_O, KC_LALT,
      KC_LSFT, KC_Z,   KC_X,   KC_C,   KC_D,   KC_V,  					     KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_SLSH, KC_LCMD,
                    MO(FKEY),MO(FKEY),                                            	KC_SPC, KC_SPC,                    
                                    LT(NUM, KC_DEL),  S(LCMD(KC_2)),       			S(LCMD(KC_1)), LT(NUM, KC_TAB),                                     
                                    TD(X_CTL), KC_CCCV,            				KC_BSPC, TD(X_CTL),                                    
                                    MO(SPANISH), KC_LCMD,             	   			KC_LCMD, MO(GERMAN)                                     
),

/* 
 * Left Hand writing
 
 * ,-------------------------------------------.
 * | Bspc | ; :  |  Y   |   U  |   L  |    J   |    
 * |------+------+------+------+------+--------| 
 * | RSFT |   O  |  I   |   E  |   N  |    M   |   
 * +------+------+------+------+------+--------|
 * |Enter | /  ? | . >  | ,  < |   H  |    K   |
 * `------+------+------+------+------+--------| 						
 *
 *
 *[LEFT] = LAYOUT( \
 *    KC_BSPC, KC_SCLN, KC_Y, KC_U, KC_L, KC_J,     	_______,_______, _______,_______, _______,_______,     
 *    KC_RSFT, KC_O, KC_I, KC_E, KC_N, KC_M,    		_______,_______, _______,_______, _______,_______,  
 *    KC_ENT, KC_SLSH,KC_DOT, KC_COMM, KC_H, KC_K,  	_______,_______, _______,_______, _______,_______,     
 *                                    					_______,_______,    _______,_______,                                   
 *														_______,_______,    _______,_______,                                   
 *														_______,_______,    _______,_______,                                  
 *														_______,_______,    _______,_______   
 *),
*/

/* 
 * Navigation Layer
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        | Home | PgDn | PgUp | End  |      |                              |      | Home | PgDn | PgUp | End  |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        | Left | Down | Up   | Right|      |                              |      | Left | Down | Up   | Right|        |
 * |--------+------+------+------+------+------+                              +------+------+------+------+------+--------|
 * | M_but1 |M_left|M_down| M_up |M_righ|M_but2|                              |M_but1|M_left|M_down| M_up |M_righ| M_but2 |
 * `----------------------+------+------+------+                              +------+------+------+----------------------'
 *       
 */

[NAV] = LAYOUT(
      _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END, _______,			 			_______, KC_HOME, KC_PGDN, KC_PGUP, KC_END, _______,
      _______, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, _______,						 _______, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, _______,
      KC_MS_BTN1, KC_MS_LEFT, KC_MS_DOWN, KC_MS_UP, KC_MS_RIGHT, KC_MS_BTN2, 	KC_MS_BTN1, KC_MS_LEFT, KC_MS_DOWN, KC_MS_UP, KC_MS_RIGHT, KC_MS_BTN2,
											_______,_______,    _______,_______,                                    
                                            _______,_______,    _______,_______,                                   
                                            _______,_______,    _______,_______,                                   
                                            _______,_______,    _______,_______                                    
    ),
    
/*
 * Numpad, SYMBOLS
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * | FKEY   |  !   |  @   |  {   |  }   |  |   | 	                      | - _  | 6 ^  | 7 &  | 8 *  | 9 (  |  / ?   | 
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |  \   | ' "  |  (   |  )   |  `   |                              |  +   | 1 !  | 2 @  | 3 #  | 4 $  |   *    |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |      |      |  [   |  ]   |  ~   |      			      |  &   | 5 %  |      |      | 0 )  |   =    |        
 * `----------------------+------+------+------+                   	      +------+------+------+------+------+--------'
 *                       
 */
    [NUM] = LAYOUT(
      MO(FKEY), KC_EXLM, KC_AT,   KC_LCBR, KC_RCBR, KC_PIPE,        KC_MINS, KC_6, KC_7, KC_8, KC_9, KC_SLSH,
      _______, KC_BSLS, KC_QUOT, KC_LPRN, KC_RPRN, KC_GRV,         KC_PLUS, KC_1, KC_2, KC_3, KC_4, KC_ASTR,
      _______, _______,   _______, KC_LBRC, KC_RBRC, KC_TILD, 		 KC_AMPR, KC_5, _______, _______, KC_0, KC_EQL, 
											_______,_______,    _______,_______,                                   
                                            _______,_______,    _______,_______,                                   
                                            _______,_______,    _______,_______,                                  
                                            _______,_______,    _______,_______                                    
    ),
    
/*
 * GERMAN letters and symbols
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |      |      |      |      |      |                              |      |      |  Ü   |      |      |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |  Ä   |      |  ß   |      |      |                              |      |      |  €   |      |  Ö   |        |
 * |--------+------+------+------+------+------+			      +------+------+------+------+------+--------|
 * |        |      |      |      |      |      |        		      |      |      |      |      |      |        |
 * `----------------------+------+------+------+			      +------+------+------+----------------------'
 *                   
 */
    [GERMAN] = LAYOUT(
      _______, _______, _______, _______, _______, _______, _______, _______, XP(UDIAR,UDIARSH), _______, _______, _______,
      _______, XP(ADIAR,ADIARSH), _______, X(ESZETT), _______, _______, _______, _______, X(EURO), _______, XP(ODIAR,ODIARSH), _______,
      _______, _______, _______, _______, _______,_______, _______, _______, _______, _______, _______, _______, 
											_______,_______,    _______,_______,                                   
                                            _______,_______,    _______,_______,                                   
                                            _______,_______,    _______,_______,                                   
                                            _______,_______,    _______,_______                                    
				  
    ),
    
/* 
 * SPANISH letters and symbols
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |   ¡  |  😉  |      |      |      |                              |  ±   |  ÷   |   Ú  |      |      |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |   Á  |      |  §   |      |      |                              |  µ   |   Ñ  |   É  |   Í  |   Ó  |        |
 * |--------+------+------+------+------+------+			      +------+------+------+------+------+--------|
 * |        |      |  ×   |      |   ⌀  |      |       			      |   °  |      |   ²  |   ·  |   ¿  |        |
 * `----------------------+------+------+------+			      +------+------+------+----------------------'
 *              
 */
    [SPANISH] = LAYOUT(
      _______, X(INVEXCL), X(WINKY), _______, _______, _______,                   X(PLUSMINUS), X(DIV), XP(UACC,UACCSH), _______, _______, _______, 
      _______, XP(AACC,AACCSH), _______, X(PARAGRAPH), _______,   _______,        X(MU),    XP(ENIE,ENIESH), XP(EACC,EACCSH), XP(IACC,IACCSH), XP(OACC,OACCSH), _______,
      _______, X(DOT), X(TIMES), _______,   X(DIAMETER),   _______,  X(DEGREE), _______, X(SUPER2), X(DOT), X(INVQUES), _______,
											_______,_______,    _______,_______,                                   
                                            _______,_______,    _______,_______,                                   
                                            _______,_______,    _______,_______,                                   
                                            _______,_______,    _______,_______                                    
    ),
 
/* 
 * F-Keys Layer
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |      |      |      |      |      |                              |      | F9   | F10  | F11  | F12  |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |                              |      | F5   | F6   | F7   | F8   |        |
 * |--------+------+------+------+------+------+			      +------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      			      |      | F1   | F2   | F3   | F4   |        |
 * `----------------------+------+------+------+   			      +------+------+------+----------------------'

 */
    [FKEY] = LAYOUT(
      _______, _______, _______, _______, _______, _______,                                     _______, KC_F9,   KC_F10,   KC_F11,   KC_F12,  _______,
      _______, _______, _______, _______, _______, _______,                                     _______, KC_F5,   KC_F6,   KC_F7,   KC_F8,  _______,
      _______, _______, _______, _______, _______, _______, 									 _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,  _______,
                      											_______,_______,    _______,_______,                                   
																_______,_______,    _______,_______,                                   
																_______,_______,    _______,_______,                                    
																_______,_______,    _______,_______                                    
    ),
    
/* 
 * STENO Mode
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |   #    |   #  |   #  |   #  |   #  |   #  |                              |   #  |   #  |   #  |   #  |   #  |    #   |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |   S  |   T  |   P  |   H  |   *  |                              |   *  |   F  |   P  |   L  |   T  |    D   |
 * |--------+------+------+------+------+------+							  +------+------+------+------+------+--------|
 * |        |   S  |   K  |   W  |   R  |   *  |      						  |   *  |   R  |   B  |   G  |   S  |    Z   |
 * `----------------------+------+------+------+ 							  +------+------+------+----------------------'
 *                 |      |      |                                                          |      |      |
 *                 +-------------+-------------+                              +-------------+-------------+
 *                               |      |      |                              |      |      |
 *                               |------+------|                              |------+------|
 *                                             +-------------+  +-------------+
 *                                             |  A   |      |  |      |  U   |
 *                                             |------+------|  |------+------|
 *                                             |  O   |      |  |      |  E   |
 *                                             +-------------+  +-------------+
 * 
 * 
 * 
 */
// [STENO] = LAYOUT(
//	STN_N1,  STN_N2,  STN_N3,  STN_N4,  STN_N5,  STN_N6,  						STN_N7,  STN_N8,  STN_N9,  STN_NA,  STN_NB,  STN_NC ,
//	_______,  STN_S1,  STN_TL,  STN_PL,  STN_HL,  STN_ST1, 						STN_ST3, STN_FR,  STN_PR,  STN_LR,  STN_TR,  STN_DR ,
//	_______, STN_S2,  STN_KL,  STN_WL,  STN_RL,  STN_ST2, 						STN_ST4, STN_RR,  STN_BR,  STN_GR,  STN_SR,  STN_ZR ,
//														_______,_______,    _______,_______,                                   
//														_______, _______,   _______,_______,                                   
// 														STN_A, _______,   	_______,STN_U,                                  
// 														STN_O, _______,    	_______,STN_E                                             
//   )
};

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_CCCV:  // One key copy/paste
            if (record->event.pressed) {
                copy_paste_timer = timer_read();
            } else {
                if (timer_elapsed(copy_paste_timer) > TAPPING_TERM) {  // Hold, copy
                    tap_code16(LCTL(KC_C));
                } else { // Tap, paste
                    tap_code16(LCTL(KC_V));
                }
            }
            break;
    }
    return true;
}


/* Return an integer that corresponds to what kind of tap dance should be executed.
 *
 * How to figure out tap dance state: interrupted and pressed.
 *
 * Interrupted: If the state of a dance dance is "interrupted", that means that another key has been hit
 *  under the tapping term. This is typically indicitive that you are trying to "tap" the key.
 *
 * Pressed: Whether or not the key is still being pressed. If this value is true, that means the tapping term
 *  has ended, but the key is still being pressed down. This generally means the key is being "held".
 *
 * One thing that is currenlty not possible with qmk software in regards to tap dance is to mimic the "permissive hold"
 *  feature. In general, advanced tap dances do not work well if they are used with commonly typed letters.
 *  For example "A". Tap dances are best used on non-letter keys that are not hit while typing letters.
 *
 * Good places to put an advanced tap dance:
 *  z,q,x,j,k,v,b, any function key, home/end, comma, semi-colon
 *
 * Criteria for "good placement" of a tap dance key:
 *  Not a key that is hit frequently in a sentence
 *  Not a key that is used frequently to double tap, for example 'tab' is often double tapped in a terminal, or
 *    in a web form. So 'tab' would be a poor choice for a tap dance.
 *  Letters used in common words as a double. For example 'p' in 'pepper'. If a tap dance function existed on the
 *    letter 'p', the word 'pepper' would be quite frustating to type.
 *
 * For the third point, there does exist the 'DOUBLE_SINGLE_TAP', however this is not fully tested
 *
 */
uint8_t cur_dance(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return SINGLE_TAP;
        // Key has not been interrupted, but the key is still held. Means you want to send a 'HOLD'.
        else return SINGLE_HOLD;
    } else if (state->count == 2) {
        // DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
        // action when hitting 'pp'. Suggested use case for this return value is when you want to send two
        // keystrokes of the key, and not the 'double tap' action/macro.
        if (state->interrupted) return DOUBLE_SINGLE_TAP;
        else if (state->pressed) return DOUBLE_HOLD;
        else return DOUBLE_TAP;
    }

    // Assumes no one is trying to type the same letter three times (at least not quickly).
    // If your tap dance key is 'KC_W', and you want to type "www." quickly - then you will need to add
    // an exception here to return a 'TRIPLE_SINGLE_TAP', and define that enum just like 'DOUBLE_SINGLE_TAP'
    if (state->count == 3) {
        if (state->interrupted || !state->pressed) return TRIPLE_TAP;
        else return TRIPLE_HOLD;
    } else return 8; // Magic number. At some point this method will expand to work for more presses
}

// Create an instance of 'tap' for the 'x' tap dance.
static tap xtap_state = {
    .is_press_action = true,
    .state = 0
};

void x_finished(tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case SINGLE_TAP: register_code(KC_SPC); break;
        case SINGLE_HOLD: layer_on(NAV); break;
        case DOUBLE_TAP: register_code(KC_ENT); break;
        //case DOUBLE_HOLD: register_code(KC_LALT); break;
        // Last case is for fast typing. Assuming your key is `f`:
        // For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
        // In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
        //case DOUBLE_SINGLE_TAP: tap_code(KC_X); register_code(KC_X);
    }
}

void x_reset(tap_dance_state_t *state, void *user_data) {
    switch (xtap_state.state) {
        case SINGLE_TAP: unregister_code(KC_SPC); break;
        case SINGLE_HOLD: layer_off(NAV); break;
        case DOUBLE_TAP: unregister_code(KC_ENT); break;
        //case DOUBLE_HOLD: unregister_code(KC_LALT);
        //case DOUBLE_SINGLE_TAP: unregister_code(KC_X);
    }
    xtap_state.state = 0;
}

tap_dance_action_t tap_dance_actions[] = {
    [X_CTL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, x_finished, x_reset)
};
