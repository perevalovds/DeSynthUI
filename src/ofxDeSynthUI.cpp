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
#define FADER(NAME, TITLE, MAX, X, Y, D) ui##NAME = new Fader(ControlData(this, TITLE, X, Y, D, D), &NAME, MAX );
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
	void Font::draw(const string& text, float x, float y, bool centerY)
	{
		ofSetColor(color);
		auto box = font.getStringBoundingBox(text, 0, 0);
		y = (centerY) ? y - box.y / 2 : y - shiftY;
		font.drawString(text, x-box.width / 2, y);
	}

	//--------------------------------------------------------------
	void Control::draw(Font& font) {

	}
	void Fader::draw(Font& font) {
		ofSetColor(128);
		ofNoFill();
		ofDrawEllipse(pos.x, pos.y, size.x, size.y);
		font.draw(title, pos.x, pos.y - size.y / 2);

		// Marks
		float R1 = size.x / 2;
		float R2 = R1 * 0.8;
		ofSetColor(128);
		for (int i = 0; i <= maxval; i++) {
			auto vec = value_to_vec(i);
			ofDrawLine(pos + vec * R1, pos + vec * R2);
		}
		// Current value
		ofSetColor(255);
		auto vec = value_to_vec(*value);
		ofDrawLine(pos, pos + vec * R2);
	}
	glm::vec2 Fader::value_to_vec(int v) {
		const float wide = 60;
		const float angle1 = 90 + wide;
		const float angle2 = 360 + 90 -wide;
		float angle = ofMap(v, 0, maxval, angle1, angle2) * DEG_TO_RAD;
		return glm::vec2(cos(angle), sin(angle));
	}

	void Button::draw(Font& font) {
		ofSetColor(128);
		ofNoFill();
		ofDrawRectangle(pos.x - size.x / 2, pos.y - size.y / 2, size.x, size.y);
		font.draw(title, pos.x, pos.y, true);
	}
	void Led::draw(Font& font) {
		ofSetColor(128);
		ofNoFill();
		ofDrawEllipse(pos.x, pos.y, size.x, size.y);
		font.draw(title, pos.x, pos.y - size.y / 2);
	}
	void Screen::draw(Font& font) {
		ofSetColor(128);
		ofNoFill();
		ofDrawRectangle(pos.x-1, pos.y-1, size.x+2, size.y+2);
		font.draw(title, pos.x + size.x/2, pos.y-1);
	}

	//--------------------------------------------------------------
}