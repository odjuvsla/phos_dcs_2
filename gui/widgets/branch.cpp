#include "branch.h"
#include "feecard.h"
#include <QFrame>
#include "QDebug"

branch::branch( Branch_t branchId, QWidget* parent, Qt::WindowFlags f ) : QWidget ( parent, f )
,_branch(branchId)
,_feeCards(0)
,_kWidth(800)
,_kHeight(400)
{
  setFixedSize(_kWidth, _kHeight);
  setupWidgets();
}

branch::~branch()
{
  
}

void branch::setupWidgets()
{
  _frame = new QFrame(this);
  _frame->setFrameShadow(QFrame::Raised);
  _frame->setFrameShape(QFrame::StyledPanel);
  _frame->setFixedSize(CARDS_PER_BRANCH*15+40, 110);
        
  for(int c = 0; c < CARDS_PER_BRANCH; c++)
  {
    Fec_t cardId(c+1, _branch.getBranchId(), _branch.getRcuId(), _branch.getModuleId());
    feeCard *card = new feeCard(cardId, this);
    card->setGeometry(20+c*15, 10);
  }
}

#include "branch.moc"