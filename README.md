<h1 align="center">Hi 👋, I'm Sergey Makarov</h1>
<p align="left"> <img src="https://komarev.com/ghpvc/?username=sergey030520&label=Profile%20views&color=0e75b6&style=flat" alt="sergey030520" /> </p>

<p align="left"> <a href="https://github.com/ryo-ma/github-profile-trophy"><img src="https://github-profile-trophy.vercel.app/?username=sergey030520" alt="sergey030520" /></a> </p>

- 🔭 I’m currently working on [DrawSVG](https://github.com/Sergey030520/DrawSVG)

- 👨‍💻 All of my projects are available at [https://github.com/Sergey030520](https://github.com/Sergey030520)

<h3 align="left">Connect with me:</h3>
<p align="left">
</p>

<h3 align="left">Languages and Tools:</h3>
<p align="left"> 
<a href="https://www.w3schools.com/cpp/" target="_blank" rel="noreferrer"> <img src="https://raw.githubusercontent.com/devicons/devicon/master/icons/cplusplus/cplusplus-original.svg" alt="cplusplus" width="40" height="40"/> </a> 
<a href="https://git-scm.com/" target="_blank" rel="noreferrer"> <img src="https://www.vectorlogo.zone/logos/git-scm/git-scm-icon.svg" alt="git" width="40" height="40"/> </a>
<a href="https://www.qt.io/" target="_blank" rel="noreferrer"> <img src="https://upload.wikimedia.org/wikipedia/commons/0/0b/Qt_logo_2016.svg" alt="qt" width="40" height="40"/> </a>
<a href="https://cmake.org/" rel="noreferrer"><img src="https://www.vectorlogo.zone/logos/cmake/cmake-icon.svg" alt="Cmake" width="40" height="40"/></a>
</p>

# DrawSVG

## Описание

Разработанная программа позволяет растеризовывать условные знаки в векторном формате SVG на электронных картах ГИС "Горизонт". Пргограмма имеет следующую функциональность:
1. загрузка растровой подложки;
2. загрузка карты конфигурационного файла с условными знаками;
3. добавление условного знака на электронную карту;
4. сохранение готовой карты с условными знаками в растровом формате (JPEG, PNG, BMP);
5. создание конфигурационного файла карты с условными знаками в формате JSON с последующим сохранением на компьютере;
6. изменение размера и перемещение условных знаков на растровой подложке.

## Инструкция по подключению библиотек

В проекте уже сгенированны два файла конфигурации [CMakeLists.txt](https://github.com/Sergey030520/DrawSVG/blob/4a86d1db5301a9ea4958864bc5388e7e0ff71ed8/CMakeLists.txt) (Производит поиск библиотек Qt5, устанавливает глобальные переменные и подключает папку src с файлами классов программы) и [CMakeLists.txt](https://github.com/Sergey030520/DrawSVG/blob/4a86d1db5301a9ea4958864bc5388e7e0ff71ed8/src/CMakeLists.txt) (Подключает библиотеку Qt5 и производит допонительну настройку проекта).

## Инструкция по сборке

Сборка проекта производится с помощью инструмента [CMake](https://cmake.org/). В терминале компьютера необходимо прописать следующие команды: 

```
cmake --build . --config Release --target main
```
## Интерфейс приложения
Проектирование и создание графического интерфейса приложения реализовано с помощью инструмента Qt Designer. Интерфейс главного окна представлен в файле [gui.ui](ui/gui.ui). Основное окно приложения состоит из графической сцены и 5 кнопок:
+ кнопки загрузки растрового изображения карты;
+ кнопки загрузки карты с объектами и их настройками;
+ кнопки добавления объектов;
+ кнопки сохранения карты с объектами и их настройками;
+ кнопки сохранения карты в растровом формате.

Компоновка графических элементов реализована с помощью классов "QHorizontalLayout" и "QVerticalLayout".
![Application DrawSVG](Image/Application_DrawSVG.jpg)

## Пример создания готовой растровой карты с условными знаками
В начале необходимо выбрать растровую подложку. В качетсве примера была взята [карта Ялты](Image/Map.bmp)
Затем необходимо выбрать условный знак в формате SVG. В качестве примера был разработан условный знак ["Якорь"](Image/anchors.svg)
После того как был выбран условный знак, необходимо выбрать на карте место нажав мышью в выбранном месте и затем будет произведена растеризация данного УЗ на карте.
![Map result](Image/map_26_04_2022_11_42.BMP)

## Пример конфигурационного файла

![Map configuration](Image/map_configuration.jpg)
