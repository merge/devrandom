# a restrictive OpenWRT Tor router
This is brainstorming only!

## don't run Tor but allow only Tor
The idea here is to have a router that forces users to use Tor for any and
all connections - for example to use Tor Browser.

We have to whitelist about 2000 ip:port combinations and drop everything else.

### consensus source
We need to hourly fetch a consesus file. Do we have to use a Network Authority?
See https://consensus-health.torproject.org/

### iptables and ipset
Untested.



This uses a consensus file, parses for servers with Guard flag, refactors
for `ipset` and runs `ipset add` on each server in the list:


		ipset create guardset
		cat consensus | grep -B 1 Guard | grep -o '[0-9]\{2,3\}\.[0-9]\{1,3\}\.[0-9]\{1,3\}\.[0-9]\{1,3\}\ [0-9]\{1,5\}' | tr ' ' ',' | while read entry; do ipset add guardset $entry; done


To enable it:

TODO


		iptables -A INPUT -m set ! --match-set guardset src -j DROP


### hourly update
https://wiki.gentoo.org/wiki/IPSet

### OpenWRT network
We want to apply iptables to the wifi...

### Hardware
What constraints do we have here?
