#include "ofxDeSynthUI.h"


namespace DeUI {
	//--------------------------------------------------------------
	UI::UI()
	{
		// Components creation
#define FADER(NAME, V, TITLE, MAX, X, Y, D) ui##NAME = new Fader(ControlData(this, #NAME, TITLE, X, Y, D, D), &V, MAX);
#define JOYSTICK(NAME, VX, VY, TITLE, MAX, X, Y, D) ui##NAME = new Joystick(ControlData(this, #NAME, TITLE, X, Y, D, D), &VX, &VY, MAX);
#define BUTTON(NAME, V, TITLE, KEY, X, Y, W, H, SHAPE) ui##NAME = new Button(ControlData(this, #NAME, TITLE, X, Y, W, H), &V, KEY, Shape::##SHAPE);
#define LED(NAME, V, TITLE, X, Y, D) ui##NAME = new Led(ControlData(this, #NAME, TITLE, X, Y, D, D), &V);
#define DRAWLINE(NAME, X, Y, W, H) ui##NAME = new Line(ControlData(this, #NAME, "", X, Y, W, H));
#define SCREEN(NAME, TITLE, X, Y, W, H) ui##NAME = new Screen(ControlData(this, #NAME, TITLE, X, Y, W, H));

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
	float UI::value_to_float(int v, int Max)
	{
		return float(v) / Max;
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
		for (auto c : controls_) {
			c->update();
		}
	}
	void UI::store_last_values() {
		for (auto c : controls_) {
			c->store_last_value();
		}
	}


	void UI::keyPressed(int key) {
		onEvent({ DeUI::EventType::keyPressed, glm::vec2(0,0), 0, key });
	}
	void UI::keyReleased(int key) {
		onEvent({ DeUI::EventType::keyReleased, glm::vec2(0,0), 0, key });
	}
	void UI::mouseMoved(int x, int y) {
		onEvent({ DeUI::EventType::mouseMoved, glm::vec2(x, y), 0, 0 });
	}
	void UI::mouseDragged(int x, int y, int button) {
		onEvent({ DeUI::EventType::mouseDragged, glm::vec2(x, y), button, 0 });
	}
	void UI::mousePressed(int x, int y, int button) {
		onEvent({ DeUI::EventType::mousePressed, glm::vec2(x, y), button, 0 });
	}
	void UI::mouseReleased(int x, int y, int button) {
		onEvent({ DeUI::EventType::mouseReleased, glm::vec2(x, y), button, 0 });
	}

	void UI::onEvent(const Event& event) {
		Event ev = event;
		if (event.isMouseEvent()) {
			ev.pos -= transp_;
			ev.pos /= scale_;

			// On right mouse button output mouse coords
			if (event.button == 2 && event.type != EventType::mouseReleased) {
				cout << "Mouse pos " << ev.pos.x << " " << ev.pos.y << endl;
			}
		}
		for (auto c : controls_) {
			if (c->onEvent(ev)) {
				return;
			}
		}
	}

	//--------------------------------------------------------------
	void UI::draw(float W, float H) {
		scale_ = min(W / W_, H / H_);
		float w1 = W_ * scale_;
		float h1 = H_ * scale_;
		transp_ = glm::vec2((W - w1) / 2, (H - h1) / 2);

		ofPushMatrix();
		ofTranslate(transp_);
		ofScale(scale_, scale_);

		ofSetColor(BackgroundColor_);
		ofFill();
		ofDrawRectangle(0, 0, W_, H_);
		ofSetColor(PenColorSecondary_);
		ofFill();

		DrawData draw_data;
		draw_data.font = &font_;
		draw_data.BackgroundColor = BackgroundColor_;
		draw_data.PenColor = PenColor_;
		draw_data.PenColorSecondary = PenColorSecondary_;
		draw_data.PenSelected = PenSelected_;

		for (auto c : controls_) {
			c->draw(draw_data);
		}

		ofPopMatrix();
	}

	void UI::save_json(const string& file_name) {
		ofJson json = ofJson::object();
		for (auto c : controls_) {
			c->save_json(json);
		}
		ofSavePrettyJson(file_name, json);
	}

	void UI::load_json(const string& file_name) {
		ofFile file(file_name);
		if (file.exists()) {
			ofJson json;
			file >> json;
			if (json.is_object()) {
				for (auto c : controls_) {
					c->load_json(json);
				}
			}
		}
	}

	//--------------------------------------------------------------
	Control::Control(ControlData data)
		: ui(data.ui), name(data.name), title(data.title), pos(data.pos), size(data.size)
	{
		ui->register_control(this);
	}
	ofRectangle Control::rect()
	{
		return ofRectangle(pos.x - size.x / 2, pos.y - size.y / 2, size.x, size.y);
	}

	void Font::draw(const string& text, float x, float y, bool centerY)
	{
		ofSetColor(color);
		auto box = font.getStringBoundingBox(text, 0, 0);
		y = (centerY) ? y + box.y / 2 : y - shiftY;
		font.drawString(text, x - box.width / 2, y);
	}

	void Control::draw(DrawData& draw_data) {

	}

	void ControlWithValue::save_json(ofJson& json) {
		if (save_json_enabled) {
			json[name] = value->value;
		}
	}
	void ControlWithValue::load_json(ofJson& json) {
		if (save_json_enabled) {
			if (!json[name].empty()) {
				value->value = json[name];
			}
		}
	}
	void ControlWithValue::update() {
	}
	void ControlWithValue::store_last_value() {
		value->store_last_value();
	}

	void Fader::draw(DrawData& draw_data) {
		ofColor color = (click.clicked) ? draw_data.PenSelected : draw_data.PenColorSecondary;
		ofSetColor(color);
		ofNoFill();
		ofDrawEllipse(pos.x, pos.y, size.x, size.y);
		draw_data.font->draw(title, pos.x, pos.y + size.y / 2);

		// Marks
		float R1 = size.x / 2;
		float R2 = R1 * 0.8;
		ofSetColor(draw_data.PenColor);
		for (int i = 0; i <= maxval; i++) {
			auto vec = value_to_vec(i);
			ofDrawLine(pos + vec * R1, pos + vec * R2);
		}
		// Current value
		ofSetColor(draw_data.PenColor);
		auto vec = value_to_vec(value->value);
		ofDrawLine(pos, pos + vec * R2);
	}
	glm::vec2 Fader::value_to_vec(int v) {
		const float wide = 60;
		const float angle1 = 90 + wide;
		const float angle2 = 360 + 90 - wide;
		float angle = ofMap(v, 0, maxval, angle1, angle2) * DEG_TO_RAD;
		return glm::vec2(cos(angle), sin(angle));
	}
	bool Fader::onEvent(const Event& event)
	{
		switch (event.type) {
		case EventType::mousePressed:
			if (rect().inside(event.pos)) {
				click.clicked = true;
				click.pos = event.pos;
				click.value = value->value;
				return true;
			}
			break;
		case EventType::mouseDragged:
			if (click.clicked) {
				const float faderRange = 100;
				int v = int(click.value - (event.pos.y - click.pos.y) * maxval / faderRange);
				value->value = min(max(v, 0), maxval);
				return true;
			}
			break;
		case EventType::mouseReleased:
			if (click.clicked) {
				// Send last value as 'dragged' event
				Event ev = event;
				ev.type = EventType::mouseDragged;
				onEvent(ev);
				click.clicked = false;
				return true;
			}
			break;
		default:
			return false;
		}
		return false;
	}
	void Joystick::save_json(ofJson& json) {
		// json[name + "X"] = valueX->value;
		// json[name + "Y"] = valueY->value;
	}
	void Joystick::load_json(ofJson& json) {
		// if (!json[name + "X"].empty()) {
		// 	valueX->value = json[name + "X"];
		// }
		// if (!json[name + "Y"].empty()) {
		// 	valueY->value = json[name + "Y"];
		// }
	}
	void Joystick::store_last_value() {
		valueX->store_last_value();
		valueY->store_last_value();
	}
	void Joystick::draw(DrawData& draw_data) {
		ofColor color = (click.clicked) ? draw_data.PenSelected : draw_data.PenColorSecondary;
		ofSetColor(color);
		ofNoFill();
		ofDrawRectangle(pos.x - size.x / 2, pos.y - size.y / 2, size.x, size.y);
		ofDrawEllipse(pos.x, pos.y, size.x, size.y);
		draw_data.font->draw(title, pos.x, pos.y + size.y / 2);

		// Current value
		ofSetColor(draw_data.PenColor);
		auto vec = pos + value_to_vec() * (size.x / 2, size.y / 2);
		ofDrawLine(pos, vec);
		ofFill();
		ofDrawCircle(vec, size.x / 12);
	}
	glm::vec2 Joystick::value_to_vec()
	{
		return glm::vec2(float(valueX->value) / maxval, -float(valueY->value) / maxval);
	}

	bool Joystick::onEvent(const Event& event) {
		switch (event.type) {
		case EventType::mousePressed:
			if (rect().inside(event.pos)) {
				click.clicked = true;
				click.pos = event.pos;
				click.valueX = valueX->value;
				click.valueY = valueY->value;
				return true;
			}
			break;
		case EventType::mouseDragged:
			if (click.clicked) {
				const float faderRange = 100;
				int vx = int(click.value + (event.pos.x - click.pos.x) * maxval / faderRange);
				int vy = int(click.value - (event.pos.y - click.pos.y) * maxval / faderRange);
				valueX->value = min(max(vx, -maxval), maxval);
				valueY->value = min(max(vy, -maxval), maxval);
				return true;
			}
			break;
		case EventType::mouseReleased:
			if (click.clicked) {
				// Return to zero value
				valueX->value = 0;
				valueY->value = 0;
				click.clicked = false;
				return true;
			}
			break;
		default:
			return false;
		}
		return false;
	}

	void Button::draw(DrawData& draw_data) {
		/*if (value->value == 1) {
			ofSetColor(32, 32, 0);
			ofFill();
			ofDrawRectangle(pos.x - size.x / 2, pos.y - size.y / 2, size.x, size.y);
		}*/
		ofColor color = (value->value == 1) ? draw_data.PenSelected : draw_data.PenColorSecondary;
		ofSetColor(color);
		ofNoFill();
		if (shape == Shape::Rectangle)
			ofDrawRectangle(pos.x - size.x / 2, pos.y - size.y / 2, size.x, size.y);
		if (shape == Shape::Circle)
			ofDrawEllipse(pos.x, pos.y, size.x, size.y);
		draw_data.font->draw(title, pos.x, pos.y + size.y / 2);
	}
	bool Button::onEvent(const Event& event)
	{
		switch (event.type) {
		case EventType::mousePressed:
			if (rect().inside(event.pos)) {
				clicked = true;
				value->value = 1;
				return true;
			}
			break;
		case EventType::mouseReleased:
			if (clicked) {
				clicked = false;
				value->value = 0;
				return true;
			}
			break;
		case EventType::keyPressed:
			if (event.key == key) {
				value->value = 1;
				return true;
			}
			break;
		case EventType::keyReleased:
			if (event.key == key) {
				value->value = 0;
				return true;
			}
			break;
		default:
			return false;
		}
		return false;
	}

	void Led::draw(DrawData& draw_data) {
		if (value->value == 1) {
			ofSetColor(draw_data.PenSelected);
			ofFill();
			ofDrawEllipse(pos.x, pos.y, size.x / 2, size.y / 2);
		}

		ofSetColor(draw_data.PenColorSecondary);
		ofNoFill();
		ofDrawEllipse(pos.x, pos.y, size.x, size.y);
		draw_data.font->draw(title, pos.x, pos.y + size.y / 2);
	}

	void Line::draw(DrawData& draw_data)
	{
		ofSetColor(draw_data.PenColorSecondary);
		ofNoFill();
		ofDrawLine(pos.x, pos.y, pos.x + size.x, pos.y + size.y);
	}

	void Screen::draw(DrawData& draw_data) {
		if (image_.isAllocated()) {
			ofSetColor(255);
			image_.getTextureReference().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
			image_.draw(pos.x, pos.y, size.x, size.y);
		}
		ofSetColor(draw_data.PenColorSecondary);
		ofNoFill();
		ofDrawRectangle(pos.x - 1, pos.y - 1, size.x + 2, size.y + 2);
		draw_data.font->draw(title, pos.x + size.x / 2, pos.y - 1);
	}
	ofRectangle Screen::rect()
	{
		return ofRectangle(pos.x, pos.y, size.x, size.y);
	}

	void Screen::set_image_grayscale(unsigned char* image, int w, int h)
	{
		image_.setFromPixels(image, w, h, OF_IMAGE_GRAYSCALE);
	}

	void Screen::set_image_rgb(unsigned char* image, int w, int h)
	{
		image_.setFromPixels(image, w, h, OF_IMAGE_COLOR);
	}
	//--------------------------------------------------------------
}