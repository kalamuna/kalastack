/**
 * 
 * Installs PHPMYADMIN
 * 
 */
class phpmyadmin::install {
	package { "phpmyadmin" : 
		ensure => "present",
		require => [
			Class["phpfpm"],
			Class["nginx"],
			Class["mysql"],
		]
	}
}
