#!/bin/bash

# TODO get config file from argument

if [ ! -f ~/backupconfig.sh ]; then
	echo "config file not found!"
	exit 0
fi

source ~/backupconfig.sh

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

date_started=$(date +%Y-%m-%d)

if [ -d "${dest_dir}" ] ; then
	cd ${dest_dir}
else
	echo "destination directory not found!"
	exit 0
fi

rsync -aR \
 --delete-after \
 --fuzzy \
 --fuzzy \
 --verbose --human-readable --info=progress2 \
 --compress --compress-level=9 \
 --exclude=".Private" \
 --exclude=".ecryptfs" \
 --exclude=".cache" \
 --exclude=".local/share" \
 --exclude=".nobackup" \
 --exclude=".mozilla" \
 --exclude="tor-browser_en-US" \
 --ignore-missing-args \
 -e ssh ${source_ssh}:${source_dir} ${archive_name}-${date_started} \
 --link-dest="${dest_dir}/${archive_name}-last"

if [ "$?" -eq "0" ] ; then
	sync
	ln -nsf ${archive_name}-${date_started} ${archive_name}-last
	echo -e "${GREEN}Success.${NC} latest backup is now ${archive_name}-${date_started}"
else
	echo -e "${RED}Error${NC} while running rsync. resetting back..."
	rm -rf ${archive_name}-${date_started}
fi