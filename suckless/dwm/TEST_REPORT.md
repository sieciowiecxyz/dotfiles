# dwm migration test report

Data testu: 2026-06-21, `DISPLAY=:1`.

## Wynik

Aktualizacja 2026-06-21 02:35:
- TS3 mute sound z `/home/sieciowiec/Pobrane/microphone-muted-teamspeak.mp3` został przekonwertowany do lokalnego assetu `/home/sieciowiec/.local/share/dwm/sounds/mic-muted.oga`.
- Finalny asset to Ogg/Vorbis, stereo, `44100 Hz`, około `0.91s`; `paplay --volume=65536 ~/.local/share/dwm/sounds/mic-muted.oga` przeszedł poprawnie.
- `mic-kill-switch` używa `~/.local/share/dwm/sounds/mic-muted.oga`, jeśli istnieje; jeśli nie istnieje, wraca do freedesktop `dialog-warning.oga` + `bell.oga`.
- Dodano `docs/local-assets.md`, żeby release nie wymagał i nie zawierał prywatnego/copyrightowego dźwięku.
- Dodano `xidle-ms` (`tools/xidle-ms.c`); `dwm-upstream/Makefile` buduje go razem z `dwm` i instaluje do `/usr/local/bin/xidle-ms`.
- Dodano `dwm-idle`: lock + display off po `6 min` (`DWM_IDLE_SCREEN_SECONDS=360`), suspend po `10 min` (`DWM_IDLE_SUSPEND_SECONDS=600`), z pominięciem suspendu przy aktywnym caffeine albo procesach typu `qemu-system`.
- `.xinitrc` startuje teraz `dwm-idle &`; stary zakomentowany `xss-lock -- auto-suspend.sh` został zastąpiony.
- Dodano `caffeine-toggle` na `systemd-inhibit --what=idle:sleep`; `on` blokuje sleep/idle suspend, `off` przywraca automatyczny sleep.
- Dodano `sb-idle` w `dwmblocks`: pokazuje `🖥Xm` do lock/display-off, `💤Xm` do suspend albo `☕on`; klik lewy/środkowy toggluje caffeine.
- `dwmblocks/config.h` ma `{"", "sb-idle", 10, 13}` po volume.
- Test `timeout` dla `dwm-idle` przeszedł z podmienionymi komendami `lock/screen/suspend=true`, bez realnego gaszenia ekranu ani suspendu.
- Test `caffeine-toggle on/off` pokazał realny inhibitor w `systemd-inhibit --list` i potem wrócił do `💤auto`.
- Runtime test na wcześniejszej aktywnej sesji pokazał statusbar z `🖥6m`; po późniejszym zamknięciu X nie ma aktywnego `dwm`/`Xorg`, więc bieżący test runtime idle wymaga następnego `startx`.
- Test realnego `mic-kill-switch` z lokalnym dźwiękiem przeszedł: `🎙on` po unmute, `🎙mute` po drugim toggle, finalnie wszystkie input sources zostały `Mute: yes`.
- `st` ma zwiększony scrollback `HISTSIZE 10000` zamiast `2000`.
- Dodano `copyvisible()` w `st`: `Ctrl+Shift+O` kopiuje cały aktualny widok terminala do PRIMARY i CLIPBOARD.
- `st` został przebudowany i zainstalowany; `/usr/local/bin/st -v` zwraca `0.9.3`, a `nm /usr/local/bin/st` pokazuje symbol `copyvisible`.
- Test interaktywny `Ctrl+Shift+O` przez `xdotool` przeszedł: tymczasowe okno `st` skopiowało `COPYVISIBLE_TEST_ALPHA/BETA`, a `xclip -selection clipboard -o` odczytał oba wiersze.
- Layout keymap został uproszczony do górnego rzędu bez `Shift`: `Super+t tile`, `Super+y cols`, `Super+i center`, `Super+u rows`, `Super+o float`.
- `nmaster` został przeniesiony z `Super+o`/`Super+Shift+o` na `Super+p`/`Super+Shift+p`.
- `layouthelpcmd` pod prawym klikiem w symbol layoutu pokazuje nowe skróty.
- `float` ma teraz jawny symbol layoutu zamiast `NULL`, więc `Super+o` nie ryzykuje dereferencji pustego symbolu.
- `dwm` został przebudowany, zainstalowany i przeładowany przez `SIGHUP`; test `xdotool key super+t/y/i/u/o/p/shift+p` przeszedł, `dwm` pozostał żywy z CPU około `0.1%`.
- Po poprawce release-safety `make clean && make && sudo -n make install` w `dwm-upstream` instaluje `/usr/local/bin/dwm` oraz `/usr/local/bin/xidle-ms`.
- `make dist` w `dwm-upstream` przeszedł; `dwm-6.8.tar.gz` zawiera `Makefile` oraz `tools/xidle-ms.c`.
- Bieżące środowisko po zamknięciu sesji X nie ma aktywnego `Xorg`/`dwm`, więc następny pełny runtime check dla `dwm-idle`/`sb-idle` należy zrobić po `startx`.

