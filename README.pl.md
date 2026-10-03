# ![logo](https://raw.githubusercontent.com/azerothcore/azerothcore.github.io/master/images/logo-github.png) AzerothCore

# mod-polish-translation

🇬🇧 [English version](README.md)

Polskie tłumaczenie tekstów serwerowych AzerothCore (zadania, nazwy NPC i przedmiotów, dialogi i kwestie
NPC, książki, komunikaty systemowe) w postaci zwykłego modułu: bez zmian w rdzeniu, serwer pozostaje
angielski, a każde konto może przełączyć się na polski. Teksty po stronie klienta (zaklęcia, strefy,
interfejs, czcionki) nie wchodzą w skład tego modułu.

Pliki w `data/sql/` są generowane — nie edytuj ich ręcznie.

## Instalacja

```bash
cd <azerothcore>/modules
git clone https://github.com/nolt/mod-polish-translation.git
# uruchom ponownie cmake i zbuduj jak zwykle; worldserver wgra data/sql/ przy następnym starcie
```

Aktualizacja AzerothCore to nadal `git pull` i przebudowa: moduł leży w `modules/`, które rdzeń ignoruje.

## Pożyczony slot języka

Rdzeń ma sztywną listę dziewięciu języków (`LocaleConstant`) i moduł nie może dodać kolejnego, dlatego
polskie teksty trafiają do slotu języka, którego serwer nie używa: **koKR**.

- `data/sql/db-world/zz_pl_0_clear.sql` usuwa z tabel tłumaczeń koreańskie wiersze dostarczane
  z AzerothCore (inaczej wszędzie tam, gdzie brakuje polskiego tekstu, pojawiałby się koreański).
  Angielski pozostaje nietknięty — to tekst bazowy, trzymany w innych tabelach.
- `data/sql/db-world/zz_pl_<zone>.sql` wstawiają polskie wiersze z `locale = 'koKR'`, w formie plików
  aktualizacji AzerothCore (`DELETE` po kluczu, wielowierszowy `INSERT`).
- Gracz z prawdziwym koreańskim klientem zobaczyłby polskie teksty. Aktualizacja rdzenia może od czasu
  do czasu dodać koreański wiersz; będzie on widoczny tylko tam, gdzie moduł nie ma własnego tekstu.

## Przełączanie na polski

`.polski on` / `.polski off` na czacie, dla każdego gracza. Wybór jest zapisywany dla konta
(`mod_polish_translation_account` w bazie auth) i działa natychmiast: moduł przełącza sesję na
pożyczony slot (`src/mod_polish_translation.cpp`).

Klient może wysłać tę komendę sam, gdy postać wchodzi do świata (na przykład przez addon) — dlatego
komenda nic nie wypisuje, jeśli niczego nie zmienia. Po przełączeniu klient pamięta nazwy, które zdążył
zapisać, dopóki nie wyczyścisz folderu `Cache`.

Język sesji to prywatne pole rdzenia (`WorldSession::m_sessionDbLocaleIndex`); moduł sięga do niego bez
modyfikowania rdzenia. Jeśli rdzeń kiedyś zmieni nazwę tego pola, moduł przestanie się kompilować
i trzeba będzie poprawić ją także w `src/mod_polish_translation.cpp`.

## Usuwanie

Usuń katalog modułu i przebuduj serwer. Polskie wiersze zostaną w slocie koKR, ale nikt nie będzie już
na niego przełączany; żeby odzyskać koreańskie wiersze, zaimportuj ponownie bazę world.

## Licencja

Copyright (c) 2026 Nolt.

Moduł — zarówno kod, jak i polskie teksty — jest wolnym oprogramowaniem na licencji GNU General Public
License w wersji 2 lub (według uznania) dowolnej późniejszej, czyli na licencji samego AzerothCore;
zobacz `LICENSE`. Kopie i utwory zależne muszą zachować tę informację i pozostać na tej samej licencji.

Autor oryginału: [Nolt](https://github.com/nolt).
