#include "charcolumn.h"
#include "ui_charcolumn.h"

#include <QBitmap>
#include <QPainter>

CharColumn::CharColumn(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CharColumn)
{
    ui->setupUi(this);

    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setWindowFlag(Qt::FramelessWindowHint);

    m_maskColor = QColor(100, 100, 100, 155);
//    QBitmap background(this->size());
//    background.fill(Qt::green);

//    QPainter bg_painter;
//    bg_painter.begin(&background);
//    bg_painter.setRenderHint(QPainter::Antialiasing);
//    bg_painter.setPen(Qt::transparent);
//    bg_painter.setPen(Qt::NoPen);
//    bg_painter.setBrush(Qt::green);
//    bg_painter.drawRoundedRect(this->rect(), 20, 20);
//    bg_painter.end();

//    setMask(background);

}

CharColumn::~CharColumn()
{
    delete ui;
}

void CharColumn::paintEvent(QPaintEvent *e)
{
    QPainter bg_painter(this);
    bg_painter.setRenderHint(QPainter::Antialiasing);
    bg_painter.setPen(Qt::transparent);
    bg_painter.setPen(Qt::NoPen);
    bg_painter.setBrush(m_maskColor);
    bg_painter.drawRoundedRect(this->rect(), 20, 20);
    bg_painter.end();
}

const QColor &CharColumn::maskColor() const
{
    return m_maskColor;
}

void CharColumn::setMaskColor(const QColor &newMaskColor)
{
    m_maskColor = newMaskColor;
}
