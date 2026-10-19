#!/usr/bin/env bash
set -euo pipefail

umask 077
runtime_dir="$(mktemp -d "${XDG_RUNTIME_DIR:-/tmp}/bt-call-agent.XXXXXX")"
fifo="$runtime_dir/control"
cleanup() {
  exec 3>&- || true
  [[ -n "${btpid:-}" ]] && kill "${btpid}" 2>/dev/null || true
  rm -f "$fifo"
  rmdir "$runtime_dir"
}
trap cleanup EXIT INT TERM

mkfifo "$fifo"
/usr/bin/bluetoothctl <"$fifo" &
btpid=$!
exec 3>"$fifo"

printf 'agent NoInputNoOutput\ndefault-agent\npairable on\n' >&3

wait "$btpid"
