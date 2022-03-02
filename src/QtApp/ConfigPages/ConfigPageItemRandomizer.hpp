/*
 * Copyright (C) 2022 Smirnov Vladimir / mapron1@gmail.com
 * SPDX-License-Identifier: MIT
 * See LICENSE file for details.
 */
#pragma once

#include "ConfigPageAbstract.hpp"
#include "AttributeHelper.hpp"

namespace D2ModGen {

class ConfigPageItemRandomizer : public ConfigPageAbstract {
    Q_OBJECT
public:
    static constexpr const std::string_view key = IModule::Key::itemRandomizer;

    ConfigPageItemRandomizer(const IModule::Ptr& module, QWidget* parent);

    // IConfigPage interface
public:
    QString caption() const override
    {
        return tr("Item Randomizer");
    }
    QString                 pageHelp() const override;
    IConfigPage::PresetList pagePresets() const override;

    QMap<std::string, QString> widgetTitles() const override;
    QMap<std::string, QString> widgetHelps() const override;
};

}
