# ![logo](https://raw.githubusercontent.com/azerothcore/azerothcore.github.io/master/images/logo-github.png) AzerothCore

# mod-polish-translation

🇬🇧 [English version](README.md)

Polskie tłumaczenie tekstów serwerowych AzerothCore (zadania, nazwy NPC i przedmiotów, dialogi i kwestie
NPC, książki, komunikaty systemowe) w postaci zwykłego modułu: serwer pozostaje angielski, a każde konto
może przełączyć się na polski. Teksty po stronie klienta (zaklęcia, strefy, interfejs, czcionki) nie
wchodzą w skład tego modułu.

> [!IMPORTANT]
> Moduł wymaga AzerothCore z 25 października 2026 lub nowszego. Korzysta z dwóch zmian w rdzeniu
> wciągniętych w październiku 2026: moduł może zarejestrować własny język i przełączyć na niego sesję
> (`WorldSession::SetSessionDbLocaleIndex()`, tabela `acore_string_locale`). Na starszym rdzeniu się nie
> skompiluje.

Pliki w `data/sql/` są generowane — nie edytuj ich ręcznie.

## Instalacja

```bash
cd <azerothcore>/modules
git clone https://github.com/nolt/mod-polish-translation.git
# uruchom ponownie cmake i zbuduj jak zwykle; worldserver wgra data/sql/ przy następnym starcie
```

Aktualizacja AzerothCore to nadal `git pull` i przebudowa: moduł leży w `modules/`, które rdzeń ignoruje.

## Własny język

Klient nie ma języka polskiego, dlatego moduł przy starcie serwera rejestruje własny: **plPL**. Zajmuje
wolny slot za dziewięcioma językami klienta (`localeNames`), a rdzeń wczytuje wiersze o tej nazwie tak samo
jak wiersze każdego innego języka.

- `data/sql/db-world/zz_pl_<zone>.sql` wstawiają polskie wiersze z `locale = 'plPL'`, w formie plików
  aktualizacji AzerothCore (`DELETE` po kluczu, wielowierszowy `INSERT`). Komunikaty systemowe trafiają
  do `acore_string_locale`.
- Wiersze innych języków pozostają nietknięte, a tekst bez polskiego wiersza wyświetla się po angielsku.
- Klient nie może sam poprosić o ten język; sesja dostaje go wyłącznie przez komendę opisaną niżej.

## Przełączanie na polski

`.polski on` / `.polski off` na czacie, dla każdego gracza. Wybór jest zapisywany dla konta
(`mod_polish_translation_account` w bazie auth) i działa natychmiast: moduł przełącza sesję na
zarejestrowany język (`src/mod_polish_translation.cpp`).

Klient może wysłać tę komendę sam, gdy postać wchodzi do świata (na przykład przez addon) — dlatego
komenda nic nie wypisuje, jeśli niczego nie zmienia. Po przełączeniu klient pamięta nazwy, które zdążył
zapisać, dopóki nie wyczyścisz folderu `Cache`.

## Klient w pełni po polsku

Moduł tłumaczy tylko to, co wysyła serwer. Żeby mieć klienta w pełni po polsku (zaklęcia, strefy,
interfejs, czcionki z polskimi literami), pobierz [polish-client-builder](https://github.com/nolt/polish-client-builder/releases/latest).
Program tworzy tłumaczenie na komputerze gracza z plików jego własnego klienta, a spolszczony klient sam
wysyła `.polski on`.

## Usuwanie

Usuń katalog modułu i przebuduj serwer. Polskie wiersze zostaną w tabelach, ale bez modułu nikt nie
rejestruje `plPL` i rdzeń je pomija.

## Licencja

Copyright (c) 2026 Nolt.

Moduł — zarówno kod, jak i polskie teksty — jest wolnym oprogramowaniem na licencji GNU General Public
License w wersji 2 lub (według uznania) dowolnej późniejszej, czyli na licencji samego AzerothCore;
zobacz `LICENSE`. Kopie i utwory zależne muszą zachować tę informację i pozostać na tej samej licencji.

Autor oryginału: [Nolt](https://github.com/nolt).
