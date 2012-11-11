#!/bin/sh

if which getconf > /dev/null; then
	CPUS=$(getconf _NPROCESSORS_ONLN)
else
	CPUS=1
fi

echo $((CPUS*2))
