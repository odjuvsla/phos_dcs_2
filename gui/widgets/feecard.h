#ifndef FECCARD_H
#define FECCARD_H

#include <QPushButton>
#include "phosdcstypes.h"


class feeCard : public QPushButton
{
  Q_OBJECT
public:
  
  /** Constructor must pass FEC card definition */
  explicit feeCard (Fec_t card,  QWidget* parent = 0);
  
  virtual ~feeCard();
  
  void setGeometry(int x, int y) { QPushButton::setGeometry(x, y, _kWidth, _kHeight);}
  
private:

  /** FEC definition */
  Fec_t fFecId;
  
  /** Default constructor, prohibited */
  feeCard();

  const int _kWidth;
  const int _kHeight;
  
};

#endif // FECCARD_H
