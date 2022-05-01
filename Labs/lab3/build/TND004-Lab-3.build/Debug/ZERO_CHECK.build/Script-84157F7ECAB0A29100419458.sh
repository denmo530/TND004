#!/bin/sh
set -e
if test "$CONFIGURATION" = "Debug"; then :
  cd /Users/denkan/TND004/Labs/lab3/build
  make -f /Users/denkan/TND004/Labs/lab3/build/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "Release"; then :
  cd /Users/denkan/TND004/Labs/lab3/build
  make -f /Users/denkan/TND004/Labs/lab3/build/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "MinSizeRel"; then :
  cd /Users/denkan/TND004/Labs/lab3/build
  make -f /Users/denkan/TND004/Labs/lab3/build/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "RelWithDebInfo"; then :
  cd /Users/denkan/TND004/Labs/lab3/build
  make -f /Users/denkan/TND004/Labs/lab3/build/CMakeScripts/ReRunCMake.make
fi

