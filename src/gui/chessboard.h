#pragma once

#include "tile.h"
#include <QColor>
#include <QWidget>
QT_BEGIN_NAMESPACE
namespace Ui
{
    class ChessBoard;
}
QT_END_NAMESPACE

namespace ChessColors
{
    static QColor even(54, 137, 110);
    static QColor uneven(214, 231, 226);
}

class ChessBoard : public QWidget
{
    Q_OBJECT
private:
    Ui::ChessBoard *ui;
    void getTileCoords(Tile &tile, int *row, int *col);

protected:
    virtual void resizeEvent(QResizeEvent *event);

public:
    ChessBoard(QWidget *parent = nullptr);
    ~ChessBoard();
};
