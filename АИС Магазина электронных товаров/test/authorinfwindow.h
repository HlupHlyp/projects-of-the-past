#ifndef AUTHORINFWINDOW_H
#define AUTHORINFWINDOW_H

#include <QWidget>
#include <twactions.h>

namespace Ui {
class authorInfWindow;
}

class authorInfWindow : public QWidget
{
    Q_OBJECT

public:
    explicit authorInfWindow(QWidget *parent = nullptr);
    ~authorInfWindow();

signals:
    void prevWindow();
private slots:

    void on_btnBack_clicked();

private:
    Ui::authorInfWindow *ui;
    TableData data;
};

#endif // AUTHORINFWINDOW_H
