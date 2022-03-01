/*
 * Copyright (C) 2022 Smirnov Vladimir / mapron1@gmail.com
 * SPDX-License-Identifier: MIT
 * See LICENSE file for details.
 */
#include "ConfigPageCharacter.hpp"

namespace D2ModGen {

namespace {
const bool s_init = pageRegisterHelper<ConfigPageCharacter>();
}

ConfigPageCharacter::ConfigPageCharacter(QWidget* parent)
    : ConfigPageAbstract(parent)
{
    initModule();
    addEditors(QList<IValueWidget*>()
               << makeEditor("addCube", tr("Add Horadric Cube as starting item"))
               << makeEditor("idTome", tr("Replace ID scroll with ID tome"))
               << makeEditor("manaPots", tr("Replace starting Health pots with Mana"))
               << makeEditor("statPerLevel", tr("Stat points gain per level"))
               << makeEditor("skillPerLevel", tr("Skill points gain per level (D2R only!)"))
               << makeEditor("statLower", tr("Lower Strength/Dexterity requirements on items, %"))
               << makeEditor("mercHP", tr("Change mercenaries Health, multiply by"))
               << makeEditor("mercDam", tr("Change mercenaries Damage, multiply by")));
    closeLayout();
}

QString ConfigPageCharacter::pageHelp() const
{
    return tr("First three options allow you to change starting items for characters: \n"
              "add Cube, replace id scroll with Tome (useful for No-town runs), and replace health with mana potions. \n"
              "Next two sliders allow you to change how many skill and stat poits you get on levelup. \n "
              "Last slider allow you to lower Strength and Dexterity requirements on all items.  ");
}

}
