#include "tile.h"
#include "chessboard.h"
#include <QLayout>
#include <QMouseEvent>
#include <QPainter>
#include <iostream>

Tile::Tile(QWidget *parent) : QWidget(parent)
{
    setAutoFillBackground(true);
}
Tile::~Tile() {}

void Tile::setCoords(int row, int column)
{
    this->row = row;
    this->col = column;
    updateBackgroundColor();
}
void Tile::updateBackgroundColor()
{
    QColor clr = (row + col) % 2 == 0 ? ChessColors::even : ChessColors::uneven;
    QPalette p(palette());
    p.setColor(QPalette::Background, clr);
    setPalette(p);
}
int Tile::getRow()
{
    return row;
}
int Tile::getCol()
{
    return col;
}
void Tile::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        std::cout << "local event " << row << col << std::endl;
        emit tileTouched(row, col);
    }
}
