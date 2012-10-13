/**
 * 
 * Configures PHP5-FPM
 * Creates a basic pool
 * Loads all PHP extensions
 * 
 */
class phpfpm::config {
	
	php5::ini { "fpm": 
	  path     => "/etc/php5/fpm/php.ini",
	  require  => Class["phpfpm::install"],
	  notify => Class["phpfpm::service"],
	}
	
	file { "/etc/php5/fpm/pool.d/www.conf": 
	  ensure 	=> file,
	  content => template("phpfpm/www.conf.erb"),
	  require  => Class["phpfpm::install"],
	  notify => Class["phpfpm::service"],
	}
	
	include phpfpm::extensions::apc
	include phpfpm::extensions::xdebug 
	include phpfpm::extensions::curl
	include phpfpm::extensions::imap
	include phpfpm::extensions::pear
	include phpfpm::extensions::gd
	include phpfpm::extensions::mcrypt
	
}