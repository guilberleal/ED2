@echo off
echo.
echo Executando o algoritmo de geracao de entradas.
echo.

mkdir entradas

Copy Gerador_entradas.exe entradas

cd C:\Users\unknow alone\Dropbox\Faculdade\Estrutura de Dados 2\Trabalho 4\entradas
for /l %%i in ( 1, 1, 200 ) do (
Gerador_entradas.exe 100000 %%i.txt
) 

echo.
echo Finalizando a criacao de entradas
echo.

echo Programa finalizado.
echo.
pause