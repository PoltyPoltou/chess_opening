#include "chessboard.h"
#include "ui_chessboard.h"
#include <iostream>

ChessBoard::ChessBoard(QWidget *parent) : QWidget(parent), ui(new Ui::ChessBoard)
{
    ui->setupUi(this);
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            auto *ptr = ui->gridLayout->itemAtPosition(i, j);
            if (ptr != nullptr && !ptr->isEmpty())
            {
                Tile *t = qobject_cast<Tile *>(ptr->widget());
                t->setCoords(8 - i, j + 1);
            }
        }
    }
}
ChessBoard::~ChessBoard()
{
    delete ui;
}
void ChessBoard::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    if (height() > width())
    {
        int margin = (height() - width()) / 2 + 9;
        ui->gridLayout->setContentsMargins(9, margin, 9, margin);
    }
    else
    {
        int margin = (width() - height()) / 2 + 9;
        ui->gridLayout->setContentsMargins(margin, 9, margin, 9);
    }
}

void ChessBoard::getTileCoords(Tile &tile, int *row, int *col)
{
    int idx, _;
    idx = ui->gridLayout->indexOf(&tile);
    ui->gridLayout->getItemPosition(idx, row, col, &_, &_);
    *row = 8 - *row;
    ++*col;
}