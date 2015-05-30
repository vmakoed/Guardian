#ifndef ICONTEXTLABEL_H
#define ICONTEXTLABEL_H

#include <QWidget>
#include <QLabel>

class IconTextLabel : public QWidget
{
    Q_OBJECT

private:
    QLabel *iconLabel;
    QLabel *textLabel;

public:
    explicit IconTextLabel(QString iconName, QString text);

    QString getIconName();
    QString getText();

signals:

public slots:
};

#endif // ICONTEXTLABEL_H
