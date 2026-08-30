# Arch Linux dotfiles

Personal configuration for Arch Linux with suckless tools (`dwm`, `dwmblocks`, `dmenu`, and `st`).

The repository intentionally contains configuration, scripts, patches, and source files—not compiled binaries, caches, credentials, or application databases.

## Layout

- `home/` — files mirrored into `$HOME`
- `etc/` — reviewed system configuration examples
- `packages/` — native and AUR package lists
- `scripts/` — installation and rebuild helpers
- `docs/` — machine setup notes

## Install

Review the files first, then run `scripts/install.sh`. It creates symlinks for the selected home files and does not overwrite existing files without moving them to a timestamped backup.
