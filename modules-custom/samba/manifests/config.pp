/**
 * 
 * Configures samba and shares /var/www
 * 
 */
class samba::config {
	
	file { "/etc/samba/smb.conf" :
		ensure => present,
		content => template("samba/smb.conf.erb"),
		owner => "root",
		group => "root",
		require => Class["samba::install"],
		notify => Class["samba::service"],
	}
	
}