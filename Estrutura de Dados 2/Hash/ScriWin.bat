@echo off
echo.
echo Executando o algoritmo de geracao de entradas.
echo.

mkdir entradas_3020_par
mkdir entradas_3050_par
mkdir entradas_3080_par

mkdir entradas_3020_rando
mkdir entradas_3050_rando
mkdir entradas_3080_rando

Copy entradas.exe entradas_3020_par
Copy entradas.exe entradas_3050_par
Copy entradas.exe entradas_3080_par

Copy entradas.exe entradas_3020_rando
Copy entradas.exe entradas_3050_rando
Copy entradas.exe entradas_3080_rando

Copy Etapa2e3.exe entradas_3020_par
Copy Etapa2e3.exe entradas_3050_par
Copy Etapa2e3.exe entradas_3080_par

Copy Etapa2e3.exe entradas_3020_rando
Copy Etapa2e3.exe entradas_3050_rando
Copy Etapa2e3.exe entradas_3080_rando

cd C:\Users\unknow alone\Dropbox\Entradas\entradas_3020_par
set i = 0;
for /l %%i in ( 1, 1, 30 ) do (
entradas.exe 20 %%i.txt 1
) 

cd C:\Users\unknow alone\Dropbox\Entradas\entradas_3050_par
set i = 0;
for /l %%i in ( 1, 1, 30 ) do (
entradas.exe 50 %%i.txt 1
) 

cd C:\Users\unknow alone\Dropbox\Entradas\entradas_3080_par
set i = 0;
for /l %%i in ( 1, 1, 30 ) do (
entradas.exe 50 %%i.txt 1
) 

cd C:\Users\unknow alone\Dropbox\Entradas\entradas_3020_rando 
set i = 0;
for /l %%i in ( 1, 1, 30 ) do (
entradas.exe 20 %%i.txt 2
) 

cd C:\Users\unknow alone\Dropbox\Entradas\entradas_3050_rando 
set i = 0;
for /l %%i in ( 1, 1, 30 ) do (
entradas.exe 50 %%i.txt 2
) 

cd C:\Users\unknow alone\Dropbox\Entradas\entradas_3080_rando 
set i = 0;
for /l %%i in ( 1, 1, 30 ) do (
entradas.exe 50 %%i.txt 2
) 

echo.
echo Finalizando a criacao de entradas
echo.

echo.
echo Inicializando execucao do algoritmo Etapa2e3
echo.

cd C:\Users\unknow alone\Dropbox\Entradas\entradas_3020_par
set i = 0;
for /l %%i in ( 1, 1, 30) do (
Etapa2e3.exe %%i.txt
) 

cd C:\Users\unknow alone\Dropbox\Entradas\entradas_3020_rando
set i = 0;
for /l %%i in ( 1, 1, 30 ) do (
Etapa2e3.exe %%i.txt
) 

cd C:\Users\unknow alone\Dropbox\Entradas\entradas_3050_par
set i = 0;
for /l %%i in ( 1, 1, 30 ) do (
Etapa2e3.exe %%i.txt
) 

cd C:\Users\unknow alone\Dropbox\Entradas\entradas_3050_rando
set i = 0;
for /l %%i in ( 1, 1, 30 ) do (
Etapa2e3.exe %%i.txt
) 

cd C:\Users\unknow alone\Dropbox\Entradas\entradas_3080_par
set i = 0;
for /l %%i in ( 1, 1, 30 ) do (
Etapa2e3.exe %%i.txt
) 

cd C:\Users\unknow alone\Dropbox\Entradas\entradas_3080_rando
set i = 0;
for /l %%i in ( 1, 1, 30 ) do (
Etapa2e3.exe %%i.txt
) 

echo.
echo Finalizando execucao do algoritmo Etapa2e3
echo.

echo Programa finalizado.
echo.
pause