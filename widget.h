#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QIcon>
#include <QPushButton>
#include <QVector>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    const QPixmap& getIkonaGraczaCzerwonego();
    void setIkonaGraczaCzerwonego(const QPixmap& ikona);

    const QPixmap& getIkonaGraczaNiebieskiego();
    void setIkonaGraczaNiebieskiego(const QPixmap& ikona);

    const QPixmap& getIkonaZwyciezaGraczCzerwony();
    void setIkonaZwyciezaGraczCzerwony(const QPixmap& ikona);

    const QPixmap& getIkonaZwyciezaGraczNiebieski();
    void setIkonaZwyciezaGraczNiebieski(const QPixmap& ikona);

    const QIcon& getPoleGraczaCzerwonego();
    void setPoleGraczaCzerwonego(const QIcon& ikona);

    const QIcon& getPoleGraczaNiebieskiego();
    void setPoleGraczaNiebieskiego(const QIcon& ikona);

    const QIcon& getPoleRemisu();
    void setPoleRemisu(const QIcon& ikona);

    const QString& getAktualnyGracz();
    void setAktualnyGracz(const QString& gracz);

    QPushButton* getPolePlanszy(const int& wiersz, const int& kolumna);

    void zmienAktualnegoGracza();
    void ustawIkony();
    void generujPlansze();
    void generujPolaczenia();
    void ustawPolePlanszy();
    void wyszarzPolaPlanszy();
    bool sprawdzWynikGry(const int& wiersz, const int& kolumna);
    void koniecRundy();
    void zaznaczWszystkiePola();
    void uaktualnijWynik();

private slots:

    void wykonajRuch();
    void nowaRunda();

    void on_nowaRunda_clicked();

private:
    Ui::Widget *ui;

    QPixmap ikonaGraczaCzerwonego;
    QPixmap ikonaGraczaNiebieskiego;
    QPixmap ikonaZwyciezaGraczCzerwony;
    QPixmap ikonaZwyciezaGraczNiebieski;
    QIcon poleGraczaCzerwonego;
    QIcon poleGraczaNiebieskiego;
    QIcon poleRemisu;

    QString aktualnyGracz;

    QPushButton* polePlanszy[1200];

};

#endif // WIDGET_H
