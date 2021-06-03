#pragma once

#include "boardstate.h"
#include "tile.h"
#include <QColor>
#include <QGridLayout>
#include <QPixmap>
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
class ChessBoard;
class ChessBoardOverlay;
class ChessBoardOverlay : public QWidget
{
    Q_OBJECT
    friend ChessBoard;

private:
    std::map<std::pair<int, int>, QPixmap> *piecesMap;
    QPoint cursorPos;
    QPixmap *grabbedPiece;
    QGridLayout *layout;

protected:
    virtual void paintEvent(QPaintEvent *event);

public:
    ChessBoardOverlay(QWidget *parent) : QWidget(parent) { setAttribute(Qt::WA_TransparentForMouseEvents); }
};

class ChessBoard : public QWidget
{
    Q_OBJECT

private:
    Ui::ChessBoard *ui;
    std::map<std::pair<int, int>, QPixmap> piecesMap;
    ChessBoardOverlay overlay;
    chess::BoardState state;

    void getTileCoords(Tile &tile, int *row, int *col);
    Tile *getTile(int row, int col);
    void updatePieces();

protected:
    virtual void resizeEvent(QResizeEvent *event);

public:
    ChessBoard(QWidget *parent = nullptr);
    ~ChessBoard();
    void setPiece(int row, int column, const QPixmap &piece);

public slots:
    void onTileGrabbed(int row, int col);
    void onTileReleased(int startRow, int startCol, int endRow, int endCol);
    void updateCursor(const QPoint &cursor);
};
