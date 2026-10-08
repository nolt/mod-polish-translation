# ![logo](https://raw.githubusercontent.com/azerothcore/azerothcore.github.io/master/images/logo-github.png) AzerothCore

# mod-polish-translation

🇵🇱 [Wersja polska](README.pl.md)

Polish translation of AzerothCore server-side texts (quests, NPC and item names, gossip, speech, books,
system messages) as a plain module: the server stays English and each account can switch to Polish.
Client-side texts (spells, zones, UI, fonts) are not part of this module.

> [!IMPORTANT]
> This branch (`dev-next`) needs a core that lets modules register their own locale
> (`RegisterCustomLocale()`, `WorldSession::SetSessionDbLocaleIndex()`, table `acore_string_locale`).
> That change is proposed in AzerothCore pull request 27958 and is not merged yet, so on a stock
> AzerothCore this branch does not compile. Use the `main` branch there: it works without core changes and
> keeps the Polish texts in the borrowed `koKR` slot.

The files in `data/sql/` are generated; do not edit them by hand.

## Install

```bash
cd <azerothcore>/modules
git clone -b dev-next https://github.com/nolt/mod-polish-translation.git
# re-run cmake and build as usual; the worldserver applies data/sql/ on the next start
```

Updating AzerothCore stays `git pull` plus a rebuild: the module lives in `modules/`, which the core ignores.

## Own locale

The client has no Polish locale and the core has a fixed list of nine (`LocaleConstant`), so the module
registers its own while the server starts: **plPL**. The core gives it an index after the client locales and
loads the rows with that name like those of any other language.

- `data/sql/db-world/zz_pl_<zone>.sql` insert the Polish rows with `locale = 'plPL'`, in the form of
  AzerothCore update files (`DELETE` by key, multi-row `INSERT`). System messages go to
  `acore_string_locale`.
- No row of another language is touched, and a text without a Polish row is shown in English.
- A client cannot ask for this locale by itself; a session gets it only through the command below.

## Switching to Polish

`.polski on` / `.polski off` in the chat, for every player. The choice is stored per account
(`mod_polish_translation_account` in the auth database) and works at once: the module moves the session to
the registered locale (`src/mod_polish_translation.cpp`).

A client can send the command itself when a character enters the world (an addon, for example), which is
why it stays silent when nothing changes. After a switch the client keeps names it already cached until its
`Cache` folder is cleared.

## Moving from `main`

The `main` branch stores the Polish texts under `koKR` and removes the Korean rows shipped with
AzerothCore. This branch does not clean that up: the old rows stay under `koKR` (only a Korean client sees
them). For a clean state re-import the world database and let the worldserver apply `data/sql/` again.

## Remove

Delete the module directory and rebuild. The Polish rows stay in the tables, but without the module nobody
registers `plPL` and the core skips them.

## License

Copyright (c) 2026 Nolt.

The module, code and Polish texts alike, is free software under the GNU General Public License, version 2
or (at your option) any later version, the license of AzerothCore itself; see `LICENSE`. Copies and
derived works have to keep this notice and stay under the same license.

Original author: [Nolt](https://github.com/nolt).