Aktualizacja 2026-06-21 02:15:
- `mic-kill-switch` ma mocniejszy feedback na mute: odtwarza `dialog-warning.oga` i `bell.oga` z `paplay --volume=65536`; unmute nadal używa krótszego `complete.oga`.
- Dodano blok `sb-mic` i wpis `{"", "sb-mic", 0, 12}` w `dwmblocks/config.h`; blok stoi po lewej od `sb-volume`.
- `sb-mic` pokazuje `🎙on`, `🎙mute` albo `🎙none`; lewy/środkowy klik odpala `mic-kill-switch`, prawy klik pokazuje help.
- `mic-kill-switch` wysyła teraz `RTMIN+12`, więc blok mikrofonu odświeża się natychmiast po mute/unmute.
- `sb-cpu-simple` i `sb-gpu-simple` nie pokazują już totalu RAM/VRAM: format to np. `🧠1% 50C 10G` i `🎮5% 55C 1G`.
- `dwmblocks` został przebudowany, zainstalowany i uruchomiony na `DISPLAY=:0`; po kilku sekundach `ps` pokazał `0.0% CPU`.
- Test składni przeszedł dla `mic-kill-switch`, `sb-mic`, `sb-cpu-simple`, `sb-gpu-simple`.
- Test outputu bloków przeszedł: `sb-mic` zwrócił `🎙mute`, CPU/GPU zwróciły skrócony format bez `/total`.
- Aktywne XRDB dla `st` ma teraz `st.background: #000000` i `st.alpha: 1.0`; ANSI colors i foreground nadal idą z pywal.
- `gen-xresources` i `.Xresources_fallback` ustawiają terminal-only OLED black, bez wymuszania czarnego tła statusbara/dwm.
- `sb-clock` pokazuje sekundy (`%H:%M:%S`), a `dwmblocks/config.h` odświeża clock block co `1s`.
- Po restarcie `dwmblocks` root `WM_NAME` zawiera czas z sekundami, a `ps` po 5 sekundach nadal pokazał `0.0% CPU`.

Aktualizacja 2026-06-21 02:00:
- Dodano `/home/sieciowiec/.local/bin/mic-kill-switch`: mutuje/odmutowuje wszystkie źródła wejściowe Pulse/PipeWire poza `.monitor`, czyli fizyczne mikrofony/line-in oraz wirtualne mikrofony typu `deepfilter` i `echo-cancel`.
- Logika jest kill-switchowa: jeśli choć jedno wejście jest odmutowane, skrót mutuje wszystkie; jeśli wszystkie są już muted, drugi skrót odmutowuje wszystkie.
- Podpięto `Mod+Shift+m` oraz `XF86 AudioMicMute` pod ten sam skrypt.
- Test składni `sh -n ~/.local/bin/mic-kill-switch` przeszedł.
- Test realny skryptu: źródła `41`, `43`, `141`, `142` przeszły na `Mute: yes`, drugi toggle wrócił na `Mute: no`.
- Test realnego skrótu przez `xdotool key super+shift+m` przeszedł tak samo: wszystkie inputy muted, drugi raz wszystkie unmuted.
- `dwm` został przebudowany, zainstalowany i przeładowany przez `SIGHUP`; aktywny proces działa dalej, idle CPU około `0.1%`.

