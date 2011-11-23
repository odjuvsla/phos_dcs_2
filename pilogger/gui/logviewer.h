#ifndef LOGVIEWER_H
#define LOGVIEWER_H

// Lib includes
#include <QTableWidget>
#include <QHeaderView>
#include <QVector>
#include <QDateTime>
#include <QFont>

// Local includes
#include "../model/logelement.h"


class LogViewer : public QTableWidget
{
    Q_OBJECT

public:

    explicit LogViewer(QWidget *parent = 0);
    ~LogViewer();

public slots:
    void setupSignals();
    void initializeLog();
    void loadDefaultColors();
    bool addElement(const LogElement& element);
    bool addElement(const QString& text, const LogState &state = LogState::NORMAL, QDateTime dateTime = QDateTime::currentDateTime());
    /*bool removeElement(int id);
    bool removeElement(int row);
    bool removeElement(const LogElement& element);
    bool removeElement(QModelIndex modelIndex);
    bool removeElement(QTableWidgetItem* tableItem);
    */
    void clearLog();

private:
    QVector<LogElement> allElements;
    QVector<LogElement> currentElements;
    QMap<int, QColor> colors;
    int rowCount;
    int showState;
};

#endif // LOGVIEWER_H
