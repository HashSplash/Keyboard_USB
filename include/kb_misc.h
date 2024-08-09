/*Name Suggestions for keybord
* Horde
* Matrix
* Cluster
* Crew
* Nexus
* Troop
* Flock
* Armada
* Fleet
* Kaafila
*/

#ifndef KB_MISC_H
#define KB_MISC_H

#include <stdint.h>
#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>


#define ROW         6
#define COL         18
#define KB_NUMBER   2


//relevant register addresses
#define GPIO_0_BASE_REG         0x50000000
#define GPIO_1_BASE_REG         0x50000300
#define GPIO_0_IN_OFFSET        0x510
#define UICR_BASE_REG           0x10001000
#define UICR_NFCPINS_OFFSET     0x20C


extern uint8_t keyboard_matrix[ROW][COL];

// const struct device *gpio_dev;
//Array containing modKeys








/*
https://usb.org/sites/default/files/hut1_5.pdf
*/
typedef enum {
    Reserved = 0x00,
    Keyboard_ErrorRollOver1 = 0x01,
    Keyboard_POSTFail1 = 0x02,
    Keyboard_ErrorUndefined1 = 0x03,
    Keyboard_a_and_A = 0x04,
    Keyboard_b_and_B = 0x05,
    Keyboard_c_and_C = 0x06,
    Keyboard_d_and_D = 0x07,
    Keyboard_e_and_E = 0x08,
    Keyboard_f_and_F = 0x09,
    Keyboard_g_and_G = 0x0A,
    Keyboard_h_and_H = 0x0B,
    Keyboard_i_and_I = 0x0C,
    Keyboard_j_and_J = 0x0D,
    Keyboard_k_and_K = 0x0E,
    Keyboard_l_and_L = 0x0F,
    Keyboard_m_and_M = 0x10,
    Keyboard_n_and_N = 0x11,
    Keyboard_o_and_O = 0x12,
    Keyboard_p_and_P = 0x13,
    Keyboard_q_and_Q = 0x14,
    Keyboard_r_and_R = 0x15,
    Keyboard_s_and_S = 0x16,
    Keyboard_t_and_T = 0x17,
    Keyboard_u_and_U = 0x18,
    Keyboard_v_and_V = 0x19,
    Keyboard_w_and_W = 0x1A,
    Keyboard_x_and_X = 0x1B,
    Keyboard_y_and_Y = 0x1C,
    Keyboard_z_and_Z = 0x1D,
    Keyboard_1_and_Exclamation = 0x1E,
    Keyboard_2_and_At = 0x1F,
    Keyboard_3_and_Hash = 0x20,
    Keyboard_4_and_Dollar = 0x21,
    Keyboard_5_and_Percent = 0x22,
    Keyboard_6_and_Caret = 0x23,
    Keyboard_7_and_Ampersand = 0x24,
    Keyboard_8_and_Asterisk = 0x25,
    Keyboard_9_and_LeftParen = 0x26,
    Keyboard_0_and_RightParen = 0x27,
    Keyboard_Return_ENTER = 0x28,
    Keyboard_ESCAPE = 0x29,
    Keyboard_DELETE_Backspace = 0x2A,
    Keyboard_Tab = 0x2B,
    Keyboard_Spacebar = 0x2C,
    Keyboard_Dash_and_Underscore = 0x2D,
    Keyboard_Equal_and_Plus = 0x2E,
    Keyboard_LeftBracket_and_LeftBrace = 0x2F,
    Keyboard_RightBracket_and_RightBrace = 0x30,
    Keyboard_Backslash_and_Pipe = 0x31,
    Keyboard_NonUS_Pound_and_Tilde = 0x32,
    Keyboard_Semicolon_and_Colon = 0x33,
    Keyboard_Quote_and_DoubleQuote = 0x34,
    Keyboard_GraveAccent_and_Tilde = 0x35,
    Keyboard_Comma_and_LessThan = 0x36,
    Keyboard_Period_and_GreaterThan = 0x37,
    Keyboard_Slash_and_Question = 0x38,
    Keyboard_CapsLock = 0x39,
    Keyboard_F1 = 0x3A,
    Keyboard_F2 = 0x3B,
    Keyboard_F3 = 0x3C,
    Keyboard_F4 = 0x3D,
    Keyboard_F5 = 0x3E,
    Keyboard_F6 = 0x3F,
    Keyboard_F7 = 0x40,
    Keyboard_F8 = 0x41,
    Keyboard_F9 = 0x42,
    Keyboard_F10 = 0x43,
    Keyboard_F11 = 0x44,
    Keyboard_F12 = 0x45,
    Keyboard_PrintScreen = 0x46,
    Keyboard_ScrollLock = 0x47,
    Keyboard_Pause = 0x48,
    Keyboard_Insert = 0x49,
    Keyboard_Home = 0x4A,
    Keyboard_PageUp = 0x4B,
    Keyboard_Delete_Forward = 0x4C,
    Keyboard_End = 0x4D,
    Keyboard_PageDown = 0x4E,
    Keyboard_RightArrow = 0x4F,
    Keyboard_LeftArrow = 0x50,
    Keyboard_DownArrow = 0x51,
    Keyboard_UpArrow = 0x52,
    Keypad_NumLock_and_Clear = 0x53,
    Keypad_Slash = 0x54,
    Keypad_Asterisk = 0x55,
    Keypad_Dash = 0x56,
    Keypad_Plus = 0x57,
    Keypad_ENTER = 0x58,
    Keypad_1_and_End = 0x59,
    Keypad_2_and_DownArrow = 0x5A,
    Keypad_3_and_PageDn = 0x5B,
    Keypad_4_and_LeftArrow = 0x5C,
    Keypad_5 = 0x5D,
    Keypad_6_and_RightArrow = 0x5E,
    Keypad_7_and_Home = 0x5F,
    Keypad_8_and_UpArrow = 0x60,
    Keypad_9_and_PageUp = 0x61,
    Keypad_0_and_Insert = 0x62,
    Keypad_Period_and_Delete = 0x63,
    Keyboard_NonUS_Backslash_and_Pipe = 0x64,
    Keyboard_Application = 0x65,
    Keyboard_Power = 0x66,
    Keypad_Equal = 0x67,
    Keyboard_F13 = 0x68,
    Keyboard_F14 = 0x69,
    Keyboard_F15 = 0x6A,
    Keyboard_F16 = 0x6B,
    Keyboard_F17 = 0x6C,
    Keyboard_F18 = 0x6D,
    Keyboard_F19 = 0x6E,
    Keyboard_F20 = 0x6F,
    Keyboard_F21 = 0x70,
    Keyboard_F22 = 0x71,
    Keyboard_F23 = 0x72,
    Keyboard_F24 = 0x73,
    Keyboard_Execute = 0x74,
    Keyboard_Help = 0x75,
    Keyboard_Menu = 0x76,
    Keyboard_Select = 0x77,
    Keyboard_Stop = 0x78,
    Keyboard_Again = 0x79,
    Keyboard_Undo = 0x7A,
    Keyboard_Cut = 0x7B,
    Keyboard_Copy = 0x7C,
    Keyboard_Paste = 0x7D,
    Keyboard_Find = 0x7E,
    Keyboard_Mute = 0x7F,
    Keyboard_VolumeUp = 0x80,
    Keyboard_VolumeDown = 0x81,
    Keyboard_Locking_CapsLock = 0x82,
    Keyboard_Locking_NumLock = 0x83,
    Keyboard_Locking_ScrollLock = 0x84,
    Keypad_Comma = 0x85,
    Keypad_EqualSign = 0x86,
    Keyboard_International1 = 0x87,
    Keyboard_International2 = 0x88,
    Keyboard_International3 = 0x89,
    Keyboard_International4 = 0x8A,
    Keyboard_International5 = 0x8B,
    Keyboard_International6 = 0x8C,
    Keyboard_International7 = 0x8D,
    Keyboard_International8 = 0x8E,
    Keyboard_International9 = 0x8F,
    Keyboard_LANG1 = 0x90,
    Keyboard_LANG2 = 0x91,
    Keyboard_LANG3 = 0x92,
    Keyboard_LANG4 = 0x93,
    Keyboard_LANG5 = 0x94,
    Keyboard_LANG6 = 0x95,
    Keyboard_LANG7 = 0x96,
    Keyboard_LANG8 = 0x97,
    Keyboard_LANG9 = 0x98,
    Keyboard_AlternateErase = 0x99,
    Keyboard_SysReq_Attention = 0x9A,
    Keyboard_Cancel = 0x9B,
    Keyboard_Clear = 0x9C,
    Keyboard_Prior = 0x9D,
    Keyboard_Return = 0x9E,
    Keyboard_Separator = 0x9F,
    Keyboard_Out = 0xA0,
    Keyboard_Oper = 0xA1,
    Keyboard_ClearAgain = 0xA2,
    Keyboard_CrSel_Props = 0xA3,
    Keyboard_ExSel = 0xA4,
    Keypad_00 = 0xB0,
    Keypad_000 = 0xB1,
    ThousandsSeparator = 0xB2,
    DecimalSeparator = 0xB3,
    CurrencyUnit = 0xB4,
    CurrencySubUnit = 0xB5,
    Keypad_LeftParen = 0xB6,
    Keypad_RightParen = 0xB7,
    Keypad_LeftBrace = 0xB8,
    Keypad_RightBrace = 0xB9,
    Keypad_Tab = 0xBA,
    Keypad_Backspace = 0xBB,
    Keypad_A = 0xBC,
    Keypad_B = 0xBD,
    Keypad_C = 0xBE,
    Keypad_D = 0xBF,
    Keypad_E = 0xC0,
    Keypad_F = 0xC1,
    Keypad_XOR = 0xC2,
    Keypad_Caret = 0xC3,
    Keypad_Percent = 0xC4,
    Keypad_LessThan = 0xC5,
    Keypad_GreaterThan = 0xC6,
    Keypad_Ampersand = 0xC7,
    Keypad_DoubleAmpersand = 0xC8,
    Keypad_Pipe = 0xC9,
    Keypad_DoublePipe = 0xCA,
    Keypad_Colon = 0xCB,
    Keypad_Hash = 0xCC,
    Keypad_Space = 0xCD,
    Keypad_At = 0xCE,
    Keypad_Exclamation = 0xCF,
    Keypad_MemoryStore = 0xD0,
    Keypad_MemoryRecall = 0xD1,
    Keypad_MemoryClear = 0xD2,
    Keypad_MemoryAdd = 0xD3,
    Keypad_MemorySubtract = 0xD4,
    Keypad_MemoryMultiply = 0xD5,
    Keypad_MemoryDivide = 0xD6,
    Keypad_PlusMinus = 0xD7,
    Keypad_Clear = 0xD8,
    Keypad_ClearEntry = 0xD9,
    Keypad_Binary = 0xDA,
    Keypad_Octal = 0xDB,
    Keypad_Decimal = 0xDC,
    Keypad_Hexadecimal = 0xDD,
    Reserved_DE = 0xDE,
    Reserved_DF = 0xDF,
    Keyboard_LeftControl = 0xE0,
    Keyboard_LeftShift = 0xE1,
    Keyboard_LeftAlt = 0xE2,
    Keyboard_LeftGUI = 0xE3,
    Keyboard_RightControl = 0xE4,
    Keyboard_RightShift = 0xE5,
    Keyboard_RightAlt = 0xE6,
    Keyboard_RightGUI = 0xE7,
} KeyboardUsageID;

extern uint8_t const modkey[];
extern uint8_t const shift[];
#endif