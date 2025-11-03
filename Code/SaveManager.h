#ifndef __SAVEMANAGER_H
#define __SAVEMANAGER_H

#include <string>
#include <fstream>
#include <vector>
#include <ctime>

class Game;

// Structure pour stocker les informations d'une sauvegarde
struct SaveSlot {
    int slotNumber;
    bool isEmpty;
    std::string player1Name;
    std::string player2Name;
    int player1Health;
    int player2Health;
    int currentTurnNumber;
    std::string currentPlayerName;
    std::string saveDate;
    
    SaveSlot() : slotNumber(0), isEmpty(true), player1Health(0), 
                 player2Health(0), currentTurnNumber(0) {}
};

class SaveManager {
private:
    static const int MAX_SAVE_SLOTS = 3;
    std::string m_saveDirectory;
    
    std::string getSaveFilePath(int slotNumber) const;
    std::string getCurrentDateTime() const;
    
public:
    SaveManager();
    SaveManager(const std::string& saveDirectory);
    
    // Gestion des sauvegardes
    bool saveGame(const Game& game, int slotNumber);
    bool loadGame(Game& game, int slotNumber);
    
    // Informations sur les sauvegardes
    std::vector<SaveSlot> getSaveSlots() const;
    SaveSlot getSaveSlotInfo(int slotNumber) const;
    bool isSlotEmpty(int slotNumber) const;
    bool deleteSave(int slotNumber);
    
    // Affichage
    void displaySaveSlots() const;
    
    // Utilitaires
    static std::string getDefaultSaveDirectory();
};

#endif
