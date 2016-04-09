#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    ustawIkony();
    generujPlansze();
    generujPolaczenia();
    setAktualnyGracz("Czerwony");

}

Widget::~Widget()
{
    delete ui;
}

//gettery i settery

const QPixmap& Widget::getIkonaGraczaCzerwonego()
{
    return ikonaGraczaCzerwonego;
}

void Widget::setIkonaGraczaCzerwonego(const QPixmap& ikona)
{
    ikonaGraczaCzerwonego=ikona;
}

const QPixmap& Widget::getIkonaGraczaNiebieskiego()
{
    return ikonaGraczaNiebieskiego;
}

void Widget::setIkonaGraczaNiebieskiego(const QPixmap& ikona)
{
    ikonaGraczaNiebieskiego=ikona;
}

const QPixmap& Widget::getIkonaZwyciezaGraczCzerwony()
{
    return ikonaZwyciezaGraczCzerwony;
}

void Widget::setIkonaZwyciezaGraczCzerwony(const QPixmap& ikona)
{
    ikonaZwyciezaGraczCzerwony=ikona;
}

const QPixmap& Widget::getIkonaZwyciezaGraczNiebieski()
{
    return ikonaZwyciezaGraczNiebieski;
}

void Widget::setIkonaZwyciezaGraczNiebieski(const QPixmap& ikona)
{
    ikonaZwyciezaGraczNiebieski=ikona;
}

const QIcon& Widget::getPoleGraczaCzerwonego()
{
    return poleGraczaCzerwonego;
}

void Widget::setPoleGraczaCzerwonego(const QIcon& ikona)
{
    poleGraczaCzerwonego=ikona;
}

const QIcon& Widget::getPoleGraczaNiebieskiego()
{
    return poleGraczaNiebieskiego;
}

void Widget::setPoleGraczaNiebieskiego(const QIcon& ikona)
{
    poleGraczaNiebieskiego=ikona;
}

const QIcon& Widget::getPoleRemisu()
{
    return poleRemisu;
}

void Widget::setPoleRemisu(const QIcon& ikona)
{
    poleRemisu=ikona;
}

const QString& Widget::getAktualnyGracz()
{
    return aktualnyGracz;
}

void Widget::setAktualnyGracz(const QString& gracz)
{
    aktualnyGracz=gracz;
}

QPushButton* Widget::getPolePlanszy(const int& wiersz, const int& kolumna)
{
    int indeks;
    indeks = (wiersz-1)*40+(kolumna-1);
    return polePlanszy[indeks];
}

//metody sterujace

void Widget::zmienAktualnegoGracza()
{
    QString gracz=getAktualnyGracz();
    if(gracz=="Czerwony")
    {
        setAktualnyGracz("Niebieski");
        ui->ruchGracza_3->setPixmap(getIkonaGraczaNiebieskiego());
    }
    if(gracz=="Niebieski")
    {
        setAktualnyGracz("Czerwony");
        ui->ruchGracza_3->setPixmap(getIkonaGraczaCzerwonego());
    }
}

void Widget::ustawIkony()
{
    setIkonaGraczaCzerwonego(QPixmap(":/images/Chess-Game-red-256.png"));
    setIkonaGraczaNiebieskiego(QPixmap(":/images/Chess-Game-256.png"));
    setPoleGraczaCzerwonego(QIcon(":/images/Tic-Tac-Toe-Game-red-256.png"));
    setPoleGraczaNiebieskiego(QIcon(":/images/Tic-Tac-Toe-Game-256.png"));
    setPoleRemisu(QIcon(":/images/Tic-Tac-Toe-Game-grey-256.png"));
    setIkonaZwyciezaGraczCzerwony(QPixmap(":/images/Tic-Tac-Toe-Game-red-256.png"));
    setIkonaZwyciezaGraczNiebieski(QPixmap(":/images/Tic-Tac-Toe-Game-256.png"));
}

