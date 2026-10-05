#!/bin/sh

[ -f "$HOME/.config/shell/env.sh" ] && . "$HOME/.config/shell/env.sh"

# Keep X idle policy enabled. dwm-idle/power-mode may force display off later.
xset +dpms
xset dpms 360 360 360
xset s 360 360

[ -f ~/.nvidia-settings-rc ] && nvidia-settings --load-config-only &

setbg ~/.local/share/wallpapers/black-3840x2160.png

gen-xresources

setxkbmap -layout pl -option ''

dwmblocks &

xset r rate 300 50 &

DWM_IDLE_SCREEN_OFF_CMD="power-mode blank"
DWM_IDLE_SUSPEND_SECONDS=0
export DWM_IDLE_SCREEN_OFF_CMD
export DWM_IDLE_SUSPEND_SECONDS
dwm-idle &

# Inject environment to systemd BEFORE starting services
systemctl --user import-environment DISPLAY XAUTHORITY XDG_CURRENT_DESKTOP XDG_SESSION_TYPE WAYLAND_DISPLAY
dbus-update-activation-environment --systemd DISPLAY XAUTHORITY XDG_CURRENT_DESKTOP XDG_SESSION_TYPE WAYLAND_DISPLAY

# Start graphical target for systemd user services
systemctl --user start graphical-session.target

gnome-keyring-daemon --start --components=secrets &

power-mode apply-current --quiet >/dev/null 2>&1 &

exec dwm
