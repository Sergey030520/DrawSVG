//
// Created by Malip on 01.03.2022.
//

#include "../include/Map.h"
#include <QPainter>
#include <utility>


Map::~Map(){
    for (auto val : svgObjects) {
        delete val;
        val = nullptr;
    }
    delete currentSvgObj;
}

void Map::loadSvgObjects(QVector<SvgRenderer *> inSvgObjects) {
    svgObjects = inSvgObjects;
    emit CallDrawResMap();
    emit CallChangeCursorView(Qt::ArrowCursor);
}

void Map::addSvgObject(SvgRenderer *objSvg) {
    svgObjects.push_back(objSvg);
    emit CallDrawResMap();
    emit CallChangeCursorView(Qt::ArrowCursor);
}


QPixmap Map::rasterization(QPixmap pixmap) {
    QPainter painter(&pixmap);
    for (auto & objSvg : svgObjects) {
        objSvg->render(&painter, *objSvg->getObjectRect());
    }
    if(currentSvgObj != nullptr){
        drawSettingsSvgObject(&painter);
    }
    return pixmap;
}

void Map::drawSettingsSvgObject(QPainter* painter) {
    QPen pen(Qt::DashDotDotLine);
    pen.setWidth(2);
    pen.setColor(QColor(Qt::black));
    painter->setPen(pen);
    painter->drawRect(*currentSvgObj->getObjectRect());
}

void Map::ProvideFindObject(QPoint pointClick) {
    currentSvgObj = nullptr;
    for (auto svgObj : svgObjects) {
        if (svgObj->getObjectRect()->contains(pointClick.x(), pointClick.y())) {
            currentSvgObj =  svgObj;
            break;
        }
    }
    emit CallDrawResMap();
    emit CallSetStatusSvgSettings(currentSvgObj != nullptr);
}

void Map::clearSvgObjects() {
    if(!svgObjects.isEmpty()) svgObjects.clear();
}
mouse_location Map::CheckingPointObjAngle(QPoint point){
    if(currentSvgObj->getLeftTopAngle()->contains(point.x(), point.y())){
        return mouse_location::F_DIAG_LEFT_TOP;
    }else if(currentSvgObj->getLeftBottomAngle()->contains(point.x(), point.y())){
        return mouse_location::B_DIAG_LEFT_BOTTOM;
    }else if(currentSvgObj->getRightTopAngle()->contains(point.x(), point.y())){
        return mouse_location::B_DIAG_RIGHT_TOP;
    }else if(currentSvgObj->getRightBottomAngle()->contains(point.x(), point.y())){
        return mouse_location::F_DIAG_RIGHT_BOTTOM;
    }
    return mouse_location::OUTSIDE;
}

mouse_location Map::CheckingPointObjBorder(QPoint point) {
    if(currentSvgObj->getTopBorder()->contains(point.x(), point.y())){
        return mouse_location::VERTICAL_BORDER_TOP;
    }else if(currentSvgObj->getBottomBorder()->contains(point.x(), point.y())){
        return mouse_location::VERTICAL_BORDER_BOTTOM;
    }else if(currentSvgObj->getLeftBorder()->contains(point.x(), point.y())){
        return mouse_location::HORIZONTAL_BORDER_LEFT;
    }else if(currentSvgObj->getRightBorder()->contains(point.x(), point.y())){
        return mouse_location::HORIZONTAL_BORDER_RIGHT;
    }
    return mouse_location::OUTSIDE;
}

