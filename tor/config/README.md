# bits about tor relay configurations

## Offline master key
For a new relay, let's use the
[https://trac.torproject.org/projects/tor/wiki/doc/TorRelaySecurity/OfflineKeys offline master key]
feature. Since we build tor's latest release manually and upgrade and monitor
our relay's system more or less manually, we need access to it at all times
anyways. If we lose access, the relay goes down automatically.

### generate encrypted `ed25519_master_id_secret_key`
Let's use a relatively new Debian system, without non-free.

* `tor --SigningKeyLifetime '3 months' --keygen --DataDirectory </path/to/save>`
* Use a password!
* `keys` directory is generated there
* move `ed25519_master_id_public_key`, `ed25519_signing_secret_key` and `ed25519_signing_cert` to the relay system
* move them to DataDir/keys/.
* chown them to tor's user there
* adjust filesystem permissions: `chmod -R u+X,og-rwx /DataDir/`

if `secret_id_key` is generated during tor startup, it can be ignored.

### torrc


		OfflineMasterKey 1


### renew the signing key
* `tor --keygen --SigningKeyLifetime '6 months' --DataDirectory </path/to/save>` (path where keys directory *with* master key is inside)
* verify what key files are old and new
* move `ed25519_master_id_public_key`, `ed25519_signing_secret_key` and `ed25519_signing_cert` to the relay system
* chown them to tor's user there
* adjust filesystem permissions: `chmod -R u+X,og-rwx /DataDir/`
* move them to DataDir/keys/.
* Restarting or reloading Tor after renewing the keys is *not* required.

### check expiration date
tor --key-expiration

## exit relay config

		ExitPolicy reject *:25
		ExitPolicy accept *:*
		ExitRelay 1
		IPv6Exit 1


## general relay config

		ORPort XXX
		ORPort [ipv6]:XXX
		Nickname XXX
		RleayBandwidthRate...
		RleayBandwidthBurst...
		RunAsDaemon 1
		AvoidDiskWrites 1
		DirPort XX
		DisPortFrontPage...
