#include "ofxDeSynthUI.h"


namespace DeUI {

	//--------------------------------------------------------------
	Control::Control(ControlData data)
		: parent(data.parent), title(data.title), pos(data.pos), size(data.size)
	{
		parent->register_control(this);
	}

	//--------------------------------------------------------------
	UI::UI()
	{
		// Components creation
#define FADER(NAME, TITLE, X, Y, D) ui##NAME = new Fader(ControlData(this, TITLE, X, Y, D, D), &NAME);
#define BUTTON(NAME, TITLE, X, Y, W, H) ui##NAME = new Button(ControlData(this, TITLE, X, Y, W, H), &NAME);
#define LED(NAME, TITLE, X, Y, D) ui##NAME = new Led(ControlData(this, TITLE, X, Y, D, D), &NAME);
#define SCREEN(NAME, TITLE, X, Y, W, H) ui##NAME = new Screen(ControlData(this, TITLE, X, Y, W, H));

#include "DefUI.h"
	}

	//--------------------------------------------------------------
	UI::~UI()
	{
		for (auto c : controls_) {
			delete c;
		}
		controls_.clear();
	}

	//--------------------------------------------------------------
	void UI::register_control(Control* c)
	{
		controls_.push_back(c);
	}

	//--------------------------------------------------------------
	void UI::setup() {
#include "DefUI.h"
	}

	//--------------------------------------------------------------
	void UI::update() {

	}

	//--------------------------------------------------------------
	void UI::draw() {
		for (auto c : controls_) {
			c->draw();
		}
	}

	//--------------------------------------------------------------
	void Control::draw() {

	}
	void Fader::draw() {

	}
	void Button::draw() {

	}
	void Led::draw() {

	}
	void Screen::draw() {

	}

	//--------------------------------------------------------------
}