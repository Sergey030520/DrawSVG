#ifndef DRAWSVG_GRAPHICSCENE_H
#define DRAWSVG_GRAPHICSCENE_H


#include <QGraphicsScene>
#include <QPoint>

class GraphicScene : public QGraphicsScene{
    Q_OBJECT
private:
    bool isAddNewObject = false;
    bool isSvgSettings = false;
    bool isResizeObject = false;
    bool isMoveObject = false;
public:
    GraphicScene(QObject* parent = nullptr);
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void keyPressEvent(QKeyEvent* event) override;
    /**
* Метод включает режим добавления объекта
* @param status устанавливает новый статус
*/
    void setStatusAddObject(bool status = true);
public slots:
    /**
* Метод включает и выключает режим настройки объекта SVG
* @param status устанавливает новый статус
*/
    void setStatusSvgSettings(bool status);
    /**
* Метод определяет количество вхождений слова word в загруженной базе
документов
* @param word слово, частоту вхождений которого необходимо определить
* @return возвращает подготовленный список с частотой слов
*/
    void setStatusResizeObject(bool status);
    /**
* Метод определяет количество вхождений слова word в загруженной базе
документов
* @param word слово, частоту вхождений которого необходимо определить
* @return возвращает подготовленный список с частотой слов
*/
    void setStatusMoveObject(bool status);
signals:
    /**
* Методы-сигналы производят вызов подлючённых слотов в классе mainwindow
* @param point координаты нажатия мышки на карте
*/
    void CallLoadNewSvgObjOnMap(QPoint);
    void CallProvideFindObject(QPoint);
    void CallResizeSvgObject(QPoint);
    void CallCheckClickOnSettings(QPoint);
    void CallMouseOnSvgObj(QPoint);
    void CallMoveObject(QPoint);
    void CallDeleteObject();
};


#endif //DRAWSVG_GRAPHICSCENE_H
