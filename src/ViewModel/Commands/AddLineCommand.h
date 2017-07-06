//
// Created by Raye on 2017/7/6.
//

#ifndef MINIPHOTOSHOP_ADDLINECOMMAND_H
#define MINIPHOTOSHOP_ADDLINECOMMAND_H

#include "../../Common/BaseCommand.h"
#include "../../Model/Model.h"

class AddLineCommand : public BaseCommand {
public:
    AddLineCommand(const shared_ptr<Model> &pModel):pModel(pModel){}

    void setPModel(const shared_ptr<Model> &pModel);

    void exec() {
        pModel->addLine();
    }

private:
    shared_ptr<Model> pModel;
};


#endif //MINIPHOTOSHOP_ADDLINECOMMAND_H
