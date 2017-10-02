# bits about tor relay configurations

## Offline master key
For a new relay, let's use the
[https://trac.torproject.org/projects/tor/wiki/doc/TorRelaySecurity/OfflineKeys offline master key]
feature. Since we build tor's latest release manually and upgrade and monitor
our relay's system more or less manually, we need access to it at all times
anyways. If we lose access, the relay goes down automatically.

### first time generate encrypted `ed25519_master_id_secret_key`
Let's use a relatively new Debian system, without non-free.

* `tor --SigningKeyLifetime '3 months' --keygen --DataDirectory </path/to/save>`
* Use a password!
* `keys` directory is generated there
* move `ed25519_master_id_public_key`, `ed25519_signing_secret_key` and `ed25519_signing_cert` to the relay system
* move them to DataDir/keys/.
* chown them to tor's user there
* adjust filesystem permissions: `chmod -R u+X,og-rwx /DataDir/`
* start tor

if `secret_id_key` is generated during tor startup, it can be ignored.

### `torrc`


		OfflineMasterKey 1


### renew the signing key
* `tor --keygen --SigningKeyLifetime '3 months' --DataDirectory </path/to/save>` (path where keys directory *with* master key is inside)
* verify what key files are old and new
* move `ed25519_master_id_public_key`, `ed25519_signing_secret_key` and `ed25519_signing_cert` to the relay system
* chown them to tor's user there
* adjust filesystem permissions: `chmod -R u+X,og-rwx /DataDir/`
* move them to DataDir/keys/.
* done. restarting or reloading Tor after renewing the keys is *not* required.

### check expiration date
* Does `tor --key-expiration sign` exit or start tor?
* python script to run on the cert is available

## exit relay config
This will not describe everything we do in preparation for running an exit relay.
Just some thoughts:
* whois
* abuse mail forwarding
* open relay, no closed ports
* reverse dns

### `torrc`

		ExitPolicy reject *:25
		ExitPolicy accept *:*
		ExitRelay 1
		IPv6Exit 1


## general relay config
This is what we want to consider for any relay we run.

### `/etc/security/limits.conf`


		*               soft    nofile          4096
		*               hard    nofile          65535


### sysctl

		sysctl -p << EOF
		net.ipv4.tcp_rmem = 4096 87380 16777216
		net.ipv4.tcp_wmem = 4096 65536 16777216
		net.core.netdev_max_backlog = 2500
		net.ipv4.tcp_no_metrics_save = 1
		net.ipv4.tcp_moderate_rcvbuf = 1
		net.core.rmem_max = 1048575
		net.core.wmem_max = 1048575
		EOF

### `torrc`

		ORPort XXX
		ORPort [ipv6]:XXX
		Nickname XXX
		RleayBandwidthRate...
		RleayBandwidthBurst...
		RunAsDaemon 1
		AvoidDiskWrites 1
		DirPort XX
		DisPortFrontPage...
