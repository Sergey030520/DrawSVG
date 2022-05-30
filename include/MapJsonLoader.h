//
// Created by Malip on 18.04.2022.
//

#ifndef DRAWSVG_MAPJSONLOADER_H
#define DRAWSVG_MAPJSONLOADER_H

#include <QJsonObject>
#include "SvgRenderer.h"
#include <QDir>

using namespace std;

class MapJsonLoader {
    QJsonObject object;
    QString pathMapImg;
    QVector<SvgRenderer*> objects;
    void loadMap();
    void loadObjects();
    /**
* Метод создаёт аболютный путь до файла
* @param relativePathString хранит относительный путь до файла
* @return возвращает абсолютный путь до файла
*/
    QString createAbsolutePath(QString* relativePathString);
    /**
* Метод создаёт относительный путь до файла
* @param absolutePathString хранит абсолютный путь до файла
* @return возвращает относительный путь до файла
*/
    QString createRelativePath(QString* absolutePathString);
public:
    MapJsonLoader() = default;
    MapJsonLoader(const QString* path);
    ~MapJsonLoader();
    QString getPathMap();
    bool isEmpty();
    /**
* Метод возращает список объектов считанный с конфигурационного файла
* @return возвращает подготовленный список SVG объектов
*/
    QVector<SvgRenderer*> getObjects();
    /**
* Метод создаёт файл конфигурации карты
* @param pathToJsonMap хранит путь до нрасположения нового конфигурационного файла,
     *pathToImgMap хранит путь растровой подложки,
     * objectsSvg хранит список SVG объектов
* @return возвращает подготовленный список с частотой слов
*/
    void save(QString* pathToJsonMap, QString* pathToImgMap, QVector<SvgRenderer*>* objectsSvg);
};


#endif //DRAWSVG_MAPJSONLOADER_H
