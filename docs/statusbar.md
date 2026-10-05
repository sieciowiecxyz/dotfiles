# Statusbar

`dwmblocks/config.h` selects modules; `home/.local/bin/statusbar` contains their
scripts. CPU and GPU modules each show load, temperature and memory usage.

The local DWM renderer supports `^0^` (default), `^1^` (white), `^2^` (green),
`^3^` (yellow), `^4^` (orange-red). Each metric resets its colour with `^0^`.
Drawing and mouse hit testing use the same width parser. Palette colours live
in `suckless/dwm/config.h`, thresholds in `sb-cpu-simple` and `sb-gpu-simple`.

Thresholds selected for the local Ryzen 9 9900X3D, 96 GB RAM without swap,
and RTX 5070 Ti 16 GB:

| Metric | Default text: low | Green: medium | Yellow: high | Orange-red: very high |
| --- | --- | --- | --- | --- |
| CPU/GPU load | <30% | 30–59% | 60–89% | ≥90% |
| CPU temperature | <60°C | 60–79°C | 80–89°C | ≥90°C |
| GPU temperature | <50°C | 50–74°C | 75–84°C | ≥85°C |
| RAM occupied | <50% | 50–79% | 80–89% | ≥90% |
| VRAM occupied | <50% | 50–79% | 80–94% | ≥95% |

These are display thresholds, not hardware safety limits. RAM usage is
MemTotal minus MemAvailable, so reclaimable cache does not trigger a warning.
VRAM colour uses memory.used / memory.total, not memory controller utilisation.
The displayed G values are rounded GiB; colours use unrounded memory data.

Updates use `paru -Qu --color never` (repo + AUR), every 30 minutes and on
signal 8. Repository results depend on the last database sync, while AUR is
queried online. Ignored packages are excluded. Failed checks display `📦?`.
Left click runs `paru -Syu`; middle click displays the package list.
