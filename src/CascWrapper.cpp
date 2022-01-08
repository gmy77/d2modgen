/*
 * Copyright (C) 2022 Smirnov Vladimir / mapron1@gmail.com
 * SPDX-License-Identifier: MIT
 * See LICENSE file for details.
 */
#include "CascLib.h"
#include "StormLib.h"

#include "CascWrapper.hpp"

#include "Utils.hpp"

bool ExtractTables(const QString& d2rpath, TableSet& tableSet)
{
    const std::string utf8path = d2rpath.toStdString();
    HANDLE            storage;
    if (!CascOpenStorage(utf8path.c_str(), 0, &storage))
        return false;
    MODGEN_SCOPE_EXIT([storage] { CascCloseStorage(storage); });

    //    {
    //        CASC_FIND_DATA findData;
    //        HANDLE findHandle = CascFindFirstFile(storage, "*.txt", &findData, nullptr);
    //        if (findHandle == INVALID_HANDLE_VALUE)
    //            return false;
    //        return false;
    //    }

    for (const QString& id : g_tableNames) {
        const std::string fullId = QString("data:data\\global\\excel\\%1.txt").arg(id).toStdString();
        HANDLE            fileHandle;

        if (!CascOpenFile(storage, fullId.c_str(), CASC_LOCALE_ALL, 0, &fileHandle)) {
            qWarning() << "failed to open:" << fullId.c_str();
            return false;
        }
        MODGEN_SCOPE_EXIT([fileHandle] { CascCloseFile(fileHandle); });

        auto       dataSize = CascGetFileSize(fileHandle, nullptr);
        QByteArray buffer;
        buffer.resize(dataSize);
        DWORD wread;
        if (!CascReadFile(fileHandle, buffer.data(), dataSize, &wread)) {
            qWarning() << "failed to read:" << fullId.c_str();
            return false;
        }

        QString data = QString::fromUtf8(buffer);
        Table   table;
        table.id = id;
        if (!readCSV(data, table)) {
            qWarning() << "failed to parse:" << fullId.c_str();
            return false;
        }

        tableSet.tables[id] = std::move(table);
    }
    if (tableSet.tables.empty())
        return false;

    return true;
}

bool ExtractTablesLegacy(const QString& d2rpath, TableSet& tableSet)
{
    const std::string utf8path = d2rpath.toStdString() + "patch_d2.mpq";
    HANDLE            mpq;
    if (!SFileOpenArchive(utf8path.c_str(), 0, STREAM_FLAG_READ_ONLY, &mpq))
        return false;

    MODGEN_SCOPE_EXIT([mpq] { SFileCloseArchive(mpq); });
    for (const QString& id : g_tableNames) {
        const std::string fullId = QString("data\\global\\excel\\%1.txt").arg(id).toStdString();
        if (!SFileHasFile(mpq, fullId.c_str()))
            continue;

        HANDLE fileHandle;
        if (!SFileOpenFileEx(mpq, fullId.c_str(), SFILE_OPEN_FROM_MPQ, &fileHandle)) {
            qWarning() << "failed to open:" << fullId.c_str();
            return false;
        }
        MODGEN_SCOPE_EXIT([fileHandle] { SFileCloseFile(fileHandle); });

        auto       dataSize = SFileGetFileSize(fileHandle, nullptr);
        QByteArray buffer;
        buffer.resize(dataSize);
        DWORD wread;
        if (!SFileReadFile(fileHandle, buffer.data(), dataSize, &wread, nullptr)) {
            qWarning() << "failed to read:" << fullId.c_str();
            return false;
        }

        QString data = QString::fromUtf8(buffer);
        Table   table;
        table.id = id;
        if (!readCSV(data, table)) {
            qWarning() << "failed to parse:" << fullId.c_str();
            return false;
        }

        tableSet.tables[id] = std::move(table);
    }
    if (tableSet.tables.empty())
        return false;

    return true;
}
