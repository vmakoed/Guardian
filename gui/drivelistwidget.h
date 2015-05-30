#ifndef DRIVELISTWIDGET_H
#define DRIVELISTWIDGET_H

#include <QWidget>
#include <QLabel>

class DriveListWidget : public QWidget
{
    Q_OBJECT

private:
    QLabel *driveLetterLabel;
    QLabel *driveNameLabel;

public:
    explicit DriveListWidget(QString driveLetter, QString driveName);

    QString getDrive();
    QString getDriveName();

signals:

public slots:
};

#endif // DRIVELISTWIDGET_H