Aktualizacja 2026-06-21 01:45:
- `sb-media` ma teraz interwał `1s` w `dwmblocks/config.h`, żeby czas utworu i stan play/pause były bardziej natychmiastowe.
- Scroll na bloku media ma debounce `500ms` (`MEDIA_SCROLL_DEBOUNCE_MS`), więc szybki impuls z MX Master nie powinien przeskakiwać kilku tracków naraz.
- `sb-media` trzyma ostatni poprawny output przez `8s` (`MEDIA_GRACE_SECONDS`), więc przy zmianie tracka/blinku MPRIS nie znika agresywnie z paska.
- Test `sh -n ~/.local/bin/statusbar/sb-media` przeszedł, zwykły output zwrócił aktualny track z czasem.
- Test cache fallback przez fałszywe `playerctl=/bin/false` zwrócił ostatni zapisany track.
- Test debounce: dwa wywołania `BLOCK_BUTTON=5` w czasie poniżej `500ms` zostawiły ten sam timestamp w `~/.cache/dwm/sb-media.scroll`.
- `dwmblocks` został przebudowany, zainstalowany i uruchomiony na `DISPLAY=:0`; po kilku sekundach `ps` pokazał `0.0% CPU`.

Aktualizacja 2026-06-21 01:05:
- `sysact renew dwm` został przetestowany realnie przez menu: `sysact` otwarte na `DISPLAY=:0`, wpisane `renew`, zatwierdzone, `dwm` pozostał żywy.
- `dwm` ustawia teraz `_NET_WM_PID` na `_NET_SUPPORTING_WM_CHECK`; `sysact` używa tego PID zamiast kruchego `pstree`.
- `Super+Backspace` po usunięciu variation selectorów z `sysact` nie pokazuje już tofu przy `renew`/`shutdown` w screenshot teście `/tmp/dwm-audit-super-backspace-fixed.png`.
- `Super+grave` / `dmenuunicode` filtruje `U+FE0F` i `U+200D`; widoczne wpisy w screenshot teście `/tmp/dwm-audit-dmenuunicode-fixed.png` nie pokazują dodatkowych prostokątów.
- Głośność w górę ma hard cap `wpctl set-volume -l 1.0`; runtime test przy `Volume: 1.00` pozostał na `Volume: 1.00`.
- Pobrano, zbudowano i zainstalowano `mrdotx/st`; `/usr/local/bin/st -v` zwraca `0.9.3`, a testowe okno X z emoji uruchomiło się poprawnie.
- Aktywne XRDB ma wspólny font setup: `Atkinson Hyperlegible Mono`, `NotoColorEmoji`, `JetBrainsMonoNL Nerd Font`, `Noto Sans Symbols 2` dla `dwm`, `dmenu` i `st`.
- Dodano blok `sb-media` przed volume w `dwmblocks`; pokazuje MPRIS/playerctl track + elapsed/total time.
- Dodano skróty `Mod+,` previous, `Mod+.` play/pause, `Mod+/` next, `Mod+-` volume down, `Mod+=` volume up z capem 100%, `Mod+m` mute/unmute.
- Test `Mod+.` zmienił `Playing -> Paused -> Playing`; test `Mod+m` zmienił `Volume: 1.00 -> Volume: 1.00 [MUTED] -> Volume: 1.00`.
- Test `Mod+=` przy `Volume: 1.00` pozostał na `1.00`; `Mod+-` zszedł do `0.97`, a `Mod+=` przywrócił `1.00`.
- Test `Mod+/` i `Mod+,` wysłał komendy, ale aktualny YouTube Shorts MPRIS nie zmienił tytułu; to zależy od obsługi next/previous przez dany web player.

Buildy:
- `dwm-upstream`: `make clean && make` przeszedł bez warningów i errorów.
- `dmenu`: `make clean && make` przeszedł bez warningów i errorów.
- `dwmblocks`: `make clean && make` przeszedł bez errorów.

Instalacja:
- `sudo -n make install` dla `dwm`, `dmenu`, `dwmblocks` przeszedł poprawnie.
- `dwmblocks` został zrestartowany z `/usr/local/bin/dwmblocks`.
- Aktywny proces `dwm` nie został przeładowany, bo aktualnie uruchomiony PID `200413` nie łapie `SIGHUP` (`SigCgt=0`). Wysłanie `HUP` zakończyłoby sesję X zamiast zrobić safe restart. Nowa zainstalowana binarka ma już obsługę restartu przez `SIGHUP`; zacznie działać po następnym `startx`/restarcie sesji.

