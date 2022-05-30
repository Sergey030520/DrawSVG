#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsPixmapItem>
#include <QScrollArea>
#include <QGraphicsView>
#include "GraphicScene.h"
#include "SvgRenderer.h"
#include "Map.h"
#include "../ui/ui_gui.h"
#include "MapJsonLoader.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void openBitMapFile();
    void openSVGFile();
    void loadMap();
    void saveMapSettings();
    void saveMap();
public slots:
    void loadNewSvgObjOnMap(QPoint point);
    void DrawResMap();
    void ChangeCursor(Qt::CursorShape);
private:
    QString pathFileBitMap, pathFileSVG;
    MapJsonLoader* mapJsonLoader;
    QPixmap imagePixmap;
    GraphicScene* scene;
    Map* map;
    QGraphicsPixmapItem* graphicsPixmapItem;
    void renderMap();
public:
    Ui::MainWindow* ui;
};
#endif // MAINWINDOW_H
