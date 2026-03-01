Требования:
- CMake
- Компилятор C: MSVC (Build Tools / Visual Studio)

Сборка

1. Установите Build Tools for Visual Studio (https://visualstudio.microsoft.com/ru/visual-cpp-build-tools/)

2. Откройте Developer Command Prompt for VS или x64 Native Tools Command Prompt из меню Пуск.

3. Выполните:

cd ..\kotlin-novator\build
cmake ..
cmake --build .

4. Исполняемый файл появится в build\nuke.exe

Запуск

Запускайте программу из корня проекта kotlin-novator, чтобы файл с координатами искался в текущей папке:

cd ..\kotlin-novator

build\nuke.exe coords.txt 10

Параметры:
- первый - путь к файлу с координатами целей (каждая строка: "x,y");
- второй - радиус поражения (целое число).

Вывод:
- первая строка - координаты точки запуска "x,y";
- вторая строка - количество поражённых целей.
