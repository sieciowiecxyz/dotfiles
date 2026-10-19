#!/bin/sh

[ ! -r "$HOME/.config/shell/env.sh" ] || . "$HOME/.config/shell/env.sh"

export XDG_SESSION_TYPE=x11
export XDG_CURRENT_DESKTOP=dwm
export XDG_SESSION_DESKTOP=dwm
export DESKTOP_SESSION=dwm
unset WAYLAND_DISPLAY

# Preserve the integration scripts shipped by Arch packages.
if [ -d /etc/X11/xinit/xinitrc.d ]; then
    for script in /etc/X11/xinit/xinitrc.d/?*.sh; do
        [ ! -x "$script" ] || . "$script"
    done
    unset script
fi

# Import session identity after the standard DISPLAY/XAUTHORITY setup.
systemctl --user unset-environment WAYLAND_DISPLAY
systemctl --user import-environment PATH XDG_SESSION_TYPE XDG_CURRENT_DESKTOP XDG_SESSION_DESKTOP DESKTOP_SESSION
dbus-update-activation-environment --systemd PATH XDG_SESSION_TYPE XDG_CURRENT_DESKTOP XDG_SESSION_DESKTOP DESKTOP_SESSION

xset +dpms
xset dpms 360 360 360
xset s 360 360
xset r rate 300 50

if [ -f "$HOME/.nvidia-settings-rc" ]; then
    nvidia-settings --load-config-only &
fi
setbg "$HOME/.local/share/wallpapers/black-3840x2160.png"
gen-xresources
setxkbmap -layout pl -option ''
power-mode apply-current --quiet >/dev/null 2>&1 &

# D-Bus/systemd activate GNOME Keyring on demand.
exec dwm-session
