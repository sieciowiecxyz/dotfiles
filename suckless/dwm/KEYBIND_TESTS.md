# dwm keybind test matrix

Cel: każdy skrót z `config.h` ma opisany efekt i minimalny test. Testy są pisane pod ten build, nie pod vanilla dwm.

Założenia:
- `Mod` = `Super`.
- Testy manualne wykonuj na pustych tagach albo na testowych terminalach, żeby nie ruszać realnej pracy.
- Jeśli test używa zewnętrznego programu (`brave`, `thunar`, `wpctl`, `playerctl`, `brightnessctl`, `maim`, `scrot`, `xclip`), najpierw sprawdź `command -v PROGRAM`.
- Test statusbara wymaga działającego `dwmblocks`; test klików wymaga, żeby blok miał przypisany signal w `dwmblocks/config.h`.

## Nawigacja i stack

| Skrót | Efekt | Test |
| --- | --- | --- |
| `Mod+j` | fokus następnego okna w stacku | Otwórz 3 terminale, naciśnij skrót, aktywna ramka ma przejść na kolejne okno. |
| `Mod+k` | fokus poprzedniego okna w stacku | Otwórz 3 terminale, naciśnij skrót, aktywna ramka ma przejść na poprzednie okno. |
| `Mod+v` | fokus master/ostatnia pozycja według patcha stack | Otwórz 3 terminale, zmień fokus, naciśnij skrót, fokus ma skoczyć według zachowania `focusstack` z argumentem `0`. |
| `Mod+Shift+j` | przesuwa okno w dół stacka | Otwórz 3 terminale, zapamiętaj pozycję aktywnego, naciśnij skrót, układ okien ma się zmienić. |
| `Mod+Shift+k` | przesuwa okno w górę stacka | Jak wyżej, ale w przeciwnym kierunku. |
| `Mod+Shift+v` | przesuwa aktywne okno do pozycji master/0 | Otwórz 3 terminale, fokus na okno ze stacka, naciśnij skrót, aktywne okno ma trafić w pozycję master. |
| `Mod+Tab` | powrót do poprzedniego widoku tagów | Przejdź z taga 1 na 2, naciśnij skrót, powinien wrócić tag 1. |
| `Mod+Left` | fokus poprzedniego monitora | Na jednym monitorze brak widocznej zmiany; na dwóch monitorach fokus przechodzi na lewy/poprzedni. |
| `Mod+Right` | fokus następnego monitora | Na jednym monitorze brak widocznej zmiany; na dwóch monitorach fokus przechodzi na prawy/następny. |
| `Mod+Shift+Left` | przenosi aktywne okno na poprzedni monitor | Test tylko na multi-monitor: aktywne okno ma przejść na drugi monitor. |
| `Mod+Shift+Right` | przenosi aktywne okno na następny monitor | Test tylko na multi-monitor: aktywne okno ma przejść na drugi monitor. |

## Tagi

| Skrót | Efekt | Test |
| --- | --- | --- |
| `Mod+1` ... `Mod+9` | pokazuje tag 1-9 | Naciśnij każdy skrót, zaznaczony tag w barze ma się zmienić. |
| `Mod+Ctrl+1` ... `Mod+Ctrl+9` | dołącza/odłącza tag do aktualnego widoku | Na tagu 1 włącz `Mod+Ctrl+2`; bar powinien pokazać widok 1+2. Ponowne naciśnięcie odłącza 2. |
| `Mod+Shift+1` ... `Mod+Shift+9` | przenosi aktywne okno na tag 1-9 | Otwórz terminal, naciśnij skrót, okno znika z obecnego taga i pojawia się na wybranym. |

## Layouty i okna

