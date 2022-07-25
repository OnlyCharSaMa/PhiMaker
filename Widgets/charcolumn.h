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
public:
    explicit CharColumn(QWidget *parent = nullptr);
    ~CharColumn();

    void paintEvent(QPaintEvent* e) override;

public:
    const QColor &maskColor() const;
    void setMaskColor(const QColor &newMaskColor);

private:
    Ui::CharColumn *ui;

    QColor m_maskColor; // 这个类不知道为什么用不了C++新特性，所以初始化放在了构造函数
};

#endif // CHARCOLUMN_H
