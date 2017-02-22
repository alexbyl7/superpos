#include "drawer.h"
#include <iostream>

using namespace std;

Drawer::Drawer():
  item(NULL)
{
}

Drawer::~Drawer()
{

}

void Drawer::init()
{
  scene.setSceneRect(-3000, -3000, 6000, 6000);

  opacity[0] = opacity[1] = 0.5;

 locators[0].init(QPointF( 363.8,  272.7 * -1), 0);
 locators[1].init(QPointF(-566.4, -352.4 * -1), 0);

 // locators[0].init(QPointF(0, 0), 0);
 // locators[1].init(QPointF(0, 0), 0);

  locators[0].addBackground("/windows/Work/IANS/polinom/Эксперименты_10_6хРЛС/2_250316/RLS_1_fileRLS_FFT_001.b");
  locators[1].addBackground("/windows/Work/IANS/polinom/Эксперименты_10_6хРЛС/2_250316/RLS_4_fileRLS_FFT_001.b");

  for (int i = 0; i < LOCATORS_NUM; ++i)
    locators[i].updatePixmap();

  targets.push_back(Target(QPointF(281.51, -256.59),
                           QPointF((-458.44-281.51) / 50,  (54.49+256.59) / 50)));

  time.start();

  emit updateScreen();
}

void Drawer::process()
{
  QPointF crd = targets[0].getCoords(0.001*time.elapsed());

  scene.clear();

  // Фоновая обстановка по данным локаторов:
  for (int i = 0; i < LOCATORS_NUM; ++i) {
    pixmap = locators[i].getPixmap();
    QGraphicsItem *itemPixmap = scene.addPixmap(pixmap);
    itemPixmap->setOpacity(opacity[i]);
    //itemPixmap->setFlag(QGraphicsItem::ItemIsMovable);
    itemPixmap->setTransformOriginPoint(QPointF(pixmap.width()/2, pixmap.height()/2));
    itemPixmap->setPos(locators[i].getCenter() - QPointF(pixmap.width()/2, pixmap.height()/2));
    itemPixmap->setRotation(locators[i].getAngle0());

    // Для контроля масштабов:
    /*  scene.addEllipse(locators[i].getCenter().x() - 1000*0.79,
                     locators[i].getCenter().y() - 1000*0.79,
                     2000*0.79, 2000*0.79, QPen(Qt::red, 2));
    */
  }

  // Центр (КПА)
  scene.addEllipse(-5, -5, 10, 10, QPen(Qt::red, 5));
  // ВПП
  scene.addLine(QLineF(QPointF(281.51, 54.49 * -1),
                       QPointF(-458.44, -256.59 * -1)),
                QPen(Qt::cyan, 5));

#if 0
  // Текущее направление локаторов:
  for (int i = 0; i < LOCATORS_NUM; ++i) {
    QPointF cnt = locators[i].getCenter();
    double phi = locators[i].getNextPhi();

    // cout << phi << " ";
    // if (i == 1) cout << endl;

    double L = DISCR_NUM * METERS_IN_DISCR;
    QGraphicsItem *itemLine = scene.addLine(QLineF(0,0, L,0),
                                            QPen(Qt::green, 10));
    itemLine->setPos(cnt);
    itemLine->setRotation(phi);
  }

  // Цель:
  item = scene.addEllipse(-20, -20, 40,40, QPen(), QBrush(Qt::white));
  item->setPos(crd);
#endif

  emit updateScreen();
}
