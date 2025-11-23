// SPDX-FileCopyrightText: 2025 Sergio Martins
// SPDX-License-Identifier: MIT

#include "qt_utils.h"

#include <QtCore>

int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);

    debug_utils::log_to_file("works");
    debug_utils::log_to_file("works1");

    return app.exec();
}
