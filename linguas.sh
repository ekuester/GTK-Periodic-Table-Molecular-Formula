#!/bin/bash
linguas="po/LINGUAS"
IFS=$'\n'
for lingua in `cat $linguas`; do
  [[ "$lingua" =~ ^#.*$ ]] && continue
  echo "$lingua.po read from $linguas"
  rm -frv $lingua
  mkdir -p "$lingua/LC_MESSAGES"
  msgfmt po/$lingua.po -o "$lingua/LC_MESSAGES/GTKPeriodicTable.mo"
  echo "po/$lingua/LC_MESSAGES/GTKPeriodicTable.mo generated"
done

