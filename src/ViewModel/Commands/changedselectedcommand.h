#ifndef CHANGEDSELECTEDCOMMAND_H
#define CHANGEDSELECTEDCOMMAND_H

#include "../../Common/BaseCommand.h"
#include "../../Model/Model.h"

class ChangedSelectedCommand : public BaseCommand {
public:
    ChangeSelectedCommand(const shared_ptr<Model> &pModel,const shared_ptr<ViewModel> &pViewModel) : BaseCommand(pModel,pViewModel) {}

    void exec() {
        vector<int> ints=params.getInts();
        pViewModel->SetSelectedLayout(ints[0]);
    }
};

#endif // CHANGEDSELECTEDCOMMAND_H