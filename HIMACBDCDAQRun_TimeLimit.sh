#!/usr/bin/env bash
say "Start"

bash KOMACDAQRun.sh $1

sleep 100

bash KOMACDAQStop.sh

say "End"



