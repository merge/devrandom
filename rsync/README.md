# rsync backup solution
* maximum compression - obvious
* incremental backup using hardlinks: `--link-dest` pointing to the last backup
* Recognize renamings: The second `--fuzzy` option should compare a source file
to all of `--link-dest`.

		source_ssh=<see ssh config>
		source_dir=<dir at ssh source>
		destination=<local dir destination>
		archive_name=<prefix>
		date_started=$(date +%Y-%m-%d)

		rsync -aR \
		--delete-delay \
		--fuzzy \
		--fuzzy \
		--verbose --human-readable --info=progress2 \
		--compress --compress-level=9 \
		--exclude=".Private" \
		--exclude=".ecryptfs" \
		--exclude=".cache" \
		-e ssh ${source_ssh}:${source_dir} ${archive_name}-${date_started} \
		--link-dest="${destination}/${archive_name}-last"

		sync

		ln -nsf ${archive_name}-${date_started} ${archive_name}-last

