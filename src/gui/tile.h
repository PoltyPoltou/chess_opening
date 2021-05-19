#pragma once

#include <QWidget>

class Tile : public QWidget
{
    Q_OBJECT
private:
    int row, col;

protected:
    virtual void mousePressEvent(QMouseEvent *event);

public:
    Tile(QWidget *parent = nullptr);
    ~Tile();
    void setCoords(int row, int column);
    int getRow();
    int getCol();
    void updateBackgroundColor();
signals:
    void tileTouched(int row, int column);
};
