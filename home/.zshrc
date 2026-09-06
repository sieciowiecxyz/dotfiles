[ -f "$HOME/.config/shell/env.sh" ] && . "$HOME/.config/shell/env.sh"

PROMPT='[%n@%m %1~]$ '

alias ls='ls --color=auto'
alias grep='grep --color=auto'
alias dotfiles='/usr/bin/git -C "$HOME/dev/dotfiles"'

function nvim() {
  NVIM_TEST=1 command nvim "$@"
}

HISTFILE="$HOME/.zsh_history"
HISTSIZE=10000
SAVEHIST=20000
setopt HIST_IGNORE_DUPS SHARE_HISTORY

KEYTIMEOUT=1
bindkey -e
bindkey '^[[1;5D' backward-word
bindkey '^[[1;5C' forward-word
bindkey '^[[5D' backward-word
bindkey '^[[5C' forward-word
bindkey '^[[1;3D' backward-word
bindkey '^[[1;3C' forward-word

autoload -Uz compinit
compinit

source /usr/share/zsh/plugins/zsh-autosuggestions/zsh-autosuggestions.zsh
bindkey '^[[C' autosuggest-accept

# Keep a slim beam cursor in st instead of the default block.
[[ -t 1 ]] && printf '\e[5 q'
# Encrypted password store managed by pass.
export PASSWORD_STORE_DIR="$HOME/dev/shell/pass"