| Skrót | Efekt | Test |
| --- | --- | --- |
| `Mod+t` | layout `tile` | Otwórz 3 terminale, naciśnij skrót, bar pokazuje `tile`, master po lewej. |
| `Mod+y` | layout `cols` | Otwórz 3 terminale, naciśnij skrót, bar pokazuje `cols`, okna są pionowymi kolumnami o podobnej szerokości. |
| `Mod+i` | layout `center` | Otwórz 3+ terminale, naciśnij skrót, master jest centralnie, stack po bokach. |
| `Mod+u` | layout `rows` | Otwórz 3 terminale, naciśnij skrót, bar pokazuje `rows`, master u góry, stack na dole. |
| `Mod+o` | layout `float` | Otwórz 2 terminale, naciśnij skrót, bar pokazuje `float`, okna nie są układane automatycznie. |
| `Mod+p` | zwiększa liczbę okien master | W `tile` z 3 terminalami naciśnij skrót, liczba okien w master ma wzrosnąć. |
| `Mod+Shift+p` | zmniejsza liczbę okien master | Po poprzednim teście naciśnij skrót, liczba okien master ma spaść. |
| `Mod+a` | przełącza gappy per-tag | Przy kilku oknach naciśnij skrót; defaultowo gapless, po przełączeniu mogą pojawić się aktualne wartości gapów dla tego taga. |
| `Mod+s` | przełącza sticky dla aktywnego okna | Aktywna ramka sticky ma dostać kolor `stickybordercolor`; po przejściu na inny tag okno zostaje widoczne. |
| `Mod+f` | fullscreen aktywnego okna | Aktywne okno zajmuje ekran; ponowne naciśnięcie wraca. |
| `Mod+h` | zmniejsza `mfact` | W `tile` master robi się węższy. |
| `Mod+l` | zwiększa `mfact` | W `tile` master robi się szerszy. |
| `Mod+space` | przełącza na następny layout | Naciskaj kilka razy; symbol layoutu cyklicznie się zmienia. |
| `Mod+Shift+space` | toggle floating aktywnego okna | Aktywne okno przechodzi w floating; ponowne naciśnięcie wraca do tilingu. |
| `Mod+q` | zamyka aktywne okno | Otwórz testowy terminal, naciśnij skrót, terminal ma się zamknąć. |
| `Mod+b` | pokazuje/ukrywa bar | Bar znika; ponowne naciśnięcie pokazuje bar. |
| `Mod+F5` | reload XRDB resources | Zmień testowo Xresources albo uruchom bez zmian; dwm nie powinien się zawiesić. |

## Scratchpady

| Skrót | Efekt | Test |
| --- | --- | --- |
| `Mod+'` | scratchpad kalkulatora `bc` | Otwiera floating terminal z `bc -lq`; ponowne naciśnięcie chowa/pokazuje. |
| `Mod+Shift+Enter` | scratchpad terminala | Otwiera floating terminal `spterm`; ponowne naciśnięcie chowa/pokazuje. |

## Launchery i codzienne

| Skrót | Efekt | Test |
| --- | --- | --- |
| `Mod+Return` | uruchamia terminal `st` | Terminal pojawia się na obecnym tagu. |
| `Mod+d` | uruchamia `dmenu_run` | Pasek dmenu ma mieć font/height spójny z dmenu buildem i bez tofu przy emoji w wynikach. |
| `Mod+grave` | uruchamia `dmenuunicode` | Menu emoji/symboli ma się pojawić; wybór kopiuje znak do clipboarda. |
| `Mod+w` | uruchamia Brave | `brave` startuje albo fokusuje istniejący proces zależnie od Brave. |
| `Mod+r` | uruchamia Thunar | `thunar` startuje. |
| `Mod+Backspace` | uruchamia `sysact` | Menu systemowe ma mieć emoji bez kwadratów; cancel nie robi nic. |
| `Mod+Shift+q` | uruchamia `sysact` | Ten sam test co `Mod+Backspace`. |

## Screenshoty

| Skrót | Efekt | Test |
| --- | --- | --- |
| `Print` | pełny screenshot przez `maim` | Jeśli `maim` istnieje, w katalogu roboczym pojawia się `pic-full-*.png`. |
| `Shift+Print` | zaznaczany screenshot przez `maim -s` | Jeśli `maim` istnieje, po zaznaczeniu obszaru pojawia się `pic-area-*.png`. |
| `Mod+Shift+s` | screenshot do clipboarda przez `scrot` + `xclip` | Jeśli `scrot` i `xclip` istnieją, zaznaczony obraz trafia do clipboarda. |

