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

PANEL_SIZE(1000, 1000)

SCREEN(SCR, "", 20, 20, 50, 50)

FADER(FD1_1, "Vol", 50, 100, 30)
FADER(FD1_2, "Atck", 50, 150, 30)
FADER(FD1_4, "Dcy", 50, 200, 30)
FADER(FD1_3, "Rel", 50, 250, 30)

FADER(FD2_1, "Vol", 150, 100, 30)
FADER(FD2_2, "Atck", 150, 150, 30)
FADER(FD2_4, "Dcy", 150, 200, 30)
FADER(FD2_3, "Rel", 150, 250, 30)

LED(LED1, "", 50, 300, 30)
LED(LED2, "", 150, 300, 30)

BUTTON(PAD1, "Pad 1", 50, 350, 50, 30)
BUTTON(PAD2, "Pad 2", 150, 350, 50, 30)

