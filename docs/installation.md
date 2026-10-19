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

## X11 session

`startx` reads `~/.xinitrc`, which loads Arch's `xinitrc.d` hooks, sets the
X11/DWM identity, and starts `dwm-session`. The launcher starts
`dwm-session.target`, runs DWM, and stops the target on logout or termination.
`dwmblocks` and `dwm-idle` are services belonging to that target. Do not enable
these three units at user login: the launcher starts them with the X session.

After installing changed unit files, run `systemctl --user daemon-reload`.
Session startup changes apply fully on the next `startx`; do not source
`.xinitrc` in an existing session. Standard shell login profiles are tracked,
and sourcing the shared shell environment repeatedly keeps PATH unique.

GNOME Keyring uses its packaged D-Bus/systemd socket activation. DWM uses the
GTK portal backend selected by `dwm-portals.conf`.

## Audio

WirePlumber remembers the selected output/EQ. The obsolete `eq-default.service`
was removed instead of forcing a nonexistent sink after a fixed delay.
DeepFilter and its dependent virtual call microphone were removed from the
machine. Bluetooth uses normal WirePlumber routing without references to those
removed nodes. There is no AI denoising service in this repository.

## System configuration maintenance

The 2026-10-19 `.pacnew` review kept local SSH/sudo access, encrypted boot hooks,
VFIO modules, power-button actions, persistent journals, package repositories,
and local build settings. New Fortran defaults and TPM FAPI JSON templates were
accepted. No TPM enrollment or NV indexes were changed, and the UKI was not rebuilt.
Root configuration backups are outside this repository in the protected
`~/dev/dotfiles-backups/20261019-session-audio/system-before/` directory.
