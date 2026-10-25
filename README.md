# ![logo](https://raw.githubusercontent.com/azerothcore/azerothcore.github.io/master/images/logo-github.png) AzerothCore

# mod-polish-translation

🇵🇱 [Wersja polska](README.pl.md)

Polish translation of AzerothCore server-side texts (quests, NPC and item names, gossip, speech, books,
system messages) as a plain module: the server stays English and each account can switch to Polish.
Client-side texts (spells, zones, UI, fonts) are not part of this module.

> [!IMPORTANT]
> The module needs AzerothCore from 25 October 2026 or newer. It uses two core changes merged in October
> 2026: a module can register its own locale and move a session to it
> (`WorldSession::SetSessionDbLocaleIndex()`, table `acore_string_locale`). On an older core it does not
> compile.

The files in `data/sql/` are generated; do not edit them by hand.

## Install

```bash
cd <azerothcore>/modules
git clone https://github.com/nolt/mod-polish-translation.git
# re-run cmake and build as usual; the worldserver applies data/sql/ on the next start
```

Updating AzerothCore stays `git pull` plus a rebuild: the module lives in `modules/`, which the core ignores.

## Own locale

The client has no Polish locale, so the module registers its own while the server starts: **plPL**. It takes
a free slot after the nine client locales (`localeNames`) and the core loads the rows with that name like
those of any other language.

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

## Fully Polish client

The module translates only what the server sends. For a fully Polish client (spells, zones, interface,
fonts with Polish letters) download [polish-client-builder](https://github.com/nolt/polish-client-builder/releases/latest).
It builds the translation on the player's computer from their own client files, and the client it
produces sends `.polski on` by itself.

## Remove

Delete the module directory and rebuild. The Polish rows stay in the tables, but without the module nobody
registers `plPL` and the core skips them.

## License

Copyright (c) 2026 Nolt.

The module, code and Polish texts alike, is free software under the GNU General Public License, version 2
or (at your option) any later version, the license of AzerothCore itself; see `LICENSE`. Copies and
derived works have to keep this notice and stay under the same license.

Original author: [Nolt](https://github.com/nolt).
