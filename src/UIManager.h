#pragma once
class Manager;
class Entity;

struct ButtonImages {
    std::string normalImage = "";
    std::string highlightedImage = "";
};

class UIManager {
public:
    UIManager(Manager* manager);
    void init();
    void changedState();
    void draw();
private:
    void showPlayButton();
    void showGameUI();
    void showPauseUI();
    void showFinishUI();

    void clear();

    Entity& createUIObject();
    const Entity& createButton();

private:
    Manager* _manager;
};

typedef std::shared_ptr<UIManager> UIManagerPtr;
