// Defines for UI controls

// Empty definitions
#ifndef FADER
#define FADER(NAME, TITLE, MAX, X, Y, D)
#define BUTTON(NAME, TITLE, KEY, X, Y, W, H)
#define LED(NAME, TITLE, X, Y, D)
#define SCREEN(NAME, TITLE, X, Y, W, H)
#endif
#ifndef PANEL_SIZE
#define PANEL_SIZE(Width, Height)
#endif
#ifndef FONT_DEF
#define FONT_DEF(FontFile, FontSize, FontColor, ShiftY)
#endif

PANEL_SIZE(400, 600)
FONT_DEF("fonts/verdana.ttf", 10, ofColor(128), 4)

SCREEN(SCR, "Screen", 50, 80, 300, 100)

FADER(FD1_Vol, "Vol", 10, 150, 250, 30)
FADER(FD1_Atck, "Atck", 10, 150, 300, 30)
FADER(FD1_Dcy, "Dcy", 10, 150, 350, 30)
FADER(FD1_Rel, "Rel", 10, 150, 400, 30)

FADER(FD2_Vol, "Vol", 10, 250, 250, 30)
FADER(FD2_Atck, "Atck", 10, 250, 300, 30)
FADER(FD2_Dcy, "Dcy", 10, 250, 350, 30)
FADER(FD2_Rel, "Rel", 10, 250, 400, 30)

LED(LED1, "Led 1", 150, 450, 15)
LED(LED2, "Led 2", 250, 450, 15)

BUTTON(PAD1, "Pad 1", '1', 150, 480, 50, 30)
BUTTON(PAD2, "Pad 2", '2', 250, 480, 50, 30)

// Clear definitions
#undef FADER
#undef BUTTON
#undef LED(NAME, TITLE, X, Y, D)
#undef SCREEN(NAME, TITLE, X, Y, W, H)
#undef PANEL_SIZE
#undef FONT_DEF
