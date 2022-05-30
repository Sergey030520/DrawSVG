//
// Created by Malip on 01.03.2022.
//

#include <QFile>
#include "../include/SvgRenderer.h"
#include <QDir>
#include "iostream"

SvgRenderer::SvgRenderer(const QString& path, QPoint* newPos): id((int)++counterId), pathToImgSvg(path) {
    load(path);
    objectRect = new QRect(QPoint(newPos->x() - defaultSize().width() / 2,
                                newPos->y() - defaultSize().height() / 2),defaultSize());
}

SvgRenderer::SvgRenderer(const QString &path, QRect* rect) : id((int)++counterId), pathToImgSvg(path) {
    load(path);
    objectRect = rect;
}

int SvgRenderer::counterId = -1;


QRect* SvgRenderer::getObjectRect(){
    return objectRect;
}

QRect *SvgRenderer::getRightBottomAngle() {
    return new QRect(objectRect->right() - corrector_border, objectRect->bottom() - corrector_border,
                     corrector_border*2, corrector_border*2);
}

QRect *SvgRenderer::getLeftBorder() {
    return new QRect(objectRect->left() - corrector_border, objectRect->top() + corrector_border,
                     corrector_border*2, objectRect->height()-(corrector_border*2));
}

QRect *SvgRenderer::getRightBorder() {
    return new QRect(objectRect->right() - corrector_border, objectRect->top() + corrector_border,
                     corrector_border*2, objectRect->height()-(corrector_border*2));
}

QRect *SvgRenderer::getTopBorder() {
    return new QRect(objectRect->left() + corrector_border, objectRect->top() - corrector_border,
                     objectRect->width() - (corrector_border*2), corrector_border*2);
}

QRect *SvgRenderer::getBottomBorder() {
    return new QRect(objectRect->left() + corrector_border, objectRect->bottom() - corrector_border,
                     objectRect->width() - (corrector_border*2), corrector_border*2);
}

QRect *SvgRenderer::getLeftTopAngle() {
    return new QRect(objectRect->left() - corrector_border, objectRect->top() - corrector_border,
                     corrector_border*2, corrector_border*2);
}

QRect *SvgRenderer::getRightTopAngle() {
    return new QRect(objectRect->right() - corrector_border, objectRect->top() - corrector_border,
                     corrector_border*2, corrector_border*2);
}

QRect *SvgRenderer::getLeftBottomAngle() {
    return new QRect(objectRect->left() - corrector_border, objectRect->bottom() - corrector_border,
                     corrector_border*2, corrector_border*2);
}

QRect* SvgRenderer::getCentralRect() {
    return new QRect(objectRect->left() + corrector_border, objectRect->top() + corrector_border,
                 abs(objectRect->width() - (corrector_border * 2)), objectRect->height() - (corrector_border*2));
}

int SvgRenderer::getId() {
    return id;
}

SvgRenderer::~SvgRenderer() {
    --counterId;
}

QJsonObject *SvgRenderer::getJsonObject() {
    QJsonObject* jsonObject = new QJsonObject();
    jsonObject->insert("path", createRelativePath(new QString(pathToImgSvg)));
    jsonObject->insert("x", QJsonValue::fromVariant(objectRect->x()));
    jsonObject->insert("y", QJsonValue::fromVariant(objectRect->y()));
    jsonObject->insert("width", QJsonValue::fromVariant(objectRect->width()));
    jsonObject->insert("height", QJsonValue::fromVariant(objectRect->height()));
    return jsonObject;
}

QString SvgRenderer::createRelativePath(QString *absolutePathString) {
    QDir dir(*absolutePathString);
    dir.cdUp();
    return "/" + dir.dirName() + "/" + QDir(*absolutePathString).dirName();
}



