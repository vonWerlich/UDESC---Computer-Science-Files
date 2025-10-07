@echo off
setlocal enabledelayedexpansion

set count=0

:: Parâmetros
set crossover_types=UNIFORM TWO_POINT ONE_POINT
set pc_rates=0.90 0.85 0.80 0.75 0.70
set pm_rates=0.005 0.01 0.02 0.03
set elitism_options=1 0
set k_values=2 3 5

echo Por favor, aguarde. Gerando todas as combinacoes reais...

:: --- TOURNAMENT ---
for %%B in (%crossover_types%) do (
    for %%C in (%pc_rates%) do (
        for %%D in (%pm_rates%) do (
            for %%E in (%elitism_options%) do (
                for %%F in (%k_values%) do (
                    call :create_tournament %%B %%C %%D %%E %%F
                )
            )
        )
    )
)

:: --- ROULETTE ---
for %%A in (ROULETTE_WOR ROULETTE_WR) do (
    for %%B in (%crossover_types%) do (
        for %%C in (%pc_rates%) do (
            for %%D in (%pm_rates%) do (
                for %%E in (%elitism_options%) do (
                    call :create_roulette %%A %%B %%C %%D %%E
                )
            )
        )
    )
)

echo.
echo !count! arquivos .ini foram criados com sucesso!
pause
exit /b

:create_tournament
set /a count+=1
set "filename=config!count!.ini"
echo # Teste !count!: TOURNAMENT(K=%5) ^| %1 ^| PC %2 ^| PM %3 ^| Elitism %4 > "!filename!"
(
echo COD = BIN
echo RUN = 10
echo GEN = 2000
echo POP = 30
echo DIM = 100
echo ELITISM = %4
echo SELECTION_METHOD = TOURNAMENT
echo TOURNAMENT_K = %5
echo TOURNAMENT_KP = 0.95
echo BIN_CROSSOVER = %1
echo PC = %2
echo PM = %3
) >> "!filename!"
exit /b

:create_roulette
set /a count+=1
set "filename=config!count!.ini"
echo # Teste !count!: %1 ^| %2 ^| PC %3 ^| PM %4 ^| Elitism %5 > "!filename!"
(
echo COD = BIN
echo RUN = 10
echo GEN = 2000
echo POP = 30
echo DIM = 100
echo ELITISM = %5
echo SELECTION_METHOD = %1
echo BIN_CROSSOVER = %2
echo PC = %3
echo PM = %4
) >> "!filename!"
exit /b
