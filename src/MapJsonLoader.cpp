//
// Created by Malip on 18.04.2022.
//

#include "../include/MapJsonLoader.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <iostream>
#include <QCoreApplication>

MapJsonLoader::MapJsonLoader(const QString *path) {
    QFile file(*path);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    object = QJsonDocument::fromJson(QString(file.readAll()).toUtf8()).object();
    file.close();
    loadMap();
    loadObjects();
}

QVector<SvgRenderer*> MapJsonLoader::getObjects() {
    return objects;
}

void MapJsonLoader::loadMap() {
    if(!object["map"].isNull() && object["map"].isObject()){
        pathMapImg = createAbsolutePath(new QString(object["map"].toObject()["path"].toString()));
    }
}

void MapJsonLoader::loadObjects() {
    if(!object["objects"].isNull() && object["objects"].isArray()) {
        QJsonArray jsonArray = object["objects"].toArray();
        for (const QJsonValue &value: jsonArray) {
            if (value.isObject()) {
                auto obj = value.toObject();
                QFile file(createAbsolutePath(new QString(obj["path"].toString())));
                if (file.exists()) {
                    objects.push_back(new SvgRenderer(createAbsolutePath(
                                                              new QString(obj["path"].toString())),
                                                      new QRect(
                                                              QPoint((!obj["x"].isNull() ? obj["x"].toInt() : 0),
                                                                     (!obj["y"].isNull() ? obj["y"].toInt() : 0)),
                                                              QSize(
                                                                      (!obj["width"].isNull() ? obj["width"].toInt()
                                                                                              : 0),
                                                                      (!obj["height"].isNull() ? obj["height"].toInt()
                                                                                               : 0)
                                                              ))));
                }
            }
        }
    }
}

QString MapJsonLoader::getPathMap() {
    return pathMapImg;
}

bool MapJsonLoader::isEmpty() {
    return pathMapImg.isEmpty();
}

void MapJsonLoader::save(QString* pathToJsonMap, QString* pathToImgMap, QVector<SvgRenderer*>* objectsSvg) {
    QJsonObject objJson, mapObject;

    mapObject.insert("path", createRelativePath(pathToImgMap));
    objJson.insert("map", mapObject);

    QJsonArray jsonArrayObjects;
    for (SvgRenderer *obj : *objectsSvg) {
        jsonArrayObjects.push_back(*obj->getJsonObject());
    }
    objJson.insert("objects", jsonArrayObjects);

    QJsonDocument doc(objJson);

    QFile file(*pathToJsonMap);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream stream(&file);
    stream << doc.toJson(QJsonDocument::Indented);
    file.flush();
    file.close();
}

QString MapJsonLoader::createAbsolutePath(QString* relativePathString) {
    QDir absolutePathDir(QCoreApplication::applicationDirPath());
    absolutePathDir.cd("../../");
    absolutePathDir = QDir(absolutePathDir.absolutePath() + relativePathString);
    return absolutePathDir.absolutePath();
}

QString MapJsonLoader::createRelativePath(QString *absolutePathString) {
    QDir dir(*absolutePathString);
    dir.cdUp();
    return "/" + dir.dirName() + "/" + QDir(*absolutePathString).dirName();
}




