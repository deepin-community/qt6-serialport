/****************************************************************************
**
** Copyright (C) 2012 Denis Shienkov <denis.shienkov@gmail.com>
** Copyright (C) 2013 Laszlo Papp <lpapp@kde.org>
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtSerialPort module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl-3.0.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 2.0 or (at your option) the GNU General
** Public license version 3 or any later version approved by the KDE Free
** Qt Foundation. The licenses are as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL2 and LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-2.0.html and
** https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QSERIALPORT_H
#define QSERIALPORT_H

#include <QtCore/qiodevice.h>

#include <QtSerialPort/qserialportglobal.h>

QT_BEGIN_NAMESPACE

class QSerialPortInfo;
class QSerialPortPrivate;

class Q_SERIALPORT_EXPORT QSerialPort : public QIODevice
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(QSerialPort)

    Q_PROPERTY(qint32 baudRate READ baudRate WRITE setBaudRate NOTIFY baudRateChanged)
    Q_PROPERTY(DataBits dataBits READ dataBits WRITE setDataBits NOTIFY dataBitsChanged
                BINDABLE bindableDataBits)
    Q_PROPERTY(Parity parity READ parity WRITE setParity NOTIFY parityChanged BINDABLE bindableParity)
    Q_PROPERTY(StopBits stopBits READ stopBits WRITE setStopBits NOTIFY stopBitsChanged
                BINDABLE bindableStopBits)
    Q_PROPERTY(FlowControl flowControl READ flowControl WRITE setFlowControl NOTIFY flowControlChanged
                BINDABLE bindableFlowControl)
    Q_PROPERTY(bool dataTerminalReady READ isDataTerminalReady WRITE setDataTerminalReady
                NOTIFY dataTerminalReadyChanged)
    Q_PROPERTY(bool requestToSend READ isRequestToSend WRITE setRequestToSend NOTIFY requestToSendChanged)
    Q_PROPERTY(SerialPortError error READ error RESET clearError NOTIFY errorOccurred BINDABLE bindableError)
    Q_PROPERTY(bool breakEnabled READ isBreakEnabled WRITE setBreakEnabled NOTIFY breakEnabledChanged
                BINDABLE bindableIsBreakEnabled)

#if defined(Q_OS_WIN32)
    typedef void* Handle;
#else
    typedef int Handle;
#endif

public:

    enum Direction  {
        Input = 1,
        Output = 2,
        AllDirections = Input | Output
    };
    Q_FLAG(Direction)
    Q_DECLARE_FLAGS(Directions, Direction)

    enum BaudRate {
        Baud1200 = 1200,
        Baud2400 = 2400,
        Baud4800 = 4800,
        Baud9600 = 9600,
        Baud19200 = 19200,
        Baud38400 = 38400,
        Baud57600 = 57600,
        Baud115200 = 115200
    };
    Q_ENUM(BaudRate)

    enum DataBits {
        Data5 = 5,
        Data6 = 6,
        Data7 = 7,
        Data8 = 8
    };
    Q_ENUM(DataBits)

    enum Parity {
        NoParity = 0,
        EvenParity = 2,
        OddParity = 3,
        SpaceParity = 4,
        MarkParity = 5
    };
    Q_ENUM(Parity)

    enum StopBits {
        OneStop = 1,
        OneAndHalfStop = 3,
        TwoStop = 2
    };
    Q_ENUM(StopBits)

    enum FlowControl {
        NoFlowControl,
        HardwareControl,
        SoftwareControl
    };
    Q_ENUM(FlowControl)

    enum PinoutSignal {
        NoSignal = 0x00,
        DataTerminalReadySignal = 0x04,
        DataCarrierDetectSignal = 0x08,
        DataSetReadySignal = 0x10,
        RingIndicatorSignal = 0x20,
        RequestToSendSignal = 0x40,
        ClearToSendSignal = 0x80,
        SecondaryTransmittedDataSignal = 0x100,
        SecondaryReceivedDataSignal = 0x200
    };
    Q_FLAG(PinoutSignal)
    Q_DECLARE_FLAGS(PinoutSignals, PinoutSignal)

    enum SerialPortError {
        NoError,
        DeviceNotFoundError,
        PermissionError,
        OpenError,
        WriteError,
        ReadError,
        ResourceError,
        UnsupportedOperationError,
        UnknownError,
        TimeoutError,
        NotOpenError
    };
    Q_ENUM(SerialPortError)

    explicit QSerialPort(QObject *parent = nullptr);
    explicit QSerialPort(const QString &name, QObject *parent = nullptr);
    explicit QSerialPort(const QSerialPortInfo &info, QObject *parent = nullptr);
    virtual ~QSerialPort();

    void setPortName(const QString &name);
    QString portName() const;

    void setPort(const QSerialPortInfo &info);

    bool open(OpenMode mode) override;
    void close() override;

    bool setBaudRate(qint32 baudRate, Directions directions = AllDirections);
    qint32 baudRate(Directions directions = AllDirections) const;

    bool setDataBits(DataBits dataBits);
    DataBits dataBits() const;
    QBindable<DataBits> bindableDataBits();

    bool setParity(Parity parity);
    Parity parity() const;
    QBindable<Parity> bindableParity();

    bool setStopBits(StopBits stopBits);
    StopBits stopBits() const;
    QBindable<bool> bindableStopBits();

    bool setFlowControl(FlowControl flowControl);
    FlowControl flowControl() const;
    QBindable<FlowControl> bindableFlowControl();

    bool setDataTerminalReady(bool set);
    bool isDataTerminalReady();

    bool setRequestToSend(bool set);
    bool isRequestToSend();

    PinoutSignals pinoutSignals();

    bool flush();
    bool clear(Directions directions = AllDirections);

    SerialPortError error() const;
    void clearError();
    QBindable<SerialPortError> bindableError() const;

    qint64 readBufferSize() const;
    void setReadBufferSize(qint64 size);

    bool isSequential() const override;

    qint64 bytesAvailable() const override;
    qint64 bytesToWrite() const override;
    bool canReadLine() const override;

    bool waitForReadyRead(int msecs = 30000) override;
    bool waitForBytesWritten(int msecs = 30000) override;

    bool setBreakEnabled(bool set = true);
    bool isBreakEnabled() const;
    QBindable<bool> bindableIsBreakEnabled();

    Handle handle() const;

Q_SIGNALS:
    void baudRateChanged(qint32 baudRate, QSerialPort::Directions directions);
    void dataBitsChanged(QSerialPort::DataBits dataBits);
    void parityChanged(QSerialPort::Parity parity);
    void stopBitsChanged(QSerialPort::StopBits stopBits);
    void flowControlChanged(QSerialPort::FlowControl flowControl);
    void dataTerminalReadyChanged(bool set);
    void requestToSendChanged(bool set);
    void errorOccurred(QSerialPort::SerialPortError error);
    void breakEnabledChanged(bool set);

protected:
    qint64 readData(char *data, qint64 maxSize) override;
    qint64 readLineData(char *data, qint64 maxSize) override;
    qint64 writeData(const char *data, qint64 maxSize) override;

private:
    Q_DISABLE_COPY(QSerialPort)

#if defined(Q_OS_WIN32)
    Q_PRIVATE_SLOT(d_func(), bool _q_startAsyncWrite())
#endif
};

Q_DECLARE_OPERATORS_FOR_FLAGS(QSerialPort::Directions)
Q_DECLARE_OPERATORS_FOR_FLAGS(QSerialPort::PinoutSignals)

QT_END_NAMESPACE

#endif // QSERIALPORT_H