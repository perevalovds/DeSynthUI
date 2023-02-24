#pragma once

// UI for synth
/*
## Usage
- Prepare DefUI.h file with UI definition - see example.
- Add data / fonts / verdana.ttf font file.
- In case of compiling errors, add `./src` to project Additional Include Directories.
*/

#include "ofMain.h"

namespace DeUI {
	class UI;
	struct ValueInt {
		int value = 0;	// value from control
		int value_prev = 0;
		void store_last_value() { value_prev = value; }
		bool changed() const { return value != value_prev; }
	};
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
	struct ClickData {
		bool clicked = false;
		glm::vec2 pos = glm::vec2(0, 0);
		int value = 0;	// For Fader
		int valueX = 0; // For Joystick
		int valueY = 0;
	};
	struct ControlData {
		ControlData() {}
		ControlData(UI* Ui, string Name, string Title, float X, float Y, float W, float H)
			: ui(Ui), name(Name), title(Title), pos(X, Y), size(W, H)
		{
		}
		UI* ui = nullptr;
		string name;
		string title;
		glm::vec2 pos;
		glm::vec2 size;
	};
	struct DrawData {
		Font* font = nullptr;
		ofColor BackgroundColor;
		ofColor PenColor;
		ofColor PenColorSecondary;
		ofColor PenSelected;
	};
	class Control {
	public:
		Control(ControlData data);
		virtual ~Control() {}
		UI* ui;
		string name;
		string title;
		glm::vec2 pos;
		glm::vec2 size;
		virtual void draw(DrawData& draw_data);
		virtual ofRectangle rect();
		virtual bool onEvent(const Event& event) { return false; }
		virtual void save_json(ofJson& json) {}
		virtual void load_json(ofJson& json) {}
		virtual void update() {}
		virtual void store_last_value() {};
	};
	class ControlWithValue : public Control {
	public:
		ControlWithValue(ControlData data, ValueInt* Value,
			bool SaveJson) 
			: Control(data), value(Value),
			save_json_enabled(SaveJson) {}
		virtual ~ControlWithValue() {}
		ValueInt* value = nullptr;
		bool save_json_enabled = true;
		virtual void save_json(ofJson& json);
		virtual void load_json(ofJson& json);
		virtual void update();
		virtual void store_last_value();
	};
	class Fader : public ControlWithValue {
	public:
		Fader(ControlData data, ValueInt* Value, int Max) 
			: ControlWithValue(data, Value, true), maxval(Max) {}
		virtual ~Fader() {}
		virtual void draw(DrawData& draw_data);
		int maxval = 10;
		glm::vec2 value_to_vec(int v);
		virtual bool onEvent(const Event& event);
		ClickData click;
	};
	class Joystick : public Control {
	public:
		Joystick(ControlData data, ValueInt* ValueX, ValueInt* ValueY, int Max)
			: Control(data), valueX(ValueX), valueY(ValueY), maxval(Max) {}
		virtual ~Joystick() {}

		virtual void save_json(ofJson& json);
		virtual void load_json(ofJson& json);
		virtual void store_last_value();
		virtual void draw(DrawData& draw_data);
		virtual bool onEvent(const Event& event);

		ValueInt* valueX = nullptr;
		ValueInt* valueY = nullptr;
		int maxval = 10;
		glm::vec2 value_to_vec();
		ClickData click;
	};
	class Button : public ControlWithValue {
	public:
		Button(ControlData data, ValueInt* Value, int Key)
			: ControlWithValue(data, Value, false), key(Key) {}
		virtual ~Button() {}
		virtual void draw(DrawData& draw_data);
		int key = 0;
		virtual bool onEvent(const Event& event);
		bool clicked = false;
	};
	class Led : public ControlWithValue {
	public:
		Led(ControlData data, ValueInt* Value) 
			: ControlWithValue(data, Value, false) {}
		virtual ~Led() {}
		virtual void draw(DrawData& draw_data);
	};
	class Screen : public Control {
	public:
		Screen(ControlData data) : Control(data) {}
		virtual ~Screen() {}
		virtual void draw(DrawData& draw_data);
		virtual ofRectangle rect();
		void set_image_grayscale(unsigned char* image, int w, int h);
		void set_image_rgb(unsigned char* image, int w, int h);
	protected:
		ofImage image_;
	};
	//----------------------------------------------------------
	class UI {
	public:
		UI();
		~UI();
		void setup();
		void update();
		void store_last_values();
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

		float value_to_float(int v, int Max);

		// Variables definitions
#define VAR(V) ValueInt V;
#define VARARR(V, COUNT) ValueInt V[COUNT];

		// Components definitions
#define FADER(NAME, V, TITLE, MAX, X, Y, D) Fader* ui##NAME;
#define JOYSTICK(NAME, VX, VY, TITLE, MAX, X, Y, D) Joystick* ui##NAME;
#define BUTTON(NAME, V, KEY, TITLE, X, Y, W, H) Button* ui##NAME;
#define LED(NAME, V, TITLE, X, Y, D) Led* ui##NAME;
#define SCREEN(NAME, TITLE, X, Y, W, H) Screen* ui##NAME;
#define PANEL_SIZE(Width, Height) float W_ = Width; float H_ = Height;
#define	UI_COLORS(BackgroundColor, PenColor, PenColorSecondary, PenSelected) \
  ofColor BackgroundColor_ = BackgroundColor; \
  ofColor PenColor_ = PenColor; \
  ofColor PenColorSecondary_ = PenColorSecondary; \
  ofColor PenSelected_ = PenSelected;

#include "DefUI.h"

	protected:
		vector<Control*> controls_;
		Font font_;

		float scale_ = 1;
		glm::vec2 transp_ = glm::vec2(0, 0);

		void onEvent(const Event& event);
	};

}