void Widget::generujPlansze()
{
    for(int wiersz=1; wiersz<=30; wiersz++)
    {
        for(int kolumna=1; kolumna<=40; kolumna++)
        {
            int indeks;
            indeks = (wiersz-1)*40+(kolumna-1);
            polePlanszy[indeks] = new QPushButton(this);
            polePlanszy[indeks]->setGeometry((kolumna-1)*25+10,(wiersz-1)*25+10,25,25);
            polePlanszy[indeks]->setIconSize(QSize(25,25));
            polePlanszy[indeks]->setCheckable(true);
            polePlanszy[indeks]->setChecked(false);
        }
    }
    ui->nowaRunda->setVisible(true);

}

void Widget::generujPolaczenia()
{
    for(int wiersz=1; wiersz<=30; wiersz++)
    {
        for(int kolumna=1; kolumna<=40; kolumna++)
        {
            connect(getPolePlanszy(wiersz,kolumna),SIGNAL(clicked()),this,SLOT(wykonajRuch()));
        }
    }
}

void Widget::ustawPolePlanszy()
{
    QPushButton* pole = dynamic_cast <QPushButton*> (QObject::sender());
    if(pole->isChecked())
    {
        const QString& gracz = getAktualnyGracz();
        if(gracz=="Czerwony")
        {
            pole->setIcon(getPoleGraczaCzerwonego());
        }
        if(gracz=="Niebieski")
        {
            pole->setIcon(QIcon(getPoleGraczaNiebieskiego()));
        }
        pole->setAccessibleDescription(gracz);

        int xPole;
        int yPole;
        xPole = pole->geometry().left();
        yPole = pole->geometry().top();
        int wiersz;
        int kolumna;
        wiersz = (yPole-10)/25+1;
        kolumna = (xPole-10)/25+1;

        ui->lcdWspolrzednaX->display(kolumna);
        ui->lcdWspolrzednaY->display(wiersz);

        if(sprawdzWynikGry(wiersz, kolumna)==true)
        {
            koniecRundy();
        } else zmienAktualnegoGracza();

    }
    if(!pole->isChecked()) pole->setChecked(true);

}

void Widget::wyszarzPolaPlanszy()
{
    for (int wiersz=1; wiersz<=30; wiersz++)
    {
        for (int kolumna=1; kolumna<=40; kolumna++)
        {
            QPushButton* pole = getPolePlanszy(wiersz, kolumna);
            if(pole->accessibleDescription()!="")
            {
                pole->setIcon(getPoleRemisu());
            }

        }
    }
}

