#include <QApplication>
#include "REPO/melodiiRepo.h"
#include "SERVICE/melodiiService.h"
#include "GUI/MelodiiGUI.h"
#include "TESTE/teste.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    Teste t;
    t.ruleazaToateTestele();
    MelodieRepo repo{"C:\\Users\\PPK\\Desktop\\info\\semestrul 2\\OOP\\EXAMENFINALSESIUNE\\melodii.txt"};
    MelodieService srv{repo};
    MelodieGUI gui{srv};

    gui.setWindowTitle("Manager Melodii");
    gui.resize(900, 500);
    gui.show();

    return a.exec();
}