CPU:
- Stary runaway `dwm` na `tty1/:0`, PID `8901`, zużywał około `98% CPU`.
- Proces `8901` został zakończony przez `SIGTERM`; stara sesja `:0` zniknęła.
- Aktywny `dwm` PID `200413` przez 5 próbek idle miał `0.0% CPU`.
- Nowy `dwmblocks` PID `345687` przez 5 próbek idle miał `0.0% CPU`.
- Aktywny `Xorg :1` miał około `3.2% CPU`.

Fonty:
- `Atkinson Hyperlegible Mono` nie był wcześniej zainstalowany i fallbackował do `Noto Sans Mono`.
- Font został zainstalowany lokalnie do `~/.local/share/fonts/atkinson-hyperlegible-mono`.
- `fc-match 'Atkinson Hyperlegible Mono'` zwraca teraz `AtkinsonHyperlegibleMono-Regular.ttf`.
- `JetBrainsMonoNL Nerd Font`, `Noto Sans Symbols 2`, `NotoColorEmoji` są widziane przez fontconfig.

XRDB:
- Aktywne `dmenu.font` zostało zmienione z `monospace:size=10` na `Atkinson Hyperlegible Mono:size=12`.
- Aktywne `dwm.gappih/gappiv/gappoh/gappov` są `0`.
- Aktywne `dwm.smartgaps` jest `0`.
- `~/.local/bin/gen-xresources` i `~/.config/x11/.Xresources_fallback` zostały poprawione, żeby zmiany nie znikały po restarcie.

Smoke test dmenu:
- `sysact` otworzył menu na `DISPLAY=:1`, przyjął `Escape`, zakończył się kodem `1`, bez stderr.
- `dmenuunicode` otworzył menu; pierwszy automatyczny `Escape` nie trafił w fokus, więc testowy proces został ręcznie zamknięty. Brak stderr.
- Nie wykonano screenshot-testu tofu/kwadratów, bo w systemie brakuje `Xvfb`, `Xephyr`, `maim`, `xwd`. Test procesu i fontconfig przeszedł, ale wizualna asercja wymaga albo ręcznego spojrzenia, albo doinstalowania narzędzia do screenshotów.

Statusbar:
- Aktywne skrypty statusbara zwracają poprawne Unicode/emoji:
- `sb-volume`: `🔊100%`
- `sb-cpu-simple`: `🧠...`
- `sb-gpu-simple`: `🎮...`
- `sb-forecast`: `☔... 🥶...° 🌞...°`
- `sb-clock`: data/czas bez emoji.
- `sb-pacpackages`: pusty output przy braku aktualizacji.
- `dwmblocks` root `WM_NAME` zawiera bajty kontrolne sygnałów. To jest oczekiwane dla klików statusbara. Poprawiony `dwm` filtruje te bajty przed renderowaniem; aktywny stary proces może dalej pokazywać śmieci do restartu sesji.

## Diff / rozmiar

Względem upstream `dwm`:
- `dwm.c`: `+508`, `-97`, razem `2576` linii.
- `config.h` względem `config.def.h`: `+214`, `-81`, razem `250` linii.
- `vanitygaps.c`: dodatkowe `275` linii.
- `KEYBIND_TESTS.md`: `132` linie test matrix.

## Blokery pełnej automatycznej walidacji

- Brak headless X (`Xvfb`/`Xephyr`) uniemożliwia uruchomienie nowego `dwm` obok aktywnej sesji.
- Aktywny `dwm` PID `200413` nie łapie `SIGHUP`, więc nie da się go bezpiecznie przeładować do nowej binarki bez zamknięcia sesji X.
- Brak narzędzia screenshotowego (`maim`/`xwd`) uniemożliwia automatyczne potwierdzenie wizualne, że dmenu/statusbar nie pokazują tofu.

## Następny test po restarcie X

Po wyjściu z obecnej sesji X i uruchomieniu `startx`:
- Sprawdź `ps -C dwm -o pid,stat,pcpu,args`; idle powinno być `0.0%`.
- Sprawdź statusbar wizualnie: emoji powinny wrócić bez pustych kwadratów, a kliknięcia w bloki powinny działać.
- `Super+Backspace` powinien pokazać większe menu `sysact` z emoji bez tofu.
- `Super+grave` powinien pokazać `dmenuunicode`.
- `Super+Shift+q` -> `renew dwm` powinno już robić restart przez `SIGHUP`, nie zabijać sesji.