bool Widget::sprawdzWynikGry(const int& wiersz, const int& kolumna)
{      
    bool zwyciestwo=false;
    int zaznaczonePola;
    zaznaczonePola=0;

    for (int j=0; j<=4; j++)
    {
        zaznaczonePola=0;
        for (int i=1+j; i<=5+j; i++)
        {
            if((kolumna-4)>=1 && (kolumna+4)<=40)
            {
                if(getPolePlanszy(wiersz, kolumna-5+i)->accessibleDescription()==getAktualnyGracz()) zaznaczonePola+=1;
            }
            if(zaznaczonePola==5)
            {
                zwyciestwo=true;
                // zerowanie accesibleDescription pól wygrywających, aby nie zostały wyszarzone przez metodę wyszarzPolaPlanszy()
                for (int k=i-4; k<=i; k++)
                {
                    getPolePlanszy(wiersz, kolumna-5+k)->setAccessibleDescription("");
                }
            }
        }
    }

    if(zwyciestwo==false)
    {
        for (int j=0; j<=4; j++)
        {
            zaznaczonePola=0;
            for (int i=1+j; i<=5+j; i++)
            {
                if((wiersz-4)>=1 && (wiersz+4)<=30)
                {
                    if(getPolePlanszy(wiersz-5+i, kolumna)->accessibleDescription()==getAktualnyGracz()) zaznaczonePola+=1;
                }
                if(zaznaczonePola==5)
                {
                    zwyciestwo=true;
                    // zerowanie accesibleDescription pól wygrywających, aby nie zostały wyszarzone przez metodę wyszarzPolaPlanszy()
                    for (int k=i-4; k<=i; k++)
                    {
                        getPolePlanszy(wiersz-5+k, kolumna)->setAccessibleDescription("");
                    }

                }
            }
        }
    }

    if(zwyciestwo==false)
    {
        for (int j=0; j<=4; j++)
        {
            zaznaczonePola=0;
            for (int i=1+j; i<=5+j; i++)
            {
               if((wiersz-4)>=1 && (wiersz+4)<=30 && (kolumna-4)>=1 && (kolumna+4)<=40)
                {
                    if(getPolePlanszy(wiersz-5+i, kolumna-5+i)->accessibleDescription()==getAktualnyGracz()) zaznaczonePola+=1;
                }
                if(zaznaczonePola==5)
                {
                    zwyciestwo=true;
                    // zerowanie accesibleDescription pól wygrywających, aby nie zostały wyszarzone przez metodę wyszarzPolaPlanszy()
                    for (int k=i-4; k<=i; k++)
                    {
                        getPolePlanszy(wiersz-5+k, kolumna-5+k)->setAccessibleDescription("");
                    }
                }
            }
        }
    }

    if(zwyciestwo==false)
    {
        for (int j=0; j<=4; j++)
        {
            zaznaczonePola=0;
            for (int i=1+j; i<=5+j; i++)
            {
               if((wiersz-4)>=1 && (wiersz+4)<=30 && (kolumna-4)>=1 && (kolumna+4)<=40)
                {
                    if(getPolePlanszy(wiersz+5-i, kolumna-5+i)->accessibleDescription()==getAktualnyGracz()) zaznaczonePola+=1;
                }
                if(zaznaczonePola==5)
                {
                    zwyciestwo=true;
                    // zerowanie accesibleDescription pól wygrywających, aby nie zostały wyszarzone przez metodę wyszarzPolaPlanszy()
                    for (int k=i-4; k<=i; k++)
                    {
                        getPolePlanszy(wiersz+5-k, kolumna-5+k)->setAccessibleDescription("");
                    }
                }
            }
        }
    }
    return zwyciestwo;
}

void Widget::koniecRundy()
{
    ui->ruchGracza->setText("<p align='center'><span style= 'font-size:14pt; font-weight:600;'><b>Wygrywa:</b></span></p>");
    if(getAktualnyGracz()=="Czerwony")
    {
        ui->ruchGracza_3->setPixmap(getIkonaZwyciezaGraczCzerwony());
    }
    if(getAktualnyGracz()=="Niebieski")
    {
        ui->ruchGracza_3->setPixmap(getIkonaZwyciezaGraczNiebieski());
    }
    zaznaczWszystkiePola();
    ui->nowaRunda->setVisible(true);
    uaktualnijWynik();
    wyszarzPolaPlanszy();
}

void Widget::zaznaczWszystkiePola()
{
    for (int wiersz=1; wiersz<=30; wiersz++)
    {
        for (int kolumna=1; kolumna<=40; kolumna++)
        {
            getPolePlanszy(wiersz, kolumna)->setChecked(true);
        }
    }
}

void Widget::uaktualnijWynik()
{
    if(getAktualnyGracz()=="Czerwony")
    {
        int aktualnyWynik = ui->lcdWynikCzerwony->value();
        ui->lcdWynikCzerwony->display(aktualnyWynik+1);
    }
    if(getAktualnyGracz()=="Niebieski")
    {
        int aktualnyWynik = ui->lcdWynikNiebieski->value();
        ui->lcdWynikNiebieski->display(aktualnyWynik+1);
    }
}

//slots

void Widget::wykonajRuch()
{
    ustawPolePlanszy();

}

void Widget::nowaRunda()
{
    for (int wiersz=1; wiersz<=30; wiersz++)
    {
        for (int kolumna=1; kolumna<=40; kolumna++)
        {
            QPushButton* pole = getPolePlanszy(wiersz, kolumna);
            pole->setAccessibleDescription("");
            pole->setIcon(QIcon());
            pole->setChecked(false);

        }
    }
    ui->ruchGracza->setText("<p align='center'><span style= 'font-size:14pt; font-weight:600;'><b>Ruch gracza:</b></span></p>");
    zmienAktualnegoGracza();
}

//signals

void Widget::on_nowaRunda_clicked()
{
    nowaRunda();
}