## Media i klawisze sprzętowe

| Skrót | Efekt | Test |
| --- | --- | --- |
| `Mod+,` | poprzedni track | Przy działającym playerze `playerctl metadata title` powinien zmienić utwór; blok media ma odświeżyć się od razu. |
| `Mod+.` | play/pause | `playerctl status` zmienia `Playing`/`Paused`; blok media ma zmienić ikonę `▶`/`⏸`. |
| `Mod+/` | następny track | Przy działającym playerze `playerctl metadata title` powinien zmienić utwór; blok media ma odświeżyć się od razu. |
| `Mod+-` | ciszej o 3% | `wpctl get-volume @DEFAULT_AUDIO_SINK@` ma spaść; blok volume ma odświeżyć się od razu. |
| `Mod+=` | głośniej o 3%, maksymalnie do 100% | Przy `Volume: 1.00` skrót nie może podbić powyżej `1.00`; używa `wpctl set-volume -l 1.0`. |
| `Mod+m` | mute/unmute output | `wpctl get-volume @DEFAULT_AUDIO_SINK@` zmienia stan mute; blok volume ma odświeżyć się od razu. |
| `Mod+Shift+m` | OS-level microphone kill switch | Wszystkie `pactl list short sources` bez `.monitor` mają przejść na `Mute: yes`; drugi raz mają wrócić na `Mute: no`; ma być notify + dźwięk. |
| `XF86 AudioMute` | mute output | `wpctl get-volume @DEFAULT_AUDIO_SINK@` przed/po ma pokazać zmianę mute. |
| `XF86 AudioRaiseVolume` | głośniej o 3%, maksymalnie do 100% | Przy `Volume: 1.00` skrót nie może podbić powyżej `1.00`; używa `wpctl set-volume -l 1.0`. |
| `XF86 AudioLowerVolume` | ciszej o 3% | `wpctl get-volume @DEFAULT_AUDIO_SINK@` ma spaść. |
| `XF86 AudioPrev` | poprzedni track | Przy działającym playerze `playerctl metadata title` powinien zmienić utwór. |
| `XF86 AudioNext` | następny track | Przy działającym playerze `playerctl metadata title` powinien zmienić utwór. |
| `XF86 AudioPause` | play/pause | `playerctl status` zmienia `Playing`/`Paused`. |
| `XF86 AudioPlay` | play/pause | Jak wyżej. |
| `XF86 AudioStop` | stop | `playerctl status` przechodzi w `Stopped` albo player kończy playback. |
| `XF86 AudioMicMute` | OS-level microphone kill switch | Jak `Mod+Shift+m`; używa `mic-kill-switch`, a nie tylko `@DEFAULT_AUDIO_SOURCE@`. |
| `XF86 Calculator` | kalkulator `bc` w terminalu | Otwiera terminal z `bc -lq`. |
| `XF86 WWW` | przeglądarka | Uruchamia Brave. |
| `XF86 DOS` | terminal | Uruchamia `st`. |
| `XF86 MonBrightnessUp` | jasność +1% | `brightnessctl get` rośnie. |
| `XF86 MonBrightnessDown` | jasność -1% | `brightnessctl get` maleje. |

## Terminal `st`

| Skrót | Efekt | Test |
| --- | --- | --- |
| `Ctrl+Shift+O` | kopiuje aktualny widok terminala do clipboarda | W oknie `st` z testowym tekstem skrót ustawia CLIPBOARD; `xclip -selection clipboard -o` pokazuje ten tekst. |
| `Ctrl+Shift+Esc` | keyboard_select | Umożliwia wybieranie tekstu klawiaturą, przydatne gdy mysza/scroll są niewygodne. |

## Mysz

