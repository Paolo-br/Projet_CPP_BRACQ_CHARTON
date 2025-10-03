#ifndef GAMESETTINGS_H
#define GAMESETTINGS_H

class GameSettings {
private:
    bool godMode;

public:
    GameSettings(); // constructeur par défaut
    void enableGodMode();
    void disableGodMode();
    bool isGodModeEnabled() const;
};

#endif // GAMESETTINGS_H
