#pragma once

#include <QWidget>

class Tile : public QWidget
{
    Q_OBJECT
private:
    int row, col;
    QPoint dragStartPos;

protected:
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void dragEnterEvent(QDragEnterEvent *event);
    virtual void dragMoveEvent(QDragMoveEvent *event);
    virtual void dropEvent(QDropEvent *event);

public:
    Tile(QWidget *parent = nullptr);
    ~Tile();
    void setCoords(int row, int column);
    int getRow();
    int getCol();
    void updateBackgroundColor();
signals:
    void tileTouched(int row, int column);
    void tileStartDrag(int row, int column);
    void tileMoveDrag(const QPoint &cursor);
    void tileEndDrag(int startRow, int startCol, int endRow, int Endcol);
};