| Akcja | Efekt | Test |
| --- | --- | --- |
| Klik lewy w symbol layoutu | następny layout | Kliknij symbol layoutu; nazwa layoutu zmienia się cyklicznie. |
| Klik prawy w symbol layoutu | `notify-send` z instrukcją layoutów | Pojawia się notyfikacja z listą layoutów. |
| Środkowy klik w tytuł okna | `zoom` | Aktywne okno zamienia się z master. |
| `Mod` + lewy przycisk na oknie | przesuwanie floating | Trzymając `Mod`, przeciągnij okno. |
| `Mod` + środkowy przycisk na oknie | reset gapów na tagu | Po zmianie gapów klik resetuje wartości i wyłącza gappy dla taga. |
| `Mod` + prawy przycisk na oknie | resize floating | Trzymając `Mod`, zmień rozmiar okna. |
| `Mod` + scroll up na oknie | zwiększa gappy | Na tagu z gapami wartość gapów rośnie. |
| `Mod` + scroll down na oknie | zmniejsza gappy | Na tagu z gapami wartość gapów maleje. |
| Lewy klik w tag | widok tagu | Kliknięty tag staje się aktywny. |
| Prawy klik w tag | toggle widoku taga | Kliknięty tag jest dołączany/odłączany od widoku. |
| `Mod` + lewy klik w tag | przenieś aktywne okno na tag | Aktywne okno trafia na kliknięty tag. |
| Lewy/środkowy/prawy/scroll/Shift+lewy klik w statusbar | sygnał do właściwego bloku `dwmblocks` | Klik w segment statusbara odpala akcję bloku, jeśli jego skrypt obsługuje sygnał i przycisk. |
| Lewy/środkowy klik w `🎙` statusbar | OS-level microphone kill switch | `sb-mic` zmienia `🎙on`/`🎙mute`; wszystkie źródła bez `.monitor` zmieniają mute. |
| Prawy klik w `🎙` statusbar | help mikrofonu | Pojawia się `notify-send` z opisem modułu. |
| Lewy/środkowy klik w `🖥`/`💤`/`☕` statusbar | caffeine toggle | `sb-idle` zmienia `🖥Xm`/`💤Xm` na `☕on`; `systemd-inhibit --list` pokazuje inhibitor. Drugi klik wyłącza inhibitor. |
| Prawy klik w `🖥`/`💤`/`☕` statusbar | help idle/caffeine | Pojawia się `notify-send` z opisem modułu. |
| Środkowy klik w root window | toggle bar | Przy kliknięciu w puste tło bar znika/pokazuje się. |

## Testy regresji wymagane przed instalacją

| Obszar | Komenda/test | Oczekiwany wynik |
| --- | --- | --- |
| Build dwm | `make clean && make` w `dwm-upstream` | Brak warningów i errorów. |
| Build dmenu | `make clean && make` w `dmenu` | Brak warningów i errorów. |
| Build dwmblocks | `make clean && make` w `dwmblocks` | Brak warningów i errorów. |
| Font fallback | `fc-match 'Atkinson Hyperlegible Mono'`, `fc-match 'JetBrainsMonoNL Nerd Font'`, `fc-match 'Noto Sans Symbols 2'`, `fc-match 'NotoColorEmoji'` | Fontconfig znajduje realne pliki, nie fallback typu `DejaVuSans.ttf` dla emoji. |
| `sysact` syntax | `sh -n ~/.local/bin/sysact` | Brak błędów składni. |
| `dmenuunicode` syntax | `sh -n ~/.local/bin/dmenuunicode` | Brak błędów składni. |
| Status scripts syntax | `sh -n`/`bash -n` na aktywnych skryptach statusbara | Brak błędów składni. |
| Statusbar tofu risk | ręcznie uruchomić aktywne skrypty statusbara | Output zawiera zamierzone emoji, a font stack ma `NotoColorEmoji`. |
| CPU | `ps -eo pid,tty,stat,pcpu,comm,args | rg 'dwm|dwmblocks'` | Aktywny `dwm` i `dwmblocks` nie mielą CPU w idle. |