void Map::CheckMouseHoverOverCustomObject(QPoint point) {
    if(currentSvgObj->getCentralRect()->contains(point.x(), point.y())){
        emit CallChangeCursorView(Qt::OpenHandCursor);
    }else {
        mouse_direct = CheckingPointObjAngle(point);
        if (CheckFDiag(mouse_direct)) emit CallChangeCursorView(Qt::SizeFDiagCursor);
        else if (CheckBDiag(mouse_direct)) emit CallChangeCursorView(Qt::SizeBDiagCursor);
        else {
            mouse_direct = CheckingPointObjBorder(point);
            if (CheckHor(mouse_direct)) emit CallChangeCursorView(Qt::SizeHorCursor);
            else if (CheckVert(mouse_direct)) emit CallChangeCursorView(Qt::SizeVerCursor);
            else emit CallChangeCursorView(Qt::ArrowCursor);
        }
    }
}
void Map::ResizeSvgObj(QPoint point) {
    if(CheckFDiag(mouse_direct) || CheckBDiag(mouse_direct)) {
        ResizeDiagSvgObj(point);
    }else if(CheckVert(mouse_direct) || CheckHor(mouse_direct)){
        ResizeHorAndVerSvgObj(point);
    }
    emit CallDrawResMap();
}
void Map::ResizeHorAndVerSvgObj(QPoint point) {
    switch (mouse_direct) {
        case VERTICAL_BORDER_TOP:
            currentSvgObj->getObjectRect()->setTop(point.y());
            break;
        case VERTICAL_BORDER_BOTTOM:
            currentSvgObj->getObjectRect()->setBottom(point.y());
            break;
        case HORIZONTAL_BORDER_LEFT:
            currentSvgObj->getObjectRect()->setLeft(point.x());
            break;
        case HORIZONTAL_BORDER_RIGHT:
            currentSvgObj->getObjectRect()->setRight(point.x());
            break;
        default: break;
    }
}

void Map::ResizeDiagSvgObj(QPoint point){
    if(mouse_direct == B_DIAG_LEFT_BOTTOM && point.x() < currentSvgObj->getObjectRect()->right() &&
      point.y() > currentSvgObj->getObjectRect()->top()){
        currentSvgObj->getObjectRect()->setBottomLeft(point);
    }else if(mouse_direct == B_DIAG_RIGHT_TOP && point.x() > currentSvgObj->getObjectRect()->left() &&
             point.y() < currentSvgObj->getObjectRect()->bottom()){
        currentSvgObj->getObjectRect()->setTopRight(point);
    }else if(mouse_direct == F_DIAG_RIGHT_BOTTOM && point.x() > currentSvgObj->getObjectRect()->left() &&
             point.y() > currentSvgObj->getObjectRect()->top()){
        currentSvgObj->getObjectRect()->setBottomRight(point);
    }else if(mouse_direct == F_DIAG_LEFT_TOP && point.x() < currentSvgObj->getObjectRect()->right() &&
             point.y() < currentSvgObj->getObjectRect()->bottom()){
        currentSvgObj->getObjectRect()->setTopLeft(point);
    }
}

void Map::CheckMousePressSettings(QPoint point) {
    if(currentSvgObj->getCentralRect()->contains(point.x(), point.y())) {
        emit CallChangeCursorView(Qt::ClosedHandCursor);
        emit CallSetStatusMoveObject(true);
    }else if (mouse_direct == mouse_location::OUTSIDE) {
        currentSvgObj = nullptr;
        emit CallSetStatusSvgSettings(false);
        emit CallDrawResMap();
    }else{
        emit CallSetStatusResizeSvgObj(true);
    }
}

bool Map::CheckFDiag(mouse_location pos) {
    return (pos == mouse_location::F_DIAG_RIGHT_BOTTOM || pos == mouse_location::F_DIAG_LEFT_TOP);
}

bool Map::CheckBDiag(mouse_location pos) {
    return (pos == mouse_location::B_DIAG_RIGHT_TOP || pos == mouse_location::B_DIAG_LEFT_BOTTOM);
}
bool Map::CheckVert(mouse_location pos) {
    return (pos == mouse_location::VERTICAL_BORDER_BOTTOM || pos == mouse_location::VERTICAL_BORDER_TOP);
}

bool Map::CheckHor(mouse_location pos) {
return (pos == mouse_location::HORIZONTAL_BORDER_RIGHT || pos == mouse_location::HORIZONTAL_BORDER_LEFT);
}

void Map::MoveObject(QPoint point) {
    currentSvgObj->getObjectRect()->moveCenter(point);
    emit CallDrawResMap();
}

void Map::DeleteSvgObject() {
    if(currentSvgObj != nullptr){
        emit CallSetStatusSvgSettings(false);
        std::swap(svgObjects[currentSvgObj->getId()], svgObjects[svgObjects.size()-1]);
        svgObjects.pop_back();
        emit CallDrawResMap();
    }
}


QVector<SvgRenderer*>  *Map::getSvgObjects() {
    return &svgObjects;
}
