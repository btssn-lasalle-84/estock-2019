#ifndef CASIER_H
#define CASIER_H

#include <QtWidgets>

class Casier : public QLabel
{
    Q_OBJECT
public:
    Casier(int numero, bool autorise=true, bool present=true, QWidget *parent=0);
    ~Casier();
    void mousePressEvent(QMouseEvent *event);

    bool estAutorise() const;
    bool estOuvert() const;
    void actionner();
    void ouvrir();
    void fermer();

private:
    int numero;
    bool autorise;
    bool ouvert;

public slots:

signals:
      void clicked(int);
      void clicked();
};

#endif // CASIER_H
