#!/bin/sh
set -eu

repo_dir=$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)
for project in dmenu dwm dwmblocks st; do
	make -C "$repo_dir/home/.local/src/$project"
done
