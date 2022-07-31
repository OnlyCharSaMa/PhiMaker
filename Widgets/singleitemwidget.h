#ifndef SINGLEITEMWIDGET_H
#define SINGLEITEMWIDGET_H

#include <QWidget>

namespace Ui {
class SingleItemWidget;
}

class SingleItemWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QString iconFile READ iconFile WRITE setIconFile NOTIFY iconFileChanged)
    Q_PROPERTY(int imageWidgetRadius READ imageWidgetRadius WRITE setImageWidgetRadius NOTIFY imageWidgetRadiusChanged)
    Q_PROPERTY(QColor clipLineColor READ clipLineColor WRITE setClipLineColor NOTIFY clipLineColorChanged)
    Q_PROPERTY(int clipLineWidth READ clipLineWidth WRITE setClipLineWidth NOTIFY clipLineWidthChanged)
    Q_PROPERTY(bool isOn READ isOn WRITE setIsOn NOTIFY isOnChanged)
    Q_PROPERTY(QColor selectedColor READ selectedColor WRITE setSelectedColor NOTIFY selectedColorChanged)
public:
    explicit SingleItemWidget(QWidget *parent = nullptr);
    ~SingleItemWidget();

    void paintEvent(QPaintEvent* e);
    void mousePressEvent(QMouseEvent* e);

public:
    void setLabelColor(const QColor& color);

    // getter 和 setter
    int imageWidgetRadius() const;
    void setImageWidgetRadius(int newImageWidgetRadius);

    const QColor &clipLineColor() const;
    void setClipLineColor(const QColor &newClipLineColor);

    int clipLineWidth() const;
    void setClipLineWidth(int newClipLineWidth);

    const QString &iconFile() const;
    void setIconFile(const QString &newIconFile);

    bool isOn() const;
    void setIsOn(bool newIsOn);

    const QColor &selectedColor() const;
    void setSelectedColor(const QColor &newSelectedColor);

public slots:
    void updateQSS();
    void updateImageWidgetQSS();
    void updateLabelWidgetQSS();

    void onIsOnChanged();


private:


private:
    Ui::SingleItemWidget *ui;

    // 控件的属性
    // imageWidget
    QString m_iconFile;
    int     m_imageWidgetRadius;
    // labelWidget
    QColor  m_clipLineColor;
    int     m_clipLineWidth;

    // 本身属性
    QColor  m_selectedColor;
    bool    m_isOn = false;


signals:
    void iconFileChanged();
    void imageWidgetRadiusChanged();
    void clipLineColorChanged();
    void clipLineWidthChanged();
    void isOnChanged();
    void selectedColorChanged();
};

#endif // SINGLEITEMWIDGET_H
