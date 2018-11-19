#include "ButtonView.h"
/*#include "ButtonViewHidden.h"
#include "ButtonViewEnabled.h"
#include "ButtonViewDisabled.h"*/
#include <string>

ButtonView::ButtonView(const std::string &filename, const SdlWindow &window, int number_steps) :
	buttonState(ViewState::HIDDEN),
	/*currentState(new ButtonHidden()),*/
	buttonImage(filename, window),
    timer(window.getRenderer(), number_steps),
	x(0),
	y(0),
	width(buttonImage.width),
	height(buttonImage.height) {}

ButtonView::~ButtonView() {
	// delete this->currentState;
}

bool ButtonView::isClicked(const int x, const int y) {
	return (((x >= this->x) && (x <= this->x + this->width)) &&
	        (((y >= this->y) && (y <= this->y + this->height))));
}

void ButtonView::setState(const ViewState newState) {
	// delete this->currentState;

	switch (newState) {
	case ViewState::HIDDEN:
		// this->currentState = new ButtonHidden();
		this->buttonState = ViewState::HIDDEN;
		break;
	case ViewState::ENABLED:
		// this->currentState = new ButtonEnabled();
		this->buttonState = ViewState::ENABLED;
		break;
	case ViewState::DISABLED:
		// this->currentState = new ButtonDisabled();
		this->buttonState = ViewState::DISABLED;
		break;
	case ViewState::BUSY:
		// this->currentState = new ButtonDisabled();
		this->buttonState = ViewState::BUSY;
		break;
	}
}

void ButtonView::render(const Area& dest) {
	Area enabledSrc(0, 0, this->buttonImage.width / 2,
	                this->buttonImage.height);
	Area disabledSrc(this->buttonImage.width/2, 0,
	                 this->buttonImage.width,
	                 this->buttonImage.height);
	switch (this->buttonState) {
	case ViewState::HIDDEN:
		break;
	case ViewState::ENABLED:
		this->buttonImage.render(enabledSrc, dest);
		this->x = dest.getX();
		this->y = dest.getY();
		this->height = dest.getHeight();
		this->width = dest.getWidth();
		break;
	case ViewState::DISABLED:
		this->buttonImage.render(disabledSrc, dest);
        break;
	case ViewState::BUSY:
		this->buttonImage.render(disabledSrc, dest);
		this->timer.render(dest);
		break;
	}
}
