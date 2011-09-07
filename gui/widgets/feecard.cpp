#include "feecard.h"

feeCard::feeCard (Fec_t card, QWidget* parent) : QPushButton ( parent )
,fFecId(card)
,_kWidth(20)
,_kHeight(100)
{
  setFixedHeight(80);
  setFixedWidth(15);
  QString hexId;
  hexId = hexId.setNum(card.getFecId(), 16);
  setText(hexId.toUpper());
}

feeCard::~feeCard()
{

}


#include "feecard.moc"
