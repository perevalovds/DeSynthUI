#pragma once

// UI for synth
/*
## Usage
- Prepare DefUI.h file with UI definition - see example.
- Add data / fonts / verdana.ttf font file.
- In case of compiling errors, add `. / src` to project Additional Include Directories.
*/

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
		glm::vec2 pos = glm::vec2(0, 0);
		int button = 0;
		int key = 0;
		bool isMouseEvent() const { return type >= EventType::mouseMoved; }
	};
	struct Font {
		ofTrueTypeFont font;
		ofColor color;
		float shiftY = 0;
		void draw(const string& text, float x, float y, bool centerY = false);
	};
	struct FaderClickData {
		bool clicked = false;
		glm::vec2 pos = glm::vec2(0, 0);
		int value = 0;
	};
	struct ControlData {
		ControlData() {}
		ControlData(UI* Parent, string Name, string Title, float X, float Y, float W, float H)
			: parent(Parent), name(Name), title(Title), pos(X, Y), size(W, H)
		{
		}
		UI* parent = nullptr;
		string name;
		string title;
		glm::vec2 pos;
		glm::vec2 size;
	};
	class Control {
	public:
		Control(ControlData data);
		virtual ~Control() {}
		UI* parent;
		string name;
		string title;
		glm::vec2 pos;
		glm::vec2 size;
		virtual void draw(Font& font);
		virtual ofRectangle rect();
		virtual bool onEvent(const Event& event) { return false; }
		virtual void save_json(ofJson& json) {}
		virtual void load_json(ofJson& json) {}
	};
	class ControlWithValue : public Control {
	public:
		ControlWithValue(ControlData data, int* Value) : Control(data), value(Value) {}
		virtual ~ControlWithValue() {}
		int* value = nullptr;
		virtual void save_json(ofJson& json);
		virtual void load_json(ofJson& json);
	};
	class Fader : public ControlWithValue {
	public:
		Fader(ControlData data, int* Value, int Max) : ControlWithValue(data, Value), maxval(Max) {}
		virtual ~Fader() {}
		virtual void draw(Font& font);
		int maxval = 10;
		glm::vec2 value_to_vec(int v);
		virtual bool onEvent(const Event& event);
		FaderClickData click;
	};
	class Button : public ControlWithValue {
	public:
		Button(ControlData data, int* Value, int Key) : ControlWithValue(data, Value), key(Key) {}
		virtual ~Button() {}
		virtual void draw(Font& font);
		int key = 0;
		virtual bool onEvent(const Event& event);
		bool clicked = false;
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
	//----------------------------------------------------------
	class UI {
	public:
		UI();
		~UI();
		void setup();
		void update();
		void draw(float W, float H);
		void save_json(const string& file_name = "values.json");
		void load_json(const string& file_name = "values.json");

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);

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

		float scale_ = 1;
		glm::vec2 transp_ = glm::vec2(0, 0);

		void onEvent(const Event& event);
	};

}