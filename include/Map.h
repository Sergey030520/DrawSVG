//
// Created by Malip on 01.03.2022.
//

#ifndef DRAWSVG_MAP_H
#define DRAWSVG_MAP_H

#include "SvgRenderer.h"
#include "QPixmap"
#include "MapJsonLoader.h"
#include <QPainter>

enum mouse_location {OUTSIDE,VERTICAL_BORDER_TOP, VERTICAL_BORDER_BOTTOM, HORIZONTAL_BORDER_LEFT,
        HORIZONTAL_BORDER_RIGHT, B_DIAG_LEFT_BOTTOM, B_DIAG_RIGHT_TOP,
        F_DIAG_RIGHT_BOTTOM, F_DIAG_LEFT_TOP};


class Map : public QObject{
Q_OBJECT
private:
    QVector<SvgRenderer*> svgObjects;
    SvgRenderer* currentSvgObj = nullptr;
    /**
* Методы определяют по переданному местоположению, где относительно квадрата настройек находится мышь
* @param word слово, частоту вхождений которого необходимо определить
* @return
*/
    mouse_location CheckingPointObjAngle(QPoint point);
    mouse_location CheckingPointObjBorder(QPoint point);
    mouse_location mouse_direct = mouse_location::OUTSIDE;

    bool CheckFDiag(mouse_location);
    bool CheckBDiag(mouse_location);
    bool CheckVert(mouse_location);
    bool CheckHor(mouse_location);
public:
    Map() = default;
    ~Map();
    /**
* Метод загружает SVG объект
* @param inSvgObjects хранит
* @return возвращает подготовленный список с частотой слов
*/
    void loadSvgObjects(QVector<SvgRenderer*> inSvgObjects);
    /**
* Метод отрисовывает настройки для выбранного SVG объекта
* @param painter хранит готовую карту и производит отрисовку квадрата
*/
    void drawSettingsSvgObject(QPainter* painter);
    /**
* Метод производит растеризацию SVG объектов на растровой подложке
* @param pixmap хранит растровую подложку
* @return готовую карту с объектами
*/
    QPixmap rasterization(QPixmap pixmap);
    /**
 * Метод добавляет новый SVG объект в список
 * @param objSvg хранит указатель на созданный SVG объект
 * @return возвращает подготовленный список с частотой слов
 */
    void addSvgObject(SvgRenderer* objSvg);
    /**
 * Метод очищает список SVG объектов
 */
    void clearSvgObjects();
    /**
 * Методы изменяют размер SVG объекта
 * @param point хранит местоположение с помощью, которого расчитывается новый размер объекта
 * @return возвращает подготовленный список с частотой слов
 */
    void ResizeDiagSvgObj(QPoint point);
    void ResizeHorAndVerSvgObj(QPoint point);
    /**
* Метод возращает SVG объекты
* @return возвращает подготовленный список объектов SVG
*/
    QVector<SvgRenderer*> *getSvgObjects();

public slots:
    void ProvideFindObject(QPoint pointClick);
    void CheckMouseHoverOverCustomObject(QPoint point);
    void ResizeSvgObj(QPoint point);
    void CheckMousePressSettings(QPoint point);
    void MoveObject(QPoint point);
    void DeleteSvgObject();
signals:
    void CallDrawResMap();
    void CallChangeCursorView(Qt::CursorShape);
    void CallSetStatusSvgSettings(bool);
    void CallSetStatusResizeSvgObj(bool);
    void CallSetStatusMoveObject(bool);
};


#endif //DRAWSVG_MAP_H
