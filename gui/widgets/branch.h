#ifndef BRANCH_H
#define BRANCH_H

#include <QtGui/qwidget.h>
#include <phosdcstypes.h>

class QLabel;
class QFrame;
class feeCard;

class branch : public QWidget
{

  Q_OBJECT
    
public:
    /** Constructor */
    explicit branch ( Branch_t branchId, QWidget* parent = 0, Qt::WindowFlags f = 0 );

    /** Destructor */
    virtual ~branch();

    void setGeometry(int x, int y) { QWidget::setGeometry(x, y, _kWidth, _kHeight);}

private:

  /** Setup the internal widgets */
  void setupWidgets();
  
  /** Branch id */
  Branch_t _branch;
  
  /** The FECs */
  QVector<feeCard*> _feeCards;

  /** The frame */
  QFrame *_frame;

  /** The label */
  QLabel *_label;
  
  const int _kWidth;
  const int _kHeight;

  
};

#endif // BRANCH_H
