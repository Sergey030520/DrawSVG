//
// Created by Malip on 01.03.2022.
//

#ifndef DRAWSVG_SVGRENDERER_H
#define DRAWSVG_SVGRENDERER_H

#include <QSvgRenderer>
#include <QJsonObject>

class SvgRenderer : public QSvgRenderer{
    static int counterId;
    int id;
    QString pathToImgSvg;
    int corrector_border = 10;
    QRect* objectRect;
    QString createRelativePath(QString *absolutePathString);
public:
    SvgRenderer(const QString& path, QPoint* newPos);
    SvgRenderer(const QString& path, QRect* rect);
    ~SvgRenderer() override;
    int getId();
    /**
* Методы возвращают определённый QRect подделённого на квадраты объекта SVG
* @return возвращают QRect
*/
    QRect* getObjectRect();
    QRect* getLeftBorder();
    QRect* getRightBorder();
    QRect* getTopBorder();
    QRect* getBottomBorder();
    QRect* getLeftTopAngle();
    QRect* getRightTopAngle();
    QRect* getLeftBottomAngle();
    QRect* getRightBottomAngle();
    QRect* getCentralRect();
    /**
* Метод возвращает информацию об объекте
* @return возвращает объект Json
*/
    QJsonObject* getJsonObject();
};


#endif //DRAWSVG_SVGRENDERER_H
