/*
 * Copyright (C) 2026 Nolt
 *
 * This program is free software; you can redistribute it and/or modify it under the terms of the
 * GNU General Public License as published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version. See the file LICENSE.
 */

/*
 * mod-polish-translation: lets an account switch the database texts to Polish.
 *
 * The client has no Polish locale, so the module registers one in the core ("plPL"), the Polish texts
 * are stored under that name and a session is moved to that locale when its account asked for it. The
 * server stays English for everybody else.
 */

#include "Chat.h"
#include "CommandScript.h"
#include "DatabaseEnv.h"
#include "Log.h"
#include "Player.h"
#include "ScriptMgr.h"
#include "WorldSession.h"
#include <mutex>
#include <unordered_map>
#include <unordered_set>

using namespace Acore::ChatCommands;

namespace
{
    Optional<LocaleConstant> polishLocale; // registered when the scripts are loaded

    std::mutex accountsLock;
    std::unordered_set<uint32> polishAccounts;                  // accounts with Polish switched on
    std::unordered_map<uint32, LocaleConstant> originalLocales; // locale of the session before the switch

    bool IsPolishAccount(uint32 accountId)
    {
        std::lock_guard<std::mutex> guard(accountsLock);
        return polishAccounts.find(accountId) != polishAccounts.end();
    }

    void SetSessionLocale(WorldSession* session, bool polish)
    {
        if (!polishLocale)
            return;

        LocaleConstant locale = session->GetSessionDbLocaleIndex();
        std::lock_guard<std::mutex> guard(accountsLock);
        if (polish)
        {
            if (locale != *polishLocale)
                originalLocales[session->GetAccountId()] = locale;

            session->SetSessionDbLocaleIndex(*polishLocale);
            return;
        }

        if (locale != *polishLocale)
            return;

        auto itr = originalLocales.find(session->GetAccountId());
        session->SetSessionDbLocaleIndex(itr != originalLocales.end() ? itr->second : session->GetSessionDbcLocale());
    }
}

class mod_polish_translation_world : public WorldScript
{
public:
    mod_polish_translation_world() : WorldScript("mod_polish_translation_world") { }

    void OnStartup() override
    {
        QueryResult result = LoginDatabase.Query("SELECT `account` FROM `mod_polish_translation_account`");
        std::lock_guard<std::mutex> guard(accountsLock);
        polishAccounts.clear();
        if (result)
        {
            do
            {
                polishAccounts.insert((*result)[0].Get<uint32>());
            } while (result->NextRow());
        }

        LOG_INFO("server.loading", ">> mod-polish-translation: {} accounts with Polish texts", polishAccounts.size());
    }
};

class mod_polish_translation_player : public PlayerScript
{
public:
    mod_polish_translation_player() : PlayerScript("mod_polish_translation_player", { PLAYERHOOK_ON_LOGIN }) { }

    void OnPlayerLogin(Player* player) override
    {
        WorldSession* session = player->GetSession();
        if (IsPolishAccount(session->GetAccountId()))
            SetSessionLocale(session, true);
    }
};

class mod_polish_translation_commandscript : public CommandScript
{
public:
    mod_polish_translation_commandscript() : CommandScript("mod_polish_translation_commandscript") { }

    ChatCommandTable GetCommands() const override
    {
        static ChatCommandTable commandTable =
        {
            { "polski", HandlePolskiCommand, SEC_PLAYER, Console::No }
        };
        return commandTable;
    }

    // ".polski on|off". A client may send it on every login, so it only answers when something changes.
    static bool HandlePolskiCommand(ChatHandler* handler, bool enable)
    {
        WorldSession* session = handler->GetSession();
        uint32 accountId = session->GetAccountId();
        if (IsPolishAccount(accountId) == enable)
        {
            SetSessionLocale(session, enable);
            return true;
        }

        {
            std::lock_guard<std::mutex> guard(accountsLock);
            if (enable)
                polishAccounts.insert(accountId);
            else
                polishAccounts.erase(accountId);
        }

        if (enable)
            LoginDatabase.Execute("REPLACE INTO `mod_polish_translation_account` (`account`) VALUES ({})", accountId);
        else
            LoginDatabase.Execute("DELETE FROM `mod_polish_translation_account` WHERE `account` = {}", accountId);

        SetSessionLocale(session, enable);
        if (enable)
            handler->SendSysMessage("Polskie teksty serwera włączone. Nazwy, które klient już zapamiętał, zmienią się po wyczyszczeniu folderu Cache.");
        else
            handler->SendSysMessage("Polish server texts are off. Names the client already cached change after the Cache folder is cleared.");

        return true;
    }
};

void AddSC_mod_polish_translation()
{
    // before the world loads the *_locale tables, so the rows with locale = 'plPL' are picked up
    polishLocale = RegisterCustomLocale("plPL");
    if (!polishLocale)
        LOG_ERROR("server.loading", "mod-polish-translation: the core has no free locale left, Polish texts are off");

    new mod_polish_translation_world();
    new mod_polish_translation_player();
    new mod_polish_translation_commandscript();
}
