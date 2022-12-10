#pragma once

// UI for synth
// It's required to prepare DefUI.h file with UI definition,
// See example.

#include "ofMain.h"

namespace DeUI {
	class UI;
	struct ControlData {
		ControlData() {}
		ControlData(UI* Parent, string Title, float X, float Y, float W, float H)
			: parent(Parent), title(Title), pos(X, Y), size(W, H)
		{
		}
		UI* parent;
		string title;
		glm::vec2 pos;
		glm::vec2 size;
	};
	class Control {
	public:
		Control(ControlData data);
		virtual ~Control() {}	
		UI* parent;
		string title;
		glm::vec2 pos;
		glm::vec2 size;
		virtual void draw();
	};

	class Fader : public Control {
	public:
		Fader(ControlData data, float *Value) : Control(data), value(Value) {}
		virtual ~Fader() {}
		float* value = nullptr;
		virtual void draw();
	};
	class Button : public Control {
	public:
		Button(ControlData data, int *Value) : Control(data), value(Value) {}
		virtual ~Button() {}
		int* value = 0;
		virtual void draw();
	};
	class Led : public Control {
	public:
		Led(ControlData data, int *Value) : Control(data), value(Value) {}
		virtual ~Led() {}
		int* value = 0;
		virtual void draw();
	};
	class Screen : public Control {
	public:
		Screen(ControlData data) : Control(data) {}
		virtual ~Screen() {}
		virtual void draw();
	};

	class UI {
	public:
		UI();
		~UI();
		void setup();
		void update();
		void draw(float W, float H);

		void register_control(Control* c);

		// Components definitions
#define FADER(NAME, TITLE, X, Y, D) Fader* ui##NAME; float NAME = 0;
#define BUTTON(NAME, TITLE, X, Y, W, H) Button* ui##NAME; int NAME = 0;
#define LED(NAME, TITLE, X, Y, D) Led* ui##NAME; int NAME = 0;
#define SCREEN(NAME, TITLE, X, Y, W, H) Screen* ui##NAME;
#define PANEL_SIZE(Width, Height) float W_ = Width; float H_ = Height;
#include "DefUI.h"

	protected:
		vector<Control*> controls_;
		ofTrueTypeFont font_;
		ofColor font_color_;
	};

}