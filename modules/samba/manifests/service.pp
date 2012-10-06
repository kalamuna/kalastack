
class samba::service {
	service { "samba":
		name => "smbd",
		ensure => running,
		hasstatus => true,
		hasrestart => true,
		enable => true,
		require => Class["samba::install"],
	}
}