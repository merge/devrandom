# Thinkpad X220 Setup Notes

## General Debian Setup

synaptics TapButton1 and TapButton2

## coreboot
* config

### suspend to RAM
Ideally systemd's defaults would just work. For me they don't, so we disable them
according to [the Debian wiki](https://wiki.debian.org/Suspend):

    systemctl mask sleep.target suspend.target hibernate.target hybrid-sleep.target

And we use pm-utils instead: `apt-get install pm-utils`

We create `/etc/pm/config.d/40-coreboot-compat` and put in
`ADD_PARAMETERS="--quirk-reset-brightness --quirk-vbe-post --quirk-vbestate-restor --quirk-vbemode-restore"`
and pm-suspend should now work.

Now use `acpid` systemd service and create `/etc/acpi/events/lid` containing

    event=button/lid
    action=/etc/acpi/lid.sh

and the corresponding lid.sh containing

    #!/bin/bash
    # if launched through a lid event and lid is open, do nothing
    grep -q closed /proc/acpi/button/lid/LID/state
    if [ $? = 0 ]
    then
    	xtrlock -f -b
    	pm-suspend
    fi

