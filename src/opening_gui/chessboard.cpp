#include "chessboard.h"
#include "ui/ui_chessboard.h"
#include <QMouseEvent>
#include <QPainter>
#include <QPixmap>
#include <iostream>

ChessBoard::ChessBoard(QWidget *parent) : QWidget(parent), ui(new Ui::ChessBoard), overlay(parent)
{
    ui->setupUi(this);
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            Tile *t = getTile(i, j);
            if (t != nullptr)
            {
                t->setCoords(8 - i, j + 1);
            }
        }
    }
    overlay.layout = ui->gridLayout;
    overlay.piecesMap = &piecesMap;
    overlay.cursorPos = QPoint(0, 0);
    overlay.grabbedPiece = nullptr;
}

ChessBoard::~ChessBoard()
{
    delete ui;
}
void ChessBoard::setPiece(int row, int column, const QPixmap &p)
{
    piecesMap[std::make_tuple(8 - row, column - 1)] = p;
}

std::tuple<int, int> ChessBoard::getGridCoords(int row, int column) const
{
    return std::make_tuple(8 - row, column - 1);
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
    overlay.setGeometry(geometry());
}
void ChessBoard::updateCursor(const QPoint &cursor)
{
    if (overlay.grabbedPiece)
    {
        overlay.cursorPos = cursor;
        overlay.repaint();
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

Tile *ChessBoard::getTile(int row, int col)
{
    Tile *result = nullptr;
    auto *ptr = ui->gridLayout->itemAtPosition(row, col);
    if (ptr != nullptr && !ptr->isEmpty())
    {
        result = qobject_cast<Tile *>(ptr->widget());
    }
    return result;
}

void ChessBoard::onTileGrabbed(int row, int col)
{
    std::tuple<int, int> key = getGridCoords(row, col);
    if (piecesMap.find(key) != piecesMap.end())
    {
        overlay.grabbedPiece = &piecesMap[key];
    }
}

void ChessBoard::onTileReleased(int startRow, int startCol, int endRow, int endCol)
{
    overlay.grabbedPiece = nullptr;
    overlay.repaint();
}

void ChessBoardOverlay::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    QPainter paint(this);
    paint.setRenderHint(QPainter::SmoothPixmapTransform);
    for (auto iter : *piecesMap)
    {
        std::tuple<int, int> key = iter.first;
        QPixmap *piece = &piecesMap->at(key);
        QRect tileRect = layout->itemAtPosition(std::get<0>(key), std::get<1>(key))->geometry();
        if (piece == grabbedPiece)
        {
            tileRect.moveCenter(cursorPos);
        }
        paint.drawPixmap(tileRect, *piece);
    }
}