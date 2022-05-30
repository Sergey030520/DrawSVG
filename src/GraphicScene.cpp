#include "../include/GraphicScene.h"
#include "../include/mainwindow.h"
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include <iostream>

GraphicScene::GraphicScene(QObject* parent){
    setParent(parent);
}

void GraphicScene::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if(isSvgSettings){
        emit CallCheckClickOnSettings(event->scenePos().toPoint());
    }else if(!isAddNewObject){
        emit CallProvideFindObject(event->scenePos().toPoint());
    }
}

void GraphicScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    if(isSvgSettings) {
        if (isResizeObject) {
            emit CallResizeSvgObject(event->scenePos().toPoint());
        }else if(isMoveObject){
            emit CallMoveObject(event->scenePos().toPoint());
        }else {
            emit CallMouseOnSvgObj(event->scenePos().toPoint());
        }
    }
}

void GraphicScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    if(isAddNewObject){
        setStatusAddObject(false);
        emit CallLoadNewSvgObjOnMap(event->scenePos().toPoint());
    }else if(isResizeObject) {
        emit CallResizeSvgObject(event->scenePos().toPoint());
        setStatusResizeObject(false);
    }else if(isMoveObject){
        setStatusMoveObject(false);
    }
}

void GraphicScene::setStatusAddObject(bool status) {
    isAddNewObject = status;
}

void GraphicScene::setStatusSvgSettings(bool status) {
    isSvgSettings = status;
}

void GraphicScene::setStatusResizeObject(bool status) {
    isResizeObject = status;
}

void GraphicScene::setStatusMoveObject(bool status) {
    isMoveObject = status;
}

void GraphicScene::keyPressEvent(QKeyEvent *event) {
    int key = event->key();
    if((key == Qt::Key_Delete || key == Qt::Key_Backspace) && isSvgSettings){
        emit CallDeleteObject();
    }
}



