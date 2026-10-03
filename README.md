# ![logo](https://raw.githubusercontent.com/azerothcore/azerothcore.github.io/master/images/logo-github.png) AzerothCore

# mod-polish-translation

🇵🇱 [Wersja polska](README.pl.md)

Polish translation of AzerothCore server-side texts (quests, NPC and item names, gossip, speech, books,
system messages) as a plain module: no core changes, the server stays English and each account can switch
to Polish. Client-side texts (spells, zones, UI, fonts) are not part of this module.

The files in `data/sql/` are generated; do not edit them by hand.

## Install

```bash
cd <azerothcore>/modules
git clone https://github.com/nolt/mod-polish-translation.git
# re-run cmake and build as usual; the worldserver applies data/sql/ on the next start
```

Updating AzerothCore stays `git pull` plus a rebuild: the module lives in `modules/`, which the core ignores.

## Borrowed locale slot

The core has a fixed list of nine locales (`LocaleConstant`) and a module cannot add one, so the Polish
texts are stored in the slot of a locale the server does not use: **koKR**.

- `data/sql/db-world/zz_pl_0_clear.sql` removes the Korean rows shipped with AzerothCore from the locale
  tables (otherwise Korean would show wherever there is no Polish text). English is untouched: it is the base
  text in other tables.
- `data/sql/db-world/zz_pl_<zone>.sql` insert the Polish rows with `locale = 'koKR'`, in the form of
  AzerothCore update files (`DELETE` by key, multi-row `INSERT`).
- A player with a real Korean client would get Polish texts. A core update may add a Korean row now and then;
  it shows only where the module has no text for that row.

## Switching to Polish

`.polski on` / `.polski off` in the chat, for every player. The choice is stored per account
(`mod_polish_translation_account` in the auth database) and works at once: the module moves the session to
the borrowed slot (`src/mod_polish_translation.cpp`).

A client can send the command itself when a character enters the world (an addon, for example), which is
why it stays silent when nothing changes. After a switch the client keeps names it already cached until its
`Cache` folder is cleared.

The session locale is a private member of the core (`WorldSession::m_sessionDbLocaleIndex`); the module
reaches it without touching the core. If the core ever renames it, the module stops compiling and the name
in `src/mod_polish_translation.cpp` has to follow.

## Remove

Delete the module directory and rebuild. The Polish rows stay in the koKR slot but nobody is moved to it;
to get the Korean rows back, re-import the world database.

## License

Copyright (c) 2026 Nolt.

The module, code and Polish texts alike, is free software under the GNU General Public License, version 2
or (at your option) any later version, the license of AzerothCore itself; see `LICENSE`. Copies and
derived works have to keep this notice and stay under the same license.

Original author: [Nolt](https://github.com/nolt).
