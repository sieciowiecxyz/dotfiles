# Local Assets

This build can use private local assets without shipping them in the source tree.

## Microphone Mute Sound

`mic-kill-switch` checks this optional file:

```text
~/.local/share/dwm/sounds/mic-muted.oga
```

If the file exists, it is used for microphone mute feedback. If it does not
exist, the script falls back to freedesktop system sounds:

```text
/usr/share/sounds/freedesktop/stereo/dialog-warning.oga
/usr/share/sounds/freedesktop/stereo/bell.oga
```

This keeps personal or copyrighted sounds out of the release while still
allowing local customization.
