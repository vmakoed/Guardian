#include "drivewidget.h"

#include <QHBoxLayout>
#include <QStyleOption>
#include <QPainter>;

DriveWidget::DriveWidget(QWidget *parent, QString driveLetter, QString driveName) : QPushButton(parent)
{
    setObjectName("driveWidget");

    driveLetterLabel = new QLabel(driveLetter);
    driveLetterLabel->setObjectName("driveLetterLabel");


    driveNameLabel = new QLabel(driveName);
    driveLetterLabel->setObjectName("driveNameLabel");

    QHBoxLayout *rootLayout = new QHBoxLayout;
    rootLayout->setContentsMargins(0, 0, 0, 0);
    rootLayout->setSpacing(0);

    rootLayout->addSpacerItem(new QSpacerItem(20, 0, QSizePolicy::Fixed, QSizePolicy::Fixed));
    rootLayout->addWidget(driveLetterLabel);
    rootLayout->addSpacerItem(new QSpacerItem(15, 0, QSizePolicy::Fixed, QSizePolicy::Fixed));
    rootLayout->addWidget(driveNameLabel);

    setLayout(rootLayout);
    setCheckable(true);
    uncheck();

    connect(this, &DriveWidget::clicked, this, &DriveWidget::check);
}

QString DriveWidget::getDriveLetter()
{
    return driveLetterLabel->text();
}

void DriveWidget::uncheck()
{
    setChecked(false);

    setStyleSheet("QWidget:hover {background: #F0F0F0}");

    driveNameLabel->setStyleSheet("\
    QLabel { \
        color: #212121; \
    }");

    driveLetterLabel->setStyleSheet(
                      " QLabel {          \
                          min-width: 36px;                      \
                          max-width: 36px;                      \
                          min-height: 36px;                     \
                          max-height: 36px;                     \
                          border-radius: 18px;                  \
                          qproperty-alignment: AlignCenter;     \
                          font-weight : bold;                   \
                          background: solid qradialgradient(cx:0.5, cy:0.5, fx:0.5, fy:0.5, radius: 0.5, \
               stop:0 #FFFFFF, stop: 0.89 #FFFFFF stop: 0.9 #212121, stop: 1 #212121); \
                          color: #212121;                       \
                        }");
}

void DriveWidget::check()
{
    driveNameLabel->setStyleSheet("\
    QLabel { \
        color: #2196F3; \
        font-weight: bold; \
    }");

    driveLetterLabel->setStyleSheet(
                      " QLabel {                                \
                          min-width: 36px;                      \
                          max-width: 36px;                      \
                          min-height: 36px;                     \
                          max-height: 36px;                     \
                          border-radius: 18px;                  \
                          qproperty-alignment: AlignCenter;     \
                          font-weight : bold;                   \
                          background : solid #2196F3;           \
                          color: #FFFFFF                        \
                        }");
}

void DriveWidget::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
