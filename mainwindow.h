#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidgetItem>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_spinBox_valueChanged(int arg1);

    void on_tableWidget_itemChanged(QTableWidgetItem *item);

    double vektor_proz(double a[2], double b[2]);

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;

    int lol(double a);
    void samoper(int poinscount);
    bool peresech;
};

#endif // MAINWINDOW_H
