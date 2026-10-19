export TERMINAL="st"
export EDITOR="nvim"
export HISTFILESIZE=20000
export HISTSIZE=10000
export PNPM_HOME="${PNPM_HOME:-$HOME/.local/share/pnpm}"

[ ! -r "$HOME/.cargo/env" ] || . "$HOME/.cargo/env"

# Private machine-specific settings may extend PATH.
[ ! -r "$HOME/.config/shell/local-env.sh" ] || . "$HOME/.config/shell/local-env.sh"

# Login shells, interactive shells and X11 can all source this file.
# Keep command precedence stable and remove repeated/empty PATH entries.
PATH=$(printf '%s' "$HOME/.cargo/bin:$HOME/.local/bin:$HOME/.local/bin/statusbar:$PNPM_HOME:$PATH" |
    awk -v RS=: 'length($0) && !seen[$0]++ { printf "%s%s", separator, $0; separator=":" }')
export PATH
