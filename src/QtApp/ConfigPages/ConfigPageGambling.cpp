/*
 * Copyright (C) 2022 Smirnov Vladimir / mapron1@gmail.com
 * SPDX-License-Identifier: MIT
 * See LICENSE file for details.
 */
#include "ConfigPageGambling.hpp"

namespace D2ModGen {

namespace {
const bool s_init = pageRegisterHelper<ConfigPageGambling>();
}

ConfigPageGambling::ConfigPageGambling(QWidget* parent)
    : ConfigPageAbstract(parent)
{
    initModule();
    addEditors(QList<IValueWidget*>()
               << makeEditor("charmGamble", tr("Allow gambling for charms and jewels (Legacy only)\nNote: crashes D2R - so enabled only for D2."))
               << makeEditor("ratioUnique", tr("Increase Unique chance, times<br>Note: you still can get a lot of failed uniques for no known reason."))
               << makeEditor("ratioSet", tr("Increase Set chance, times"))
               << makeEditor("ratioRare", tr("Increase Rare chance, times"))
               << makeEditor("ratioExc", tr("Increase Exceptional upgrade chance, times"))
               << makeEditor("ratioElite", tr("Increase Elite upgrade chance, times<br>Note: seems like Exc. check is done beforehead, so if it's high enough, elite won't generate.")));
    closeLayout();
}

QString ConfigPageGambling::pageHelp() const
{
    return tr("First option enables Charms in Gambling window, but only for D2 Legacy.\n"
              "Next sliders allow you increase basic chance of getting Unique/Rare/Set/High-quality item.  ");
}

}
