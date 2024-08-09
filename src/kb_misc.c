#include <stdint.h>
#include "kb_misc.h"


//initialise this to 0 initially when doing init
uint8_t keyboard_matrix[ROW][COL]={
    {Keyboard_ESCAPE, Keyboard_F1, Keyboard_F2, Keyboard_F3, Keyboard_F4, Keyboard_F5, Keyboard_F6,Keyboard_F7,Keyboard_F8,Keyboard_F9,Keyboard_F10,Keyboard_F11,Keyboard_F12,Keyboard_DELETE_Backspace,0,0,0,0},
    {Keyboard_GraveAccent_and_Tilde,Keyboard_1_and_Exclamation,Keyboard_2_and_At,Keyboard_3_and_Hash,Keyboard_4_and_Dollar,Keyboard_5_and_Percent,Keyboard_6_and_Caret,Keyboard_7_and_Ampersand,Keyboard_8_and_Asterisk,Keyboard_9_and_LeftParen,Keyboard_0_and_RightParen,Keyboard_Dash_and_Underscore,Keyboard_Equal_and_Plus,Keypad_Backspace,Keyboard_Insert,0,0,0},
    {Keypad_Tab,Keyboard_q_and_Q,Keyboard_w_and_W,Keyboard_e_and_E,Keyboard_r_and_R,Keyboard_t_and_T,Keyboard_y_and_Y,Keyboard_u_and_U,Keyboard_i_and_I,Keyboard_o_and_O,Keyboard_p_and_P,Keyboard_LeftBracket_and_LeftBrace,Keyboard_RightBracket_and_RightBrace,Keyboard_Backslash_and_Pipe,Keyboard_End,0,0,0},
    {Keyboard_CapsLock,Keyboard_a_and_A,Keyboard_s_and_S,Keyboard_d_and_D,Keyboard_f_and_F,Keyboard_g_and_G,Keyboard_h_and_H,Keyboard_j_and_J,Keyboard_k_and_K,Keyboard_l_and_L,Keyboard_Semicolon_and_Colon,Keyboard_Quote_and_DoubleQuote,Keyboard_Return_ENTER,Keyboard_PageUp,0,0,0,0},
    {Keyboard_LeftShift,Keyboard_z_and_Z,Keyboard_x_and_X,Keyboard_c_and_C,Keyboard_v_and_V,Keyboard_b_and_B,Keyboard_n_and_N,Keyboard_m_and_M,Keyboard_Comma_and_LessThan,Keyboard_Period_and_GreaterThan,Keyboard_Slash_and_Question,Keyboard_RightShift,Keyboard_UpArrow,Keyboard_PageDown,0,0,0,0},
    {Keyboard_LeftControl,Keyboard_Home,Keyboard_LeftAlt,Keyboard_Spacebar,Keyboard_RightAlt,Keyboard_RightControl,Keyboard_LeftArrow,Keyboard_DownArrow,Keyboard_RightArrow,0,0,0,0,0,0,0,0,0}
};

/*
 * American ANSI Keyboard Layout (Resembling Kreo Hive)
 *
 * ,--------------------------------------------------------------------.-----------------------------------
 * |  Esc |  F1 |  F2 |  F3 |  F4 |  F5 |  F6 |  F7 |  F8 |  F9 | F10  | F11 | F12 |  Del |      (vol) 
 * |--------------------------------------------------------------------|
 * |  ~  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |  -  |  =  | Backspace |    |  Ins |
 * |--------------------------------------------------------------------|
 * |  Tab  |  Q  |  W  |  E  |  R  |  T  |  Y  |  U  |  I  |  O  |  P  |  [  |  ]  |    \   |     | End |
 * |--------------------------------------------------------------------|
 * | Caps  |  A  |  S  |  D  |  F  |  G  |  H  |  J  |  K  |  L  |  ;  |  '  |   Enter    |       | PgUp |
 * |--------------------------------------------------------------------|
 * | Shift  |  Z  |  X  |  C  |  V  |  B  |  N  |  M  |  ,  |  .  |  /  |  Shift    |  ↑  |       | PgUp |
 * |--------------------------------------------------------------------|
 * | Ctrl | Win | Alt |         Space          | Alt | Fn | Ctrl |            | ←  | ↓  | →  |
 * `--------------------------------------------------------------------'-----------------------------------
 */

uint8_t const modkey[]={Keyboard_LeftControl,Keyboard_LeftShift,Keyboard_LeftAlt,Keyboard_LeftGUI,
                        Keyboard_RightControl,Keyboard_RightShift,Keyboard_RightAlt,Keyboard_RightGUI};

uint8_t const shift[]=  {2,3,4,8,9,10,13,14,15,16,17,25,26,27,28,29,30,31};
