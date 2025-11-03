@echo off
@echo off
chcp 65001 >nul
setlocal

echo ========================================
echo    HERO REALMS - Compilation et Lancement
echo ========================================
echo.

REM Répertoire du script (avec backslash final)
set "SCRIPT_DIR=%~dp0"

REM Si l'exécutable existe déjà, lance-le directement (Windows)
if exist "%SCRIPT_DIR%main.exe" (
    echo Executable Windows trouve : lancement de main.exe
    pushd "%SCRIPT_DIR%"
    main.exe
    popd
    goto :end
)
pause

REM Si l'exécutable Linux existe (par ex. deja compile via WSL), lance-le via WSL
for %%F in ("%SCRIPT_DIR%main") do (
    if exist "%%~fF" (
        echo Executable Linux trouve : lancement via WSL
        for /f "usebackq delims=" %%i in (`wsl wslpath "%SCRIPT_DIR%" 2^>nul`) do set "WSL_DIR=%%i"
        if defined WSL_DIR (
            wsl bash -c "cd '%WSL_DIR%' && ./main"
            pause
            goto :end
        )
    )
)

REM Tenter la branche WSL (conversion du chemin)
for /f "usebackq delims=" %%i in (`wsl wslpath "%SCRIPT_DIR%" 2^>nul`) do set "WSL_DIR=%%i"
if defined WSL_DIR (
    echo WSL detecte. Compilation via WSL...
    wsl bash -c "cd '%WSL_DIR%' && make clean && make && ./main"
    if %ERRORLEVEL% EQU 0 goto :end
    pause
    echo Echec de la construction via WSL, tentative locale...
)

REM Branche locale : utilisation de make si present
pushd "%SCRIPT_DIR%"
where make >nul 2>&1
if %ERRORLEVEL% EQU 0 (
    echo make detecte localement. Lancement de make...
    make
    if %ERRORLEVEL% EQU 0 (
        if exist main.exe (
            echo Compilation reussie. Lancement...
                main.exe
                pause
            popd
            goto :end
        ) else (
            echo make a termine mais main.exe introuvable.
        )
    ) else (
        echo make a echoue localement.
    )
)

REM Si make absent ou a echoue, tenter g++ direct
g++ --version >nul 2>&1
if %ERRORLEVEL% EQU 0 (
    echo g++ detecte. Compilation manuelle en cours...
    REM Compilation explicite (ajuster si vous modifiez l'arborescence)
    g++ -Wall -Wextra -Werror -std=c++11 -I. -o main.exe ^
        main.cpp Player.cpp ResourceType.cpp ConditionType.cpp SaveManager.cpp GodMode.cpp InPlayArea.cpp Faction.cpp Game.cpp Turn.cpp Utils.cpp CardFactory.cpp ^
        Cards/Deck.cpp Cards/Hand.cpp Cards/DiscardPile.cpp Cards/Market.cpp ^
        CardsType/Card.cpp CardsType/ActionCard.cpp CardsType/ItemCard.cpp CardsType/ChampionCard.cpp ^
        Abilities/Ability.cpp Abilities/SacrificeAbility.cpp Abilities/AllyAbility.cpp Abilities/ActivateAbility.cpp Abilities/PrimaryAbility.cpp ^
        Effects/Effect.cpp Effects/GoldEffect.cpp Effects/AttackEffect.cpp Effects/HealEffect.cpp Effects/DrawEffect.cpp Effects/SacrificeEffect.cpp Effects/PrepareChampionEffect.cpp Effects/StunChampionEffect.cpp Effects/DiscardOpponentEffect.cpp Effects/ConditionalEffect.cpp Effects/ChoiceEffect.cpp Effects/DrawThenDiscardEffect.cpp Effects/PutNextCardOnTopEffect.cpp Effects/PutNextCardInHandEffect.cpp Effects/PutFromDiscardOnTopEffect.cpp Effects/PutChampionFromDiscardOnTopEffect.cpp Effects/OptionalSacrificeEffect.cpp

    if %ERRORLEVEL% EQU 0 (
        echo Compilation reussie. Lancement...
        main.exe
        pause
        popd
        goto :end
    ) else (
        echo Compilation via g++ a echoue.
    )
)

echo ERREUR : Impossible de compiler ou d'executer le projet.
echo Assurez-vous d'avoir WSL (avec make/g++) ou un compilateur g++/make Windows.
echo Pour distribuer a des non-developpeurs, fournissez l'executable precompile 'main.exe'.
pause
popd

:end
endlocal
