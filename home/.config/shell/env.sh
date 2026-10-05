export PATH="$HOME/.local/bin:$HOME/.local/bin/statusbar:$PATH"
export PATH="$HOME/.cargo/bin:$PATH"
export TERMINAL="st"
export EDITOR="nvim"
export HISTFILESIZE=20000
export HISTSIZE=10000

export PNPM_HOME="$HOME/.local/share/pnpm"
case ":$PATH:" in
  *":$PNPM_HOME:"*) ;;
  *) export PATH="$PNPM_HOME:$PATH" ;;
esac

. "$HOME/.cargo/env"

# Keep machine-specific locations and local paths outside the public dotfiles.
[ ! -r "$HOME/.config/shell/local-env.sh" ] || . "$HOME/.config/shell/local-env.sh"
