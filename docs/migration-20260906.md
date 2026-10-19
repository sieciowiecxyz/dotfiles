# Local migration, 2026-09-06

- Repository moved from `~/.dotfiles-work` to `~/dev/dotfiles`.
- Live tracked home files were copied into the repository before linking them.
- Added current statusbar scripts, idle/power controls and screenshot-select.
- Source trees moved out of `~/.local/src`; full originals, including nested Git
  histories, remain in `~/dev/dotfiles-backups/20260906-migration/src`.
- Former bare Git repository is preserved in the same backup as `bare-dotfiles`.
- Main DWM is the customized 6.8 tree formerly named dwm-upstream, upstream commit
  `44dbc6809d05b8f2addc483f882e670db0b6b8e9`, with local changes preserved.
- Main st source is the customized mrdotx 0.9.3 tree. Its rebuilt executable does
  not have the same checksum as the previously installed st; the installed st
  executable is preserved unchanged during this migration.
- DWM, st, dmenu and dwmblocks compiled successfully. DWM was installed and
  restarted via SIGHUP; the running executable checksum matches the new build.
- `/usr/local/bin/dwm` forwards to `~/.local/bin/dwm` for older session PATHs.
- No remote push was performed. Previous test reports are historical records.

## Current layout, 2026-10-19

DWM 6.4 source and executable backups have been removed. The socket-enabled
st 0.9.1 source was moved from the migration backup to
`~/dev/rust/interview/streamer/st` and published in that repository. Its nested
Git history is preserved separately as `src/st-socket-history.git` in the
migration backup. The source under `suckless/st` remains the everyday st 0.9.3.
The statements above describe the original migration, not the current remote
publication state.
