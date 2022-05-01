#!/bin/sh
set -e
if test "$CONFIGURATION" = "Debug"; then :
  cd /Users/denkan/TND004/Labs/lab3/build
  echo Build\ all\ projects
fi
if test "$CONFIGURATION" = "Release"; then :
  cd /Users/denkan/TND004/Labs/lab3/build
  echo Build\ all\ projects
fi
if test "$CONFIGURATION" = "MinSizeRel"; then :
  cd /Users/denkan/TND004/Labs/lab3/build
  echo Build\ all\ projects
fi
if test "$CONFIGURATION" = "RelWithDebInfo"; then :
  cd /Users/denkan/TND004/Labs/lab3/build
  echo Build\ all\ projects
fi

