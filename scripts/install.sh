#!/bin/sh
set -eu

repo_dir=$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)
backup_dir="$HOME/dev/dotfiles-backups/links-$(date +%Y%m%d-%H%M%S)"

find "$repo_dir/home" -type f | while IFS= read -r source; do
	relative=${source#"$repo_dir/home/"}
	target="$HOME/$relative"
	mkdir -p "$(dirname "$target")"
	if [ -L "$target" ] && [ "$(readlink "$target")" = "$source" ]; then
		continue
	fi
	if [ -e "$target" ] || [ -L "$target" ]; then
		mkdir -p "$(dirname "$backup_dir/$relative")"
		mv "$target" "$backup_dir/$relative"
	fi
	ln -sfn "$source" "$target"
done

echo "Dotfiles linked. Backups: $backup_dir (if any files needed backup)."
