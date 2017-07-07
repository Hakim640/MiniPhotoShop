#include "View/mainwindow.h"
#include "Constants.h"
#include <QApplication>
#include <src/ViewModel/ViewModel.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    shared_ptr<Model> pModel(new Model);
    shared_ptr<ViewModel> pViewModel(new ViewModel(pModel));
    shared_ptr<MainWindow> pMainWindows(new MainWindow);

    //add viewModel to the observer list of model
    pModel->addObserver(pViewModel);
    //add view to the observer list of viewModel.
    pViewModel->addObserver(pMainWindows);

    //bind the commands
    pMainWindows->setAddLineCommand(pViewModel->getAddLineCommand());

    return a.exec();
}