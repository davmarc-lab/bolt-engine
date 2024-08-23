#pragma once

enum Key {
    KEY_Q,
    KEY_W,
    KEY_A,
    KEY_S,
    KEY_D,
    KEY_UNKNOWN,
};

enum KeyAction {
    KEY_PRESS,
    KEY_RELEASE,
    KEY_REPEAT,
    KEY_NO_ACTION,
};

enum KeyMod {
    KEY_MOD_NONE,
    KEY_MOD_SHIFT,
    KEY_MOD_CONTROL,
    KEY_MOD_ALT,
    KEY_MOD_SUPER,
    KEY_MOD_CAPS_LOCK,
    KEY_MOD_NUM_LOCK,
};

struct KeyPress {
    Key key;
    int scancode;
    KeyAction action;
    KeyMod mod;
};

