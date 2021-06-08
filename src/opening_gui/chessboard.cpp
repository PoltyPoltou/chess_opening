#include "chessboard.h"
#include "ui/ui_chessboard.h"
#include <QMouseEvent>
#include <QPainter>
#include <QPixmap>
#include <QString>
#include <iostream>

namespace
{
    std::string getImagePath(chess::Piece piece, bool colour)
    {
        std::string path("./img/std/");
        if (colour == chess::WHITE)
        {
            path += 'w';
        }
        else
        {
            path += 'b';
        }
        return path + static_cast<char>(piece) + ".png";
    }

    void getPiecePixMap(QPixmap &pixmap, chess::Piece piece, bool colour)
    {
        pixmap.load(QString::fromStdString(getImagePath(piece, colour)));
    }

}

ChessBoard::ChessBoard(QWidget *parent) : QWidget(parent), ui(new Ui::ChessBoard), overlay(parent), state(chess::BoardState())
{
    ui->setupUi(this);
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            Tile *t = getTile(i, j);
            if (t != nullptr)
            {
                t->setCoords(i, j);
            }
        }
    }
    overlay.layout = ui->gridLayout;
    overlay.piecesMap = &piecesMap;
    overlay.cursorPos = QPoint(0, 0);
    overlay.grabbedPiece = nullptr;
    updatePieces();
}

ChessBoard::~ChessBoard()
{
    delete ui;
}
/**
 * the pixmap will be moved so p will not be usable after this function
 */
void ChessBoard::setPiece(int row, int column, const QPixmap &p)
{
    piecesMap[std::make_pair(row, column)] = std::move(p);
}

void ChessBoard::updatePieces()
{
    chess::Tile *t;
    QPixmap pieceImg;
    piecesMap.clear();
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            t = state.get(i, j);
            if (!t->is_empty())
            {
                getPiecePixMap(pieceImg, t->piece(), t->color());
                setPiece(i, j, pieceImg);
            }
        }
    }
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
    *row = 7 - *row;
}

Tile *ChessBoard::getTile(int row, int col)
{
    Tile *result = nullptr;
    QLayoutItem *ptr = ui->gridLayout->itemAtPosition(7 - row, col);
    if (ptr != nullptr && !ptr->isEmpty())
    {
        result = qobject_cast<Tile *>(ptr->widget());
    }
    return result;
}

void ChessBoard::onTileGrabbed(int row, int col)
{
    std::pair<int, int> key = std::make_pair(row, col);
    if (piecesMap.find(key) != piecesMap.end())
    {
        overlay.grabbedPiece = &piecesMap[key];
    }
}

void ChessBoard::onTileReleased(int startRow, int startCol, int endRow, int endCol)
{
    overlay.grabbedPiece = nullptr;
    attemptMove(std::make_pair(startRow, startCol), std::make_pair(endRow, endCol));
    overlay.repaint();
}

void ChessBoardOverlay::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    QPainter paint(this);
    paint.setRenderHint(QPainter::SmoothPixmapTransform);
    for (auto iter : *piecesMap)
    {
        std::pair<int, int> key = iter.first;
        QPixmap *piece = &piecesMap->at(key);
        QRect tileRect = layout->itemAtPosition(7 - key.first, key.second)->geometry();
        if (piece == grabbedPiece)
        {
            tileRect.moveCenter(cursorPos);
        }
        paint.drawPixmap(tileRect, *piece);
    }
}

bool ChessBoard::attemptMove(std::pair<int, int> t1, std::pair<int, int> t2)
{
    chess::Move mv(t1.first, t1.second, t2.first, t2.second);
    bool playable = state.isLegal(mv);
    if (playable)
    {
        state.playMove(mv);
    }
    updatePieces();
    return playable;
}