#ifndef REMOTECONTROL_H
#define REMOTECONTROL_H

#include <QObject>
#include <QDebug>
#include <QTimer>
#include <QTime>
#include <QSerialPort>
#include <QSerialPortInfo>

#include "quadstates.h"
#include "remotecontrol_xbee_at.h"

class RemoteControl : public QObject
{
    Q_OBJECT
public:
    explicit RemoteControl(QObject *parent = nullptr);
    RemoteControl(QString, QString, QString addr[], QObject *parent = 0);
    void stop();
    uint16_t mapAngleToPWM(float realAngle, float minAngle, float maxAngle, uint16_t minPWM, uint16_t maxPWM);
    Msp_rc_channels manual_rc_values;
    Msp_rc_channels rc_values[3];
    void initRCValues();
    void setValuesFromManual(uint8_t);
    void setValuesFromAuto(uint16_t);
    void sendCommand();

    QString rcSerialPortName;
    QString rcConnectionName;
    QString rcAddrList[3];

    bool rcSerialReady;
    QTimer *rcTimer;
    QSerialPort *rcSerial;

    RemoteControl_XBEE_AT *rc_xbee_at;
    void rcWorker();

    uint8_t manualMode;
    uint16_t autoMode;

signals:

public slots:
    void updateRCValues(QString msg);
    void rcSwitch();
};

#endif // REMOTECONTROL_H