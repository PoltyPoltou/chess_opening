#include "tile.h"
#include "chessboard.h"
#include <QApplication>
#include <QDrag>
#include <QLayout>
#include <QMimeData>
#include <QMouseEvent>
#include <QPainter>
#include <iostream>

Tile::Tile(QWidget *parent) : QWidget(parent)
{
    setAutoFillBackground(true);
    setAcceptDrops(true);
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
        dragStartPos = event->pos();
        emit tileTouched(row, col);
    }
}
void Tile::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton && (dragStartPos - event->pos()).manhattanLength() > 10)
    {
        QDrag *drag = new QDrag(this);
        //using Mime Data to transfer a text of two digits row and column without any spaces
        QMimeData *data = new QMimeData;
        data->setText(QString::fromStdString(std::to_string(row) + std::to_string(col)));
        drag->setMimeData(data);
        Qt::DropAction dropAction = drag->exec();
    }
}
void Tile::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasText())
    {
        event->acceptProposedAction();
    }
}
void Tile::dropEvent(QDropEvent *event)
{
    std::string startDragTile = event->mimeData()->text().toStdString();
    int startRow, startCol;
    startRow = startDragTile[0] - '0';
    startCol = startDragTile[1] - '0';
    std::cout << "Tile dragging from (" << startRow << ',' << startCol << ')' << " to (" << row << ',' << col << ')' << std::endl;
}
