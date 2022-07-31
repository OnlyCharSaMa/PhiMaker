#include "singleitemwidget.h"
#include "ui_singleitemwidget.h"

#include <QImage>
#include <QPainter>

SingleItemWidget::SingleItemWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SingleItemWidget)
{
    ui->setupUi(this);

    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setWindowFlag(Qt::FramelessWindowHint);

    // 初始化
    m_selectedColor = QColor(87, 250, 255, 255);


    // 连接
    connect(this, &SingleItemWidget::isOnChanged,
            [=]{onIsOnChanged();});

    // imageWidget
    connect(this, &SingleItemWidget::imageWidgetRadiusChanged,
            [=]{updateImageWidgetQSS();});

    connect(this, &SingleItemWidget::iconFileChanged,
            [=]{updateImageWidgetQSS();});


    // singleItemWidget
    connect(this, &SingleItemWidget::clipLineColorChanged,
            [=]{updateLabelWidgetQSS();});

    connect(this, &SingleItemWidget::clipLineWidthChanged,
            [=]{updateLabelWidgetQSS();});



}

SingleItemWidget::~SingleItemWidget()
{
    delete ui;
}

void SingleItemWidget::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.setBrush(QBrush(m_selectedColor));
    if(m_isOn) painter.drawRect(this->rect());
}

void SingleItemWidget::mousePressEvent(QMouseEvent *e)
{
    setIsOn(!isOn());
}

void SingleItemWidget::setLabelColor(const QColor &color)
{
    QPalette palette = ui->label->palette();
    palette.setColor(QPalette::WindowText, color);
    ui->label->setPalette(palette);
}


int SingleItemWidget::clipLineWidth() const
{
    return m_clipLineWidth;
}

void SingleItemWidget::setClipLineWidth(int newClipLineWidth)
{
    if (m_clipLineWidth == newClipLineWidth)
        return;
    m_clipLineWidth = newClipLineWidth;
    emit clipLineWidthChanged();
}

const QColor &SingleItemWidget::clipLineColor() const
{
    return m_clipLineColor;
}

void SingleItemWidget::setClipLineColor(const QColor &newClipLineColor)
{
    if (m_clipLineColor == newClipLineColor)
        return;
    m_clipLineColor = newClipLineColor;
    emit clipLineColorChanged();
}

int SingleItemWidget::imageWidgetRadius() const
{
    return m_imageWidgetRadius;
}

void SingleItemWidget::setImageWidgetRadius(int newImageWidgetRadius)
{
    if (m_imageWidgetRadius == newImageWidgetRadius)
        return;
    m_imageWidgetRadius = newImageWidgetRadius;
    emit imageWidgetRadiusChanged();
}

void SingleItemWidget::updateImageWidgetQSS()
{
    QString QSS = "";

    QSS += "#imageWidget {";

    QSS += "border-radius:";
    QSS += QString::number(m_imageWidgetRadius);
    QSS += "px;";

    QSS += "background-color: pink;";

    QSS += "border-image: url(";
    QSS += m_iconFile;
    QSS += ");";

    QSS += "}";

    ui->imageWidget->setStyleSheet(QSS);
}

void SingleItemWidget::updateLabelWidgetQSS()
{
    QString QSS = "";

    QSS += "#labelWidget {";

    QSS += "border-bottom-style: solid;";

    QSS += "border-bottom-color: rgba(";
    QSS += QString::number(m_clipLineColor.red()  );
    QSS += ",";
    QSS += QString::number(m_clipLineColor.green());
    QSS += ",";
    QSS += QString::number(m_clipLineColor.blue() );
    QSS += ",";
    QSS += QString::number(m_clipLineColor.alpha());
    QSS += ");";

    QSS += "border-bottom-width:";
    QSS += QString::number(m_clipLineWidth);
    QSS += "px;";

    QSS += "}";

    ui->labelWidget->setStyleSheet(QSS);
}

void SingleItemWidget::onIsOnChanged()
{
    update();
}

const QColor &SingleItemWidget::selectedColor() const
{
    return m_selectedColor;
}

void SingleItemWidget::setSelectedColor(const QColor &newSelectedColor)
{
    if (m_selectedColor == newSelectedColor)
        return;
    m_selectedColor = newSelectedColor;
    emit selectedColorChanged();
}

void SingleItemWidget::updateQSS()
{

}

bool SingleItemWidget::isOn() const
{
    return m_isOn;
}

void SingleItemWidget::setIsOn(bool newIsOn)
{
    if (m_isOn == newIsOn)
        return;
    m_isOn = newIsOn;
    emit isOnChanged();
}



const QString &SingleItemWidget::iconFile() const
{
    return m_iconFile;
}

void SingleItemWidget::setIconFile(const QString &newIconFile)
{
    if (m_iconFile == newIconFile)
        return;
    m_iconFile = newIconFile;
    emit iconFileChanged();
}
