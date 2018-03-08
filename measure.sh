# #!/usr/bin/env bash

# Define a timestamp function
LOGPATH="status.log"



timestamp() {
  date +"%Y-%m-%dT%T.%N"
}

rm status.log
while ( pgrep structure.py >/dev/null 2>&1 ) ; do
#cpu usage
echo -n "$(timestamp) linux::systemstatus::cpu " >> $LOGPATH
top -bn 1 | sed -n 3p >> $LOGPATH


#disk usage
echo -n "$(timestamp) linux::systemstatus::storage " >> $LOGPATH
df --total|grep total|sed "s/total//g"| sed 's/^ *//' >> $LOGPATH



done
