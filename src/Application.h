#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "View/View.h"
#include "Controller/InputHandler.h"
#include "Model/Model.h"
#define WINDOW_WIDTH  2048
#define WINDOW_HEIGHT (WINDOW_WIDTH*3/4)

class Application {
public:
	//
	Application(View& view, InputHandler& handler, Model& model);
	// Application();

	//
	~Application();

	//
	bool running();

	//
	void handleEvent();

	//
	void update();

	//
	void render();

private:
	bool isRunning;
	// std::string host, port, house;
	View& view;
	InputHandler& handler;
	Model& model;
};

#endif	// __APPLICATION_H__