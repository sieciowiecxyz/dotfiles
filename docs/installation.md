# Installation notes

1. Install Arch Linux and the packages you need from `packages/pacman.txt` and
   `packages/aur.txt`. These are snapshots of explicitly installed packages,
   not a requirement to install every application.
2. Clone this repository to `~/dev/dotfiles`.
3. Review `home/` and the package lists. `home/.local/bin/sb-power` contains the
   local Tasmota plug address; change it for another machine.
4. Run `scripts/install.sh` to link home files, backing up existing files.
5. Run `scripts/build-suckless.sh` to build, then
   `scripts/build-suckless.sh install` to install into `~/.local` as your user.
6. Keep `~/.local/bin` and `~/.local/bin/statusbar` in PATH. Start the next X11
   session with the linked `.xinitrc`.

The statusbar configuration is `suckless/dwmblocks/config.h`. Rebuild and
restart dwmblocks after changing its module list. Script-only changes take
effect at the next module refresh.

The socket-enabled terminal and its web viewer are maintained separately in
`sieciowiecxyz/interview`; this installer uses the everyday terminal only.
