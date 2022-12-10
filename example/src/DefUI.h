// Defines for UI controls

#ifndef FADER
#define FADER(NAME, TITLE, X, Y, D)
#define BUTTON(NAME, TITLE, X, Y, W, H)
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
FONT_DEF("fonts/verdana.ttf", 16, ofColor(128), 10)

SCREEN(SCR, "", 50, 50, 300, 100)

FADER(FD1_1, "Vol", 150, 250, 30)
FADER(FD1_2, "Atck", 150, 300, 30)
FADER(FD1_4, "Dcy", 150, 350, 30)
FADER(FD1_3, "Rel", 150, 400, 30)

FADER(FD2_1, "Vol", 250, 250, 30)
FADER(FD2_2, "Atck", 250, 300, 30)
FADER(FD2_4, "Dcy", 250, 350, 30)
FADER(FD2_3, "Rel", 250, 400, 30)

LED(LED1, "", 150, 450, 15)
LED(LED2, "", 250, 450, 15)

BUTTON(PAD1, "Pad 1", 150, 480, 50, 30)
BUTTON(PAD2, "Pad 2", 250, 480, 50, 30)

