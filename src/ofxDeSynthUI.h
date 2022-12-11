#pragma once

// UI for synth
// It's required to prepare DefUI.h file with UI definition,
// See example.

#include "ofMain.h"

namespace DeUI {
	class UI;
	enum class EventType : int {
		keyPressed = 0,
		keyReleased,
		mouseMoved,
		mouseDragged,
		mousePressed,
		mouseReleased
	};
	struct Event {
		EventType type;
		int value1 = 0;
		int value2 = 0;
		int value3 = 0;
	};
	struct Font {
		ofTrueTypeFont font;
		ofColor color;
		float shiftY = 0;
		void draw(const string& text, float x, float y, bool centerY = false);
	};
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
		virtual void draw(Font& font);
		virtual ofRectangle rect();
		virtual bool onEvent(const Event& event) { return false; }
	};
	class ControlWithValue : public Control {
	public:
		ControlWithValue(ControlData data, int* Value) : Control(data), value(Value) {}
		virtual ~ControlWithValue() {}
		int* value = nullptr;
	};
	class Fader : public ControlWithValue {
	public:
		Fader(ControlData data, int* Value, int Max) : ControlWithValue(data, Value), maxval(Max) {}
		virtual ~Fader() {}
		virtual void draw(Font& font);
		int maxval = 10;
		glm::vec2 value_to_vec(int v);
		virtual bool onEvent(const Event& event);
	};
	class Button : public ControlWithValue {
	public:
		Button(ControlData data, int* Value, int Key) : ControlWithValue(data, Value), key(Key) {}
		virtual ~Button() {}
		virtual void draw(Font& font);
		virtual ofRectangle rect();
		int key = 0;
		virtual bool onEvent(const Event& event);
	};
	class Led : public ControlWithValue {
	public:
		Led(ControlData data, int* Value) : ControlWithValue(data, Value) {}
		virtual ~Led() {}
		virtual void draw(Font& font);
	};
	class Screen : public Control {
	public:
		Screen(ControlData data) : Control(data) {}
		virtual ~Screen() {}
		virtual void draw(Font& font);
		virtual ofRectangle rect();
	};

	class UI {
	public:
		UI();
		~UI();
		void setup();
		void update();
		void draw(float W, float H);
		void onEvent(const Event& event);

		void register_control(Control* c);

		// Components definitions
#define FADER(NAME, TITLE, MAX, X, Y, D) Fader* ui##NAME; int NAME = 0;
#define BUTTON(NAME, TITLE, X, Y, W, H) Button* ui##NAME; int NAME = 0;
#define LED(NAME, TITLE, X, Y, D) Led* ui##NAME; int NAME = 0;
#define SCREEN(NAME, TITLE, X, Y, W, H) Screen* ui##NAME;
#define PANEL_SIZE(Width, Height) float W_ = Width; float H_ = Height;
#include "DefUI.h"

	protected:
		vector<Control*> controls_;
		Font font_;
	};

}