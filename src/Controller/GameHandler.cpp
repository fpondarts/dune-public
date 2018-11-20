#include "GameHandler.h"
#include "ButtonHandlerHarvester.h"
#include "ButtonHandlerTank.h"
#include "ButtonHandlerTrike.h"
#include "ButtonHandlerRaider.h"
#include "ButtonHandlerHeavyInfantry.h"
#include "ButtonHandlerLightInfantry.h"
#include "ButtonHandlerBarracks.h"
#include "ButtonHandlerHeavyFactory.h"
#include "ButtonHandlerLightFactory.h"
#include "ButtonHandlerSpiceRefinery.h"
#include "ButtonHandlerSpiceSilo.h"
#include "ButtonHandlerWindTrap.h"
#include "../View/UnitViewFactory.h"
#include <vector>

int GameHandler::actual_player = PLAYER;

GameHandler::GameHandler(GameView &view, Model &model) :
    InputHandler(),
    view(view),
    model(model),
    selector(0, 0),
    constructor(model,model.getPlayer(GameHandler::actual_player),view) {
    view.addSelectorView(this->selector);
    this->buttons.push_back(new ButtonHandlerWindTrap(this->model, this->view, constructor));
    this->buttons.push_back(new ButtonHandlerSpiceRefinery(this->model, this->view, constructor));
    this->buttons.push_back(new ButtonHandlerBarracks(this->model, this->view, constructor));
    this->buttons.push_back(new ButtonHandlerLightFactory(this->model, this->view, constructor));
    this->buttons.push_back(new ButtonHandlerHeavyFactory(this->model, this->view, constructor));
    this->buttons.push_back(new ButtonHandlerSpiceSilo(this->model, this->view, constructor));
    this->buttons.push_back(new ButtonHandlerLightInfantry(this->model, this->view));
    this->buttons.push_back(new ButtonHandlerHeavyInfantry(this->model, this->view));
    this->buttons.push_back(new ButtonHandlerTrike(this->model, this->view));
    this->buttons.push_back(new ButtonHandlerRaider(this->model, this->view));
    this->buttons.push_back(new ButtonHandlerTank(this->model, this->view));
    this->buttons.push_back(new ButtonHandlerHarvester(this->model, this->view));
    for (auto& button : this->buttons) {
        if (button->canBeEnabled()) {
            button->setState(State::ENABLED);
        }
    }
} 

GameHandler::~GameHandler() {
    while (!this->buttons.empty()) {
        delete this->buttons.back();
        this->buttons.pop_back();
    }
}

bool GameHandler::handleInput() {
    bool keepPlaying = true;
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type) {
    case SDL_QUIT:
        keepPlaying = false;
        break;
    case SDL_MOUSEBUTTONDOWN:
        if (event.button.button == SDL_BUTTON_LEFT) {
            //this->view.grabMouse();
            this->cursor.initialPosition();
            if (constructor.on == false){ 
                this->selector.drag = true;
                this->selector.drag_source = selector.pos;
            }
        }
        break;
    case SDL_MOUSEMOTION:
        this->cursor.currentPosition();
        if (this->cursor.current_x >= view.getCameraWidth()){
            this->selector.pos.x = this->view.getCameraX() + this->view.getCameraWidth();
        } else this->selector.pos.x = this->view.getCameraX() + this->cursor.current_x;
        this->selector.pos.y = this->cursor.current_y + this->view.getCameraY();
        this->constructor.pos.x = this->selector.pos.x;
        this->constructor.pos.y = this->selector.pos.y;
        break;
    case SDL_MOUSEBUTTONUP:
        this->cursor.currentPosition();
        if (event.button.button == SDL_BUTTON_LEFT) {
            this->selector.drag = false;
            Area selectArea(this->selector.drag_source, this->selector.pos);
            std::vector<Unit*> selection = model.selectUnitsInArea(selectArea, model.getPlayer(GameHandler::actual_player));
            std::vector<Building*> selected_buildings = model.selectBuildingsInArea(selectArea,model.getPlayer(GameHandler::actual_player));
            this->selector.addSelection(selection); 
            this->selector.addSelection(selected_buildings); 
            this->view.releaseMouse();
            if (constructor.on){
                constructor.build();
            }
            for (auto& button : this->buttons) {
                button->handleUserInput(this->cursor.current_x, this->cursor.current_y);
            }
        }
        // TEST
        if (event.button.button == SDL_BUTTON_RIGHT) {
            this->cursor.currentPosition();
            this->constructor.on = false;
            //this->model.getMap().setDestiny(unit, this->cursor.current_x + this->view.getCameraX(), this->cursor.current_y + this->view.getCameraY());
            Position pos(this->cursor.current_x + this->view.getCameraX(), this->cursor.current_y + this->view.getCameraY());
            for (auto& unit : this->selector.selection.getSelectedUnits()) {
                this->model.actionOnPosition(pos, *unit);
            }
        }
        break;
    case SDL_KEYDOWN:
        switch ( event.key.keysym.sym ) {
        case SDLK_LEFT:
        case SDLK_a:
            view.moveLeft(MOVE_AMOUNT);
            break;
        case SDLK_RIGHT:
        case SDLK_d:
            view.moveRight(MOVE_AMOUNT);
            break;
        case SDLK_DOWN:
        case SDLK_s:
            view.moveDown(MOVE_AMOUNT);
            break;
        case SDLK_UP:
        case SDLK_w:
            view.moveUp(MOVE_AMOUNT);
            break;

        case SDLK_DELETE:
        case SDLK_BACKSPACE:
            {
                std::vector<Building*>& to_sell = this->selector.selection.getSelectedBuildings();
                for (auto itr = to_sell.begin(); itr!=to_sell.end() ; itr++){
                    model.getPlayer(GameHandler::actual_player).sellBuilding(*itr);
                }
            }
            break;
        // Temporal
        case SDLK_c:
            GameHandler::actual_player++;
            if (GameHandler::actual_player >= 3){
                GameHandler::actual_player = 0;
            }
            view.changePlayer(actual_player);
            break;
            /////////
        default:
            break;
        }
        break;
    }
    for (auto& button : this->buttons) {
        button->update();
    }
    this->view.cleanDeadViews();
    this->selector.selection.eraseDeads();
    return keepPlaying;
}
