# If not running interactively, don't do anything
[[ $- != *i* ]] && return

PS1='[\u@\h \W]\$ '

alias ls='ls --color=auto'
alias grep='grep --color=auto'
alias dotfiles='/usr/bin/git --git-dir=$HOME/.dotfiles/ --work-tree=$HOME'

[ -f "$HOME/.config/shell/env.sh" ] && . "$HOME/.config/shell/env.sh"
function nvim() {
  NVIM_TEST=1 command nvim "$@"
}
