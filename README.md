# Arch Linux dotfiles

Personal configuration for Arch Linux with suckless tools (`dwm`, `dwmblocks`, `dmenu`, and `st`).

The repository intentionally contains configuration, scripts, patches, and source files—not compiled binaries, caches, credentials, or application databases.

## Layout

- `home/` — files mirrored into `$HOME`
- `suckless/` — canonical source trees; local DWM fork based on 6.8
- `etc/` — reviewed system configuration examples
- `packages/` — native and AUR package lists
- `scripts/` — installation and rebuild helpers
- `docs/` — machine setup notes

## Install

Review the files first, then run `scripts/install.sh`. It creates symlinks for the selected home files and does not overwrite existing files without moving them to a timestamped backup.

Build with `scripts/build-suckless.sh`; install with `scripts/build-suckless.sh install`.
Programs go to `~/.local/bin`, which must precede `/usr/local/bin` in PATH.
Use `git -C ~/dev/dotfiles` (or the `dotfiles` shell alias) for version control.
Source trees are maintained directly in this repository, without nested Git repositories.

The 2026-09-06 migration preserved original source trees and their Git histories,
the old DWM 6.4 executable, and the former bare repository in
`~/dev/dotfiles-backups/20260906-migration/`.
The active DWM source is the former `dwm-upstream`, with its custom config and
the current `screenshot-select` binding. Historical test reports describe past tests.
