#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QButtonGroup>

#include <QMouseEvent>

class Toolbar : public QWidget
{
    Q_OBJECT

private:
    QLabel *appIcon;
    QLabel *appTitle;

    QButtonGroup *toolButtons;

    QPushButton *infoButton;
    QPushButton *deleteButton;
    QPushButton *settingsButton;
    QPushButton *closeButton;

public:
    explicit Toolbar(QWidget *parent = 0);

    void paintEvent(QPaintEvent *);

signals:
    void closeClicked();
    void deleteClicked();

public slots:
};

#endif // TOOLBAR_H
