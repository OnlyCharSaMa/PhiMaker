#include "charcolumn.h"
#include "ui_charcolumn.h"

#include <QBitmap>
#include <QPainter>
#include <QStyleOption>

#include <QDebug>

CharColumn::CharColumn(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CharColumn)
{
    ui->setupUi(this);

    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setWindowFlag(Qt::FramelessWindowHint);




    // 信号连接
    connect(this, &CharColumn::backgroundColorChanged,
            [=](){onBackgroundColorChanged();});

    connect(this,  &CharColumn::radiusChanged,
            [=](){onRadiusChanged();});

    connect(this, &CharColumn::addedWidget,
            [=](){updateContent();});
}

CharColumn::~CharColumn()
{
    delete ui;
}

CharColumn &CharColumn::operator<<(QWidget *widget)
{
    return addWidget(widget);
}

void CharColumn::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);


}

void CharColumn::resizeEvent(QResizeEvent *e)
{
    ui->backgroundWidget->setFixedSize(size());
    updateContent();

    emit resized();
}

CharColumn &CharColumn::addWidget(QWidget *widget)
{
    widget->setParent(ui->backgroundWidget);
    m_widgetList.push_back(widget);
    emit addedWidget();
    return *this;
}


void CharColumn::updateBackgroundQSS()
{
    QString QSS = "";
    QSS += "#backgroundWidget {";

    QSS += "background-color: rgba(";
    QSS += QString::number(m_backgroundColor.red());
    QSS += ",";
    QSS += QString::number(m_backgroundColor.green());
    QSS += ",";
    QSS += QString::number(m_backgroundColor.blue());
    QSS += ",";
    QSS += QString::number(m_backgroundColor.alpha());
    QSS += ");";

    QSS += "border-radius: ";
    QSS += QString::number(radius());
    QSS += "px;";

    QSS += "}";

    ui->backgroundWidget->setStyleSheet(QSS);
    ui->backgroundWidget->update();

}

void CharColumn::updateContent()
{
    // 自动修正里面所有的widget高
    int numsOfWidgets = m_widgetList.length();
    if(numsOfWidgets == 0) return; // 防止程序除以0 导致崩溃
    int widgetHeight  = this->height() / numsOfWidgets;
    for(int i = 0; i < m_widgetList.length(); i++)
    {
        QWidget* widget = m_widgetList[i];
        widget->setGeometry(0, widgetHeight * i, width(), widgetHeight);
    }
}

int CharColumn::radius() const
{
    return m_radius;
}

void CharColumn::setRadius(int newRadius)
{
    if (m_radius == newRadius)
        return;
    m_radius = newRadius;
    emit radiusChanged();
}

const QColor &CharColumn::backgroundColor() const
{
    return m_backgroundColor;
}

void CharColumn::setBackgroundColor(const QColor &newBackgroundColor)
{
    if (m_backgroundColor == newBackgroundColor)
        return;
    m_backgroundColor = newBackgroundColor;
    emit backgroundColorChanged();
}

void CharColumn::onBackgroundColorChanged()
{
    updateBackgroundQSS();
}

void CharColumn::onRadiusChanged()
{
    updateBackgroundQSS();
}

