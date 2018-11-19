#ifndef __GAME_VIEW_H__
#define __GAME_VIEW_H__

#include "View.h"
#include "../Model/Model.h"
#include "UnitView.h"
#include "BuildingView.h"
#include "SelectorView.h"
#include "BuildingConstructorView.h"
#include "MapView.h"
#include "ButtonView.h"
#include <memory>
#include <string>
#include <vector>

#define TAG_FONT_SIZE	16

#define BTN_INIT_HEIGHT 6
#define BTN_WIDTH 80
#define BTN_HEIGHT ((BTN_WIDTH) * 3 / 4)
#define BTN_VERT_SPACE ((BTN_HEIGHT) + 5)

#define ENERGY_BAR_WIDTH 5


class GameView : public View {
private:
	Model& model;
	std::vector<UnitView*> unitViews;
	std::vector<DeadUnitView*> deadUnitViews;
	std::vector<BuildingView*> buildingViews;
	SelectorView* selectorView;
	BuildingConstructorView* constructorView;
	MapView map_view;
	Area camera;
	Sound backgroundMusic;
	Text moneyTag, moneyBalance, buildingTag, unitsTag;
	std::vector<ButtonView*> buildingButtons;
	std::vector<ButtonView*> unitButtons;
	SdlTexture buttons;
	int map_width;
	int map_height;
	int camera_width;
	int camera_height;

public:
	GameView(const int width, const int height, Model& model);

	~GameView();

	SdlWindow& getWindow();

	void addUnitView(UnitView* unitView);

	void addBuildingView(BuildingView* buildingView);

	void addSelectorView(Selector& selector);

	void addBuildingConstructorView(BuildingConstructor* constructor);

	void RenderVPBar(int x, int y, int h, float percent, SDL_Color FGColor, SDL_Color BGColor);

	void cleanDeadViews();

	void moveUp(int distance);
	void moveDown(int distance);
	void moveLeft(int distance);
	void moveRight(const int distance);

	int getCameraX();
	int getCameraY();

	void grabMouse();
	void releaseMouse();

    ButtonView& createUnitButton(const std::string& filename);

	ButtonView& createBuildingButton(const std::string& filename);

	void render() override;
};

#endif	// __GAME_VIEW_H__
