#ifndef CHARCOLUMN_H
#define CHARCOLUMN_H

#include <QWidget>
#include <QColor>

namespace Ui {
class CharColumn;
}

class CharColumn : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor NOTIFY backgroundColorChanged)
    Q_PROPERTY(int radius READ radius WRITE setRadius NOTIFY radiusChanged)
public:
    explicit CharColumn(QWidget *parent = nullptr);
    ~CharColumn();

    CharColumn& operator<<(QWidget* widget);
    void paintEvent(QPaintEvent* e) override;
    void resizeEvent(QResizeEvent* e) override;

    CharColumn& addWidget(QWidget* widget);

public:
    const QColor &backgroundColor() const;
    void setBackgroundColor(const QColor &newBackgroundColor);

    int radius() const;
    void setRadius(int newRadius);

public slots:
    void onBackgroundColorChanged();
    void onRadiusChanged();

    void updateBackgroundQSS();
    void updateContent();

signals:
    // 类成员变化信号
    void backgroundColorChanged();
    void radiusChanged();

    // 状态改变信号
    void addedWidget();
    void resized();

private:
    Ui::CharColumn *ui;

    QColor m_backgroundColor; // 这个类不知道为什么用不了C++新特性，所以初始化放在了构造函数
    int    m_radius;          // 背景里面的圆角
    QVector<QWidget*> m_widgetList;


};

#endif // CHARCOLUMN_H
