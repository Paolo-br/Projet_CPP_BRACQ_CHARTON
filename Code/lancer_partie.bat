@echo off
echo ========================================
echo    HERO REALMS - Compilation et Lancement
echo ========================================
echo.

REM Vérifier si WSL est disponible
wsl --list >nul 2>&1
if %ERRORLEVEL% EQU 0 (
    echo WSL detecte ! Compilation via WSL...
    echo.
    wsl bash -c "cd '/mnt/c/Users/paolo/OneDrive/Desktop/ET4/C++/Projet/Code' && make clean && make main && ./main"
) else (
    echo WSL non detecte. Tentative avec g++ local...
    echo.
    
    REM Vérifier si g++ est disponible
    g++ --version >nul 2>&1
    if %ERRORLEVEL% EQU 0 (
        echo Compilation en cours...
        g++ -Wall -Wextra -std=c++11 main.cpp Player.cpp Deck.cpp Card.cpp ChampionCard.cpp Ability.cpp SacrificeAbility.cpp Hand.cpp InPlayArea.cpp DiscardPile.cpp Market.cpp AllyAbility.cpp ActivateAbility.cpp Faction.cpp Game.cpp GameSettings.cpp PrimaryAbility.cpp Turn.cpp ActionCard.cpp ItemCard.cpp Effect.cpp GoldEffect.cpp AttackEffect.cpp HealEffect.cpp DrawEffect.cpp SacrificeEffect.cpp PrepareChampionEffect.cpp StunChampionEffect.cpp DiscardOpponentEffect.cpp ConditionalEffect.cpp ChoiceEffect.cpp DrawThenDiscardEffect.cpp Utils.cpp -o main.exe
        
        if %ERRORLEVEL% EQU 0 (
            echo.
            echo Compilation reussie ! Lancement du jeu...
            echo.
            main.exe
        ) else (
            echo.
            echo ERREUR : La compilation a echoue.
            pause
        )
    ) else (
        echo.
        echo ERREUR : Ni WSL ni g++ n'ont ete trouves.
        echo.
        echo Veuillez installer l'un des deux :
        echo   - WSL : wsl --install
        echo   - MinGW : https://www.mingw-w64.org/
        echo.
        pause
    )
)

echo.
pause
