#include "vekMessage.h"

#include <QLoggingCategory>


Q_DECLARE_LOGGING_CATEGORY(testLogger)
Q_LOGGING_CATEGORY(testLogger, "ssh.client", QtDebugMsg)

vekMessage::vekMessage(QWidget *parent) : QWidget(parent)
{
    this->resize(400, 300);
    is_finished = false;

    browser = new QTextBrowser();
    start_button = new QPushButton();
    clear_button = new QPushButton();

    start_button->setText("start");
    clear_button->setText("clear");

    QHBoxLayout *button_layout = new QHBoxLayout();
    button_layout->addStretch();
    button_layout->addWidget(start_button);
    button_layout->addWidget(clear_button);
    button_layout->setSpacing(10);
    button_layout->setContentsMargins(0, 0, 10, 10);

    QVBoxLayout *main_layout = new QVBoxLayout();
    main_layout->addWidget(browser);
    main_layout->addLayout(button_layout);
    main_layout->setSpacing(10);
    main_layout->setContentsMargins(0, 0, 0, 0);

    this->setLayout(main_layout);
    connect(start_button, &QPushButton::clicked, this, &vekMessage::start);
    connect(clear_button, &QPushButton::clicked, browser, &QTextBrowser::clear);
}


void vekMessage::outputMessage(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QString message;
    switch(type)
    {
        case QtDebugMsg:
        message = QString("Debug:");
        break;

        case QtWarningMsg:
        message = QString("Warning:");
        break;

        case QtCriticalMsg:
        message = QString("Critical:");
        break;

        case QtFatalMsg:
        message = QString("Fatal:");
    }

    browser->append(message.append(msg));
}


void vekMessage::start()
{
    if(!is_finished)
    {
        for(int i=0; i<1000000; i++)
        {
            QCoreApplication::processEvents();
            qCDebug(testLogger)   << ": test ";
            qDebug()<<QString("This is a Qt log browser").append(QString::number(i, 10));

        }
        is_finished = true;
    }
}

void vekMessage::closeEvent(QCloseEvent *event)
{
    QMessageBox::StandardButton answer = QMessageBox::question(
        this,
        tr("Close Log Browser?"),
        tr("Do you really want to close the log browser?"),
        QMessageBox::Yes | QMessageBox::No
    );

    if (answer == QMessageBox::Yes)
        event->accept();
    else
        event->ignore();
}

void vekMessage::keyPressEvent(QKeyEvent *event)
{
    event->ignore();
}
