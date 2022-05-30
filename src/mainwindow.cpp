#include "../include/mainwindow.h"
#include <QFileDialog>
#include <QApplication>
#include <QGraphicsView>
#include <iostream>


MainWindow::MainWindow(QWidget *parent){
    setParent(parent);
    ui = new Ui::MainWindow();
    ui->setupUi(this);

    map = new Map();
    scene = new GraphicScene(new QGraphicsScene);
    graphicsPixmapItem = new QGraphicsPixmapItem();
    scene->addItem(graphicsPixmapItem);
    ui->scrollArea->setWidget(new QGraphicsView(scene));
    connect(ui->btnLoadRasterMap, &QPushButton::clicked, this, &MainWindow::openBitMapFile);//загрузка основы для карты
    connect(ui->btnAddObject, &QPushButton::clicked, this, &MainWindow::openSVGFile);//загрузка объекта svg
    connect(ui->btnLoadMapObjs, &QPushButton::clicked, this, &MainWindow::loadMap);//загрузка карты с объектами
    connect(ui->btnSaveMapObjs, &QPushButton::clicked, this, &MainWindow::saveMapSettings);//сохранение карты с настройками
    connect(ui->btnSaveMap, &QPushButton::clicked, this, &MainWindow::saveMap);//сохранение карты

    connect(scene, &GraphicScene::CallLoadNewSvgObjOnMap, this, &MainWindow::loadNewSvgObjOnMap);//загрузка нового объекта на карту
    connect(map, &Map::CallDrawResMap, this, &MainWindow::DrawResMap);//отрисовка карты
    connect(map, &Map::CallChangeCursorView, this, &MainWindow::ChangeCursor);//изменение вида курсора

    connect(scene, &GraphicScene::CallProvideFindObject, map, &Map::ProvideFindObject);//поиск объекта на который производился клик
    connect(map, &Map::CallSetStatusSvgSettings, scene, &GraphicScene::setStatusSvgSettings);//установка флага настройки объекта

    connect(scene, &GraphicScene::CallCheckClickOnSettings, map, &Map::CheckMousePressSettings);/*проверка нажатия на рамку*/
    connect(map, &Map::CallSetStatusResizeSvgObj, scene, &GraphicScene::setStatusResizeObject);/*результат проверки нажатия*/
    connect(scene, &GraphicScene::CallResizeSvgObject, map, &Map::ResizeSvgObj);/*генерация изменения размера*/

    connect(map, &Map::CallSetStatusMoveObject, scene, &GraphicScene::setStatusMoveObject);//установка статуса переноса объекта
    connect(scene, &GraphicScene::CallMoveObject, map, &Map::MoveObject);//передвижение объекта

    connect(scene, &GraphicScene::CallMouseOnSvgObj, map, &Map::CheckMouseHoverOverCustomObject);//проверка на покрытие области объекта мышкой
    connect(scene, &GraphicScene::CallDeleteObject, map, &Map::DeleteSvgObject);//удаление элемента
}

MainWindow::~MainWindow()
{
    delete graphicsPixmapItem, scene, ui, map;
}

void MainWindow::openBitMapFile() {
    pathFileBitMap = QFileDialog::getOpenFileName(this,
                                                  "Выберите растровую карту",
                                                  QApplication::applicationDirPath(),
                                                  "Bitmap (*.JPG *.jpg *.JPEG *.png *.BMP)");
    if(!pathFileBitMap.isEmpty()) {
        mapJsonLoader = new MapJsonLoader();
        renderMap();
    }
}

void MainWindow::openSVGFile() {
    pathFileSVG = QFileDialog::getOpenFileName(this,
                                               "Выберите svg объект",
                                               QApplication::applicationDirPath(),
                                               "SVG (*.svg)");
    if(!pathFileSVG.isEmpty()){
        scene->setStatusAddObject(true);
        graphicsPixmapItem->setCursor(QCursor(Qt::CrossCursor));
    }
}

void MainWindow::loadNewSvgObjOnMap(QPoint point) {
    if(!imagePixmap.isNull() && !pathFileSVG.isEmpty()) {
        map->addSvgObject(new SvgRenderer(pathFileSVG, &point));
    }
}

void MainWindow::loadMap() {
    QString path = QFileDialog::getOpenFileName(this,
                                                "Выберите готовую карту",
                                                QApplication::applicationDirPath(),
                                                "Map (*.json)");
    if (!path.isEmpty()){
        mapJsonLoader = new MapJsonLoader(&path);
        if(!mapJsonLoader->isEmpty()){
            pathFileBitMap = mapJsonLoader->getPathMap();
            renderMap();
            map->loadSvgObjects(mapJsonLoader->getObjects());
        }
    }
}

void MainWindow::saveMapSettings() {
    QString path = QFileDialog::getSaveFileName(this,
                                                "Выберите место для сохранения карты",
                                                QApplication::applicationDirPath(),
                                                "Map (*.json)");
    if (!path.isEmpty()) {
        mapJsonLoader->save(&path, &pathFileBitMap, map->getSvgObjects());
    }
}

void MainWindow::saveMap() {
    QString format("");
    QString path = QFileDialog::getSaveFileName(this,
                                                "Выберите место для сохранения карты",
                                                QApplication::applicationDirPath(),
                                                "*.JPG ;; *.jpg ;; *.JPEG ;; *.png ;; *.BMP",
                                                &format);
    cout << format.toStdString() << "\n" << path.toStdString() << endl;
    if (!path.isEmpty() && !imagePixmap.isNull() && !format.isEmpty()) {
        QFile file(path + format);
        file.open(QIODevice::WriteOnly);
        if(format.contains("JPG")){
            map->rasterization(imagePixmap).save(path, "JPG");
        }else if(format.contains("jpg")){
            map->rasterization(imagePixmap).save(path, "jpg");
        }else if(format.contains("JPEG")){
            map->rasterization(imagePixmap).save(path, "JPEG");
        }else if(format.contains("png")){
            map->rasterization(imagePixmap).save(path, "png");
        }else if(format.contains("BMP")){
            map->rasterization(imagePixmap).save(path, "BMP");
        }
    }
}

void MainWindow::DrawResMap() {
    graphicsPixmapItem->setPixmap(map->rasterization(imagePixmap));
    update();
}

void MainWindow::ChangeCursor(Qt::CursorShape type){
    graphicsPixmapItem->setCursor(QCursor(type));
}

void MainWindow::renderMap() {
    map->clearSvgObjects();
    QImage imageBitMap(pathFileBitMap);
    imagePixmap = QPixmap(QPixmap::fromImage(imageBitMap));
    graphicsPixmapItem->setPixmap(imagePixmap);
}


