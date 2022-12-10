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
#define FONT_DEF(FontFile, FontSize, FontColor, ShiftY) \
	string font_file = FontFile; \
	int font_size = FontSize; \
	font_.color = FontColor; \
	font_.shiftY = ShiftY;
#include "DefUI.h"

		font_.font.load(font_file, font_size);
	}

	//--------------------------------------------------------------
	void UI::update() {

	}

	//--------------------------------------------------------------
	void UI::draw(float W, float H) {
		float scl = min(W / W_, H / H_);
		float w1 = W_ * scl;
		float h1 = H_ * scl;

		ofPushMatrix();
		ofTranslate((W - w1) / 2, (H - h1) / 2);
		ofScale(scl, scl);
		for (auto c : controls_) {
			c->draw(font_);
		}

		ofSetColor(128);
		ofNoFill();
		ofDrawRectangle(0, 0, W_, H_);

		ofPopMatrix();
	}

	//--------------------------------------------------------------
	void Font::draw(const string& text, float x, float y)
	{
		ofSetColor(color);
		font.drawString(text, x, y - shiftY);
	}

	//--------------------------------------------------------------
	void Control::draw(Font& font) {

	}
	void Fader::draw(Font& font) {
		ofSetColor(128);
		ofNoFill();
		ofDrawEllipse(pos.x, pos.y - size.y / 2, size.x, size.y);
		font.draw(title, pos.x, pos.y - size.y / 2);
	}
	void Button::draw(Font& font) {
		ofSetColor(128);
		ofNoFill();
		ofDrawRectangle(pos.x - size.x / 2, pos.y - size.y / 2, size.x, size.y);

	}
	void Led::draw(Font& font) {
		ofSetColor(128);
		ofNoFill();
		ofDrawEllipse(pos.x, pos.y - size.y / 2, size.x, size.y);
	}
	void Screen::draw(Font& font) {
		ofSetColor(128);
		ofFill();
		ofDrawRectangle(pos.x, pos.y, size.x, size.y);

	}

	//--------------------------------------------------------------
}