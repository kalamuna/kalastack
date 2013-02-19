/**
 * 
 * Installs PHPMYADMIN
 * 
 */
class phpmyadmin::install {
	package { "phpmyadmin" : 
		ensure => "4:3.4.10.1-1",
		require => [
			Class["phpfpm"],
			Class["nginx"],
			Class["mysql"],
		]
	}
}